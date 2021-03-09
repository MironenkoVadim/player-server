#ifndef VEER_TYPES_COMMON_TIMESPEC32_HPP_
#define VEER_TYPES_COMMON_TIMESPEC32_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/const.hpp>

#include <cmath>
#include <ctime>

#include <sys/time.h>

namespace VC = veer::common;

namespace veer::types::common {

#pragma pack(push, 1)

class TimeSpec32
{
public:
	TimeSpec32()
	{
		struct timeval tv {0, 0};
		gettimeofday( &tv, nullptr );
		fromTimeval( tv );
	}

	explicit TimeSpec32( const struct timeval value ) noexcept { fromTimeval( value ); }
	explicit TimeSpec32( const struct timespec value ) noexcept { fromTimespec( value ); }
	explicit TimeSpec32( const qint32 sec, const qint32 nsec ) noexcept :
		m_sec ( sec ),
		m_nsec( nsec ) {}
	explicit TimeSpec32( const qint32 sec, const qint64 nsec ) noexcept :
		m_sec ( sec ),
		m_nsec( static_cast< qint32 >( nsec ) ) {}

	qint32 seconds() const { return( m_sec ); }
	void setSeconds( const qint32 value ) { m_sec = value; }
	qint32 nanoseconds() const { return ( m_nsec ); }
	void setNanoseconds( const qint32 value ) { m_nsec = value; }

	void fromTimeval( const struct timeval value )
	{
		m_sec  = static_cast< qint32 >( value.tv_sec );
		m_nsec = static_cast< qint32 >( value.tv_usec * VC::K );
	}

	struct timeval toTimeval() const
	{
		struct timeval tv {m_sec, m_nsec / VC::K};
		return( tv );
	}

	void fromTimespec( const struct timespec val )
	{
		m_sec  = static_cast< quint32 >( val.tv_sec );
		m_nsec = static_cast< qint32 >( val.tv_nsec );
	}

	struct timespec toTimespec() const
	{
		struct timespec ts {m_sec, m_nsec};
		return( ts );
	}

	bool operator==( const TimeSpec32& rhs ) const
	{
		return ( ( m_sec == rhs.m_sec ) && ( m_nsec == rhs.m_nsec ) );
	}

	bool operator!=( const TimeSpec32& rhs ) const
	{
		return ( ( m_sec != rhs.m_sec ) || ( m_nsec != rhs.m_nsec ) );
	}

	bool operator<( const TimeSpec32& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec < rhs.m_nsec );
		}
		return( m_sec < rhs.m_sec );
	}

	bool operator<=( const TimeSpec32& rhs ) const
	{
		if ( m_sec == rhs.m_sec )
		{
			return( m_nsec <= rhs.m_nsec );
		}
		return( m_sec <= rhs.m_sec );
	}

	TimeSpec32 operator+( double seconds ) const
	{
		double intpart;
		double fractpart = modf( seconds, &intpart );
		TimeSpec32 ts { m_sec, m_nsec };

		ts.m_nsec += std::lround( fractpart * VC::G );
		if ( ts.m_nsec >= VC::G )
		{
			ts.m_nsec -= VC::G;
			ts.m_sec  += 1;
		}

		if ( ts.m_nsec < 0 )
		{
			ts.m_nsec += VC::G;
			ts.m_sec  -= 1;
		}

		ts.m_sec += std::lround( intpart );

		return( ts );
	} // +

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, TimeSpec32 value );
	friend QDataStream& operator>>( QDataStream& ds, TimeSpec32& value );
	friend QDebug operator<<( QDebug dbg, TimeSpec32 value );
	#endif

private:
	qint32 m_sec  { INT32_MAX }; //!< Секунды { с }
	qint32 m_nsec { INT32_MAX }; //!< Наносекунды { нс }
}; // class TimeSpec32

#pragma pack(pop)

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/timespec32.hpp>
#endif

static_assert( sizeof( veer::types::common::TimeSpec32 ) == 8,
               "Invalid size of class veer::types::common::TimeSpec32" );

#endif // ifndef VEER_TYPES_COMMON_TIMESPEC32_HPP_
