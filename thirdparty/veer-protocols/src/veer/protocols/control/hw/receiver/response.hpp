#ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_HW_RECEIVER_RESPONSE_HPP_

#pragma once


namespace veer::protocols::control::hw::receiver {

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

} // namespace veer::protocols::control::hw::receiver
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/hw/receiver/qt/response.hpp>
#endif

static_assert( sizeof( veer::protocols::control::hw::receiver::Response ) == 24,
               "Invalid size of class veer::protocols::control::receiver::Response" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_RESPONSE_HPP_
