/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <elf.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include <android-base/file.h>
#include <gtest/gtest.h>

#include <unwindstack/Elf.h>
#include <unwindstack/MapInfo.h>
#include <unwindstack/Maps.h>
#include <unwindstack/Memory.h>

#include "ElfTestUtils.h"
#include "utils/MemoryFake.h"

namespace unwindstack {

class MapInfoGetElfTest : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_ = new MemoryFake;
    process_memory_.reset(memory_);
  }

  template <typename Ehdr, typename Shdr>
  static void InitElf(uint64_t sh_offset, Ehdr* ehdr, uint8_t class_type, uint8_t machine_type) {
    memset(ehdr, 0, sizeof(*ehdr));
    memcpy(ehdr->e_ident, ELFMAG, SELFMAG);
    ehdr->e_ident[EI_CLASS] = class_type;
    ehdr->e_machine = machine_type;
    ehdr->e_shoff = sh_offset;
    ehdr->e_shentsize = sizeof(Shdr) + 100;
    ehdr->e_shnum = 4;
  }

  void InitMapInfo(std::vector<std::shared_ptr<MapInfo>>& maps, bool in_memory);

  const size_t kMapSize = 4096;

  std::shared_ptr<Memory> process_memory_;
  MemoryFake* memory_;

  TemporaryFile elf_;
};

TEST_F(MapInfoGetElfTest, invalid) {
  auto info = MapInfo::Create(0x1000, 0x2000, 0, PROT_READ, "");

  // The map is empty, but this should still create an invalid elf object.
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());
}

TEST_F(MapInfoGetElfTest, valid32) {
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memory_->SetMemory(0x3000, &ehdr, sizeof(ehdr));

  auto info = MapInfo::Create(0x3000, 0x4000, 0, PROT_READ, "");
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  EXPECT_EQ(static_cast<uint32_t>(EM_ARM), elf->machine_type());
  EXPECT_EQ(ELFCLASS32, elf->class_type());

  // Now verify that an empty process memory returns an invalid elf object.
  info->set_elf(nullptr);
  elf = info->GetElf(std::shared_ptr<Memory>(), ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());
}

TEST_F(MapInfoGetElfTest, valid64) {
  Elf64_Ehdr ehdr;
  TestInitEhdr<Elf64_Ehdr>(&ehdr, ELFCLASS64, EM_AARCH64);
  memory_->SetMemory(0x8000, &ehdr, sizeof(ehdr));

  auto info = MapInfo::Create(0x8000, 0x9000, 0, PROT_READ, "");
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM64);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  EXPECT_EQ(static_cast<uint32_t>(EM_AARCH64), elf->machine_type());
  EXPECT_EQ(ELFCLASS64, elf->class_type());
}

TEST_F(MapInfoGetElfTest, invalid_arch_mismatch) {
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memory_->SetMemory(0x3000, &ehdr, sizeof(ehdr));

  auto info = MapInfo::Create(0x3000, 0x4000, 0, PROT_READ, "");
  Elf* elf = info->GetElf(process_memory_, ARCH_X86);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());
}

TEST_F(MapInfoGetElfTest, gnu_debugdata_init32) {
  TestInitGnuDebugdata<Elf32_Ehdr, Elf32_Shdr>(ELFCLASS32, EM_ARM, true,
                                               [&](uint64_t offset, const void* ptr, size_t size) {
                                                 memory_->SetMemory(0x2000 + offset, ptr, size);
                                               });

  auto info = MapInfo::Create(0x2000, 0x3000, 0, PROT_READ, "");
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  EXPECT_EQ(static_cast<uint32_t>(EM_ARM), elf->machine_type());
  EXPECT_EQ(ELFCLASS32, elf->class_type());
  EXPECT_TRUE(elf->gnu_debugdata_interface() != nullptr);
}

