#ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/gate/header.hpp>
#include <veer/common/config.hpp>

namespace veer::protocols::control::gate::amplifier {

namespace VC  = veer::common;
namespace VTC = veer::types::common;

#pragma pack(push, 1)


class Response
{
public:
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Response& value );
	friend QDataStream& operator>>( QDataStream& ds, Response& value );
	#endif

	qint8 state() const { return( static_cast< qint8 >( m_state ) ); }
	void setState( qint8 state ){ m_state = state; }
	qint8 mode() const { return( static_cast< qint8 >( m_mode ) ); }
	void setMode( qint8 mode ) { m_mode = mode; }
	qint8 ls() const { return( static_cast< qint8 >( m_ls ) ); }
	void setLs( qint8 ls ){ m_ls = ls; }
	qint8 b6011() const { return( static_cast< qint8 >( m_b6011 ) ); }
	void setB6011( qint8 b6011 ){ m_b6011 = b6011; }
	qint8 b6012() const { return( static_cast< qint8 >( m_b6012 ) ); }
	void setB6012( qint8 b6012 ){ m_b6012 = b6012; }
	qint8 b6013() const { return( static_cast< qint8 >( m_b6013 ) ); }
	void setB6013( qint8 b6013 ){ m_b6013 = b6013; }
	qint8 b6014() const { return( static_cast< qint8 >( m_b6014 ) ); }
	void setB6014( qint8 b6014 ){ m_b6014 = b6014; }
	qint8 b6021() const { return( static_cast< qint8 >( m_b6021 ) ); }
	void setB6021( qint8 b6021 ){ m_b6021 = b6021; }
	qint8 b6022() const { return( static_cast< qint8 >( m_b6022 ) ); }
	void setB6022( qint8 b6022 ){ m_b6022 = b6022; }
	qint8 b6023() const { return( static_cast< qint8 >( m_b6023 ) ); }
	void setB6023( qint8 b6023 ){ m_b6023 = b6023; }
	qint8 b6024() const { return( static_cast< qint8 >( m_b6024 ) ); }
	void setB6024( qint8 b6024 ){ m_b6024 = b6024; }
	qint8 b603() const { return( static_cast< qint8 >( m_b603 ) ); }
	void setB603( qint8 b603 ){ m_b603 = b603; }
	qint8 b605() const { return( static_cast< qint8 >( m_b605 ) ); }
	void setB605( qint8 b605 ){ m_b605 = b605; }
	qint8 temp1() const { return( static_cast< qint8 >( m_temp1 ) ); }
	void setTemp1( qint8 temp1 ){ m_temp1 = temp1; }
	qint8 temp2() const { return( static_cast< qint8 >( m_temp2 ) ); }
	void setTemp2( qint8 temp2 ){ m_temp2 = temp2; }
	qint8 temp3() const { return( static_cast< qint8 >( m_temp3 ) ); }
	void setTemp3( qint8 temp3 ){ m_temp3 = temp3; }
	qint8 temp4() const { return( static_cast< qint8 >( m_temp4 ) ); }
	void setTemp4( qint8 temp4 ){ m_temp4 = temp4; }
	qint8 power1() const { return( static_cast< qint8 >( m_power1 ) ); }
	void setPower1( qint8 power1 ){ m_power1 = power1; }
	qint8 power2() const { return( static_cast< qint8 >( m_power2 ) ); }
	void setPower2( qint8 power2 ){ m_power2 = power2; }
	qint8 power3() const { return( static_cast< qint8 >( m_power3 ) ); }
	void setPower3( qint8 power3 ){ m_power3 = power3; }
	qint8 power4() const { return( static_cast< qint8 >( m_power4 ) ); }
	void setPower4( qint8 power4 ){ m_power4 = power4; }
	qint8 ls1() const { return( static_cast< qint8 >( m_ls1 ) ); }
	void setLs1( qint8 ls1 ){ m_ls1 = ls1; }
	qint8 ls2() const { return( static_cast< qint8 >( m_ls2 ) ); }
	void setLs2( qint8 ls2 ){ m_ls2 = ls2; }
	qint8 ls3() const { return( static_cast< qint8 >( m_ls3 ) ); }
	void setLs3( qint8 ls3 ){ m_ls3 = ls3; }
	qint8 ls4() const { return( static_cast< qint8 >( m_ls4 ) ); }
	void setLs4( qint8 ls4 ){ m_ls4 = ls4; }
private:
	qint8 m_state;
	qint8 m_mode;
	qint8 m_ls;
	qint8 m_b6011;
	qint8 m_b6012;
	qint8 m_b6013;
	qint8 m_b6014;
	qint8 m_b6021;
	qint8 m_b6022;
	qint8 m_b6023;
	qint8 m_b6024;
	qint8 m_b603;
	qint8 m_b605;
	qint8 m_temp1;
	qint8 m_temp2;
	qint8 m_temp3;
	qint8 m_temp4;
	qint8 m_power1;
	qint8 m_power2;
	qint8 m_power3;
	qint8 m_power4;
	qint8 m_ls1;
	qint8 m_ls2;
	qint8 m_ls3;
	qint8 m_ls4;
}; // class Response

// class Response


#pragma pack(pop)

} // namespace veer::protocols::control::gate::amplifier

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/gate/amplifier/qt/response.hpp>
#endif

static_assert( sizeof( veer::protocols::control::gate::amplifier::Response ) == 25,
               "Invalid size of struct veer::protocols::control::amplifier::Response" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_RESPONSE_HPP_
