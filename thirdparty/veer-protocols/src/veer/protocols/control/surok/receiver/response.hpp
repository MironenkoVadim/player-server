#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_RESPONSE_HPP_

#pragma once

#include <endian.h>
#include <veer/common/config.hpp>

namespace veer::protocols::control::surok::receiver {

#pragma pack(push, 1)


class Response
{
public:
	quint8 code() const { return( m_code ); }

	quint8 b0031() const { return( m_s1.b0031 ); }
	quint8 b0032() const { return( m_s1.b0032 ); }
	quint8 b0033() const { return( m_s1.b0033 ); }
	quint8 b0034() const { return( m_s1.b0034 ); }
	quint8 b0035() const { return( m_s1.b0035 ); }
	quint8 b0036() const { return( m_s1.b0036 ); }
	quint8 b002() const { return( m_s1.b002 ); }
	quint8 bus() const { return( m_s1.bus ); }

	quint8 ch1() const { return( m_s2.ch1 ); }
	quint8 ch2() const { return( m_s2.ch2 ); }
	quint8 ch3() const { return( m_s2.ch3 ); }
	quint8 ch4() const { return( m_s2.ch4 ); }
	quint8 ch5() const { return( m_s2.ch5 ); }
	quint8 ch6() const { return( m_s2.ch6 ); }
	quint8 ch7() const { return( m_s2.ch7 ); }
	quint8 ch8() const { return( m_s2.ch8 ); }

	quint8 ch9() const { return( m_s3.ch9 ); }
	quint8 ch10() const { return( m_s3.ch10 ); }
	quint8 ch11() const { return( m_s3.ch11 ); }
	quint8 ch12() const { return( m_s3.ch12 ); }
	quint8 gen() const { return( m_s3.gen ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, Response value );
	friend QDataStream& operator>>( QDataStream& ds, Response& value );
	friend QDebug operator<<( QDebug dbg, const Response value );
	#endif

private:
	quint8 m_code;
	union
	{
		quint8 m_state1;
		struct
		{
			unsigned b0031 : 1;
			unsigned b0032 : 1;
			unsigned b0033 : 1;
			unsigned b0034 : 1;
			unsigned b0035 : 1;
			unsigned b0036 : 1;
			unsigned b002  : 1;
			unsigned bus   : 1;
		} m_s1;
	};
	union
	{
		quint8 m_state2;
		struct
		{
			unsigned ch1 : 1;
			unsigned ch2 : 1;
			unsigned ch3 : 1;
			unsigned ch4 : 1;
			unsigned ch5 : 1;
			unsigned ch6 : 1;
			unsigned ch7 : 1;
			unsigned ch8 : 1;
		} m_s2;
	};
	union
	{
		quint8 m_state3;
		struct
		{
			unsigned ch9     : 1;
			unsigned ch10    : 1;
			unsigned ch11    : 1;
			unsigned ch12    : 1;
			unsigned gen     : 1;
			unsigned reserve : 3;
		} m_s3;
	};
}; // class Response

#pragma pack(pop)

} // namespace veer::protocols::control::surok::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/receiver/qt/response.hpp>
#endif

static_assert( sizeof( veer::protocols::control::surok::receiver::Response ) == 4,
               "Invalid size of class veer::protocols::control::receiver::Response" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_RESPONSE_HPP_
