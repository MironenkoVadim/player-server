#ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_HW_RECEIVER_COMMAND_HPP_

#pragma once

#include <veer/common/enum_bitmask_operations.hpp>
#include <veer/types/common/timespec32.hpp>

namespace veer::protocols::control::hw::receiver {

//namespace VC  = veer::common;
//namespace VTC = veer::types::common;

#pragma pack(push, 1)


/*!
 * \brief Режим работы приёмника
 */
enum class Mode : qint16
{
	Stop     = 0,           //!< Останов
	FC       = 1,           //!< Функциональный контроль
	ADC      = 2,           //!< Обнаружение
	Input    = 3,           //!< Управление входом приёмных каналов
	Imitator = 4,           //!< Управление имитаторами
	Amp      = 5,           //!< Управление усилителем мощности
};


enum class Flags : quint16
{
	Vio        = 0x0001,    //!< ВИО включено
	Afc        = 0x0002,    //!< Амплитудно-фазовая коррекция
	Imitator   = 0x0008,    //!< Имитационный сигнал
	ZS1        = 0x0010,    //!< Излучение зондирующего сигнала 1
	ZS2        = 0x0020,    //!< Излучение зондирующего сигнала 2
	Antenna    = 0x0040,    //!< Подключение антенны
	PcOutput   = 0x0080,    //!< Выход на ВК
	OutputSink = 0x0100,    //!< Выход: 0 - Ethernet, 1 - USB
	ZSBlock    = 0x0200,    //!< Блокировка на время излучения
	SingleFreq = 0x0400,    //!< Одночастотный режим
	Sync1KHz   = 0x0800     //!< Привязка к 1 КГц
};


enum class FCMode : quint8
{
	Enable     = 0x00,
	Periodic   = 0x01,
	ModeSwitch = 0x02,
	aaa        = 0x04
};


class Command
{
public:
	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Command& value );
	friend QDataStream& operator>>( QDataStream& ds, Command& value );
	#endif

private:
	Mode    m_mode;         //!< Номер режима
	Flags   m_flags;        //!< Флаги режимов
	quint16 m_period;       //!< Период повторения
	quint16 m_attenuator;   //!< Аттенюатор
	quint16 m_zs1Freq;      //!< Рабочая частота ЗС 1
	quint16 m_zs1Time;      //!< Длительность ЗС 1
	quint16 m_zs1Dev;       //!< Девиация ЗС 1
	quint16 m_zs1Zone;      //!< Рабочая зона 1 частотного канала (кол-во каналов дальности)
	quint16 m_zs1Shift;     //!< Сдвиг рабочей частоты 1 частотного канала (кол-во каналов дальности)
	quint16 m_zs2Freq;      //!< Рабочая частота ЗС 2
	quint16 m_zs2Time;      //!< Длительность ЗС 2
	quint16 m_zs2Dev;       //!< Девиация ЗС 2
	quint16 m_zs2Zone;      //!< Рабочая зона 2 частотного канала (кол-во каналов дальности)
	quint16 m_zs2Shift;     //!< Сдвиг рабочей частоты 2 частотного канала (кол-во каналов дальности)
	quint16 m_zsPause;      //!< Пауза между стробами ЗС 1 и ЗС 2 (мкс)
	quint16 m_zsStrobPause; //!< Задержка ЗС относительно начала строба (мкс)
	quint16 m_bandwidth;    //!< Полоса пропускания (100, 200, 300, 400, 500)
	quint16 m_stub1;
	quint16 m_imr;
	quint16 m_imFreq;       //!< Рабочая частота имитатора
	quint16 m_imAttenuator; //!< Ослабление
	quint16 m_imDelay;      //!< Задержка
	quint16 m_imZS;         //!< Параметры ЗС 1 или ЗС 2
	quint16 m_stub2;
	quint16 m_stub3;
}; // class Command

#pragma pack(pop)

} // namespace veer::protocols::control::hw::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/hw/receiver/qt/command.hpp>
#endif

ENABLE_BITMASK_OPERATORS( veer::protocols::control::hw::receiver::Flags )

static_assert( sizeof( veer::protocols::control::hw::receiver::Command ) == 50,
               "Invalid size of struct veer::protocols::control::hw::receiver::Command" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_HW_RECEIVER_COMMAND_HPP_
