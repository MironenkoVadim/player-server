#ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_RESPONSE_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_RESPONSE_HPP_

#pragma once

#include <endian.h>

#include <array>
#include <veer/common/config.hpp>

namespace veer::protocols::control::surok::amplifier {

namespace VPCSA = veer::protocols::control::surok::amplifier;

#pragma pack(push, 1)


class ChannelResponse
{
public:
	quint8 blockingState() const { return( m_s1.blockingState ); }
	quint8 dummyEmission() const { return( m_s1.dummyEmission ); }
	quint8 emissionState() const { return( m_s1.emissionState ); }
	quint8 powerState() const { return( m_s1.powerState ); }
	quint8 temperatureState() const { return( m_s1.temperatureState ); }

	quint8 swr1State() const { return( m_s2.swr1State ); }
	quint8 swr2State() const { return( m_s2.swr2State ); }
	quint8 u48State() const { return( m_s2.u48State ); }
	quint8 emissionChannelState() const { return( m_s2.emissionChannelState ); }
	quint8 zsState() const { return( m_s2.zsState ); }
	quint8 u12State() const { return( m_s2.u12State ); }

	quint8 power1() const { return( m_power1 ); }
	quint8 power2() const { return( m_power2 ); }
	quint8 swr1() const { return( m_swr1 ); }
	quint8 swr2() const { return( m_swr2 ); }
	quint8 phase1() const { return( m_phase1 ); }
	quint8 phase2() const { return( m_phase2 ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const ChannelResponse& value );
	friend QDataStream& operator>>( QDataStream& ds, ChannelResponse& value );
	friend QDebug operator<<( QDebug dbg, ChannelResponse value );
	#endif

private:
	union
	{
		quint8 m_state1;
		struct
		{
			unsigned blockingState    : 1;     //!< Блокировка канала
			unsigned dummyEmission    : 1;     //!< Излучение на эквивалент (dummy antenna)
			unsigned emissionState    : 1;     //!< Состояние излучения
			unsigned powerState       : 2;     //!< Состояние мощности
			unsigned temperatureState : 2;     //!< Состояние температуры
			unsigned bit7             : 1;     //!< Не используется
		} m_s1;
	};

	union
	{
		quint8 m_state2;
		struct
		{
			unsigned swr1State            : 2; //!< Состояние КСВ1 (standing wave ratio)
			unsigned swr2State            : 2; //!< Состояние КСВ2
			unsigned u48State             : 1; //!< Состояние блока 48В
			unsigned emissionChannelState : 1; //!< Состояние канала излучения
			unsigned zsState              : 1; //!< Состояние зондирующего сигнала
			unsigned u12State             : 1; //!< Состояние блока 12В
		} m_s2;
	};

	quint8 m_power1; //!< Мощность первого импульса
	quint8 m_power2; //!< Мощность второго импульса
	quint8 m_swr1;   //!< КСВ первого импульса
	quint8 m_swr2;   //!< КСВ второго импульса
	quint8 m_phase1; //!< Фаза первого импульса
	quint8 m_phase2; //!< Фаза второго импульса
}; // class ChannelResponse

using Channels = std::array< ChannelResponse, 4 >;


class Response
{
public:
	quint8 startMarker() const { return ( m_startMarker ); }
	bool isStartMarkerValid() const { return ( m_startMarker == C::StartMarker ); }

	quint8 endMarker() const { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::EndMarker ); }

	quint16 crc() const { return ( m_crc ); }
	bool isCrcValid() const { return ( m_crc == calcCrc() ); }

	bool remoteControl() const { return( m_c.remoteControl ); }
	bool localControl() const { return( m_c.localControl ); }
	bool on() const { return( m_c.on ); }
	bool off() const { return( m_c.off ); }
	bool f1Changed() const { return( m_c.f1Changed ); }
	bool f2Changed() const { return( m_c.f2Changed ); }

	quint8 uPowerState() const { return( m_s.uPowerState ); }
	quint8 uCMState() const { return( m_s.uCMState ); }
	quint8 zsState() const { return( m_s.zsState ); }
	quint8 u4CMState() const { return( m_s.u4CMState ); }
	quint8 u4CMB003State() const { return( m_s.u4CMB003State ); }

	inline Channels& channels()                  { return ( m_channels ); }
	inline const Channels& constChannels() const { return ( m_channels ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Response& value );
	friend QDataStream& operator>>( QDataStream& ds, Response& value );
	friend QDebug operator<<( QDebug dbg, Response value );
	#endif

private:
	quint8 m_startMarker;

	union
	{
		quint8 m_control;
		struct
		{
			unsigned remoteControl : 1; //!< Удаленное управление
			unsigned localControl  : 1; //!< Местное управление
			unsigned on            : 1; //!< Передатчик включен
			unsigned off           : 1; //!< Передатчик выключен
			unsigned f1Changed     : 1; //!< Изменение частоты первого импульса
			unsigned f2Changed     : 1; //!< Изменение частоты второго импульса
			unsigned bit6          : 1; //!< Не используется
			unsigned bit7          : 1; //!< Не используется
		} m_c;
	};

	union
	{
		quint8 m_state;
		struct
		{
			unsigned uPowerState   : 1; //!< Состояние усилителя мощности
			unsigned uCMState      : 1; //!< Состояние блока CM
			unsigned zsState       : 1; //!< Состояние зондирующего сигнала
			unsigned bit3          : 1; //!< Не используется
			unsigned u4CMState     : 1; //!< Состояние блока 4СМ
			unsigned u4CMB003State : 1; //!< Состояние блока 4СМ Б003
			unsigned bit6          : 1; //!< Не используется
			unsigned bit7          : 1; //!< Не используется
		} m_s;
	};

	Channels m_channels; //!< Каналы усиления

	quint16 m_crc;       //!< Контрольная сумма
	quint8  m_endMarker; //!< Маркер конца команды

	inline quint16 calcCrc() const
	{
		int crc             = 0;
		const quint8* array = reinterpret_cast< const quint8* >( this );
		for ( quint8 k = 1; k < sizeof( Response ) - 3; k++ )
		{
			crc += array[k];
		}
		return( static_cast< quint16 >( crc ) );
	}
}; // class Response

#pragma pack(pop)

} // namespace veer::protocols::control::surok::amplifier

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/amplifier/qt/response.hpp>
#endif

static_assert( sizeof( veer::protocols::control::surok::amplifier::Response ) == 38,
               "Invalid size of struct veer::protocols::control::amplifier::Response" );


#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_RESPONSE_HPP_
