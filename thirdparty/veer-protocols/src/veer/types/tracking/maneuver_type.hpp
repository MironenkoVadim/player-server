#ifndef VEER_TYPES_TRACKING_MANEUVER_TYPE_HPP_
#define VEER_TYPES_TRACKING_MANEUVER_TYPE_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>

namespace veer::types::tracking {

/*!
 * \brief Признак манёвра
 */
enum class ManeuverType : quint8
{
	Lack          = 0, //!< Отсутствие манёвра
	LowIntensity  = 1, //!< Манёвр слабой интенсивности (без смены модели движения)
	HighIntensity = 2  //!< Манёвр высокой интенсивности (смена модели движения)
};

} // namespace veer::types::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/maneuver_type.hpp>
#endif

#endif // ifndef VEER_TYPES_TRACKING_MANEUVER_TYPE_HPP_
