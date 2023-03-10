// Copyright (C) 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "icing/schema/schema-store.h"

#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "icing/absl_ports/str_cat.h"
#include "icing/document-builder.h"
#include "icing/file/filesystem.h"
#include "icing/file/mock-filesystem.h"
#include "icing/portable/equals-proto.h"
#include "icing/proto/document.pb.h"
#include "icing/proto/schema.pb.h"
#include "icing/schema-builder.h"
#include "icing/schema/schema-util.h"
#include "icing/schema/section-manager.h"
#include "icing/schema/section.h"
#include "icing/store/document-filter-data.h"
#include "icing/testing/common-matchers.h"
#include "icing/testing/fake-clock.h"
#include "icing/testing/tmp-directory.h"
#include "icing/text_classifier/lib3/utils/base/status.h"
#include "icing/util/crc32.h"

namespace icing {
namespace lib {

namespace {

using ::icing::lib::portable_equals_proto::EqualsProto;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::HasSubstr;
using ::testing::Not;
using ::testing::Pointee;
using ::testing::Return;
using ::testing::SizeIs;

constexpr PropertyConfigProto::Cardinality::Code CARDINALITY_OPTIONAL =
    PropertyConfigProto::Cardinality::OPTIONAL;
constexpr PropertyConfigProto::Cardinality::Code CARDINALITY_REPEATED =
    PropertyConfigProto::Cardinality::REPEATED;

constexpr StringIndexingConfig::TokenizerType::Code TOKENIZER_PLAIN =
    StringIndexingConfig::TokenizerType::PLAIN;

constexpr TermMatchType::Code MATCH_EXACT = TermMatchType::EXACT_ONLY;
constexpr TermMatchType::Code MATCH_PREFIX = TermMatchType::PREFIX;

constexpr PropertyConfigProto::DataType::Code TYPE_STRING =
    PropertyConfigProto::DataType::STRING;
constexpr PropertyConfigProto::DataType::Code TYPE_DOUBLE =
    PropertyConfigProto::DataType::DOUBLE;

class SchemaStoreTest : public ::testing::Test {
 protected:
  void SetUp() override {
    temp_dir_ = GetTestTempDir() + "/icing";
    schema_store_dir_ = temp_dir_ + "/schema_store";
    filesystem_.CreateDirectoryRecursively(schema_store_dir_.c_str());

    schema_ =
        SchemaBuilder()
            .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
                // Add an indexed property so we generate section metadata on it
                PropertyConfigBuilder()
                    .SetName("subject")
                    .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                    .SetCardinality(CARDINALITY_OPTIONAL)))
            .Build();
  }

  void TearDown() override {
    // Check that the schema store directory is the *only* directory in the
    // schema_store_dir_. IOW, ensure that all temporary directories have been
    // properly cleaned up.
    std::vector<std::string> sub_dirs;
    ASSERT_TRUE(filesystem_.ListDirectory(temp_dir_.c_str(), &sub_dirs));
    ASSERT_THAT(sub_dirs, ElementsAre("schema_store"));

    // Finally, clean everything up.
    ASSERT_TRUE(filesystem_.DeleteDirectoryRecursively(temp_dir_.c_str()));
  }

  Filesystem filesystem_;
  std::string temp_dir_;
  std::string schema_store_dir_;
  SchemaProto schema_;
  FakeClock fake_clock_;
};

TEST_F(SchemaStoreTest, CreationWithNullPointerShouldFail) {
  EXPECT_THAT(
      SchemaStore::Create(/*filesystem=*/nullptr, schema_store_dir_, &fake_clock_),
      StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));
}

TEST_F(SchemaStoreTest, SchemaStoreMoveConstructible) {
  // Create an instance of SchemaStore.
  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("TypeA").AddProperty(
              PropertyConfigBuilder()
                  .SetName("prop1")
                  .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                  .SetCardinality(CARDINALITY_OPTIONAL)))
          .Build();

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  ICING_ASSERT_OK(schema_store->SetSchema(schema));
  ICING_ASSERT_OK_AND_ASSIGN(Crc32 expected_checksum,
                             schema_store->ComputeChecksum());

  // Move construct an instance of SchemaStore
  SchemaStore move_constructed_schema_store(std::move(*schema_store));
  EXPECT_THAT(move_constructed_schema_store.GetSchema(),
              IsOkAndHolds(Pointee(EqualsProto(schema))));
  EXPECT_THAT(move_constructed_schema_store.ComputeChecksum(),
              IsOkAndHolds(Eq(expected_checksum)));
  SectionMetadata expected_metadata(/*id_in=*/0, MATCH_EXACT, TOKENIZER_PLAIN,
                                    "prop1");
  EXPECT_THAT(move_constructed_schema_store.GetSectionMetadata("TypeA"),
              IsOkAndHolds(Pointee(ElementsAre(expected_metadata))));
}

