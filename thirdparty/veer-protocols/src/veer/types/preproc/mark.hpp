#ifndef VEER_TYPES_PREPROC_MARK_HPP_
#define VEER_TYPES_PREPROC_MARK_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/base/header.hpp>
#include <veer/types/common/points.hpp>
#include <veer/types/common/timespec64.hpp>
#include <veer/types/common/velocities.hpp>
#include <veer/types/preproc/mark_types.hpp>
#include <veer/types/radar/zone_index.hpp>


namespace veer::types::preproc {

namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VTR = veer::types::radar;

#pragma pack(push, 1)


class Mark
{
public:
	VTC::RadarPoint3F position() const { return( m_position ); }
	void setPosition( VTC::RadarPoint3F value ) { m_position = value; }

	VTC::DopplerVelocity velocity() const { return( m_v ); }
	void setVelocity( VTC::DopplerVelocity value ) { m_v = value; }

	VTC::RadarPoint3F positionStdDev() const { return( m_positionStdDev ); }
	void setPositionStdDev( VTC::RadarPoint3F value ) { m_positionStdDev = value; }

	VTC::DopplerVelocity velocityStdDev() const { return( m_vStdDev ); }
	void setVelocityStdDev( VTC::DopplerVelocity value ) { m_vStdDev = value; }

	float snr() const { return( m_snr ); }
	void setSnr( float value ) { m_snr = value; }

	float threshold() const { return( m_threshold ); }
	void setThreshold( float value ) { m_threshold = value; }

	quint32 markId() const { return( m_markId ); }
	void setMarkId( quint32 value ) { m_markId = value; }

	quint16 distanceIndex() const { return( m_distanceIndex ); }
	void setDistanceIndex( quint16 value ) { m_distanceIndex = value; }

	quint16 azimuthIndex() const { return ( m_azimuthIndex ); }
	void setAzimuthIndex( quint16 value ) { m_azimuthIndex = value; }

	quint16 dopplerIndex() const { return( m_dopplerIndex ); }
	void setDopplerIndex( quint16 value ) { m_dopplerIndex = value; }

	VTR::ZoneIndex zoneNumber() const { return( m_zoneNumber ); }
	void setZoneNumber( quint8 value ) { m_zoneNumber = static_cast< VTR::ZoneIndex >( value ); }
	void setZoneNumber( VTR::ZoneIndex value ) { m_zoneNumber = value; }

	MarkTypes markTypes() const { return( m_markTypes ); }
	void setMarkTypes( quint8 value ) { m_markTypes = static_cast< MarkTypes >( value ); }
	void setMarkTypes( MarkTypes value ) { m_markTypes = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Mark& value );
	friend QDataStream& operator>>( QDataStream& ds, Mark& value );
	friend QDebug operator<<( QDebug dbg, const Mark& value );
	#endif

private:
	VTC::RadarPoint3F    m_position;                            //!< Координаты отметки { м, рад, рад }
	VTC::DopplerVelocity m_v { VC::FloatNAN };                  //!< Радиальная скорость { м/с }

	VTC::RadarPoint3F    m_positionStdDev;                      //!< СКО координат отметок { м, рад, рад }
	VTC::DopplerVelocity m_vStdDev { VC::FloatNAN };            //!< СКО радиальной скорости { м/с }

	float m_snr       { VC::FloatNAN };                         //!< Отношение уровня сигнала к среднему уровню шума { дБ }
	float m_threshold { VC::FloatNAN };                         //!< Порог { дБ }

	quint32        m_markId        { UINT32_MAX };              //!< Уникальный номер отметки в текущем периоде накопления (UINT32_MAX, если неизвестно)
	quint16        m_distanceIndex { UINT16_MAX };              //!< Номер дальностного фильтра
	quint16        m_azimuthIndex  { UINT16_MAX };              //!< Номер азимутального фильтра
	quint16        m_dopplerIndex  { UINT16_MAX };              //!< Номер доплеровского фильтра
	VTR::ZoneIndex m_zoneNumber    { VTR::ZoneIndex::Unknown }; //!< Номер зоны, в которой получена отметка (UINT8_MAX, если неизвестно)
	MarkTypes      m_markTypes     { MarkTypes::Undefined };    //!< Информация о типе отметки (возможно наличие нескольких типов)
}; // class Mark

#pragma pack(pop)

} // namespace veer::types::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/preproc/qt/mark.hpp>
#endif


static_assert( sizeof( veer::types::preproc::Mark ) == 52,
               "Invalid size of struct veer::types::preproc::Mark" );


#endif // ifndef VEER_TYPES_PREPROC_MARK_HPP_
