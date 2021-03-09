#ifndef VEER_PROTOCOLS_TRACKING_ADSB_TRACKS_PACKET_HPP_
#define VEER_PROTOCOLS_TRACKING_ADSB_TRACKS_PACKET_HPP_

#pragma once

#include <veer/protocols/tracking/adsb_track.hpp>


namespace veer::protocols::tracking {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
const quint16 AdsbTracksPacketVersion { 0x5631 };       // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей пакет трасс ADS-B
 */
const quint32 AdsbTracksPacketEndMarker { 0x54414450 }; // TADP

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

using AdsbTracksVector = std::vector< AdsbTrack >;

/*!
 * \brief Заголовок пакета для передачи набора трасс от ADS-B
 */
class AdsbTracksPacketHeader : public veer::protocols::base::Header
{
public:
	AdsbTracksPacketHeader()
	{
		setType( VTC::CodogramType::AdsbTracksPack );
		setSize( sizeof( AdsbTracksPacketHeader ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::AdsbTracksPacketVersion ); }

	quint16 tracksCount() const { return( m_tracksCount ); }
	void setTracksCount( quint16 tracksCount ) { m_tracksCount = tracksCount; }

	quint32 cycleNumber() const { return( m_cycleNumber ); }
	void setCycleNumber( quint32 cycleNumber ) { m_cycleNumber = cycleNumber; }

	VTC::TimeSpec64 periodStartTime() const { return( m_periodStartTime ); }
	void setPeriodStartTime( VTC::TimeSpec64 periodStartTime ) { m_periodStartTime = periodStartTime; }

	VTC::TimeSpec64 sendingTime() const { return( m_sendingTime ); }
	void setSendingTime( VTC::TimeSpec64 sendingTime ) { m_sendingTime = sendingTime; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const AdsbTracksPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, AdsbTracksPacketHeader& value );
	friend QDebug operator<<( QDebug dbg, const AdsbTracksPacketHeader value );
	#endif

	friend class AdsbTracksData;

private:
	quint16         m_version { C::AdsbTracksPacketVersion }; //!< Номер версии структуры
	quint16         m_tracksCount     { UINT16_MAX };         //!< Количество треков в пакете
	quint32         m_cycleNumber     { UINT32_MAX };         //!< Номер периода обзора
	VTC::TimeSpec64 m_periodStartTime { 0 };                  //!< Время начала периода когерентного накопления { с, нс }
	VTC::TimeSpec64 m_sendingTime     { 0 };                  //!< Время отправки в канал связи { с, нс }
}; // class AdsbTracksPacketHeader


/*!
 * \brief Маркер окончания пакета для передачи набора трасс от ADS-B
 */
struct AdsbTracksPacketFooter
{
	quint32 endMarker = C::AdsbTracksPacketEndMarker; //!< Маркер, записываемый в конец описания пакета трасс от ADS-B
};


class AdsbTracksData
{
public:

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, AdsbTracksData& value );
	friend QDataStream& operator>>( QDataStream& ds, AdsbTracksData& value );
	#endif

	AdsbTracksPacketHeader& header() { return( m_header ); }
	AdsbTracksVector& tracks() { return ( m_tracks ); }
	AdsbTracksPacketFooter& footer() { return( m_footer ); }
	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize();

private:
	AdsbTracksPacketHeader m_header;
	AdsbTracksVector       m_tracks;
	AdsbTracksPacketFooter m_footer;
}; // class AdsbTracksData


inline void AdsbTracksData::updateSize()
{
	quint32 size = sizeof( AdsbTracksPacketHeader ) + sizeof( AdsbTracksPacketFooter ) - sizeof( VPB::Header );
	size += static_cast< quint32 >( m_tracks.size() * sizeof( AdsbTrack ) );
	m_header.setSize( size );
}


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/adsb_tracks_packet.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::AdsbTracksPacketHeader ) == sizeof( veer::protocols::base::Header ) + 32,
               "Invalid size of class veer::protocols::AdsbTracksPacketHeader" );


#endif // ifndef VEER_PROTOCOLS_TRACKING_ADSB_TRACKS_PACKET_HPP_