TEST_F(MapInfoGetElfTest, gnu_debugdata_init64) {
  TestInitGnuDebugdata<Elf64_Ehdr, Elf64_Shdr>(ELFCLASS64, EM_AARCH64, true,
                                               [&](uint64_t offset, const void* ptr, size_t size) {
                                                 memory_->SetMemory(0x5000 + offset, ptr, size);
                                               });

  auto info = MapInfo::Create(0x5000, 0x8000, 0, PROT_READ, "");
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM64);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  EXPECT_EQ(static_cast<uint32_t>(EM_AARCH64), elf->machine_type());
  EXPECT_EQ(ELFCLASS64, elf->class_type());
  EXPECT_TRUE(elf->gnu_debugdata_interface() != nullptr);
}

TEST_F(MapInfoGetElfTest, end_le_start) {
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, &ehdr, sizeof(ehdr)));

  auto info = MapInfo::Create(0x1000, 0x1000, 0, PROT_READ, elf_.path);
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());

  info->set_elf(nullptr);
  info->set_end(0xfff);
  elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());

  // Make sure this test is valid.
  info->set_elf(nullptr);
  info->set_end(0x2000);
  elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
}

// Verify that if the offset is non-zero but there is no elf at the offset,
// that the full file is used.
TEST_F(MapInfoGetElfTest, file_backed_non_zero_offset_full_file) {
  std::vector<uint8_t> buffer(0x1000);
  memset(buffer.data(), 0, buffer.size());
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memcpy(buffer.data(), &ehdr, sizeof(ehdr));
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, buffer.data(), buffer.size()));

  auto info = MapInfo::Create(0x1000, 0x2000, 0x100, PROT_READ, elf_.path);
  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  ASSERT_TRUE(elf->memory() != nullptr);
  ASSERT_EQ(0x100U, info->elf_offset());

  // Read the entire file.
  memset(buffer.data(), 0, buffer.size());
  ASSERT_TRUE(elf->memory()->ReadFully(0, buffer.data(), buffer.size()));
  ASSERT_EQ(0, memcmp(buffer.data(), &ehdr, sizeof(ehdr)));
  for (size_t i = sizeof(ehdr); i < buffer.size(); i++) {
    ASSERT_EQ(0, buffer[i]) << "Failed at byte " << i;
  }

  ASSERT_FALSE(elf->memory()->ReadFully(buffer.size(), buffer.data(), 1));
}

// Verify that if the offset is non-zero and there is an elf at that
// offset, that only part of the file is used.
TEST_F(MapInfoGetElfTest, file_backed_non_zero_offset_partial_file) {
  auto info = MapInfo::Create(0x1000, 0x2000, 0x2000, PROT_READ, elf_.path);

  std::vector<uint8_t> buffer(0x4000);
  memset(buffer.data(), 0, buffer.size());
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memcpy(&buffer[info->offset()], &ehdr, sizeof(ehdr));
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, buffer.data(), buffer.size()));

  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  ASSERT_TRUE(elf->memory() != nullptr);
  ASSERT_EQ(0U, info->elf_offset());

  // Read the valid part of the file.
  ASSERT_TRUE(elf->memory()->ReadFully(0, buffer.data(), 0x1000));
  ASSERT_EQ(0, memcmp(buffer.data(), &ehdr, sizeof(ehdr)));
  for (size_t i = sizeof(ehdr); i < 0x1000; i++) {
    ASSERT_EQ(0, buffer[i]) << "Failed at byte " << i;
  }

  ASSERT_FALSE(elf->memory()->ReadFully(0x1000, buffer.data(), 1));
}

