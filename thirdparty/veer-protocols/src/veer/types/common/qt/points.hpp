#ifndef VEER_TYPES_COMMON_QT_POINTS_HPP_
#define VEER_TYPES_COMMON_QT_POINTS_HPP_

#pragma once

#include <veer/types/common/points.hpp>

// Обязательно вне пространства имён!
template< typename T > inline QDataStream& operator<<( QDataStream& ds, const veer::types::common::Array3< T >& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	if ( std::is_same< T, float >::value ) { ds.setFloatingPointPrecision( QDataStream::SinglePrecision ); }
	if ( std::is_same< T, double >::value ) { ds.setFloatingPointPrecision( QDataStream::DoublePrecision ); }

	ds << value[0];
	ds << value[1];
	ds << value[2];

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


// Обязательно вне пространства имён!
template< typename T > inline QDataStream& operator>>( QDataStream& ds, veer::types::common::Array3< T >& value )
{
	QDataStream::FloatingPointPrecision prec { ds.floatingPointPrecision() };
	if ( std::is_same< T, float >::value ) { ds.setFloatingPointPrecision( QDataStream::SinglePrecision ); }
	if ( std::is_same< T, double >::value ) { ds.setFloatingPointPrecision( QDataStream::DoublePrecision ); }

	ds >> value[0];
	ds >> value[1];
	ds >> value[2];

	ds.setFloatingPointPrecision( prec );
	return( ds );
}


template< typename T > inline QDebug operator<<( QDebug dbg, const veer::types::common::Array3< T >& value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::Array3: = [";
	dbg << "a[0] = " << value[0];
	dbg << "a[1] = " << value[1];
	dbg << "a[2] = " << value[2];
	dbg << "]";
	return( dbg );
}


namespace veer::types::common {

inline QDataStream& operator<<( QDataStream& ds, Point3F value )
{
	ds << value.constArray();
	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, Point3F& value )
{
	ds >> value.array();
	return( ds );
}


inline QDebug operator<<( QDebug dbg, Point3F value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::Point3F: = [";
	dbg << "a = " << value.array()[0];
	dbg << "b = " << value.array()[1];
	dbg << "c = " << value.array()[2];
	dbg << "]";
	return( dbg );
}


inline QDebug operator<<( QDebug dbg, RadarPoint3F value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::RadarPoint3F: = [";
	dbg << "r = " << value.array()[0];
	dbg << "az = " << value.array()[1];
	dbg << "el = " << value.array()[2];
	dbg << "]";
	return( dbg );
}


inline QDebug operator<<( QDebug dbg, CartesianPoint3F value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::CartesianPoint3F: = [";
	dbg << "x = " << value.array()[0];
	dbg << "y = " << value.array()[1];
	dbg << "h = " << value.array()[2];
	dbg << "]";
	return( dbg );
}


inline QDebug operator<<( QDebug dbg, LatLongPoint3F value )
{
	QDebugStateSaver saver( dbg );
	dbg.nospace() << "(VTC::LatLongPoint3F: = [";
	dbg << "ph = " << value.array()[0];
	dbg << "la = " << value.array()[1];
	dbg << "h = " << value.array()[2];
	dbg << "]";
	return( dbg );
}

} // namespace veer::types::common


#endif // ifndef VEER_TYPES_COMMON_QT_POINTS_HPP_
