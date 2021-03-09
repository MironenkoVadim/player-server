#ifndef VEER_TYPES_COMMON_APPLICATION_HPP_
#define VEER_TYPES_COMMON_APPLICATION_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/enum_bitmask_operations.hpp>

namespace veer::types::common {

/**
 * \brief Идентификаторы программ в проекте
 */

enum class Application : quint16
{
	None        = 0x0000,
	Poi         = 0x0001,
	Accumulator = 0x0002,
	Toi         = 0x0004,
	Any         = 0xFFFF
};

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/application.hpp>
#endif

// Обязательно в глобальной области видимости
ENABLE_BITMASK_OPERATORS( veer::types::common::Application )

static_assert( sizeof( veer::types::common::Application ) == 2,
               "Invalid size of enum veer::types::common::Application" );

#endif // ifndef VEER_TYPES_COMMON_APPLICATION_HPP_
