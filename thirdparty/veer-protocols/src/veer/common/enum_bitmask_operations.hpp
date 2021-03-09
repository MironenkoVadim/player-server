#ifndef ENUM_BITWISE_OPERATIONS_HPP_
#define ENUM_BITWISE_OPERATIONS_HPP_

#pragma once

/*!
 * \file Битовые операции со значениями перечислений
 */

#include <type_traits>
#include <veer/backports/cpp/helpers.hpp>

template< typename Enum >
struct EnableBitMaskOperators
{
	static const bool Enable = false;
};

// NOLINTNEXTLINE
#define ENABLE_BITMASK_OPERATORS( x ) \
	template<> \
	struct EnableBitMaskOperators< x > \
	{ \
		static const bool Enable = true; \
	};


template< typename Enum >
typename std::enable_if< EnableBitMaskOperators< Enum >::Enable, Enum >::type
operator~( Enum e )
{
	using UE = std::underlying_type_t< Enum >;
	return( static_cast< Enum >( ~static_cast< UE >( e ) ) );
}


template< typename Enum >
typename std::enable_if< EnableBitMaskOperators< Enum >::Enable, Enum >::type
operator|( Enum lhs, Enum rhs )
{
	using UE = std::underlying_type_t< Enum >;
	return( static_cast< Enum >( static_cast< UE >( lhs ) | static_cast< UE >( rhs ) ) );
}


template< typename Enum >
typename std::enable_if< EnableBitMaskOperators< Enum >::Enable, typename std::add_lvalue_reference< Enum >::type >::type
operator|=( Enum& lhs, Enum rhs )
{
	using UE = std::underlying_type_t< Enum >;
	lhs      = static_cast< Enum >( static_cast< UE >( lhs ) | static_cast< UE >( rhs ) );
	return( lhs );
}


template< typename Enum >
typename std::enable_if< EnableBitMaskOperators< Enum >::Enable, Enum >::type
operator&( Enum lhs, Enum rhs )
{
	using UE = std::underlying_type_t< Enum >;
	return( static_cast< Enum >( static_cast< UE >( lhs ) & static_cast< UE >( rhs ) ) );
}


template< typename Enum >
typename std::enable_if< EnableBitMaskOperators< Enum >::Enable, typename std::add_lvalue_reference< Enum >::type >::type
operator&=( Enum& lhs, Enum rhs )
{
	using UE = std::underlying_type_t< Enum >;
	lhs      = static_cast< Enum >( static_cast< UE >( lhs ) & static_cast< UE >( rhs ) );
	return( lhs );
}


#endif // ifndef ENUM_BITWISE_OPERATIONS_HPP_
