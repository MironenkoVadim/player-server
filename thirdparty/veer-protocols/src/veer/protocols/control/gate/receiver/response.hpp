#ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_RESPONSE_HPP_

#pragma once

#include <veer/protocols/control/gate/header.hpp>


namespace veer::protocols::control::gate::receiver {

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
	qint8 b001() const { return( static_cast< qint8 >( m_b001 ) ); }
	void setB001( qint8 b001 ){ m_b001 = b001; }
	qint8 b0021() const { return( static_cast< qint8 >( m_b0021 ) ); }
	void setB0021( qint8 b0021 ){ m_b0021 = b0021; }
	qint8 b0022() const { return( static_cast< qint8 >( m_b0022 ) ); }
	void setB0022( qint8 b0022 ){ m_b0022 = b0022; }
	qint8 b0031() const { return( static_cast< qint8 >( m_b0031 ) ); }
	void setB0031( qint8 b0031 ){ m_b0031 = b0031; }
	qint8 b0032() const { return( static_cast< qint8 >( m_b0032 ) ); }
	void setB0032( qint8 b0032 ){ m_b0032 = b0032; }
	qint8 b0033() const { return( static_cast< qint8 >( m_b0033 ) ); }
	void setB0033( qint8 b0033 ){ m_b0033 = b0033; }
	qint8 b0034() const { return( static_cast< qint8 >( m_b0034 ) ); }
	void setB0034( qint8 b0034 ){ m_b0034 = b0034; }
	qint8 b0035() const { return( static_cast< qint8 >( m_b0035 ) ); }
	void setB0035( qint8 b0035 ){ m_b0035 = b0035; }
	qint8 b0036() const { return( static_cast< qint8 >( m_b0036 ) ); }
	void setB0036( qint8 b0036 ){ m_b0036 = b0036; }
	qint8 b004() const { return( static_cast< qint8 >( m_b004 ) ); }
	void setB004( qint8 b004 ){ m_b004 = b004; }
	qint8 b0051() const { return( static_cast< qint8 >( m_b0051 ) ); }
	void setB0051( qint8 b0051 ){ m_b0051 = b0051; }
	qint8 b0052() const { return( static_cast< qint8 >( m_b0052 ) ); }
	void setB0052( qint8 b0052 ){ m_b0052 = b0052; }
	qint8 b006() const { return( static_cast< qint8 >( m_b006 ) ); }
	void setB006( qint8 b006 ){ m_b006 = b006; }
	qint8 additionalAntenna() const { return( static_cast< qint8 >( m_additionalAntenna ) ); }
	void setAdditionalAntenna( qint8 additionalAntenna ){ m_additionalAntenna = additionalAntenna; }
	qint64 mainAntenna() const { return( static_cast< qint64 >( m_mainAntenna ) ); }
	void setMainAntenna( qint64 mainAntenna ){ m_mainAntenna = mainAntenna; }
private:
	qint8  m_state;
	qint8  m_mode;
	qint8  m_b001;
	qint8  m_b0021;
	qint8  m_b0022;
	qint8  m_b0031;
	qint8  m_b0032;
	qint8  m_b0033;
	qint8  m_b0034;
	qint8  m_b0035;
	qint8  m_b0036;
	qint8  m_b004;
	qint8  m_b0051;
	qint8  m_b0052;
	qint8  m_b006;
	qint8  m_additionalAntenna;
	qint64 m_mainAntenna;
}; // class Response

#pragma pack(pop)

} // namespace veer::protocols::control::gate::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/gate/receiver/qt/response.hpp>
#endif

static_assert( sizeof( veer::protocols::control::gate::receiver::Response ) == 24,
               "Invalid size of class veer::protocols::control::receiver::Response" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_RESPONSE_HPP_
