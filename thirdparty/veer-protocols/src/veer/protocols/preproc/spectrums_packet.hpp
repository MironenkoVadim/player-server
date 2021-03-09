#ifndef VEER_PROTOCOLS_PREPROC_SPECTRUMS_PACKET_HPP_
#define VEER_PROTOCOLS_PREPROC_SPECTRUMS_PACKET_HPP_

#pragma once

#include <veer/types/preproc/adaptive_threshold.hpp>
#include <veer/types/preproc/mark.hpp>
#include <veer/types/preproc/spectrum.hpp>

#include <veer/types/radar/emission_direction.hpp>
#include <veer/types/radar/emission_pattern.hpp>
#include <veer/types/radar/zone.hpp>

#include <veer/protocols/base/header.hpp>

namespace veer::protocols::preproc {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
const quint16 SpectrumsPacketVersion { 0x5631 };       // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей спектр
 */
const quint32 SpectrumsPacketEndMarker { 0x50534152 }; // PSAR

} // namespace constants

namespace C   = constants;
namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VTP = veer::types::preproc;
namespace VTR = veer::types::radar;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

using SpectrumsVector = std::vector< std::tuple< VTR::ControlZone, std::vector< VTP::Mark >, std::vector< VTP::Spectrum >, VTP::AdaptiveThreshold > >;

/*!
 * \brief Заголовок пакета для передачи набора спектров от программы первичной обработки
 */
class SpectrumsPacketHeader : public veer::protocols::base::Header
{
public:
	SpectrumsPacketHeader()
	{
		setType( VTC::CodogramType::SpectrumsPack );
		setSize( sizeof( SpectrumsPacketHeader ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::SpectrumsPacketVersion ); }

	quint16 periodsCount()                { return ( m_periodsCount ); }
	void setPeriodsCount( quint16 value ) { m_periodsCount = value; }

	float periodTime()                { return ( m_periodDuration ); }
	void setPeriodTime( float value ) { m_periodDuration = value; }

	VTC::TimeSpec64 periodStartTime()                     { return ( m_periodStartTime ); }
	void setPeriodStartTime( const VTC::TimeSpec64 time ) { m_periodStartTime = time; }

	VTC::TimeSpec64 sendingTime()                     { return ( m_sendingTime ); }
	void setSendingTime( const VTC::TimeSpec64 time ) { m_sendingTime = time; }
	void setSendingTime()                             { m_sendingTime = VTC::TimeSpec64(); }

	quint32 cycleNumber()                { return ( m_cycleNumber ); }
	void setCycleNumber( quint32 value ) { m_cycleNumber = value; }

	VTR::EmissionDirection emissionDirection() const { return( m_emissionDirection ); }
	void setEmissionDirection( VTR::EmissionDirection emissionDirection ) { m_emissionDirection = emissionDirection; }

	VTR::EmissionPattern emissionPattern() const { return( m_emissionPattern ); }
	void setEmissionPattern( VTR::EmissionPattern emissionPattern ) { m_emissionPattern = emissionPattern; }

	quint8 zonesCount() const { return( m_zonesCount ); }
	void setZonesCount( quint8 zonesCount ) { m_zonesCount = zonesCount; }

	quint8 blocksCount() const { return( m_blocksCount ); }
	void setBlocksCount( quint8 blocksCount ) { m_blocksCount = blocksCount; }

	float samplingFrequency()                { return ( m_samplingFrequency ); }
	void setSamplingFrequency( float value ) { m_samplingFrequency = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SpectrumsPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, SpectrumsPacketHeader& value );
	#endif
	friend class SpectrumsData;

private:
	quint16                m_version           { C::SpectrumsPacketVersion };      //!< Номер версии структуры
	quint16                m_periodsCount      { UINT16_MAX };                     //!< Количество периодов когерентного накопления
	float                  m_periodDuration    { VC::FloatNAN };                   //!< Длительность периода когерентного накопления { с }
	VTC::TimeSpec64        m_periodStartTime   { 0 };                              //!< Время начала периода когерентного накопления { с, нс }
	VTC::TimeSpec64        m_sendingTime       { 0 };                              //!< Время отправки в канал связи { с, нс }
	quint32                m_cycleNumber       { UINT32_MAX };                     //!< Номер периода обзора
	VTR::EmissionDirection m_emissionDirection { VTR::EmissionDirection::Zero };   //!< Битовая маска направлений излучения в данном периоде накопления
	VTR::EmissionPattern   m_emissionPattern   { VTR::EmissionPattern::AlwaysOn }; //!< Шаблон излучения
	quint8                 m_zonesCount        { UINT8_MAX };                      //!< Количество зон в периоде обзора
	quint8                 m_blocksCount       { UINT8_MAX };                      //!< Количество блоков данных для хранения спектров
	float                  m_samplingFrequency { VC::FloatNAN };                   //!< Частота дискретизации
}; // class SpectrumsPacketHeader


/*!
 * \brief Маркер окончания пакета для передачи набора спектров
 */
struct SpectrumsPacketFooter
{
	quint32 endMarker = C::SpectrumsPacketEndMarker; //!< Маркер, записываемый в конец описания пакета спектров
};


class SpectrumsData
{
public:
	SpectrumsPacketHeader& header()       { return( m_header ); }
	SpectrumsVector& zones()              { return( m_zones ); }
	SpectrumsPacketFooter& footer()       { return( m_footer ); }
	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize();

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, SpectrumsData& value );
	friend QDataStream& operator>>( QDataStream& ds, SpectrumsData& value );
	#endif

private:
	SpectrumsPacketHeader m_header;
	SpectrumsVector       m_zones;
	SpectrumsPacketFooter m_footer;
}; // class SpectrumsData


inline void SpectrumsData::updateSize()
{
	quint32 size = sizeof( SpectrumsPacketHeader ) + sizeof( SpectrumsPacketFooter ) - sizeof( VPB::Header );
	for ( const auto& zone: m_zones )
	{
		size += static_cast< quint32 >( sizeof( VTR::ControlZone ) );
		size += static_cast< quint32 >( std::get< 1 >( zone ).size() * sizeof( VTP::Mark ) );
		for ( const auto& spectrum: std::get< 2 >( zone ) )
		{
			size += static_cast< quint32 >( sizeof( VTP::Spectrum ) + spectrum.dataSize() - sizeof( std::complex< double >* ) );
		}
		size += static_cast< quint32 >( sizeof( VTP::AdaptiveThreshold ) + std::get< 3 >( zone ).dataSize() - sizeof( double* ) );
	}
	m_header.setSize( size );
}


#pragma pack(pop)

} // namespace veer::protocols::preproc
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/preproc/qt/spectrums_packet.hpp>
#endif

static_assert( sizeof( veer::protocols::preproc::SpectrumsPacketHeader ) == sizeof( veer::protocols::base::Header ) + 44,
               "Invalid size of struct veer::protocols::SpectrumsPacketHeader" );


#endif // ifndef VEER_PROTOCOLS_PREPROC_SPECTRUMS_PACKET_HPP_
