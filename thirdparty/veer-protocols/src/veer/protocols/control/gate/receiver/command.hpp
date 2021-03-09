#ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_COMMAND_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/control/gate/header.hpp>
#include <veer/types/common/timespecns.hpp>

namespace veer::protocols::control::gate::receiver {

namespace VC  = veer::common;
namespace VTC = veer::types::common;

#pragma pack(push, 1)


enum class Mode : qint8
{
	Stop = 0,
	FC   = 1,
	ADC  = 2,
	Amp  = 5,
};


enum class Flags : quint16
{
	Unset        = 0x0000,
	Vio          = 0x0001,          // ВИО включено
	Afc          = 0x0002,          // Амплитудно-фазовая коррекция
	Calib        = 0x0004,          // Калибровочный интервал
	ImitKey      = 0x0008,          // Управление ключом на входе
	AntKey       = 0x0010,          // Управление ключом на входе
	ZSOutput     = 0x0040,          // Выход ЗС
	UbsOutput    = 0x0080,
	EthOutput    = 0x0100,
	ZSBlock      = 0x0200,
	Sync         = 0x0800,
	SignalOutput = 0x1000,
	Attenuator   = 0x4000,
	DigitalKey   = 0x8000
};


enum class FCMode : quint8
{
	Enable     = 0x00,
	Periodic   = 0x01,
	ModeSwitch = 0x02,
	Aaa        = 0x04
};


class Command
{
public:
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, Command value );
	friend QDataStream& operator>>( QDataStream& ds, Command& value );
	friend QDataStream& operator<<( QDataStream& ds, Mode value );
	friend QDataStream& operator>>( QDataStream& ds, Mode& value );
	friend QDataStream& operator<<( QDataStream& ds, Flags value );
	friend QDataStream& operator>>( QDataStream& ds, Flags& value );
	friend QDataStream& operator<<( QDataStream& ds, FCMode value );
	friend QDataStream& operator>>( QDataStream& ds, FCMode& value );
	#endif

	quint16 id() const { return( static_cast< quint16 >( m_id ) ); }
	void setId( quint16 id ){ m_id = id; }
	VTC::TimeSpecNs time() const { return( m_time ); }
	void setTime( VTC::TimeSpecNs time ){ m_time = time; }
	Mode mode() const { return( m_mode ); }
	void setMode( Mode mode ){ m_mode = mode; }
	Flags flags() const { return( m_flags ); }
	void setFlags( Flags flags ){ m_flags = flags; }
	FCMode fcMode() const { return( m_fcMode ); }
	void setFcMode( FCMode fcMode ){ m_fcMode = fcMode; }
	quint32 period() const { return( static_cast< quint32 >( m_period ) ); }
	void setPeriod( quint32 period ){ m_period = period; }
	quint8 spectr() const { return( static_cast< quint8 >( m_spectr ) ); }
	void setSpectr( quint8 spectr ){ m_spectr = spectr; }
	quint8 zsCount() const { return( static_cast< quint8 >( m_zsCount ) ); }
	void setZsCount( quint8 zsCount ){ m_zsCount = zsCount; }
	quint8 recvCount() const { return( static_cast< quint8 >( m_recvCount ) ); }
	void setRecvCount( quint8 recvCount ){ m_recvCount = recvCount; }
	quint8 isCount() const { return( static_cast< quint8 >( m_isCount ) ); }
	void setIsCount( quint8 isCount ){ m_isCount = isCount; }
	quint32 calibrTime() const { return( static_cast< quint32 >( m_calibrTime ) ); }
	void setCalibrTime( quint32& calibrTime ){ m_calibrTime = calibrTime; }

private:
	quint16         m_id { 0 };     //!< Идентификатор управления: 0 – код покоя; 10..65535
	VTC::TimeSpecNs m_time;
	Mode            m_mode { Mode::Stop };
	Flags           m_flags { Flags::Unset };
	FCMode          m_fcMode { FCMode::Enable };
	quint32         m_period { 0 };
	quint8          m_spectr { 0 }; // 0 - нормальный режим чтения данных по UART;
	// 1...N – номер канала дальности
	quint8  m_zsCount { 0 };
	quint8  m_recvCount { 0 };
	quint8  m_isCount { 0 };
	quint32 m_calibrTime { 0 };
}; // class Command

// class Command

#pragma pack(pop)

} // namespace veer::protocols::control::gate::receiver


#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/gate/receiver/qt/command.hpp>
#endif

static_assert( sizeof( veer::protocols::control::gate::receiver::Command ) == 26,
               "Invalid size of struct veer::protocols::control::gate::receiver::Command" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_RECEIVER_COMMAND_HPP_
