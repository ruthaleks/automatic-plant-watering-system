#pragma once    
#include <cstdint>

#include "lib/expected.h"

#include "param.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"

using Exp_i32 = const util::Expected<int32_t>;
using Exp_u32 = const util::Expected<uint32_t>;


template <typename T> const util::Expected<T> check_type(int32_t value, T&) noexcept;
Exp_i32 parse_param(uint32_t, const char*) noexcept;
template <typename T> const util::Expected<T> read_param(Param, T&) noexcept;
void set_params(TankManager&, PotManager&) noexcept;

namespace print{
void error_msg(const char*) noexcept;
void ok_msg(const char* ) noexcept;
void wrn_msg(const char* ) noexcept;
}
