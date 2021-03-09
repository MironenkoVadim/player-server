#ifndef VEER_PROTOCOLS_TRACKING_BASE_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_BASE_TRACK_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/protocols/tracking/target.hpp>

#include <veer/types/common/timespec64.hpp>
#include <veer/types/tracking/info_sources.hpp>
#include <veer/types/tracking/maneuver_type.hpp>
#include <veer/types/tracking/target_type.hpp>
#include <veer/types/tracking/track_status.hpp>

#include <array>
#include <cmath>

namespace veer::protocols::tracking {

namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;

#pragma pack(push, 1)

class BaseTrack
{
public:
	quint32 number() const { return( m_number ); }
	void setNumber( quint32 number ) { m_number = number; }

	quint32 markId() const { return( m_markId ); }
	void setMarkId( quint32 value ) { m_markId = value; }

	quint16 externalNumber() const { return( m_externalNumber ); }
	void setExternalNumber( quint16 value ) { m_externalNumber = value; }

	VTC::TimeSpec64 formingTime() const { return( m_formingTime ); }
	void setFormingTime( VTC::TimeSpec64 formingTime ) { m_formingTime = formingTime; }

	VTC::TimeSpec64 captureTime() const { return( m_captureTime ); }
	void setCaptureTime( VTC::TimeSpec64 captureTime ) { m_captureTime = captureTime; }

	VTC::TimeSpec64 trackingTime() const { return( m_trackingTime ); }
	void setTrackingTime( VTC::TimeSpec64 trackingTime ) { m_trackingTime = trackingTime; }

	quint16 trackingSteps() const { return( m_trackingSteps ); }
	void setTrackingSteps( quint16 trackingSteps ) { m_trackingSteps = trackingSteps; }

	quint16 confirmationsCount() const { return( m_confirmationsCount ); }
	void setConfirmationsCount( quint16 confirmationsCount ) { m_confirmationsCount = confirmationsCount; }

	quint8 missesCount() const { return( m_missesCount ); }
	void setMissesCount( quint8 missesCount ) { m_missesCount = missesCount; }

	quint8 trackingCode() const { return( m_trackingCode ); }
	void setTrackingCode( quint8 trackingCode ) { m_trackingCode = trackingCode; }

	VTT::InfoSources infoSources() const { return( m_infoSources ); }
	void setInfoSources( VTT::InfoSources value ) { m_infoSources = value; }

	VTT::ManeuverType maneuverType() const { return( m_maneuverType ); }
	void setManeuverType( VTT::ManeuverType maneuverType ) { m_maneuverType = maneuverType; }

	VTT::TrackStatus trackStatus() const { return( m_trackStatus ); }
	void setTrackStatus( VTT::TrackStatus trackStatus ) { m_trackStatus = trackStatus; }

	Target& target() { return( m_target ); }
	void setTarget( const Target& target ) { m_target = target; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const BaseTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, BaseTrack& value );
	friend QDebug operator<<( QDebug dbg, const BaseTrack value );
	#endif

private:
	quint32           m_number             { UINT32_MAX };            //!< Номер трассы от 1 до 500 (для сопровождаемых трасс и трасс на захвате используются разные номера)
	quint32           m_markId             { UINT32_MAX };            //!< Номер отметки, на основании которой построена трасса (UINT32_MAX, если неизвестно)
	quint16           m_externalNumber     { UINT16_MAX };            //!< Номер трассы, назначенный внешним КП
	VTC::TimeSpec64   m_formingTime        { 0 };                     //!< Время формирования трассы
	VTC::TimeSpec64   m_captureTime        { 0 };                     //!< Время взятия на захват
	VTC::TimeSpec64   m_trackingTime       { 0 };                     //!< Время взятия на сопровождение
	quint16           m_trackingSteps      { UINT16_MAX };            //!< Количество тактов сопровождения
	quint16           m_confirmationsCount { UINT16_MAX };            //!< Количество подтверждений
	quint8            m_missesCount        { UINT8_MAX };             //!< Количество пропусков
	quint8            m_trackingCode       { UINT8_MAX };             //!< Коды сопровождения для последних 16 тактов (0 - экстраполяция, 1 - найдена отметка)
	VTT::InfoSources  m_infoSources  { VTT::InfoSources::Undefined }; //!< Источники объединённой трассы
	VTT::ManeuverType m_maneuverType { VTT::ManeuverType::Lack };     //!< Наличие манёвра
	VTT::TrackStatus  m_trackStatus  { VTT::TrackStatus::Reset };     //!< Статус трассы
	quint8            m_stub         { UINT8_MAX };
	Target            m_target;                                       //!< Координатная информация о трассе
}; // class BaseTrack

#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/base_track.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::BaseTrack ) == 108,
               "Invalid size of class veer::protocols::tracking::BaseTrack" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_BASE_TRACK_HPP_
