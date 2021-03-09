#ifndef VEER_PROTOCOLS_PREPROC_SPECTRUMS_REQUEST_HPP_
#define VEER_PROTOCOLS_PREPROC_SPECTRUMS_REQUEST_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>
#include <veer/types/common/timespec64.hpp>

namespace veer::protocols::preproc {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 SpectrumsRequestVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей запрос для выдачи спектров от первички
 */
constexpr quint32 SpectrumsRequestEndMarker { 0x50505352 }; // PPSR

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;


#pragma pack(push, 1)

/*!
 * \brief Кодограмма запроса для выдачи спектров от первички
 */
class SpectrumsRequest : public VPB::Header
{
	inline quint64 makeChannelMask( int number )
	{
		if ( number <= 0 ) { return( 0 ); }
		if ( number > 64 ) { number = 64; }
		return ( static_cast< quint64 >( 1UL << ( number - 1 ) ) );
	}

public:
	SpectrumsRequest()
	{
		setType( VTC::CodogramType::SpectrumsRequest );
		setSize( sizeof( SpectrumsRequest ) - sizeof( Header ) );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::SpectrumsRequestVersion ); }

	void enablePrimaryChannel( int number ) { m_primaryChannelsMask |= makeChannelMask( number ); }
	void disablePrimaryChannel( int number )   { m_primaryChannelsMask &= ~makeChannelMask( number ); }
	bool isPrimaryChannelEnabled( int number ) { return ( m_primaryChannelsMask & makeChannelMask( number ) ); }
	quint64 primaryChannelsMask() const { return( m_primaryChannelsMask ); }
	void setPrimaryChannelsMask( quint64 value = 0 ) { m_primaryChannelsMask = value; }

	void enableSecondaryChannel( int number ) { m_secondaryChannelsMask |= makeChannelMask( number ); }
	void disableSecondaryChannel( int number )   { m_secondaryChannelsMask &= ~makeChannelMask( number ); }
	bool isSecondaryChannelEnabled( int number ) { return ( m_secondaryChannelsMask & makeChannelMask( number ) ); }
	quint64 secondaryChannelsMask() const { return( m_secondaryChannelsMask ); }
	void setSecondaryChannelsMask( quint64 value = 0 ) { m_secondaryChannelsMask = value; }

	VTC::TimeSpec64 requestTime()                     { return ( m_requestTime ); }
	void setRequestTime( const VTC::TimeSpec64 time ) { m_requestTime = time; }
	void setCurrentTime()                             { m_requestTime = VTC::TimeSpec64(); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::SpectrumsRequestEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const SpectrumsRequest& value );
	friend QDataStream& operator>>( QDataStream& ds, SpectrumsRequest& value );
	#endif

private:
	quint16         m_version      { C::SpectrumsRequestVersion };   //!< Номер версии структуры
	quint16         m_stub         { 0 };                            //!<
	quint64         m_primaryChannelsMask   { 0 };                   //!< Битовая маска первичных каналов для передачи
	quint64         m_secondaryChannelsMask { 0 };                   //!< Битовая маска вторичных каналов для передачи
	VTC::TimeSpec64 m_requestTime  { VTC::TimeSpec64() };            //!< Время отправки запроса { с, нс }
	quint32         m_endMarker    { C::SpectrumsRequestEndMarker }; //!< Маркер, записываемый в конец структуры
}; // class SpectrumsRequest


#pragma pack(pop)

} // namespace veer::protocols::preproc

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/preproc/qt/spectrums_request.hpp>
#endif
static_assert( sizeof( veer::protocols::preproc::SpectrumsRequest ) == sizeof( veer::protocols::base::Header ) + 36,
               "Invalid size of struct veer::protocols::preproc::SpectrumsRequest" );


#endif // ifndef VEER_PROTOCOLS_PREPROC_SPECTRUMS_REQUEST_HPP_
