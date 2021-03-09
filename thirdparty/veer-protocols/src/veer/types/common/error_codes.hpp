#ifndef VEER_TYPES_COMMON_ERROR_CODES_HPP_
#define VEER_TYPES_COMMON_ERROR_CODES_HPP_

#pragma once

#include <veer/common/config.hpp>


namespace veer::types::common {

enum class ErrorCode : quint16
{
	OK    = 0x0000, //!< Нет ошибки
	Error = 0x0001  //!< Обобщённая ошибка
};

} // namespace veer::types::common
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/error_codes.hpp>
#endif

static_assert( sizeof( veer::types::common::ErrorCode ) == 2,
               "Invalid size of enum veer::types::common::ErrorCode" );

#endif // ifndef VEER_TYPES_COMMON_ERROR_CODES_HPP_
