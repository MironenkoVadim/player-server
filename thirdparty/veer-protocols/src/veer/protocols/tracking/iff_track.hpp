#ifndef VEER_PROTOCOLS_TRACKING_IFF_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_IFF_TRACK_HPP_

#pragma once

#include <veer/types/tracking/iff.hpp>

#include <veer/protocols/tracking/base_track.hpp>

namespace veer::protocols::tracking {

namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;


#pragma pack(push, 1)

class IffTrack : public BaseTrack
{
public:
	IffTrack() { setInfoSources( VTT::InfoSources::Iff ); }

	VTT::IffInfo& iffInfo() { return( m_iffInfo ); }
	void setIffInfo( const VTT::IffInfo& value ) { m_iffInfo = value; }
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const IffTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, IffTrack& value );
	#endif

private:
	VTT::IffInfo m_iffInfo; //!< Код режима MarkS
};


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/iff_track.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::IffTrack ) == sizeof( veer::protocols::tracking::BaseTrack ) + 16,
               "Invalid size of class veer::protocols::tracking::IffTrack" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_IFF_TRACK_HPP_