TEST_F(SchemaStoreTest, SchemaStoreMoveAssignment) {
  // Create an instance of SchemaStore.
  SchemaProto schema1 =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("TypeA").AddProperty(
              PropertyConfigBuilder()
                  .SetName("prop1")
                  .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                  .SetCardinality(CARDINALITY_OPTIONAL)))
          .Build();

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  ICING_ASSERT_OK(schema_store->SetSchema(schema1));
  ICING_ASSERT_OK_AND_ASSIGN(Crc32 expected_checksum,
                             schema_store->ComputeChecksum());

  // Construct another instance of SchemaStore
  SchemaProto schema2 =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("TypeB").AddProperty(
              PropertyConfigBuilder()
                  .SetName("prop2")
                  .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                  .SetCardinality(CARDINALITY_OPTIONAL)))
          .Build();

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> move_assigned_schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));
  ICING_ASSERT_OK(schema_store->SetSchema(schema2));

  // Move assign the first instance into the second one.
  *move_assigned_schema_store = std::move(*schema_store);
  EXPECT_THAT(move_assigned_schema_store->GetSchema(),
              IsOkAndHolds(Pointee(EqualsProto(schema1))));
  EXPECT_THAT(move_assigned_schema_store->ComputeChecksum(),
              IsOkAndHolds(Eq(expected_checksum)));
  SectionMetadata expected_metadata(/*id_in=*/0, MATCH_EXACT, TOKENIZER_PLAIN,
                                    "prop1");
  EXPECT_THAT(move_assigned_schema_store->GetSectionMetadata("TypeA"),
              IsOkAndHolds(Pointee(ElementsAre(expected_metadata))));
}

TEST_F(SchemaStoreTest, CorruptSchemaError) {
  {
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

    // Set it for the first time
    SchemaStore::SetSchemaResult result;
    result.success = true;
    result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
    EXPECT_THAT(schema_store->SetSchema(schema_),
                IsOkAndHolds(EqualsSetSchemaResult(result)));
    ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                               schema_store->GetSchema());
    EXPECT_THAT(*actual_schema, EqualsProto(schema_));
  }

  // "Corrupt" the  ground truth schema by adding new data to it. This will mess
  // up the checksum of the schema store

  SchemaProto corrupt_schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("corrupted"))
          .Build();

  const std::string schema_file = absl_ports::StrCat(schema_store_dir_, "/schema.pb");
  const std::string serialized_schema = corrupt_schema.SerializeAsString();

  filesystem_.Write(schema_file.c_str(), serialized_schema.data(),
                    serialized_schema.size());

  // If ground truth was corrupted, we won't know what to do
  EXPECT_THAT(SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_),
              StatusIs(libtextclassifier3::StatusCode::INTERNAL));
}

TEST_F(SchemaStoreTest, RecoverCorruptDerivedFileOk) {
  {
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

    // Set it for the first time
    SchemaStore::SetSchemaResult result;
    result.success = true;
    result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
    EXPECT_THAT(schema_store->SetSchema(schema_),
                IsOkAndHolds(EqualsSetSchemaResult(result)));
    ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                               schema_store->GetSchema());
    EXPECT_THAT(*actual_schema, EqualsProto(schema_));

    EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));
  }

  // "Corrupt" the derived SchemaTypeIds by deleting the entire directory. This
  // will mess up the initialization of schema store, causing everything to be
  // regenerated from ground truth

  const std::string schema_type_mapper_dir =
      absl_ports::StrCat(schema_store_dir_, "/schema_type_mapper");
  filesystem_.DeleteDirectoryRecursively(schema_type_mapper_dir.c_str());

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Everything looks fine, ground truth and derived data
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));
  EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));
}

TEST_F(SchemaStoreTest, RecoverBadChecksumOk) {
  {
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

    // Set it for the first time
    SchemaStore::SetSchemaResult result;
    result.success = true;
    result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
    EXPECT_THAT(schema_store->SetSchema(schema_),
                IsOkAndHolds(EqualsSetSchemaResult(result)));
    ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                               schema_store->GetSchema());
    EXPECT_THAT(*actual_schema, EqualsProto(schema_));

    EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));
  }

  // Change the SchemaStore's header combined checksum so that it won't match
  // the recalculated checksum on initialization. This will force a regeneration
  // of derived files from ground truth.
  const std::string header_file =
      absl_ports::StrCat(schema_store_dir_, "/schema_store_header");
  SchemaStore::Header header;
  header.magic = SchemaStore::Header::kMagic;
  header.checksum = 10;  // Arbitrary garbage checksum
  filesystem_.DeleteFile(header_file.c_str());
  filesystem_.Write(header_file.c_str(), &header, sizeof(header));

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Everything looks fine, ground truth and derived data
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));
  EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));
}

