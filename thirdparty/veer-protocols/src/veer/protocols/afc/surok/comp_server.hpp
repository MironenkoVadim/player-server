#ifndef VEER_PROTOCOLS_AFC_SUROK_COMP_SERVER_HPP_
#define VEER_PROTOCOLS_AFC_SUROK_COMP_SERVER_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::afc::surok {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 CompServerVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры для передачи состояния сервера
 */
constexpr quint32 CompServerEndMarker { 0x4643584f }; // FCXO

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для состояния сервера
 */
class CompServer : public VPB::Header
{
public:
	CompServer()
	{
		setType( VTC::CodogramType::AfcCompServer );
		setSize( sizeof( CompServer ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::CompServerVersion ); }

	qint8 status()                { return ( m_status ); }
	void setStatus( qint8 value ) { m_status = value; }

	quint8 color()                { return ( m_color ); }
	void setColor( quint8 value ) { m_color = value; }

	VTC::TimeSpec64 responseTime()                      { return ( m_responseTime ); }
	void setResponseTime( const VTC::TimeSpec64 value ) { m_responseTime = value; }
	void setCurrentTime()                               { m_responseTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::CompServerEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const CompServer& value );
	friend QDataStream& operator>>( QDataStream& ds, CompServer& value );
	#endif

private:
	quint16         m_version      { C::CompServerVersion };   //!< Номер версии структуры
	qint8           m_status       { INT8_MAX };               //!< Результат обработки
	quint8          m_color        { Qt::transparent };        //!< Цвет для отображения на мнемосхеме
	VTC::TimeSpec64 m_responseTime { VTC::TimeSpec64() };      //!< Время отправки ответа о состоянии { с, нс }
	quint32         m_endMarker    { C::CompServerEndMarker }; //!< Маркер, записываемый в конец структуры
}; // class CompServer

#pragma pack(pop)

} // namespace veer::protocols::afc::surok

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/afc/surok/qt/comp_server.hpp>
#endif

static_assert( sizeof( veer::protocols::afc::surok::CompServer ) == sizeof( veer::protocols::base::Header ) + 20,
               "Invalid size of struct veer::protocols::afc::surok::CompServer" );

#endif // ifndef VEER_PROTOCOLS_AFC_SUROK_COMP_SERVER_HPP_
