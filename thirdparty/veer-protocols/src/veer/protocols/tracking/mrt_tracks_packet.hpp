#ifndef VEER_PROTOCOLS_TRACKING_MRT_TRACKS_PACKET_HPP_
#define VEER_PROTOCOLS_TRACKING_MRT_TRACKS_PACKET_HPP_

#pragma once

#include <veer/protocols/tracking/mrt_track.hpp>


namespace veer::protocols::tracking {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
const quint16 MrtTracksPacketVersion { 0x5631 };       // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей пакет трасс третички
 */
const quint32 MrtTracksPacketEndMarker { 0x544d5250 }; // TMRP

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

using MrtTracksVector = std::vector< MrtTrack >;

/*!
 * \brief Заголовок пакета для передачи набора трасс от третички
 */
class MrtTracksPacketHeader : public veer::protocols::base::Header
{
public:
	MrtTracksPacketHeader()
	{
		setType( VTC::CodogramType::MrtTracksPack );
		setSize( sizeof( MrtTracksPacketHeader ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::MrtTracksPacketVersion ); }

	quint16 tracksCount() const { return( m_tracksCount ); }
	void setTracksCount( quint16 tracksCount ) { m_tracksCount = tracksCount; }

	quint32 cycleNumber() const { return( m_cycleNumber ); }
	void setCycleNumber( quint32 cycleNumber ) { m_cycleNumber = cycleNumber; }

	VTC::TimeSpec64 periodStartTime() const { return( m_periodStartTime ); }
	void setPeriodStartTime( VTC::TimeSpec64 periodStartTime ) { m_periodStartTime = periodStartTime; }

	VTC::TimeSpec64 sendingTime() const { return( m_sendingTime ); }
	void setSendingTime( VTC::TimeSpec64 sendingTime ) { m_sendingTime = sendingTime; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const MrtTracksPacketHeader& value );
	friend QDataStream& operator>>( QDataStream& ds, MrtTracksPacketHeader& value );
	friend QDebug operator<<( QDebug dbg, const MrtTracksPacketHeader& value );
	#endif

	friend class MrtTracksData;

private:
	quint16         m_version { C::MrtTracksPacketVersion }; //!< Номер версии структуры
	quint16         m_tracksCount     { UINT16_MAX };        //!< Количество треков в пакете
	quint32         m_cycleNumber     { UINT32_MAX };        //!< Номер периода обзора
	VTC::TimeSpec64 m_periodStartTime { 0 };                 //!< Время начала периода когерентного накопления { с, нс }
	VTC::TimeSpec64 m_sendingTime     { 0 };                 //!< Время отправки в канал связи { с, нс }
}; // class MrtTracksPacketHeader


/*!
 * \brief Маркер окончания пакета для передачи набора трасс от третички
 */
struct MrtTracksPacketFooter
{
	quint32 endMarker = C::MrtTracksPacketEndMarker; //!< Маркер, записываемый в конец описания пакета трасс от третички
};


class MrtTracksData
{
public:
	friend QDataStream& operator<<( QDataStream& ds, MrtTracksData& value );
	friend QDataStream& operator>>( QDataStream& ds, MrtTracksData& value );

	MrtTracksPacketHeader& header() { return( m_header ); }
	MrtTracksVector& tracks() { return ( m_tracks ); }
	MrtTracksPacketFooter& footer() { return( m_footer ); }
	quint32 size()     { updateSize(); return( m_header.size() ); }
	quint32 dataSize() { updateSize(); return( m_header.dataSize() ); }
	void updateSize();

private:
	MrtTracksPacketHeader m_header;
	MrtTracksVector       m_tracks;
	MrtTracksPacketFooter m_footer;
}; // class MrtTracksData

inline void MrtTracksData::updateSize()
{
	quint32 size = sizeof( MrtTracksPacketHeader ) + sizeof( MrtTracksPacketFooter ) - sizeof( VPB::Header );
	size += static_cast< quint32 >( m_tracks.size() * sizeof( MrtTrack ) );
	m_header.setSize( size );
}


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/mrt_tracks_packet.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::MrtTracksPacketHeader ) == sizeof( veer::protocols::base::Header ) + 32,
               "Invalid size of class veer::protocols::MrtTracksPacketHeader" );


#endif // ifndef VEER_PROTOCOLS_TRACKING_MRT_TRACKS_PACKET_HPP_