TEST_F(SchemaStoreTest, CreateNoPreviousSchemaOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // The apis to retrieve information about the schema should fail gracefully.
  EXPECT_THAT(store->GetSchema(),
              StatusIs(libtextclassifier3::StatusCode::NOT_FOUND));
  EXPECT_THAT(store->GetSchemaTypeConfig("foo"),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));
  EXPECT_THAT(store->GetSchemaTypeId("foo"),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));
  EXPECT_THAT(store->GetSectionMetadata(/*schema_type_id=*/0, /*section_id=*/0),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));

  // The apis to extract content from a document should fail gracefully.
  DocumentProto doc;
  PropertyProto* prop = doc.add_properties();
  prop->set_name("name");
  prop->add_string_values("foo bar baz");

  EXPECT_THAT(store->GetStringSectionContent(doc, /*section_id=*/0),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));
  EXPECT_THAT(store->GetStringSectionContent(doc, "name"),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));
  EXPECT_THAT(store->ExtractSections(doc),
              StatusIs(libtextclassifier3::StatusCode::FAILED_PRECONDITION));

  // The apis to persist and checksum data should succeed.
  EXPECT_THAT(store->ComputeChecksum(), IsOkAndHolds(Crc32()));
  EXPECT_THAT(store->PersistToDisk(), IsOk());
}

TEST_F(SchemaStoreTest, CreateWithPreviousSchemaOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));

  schema_store.reset();
  EXPECT_THAT(SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_),
              IsOk());
}

TEST_F(SchemaStoreTest, MultipleCreateOk) {
  DocumentProto document;
  document.set_schema("email");
  auto properties = document.add_properties();
  properties->set_name("subject");
  properties->add_string_values("subject_content");

  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));

  // Verify that our in-memory structures are ok
  EXPECT_THAT(schema_store->GetSchemaTypeConfig("email"),
              IsOkAndHolds(Pointee(EqualsProto(schema_.types(0)))));
  ICING_ASSERT_OK_AND_ASSIGN(std::vector<Section> sections,
                             schema_store->ExtractSections(document));
  EXPECT_THAT(sections[0].content, ElementsAre("subject_content"));

  // Verify that our persisted data is ok
  EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));

  schema_store.reset();
  ICING_ASSERT_OK_AND_ASSIGN(
      schema_store, SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Verify that our in-memory structures are ok
  EXPECT_THAT(schema_store->GetSchemaTypeConfig("email"),
              IsOkAndHolds(Pointee(EqualsProto(schema_.types(0)))));

  ICING_ASSERT_OK_AND_ASSIGN(sections, schema_store->ExtractSections(document));
  EXPECT_THAT(sections[0].content, ElementsAre("subject_content"));

  // Verify that our persisted data is ok
  EXPECT_THAT(schema_store->GetSchemaTypeId("email"), IsOkAndHolds(0));
}

TEST_F(SchemaStoreTest, SetNewSchemaOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));
}

TEST_F(SchemaStoreTest, SetSameSchemaOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));

  // And one more for fun
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));
}

TEST_F(SchemaStoreTest, SetIncompatibleSchemaOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(schema_.types(0).schema_type());
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema_));

  // Make the schema incompatible by removing a type.
  schema_.clear_types();

  // Set the incompatible schema
  result = SchemaStore::SetSchemaResult();
  result.success = false;
  result.schema_types_deleted_by_name.emplace("email");
  result.schema_types_deleted_by_id.emplace(0);
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
}

