#ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_COMMAND_HPP_

#pragma once

#include <veer/protocols/control/gate/header.hpp>


namespace veer::protocols::control::gate::amplifier {

namespace VC  = veer::common;
namespace VTC = veer::types::common;

#pragma pack(push, 1)


class Command
{
public:
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Command& value );
	friend QDataStream& operator>>( QDataStream& ds, Command& value );
	#endif

	quint16 id() const { return( static_cast< quint16 >( m_id ) ); }
	void setId( quint16 id ) { m_id = id; }
	qint32 sec() const { return( static_cast< qint32 >( m_sec ) ); }
	void setSec( qint32 sec ) { m_sec = sec; }
	qint32 nsec() const { return( static_cast< qint32 >( m_nsec ) ); }
	void setNsec( qint32 nsec ){ m_nsec = nsec; }
	quint32 period() const { return( static_cast< qint32 >( m_period ) ); }
	void setPeriod( quint32 period ){ m_period = period; }
	quint8 spectr() const { return( static_cast< quint8 >( m_spectr ) ); }
	void setSpectr( quint8 spectr ){ m_spectr = spectr; }
	quint8 zsCount() const { return( static_cast< quint8 >( m_zsCount ) ); }
	void setZsCount( quint8 zsCount ){ m_zsCount = zsCount; }
	quint8 recvCount() const { return( static_cast< quint8 >( m_recvCount ) ); }
	void setRecvCount( quint8 recvCount ){ m_recvCount = recvCount; }
	quint8 isCount() const { return( static_cast< quint8 >( m_isCount ) ); }
	void setIsCount( quint8 isCount ){ m_isCount = isCount; }
	quint32 calibrTime() const { return( static_cast< quint8 >( m_calibrTime ) ); }
	void setCalibrTime( quint32 calibrTime ){ m_calibrTime = calibrTime; }

private:
	quint16 m_id;
	qint32  m_sec;
	qint32  m_nsec;
	quint32 m_period;
	quint8  m_spectr; // 0 - нормальный режим чтения данных по UART;
	                  // 1...N – номер канала дальности
	quint8  m_zsCount;
	quint8  m_recvCount;
	quint8  m_isCount;
	quint32 m_calibrTime;
}; // class Command

#pragma pack(pop)

} // namespace veer::protocols::control::gate::amplifier

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/gate/amplifier/qt/command.hpp>
#endif

//static_assert( sizeof( veer::protocols::preproc::Mark ) == 48,
//               "Invalid size of struct veer::protocols::preproc::Mark" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_AMPLIFIER_COMMAND_HPP_
