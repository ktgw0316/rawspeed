/*
    RawSpeed - RAW file decoder.

    Copyright (C) 2017 Axel Waggershauser

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include "io/BitStream.h"  // for BitStream, BitStreamCacheLeftInRightOut
#include "io/Buffer.h"     // for Buffer::size_type
#include "io/Endianness.h" // for getLE
#include <cstdint>         // for uint32_t, uint8_t

namespace rawspeed {

struct LSBBitPumpTag;

// The LSBPump is ordered in LSB bit order,
// i.e. we push into the cache from the left and read it from the right

using BitPumpLSB = BitStream<LSBBitPumpTag, BitStreamCacheLeftInRightOut>;

template <>
inline BitPumpLSB::size_type BitPumpLSB::fillCache(const uint8_t* input) {
  static_assert(BitStreamCacheBase::MaxGetBits >= 32, "check implementation");

  cache.push(getLE<uint32_t>(input), 32);
  return 4;
}

} // namespace rawspeed
