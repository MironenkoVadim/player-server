#ifndef VEER_PROTOCOLS_AFC_SUROK_COMP_TOWS_HPP_
#define VEER_PROTOCOLS_AFC_SUROK_COMP_TOWS_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::afc::surok {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 CompTowsVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры для передачи состояния технологического рабочего места
 */
constexpr quint32 CompTowsEndMarker { 0x4643584f }; // FCXO

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для состояния технологического рабочего места
 */
class CompTows : public VPB::Header
{
public:
	CompTows()
	{
		setType( VTC::CodogramType::AfcCompTows );
		setSize( sizeof( CompTows ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::CompTowsVersion ); }

	qint8 status()                { return ( m_status ); }
	void setStatus( qint8 value ) { m_status = value; }

	quint8 color()                { return ( m_color ); }
	void setColor( quint8 value ) { m_color = value; }

	VTC::TimeSpec64 responseTime()                      { return ( m_responseTime ); }
	void setResponseTime( const VTC::TimeSpec64 value ) { m_responseTime = value; }
	void setCurrentTime()                               { m_responseTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::CompTowsEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const CompTows& value );
	friend QDataStream& operator>>( QDataStream& ds, CompTows& value );
	#endif

private:
	quint16         m_version      { C::CompTowsVersion };   //!< Номер версии структуры
	qint8           m_status       { INT8_MAX };             //!< Результат обработки
	quint8          m_color        { Qt::transparent };      //!< Цвет для отображения на мнемосхеме
	VTC::TimeSpec64 m_responseTime { VTC::TimeSpec64() };    //!< Время отправки ответа о состоянии { с, нс }
	quint32         m_endMarker    { C::CompTowsEndMarker }; //!< Маркер, записываемый в конец структуры
}; // class CompTows

#pragma pack(pop)

} // namespace veer::protocols::afc::surok

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/afc/surok/qt/comp_tows.hpp>
#endif

static_assert( sizeof( veer::protocols::afc::surok::CompTows ) == sizeof( veer::protocols::base::Header ) + 20,
               "Invalid size of struct veer::protocols::afc::surok::CompTows" );

#endif // ifndef VEER_PROTOCOLS_AFC_SUROK_COMP_TOWS_HPP_
