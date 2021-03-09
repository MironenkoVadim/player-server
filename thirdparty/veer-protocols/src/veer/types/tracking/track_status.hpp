#ifndef VEER_TYPES_TRACKING_TRACK_STATUS_HPP_
#define VEER_TYPES_TRACKING_TRACK_STATUS_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>

namespace veer::types::tracking {

/*!
 * \brief Статус трассы
 */
enum class TrackStatus : quint8
{
	Reset         = 0, //!< Трасса сброшена
	Update        = 1, //!< Обновление статуса
	Capture       = 2, //!< Трасса на захвате (не проверен критерий подтверждения)
	CaptureStart  = 3, //!< Начало захвата
	Tracking      = 4, //!< Трасса сопровождается
	TrackingStart = 5  //!< Начало сопровождения
};

} // namespace veer::types::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/track_status.hpp>
#endif

#endif // ifndef VEER_TYPES_TRACKING_TRACK_STATUS_HPP_