TEST_F(SchemaStoreTest, SetSchemaWithAddedTypeOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema = SchemaBuilder()
                           .AddType(SchemaTypeConfigBuilder().SetType("email"))
                           .Build();

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  // Add a type, shouldn't affect the index or cached SchemaTypeIds
  schema = SchemaBuilder(schema)
               .AddType(SchemaTypeConfigBuilder().SetType("new_type"))
               .Build();

  // Set the compatible schema
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  result.schema_types_new_by_name.insert("new_type");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithDeletedTypeOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("email"))
          .AddType(SchemaTypeConfigBuilder().SetType("message"))
          .Build();

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  result.schema_types_new_by_name.insert("message");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  ICING_ASSERT_OK_AND_ASSIGN(SchemaTypeId old_email_schema_type_id,
                             schema_store->GetSchemaTypeId("email"));
  ICING_ASSERT_OK_AND_ASSIGN(SchemaTypeId old_message_schema_type_id,
                             schema_store->GetSchemaTypeId("message"));

  // Remove "email" type, this also changes previous SchemaTypeIds
  schema = SchemaBuilder()
               .AddType(SchemaTypeConfigBuilder().SetType("message"))
               .Build();

  SchemaStore::SetSchemaResult incompatible_result;
  incompatible_result.success = false;
  incompatible_result.old_schema_type_ids_changed.emplace(
      old_message_schema_type_id);
  incompatible_result.schema_types_deleted_by_name.emplace("email");
  incompatible_result.schema_types_deleted_by_id.emplace(
      old_email_schema_type_id);

  // Can't set the incompatible schema
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(incompatible_result)));

  SchemaStore::SetSchemaResult force_result;
  force_result.success = true;
  force_result.old_schema_type_ids_changed.emplace(old_message_schema_type_id);
  force_result.schema_types_deleted_by_name.emplace("email");
  force_result.schema_types_deleted_by_id.emplace(old_email_schema_type_id);

  // Force set the incompatible schema
  EXPECT_THAT(schema_store->SetSchema(
                  schema, /*ignore_errors_and_delete_documents=*/true),
              IsOkAndHolds(EqualsSetSchemaResult(force_result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithReorderedTypesOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("email"))
          .AddType(SchemaTypeConfigBuilder().SetType("message"))
          .Build();

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  result.schema_types_new_by_name.insert("message");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  // Reorder the types
  schema = SchemaBuilder()
               .AddType(SchemaTypeConfigBuilder().SetType("message"))
               .AddType(SchemaTypeConfigBuilder().SetType("email"))
               .Build();

  // Since we assign SchemaTypeIds based on order in the SchemaProto, this will
  // cause SchemaTypeIds to change
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  result.old_schema_type_ids_changed.emplace(0);  // Old SchemaTypeId of "email"
  result.old_schema_type_ids_changed.emplace(
      1);  // Old SchemaTypeId of "message"

  // Set the compatible schema
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, IndexedPropertyChangeRequiresReindexingOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
              // Add an unindexed property
              PropertyConfigBuilder()
                  .SetName("subject")
                  .SetDataType(TYPE_STRING)
                  .SetCardinality(CARDINALITY_OPTIONAL)))
          .Build();

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  // Make a previously unindexed property indexed
  schema = SchemaBuilder()
               .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
                   PropertyConfigBuilder()
                       .SetName("subject")
                       .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                       .SetCardinality(CARDINALITY_OPTIONAL)))
               .Build();

  // Set the compatible schema
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  result.schema_types_index_incompatible_by_name.insert("email");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, IndexNestedDocumentsChangeRequiresReindexingOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Make two schemas. One that sets index_nested_properties to false and one
  // that sets it to true.
  SchemaTypeConfigProto email_type_config =
      SchemaTypeConfigBuilder()
          .SetType("email")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("subject")
                           .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_OPTIONAL))
          .Build();
  SchemaProto no_nested_index_schema =
      SchemaBuilder()
          .AddType(email_type_config)
          .AddType(SchemaTypeConfigBuilder().SetType("person").AddProperty(
              PropertyConfigBuilder()
                  .SetName("emails")
                  .SetDataTypeDocument("email",
                                       /*index_nested_properties=*/false)
                  .SetCardinality(CARDINALITY_REPEATED)))
          .Build();

  SchemaProto nested_index_schema =
      SchemaBuilder()
          .AddType(email_type_config)
          .AddType(SchemaTypeConfigBuilder().SetType("person").AddProperty(
              PropertyConfigBuilder()
                  .SetName("emails")
                  .SetDataTypeDocument("email",
                                       /*index_nested_properties=*/true)
                  .SetCardinality(CARDINALITY_REPEATED)))
          .Build();

  // Set schema with index_nested_properties=false to start.
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  result.schema_types_new_by_name.insert("person");
  EXPECT_THAT(schema_store->SetSchema(no_nested_index_schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(no_nested_index_schema));

  // Set schema with index_nested_properties=true and confirm that the change to
  // 'person' is index incompatible.
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  result.schema_types_index_incompatible_by_name.insert("person");
  EXPECT_THAT(schema_store->SetSchema(nested_index_schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(nested_index_schema));

  // Set schema with index_nested_properties=false and confirm that the change
  // to 'person' is index incompatible.
  result = SchemaStore::SetSchemaResult();
  result.success = true;
  result.schema_types_index_incompatible_by_name.insert("person");
  EXPECT_THAT(schema_store->SetSchema(no_nested_index_schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(no_nested_index_schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithIncompatibleTypesOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
              // Add a STRING property
              PropertyConfigBuilder()
                  .SetName("subject")
                  .SetDataType(TYPE_STRING)
                  .SetCardinality(CARDINALITY_OPTIONAL)))
          .Build();

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  ICING_ASSERT_OK_AND_ASSIGN(SchemaTypeId old_email_schema_type_id,
                             schema_store->GetSchemaTypeId("email"));

  // Make a previously STRING property into DOUBLE
  schema = SchemaBuilder()
               .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
                   // Add a STRING property
                   PropertyConfigBuilder()
                       .SetName("subject")
                       .SetDataType(TYPE_DOUBLE)
                       .SetCardinality(CARDINALITY_OPTIONAL)))
               .Build();

  SchemaStore::SetSchemaResult incompatible_result;
  incompatible_result.success = false;
  incompatible_result.schema_types_incompatible_by_name.emplace("email");
  incompatible_result.schema_types_incompatible_by_id.emplace(
      old_email_schema_type_id);

  // Can't set the incompatible schema
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(incompatible_result)));

  SchemaStore::SetSchemaResult force_result;
  force_result.success = true;
  force_result.schema_types_incompatible_by_name.emplace("email");
  force_result.schema_types_incompatible_by_id.emplace(
      old_email_schema_type_id);

  // Force set the incompatible schema
  EXPECT_THAT(schema_store->SetSchema(
                  schema, /*ignore_errors_and_delete_documents=*/true),
              IsOkAndHolds(EqualsSetSchemaResult(force_result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithIncompatibleNestedTypesOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // 1. Create a ContactPoint type with a repeated property and set that schema
  SchemaTypeConfigBuilder contact_point_repeated_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_PREFIX, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_REPEATED));
  SchemaProto old_schema =
      SchemaBuilder().AddType(contact_point_repeated_label).Build();
  ICING_EXPECT_OK(schema_store->SetSchema(old_schema));
  ICING_ASSERT_OK_AND_ASSIGN(SchemaTypeId old_contact_point_type_id,
                             schema_store->GetSchemaTypeId("ContactPoint"));

  // 2. Create a type that references the ContactPoint type and make a backwards
  // incompatible change to ContactPoint
  SchemaTypeConfigBuilder contact_point_optional_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_PREFIX, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_OPTIONAL));
  SchemaTypeConfigBuilder person =
      SchemaTypeConfigBuilder().SetType("Person").AddProperty(
          PropertyConfigBuilder()
              .SetName("contactPoints")
              .SetDataTypeDocument("ContactPoint",
                                   /*index_nested_properties=*/true)
              .SetCardinality(CARDINALITY_REPEATED));
  SchemaProto new_schema = SchemaBuilder()
                               .AddType(contact_point_optional_label)
                               .AddType(person)
                               .Build();

  // 3. SetSchema should fail with ignore_errors_and_delete_documents=false and
  // the old schema should remain
  SchemaStore::SetSchemaResult expected_result;
  expected_result.success = false;
  expected_result.schema_types_incompatible_by_name.insert("ContactPoint");
  expected_result.schema_types_incompatible_by_id.insert(
      old_contact_point_type_id);
  expected_result.schema_types_new_by_name.insert("Person");
  EXPECT_THAT(
      schema_store->SetSchema(new_schema,
                              /*ignore_errors_and_delete_documents=*/false),
      IsOkAndHolds(EqualsSetSchemaResult(expected_result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(old_schema));

  // 4. SetSchema should succeed with ignore_errors_and_delete_documents=true
  // and the new schema should be set
  expected_result.success = true;
  EXPECT_THAT(
      schema_store->SetSchema(new_schema,
                              /*ignore_errors_and_delete_documents=*/true),
      IsOkAndHolds(EqualsSetSchemaResult(expected_result)));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(new_schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithIndexIncompatibleNestedTypesOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // 1. Create a ContactPoint type with label that matches prefix and set that
  // schema
  SchemaTypeConfigBuilder contact_point_prefix_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_PREFIX, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_REPEATED));
  SchemaProto old_schema =
      SchemaBuilder().AddType(contact_point_prefix_label).Build();
  ICING_EXPECT_OK(schema_store->SetSchema(old_schema));

  // 2. Create a type that references the ContactPoint type and make a index
  // backwards incompatible change to ContactPoint
  SchemaTypeConfigBuilder contact_point_exact_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_REPEATED));
  SchemaTypeConfigBuilder person =
      SchemaTypeConfigBuilder().SetType("Person").AddProperty(
          PropertyConfigBuilder()
              .SetName("contactPoints")
              .SetDataTypeDocument("ContactPoint",
                                   /*index_nested_properties=*/true)
              .SetCardinality(CARDINALITY_REPEATED));
  SchemaProto new_schema = SchemaBuilder()
                               .AddType(contact_point_exact_label)
                               .AddType(person)
                               .Build();

  // SetSchema should succeed, and only ContactPoint should be in
  // schema_types_index_incompatible_by_name.
  SchemaStore::SetSchemaResult expected_result;
  expected_result.success = true;
  expected_result.schema_types_index_incompatible_by_name.insert(
      "ContactPoint");
  expected_result.schema_types_new_by_name.insert("Person");
  EXPECT_THAT(
      schema_store->SetSchema(new_schema,
                              /*ignore_errors_and_delete_documents=*/false),
      IsOkAndHolds(EqualsSetSchemaResult(expected_result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(new_schema));
}

TEST_F(SchemaStoreTest, SetSchemaWithCompatibleNestedTypesOk) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // 1. Create a ContactPoint type with a optional property and set that schema
  SchemaTypeConfigBuilder contact_point_optional_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_PREFIX, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_OPTIONAL));
  SchemaProto old_schema =
      SchemaBuilder().AddType(contact_point_optional_label).Build();
  ICING_EXPECT_OK(schema_store->SetSchema(old_schema));

  // 2. Create a type that references the ContactPoint type and make a backwards
  // compatible change to ContactPoint
  SchemaTypeConfigBuilder contact_point_repeated_label =
      SchemaTypeConfigBuilder()
          .SetType("ContactPoint")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("label")
                           .SetDataTypeString(MATCH_PREFIX, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_REPEATED));
  SchemaTypeConfigBuilder person =
      SchemaTypeConfigBuilder().SetType("Person").AddProperty(
          PropertyConfigBuilder()
              .SetName("contactPoints")
              .SetDataTypeDocument("ContactPoint",
                                   /*index_nested_properties=*/true)
              .SetCardinality(CARDINALITY_REPEATED));
  SchemaProto new_schema = SchemaBuilder()
                               .AddType(contact_point_repeated_label)
                               .AddType(person)
                               .Build();

  // 3. SetSchema should succeed, and only ContactPoint should be in
  // schema_types_changed_fully_compatible_by_name.
  SchemaStore::SetSchemaResult expected_result;
  expected_result.success = true;
  expected_result.schema_types_changed_fully_compatible_by_name.insert(
      "ContactPoint");
  expected_result.schema_types_new_by_name.insert("Person");
  EXPECT_THAT(schema_store->SetSchema(
                  new_schema, /*ignore_errors_and_delete_documents=*/false),
              IsOkAndHolds(EqualsSetSchemaResult(expected_result)));
  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(new_schema));
}

