#ifndef VEER_PROTOCOLS_KSA_ALMAZ_HEADER_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_HEADER_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/limits.hpp>

namespace veer::protocols::ksa::almaz {

namespace constants
{

/*!
 * \brief Значение маркера, записываемого в начало структуры
 */
constexpr quint16 FirstWord { 0 };

} // namespace constants

namespace C = constants;

#pragma pack(push, 1)

enum class MessageType
{
	RadarTrack     = 0b000010,
	IffTrack       = 0b000011,
	Command        = 0b011101,
	ControlMessage = 0b000001,
};


/*!
 * \brief Базовый заголовок пакета для обмена с КСА
 */
class Header
{
public:
	float delay() const { return ( m_u2.delay / 50.0F ); }
	void setDelay( float value )
	{
		if ( value < 0 ) { value = 0; }
		if ( value > 5.1F ) { value = 5.1; }
		m_u2.delay = static_cast< quint8 >( value * 50 );
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, Header value );
	friend QDataStream& operator>>( QDataStream& ds, Header& value );
	friend QDebug operator<<( QDebug dbg, const Header value );
	#endif

protected:
	MessageType messageType() const { return ( static_cast< MessageType >( m_u2.messageType ) ); }
	void setMessageType( MessageType value ) { m_u2.messageType = static_cast< unsigned >( value ); }

private:
	quint16 m_w1 { C::FirstWord }; //!< Маркер, записываемый в начало структуры
	union
	{
		quint16 m_w2 { 0 };
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned delay       : 8; //!< Время задержки сообщения от момента формирования до момента выдачи в канал ПД
			unsigned messageType : 6; //!< Тип донесения
			unsigned empty       : 2;
			#endif
		} m_u2;
	};
}; // class Header


#pragma pack(pop)

} // namespace veer::protocols::ksa::almaz

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/ksa/almaz/qt/header.hpp>
#endif

static_assert( sizeof( veer::protocols::ksa::almaz::Header ) == 4,
               "Invalid size of struct veer::protocols::ksa::almaz::Header" );

#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_HEADER_HPP_
