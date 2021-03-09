#ifndef VEER_TYPES_RADAR_SUROK_COMMON_HPP_
#define VEER_TYPES_RADAR_SUROK_COMMON_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/enum_bitmask_operations.hpp>

namespace veer::types::radar::surok {

#pragma pack(push, 1)

class ControlFlags
{
public:
	ControlFlags()
	{
		off();
		enableManualControl();
		enableTemperatureReset();
		enableVoltageReset();
		enableStrob1Reset();
		enableStrob2Reset();
	}

	bool serialControl() const __attribute__( ( warn_unused_result ) ) { return( m_bf.serialControl ); }
	void enableSerialControl() { m_bf.serialControl = true; m_bf.manualControl = false; }
	void disableSerialControl() { m_bf.serialControl = false; m_bf.manualControl = true; }

	bool manualControl() const { return( m_bf.manualControl ); }
	void enableManualControl() { m_bf.manualControl = true; m_bf.serialControl = false; }
	void disableManualControl() { m_bf.manualControl = false; m_bf.serialControl = true; }

	bool workMode() const { return ( m_bf.on ); }
	void on() { m_bf.on = true; m_bf.off = false; }
	void off() { m_bf.off = true; m_bf.on = false; }

	bool temperatureReset() const { return( m_bf.temperatureReset ); }
	void enableTemperatureReset() { m_bf.temperatureReset = true; }
	void disableTemperatureReset() { m_bf.temperatureReset = false; }

	bool voltageReset() const { return( m_bf.voltageReset ); }
	void enableVoltageReset() { m_bf.voltageReset = true; }
	void disableVoltageReset() { m_bf.voltageReset = false; }

	bool strob1Reset() const { return( m_bf.strob1Reset ); }
	void enableStrob1Reset() { m_bf.strob1Reset = true; }
	void disableStrob1Reset() { m_bf.strob1Reset = false; }

	bool strob2Reset() const { return( m_bf.strob2Reset ); }
	void enableStrob2Reset() { m_bf.strob2Reset = true; }
	void disableStrob2Reset() { m_bf.strob2Reset = false; }

	quint8 value() const { return ( m_value ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, ControlFlags value );
	friend QDataStream& operator>>( QDataStream& ds, ControlFlags& value );
	friend QDebug operator<<( QDebug dbg, ControlFlags value );
	#endif

private:
	union
	{
		quint8 m_value { 0 };
		struct
		{
			#ifdef LITTLE_ENDIAN
			bool serialControl    : 1; //!< Включение режима управления по последовательному порту
			bool manualControl    : 1; //!< Включение режима местного управления
			bool on               : 1; //!< Включение усилителя
			bool off              : 1; //!< Выключение усилителя
			bool temperatureReset : 1; //!< Сброс датчика температуры
			bool voltageReset     : 1; //!< Сброс датчика напряжения
			bool strob1Reset      : 1; //!< Сброс 1 строба
			bool strob2Reset      : 1; //!< Сброс 2 строба
			#endif
		} m_bf;
	};
}; // class ControlFlags


class ChannelFlags
{
public:
	ChannelFlags()
	{
		setBlock1( true );
		setBlock2( true );
		setBlock3( true );
		setBlock4( true );
		setAntenna1( false );
		setAntenna2( false );
		setAntenna3( false );
		setAntenna4( false );
	}

	bool block1() const { return( m_bf.block1 ); }
	void setBlock1( bool value ) { m_bf.block1 = value; }

	bool block2() const { return( m_bf.block2 ); }
	void setBlock2( bool value ) { m_bf.block2 = value; }

	bool block3() const { return( m_bf.block3 ); }
	void setBlock3( bool value ) { m_bf.block3 = value; }

	bool block4() const { return( m_bf.block4 ); }
	void setBlock4( bool value ) { m_bf.block4 = value; }

	bool antenna1() const { return( m_bf.antenna1 ); }
	void setAntenna1( bool value ) { m_bf.antenna1 = value; }

	bool antenna2() const { return( m_bf.antenna2 ); }
	void setAntenna2( bool value ) { m_bf.antenna2 = value; }

	bool antenna3() const { return( m_bf.antenna3 ); }
	void setAntenna3( bool value ) { m_bf.antenna3 = value; }

	bool antenna4() const { return( m_bf.antenna4 ); }
	void setAntenna4( bool value ) { m_bf.antenna4 = value; }

	quint8 value() const { return ( m_value ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, ChannelFlags value );
	friend QDataStream& operator>>( QDataStream& ds, ChannelFlags& value );
	friend QDebug operator<<( QDebug dbg, ChannelFlags value );
	#endif

private:
	union
	{
		quint8 m_value { 0 };
		struct
		{
			#ifdef LITTLE_ENDIAN
			bool block1   : 1; //!< Блокировка излучения в 1 канале
			bool block2   : 1; //!< Блокировка излучения во 2 канале
			bool block3   : 1; //!< Блокировка излучения в 3 канале
			bool block4   : 1; //!< Блокировка излучения в 4 канале
			bool antenna1 : 1; //!< Излучение в 1 канале на антенну или на эквивалент
			bool antenna2 : 1; //!< Излучение во 2 канале на антенну или на эквивалент
			bool antenna3 : 1; //!< Излучение в 3 канале на антенну или на эквивалент
			bool antenna4 : 1; //!< Излучение в 4 канале на антенну или на эквивалент
			#endif
		} m_bf;
	};
}; // class ChannelFlags

#pragma pack(pop)

} // namespace veer::types::radar::surok

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/radar/surok/qt/common.hpp>
#endif

// Обязательно в глобальной области видимости
ENABLE_BITMASK_OPERATORS( veer::types::radar::surok::ControlFlags )
ENABLE_BITMASK_OPERATORS( veer::types::radar::surok::ChannelFlags )

#endif // ifndef VEER_TYPES_RADAR_SUROK_COMMON_HPP_
