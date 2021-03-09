#ifndef VEER_PROTOCOLS_TRACKING_RADAR_TRACKS_PACKET_HPP_
#define VEER_PROTOCOLS_TRACKING_RADAR_TRACKS_PACKET_HPP_

#pragma once

#include <veer/protocols/tracking/radar_track.hpp>


namespace veer::protocols::tracking {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
const quint16 RadarTracksPacketVersion { 0x5631 };       // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей отметку
 */
const quint32 RadarTracksPacketEndMarker { 0x54524450 }; // TRDP

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

using RadarTracksVector = std::vector< RadarTrack >;

/*!
 * \brief Заголовок пакета для передачи набора трасс от радара
 */
class RadarTracksPacketHeader : public veer::protocols::base::Header
{
public:
	RadarTracksPacketHeader()
	{
		setType( VTC::CodogramType::RadarTracksPack );
		setSize( sizeof( RadarTracksPacketHeader ) - sizeof( Header ) );
	}

	quint16 version() const { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::RadarTracksPacketVersion ); }

	quint16 tracksCount() const { return( m_tracksCount ); }
	void setTracksCount( quint16 tracksCount ) { m_tracksCount = tracksCount; }

	quint32 cycleNumber() const { return( m_cycleNumber ); }
	void setCycleNumber( quint32 cycleNumber ) { m_cycleNumber = cycleNumber; }

	VTC::TimeSpec64 periodStartTime() const { return( m_periodStartTime ); }
	void setPeriodStartTime( VTC::TimeSpec64 periodStartTime ) { m_periodStartTime = periodStartTime; }

	VTC::TimeSpec64 sendingTime() const { return( m_sendingTime ); }
	void setSendingTime( VTC::TimeSpec64 sendingTime ) { m_sendingTime = sendingTime; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const RadarTracksPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, RadarTracksPacketHeader& value );
	friend QDebug operator<<( QDebug dbg, const RadarTracksPacketHeader value );
	#endif

	friend class RadarTracksData;

private:
	quint16         m_version { C::RadarTracksPacketVersion }; //!< Номер версии структуры
	quint16         m_tracksCount     { UINT16_MAX };          //!< Количество треков в пакете
	quint32         m_cycleNumber     { UINT32_MAX };          //!< Номер периода обзора
	VTC::TimeSpec64 m_periodStartTime { 0 };                   //!< Время начала периода когерентного накопления { с, нс }
	VTC::TimeSpec64 m_sendingTime     { 0 };                   //!< Время отправки в канал связи { с, нс }
}; // class RadarTracksPacketHeader


/*!
 * \brief Маркер окончания пакета для передачи набора трасс от радара
 */
struct RadarTracksPacketFooter
{
	quint32 endMarker = C::RadarTracksPacketEndMarker; //!< Маркер, записываемый в конец описания пакета трасс от радара
};


class RadarTracksData
{
public:
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, RadarTracksData& value );
	friend QDataStream& operator>>( QDataStream& ds, RadarTracksData& value );
	#endif

	RadarTracksPacketHeader& header() { return( m_header ); }
	RadarTracksVector& tracks()       { return( m_tracks ); }
	RadarTracksPacketFooter& footer() { return( m_footer ); }
	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize();

private:
	RadarTracksPacketHeader m_header;
	RadarTracksVector       m_tracks;
	RadarTracksPacketFooter m_footer;
}; // class RadarTracksData


inline void RadarTracksData::updateSize()
{
	quint32 size = sizeof( RadarTracksPacketHeader ) + sizeof( RadarTracksPacketFooter ) - sizeof( VPB::Header );
	size += static_cast< quint32 >( m_tracks.size() * sizeof( RadarTrack ) );
	m_header.setSize( size );
}


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/radar_tracks_packet.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::RadarTracksPacketHeader ) == sizeof( veer::protocols::base::Header ) + 32,
               "Invalid size of class veer::protocols::RadarTracksPacketHeader" );


#endif // ifndef VEER_PROTOCOLS_TRACKING_RADAR_TRACKS_PACKET_HPP_
