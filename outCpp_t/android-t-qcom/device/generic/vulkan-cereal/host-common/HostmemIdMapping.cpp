// Copyright 2019 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "host-common/HostmemIdMapping.h"

namespace android {
namespace emulation {

// static
const HostmemIdMapping::Id HostmemIdMapping::kInvalidHostmemId = 0;

static HostmemIdMapping* sMapping() {
    static HostmemIdMapping* s = new HostmemIdMapping;
    return s;
}

// static
HostmemIdMapping* HostmemIdMapping::get() {
    return sMapping();
}

// TODO: Add registerHostmemFixed version that takes a predetermined id,
// for snapshots
HostmemIdMapping::Id HostmemIdMapping::add(const struct MemEntry *entry) {
    if (entry->hva == 0 || entry->size == 0) return kInvalidHostmemId;

    Id wantedId;

    if (entry->register_fixed) {
        wantedId = entry->fixed_id;
        mCurrentId = wantedId + 1;
    } else {
        wantedId = mCurrentId++;
    }

    HostmemIdMapping::Entry hostmem_entry;
    hostmem_entry.id = wantedId;
    hostmem_entry.hva = entry->hva;
    hostmem_entry.size = entry->size;
    hostmem_entry.caching = entry->caching;
    mEntries.set(wantedId, hostmem_entry);
    return wantedId;
}

void HostmemIdMapping::remove(HostmemIdMapping::Id id) {
    mEntries.erase(id);
}

HostmemIdMapping::Entry HostmemIdMapping::get(HostmemIdMapping::Id id) const {
    const HostmemIdMapping::Entry badEntry {
        kInvalidHostmemId, 0, 0,
    };

    if (kInvalidHostmemId == id) return badEntry;

    auto entry = mEntries.get(id);

    if (!entry) return badEntry;

    return *entry;
}

void HostmemIdMapping::clear() {
    mEntries.clear();
}

} // namespace android
} // namespace emulation

// C interface for use with vm operations
extern "C" {

uint64_t android_emulation_hostmem_register(const struct MemEntry *entry) {
    return static_cast<uint64_t>(
        android::emulation::HostmemIdMapping::get()->add(entry));
}

void android_emulation_hostmem_unregister(uint64_t id) {
    android::emulation::HostmemIdMapping::get()->remove(id);
}

HostmemEntry android_emulation_hostmem_get_info(uint64_t id) {
    return static_cast<HostmemEntry>(
        android::emulation::HostmemIdMapping::get()->get(id));
}

} // extern "C"
