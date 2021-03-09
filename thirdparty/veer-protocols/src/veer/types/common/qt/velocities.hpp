#ifndef VEER_TYPES_COMMON_QT_VELOCITIES_HPP_
#define VEER_TYPES_COMMON_QT_VELOCITIES_HPP_

#pragma once

#include <veer/types/common/velocities.hpp>

namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, DopplerVelocity value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds << value.m_dv;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, DopplerVelocity& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	ds.setFloatingPointPrecision( QDataStream::SinglePrecision );

	ds >> value.m_dv;

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


inline QDebug operator<<( QDebug dbg, DopplerVelocity value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::DopplerVelocity: = [";
	dbg << "dv = " << value.m_dv;
	return( dbg );
}


inline QDataStream& operator<<( QDataStream& ds, CartesianVelocity value )
{
	ds << value.constArray();
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, CartesianVelocity& value )
{
	ds >> value.array();
	return( ds );
}


inline QDebug operator<<( QDebug dbg, CartesianVelocity value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::CartesianVelocity: = [";
	dbg << "x = " << value.x();
	dbg << "y = " << value.y();
	dbg << "h = " << value.h();
	return( dbg );
}

} // namespace veer::types::common

#endif // ifndef VEER_TYPES_COMMON_QT_VELOCITIES_HPP_
