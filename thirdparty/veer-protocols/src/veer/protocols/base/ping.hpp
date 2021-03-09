#ifndef VEER_PROTOCOLS_BASE_PING_HPP_
#define VEER_PROTOCOLS_BASE_PING_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::base {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 PingVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей тестовый запрос
 */
constexpr quint32 PingEndMarker { 0x50494e47 }; // PING

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;

#pragma pack(push, 1)


/*!
 * \brief Кодограмма для отправки тестовых запросов без заголовка
 */
class PingHeaderless
{
public:
	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::PingVersion ); }

	quint16 code()               { return ( m_code ); }
	void setCode( quint16 code ) { m_code = code; }

	VTC::TimeSpec64 requestTime()                     { return( m_requestTime ); }
	void setRequestTime( const VTC::TimeSpec64 time ) { m_requestTime = time; }
	void setCurrentTime()                             { m_requestTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::PingEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const PingHeaderless& value );
	friend QDataStream& operator>>( QDataStream& ds, PingHeaderless& value );
	#endif

protected:
	quint16         m_version     { C::PingVersion };    //!< Номер версии структуры
	quint16         m_code        { UINT16_MAX };        //!< Поле для служебной информации
	VTC::TimeSpec64 m_requestTime { VTC::TimeSpec64() }; //!< Время отправки запроса  { с, нс }
	quint32         m_endMarker   { C::PingEndMarker };  //!< Маркер, записываемый в конец структуры
}; // class PingHeaderless

/*!
 * \brief Кодограмма для отправки тестовых запросов
 */
class Ping : public Header, public PingHeaderless
{
public:
	Ping()
	{
		setType( VTC::CodogramType::Ping );
		setSize( sizeof( Ping ) - sizeof( Header ) );
	}

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Ping& value );
	friend QDataStream& operator>>( QDataStream& ds, Ping& value );
	#endif
}; // class Ping

#pragma pack(pop)

} // namespace veer::protocols::base

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/base/qt/ping.hpp>
#endif

static_assert( sizeof( veer::protocols::base::Ping ) == sizeof( veer::protocols::base::Header ) + 20,
               "Invalid size of struct veer::protocols::Ping" );

#endif // ifndef VEER_PROTOCOLS_BASE_PING_HPP_
