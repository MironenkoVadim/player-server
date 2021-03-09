#ifndef VEER_TYPES_PREPROC_MARK_TYPES_HPP_
#define VEER_TYPES_PREPROC_MARK_TYPES_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/enum_bitmask_operations.hpp>


namespace veer::types::preproc {

/*!
 * \brief Информация о типах отметки
 */
enum class MarkTypes : quint8
{
	Unknown     = 0,    //!< Не известно
	ActiveNoise = 0x01, //!< Отметка активной помехи
	Target      = 0x02, //!< Отметка для программы вторичной обработки
	SuperSpeed  = 0x04, //!< Отметка со скоростью, превышающей порог обработки
	Undefined   = 0xFF  //!< Значение по умолчанию
};

} // namespace veer::types::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/preproc/qt/mark_types.hpp>
#endif

// Обязательно в глобальной области видимости
ENABLE_BITMASK_OPERATORS( veer::types::preproc::MarkTypes )

#endif // ifndef VEER_TYPES_PREPROC_MARK_TYPES_HPP_
