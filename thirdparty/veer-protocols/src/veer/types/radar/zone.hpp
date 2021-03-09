#ifndef VEER_TYPES_RADAR_ZONE_HPP_
#define VEER_TYPES_RADAR_ZONE_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/types/common/points.hpp>

#include <cmath>

namespace veer::types::radar {

namespace VC = veer::common;

#pragma pack(push, 1)

class ControlZone
{
public:
	quint8 number() const { return( m_number ); }
	void setNumber( quint8 number ) { m_number = number; }

	quint16 marksCount() const { return( m_marksCount ); }
	void setMarksCount( quint16 value ) { m_marksCount = value; }

	quint16 spectrumsCount() const { return( m_spectrumsCount ); }
	void setSpectrumsCount( quint16 value ) { m_spectrumsCount = value; }

	float nearEdge() const { return( m_nearEdge ); }
	void setNearEdge( float nearEdge ) { m_nearEdge = nearEdge; }

	float farEdge() const { return( m_farEdge ); }
	void setFarEdge( float farEdge ) { m_farEdge = farEdge; }

	float carrier() const { return( m_carrier ); }
	void setCarrier( float carrier ) { m_carrier = carrier; }

	float velocityLimit() const { return( m_velocityLimit ); }
	void setVelocityLimit( float velocityLimit ) { m_velocityLimit = velocityLimit; }

	float deviation() const { return( m_deviation ); }
	void setDeviation( float deviation ) { m_deviation = deviation; }

	float snr() const { return( m_snr ); }
	void setSnr( float snr ) { m_snr = snr; }

	float pulseTime()                { return ( m_pulseTime * 1e-6F ); }
	void setPulseTime( float value ) { m_pulseTime = static_cast< quint16 >( std::lround( value * 1e6F ) ); }

	quint16 distanceChannels() const { return( m_distanceChannels ); }
	void setDistanceChannels( quint16 value ) { m_distanceChannels = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const ControlZone& value );
	friend QDataStream& operator>>( QDataStream& ds, ControlZone& value );
	#endif

private:
	quint8  m_number           { UINT8_MAX };    //!< Номер зоны
	quint8  m_version          { 3 };            //!< Версия протокола
	quint16 m_marksCount       { UINT16_MAX };   //!< Количество отметок
	quint16 m_spectrumsCount   { UINT16_MAX };   //!< Количество блоков спектров
	quint16 m_stub             { UINT16_MAX };   //!<
	float   m_nearEdge         { VC::FloatNAN }; //!< Ближняя граница { м }
	float   m_farEdge          { VC::FloatNAN }; //!< Дальняя граница { м }
	float   m_carrier          { VC::FloatNAN }; //!< Рабочая частота { Гц }
	float   m_velocityLimit    { VC::FloatNAN }; //!< Граница однозначности радиальной скорости { м/с }
	float   m_deviation        { VC::FloatNAN }; //!< Девиация частоты сигнала, которым засвечивается зона { Гц }
	float   m_snr              { VC::FloatNAN }; //!< Средний уровень шума { дБ }
	quint16 m_pulseTime        { UINT16_MAX };   //!< Длительность ЗС для зоны { мкс }
	quint16 m_distanceChannels { UINT16_MAX };   //!< Количество каналов дальности
}; // class ControlZone


#pragma pack(pop)

} // namespace veer::types::radar

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/radar/qt/zone.hpp>
#endif

static_assert( sizeof( veer::types::radar::ControlZone ) == 36,
               "Invalid size of struct veer::types::radar::ControlZone" );


#endif // ifndef VEER_TYPES_RADAR_ZONE_HPP_
