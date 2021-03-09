#ifndef VEER_PROTOCOLS_CONTROL_GATE_HEADER_HPP_
#define VEER_PROTOCOLS_CONTROL_GATE_HEADER_HPP_

#pragma once

#include <veer/common/limits.hpp>

#include <veer/types/common/application.hpp>
#include <veer/types/common/codogram_type.hpp>

namespace veer::protocols::control::gate {

#pragma pack(push, 1)

/*!
 * \brief Базовый заголовок пакета, используемый для всех кодограмм в проекте Веер
 */
class Header
{
public:
	quint64 senderId() const { return( static_cast< quint64 >( m_senderId ) ); }
	void setSenderId( quint64 senderId ) { m_senderId = senderId; }

	quint64 receiverId() const { return( static_cast< quint64 >( m_receiverId ) ); }
	void setReceiverId( quint64 receiverId ) { m_receiverId = receiverId; }

	quint64 messageTypeId() const { return( static_cast< quint64 >( m_messageTypeId ) ); }
	void setMessageTypeId( quint64 messageTypeId ) { m_messageTypeId = messageTypeId; }

	quint64 messageSeqNumber() const { return( static_cast< quint64 >( m_messageSeqNumber ) ); }
	void setMessageSeqNumber( quint64 messageSeqNumber ) { m_messageSeqNumber = messageSeqNumber; }

	quint16 packetSize() const { return( static_cast< quint16 >( m_packetSize ) ); }
	void setPacketSize( quint16 packetSize ) { m_packetSize = packetSize; }

	quint16 packetNumber() const { quint16 v { m_packetNumber }; return( v &= 0x7fff ); }
	void setPacketNumber( quint16 packetNumber ) { packetNumber &= 0x7fff; m_packetNumber &= 0x8000; m_packetNumber |= packetNumber; }

	bool isLastPart() const { quint16 f { m_packetNumber }; return ( f >> 15 ); }
	void setLastPart( bool flag = true ) { flag ? ( m_packetNumber |= 0x8000 ) : ( m_packetNumber &= 0x7fff ); }

	quint32 magic() const { return( static_cast< quint32 >( m_magic ) ); }
	void setMagic( const quint32& magic ) { m_magic = magic; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, Header value );
	friend QDataStream& operator>>( QDataStream& ds, Header& value );
	#endif

private:
	quint64 m_senderId         { UINT64_MAX }; //!< Идентификатор отправителя
	quint64 m_receiverId       { UINT64_MAX }; //!< Идентификатор получателя
	quint64 m_messageTypeId    { UINT64_MAX }; //!< Тип пересылаемого сообщения
	quint64 m_messageSeqNumber { UINT64_MAX }; //!< Последовательный номер пересылаемого сообщения
	quint16 m_packetSize       { UINT16_MAX }; //!< Размер части сообщения, передаваемый вместе с пакетом
	quint16 m_packetNumber     { UINT16_MAX }; //!< Последовательный номер части сообщения + признак последней части пакета
	quint32 m_magic            { UINT32_MAX }; //!< Маркер пакета
}; // class Header

#pragma pack(pop)

} // namespace veer::protocols::control::gate
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/gate/qt/header.hpp>
#endif

static_assert( sizeof( veer::protocols::control::gate::Header ) == 40,
               "Invalid size of struct veer::protocols::control::Header" );

#endif // ifndef VEER_PROTOCOLS_CONTROL_GATE_HEADER_HPP_
