#ifndef VEER_PROTOCOLS_TRACKING_ADSB_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_ADSB_TRACK_HPP_

#pragma once

#include <veer/types/tracking/adsb.hpp>

#include <veer/protocols/tracking/base_track.hpp>

namespace veer::protocols::tracking {

namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;


#pragma pack(push, 1)

class AdsbTrack : public BaseTrack
{
public:
	AdsbTrack() { setInfoSources( VTT::InfoSources::Adsb ); }

	VTT::AdsbInfo& adsbInfo() { return( m_adsbInfo ); }
	void setAdsbInfo( const VTT::AdsbInfo& value ) { m_adsbInfo = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const AdsbTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, AdsbTrack& value );
	friend QDebug operator<<( QDebug dbg, const AdsbTrack& value );
	#endif

private:
	VTT::AdsbInfo m_adsbInfo; //!< Код режима MarkS
}; // class AdsbTrack


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/adsb_track.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::AdsbTrack ) ==
               sizeof( veer::protocols::tracking::BaseTrack ) + sizeof( veer::types::tracking::AdsbInfo ),
               "Invalid size of class veer::protocols::tracking::AdsbTrack" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_ADSB_TRACK_HPP_