TEST_F(SchemaStoreTest, GetSchemaTypeId) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  schema_.clear_types();

  // Add a few schema types
  const std::string first_type = "first";
  auto type = schema_.add_types();
  type->set_schema_type(first_type);

  const std::string second_type = "second";
  type = schema_.add_types();
  type->set_schema_type(second_type);

  // Set it for the first time
  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert(first_type);
  result.schema_types_new_by_name.insert(second_type);
  EXPECT_THAT(schema_store->SetSchema(schema_),
              IsOkAndHolds(EqualsSetSchemaResult(result)));

  EXPECT_THAT(schema_store->GetSchemaTypeId(first_type), IsOkAndHolds(0));
  EXPECT_THAT(schema_store->GetSchemaTypeId(second_type), IsOkAndHolds(1));
}

TEST_F(SchemaStoreTest, ComputeChecksumDefaultOnEmptySchemaStore) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  Crc32 default_checksum;
  EXPECT_THAT(schema_store->ComputeChecksum(), IsOkAndHolds(default_checksum));
}

TEST_F(SchemaStoreTest, ComputeChecksumSameBetweenCalls) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto foo_schema =
      SchemaBuilder().AddType(SchemaTypeConfigBuilder().SetType("foo")).Build();

  ICING_EXPECT_OK(schema_store->SetSchema(foo_schema));

  ICING_ASSERT_OK_AND_ASSIGN(Crc32 checksum, schema_store->ComputeChecksum());

  // Calling it again doesn't change the checksum
  EXPECT_THAT(schema_store->ComputeChecksum(), IsOkAndHolds(checksum));
}

