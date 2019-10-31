#pragma once    
#include <cstdint>

#include "lib/expected.h"

#include "params.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"

using Exp_i32 = const util::Expected<int32_t>;
using Exp_u32 = const util::Expected<uint32_t>;


Exp_i32 parse_param(uint32_t, const char*) noexcept;
template <typename T> const util::Expected<T> check_type(int32_t value, T&) noexcept;
template <typename T> const util::Expected<T> read_param(Param, T&) noexcept;
void set_params(TankManager&, PotManager&) noexcept;