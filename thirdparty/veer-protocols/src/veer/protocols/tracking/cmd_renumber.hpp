#ifndef VEER_PROTOCOLS_TRACKING_CMD_RENUMBER_HPP_
#define VEER_PROTOCOLS_TRACKING_CMD_RENUMBER_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/tracking/info_sources.hpp>

namespace veer::protocols::tracking {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 CmdRenumberVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей тестовый запрос
 */
constexpr quint32 CmdRenumberEndMarker { 0x63524e54 }; // cRNT

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VTT = veer::types::tracking;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

/*!
 * \brief Команда для сброса трассы
 */
class CmdRenumber : public VPB::Header
{
public:
	CmdRenumber()
	{
		setType( VTC::CodogramType::CmdRenumberTrack );
		setSize( sizeof( CmdRenumber ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::CmdRenumberVersion ); }

	VTT::InfoSources infoSources() const { return( m_infoSources ); }
	void setInfoSources( VTT::InfoSources value ) { m_infoSources = value; }

	quint32 oldNumber()                { return ( m_oldNumber ); }
	void setOldNumber( quint32 value ) { m_oldNumber = value; }

	quint32 newNumber()                { return ( m_newNumber ); }
	void setNewNumber( quint32 value ) { m_newNumber = value; }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::CmdRenumberEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const CmdRenumber& value );
	friend QDataStream& operator>>( QDataStream& ds, CmdRenumber& value );
	#endif

private:
	quint16          m_version     { C::CmdRenumberVersion };       //!< Номер версии структуры
	VTT::InfoSources m_infoSources { VTT::InfoSources::Undefined }; //!< Источники трассы
	quint8           m_stub        { UINT8_MAX };
	quint32          m_oldNumber   { UINT32_MAX };                  //!< Старый номер трассы
	quint32          m_newNumber   { UINT32_MAX };                  //!< Новый номер трассы
	quint32          m_endMarker   { C::CmdRenumberEndMarker };     //!< Маркер, записываемый в конец структуры
}; // class CmdRenumber


#pragma pack(pop)

} // namespace veer::protocols::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/tracking/qt/cmd_renumber.hpp>
#endif

static_assert( sizeof( veer::protocols::tracking::CmdRenumber ) == sizeof( veer::protocols::base::Header ) + 16,
               "Invalid size of struct veer::protocols::tracking::CmdRenumber" );

#endif // ifndef VEER_PROTOCOLS_TRACKING_CMD_RENUMBER_HPP_
