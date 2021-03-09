#ifndef VEER_TYPES_COMMON_POINTS_HPP_
#define VEER_TYPES_COMMON_POINTS_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/limits.hpp>

#include <array>


namespace veer::types::common {

namespace C = veer::common;

#pragma pack(push, 1)

template< typename T > using Array3 = std::array< T, 3 >;
using Array3F                       = std::array< float, 3 >;


template< typename T >
class Point3
{
public:
	inline bool operator==( const Point3& rhs ) const
	{
		return ( ( m_u.s.a == rhs.m_u.s.a ) &&
		         ( m_u.s.b == rhs.m_u.s.b ) &&
		         ( m_u.s.c == rhs.m_u.s.c ) );
	}

	inline Array3< T >& array()                  { return ( m_u.array ); }
	inline const Array3< T >& constArray() const { return ( m_u.array ); }
	inline void setArray( const Array3< T >& array )
	{
		m_u.s.a = array[0];
		m_u.s.b = array[1];
		m_u.s.c = array[2];
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	template< typename > friend QDataStream& operator<<( QDataStream& ds, Point3< T > value );
	template< typename > friend QDataStream& operator>>( QDataStream& ds, Point3< T >& value );
	template< typename > friend QDebug operator<<( QDebug dbg, Point3< T > value );
	#endif

protected:
	inline T a() { return( m_u.s.a ); }
	inline T b() { return( m_u.s.b ); }
	inline T c() { return( m_u.s.c ); }

	inline void setA( T a ) { m_u.s.a = a; }
	inline void setB( T b ) { m_u.s.b = b; }
	inline void setC( T c ) { m_u.s.c = c; }

private:
	union
	{
		struct _ { float a; float b; float c; } s;
		Array3< T > array { C::FloatNAN, C::FloatNAN, C::FloatNAN };
	} m_u;
}; // class Point3


using Point3F = Point3< float >;


class RadarPoint3F : public Point3F
{
public:
	inline RadarPoint3F() = default;
	inline RadarPoint3F( float r, float az, float el ) { setR( r ); setAz( az ); setEl( el ); }

	inline float r()  { return( a() ); }
	inline float az() { return( b() ); }
	inline float el() { return( c() ); }

	inline void setR( float r ) { setA( r ); }
	inline void setAz( float az ) { setB( az ); }
	inline void setEl( float el ) { setC( el ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDebug operator<<( QDebug dbg, RadarPoint3F value );
	#endif
}; // class RadarPoint3F


class CartesianPoint3F : public Point3F
{
public:
	inline CartesianPoint3F() = default;
	inline CartesianPoint3F( float x, float y, float h ) { setX( x ); setY( y ); setH( h ); }

	inline float x() { return( a() ); }
	inline float y() { return( b() ); }
	inline float h() { return( c() ); }

	inline void setX( float x ) { setA( x ); }
	inline void setY( float y ) { setB( y ); }
	inline void setH( float h ) { setC( h ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDebug operator<<( QDebug dbg, CartesianPoint3F value );
	#endif
}; // class CartesianPoint3F


//! Точка в сферической системе координат с высотой относительно уровня моря
class LatLongPoint3F : public Point3F
{
public:
	inline LatLongPoint3F() = default;
	inline LatLongPoint3F( float lat, float lon, float h ) { setLat( lat ); setLon( lon ); setH( h ); }

	inline float lat() { return( a() ); }
	inline float lon() { return( b() ); }
	inline float h() { return( c() ); }

	inline void setLat( float lat ) { setA( lat ); }
	inline void setLon( float lon ) { setB( lon ); }
	inline void setH( float h ) { setC( h ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDebug operator<<( QDebug dbg, LatLongPoint3F value );
	#endif
}; // class LatLongPoint3F


#pragma pack(pop)

} // namespace veer::types::common


#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/points.hpp>
#endif

static_assert( sizeof( veer::types::common::Point3F ) == 12,
               "Invalid size of struct veer::types::common::Point3F" );

#endif // ifndef VEER_TYPES_COMMON_POINTS_HPP_
