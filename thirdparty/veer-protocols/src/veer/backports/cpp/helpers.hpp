#ifndef VEER_BACKPORTS_CPP_HELPERS_HPP_
#define VEER_BACKPORTS_CPP_HELPERS_HPP_

#pragma once

#if ( __cplusplus >= 201103L )
#include <type_traits>
#endif

#if ( __cplusplus >= 201103L ) && ( __cplusplus < 201402L )

namespace std
{

template< class T >
using underlying_type_t = typename std::underlying_type< T >::type;

} // namespace std

#endif

#if ( __cplusplus >= 201103L ) && ( __cplusplus < 201702L )

namespace std
{

#if defined( __STRICT_ANSI__ ) || defined( __e2k__ )
template< typename ... Ts > struct make_void { typedef void type; };
template< typename ... Ts > using void_t = typename make_void< Ts... >::type;
#endif

} // namespace std

#endif

#endif // ifndef VEER_BACKPORTS_CPP_HELPERS_HPP_
