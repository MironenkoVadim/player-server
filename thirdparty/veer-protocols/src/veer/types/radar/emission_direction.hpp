#ifndef VEER_TYPES_RADAR_EMISSION_DIRECTION_HPP_
#define VEER_TYPES_RADAR_EMISSION_DIRECTION_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/enum_bitmask_operations.hpp>

namespace veer::types::radar {

/*!
 * \brief Активные направления излучения
 */
enum class EmissionDirection : quint8
{
	Zero   = 0x00, //!< Излучение во всех направлениях отключено
	First  = 0x01, //!< Излучение в первом направлении
	Second = 0x02, //!< Излучение во втором направлении
	Third  = 0x04, //!< Излучение в третьем направлении
	Fourth = 0x08, //!< Излучение в четвёртом направлении
};

} // namespace veer::types::radar

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/radar/qt/emission_direction.hpp>
#endif

// Обязательно в глобальной области видимости
ENABLE_BITMASK_OPERATORS( veer::types::radar::EmissionDirection )

#endif // ifndef VEER_TYPES_RADAR_EMISSION_DIRECTION_HPP_
