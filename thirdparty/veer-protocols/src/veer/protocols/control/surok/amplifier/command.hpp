#ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_COMMAND_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_COMMAND_HPP_

#pragma once

#include <veer/types/radar/surok/common.hpp>
#include <veer/common/config.hpp>
#include <endian.h>

namespace veer::protocols::control::surok::amplifier {

namespace VTRS = veer::types::radar::surok;

#pragma pack(push, 1)

namespace constants
{

#ifdef LITTLE_ENDIAN
constexpr quint8 StartMarker { 0x81 };
constexpr quint8 EndMarker   { 0x99 };
#endif

} // namespace constants


namespace C = constants;

class Command
{
public:
	quint8 startMarker() const { return ( m_startMarker ); }
	bool isStartMarkerValid() const { return ( m_startMarker == C::StartMarker ); }

	quint8 endMarker() const { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::EndMarker ); }

	quint8 crc() const { return ( m_crc ); }
	void updateCrc() { m_crc = calcCrc(); }
	bool isCrcValid() const { return ( m_crc == calcCrc() ); }

	VTRS::ControlFlags& controlFlags() __attribute__( ( warn_unused_result ) ) { return( m_controlFlags ); }
	void setControlFlags( VTRS::ControlFlags value ) { m_controlFlags = value; }

	VTRS::ChannelFlags& channelFlags() __attribute__( ( warn_unused_result ) )  { return( m_channelFlags ); }
	void setChannelFlags( VTRS::ChannelFlags value ) { m_channelFlags = value; }

	quint8 counter() const { return( m_bf.counter ); }
	void setCounter( quint8 value ) { m_bf.counter = value & 0xF; }

	quint8 pattern() const { return( m_bf.pattern ); }
	void setPattern( quint8 value ) { m_bf.pattern = value & 0xF; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Command& value );
	friend QDataStream& operator>>( QDataStream& ds, Command& value );
	friend QDebug operator<<( QDebug dbg, Command value );
	#endif

private:
	quint8             m_startMarker { C::StartMarker }; //!< Контрольное слово (0x81)
	VTRS::ControlFlags m_controlFlags;                   //!< Флаги управления усилителем
	VTRS::ChannelFlags m_channelFlags;                   //!< Флаги управления каналами усиления

	union
	{
		quint8 m_mode;
		struct
		{
			#ifdef LITTLE_ENDIAN
			quint8 counter : 4; //!< Количество периодов обзора, после которого происходит переключение схемы излучения (2^counter)
			quint8 pattern : 4; //!< Варианты схем излучения
			#endif
		} m_bf;
	};

	quint8 m_crc { UINT8_MAX };          //!< Контрольная сумма управляющей структуры
	quint8 m_endMarker { C::EndMarker }; //!< Контрольное слово (0x99)

	inline quint8 calcCrc() const
	{
		return ( static_cast< quint8 >( m_controlFlags.value() +
		                                m_channelFlags.value() +
		                                m_mode ) );
	}
}; // class Command

#pragma pack(pop)

} // namespace veer::protocols::control::surok::amplifier

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/amplifier/qt/command.hpp>
#endif

static_assert( sizeof( veer::protocols::control::surok::amplifier::Command ) == 6,
               "veer::protocols::control::surok::amplifier::Command" );


    #endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_AMPLIFIER_COMMAND_HPP_
