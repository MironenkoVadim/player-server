#ifndef VEER_PROTOCOLS_TRACKING_QT_MRT_TRACKS_PACKET_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_MRT_TRACKS_PACKET_HPP_

#pragma once

#include <veer/protocols/tracking/mrt_tracks_packet.hpp>


namespace veer::protocols::tracking {

inline QDebug operator<<( QDebug dbg, const MrtTracksPacketHeader& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPT::MrtTracksPacketHeader: = [";
	dbg << "m_version = " << value.m_version;
	dbg << ", m_tracksCount = " << value.m_tracksCount;
	dbg << ", m_cycleNumber = " << value.m_cycleNumber;
	dbg << ", m_periodStartTime = " << value.m_periodStartTime;
	dbg << ", m_sendingTime = " << value.m_sendingTime;
	dbg << "])";

	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const MrtTracksPacketHeader& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_tracksCount;
	ds << value.m_cycleNumber;
	ds << value.m_periodStartTime;
	ds << value.m_sendingTime;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, MrtTracksPacketHeader& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_tracksCount;
	ds >> value.m_cycleNumber;
	ds >> value.m_periodStartTime;
	ds >> value.m_sendingTime;

	return( ds );
}


inline QDataStream& operator<<( QDataStream& ds, MrtTracksData& value )
{
	value.updateSize();
	value.m_header.setTracksCount( static_cast< quint16 >( value.tracks().size() ) );
	ds << value.m_header;

	for ( const auto& track: value.m_tracks )
	{
		ds << track;
	}
	ds << value.m_footer.endMarker;

	return( ds );
} // <<


inline QDataStream& operator>>( QDataStream& ds, MrtTracksData& value )
{
	ds >> value.m_header;

	value.m_tracks.resize( value.m_header.tracksCount() );
	for ( auto vit = value.m_tracks.begin(); vit != value.m_tracks.end(); ++vit )
	{
		ds >> *vit;
	}
	ds >> value.m_footer.endMarker;

	return( ds );
} // >>

} // namespace veer::protocols::tracking

#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_MRT_TRACKS_PACKET_HPP_
