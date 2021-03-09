#ifndef VEER_TYPES_COMMON_TIMESPECNS_HPP_
#define VEER_TYPES_COMMON_TIMESPECBS_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/const.hpp>

#include <cmath>
#include <ctime>

#include <sys/time.h>

namespace VC = veer::common;

namespace veer::types::common {

#pragma pack(push, 1)

class TimeSpecNs
{
public:
	TimeSpecNs()
	{
		struct timeval tv {0, 0};
		gettimeofday( &tv, nullptr );
		fromTimeval( tv );
	}

	explicit TimeSpecNs( const struct timeval value ) noexcept { fromTimeval( value ); }
	explicit TimeSpecNs( const struct timespec value ) noexcept { fromTimespec( value ); }
	explicit TimeSpecNs( const qint64 sec, const qint64 nsec ) noexcept :
		m_nsec( sec * VC::G + nsec ) {}
	explicit TimeSpecNs( const qint32 sec, const qint64 nsec ) noexcept :
		m_nsec( sec * VC::G + nsec ) {}
	explicit TimeSpecNs( const qint64 nsec ) noexcept :
		m_nsec( nsec ) {}

	qint64 seconds() const { return( m_nsec / VC::G ); }
	void setSeconds( const qint64 value ) { auto ns = nanoseconds(); m_nsec = value * VC::G + ns; }
	qint64 nanoseconds() const { return ( m_nsec % VC::G ); }
	void setNanoseconds( const qint64 value ) { auto s = seconds(); m_nsec = s * VC::G + value; }

	void fromTimeval( const struct timeval value )
	{
		m_nsec = value.tv_sec * VC::G + value.tv_usec * VC::K;
	}

	struct timeval toTimeval() const
	{
		struct timeval tv {m_nsec / VC::G, ( m_nsec / VC::K ) % VC::M};
		return( tv );
	}

	void fromTimespec( const struct timespec val )
	{
		m_nsec = val.tv_sec * VC::G + val.tv_nsec;
	}

	struct timespec toTimespec() const
	{
		struct timespec ts {m_nsec / VC::G, m_nsec % VC::G};
		return( ts );
	}

	bool operator==( const TimeSpecNs& rhs ) const
	{
		return ( m_nsec == rhs.m_nsec );
	}

	bool operator!=( const TimeSpecNs& rhs ) const
	{
		return ( m_nsec != rhs.m_nsec );
	}

	bool operator<( const TimeSpecNs& rhs ) const
	{
		return( m_nsec < rhs.m_nsec );
	}

	bool operator<=( const TimeSpecNs& rhs ) const
	{
		return( m_nsec <= rhs.m_nsec );
	}

	TimeSpecNs operator+( double seconds ) const
	{
		double intpart;
		double fractpart = modf( seconds, &intpart );

		TimeSpecNs ts { m_nsec };
		ts.m_nsec += intpart * VC::G + fractpart;
		return( ts );
	} // +

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, TimeSpecNs value );
	friend QDataStream& operator>>( QDataStream& ds, TimeSpecNs& value );
	friend QDebug operator<<( QDebug dbg, TimeSpecNs value );
	#endif

private:
	qint64 m_nsec { INT64_MAX }; //!< Наносекунды относительно 00:00:00 1 января 1970 года { нс }
}; // class TimeSpecNs

#pragma pack(pop)

} // namespace veer::types::common

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/common/qt/timespecns.hpp>
#endif

static_assert( sizeof( veer::types::common::TimeSpecNs ) == 8,
               "Invalid size of class veer::types::common::TimeSpecNs" );

#endif // ifndef VEER_TYPES_COMMON_TIMESPECNS_HPP_
