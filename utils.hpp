#pragma once    
#include <cstdint>

#include "lib/expected.h"

#include "param.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;


using Exp_i32 = util::Expected<int32_t>;
using Exp_u32 = util::Expected<uint32_t>;

template <typename T> const util::Expected<T> check_type(int32_t value) noexcept;
Exp_i32 parse_param(uint32_t, const char*) noexcept;
template <typename T> const util::Expected<T> read_param( Param ) noexcept;
void set_params(TankManager&, PotManager&) noexcept;

namespace print{
void error_msg(const char*) noexcept;
void ok_msg(const char* ) noexcept;
void wrn_msg(const char* ) noexcept;
}
