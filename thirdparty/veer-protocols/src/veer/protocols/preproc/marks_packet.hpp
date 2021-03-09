#ifndef VEER_PROTOCOLS_PREPROC_MARKS_PACKET_HPP_
#define VEER_PROTOCOLS_PREPROC_MARKS_PACKET_HPP_

#pragma once

#include <veer/types/preproc/mark.hpp>
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
const quint16 MarksPacketVersion { 0x5632 };       // V2

/*!
 * \brief Фиксированное значение в конце структуры, описывающей набор отметок
 */
const quint32 MarksPacketEndMarker { 0x504d4152 }; // PMAR

} // namespace constants

namespace C   = constants;
namespace VC  = veer::common;
namespace VPB = veer::protocols::base;
namespace VTC = veer::types::common;
namespace VTP = veer::types::preproc;
namespace VTR = veer::types::radar;

#pragma pack(push, 1)

using MarksVector = std::vector< std::tuple< VTR::ControlZone, std::vector< VTP::Mark >  > >;

/*!
 * \brief Заголовок пакета для передачи набора отметок от программы первичной обработки
 */
class MarksPacketHeader : public veer::protocols::base::Header
{
public:
	MarksPacketHeader()
	{
		setType( VTC::CodogramType::MarksPack );
		setSize( sizeof( MarksPacketHeader ) - sizeof( Header ) );
	}

	MarksPacketHeader( bool withNoiseMarks )
	{
		if ( withNoiseMarks ) { setType( VTC::CodogramType::NoiseMarksPack ); }
		setSize( sizeof( MarksPacketHeader ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::MarksPacketVersion ); }

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
	friend QDataStream& operator<<( QDataStream& ds, const MarksPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, MarksPacketHeader& value );
	#endif
	friend class MarksData;

private:
	quint16                m_version           { C::MarksPacketVersion };          //!< Номер версии структуры
	quint16                m_periodsCount      { UINT16_MAX };                     //!< Количество периодов когерентного накопления
	float                  m_periodDuration    { VC::FloatNAN };                   //!< Длительность периода когерентного накопления { с }
	VTC::TimeSpec64        m_periodStartTime   { 0 };                              //!< Время начала периода когерентного накопления { с, нс }
	VTC::TimeSpec64        m_sendingTime       { 0 };                              //!< Время отправки в канал связи { с, нс }
	quint32                m_cycleNumber       { UINT32_MAX };                     //!< Номер периода обзора
	VTR::EmissionDirection m_emissionDirection { VTR::EmissionDirection::Zero };   //!< Битовая маска направлений излучения в данном периоде накопления
	VTR::EmissionPattern   m_emissionPattern   { VTR::EmissionPattern::AlwaysOn }; //!< Шаблон излучения
	quint8                 m_zonesCount        { UINT8_MAX };                      //!< Количество зон в периоде обзора
	quint8                 m_blocksCount       { UINT8_MAX };                      //!< Количество блоков данных для хранения отметок
	float                  m_samplingFrequency { VC::FloatNAN };                   //!< Частота дискретизации
}; // class MarksPacketHeader


class NoiseMarksPacketHeader : public MarksPacketHeader
{
public:
	NoiseMarksPacketHeader() :
		MarksPacketHeader( true ) {}
};

/*!
 * \brief Маркер окончания пакета для передачи набора отметок
 */
struct MarksPacketFooter
{
	quint32 endMarker = C::MarksPacketEndMarker; //!< Маркер, записываемый в конец описания пакета отметок
};


class MarksData
{
public:
	MarksData() = default;
	MarksData( bool withNoiseMarks )
	{
		if ( withNoiseMarks ) { m_header.setType( VTC::CodogramType::NoiseMarksPack ); }
	}

	MarksPacketHeader& header()       { return( m_header ); }
	MarksVector& zones()              { return( m_zones ); }
	MarksPacketFooter& footer()       { return( m_footer ); }
	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize();

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, MarksData& value );
	friend QDataStream& operator>>( QDataStream& ds, MarksData& value );
	#endif

private:
	MarksPacketHeader m_header;
	MarksVector       m_zones;
	MarksPacketFooter m_footer;
}; // class MarksData


inline void MarksData::updateSize()
{
	quint32 size = sizeof( MarksPacketHeader ) + sizeof( MarksPacketFooter ) - sizeof( VPB::Header );
	for ( const auto& zone: m_zones )
	{
		size += static_cast< quint32 >( sizeof( VTR::ControlZone ) );
		size += static_cast< quint32 >( std::get< 1 >( zone ).size() * sizeof( VTP::Mark ) );
	}
	m_header.setSize( size );
}


class NoiseMarksData : public MarksData
{
public:
	NoiseMarksData() :
		MarksData( true ) {}
};


#pragma pack(pop)

} // namespace veer::protocols::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/preproc/qt/marks_packet.hpp>
#endif

static_assert( sizeof( veer::protocols::preproc::MarksPacketHeader ) == sizeof( veer::protocols::base::Header ) + 44,
               "Invalid size of struct veer::protocols::MarksPacketHeader" );

#endif // ifndef VEER_PROTOCOLS_PREPROC_MARKS_PACKET_HPP_
