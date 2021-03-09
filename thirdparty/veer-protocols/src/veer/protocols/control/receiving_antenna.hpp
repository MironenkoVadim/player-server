#ifndef VEER_PROTOCOLS_CONTROL_RECEIVING_ANTENNA_HPP_
#define VEER_PROTOCOLS_CONTROL_RECEIVING_ANTENNA_HPP_

#pragma once

#include <veer/common/limits.hpp>
#include <veer/protocols/base/header.hpp>
#include <veer/types/common/points.hpp>

namespace veer::protocols::control {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 ReceivingAntennaVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей параметры приёмной антенны
 */
constexpr quint32 ReceivingAntennaEndMarker { 0x52435641 }; // RCVA

} // namespace constants

namespace C   = constants;
namespace VC  = veer::common;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для описания параметров приёмной антенны
 */
class ReceivingAntenna : public VPB::Header
{
public:
	ReceivingAntenna()
	{
		setType( VTC::CodogramType::ReceivingAntenna );
		setSize( sizeof( ReceivingAntenna ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::ReceivingAntennaVersion ); }

	VTC::LatLongPoint3F& position()                   { return ( m_position ); }
	void setPosition( VTC::LatLongPoint3F position )  { m_position = position; }

	float mainDirection() const { return ( m_mainDirection ); }
	void setMainDirection( float value ) { m_mainDirection = value; }

	float additionalDirection() const { return ( m_additionalDirection ); }
	void setAdditionalDirection( float value ) { m_additionalDirection = value; }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::ReceivingAntennaEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const ReceivingAntenna& value );
	friend QDataStream& operator>>( QDataStream& ds, ReceivingAntenna& value );
	#endif

private:
	quint16             m_version     { C::ReceivingAntennaVersion }; //!< Номер версии структуры
	quint16             m_stub        { UINT16_MAX };
	VTC::LatLongPoint3F m_position;                                   //!< Позиция { шир, дол, м }
	float               m_mainDirection       { VC::FloatNAN };       //!< Ориентация 1 вибратора основной антенны относительно севера
	float               m_additionalDirection { VC::FloatNAN };       //!< Ориентация 1 сектора дополнительной антенны относительно севера
	quint32             m_endMarker { C::ReceivingAntennaEndMarker }; //!< Маркер, записываемый в конец структуры
}; // class ReceivingAntenna

#pragma pack(pop)

} // namespace veer::protocols::control

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/qt/receiving_antenna.hpp>
#endif

static_assert( sizeof( veer::protocols::control::ReceivingAntenna ) == sizeof( veer::protocols::base::Header ) + 28,
               "Invalid size of struct veer::protocols::control::ReceivingAntenna" );

#endif // ifndef VEER_PROTOCOLS_CONTROL_RECEIVING_ANTENNA_HPP_
