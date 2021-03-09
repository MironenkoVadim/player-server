#ifndef VEER_PROTOCOLS_TRACKING_QT_BASE_TRACK_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_BASE_TRACK_HPP_

#pragma once

#include <veer/protocols/tracking/base_track.hpp>

namespace veer::protocols::tracking {

inline QDebug operator<<( QDebug dbg, const BaseTrack value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPT::BaseTrack: = [";
	dbg << "m_number = " << value.m_number;
	dbg << ", m_markId = " << value.m_markId;
	dbg << ", m_externalNumber = " << value.m_externalNumber;
	dbg << ", m_formingTime = " << value.m_formingTime;
	dbg << ", m_captureTime = " << value.m_captureTime;
	dbg << ", m_trackingTime = " << value.m_trackingTime;
	dbg << ", m_trackingSteps = " << value.m_trackingSteps;
	dbg << ", m_confirmationsCount = " << static_cast< quint16 >( value.m_confirmationsCount );
	dbg << ", m_missesCount = " << static_cast< quint16 >( value.m_missesCount );
	dbg << ", m_trackingCode = " << static_cast< quint16 >( value.m_trackingCode );
	dbg << ", m_infoSources = " << value.m_infoSources;
	dbg << ", m_maneuverType = " << value.m_maneuverType;
	dbg << ", m_trackStatus = " << value.m_trackStatus;
	dbg << ", m_target = " << value.m_target;
	dbg << "])";
	return ( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const BaseTrack& value )
{
	ds << value.m_number;
	ds << value.m_markId;
	ds << value.m_externalNumber;
	ds << value.m_formingTime;
	ds << value.m_captureTime;
	ds << value.m_trackingTime;
	ds << value.m_trackingSteps;
	ds << value.m_confirmationsCount;
	ds << value.m_missesCount;
	ds << value.m_trackingCode;
	ds << value.m_infoSources;
	ds << value.m_maneuverType;
	ds << value.m_trackStatus;
	ds << value.m_stub;
	ds << value.m_target;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, BaseTrack& value )
{
	ds >> value.m_number;
	ds >> value.m_markId;
	ds >> value.m_externalNumber;
	ds >> value.m_formingTime;
	ds >> value.m_captureTime;
	ds >> value.m_trackingTime;
	ds >> value.m_trackingSteps;
	ds >> value.m_confirmationsCount;
	ds >> value.m_missesCount;
	ds >> value.m_trackingCode;
	ds >> value.m_infoSources;
	ds >> value.m_maneuverType;
	ds >> value.m_trackStatus;
	ds >> value.m_stub;
	ds >> value.m_target;

	return( ds );
}

} // namespace veer::protocols::tracking

#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_BASE_TRACK_HPP_
