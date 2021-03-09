#ifndef VEER_BACKPORTS_QT_COMMON_HPP_
#define VEER_BACKPORTS_QT_COMMON_HPP_

#pragma once

#if defined( QT_VERSION )

#if QT_VERSION <= 0x050700
#include <QtGlobal>
template< typename ... Args >
struct QOverload
{
	template< typename C, typename R >
	static constexpr auto of( R ( C::* pmf )( Args... ) ) -> decltype( pmf )
	{
		return( pmf );
	}
};

// this adds const to non-const objects (like std::as_const)
template < typename T >
Q_DECL_CONSTEXPR typename std::add_const< T >::type& qAsConst( T& t ) noexcept
{
	return( t );
}


// prevent rvalue arguments:
template < typename T >
void qAsConst( const T&& ) = delete;


#endif // if QT_VERSION <= 0x050700

#endif // if defined( QT_VERSION )

#endif // VEER_BACKPORTS_QT_COMMON_HPP_
