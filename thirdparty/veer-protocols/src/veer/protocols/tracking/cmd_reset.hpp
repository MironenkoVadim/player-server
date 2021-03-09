#ifndef VEER_PROTOCOLS_TRACKING_CMD_RESET_HPP_
#define VEER_PROTOCOLS_TRACKING_CMD_RESET_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/tracking/info_sources.hpp>

namespace veer::protocols::tracking {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 CmdResetVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей тестовый запрос
 */
constexpr quint32 CmdResetEndMarker { 0x63525452 }; // cRTR

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;
namespace VPB = veer::protocols::base;


#pragma pack(push, 1)

/*!
 * \brief Команда для сброса трассы
 */
class CmdReset : public VPB::Header
{
public:
	CmdReset()
	{
		setType( VTC::CodogramType::CmdResetTrack );
		setSize( sizeof( CmdReset ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::CmdResetVersion ); }

	VTT::InfoSources infoSources() const { return( m_infoSources ); }
	void setInfoSources( VTT::InfoSources value ) { m_infoSources = value; }

	quint32 number()               { return ( m_number ); }
	void setNumber( quint32 number ) { m_number = number; }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::CmdResetEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const CmdReset& value );
	friend QDataStream& operator>>( QDataStream& ds, CmdReset& value );
	#endif

private:
	quint16          m_version     { C::CmdResetVersion };          //!< Номер версии структуры
	VTT::InfoSources m_infoSources { VTT::InfoSources::Undefined }; //!< Источники трассы
	quint8           m_stub        { UINT8_MAX };
	quint32          m_number      { UINT32_MAX };                  //!< Номер трассы
	quint32          m_endMarker   { C::CmdResetEndMarker };        //!< Маркер, записываемый в конец структуры
}; // class CmdReset


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/cmd_reset.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::CmdReset ) == sizeof( veer::protocols::base::Header ) + 12,
               "Invalid size of struct veer::protocols::tracking::CmdReset" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_CMD_RESET_HPP_
