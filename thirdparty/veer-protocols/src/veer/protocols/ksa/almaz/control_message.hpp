#ifndef VEER_PROTOCOLS_KSA_ALMAZ_CONTROL_MESSAGE_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_CONTROL_MESSAGE_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/ksa/almaz/header.hpp>

namespace veer::protocols::ksa::almaz {

namespace constants
{

constexpr quint16 EvenControlWord { 0b0101010101010101 };
constexpr quint16 OddControlWord  { 0b1010101010101010 };

} // namespace constants

namespace C = constants;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для отправки тестовых ответов
 */
class ControlMessage : public Header
{
public:
	ControlMessage()
	{
		setMessageType( MessageType::ControlMessage );
	}

	bool status() const { return( m_w9 == C::EvenControlWord ); }
	void setStatus( bool value )
	{
		value ? m_u9.controlCode = 0b1010 : 0b0101;
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const ControlMessage& value );
	friend QDataStream& operator>>( QDataStream& ds, ControlMessage& value );
	friend QDebug operator<<( QDebug dbg, const ControlMessage& value );
	#endif

private:
	quint16 m_w3 { C::OddControlWord };
	quint16 m_w4 { C::EvenControlWord };
	quint16 m_w5 { C::OddControlWord };
	quint16 m_w6 { C::EvenControlWord };
	quint16 m_w7 { C::OddControlWord };
	quint16 m_w8 { C::EvenControlWord };
	union
	{
		quint16 m_w9;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned fixed       : 12;
			unsigned controlCode : 4;
			#endif
		} m_u9 { C::OddControlWord };
	};
}; // class ControlMessage


#pragma pack(pop)

} // namespace veer::protocols::ksa::almaz


#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/ksa/almaz/qt/control_message.hpp>
#endif

static_assert( sizeof( veer::protocols::ksa::almaz::ControlMessage ) == sizeof( veer::protocols::ksa::almaz::Header ) + 14,
               "Invalid size of struct veer::protocols::ksa::almaz::ControlMessage" );

#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_CONTROL_MESSAGE_HPP_
