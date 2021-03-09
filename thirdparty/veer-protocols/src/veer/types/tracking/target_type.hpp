#ifndef VEER_TYPES_TRACKING_TARGET_TYPE_HPP_
#define VEER_TYPES_TRACKING_TARGET_TYPE_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>

namespace veer::types::tracking {

/*!
 * \brief Тип цели
 */
enum class TargetType : quint8
{
	Undefined               = 0x00, //!< Класс цели не определён
	Airplane                = 0x01, //!< Самолёт
	AirplaneDrone           = 0x02, //!< Беспилотный самолёт
	AirplaneLight           = 0x03, //!< Легкомоторный самолёт
	Helicopter              = 0x11, //!< Вертолёт
	CruiseMissile           = 0x21, //!< Крылатая ракета
	HyperSpeedCruiseMissile = 0x22, //!< Гиперзвуковая крылатая ракета
	BallisticMissile        = 0x23, //!< Баллистическая ракета
	Aerostat                = 0x41, //!< Воздушный шар / аэростат
	NoiseSetter             = 0x81  //!< Помехопостановщик
};

} // namespace veer::types::tracking
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/target_type.hpp>
#endif

#endif // ifndef VEER_TYPES_TRACKING_TARGET_TYPE_HPP_
