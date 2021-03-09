#ifndef VEER_TYPES_PREPROC_SPECTRUM_HPP_
#define VEER_TYPES_PREPROC_SPECTRUM_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/base/header.hpp>
#include <veer/types/common/points.hpp>
#include <veer/types/common/timespec64.hpp>
#include <veer/types/common/velocities.hpp>
#include <veer/types/radar/zone_index.hpp>

#include <complex>
#include <unistd.h>

namespace veer::types::preproc {

namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VTR = veer::types::radar;

#pragma pack(push, 1)


class Spectrum
{
public:
	VTR::ZoneIndex zoneNumber() const { return( m_zoneNumber ); }
	void setZoneNumber( quint8 value ) { m_zoneNumber = static_cast< VTR::ZoneIndex >( value ); }
	void setZoneNumber( VTR::ZoneIndex value ) { m_zoneNumber = value; }

	quint8 number() const { return( m_number ); }
	void setNumber( quint8 value ) { m_number = value; }

	bool isPrimary() const { return( m_isPrimary == 1 ); }
	void setPrimary( bool value ) { value ? m_isPrimary = 1 : 0; }

	std::complex< double >* data() const { return( m_data ); }
	void setData( std::complex< double >* value, quint32 size ) { m_data = value; m_dataSize = size; }

	quint32 dataSize() const { return( m_dataSize ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Spectrum& value );
	friend QDataStream& operator>>( QDataStream& ds, Spectrum& value );
	friend QDebug operator<<( QDebug dbg, const Spectrum& value );
	#endif

private:
	VTR::ZoneIndex          m_zoneNumber   { VTR::ZoneIndex::Unknown }; //!< Номер зоны, в которой получен спектр
	quint8                  m_number       { UINT8_MAX };               //!< Номер вибратора или вторичного канала
	quint8                  m_isPrimary    { 0 };                       //!< 0 (вторичный канал), 1 (сигнал с вибратора)
	quint8                  m_stub         { UINT8_MAX };               //!<
	quint32                 m_dataSize     { 0 };                       //!< Размер блока данных
	std::complex< double >* m_data         { nullptr };                 //!< Указатель на блок данных
}; // class Spectrum

#pragma pack(pop)

} // namespace veer::types::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/preproc/qt/spectrum.hpp>
#endif

static_assert( sizeof( veer::types::preproc::Spectrum ) == 8 + sizeof( double* ),
               "Invalid size of struct veer::types::preproc::Spectrum" );


#endif // ifndef VEER_TYPES_PREPROC_SPECTRUM_HPP_
