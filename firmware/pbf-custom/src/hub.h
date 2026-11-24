// Decode the two filament switches on the hub's shared analog signal.
#pragma once

#include <stdint.h>

namespace hub {

enum class State { kEmpty, kExternal, kMain, kBoth };

inline State decode(uint32_t mv) {
  // GPIO4 measured 1208 mV (both), 1498 mV (external) and 2177 mV (empty).
  // Main-only is provisionally estimated at ~1630 mV by interpolating the
  // connector's 1543 mV reading between the external-only and empty readings.
  if (mv < 1100 || mv > 2300) return State::kEmpty;
  if (mv < 1353) return State::kBoth;
  if (mv < 1564) return State::kExternal;
  if (mv < 1904) return State::kMain;
  return State::kEmpty;
}

constexpr bool externalPresent(State state) {
  return state == State::kExternal || state == State::kBoth;
}

constexpr bool mainPresent(State state) {
  return state == State::kMain || state == State::kBoth;
}

}  // namespace hub
