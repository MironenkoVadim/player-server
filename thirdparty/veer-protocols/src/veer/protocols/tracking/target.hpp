#ifndef VEER_PROTOCOLS_TRACKING_TARGET_HPP_
#define VEER_PROTOCOLS_TRACKING_TARGET_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/types/common/points.hpp>
#include <veer/types/common/velocities.hpp>
#include <veer/types/tracking/target_type.hpp>

namespace veer::protocols::tracking {

namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;

#pragma pack(push, 1)


/*!
 * \brief Координатная информация цели
 */
class Target
{
public:
	quint16 number() const { return ( m_number ); }
	void setNumber( quint16 number ) { m_number = number; }

	VTT::TargetType type() const { return ( m_type ); }
	void setType( VTT::TargetType type ) { m_type = type; }

	VTC::CartesianPoint3F& position()                   { return ( m_position ); }
	void setPosition( VTC::CartesianPoint3F position )  { m_position = position; }

	VTC::CartesianVelocity& velocity()                  { return ( m_velocity ); }
	void setVelocity( VTC::CartesianVelocity velocity ) { m_velocity = velocity; }

	float acceleration() const { return ( m_acceleration ); }
	void setAcceleration( float acceleration ) { m_acceleration = acceleration; }

	VTC::RadarPoint3F& poiPosition()                   { return ( m_poiPosition ); }
	void setPoiPosition( VTC::RadarPoint3F position )  { m_poiPosition = position; }

	VTC::DopplerVelocity& poiVelocity()                  { return ( m_poiVelocity ); }
	void setPoiVelocity( VTC::DopplerVelocity velocity ) { m_poiVelocity = velocity; }

	float snr() const { return ( m_snr ); }
	void setSnr( float snr ) { m_snr = snr; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Target& value );
	friend QDataStream& operator>>( QDataStream& ds, Target& value );
	friend QDebug operator<<( QDebug dbg, const Target value );
	#endif

private:
	quint16                m_number { UINT16_MAX };                 //!< Номер цели
	quint8                 m_stub   { UINT8_MAX };
	VTT::TargetType        m_type   { VTT::TargetType::Undefined }; //!< Тип цели
	VTC::CartesianPoint3F  m_position;                              //!< Позиция { м, м, м }
	VTC::CartesianVelocity m_velocity;                              //!< Скорость { м/с, м/с, м/с }
	float                  m_acceleration { VC::FloatNAN };         //!< Вертикальное ускорение { м/(с*c) }
	VTC::RadarPoint3F      m_poiPosition;                           //!< Позиция по данным первички
	VTC::DopplerVelocity   m_poiVelocity;                           //!< Радиальная скорость по данным первички
	float                  m_snr          { VC::FloatNAN };         //!< Отношение уровня сигнала к среднему уровню шума { дБ }
}; // class Target

#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/target.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::Target ) == 52,
               "Invalid size of class veer::protocols::tracking::Target" );


#endif // ifndef VEER_PROTOCOLS_TRACK_TARGET_HPP_
