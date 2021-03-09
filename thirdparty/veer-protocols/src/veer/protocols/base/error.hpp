#ifndef VEER_PROTOCOLS_BASE_ERROR_HPP_
#define VEER_PROTOCOLS_BASE_ERROR_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/error_codes.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::base {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 ErrorVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей сообщение об ошибке
 */
constexpr quint32 ErrorEndMarker { 0x45525221 }; // ERR!

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для отправки сообщения об ошибке
 */
class Error : public Header
{
public:
	Error()
	{
		setType( VTC::CodogramType::Error );
		setSize( sizeof( Error ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::ErrorVersion ); }

	VTC::ErrorCode code()                { return ( m_code ); }
	void setCode( VTC::ErrorCode value ) { m_code = value; }

	quint32 info()                { return ( m_info ); }
	void setInfo( quint32 value ) { m_info = value; }

	VTC::TimeSpec64 sendingTime()                     { return ( m_errorTime ); }
	void setSendingTime( const VTC::TimeSpec64 time ) { m_errorTime = time; }
	void setCurrentTime()                             { m_errorTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::ErrorEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Error& value );
	friend QDataStream& operator>>( QDataStream& ds, Error& value );
	#endif

private:
	quint16         m_version     { C::ErrorVersion };    //!< Номер версии структуры
	VTC::ErrorCode  m_code        { VTC::ErrorCode::OK }; //!< Код ошибки
	quint32         m_info        { UINT32_MAX };         //!< Дополнительная информация
	VTC::TimeSpec64 m_errorTime   { VTC::TimeSpec64() };  //!< Время появления ошибки { с, нс }
	quint32         m_endMarker   { C::ErrorEndMarker };  //!< Маркер, записываемый в конец структуры
}; // class Error

#pragma pack(pop)

} // namespace veer::protocols::base

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/base/qt/error.hpp>
#endif

static_assert( sizeof( veer::protocols::base::Error ) == sizeof( veer::protocols::base::Header ) + 24,
               "Invalid size of struct veer::protocols::base::Error" );

#endif // ifndef VEER_PROTOCOLS_BASE_ERROR_HPP_
