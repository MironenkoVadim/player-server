#ifndef VEER_PROTOCOLS_BASE_HEADER_HPP_
#define VEER_PROTOCOLS_BASE_HEADER_HPP_

#pragma once

#include <veer/common/limits.hpp>
#include <veer/types/common/application.hpp>
#include <veer/types/common/codogram_type.hpp>
#include <veer/common/config.hpp>
#include <cmath>


namespace veer::protocols::base {

namespace constants
{

/*!
 * \brief Номер версии структуры Header
 */
constexpr quint16 HeaderInfoVersion { 0x5631 };     // V1


/*!
 * \brief Фиксированное значение в начале структуры Header
 */
constexpr quint32 HeaderMarker      { 0x56656572 }; // Veer

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;

#pragma pack(push, 1)

/*!
 * \brief Базовый заголовок пакета, используемый для всех кодограмм в проекте Веер
 */
class Header
{
public:
	quint32 marker()          { return ( m_marker ); }
	bool isMarkerValid() const { return ( m_marker == C::HeaderMarker ); }

	quint16 baseVersion()          { return ( m_baseVersion ); }
	bool isBaseVersionValid() const { return ( m_baseVersion == C::HeaderInfoVersion ); }

	VTC::CodogramType type()     { return ( m_type ); }

	quint32 size() const { return ( m_size + static_cast< quint32 >( sizeof( Header ) ) ); }
	quint32 dataSize()     { return ( m_size ); }
	const char* constData() { return ( reinterpret_cast< const char* >( this + sizeof( Header ) ) ); }

	VTC::Application source() const { return( m_source ); }
	void setSource( VTC::Application source ) { m_source = source; }

	VTC::Application destination() const { return( m_destination ); }
	void setDestination( VTC::Application destination ) { m_destination = destination; }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Header& value );
	friend QDataStream& operator>>( QDataStream& ds, Header& value );
	#endif

protected:
	void setType( VTC::CodogramType type ) { m_type = type; }
	void setSize( quint32 size )     { m_size = size; }

private:
	quint32           m_marker      { C::HeaderMarker };              //!< Маркер, записываемый в начало структуры
	quint16           m_baseVersion { C::HeaderInfoVersion };         //!< Номер версии структуры
	VTC::CodogramType m_type        { VTC::CodogramType::Undefined }; //!< Тип сообщения, следующего за заголовком
	VTC::Application  m_source      { VTC::Application::Any };        //!< Источник сообщения
	VTC::Application  m_destination { VTC::Application::Any };        //!< Назначение сообщения
	quint32           m_size        { 0 };                            //!< Размер сообщения, следующего за заголовком
}; // class Header

#pragma pack(pop)

} // namespace veer::protocols::base

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/base/qt/header.hpp>
#endif

static_assert( sizeof( veer::protocols::base::Header ) == 16,
               "Invalid size of struct veer::protocols::base::Header" );

#endif // ifndef VEER_PROTOCOLS_BASE_HEADER_HPP_
