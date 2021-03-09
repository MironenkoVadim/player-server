#ifndef VEER_TYPES_PREPROC_ADAPTIVE_THRESHOLD_HPP_
#define VEER_TYPES_PREPROC_ADAPTIVE_THRESHOLD_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/base/header.hpp>
#include <veer/types/common/points.hpp>
#include <veer/types/common/timespec64.hpp>
#include <veer/types/common/velocities.hpp>
#include <veer/types/radar/zone_index.hpp>

#include <unistd.h>


namespace veer::types::preproc {

namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VTR = veer::types::radar;

#pragma pack(push, 1)


class AdaptiveThreshold
{
public:
	VTR::ZoneIndex zoneNumber() const { return( m_zoneNumber ); }
	void setZoneNumber( quint8 value ) { m_zoneNumber = static_cast< VTR::ZoneIndex >( value ); }
	void setZoneNumber( VTR::ZoneIndex value ) { m_zoneNumber = value; }

	double* data() const { return( m_data ); }
	void setData( double* value, quint16 size ) { m_data = value; m_dataSize = size; }

	quint16 dataSize() const { return( m_dataSize ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const AdaptiveThreshold& value );
	friend QDataStream& operator>>( QDataStream& ds, AdaptiveThreshold& value );
	friend QDebug operator<<( QDebug dbg, const AdaptiveThreshold& value );
	#endif

private:
	VTR::ZoneIndex m_zoneNumber   { VTR::ZoneIndex::Unknown }; //!< Номер зоны, в которой получен адаптивный порог
	quint8         m_stub         { UINT8_MAX };               //!<
	quint16        m_dataSize     { 0 };                       //!< Размер блока данных
	double*        m_data         { nullptr };                 //!< Указатель на блок данных
}; // class AdaptiveThreshold


#pragma pack(pop)

} // namespace veer::types::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/preproc/qt/adaptive_threshold.hpp>
#endif


static_assert( sizeof( veer::types::preproc::AdaptiveThreshold ) == 4 + sizeof( double* ),
               "Invalid size of struct veer::types::preproc::AdaptiveThreshold" );


#endif // ifndef VEER_TYPES_PREPROC_ADAPTIVE_THRESHOLD_HPP_
