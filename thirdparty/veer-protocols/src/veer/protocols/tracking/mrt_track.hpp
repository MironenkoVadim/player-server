#ifndef VEER_PROTOCOLS_TRACKING_MRT_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_MRT_TRACK_HPP_

#pragma once

#include <veer/types/tracking/adsb.hpp>
#include <veer/types/tracking/radar.hpp>

#include <veer/protocols/tracking/base_track.hpp>

namespace veer::protocols::tracking {

namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;


#pragma pack(push, 1)

class MrtTrack : public BaseTrack
{
public:
	VTT::PlanarCM planarCM() const { return( m_planarCM ); }
	void setPlanarCM( const VTT::PlanarCM& planarCM ) { m_planarCM = planarCM; }

	VTT::HeightCM heightCM() const { return( m_heightCM ); }
	void setHeightCM( const VTT::HeightCM& heightCM ) { m_heightCM = heightCM; }

	float averageSnr() const { return( m_averageSnr ); }
	void setAverageSnr( float value ) { m_averageSnr = value; }

	VTT::AdsbInfo& adsbInfo() { return( m_adsbInfo ); }
	void setAdsbInfo( const VTT::AdsbInfo& value ) { m_adsbInfo = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const MrtTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, MrtTrack& value );
	#endif

private:
	// из RadarTrack
	VTT::PlanarCM m_planarCM   {}; //!< Ковариационная матрица для плоскостных координат
	VTT::HeightCM m_heightCM   {}; //!< Ковариационная матрица для высоты
	float         m_averageSnr {}; //!< Усреднённое отношение сигнал/шум для отметок
	// из AdsbTrack
	VTT::AdsbInfo m_adsbInfo;      //!< Код режима MarkS
}; // class MrtTrack


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/mrt_track.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::MrtTrack ) == sizeof( veer::protocols::tracking::BaseTrack ) + 148,
               "Invalid size of class veer::protocols::tracking::MrtTrack" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_MRT_TRACK_HPP_
