#ifndef VEER_COMMON_TYPES_EMISSION_PATTERN_HPP_
#define VEER_COMMON_TYPES_EMISSION_PATTERN_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/enum_bitmask_operations.hpp>

namespace veer::types::radar {

enum class EmissionPattern : quint8
{
	AlwaysOn  = 0x00, //!< Всегда включены все направления
	Cycling42 = 0x01, //!< Циклическое переключение направлений: 4 / 2
};

} // namespace veer::types::radar

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/radar/qt/emission_pattern.hpp>
#endif

#endif // ifndef VEER_COMMON_TYPES_EMISSION_PATTERN_HPP_
