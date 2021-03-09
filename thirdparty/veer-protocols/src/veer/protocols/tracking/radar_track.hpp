#ifndef VEER_PROTOCOLS_TRACKING_RADAR_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_RADAR_TRACK_HPP_

#pragma once

#include <veer/types/tracking/radar.hpp>

#include <veer/protocols/tracking/base_track.hpp>

#include <array>

namespace veer::protocols::tracking {

namespace VTT = veer::types::tracking;

#pragma pack(push, 1)

class RadarTrack : public BaseTrack
{
public:
	RadarTrack() { setInfoSources( VTT::InfoSources::Radar ); }

	VTT::PlanarCM planarCM() const { return( m_planarCM ); }
	void setPlanarCM( const VTT::PlanarCM& planarCM ) { m_planarCM = planarCM; }

	VTT::HeightCM heightCM() const { return( m_heightCM ); }
	void setHeightCM( const VTT::HeightCM& heightCM ) { m_heightCM = heightCM; }

	float averageSnr() const { return( m_averageSnr ); }
	void setAverageSnr( float value ) { m_averageSnr = value; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const RadarTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, RadarTrack& value );
	#endif

private:
	VTT::PlanarCM m_planarCM   {}; //!< Ковариационная матрица для плоскостных координат
	VTT::HeightCM m_heightCM   {}; //!< Ковариационная матрица для высоты
	float         m_averageSnr {}; //!< Усреднённое отношение сигнал/шум для отметок
}; // class RadarTrack

#pragma pack(pop)

} // namespace veer::protocols::tracking
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/radar_track.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::RadarTrack ) == sizeof( veer::protocols::tracking::BaseTrack ) + 132,
               "Invalid size of class veer::protocols::tracking::RadarTrack" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_RADAR_TRACK_HPP_