// Verify that if the offset is non-zero and there is an elf at that
// offset, that only part of the file is used. Further verify that if the
// embedded elf is bigger than the initial map, the new object is larger
// than the original map size. Do this for a 32 bit elf and a 64 bit elf.
TEST_F(MapInfoGetElfTest, file_backed_non_zero_offset_partial_file_whole_elf32) {
  auto info = MapInfo::Create(0x5000, 0x6000, 0x1000, PROT_READ, elf_.path);

  std::vector<uint8_t> buffer(0x4000);
  memset(buffer.data(), 0, buffer.size());
  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  ehdr.e_shoff = 0x2000;
  ehdr.e_shentsize = sizeof(Elf32_Shdr) + 100;
  ehdr.e_shnum = 4;
  memcpy(&buffer[info->offset()], &ehdr, sizeof(ehdr));
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, buffer.data(), buffer.size()));

  Elf* elf = info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  ASSERT_TRUE(elf->memory() != nullptr);
  ASSERT_EQ(0U, info->elf_offset());

  // Verify the memory is a valid elf.
  memset(buffer.data(), 0, buffer.size());
  ASSERT_TRUE(elf->memory()->ReadFully(0, buffer.data(), 0x1000));
  ASSERT_EQ(0, memcmp(buffer.data(), &ehdr, sizeof(ehdr)));

  // Read past the end of what would normally be the size of the map.
  ASSERT_TRUE(elf->memory()->ReadFully(0x1000, buffer.data(), 1));
}

TEST_F(MapInfoGetElfTest, file_backed_non_zero_offset_partial_file_whole_elf64) {
  auto info = MapInfo::Create(0x7000, 0x8000, 0x1000, PROT_READ, elf_.path);

  std::vector<uint8_t> buffer(0x4000);
  memset(buffer.data(), 0, buffer.size());
  Elf64_Ehdr ehdr;
  TestInitEhdr<Elf64_Ehdr>(&ehdr, ELFCLASS64, EM_AARCH64);
  ehdr.e_shoff = 0x2000;
  ehdr.e_shentsize = sizeof(Elf64_Shdr) + 100;
  ehdr.e_shnum = 4;
  memcpy(&buffer[info->offset()], &ehdr, sizeof(ehdr));
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, buffer.data(), buffer.size()));

  Elf* elf = info->GetElf(process_memory_, ARCH_ARM64);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  ASSERT_TRUE(elf->memory() != nullptr);
  ASSERT_EQ(0U, info->elf_offset());

  // Verify the memory is a valid elf.
  memset(buffer.data(), 0, buffer.size());
  ASSERT_TRUE(elf->memory()->ReadFully(0, buffer.data(), 0x1000));
  ASSERT_EQ(0, memcmp(buffer.data(), &ehdr, sizeof(ehdr)));

  // Read past the end of what would normally be the size of the map.
  ASSERT_TRUE(elf->memory()->ReadFully(0x1000, buffer.data(), 1));
}

// Verify that if the offset is non-zero and there is an elf at that
// offset, that only part of the file is used. Further verify that if the
// the initial map is smaller than elf header size, we can still read the elf.
TEST_F(MapInfoGetElfTest, file_backed_non_zero_offset_partial_file_whole_elf64_small_map_range) {
  auto info = MapInfo::Create(0x7000, 0x7004, 0x1000, PROT_READ, elf_.path);

  std::vector<uint8_t> buffer(0x4000);
  memset(buffer.data(), 0, buffer.size());
  Elf64_Ehdr ehdr;
  TestInitEhdr<Elf64_Ehdr>(&ehdr, ELFCLASS64, EM_AARCH64);
  ehdr.e_shoff = 0x2000;
  ehdr.e_shentsize = sizeof(Elf64_Shdr) + 100;
  ehdr.e_shnum = 4;
  memcpy(&buffer[info->offset()], &ehdr, sizeof(ehdr));
  ASSERT_TRUE(android::base::WriteFully(elf_.fd, buffer.data(), buffer.size()));

  Elf* elf = info->GetElf(process_memory_, ARCH_ARM64);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());
  ASSERT_TRUE(elf->memory() != nullptr);
  ASSERT_EQ(0U, info->elf_offset());

  // Verify the memory is a valid elf.
  memset(buffer.data(), 0, buffer.size());
  ASSERT_TRUE(elf->memory()->ReadFully(0, buffer.data(), 0x1000));
  ASSERT_EQ(0, memcmp(buffer.data(), &ehdr, sizeof(ehdr)));

  // Read past the end of what would normally be the size of the map.
  ASSERT_TRUE(elf->memory()->ReadFully(0x1000, buffer.data(), 1));
}