TEST_F(SchemaStoreTest, ComputeChecksumSameAcrossInstances) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto foo_schema =
      SchemaBuilder().AddType(SchemaTypeConfigBuilder().SetType("foo")).Build();

  ICING_EXPECT_OK(schema_store->SetSchema(foo_schema));

  ICING_ASSERT_OK_AND_ASSIGN(Crc32 checksum, schema_store->ComputeChecksum());

  // Destroy the previous instance and recreate SchemaStore
  schema_store.reset();

  ICING_ASSERT_OK_AND_ASSIGN(
      schema_store, SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));
  EXPECT_THAT(schema_store->ComputeChecksum(), IsOkAndHolds(checksum));
}

TEST_F(SchemaStoreTest, ComputeChecksumChangesOnModification) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto foo_schema =
      SchemaBuilder().AddType(SchemaTypeConfigBuilder().SetType("foo")).Build();

  ICING_EXPECT_OK(schema_store->SetSchema(foo_schema));

  ICING_ASSERT_OK_AND_ASSIGN(Crc32 checksum, schema_store->ComputeChecksum());

  // Modifying the SchemaStore changes the checksum
  SchemaProto foo_bar_schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("foo"))
          .AddType(SchemaTypeConfigBuilder().SetType("bar"))
          .Build();

  ICING_EXPECT_OK(schema_store->SetSchema(foo_bar_schema));

  EXPECT_THAT(schema_store->ComputeChecksum(), IsOkAndHolds(Not(Eq(checksum))));
}

