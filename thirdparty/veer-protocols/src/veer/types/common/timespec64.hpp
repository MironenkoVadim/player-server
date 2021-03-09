#ifndef VEER_TYPES_COMMON_TIMESPEC64_HPP_
#define VEER_TYPES_COMMON_TIMESPEC64_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/const.hpp>

#include <cinttypes>
#include <cmath>
#include <ctime>

#include <sys/time.h>

namespace VC = veer::common;

namespace veer::types::common {

#pragma pack(push, 1)

class TimeSpec64
{
public:
	TimeSpec64()
	{
		struct timeval tv {0, 0};
		gettimeofday( &tv, nullptr );
		fromTimeval( tv );
	}

	explicit TimeSpec64( const struct timeval value ) noexcept { fromTimeval( value ); }
	explicit TimeSpec64( const struct timespec value ) noexcept { fromTimespec( value ); }
	explicit TimeSpec64( const qint64 sec ) noexcept :
		m_sec ( sec ),
		m_nsec( 0 ) {}
	explicit TimeSpec64( const qint64 sec, const qint32 nsec ) noexcept :
		m_sec ( sec ),
		m_nsec( nsec )  {}
	explicit TimeSpec64( const qint64 sec, const qint64 nsec ) noexcept :
		m_sec ( sec ),
		m_nsec( static_cast< qint32 >( nsec ) )  {}

	qint64 seconds() const { return( m_sec ); }
	void setSeconds( const qint64 value ) { m_sec = value; }
	qint64 nanoseconds() const { return ( m_nsec ); }
	void setNanoseconds( const qint32 value ) { m_nsec = value; }

	void fromTimeval( const struct timeval value )
	{
		m_sec  = value.tv_sec;
		m_nsec = static_cast< qint32 >( value.tv_usec * VC::K );
	}

	struct timeval toTimeval() const
	{
		struct timeval tv {m_sec, m_nsec / VC::K};
		return( tv );
	}

	void fromTimespec( const struct timespec val )
	{
		m_sec  = val.tv_sec;
		m_nsec = static_cast< qint32 >( val.tv_nsec );
	}

	struct timespec toTimespec() const
	{
		struct timespec ts {m_sec, m_nsec};
		return( ts );
	}

	void fromNs( qint64 ns )
	{
		m_sec  = ns / VC::G;
		m_nsec = static_cast< qint32 >( ns % VC::G );
	}

	qint64 toNs() const
	{
		return( m_sec * VC::G + m_nsec );
	}

	bool operator==( const TimeSpec64& rhs ) const
	{
		return ( ( m_sec == rhs.m_sec ) && ( m_nsec == rhs.m_nsec ) );
	}

	bool operator!=( const TimeSpec64& rhs ) const
	{
		return ( ( m_sec != rhs.m_sec ) || ( m_nsec != rhs.m_nsec ) );
	}

	bool operator<( const TimeSpec64& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec < rhs.m_nsec );
		}
		return( m_sec < rhs.m_sec );
	}

	bool operator>( const TimeSpec64& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec > rhs.m_nsec );
		}
		return( m_sec > rhs.m_sec );
	}

	bool operator<=( const TimeSpec64& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec <= rhs.m_nsec );
		}
		return( m_sec <= rhs.m_sec );
	}

	bool operator>=( const TimeSpec64& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec >= rhs.m_nsec );
		}
		return( m_sec >= rhs.m_sec );
	}

	TimeSpec64 operator+( double seconds ) const
	{
		double intpart;
		double fractpart = modf( seconds, &intpart );
		TimeSpec64 ts { m_sec, m_nsec };

		ts.m_nsec += static_cast< quint32 >( std::lround( fractpart * VC::G ) );
		if ( ts.m_nsec >= VC::G )
		{
			ts.m_nsec -= static_cast< quint32 >( VC::G );
			ts.m_sec  += 1;
		}

		if ( ts.m_nsec < 0 )
		{
			ts.m_nsec += static_cast< quint32 >( VC::G );
			ts.m_sec  -= 1;
		}

		ts.m_sec += std::lround( intpart );

		return( ts );
	} // +

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, TimeSpec64 value );
	friend QDataStream& operator>>( QDataStream& ds, TimeSpec64& value );
	friend QDebug operator<<( QDebug dbg, TimeSpec64 value );
	#endif

private:
	qint64 m_sec  { INT64_MAX }; //!< Секунды { с }
	qint32 m_nsec { INT32_MAX }; //!< Наносекунды { нс }
}; // class TimeSpec64

#pragma pack(pop)

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/timespec64.hpp>
#endif

static_assert( sizeof( veer::types::common::TimeSpec64 ) == 12,
               "Invalid size of class veer::types::common::TimeSpec64" );


#endif // ifndef VEER_TYPES_COMMON_TIMESPEC64_HPP_