TEST_F(MapInfoGetElfTest, check_device_maps) {
  // Create valid elf data in process memory for this to verify that only
  // the name is causing invalid elf data.
  Elf64_Ehdr ehdr;
  TestInitEhdr<Elf64_Ehdr>(&ehdr, ELFCLASS64, EM_X86_64);
  ehdr.e_shoff = 0x2000;
  ehdr.e_shentsize = sizeof(Elf64_Shdr) + 100;
  ehdr.e_shnum = 0;
  memory_->SetMemory(0x7000, &ehdr, sizeof(ehdr));

  auto info =
      MapInfo::Create(0x7000, 0x8000, 0x1000, PROT_READ | MAPS_FLAGS_DEVICE_MAP, "/dev/something");
  Elf* elf = info->GetElf(process_memory_, ARCH_X86_64);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_FALSE(elf->valid());

  // Set the name to nothing to verify that it still fails.
  info->set_elf(nullptr);
  info->set_name("");
  elf = info->GetElf(process_memory_, ARCH_X86_64);
  ASSERT_FALSE(elf->valid());

  // Change the flags and verify the elf is valid now.
  info->set_elf(nullptr);
  info->set_flags(PROT_READ);
  elf = info->GetElf(process_memory_, ARCH_X86_64);
  ASSERT_TRUE(elf->valid());
}

TEST_F(MapInfoGetElfTest, multiple_thread_get_elf) {
  static constexpr size_t kNumConcurrentThreads = 100;

  Elf64_Ehdr ehdr;
  TestInitEhdr<Elf64_Ehdr>(&ehdr, ELFCLASS64, EM_X86_64);
  ehdr.e_shoff = 0x2000;
  ehdr.e_shentsize = sizeof(Elf64_Shdr) + 100;
  ehdr.e_shnum = 0;
  memory_->SetMemory(0x7000, &ehdr, sizeof(ehdr));

  Elf* elf_in_threads[kNumConcurrentThreads];
  std::vector<std::thread*> threads;

  std::atomic_bool wait;
  wait = true;
  // Create all of the threads and have them do the GetElf at the same time
  // to make it likely that a race will occur.
  auto info = MapInfo::Create(0x7000, 0x8000, 0x1000, PROT_READ, "");
  for (size_t i = 0; i < kNumConcurrentThreads; i++) {
    std::thread* thread = new std::thread([i, this, &wait, &info, &elf_in_threads]() {
      while (wait)
        ;
      Elf* elf = info->GetElf(process_memory_, ARCH_X86_64);
      elf_in_threads[i] = elf;
    });
    threads.push_back(thread);
  }
  ASSERT_TRUE(info->elf() == nullptr);

  // Set them all going and wait for the threads to finish.
  wait = false;
  for (auto thread : threads) {
    thread->join();
    delete thread;
  }

  // Now verify that all of the elf files are exactly the same and valid.
  Elf* elf = info->elf().get();
  ASSERT_TRUE(elf != nullptr);
  EXPECT_TRUE(elf->valid());
  for (size_t i = 0; i < kNumConcurrentThreads; i++) {
    EXPECT_EQ(elf, elf_in_threads[i]) << "Thread " << i << " mismatched.";
  }
}

// Verify that previous maps don't automatically get the same elf object.
TEST_F(MapInfoGetElfTest, prev_map_elf_not_set) {
  auto info1 = MapInfo::Create(0x1000, 0x2000, 0, PROT_READ, "/not/present");
  auto info2 = MapInfo::Create(info1, 0x2000, 0x3000, 0, PROT_READ, elf_.path);

  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memory_->SetMemory(0x2000, &ehdr, sizeof(ehdr));
  Elf* elf = info2->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_NE(elf, info1->GetElf(process_memory_, ARCH_ARM));
}

