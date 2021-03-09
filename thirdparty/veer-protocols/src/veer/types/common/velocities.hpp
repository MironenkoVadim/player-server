#ifndef VEER_TYPES_COMMON_VELOCITIES_HPP_
#define VEER_TYPES_COMMON_VELOCITIES_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/types/common/points.hpp>


namespace veer::types::common {

#pragma pack(push, 1)

/*!
 * \brief Доплеровская скорость
 * Отличается от радиальной тем, что может содержать неоднозначность.
 */
class DopplerVelocity
{
public:
	inline DopplerVelocity() = default;
	inline DopplerVelocity( float value ) noexcept { m_dv = value; }

	inline bool operator==( DopplerVelocity rhs ) const
	{
		return ( m_dv == rhs.m_dv );
	}

	inline bool operator<( DopplerVelocity rhs ) const
	{
		return ( m_dv < rhs.m_dv );
	}

	inline float v() { return( m_dv ); }
	inline void setV( float v ) { m_dv = v; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, DopplerVelocity value );
	friend QDataStream& operator>>( QDataStream& ds, DopplerVelocity& value );
	friend QDebug operator<<( QDebug dbg, DopplerVelocity value );
	#endif

private:
	float m_dv {}; //!< Скорость { м/с }
}; // class DopplerVelocity


/*!
 * \brief Географическая скорость
 * Содержит компоненты скорости в декартовых координатах.
 */
class CartesianVelocity : public Point3F
{
public:
	inline CartesianVelocity() = default;
	inline CartesianVelocity( float x, float y, float h ) noexcept { setX( x ); setY( y ); setH( h ); }

	float x() { return( a() ); }
	float y() { return( b() ); }
	float h() { return( c() ); }

	void setX( float x ) { setA( x ); }
	void setY( float y ) { setB( y ); }
	void setH( float h ) { setC( h ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, CartesianVelocity value );
	friend QDataStream& operator>>( QDataStream& ds, CartesianVelocity& value );
	friend QDebug operator<<( QDebug dbg, CartesianVelocity value );
	#endif
}; // class CartesianVelocity

#pragma pack(pop)

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/velocities.hpp>
#endif

static_assert( sizeof( veer::types::common::DopplerVelocity ) == sizeof( float ),
               "Invalid size of struct veer::types::common::DopplerVelocity" );

static_assert( sizeof( veer::types::common::CartesianVelocity ) == sizeof( veer::types::common::Point3F ),
               "Invalid size of struct veer::types::common::CartesianVelocity" );


#endif // ifndef VEER_TYPES_COMMON_VELOCITIES_HPP_
