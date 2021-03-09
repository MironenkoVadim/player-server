#ifndef VEER_TYPES_PREPROC_QT_MARK_HPP_
#define VEER_TYPES_PREPROC_QT_MARK_HPP_

#pragma once

#include <veer/types/preproc/mark.hpp>

namespace veer::types::preproc {

inline QDataStream& operator<<( QDataStream& ds, const Mark& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_position;
	ds << value.m_v;
	ds << value.m_positionStdDev;
	ds << value.m_vStdDev;
	ds << value.m_snr;
	ds << value.m_threshold;
	ds << value.m_markId;
	ds << value.m_distanceIndex;
	ds << value.m_azimuthIndex;
	ds << value.m_dopplerIndex;
	ds << value.m_zoneNumber;
	ds << value.m_markTypes;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Mark& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_position;
	ds >> value.m_v;
	ds >> value.m_positionStdDev;
	ds >> value.m_vStdDev;
	ds >> value.m_snr;
	ds >> value.m_threshold;
	ds >> value.m_markId;
	ds >> value.m_distanceIndex;
	ds >> value.m_azimuthIndex;
	ds >> value.m_dopplerIndex;
	ds >> value.m_zoneNumber;
	ds >> value.m_markTypes;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, const Mark& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTP::Mark: = [";
	dbg << "position = " << value.m_position;
	dbg << ", v = " << value.m_v;
	dbg << ", positionStdDev = " << value.m_positionStdDev;
	dbg << ", vStdDev = " << value.m_vStdDev;
	dbg << ", snr = " << value.m_snr;
	dbg << ", threshold = " << value.m_threshold;
	dbg << ", markId = " << value.m_markId;
	dbg << ", distanceIndex = " << value.m_distanceIndex;
	dbg << ", azimuthIndex = " << value.m_azimuthIndex;
	dbg << ", dopplerIndex = " << value.m_dopplerIndex;
	dbg << ", zoneNumber = " << static_cast< int >( value.m_zoneNumber );
	dbg << "])";
	return ( dbg );
}

} // namespace veer::types::preproc


#endif // ifndef VEER_TYPES_PREPROC_QT_MARK_HPP_
