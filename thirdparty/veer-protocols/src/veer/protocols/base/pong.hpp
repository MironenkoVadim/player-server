#ifndef VEER_PROTOCOLS_BASE_PONG_HPP_
#define VEER_PROTOCOLS_BASE_PONG_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::base {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 PongVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей тестовый запрос
 */
constexpr quint32 PongEndMarker { 0x504f4e47 }; // PONG

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для отправки тестовых ответов
 */
class Pong : public Header
{
public:
	Pong()
	{
		setType( VTC::CodogramType::Pong );
		setSize( sizeof( Pong ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::PongVersion ); }

	quint16 code()               { return ( m_code ); }
	void setCode( quint16 code ) { m_code = code; }

	VTC::TimeSpec64 requestTime()                     { return ( m_requestTime ); }
	void setRequestTime( const VTC::TimeSpec64 time ) { m_requestTime = time; }
	void setCurrentTime()                             { m_requestTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::PongEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Pong& value );
	friend QDataStream& operator>>( QDataStream& ds, Pong& value );
	#endif

private:
	quint16         m_version     { C::PongVersion };    //!< Номер версии структуры
	quint16         m_code        { UINT16_MAX };        //!< Поле для служебной информации
	VTC::TimeSpec64 m_requestTime { VTC::TimeSpec64() }; //!< Время отправки запроса { с, нс }
	quint32         m_endMarker   { C::PongEndMarker };  //!< Маркер, записываемый в конец структуры
}; // class Pong

#pragma pack(pop)

} // namespace veer::protocols::base
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/base/qt/pong.hpp>
#endif

static_assert( sizeof( veer::protocols::base::Pong ) == sizeof( veer::protocols::base::Header ) + 20,
               "Invalid size of struct veer::protocols::base::Pong" );

#endif // ifndef VEER_PROTOCOLS_BASE_PONG_HPP_
