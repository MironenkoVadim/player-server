#ifndef VEER_PROTOCOLS_TRACKING_QT_TARGET_HPP_
#define VEER_PROTOCOLS_TRACKING_QT_TARGET_HPP_

#pragma once

#include <veer/protocols/tracking/target.hpp>

namespace veer::protocols::tracking {

inline QDebug operator<<( QDebug dbg, const Target value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VPCT::Target: = [";
	dbg << "m_number = " << value.m_number;
	dbg << ", m_type = " << value.m_type;
	dbg << ", m_position = " << value.m_position;
	dbg << ", m_velocity = " << value.m_velocity;
	dbg << ", m_acceleration = " << value.m_acceleration;
	dbg << ", m_poiPosition = " << value.m_poiPosition;
	dbg << ", m_poiVelocity = " << value.m_poiVelocity;
	dbg << ", m_snr = " << value.m_snr;
	dbg << "])";
	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, const Target& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_number;
	ds << value.m_stub;
	ds << value.m_type;
	ds << value.m_position;
	ds << value.m_velocity;
	ds << value.m_acceleration;
	ds << value.m_poiPosition;
	ds << value.m_poiVelocity;
	ds << value.m_snr;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Target& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_number;
	ds >> value.m_stub;
	ds >> value.m_type;
	ds >> value.m_position;
	ds >> value.m_velocity;
	ds >> value.m_acceleration;
	ds >> value.m_poiPosition;
	ds >> value.m_poiVelocity;
	ds >> value.m_snr;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}

} // namespace veer::protocols::tracking
#endif // ifndef VEER_PROTOCOLS_TRACKING_QT_TARGET_HPP_