TEST_F(SchemaStoreTest, PersistToDiskFineForEmptySchemaStore) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Persisting is fine and shouldn't affect anything
  ICING_EXPECT_OK(schema_store->PersistToDisk());
}

TEST_F(SchemaStoreTest, PersistToDiskPreservesAcrossInstances) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  SchemaProto schema =
      SchemaBuilder().AddType(SchemaTypeConfigBuilder().SetType("foo")).Build();

  ICING_EXPECT_OK(schema_store->SetSchema(schema));

  // Persisting shouldn't change anything
  ICING_EXPECT_OK(schema_store->PersistToDisk());

  ICING_ASSERT_OK_AND_ASSIGN(const SchemaProto* actual_schema,
                             schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));

  // Modify the schema so that something different is persisted next time
  schema = SchemaBuilder(schema)
               .AddType(SchemaTypeConfigBuilder().SetType("bar"))
               .Build();
  ICING_EXPECT_OK(schema_store->SetSchema(schema));

  // Should also persist on destruction
  schema_store.reset();

  // And we get the same schema back on reinitialization
  ICING_ASSERT_OK_AND_ASSIGN(
      schema_store, SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));
  ICING_ASSERT_OK_AND_ASSIGN(actual_schema, schema_store->GetSchema());
  EXPECT_THAT(*actual_schema, EqualsProto(schema));
}

TEST_F(SchemaStoreTest, SchemaStoreStorageInfoProto) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Create a schema with two types: one simple type and one type that uses all
  // 16 sections.
  PropertyConfigProto prop =
      PropertyConfigBuilder()
          .SetName("subject")
          .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
          .SetCardinality(CARDINALITY_OPTIONAL)
          .Build();
  SchemaProto schema =
      SchemaBuilder()
          .AddType(SchemaTypeConfigBuilder().SetType("email").AddProperty(
              PropertyConfigBuilder(prop)))
          .AddType(
              SchemaTypeConfigBuilder()
                  .SetType("fullSectionsType")
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop0"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop1"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop2"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop3"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop4"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop5"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop6"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop7"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop8"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop9"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop10"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop11"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop12"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop13"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop14"))
                  .AddProperty(PropertyConfigBuilder(prop).SetName("prop15")))
          .Build();

  SchemaStore::SetSchemaResult result;
  result.success = true;
  result.schema_types_new_by_name.insert("email");
  result.schema_types_new_by_name.insert("fullSectionsType");
  EXPECT_THAT(schema_store->SetSchema(schema),
              IsOkAndHolds(EqualsSetSchemaResult(result)));

  SchemaStoreStorageInfoProto storage_info = schema_store->GetStorageInfo();
  EXPECT_THAT(storage_info.schema_store_size(), Ge(0));
  EXPECT_THAT(storage_info.num_schema_types(), Eq(2));
  EXPECT_THAT(storage_info.num_total_sections(), Eq(17));
  EXPECT_THAT(storage_info.num_schema_types_sections_exhausted(), Eq(1));
}

