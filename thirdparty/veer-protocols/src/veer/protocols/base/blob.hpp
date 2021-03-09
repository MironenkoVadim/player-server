#ifndef VEER_PROTOCOLS_BASE_BLOB_HPP_
#define VEER_PROTOCOLS_BASE_BLOB_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>

namespace veer::protocols::base {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 BlobVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей тестовый запрос
 */
constexpr quint32 BlobEndMarker { 0x424c4f42 }; // BLOB

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для отправки тестовых ответов
 */
class Blob : public Header
{
public:
	Blob()
	{
		setType( VTC::CodogramType::Blob );
		setSize( sizeof( Blob ) - sizeof( Header ) - sizeof( char* ) + m_size );
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::BlobVersion ); }

	quint16 code()               { return ( m_code ); }
	void setCode( quint16 code ) { m_code = code; }

	quint32 size()               { return ( m_size ); }

	char* data() { return( m_data ); }
	void setData( const char* value, quint32 size )
	{
		delete m_data;
		if ( m_size > 0 )
		{
			m_data = new char[size];
			memcpy( m_data, value, size );
		}
		else
		{
			m_data = nullptr;
		}
	}

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::BlobEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const Blob& value );
	friend QDataStream& operator>>( QDataStream& ds, Blob& value );
	#endif

private:
	quint16 m_version     { C::BlobVersion };   //!< Номер версии структуры
	quint16 m_code        { UINT16_MAX };       //!< Поле для служебной информации
	quint32 m_size        { 0 };                //!< Размер произвольных данных
	char*   m_data        { nullptr };          //!< Указатель на данные
	quint32 m_endMarker   { C::BlobEndMarker }; //!< Маркер, записываемый в конец структуры
}; // class Blob

#pragma pack(pop)

} // namespace veer::protocols::base

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/base/qt/blob.hpp>
#endif

static_assert( sizeof( veer::protocols::base::Blob ) == sizeof( veer::protocols::base::Header ) + 12 + sizeof( char* ),
               "Invalid size of struct veer::protocols::base::Blob" );

#endif // ifndef VEER_PROTOCOLS_BASE_BLOB_HPP_