void MapInfoGetElfTest::InitMapInfo(std::vector<std::shared_ptr<MapInfo>>& maps, bool in_memory) {
  maps.resize(2);
  maps[0] = MapInfo::Create(0x1000, 0x2000, 0, PROT_READ, elf_.path);
  maps[1] = MapInfo::Create(maps[0], 0x2000, 0x3000, 0x1000, PROT_READ | PROT_EXEC, elf_.path);

  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  if (in_memory) {
    memory_->SetMemory(0x1000, &ehdr, sizeof(ehdr));
  } else {
    ASSERT_TRUE(android::base::WriteFully(elf_.fd, &ehdr, sizeof(ehdr)));
  }
}

// Verify that a read-only map followed by a read-execute map will result
// in the same elf object in both maps.
TEST_F(MapInfoGetElfTest, read_only_followed_by_read_exec_share_elf_exec_first) {
  std::vector<std::shared_ptr<MapInfo>> maps;

  // First use in memory maps.
  InitMapInfo(maps, true);
  ASSERT_EQ(2U, maps.size());
  MapInfo* r_map_info = maps[0].get();
  MapInfo* rx_map_info = maps[1].get();

  // Get the elf from the read-exec map first.
  Elf* elf = rx_map_info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_EQ(elf, r_map_info->GetElf(process_memory_, ARCH_ARM));

  // Now use file maps.
  maps.clear();
  InitMapInfo(maps, false);
  ASSERT_EQ(2U, maps.size());
  r_map_info = maps[0].get();
  rx_map_info = maps[1].get();

  // Get the elf from the read-exec map first.
  elf = rx_map_info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_EQ(elf, r_map_info->GetElf(process_memory_, ARCH_ARM));
}

// Verify that a read-only map followed by a read-execute map will result
// in the same elf object in both maps.
TEST_F(MapInfoGetElfTest, read_only_followed_by_read_exec_share_elf_read_only_first) {
  std::vector<std::shared_ptr<MapInfo>> maps;

  // First use in memory maps.
  InitMapInfo(maps, true);
  ASSERT_EQ(2U, maps.size());
  MapInfo* r_map_info = maps[0].get();
  MapInfo* rx_map_info = maps[1].get();

  // Get the elf from the read-only map first.
  Elf* elf = r_map_info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_EQ(elf, rx_map_info->GetElf(process_memory_, ARCH_ARM));

  // Now use file maps.
  maps.clear();
  InitMapInfo(maps, false);
  ASSERT_EQ(2U, maps.size());
  r_map_info = maps[0].get();
  rx_map_info = maps[1].get();

  // Get the elf from the read-only map first.
  elf = r_map_info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_EQ(elf, rx_map_info->GetElf(process_memory_, ARCH_ARM));
}

// Verify that a read-only map followed by an empty map, then followed by
// a read-execute map will result in the same elf object in both maps.
TEST_F(MapInfoGetElfTest, read_only_followed_by_empty_then_read_exec_share_elf) {
  auto r_info = MapInfo::Create(0x1000, 0x2000, 0, PROT_READ, elf_.path);
  auto empty = MapInfo::Create(r_info, 0x2000, 0x3000, 0, 0, "");
  auto rw_info = MapInfo::Create(empty, 0x3000, 0x4000, 0x2000, PROT_READ | PROT_EXEC, elf_.path);

  Elf32_Ehdr ehdr;
  TestInitEhdr<Elf32_Ehdr>(&ehdr, ELFCLASS32, EM_ARM);
  memory_->SetMemory(0x1000, &ehdr, sizeof(ehdr));
  Elf* elf = rw_info->GetElf(process_memory_, ARCH_ARM);
  ASSERT_TRUE(elf != nullptr);
  ASSERT_TRUE(elf->valid());

  ASSERT_EQ(elf, r_info->GetElf(process_memory_, ARCH_ARM));
}

}  // namespace unwindstack