TEST_F(SchemaStoreTest, GetDebugInfo) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Set schema
  ASSERT_THAT(
      schema_store->SetSchema(schema_),
      IsOkAndHolds(EqualsSetSchemaResult(SchemaStore::SetSchemaResult{
          .success = true,
          .schema_types_new_by_name = {schema_.types(0).schema_type()}})));

  // Check debug info
  ICING_ASSERT_OK_AND_ASSIGN(SchemaDebugInfoProto out,
                             schema_store->GetDebugInfo());
  EXPECT_THAT(out.schema(), EqualsProto(schema_));
  EXPECT_THAT(out.crc(), Gt(0));
}

TEST_F(SchemaStoreTest, GetDebugInfoForEmptySchemaStore) {
  ICING_ASSERT_OK_AND_ASSIGN(
      std::unique_ptr<SchemaStore> schema_store,
      SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));

  // Check debug info before setting a schema
  ICING_ASSERT_OK_AND_ASSIGN(SchemaDebugInfoProto out,
                             schema_store->GetDebugInfo());
  SchemaDebugInfoProto expected_out;
  expected_out.set_crc(0);
  EXPECT_THAT(out, EqualsProto(expected_out));
}

TEST_F(SchemaStoreTest, InitializeRegenerateDerivedFilesFailure) {
  // This test covers the first point that RegenerateDerivedFiles could fail.
  // This should simply result in SetSchema::Create returning an INTERNAL error.

  {
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));
    SchemaProto schema = SchemaBuilder()
                             .AddType(SchemaTypeConfigBuilder().SetType("Type"))
                             .Build();
    ICING_ASSERT_OK(schema_store->SetSchema(std::move(schema)));
  }

  auto mock_filesystem = std::make_unique<MockFilesystem>();
  ON_CALL(*mock_filesystem,
          CreateDirectoryRecursively(HasSubstr("key_mapper_dir")))
      .WillByDefault(Return(false));
  {
    EXPECT_THAT(SchemaStore::Create(mock_filesystem.get(), schema_store_dir_,
                                    &fake_clock_),
                StatusIs(libtextclassifier3::StatusCode::INTERNAL));
  }
}

TEST_F(SchemaStoreTest, SetSchemaRegenerateDerivedFilesFailure) {
  // This test covers the second point that RegenerateDerivedFiles could fail.
  // If handled correctly, the schema store and section manager should still be
  // in the original, valid state.
  SchemaTypeConfigProto type =
      SchemaTypeConfigBuilder()
          .SetType("Type")
          .AddProperty(PropertyConfigBuilder()
                           .SetName("prop1")
                           .SetDataTypeString(MATCH_EXACT, TOKENIZER_PLAIN)
                           .SetCardinality(CARDINALITY_OPTIONAL))
          .Build();
  {
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(&filesystem_, schema_store_dir_, &fake_clock_));
    SchemaProto schema = SchemaBuilder().AddType(type).Build();
    ICING_ASSERT_OK(schema_store->SetSchema(std::move(schema)));
  }

  {
    auto mock_filesystem = std::make_unique<MockFilesystem>();
    ICING_ASSERT_OK_AND_ASSIGN(
        std::unique_ptr<SchemaStore> schema_store,
        SchemaStore::Create(mock_filesystem.get(), schema_store_dir_,
                            &fake_clock_));

    ON_CALL(*mock_filesystem,
            CreateDirectoryRecursively(HasSubstr("key_mapper_dir")))
        .WillByDefault(Return(false));
    SchemaProto schema =
        SchemaBuilder()
            .AddType(type)
            .AddType(SchemaTypeConfigBuilder().SetType("Type2"))
            .Build();
    EXPECT_THAT(schema_store->SetSchema(std::move(schema)),
                StatusIs(libtextclassifier3::StatusCode::INTERNAL));
    DocumentProto document = DocumentBuilder()
                                 .SetSchema("Type")
                                 .AddStringProperty("prop1", "foo bar baz")
                                 .Build();
    SectionMetadata expected_metadata(/*id_in=*/0, MATCH_EXACT, TOKENIZER_PLAIN,
                                      "prop1");
    ICING_ASSERT_OK_AND_ASSIGN(std::vector<Section> sections,
                               schema_store->ExtractSections(document));
    ASSERT_THAT(sections, SizeIs(1));
    EXPECT_THAT(sections.at(0).metadata, Eq(expected_metadata));
    EXPECT_THAT(sections.at(0).content, ElementsAre("foo bar baz"));
  }
}

}  // namespace

}  // namespace lib
}  // namespace icing
