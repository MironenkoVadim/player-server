#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_FREQUENCIES_MASK_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_FREQUENCIES_MASK_HPP_

#pragma once

#include <veer/protocols/base/header.hpp>

namespace veer::protocols::control::surok::receiver {

namespace constants
{

/*!
 * \brief Номер версии структуры
 */
constexpr quint16 FrequenciesMaskVersion   { 0x5631 };     // V1

/*!
 * \brief Фиксированное значение в конце структуры, описывающей команду для установки маски разрешённых / запрещённых частот
 */
constexpr quint32 FrequenciesMaskEndMarker { 0x4652514d }; // FRQM

} // namespace constants

namespace C   = constants;
namespace VTC = veer::types::common;
namespace VPB = veer::protocols::base;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для установки маски разрешённых / запрещённых частот
 */
class FrequenciesMask : public VPB::Header
{
public:
	FrequenciesMask()
	{
		setType( VTC::CodogramType::FrequenciesMask );
		setSize( sizeof( FrequenciesMask ) - sizeof( Header ) );
		memset( m_mask, 1, m_size );
	}

	inline bool isEnabled( quint32 freq )
	{
		if ( ( freq < m_first ) || ( freq > m_last ) ) { return( false ); }
		return( m_mask[( freq - m_first ) / m_step] != 0 );
	}

	inline bool isDisabled( quint32 freq )
	{
		if ( ( freq < m_first ) || ( freq > m_last ) ) { return( true ); }
		return( m_mask[( freq - m_first ) / m_step] == 0 );
	}

	inline void enable( quint32 freq )
	{
		if ( ( freq >= m_first ) && ( freq <= m_last ) )
		{
			m_mask[( freq - m_first ) / m_step] = 1;
		}
	}

	inline void disable( quint32 freq )
	{
		if ( ( freq >= m_first ) && ( freq <= m_last ) )
		{
			m_mask[( freq - m_first ) / m_step] = 0;
		}
	}

	quint16 version()          { return ( m_version ); }
	bool isVersionValid() const { return ( m_version == C::FrequenciesMaskVersion ); }

	constexpr static quint16 size() { return ( m_size ); }
	constexpr static quint32 first() { return ( m_first ); }
	constexpr static quint32 step() { return ( m_step ); }
	constexpr static quint32 last() { return ( m_last ); }

	quint32 endMarker()          { return ( m_endMarker ); }
	bool isEndMarkerValid() const { return ( m_endMarker == C::FrequenciesMaskEndMarker ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const FrequenciesMask& value );
	friend QDataStream& operator>>( QDataStream& ds, FrequenciesMask& value );
	#endif

private:
	quint16              m_version     { C::FrequenciesMaskVersion };         //!< Номер версии структуры
	const static quint16 m_size        { 2000 };                              //!< Количество допустимых частот
	const static quint32 m_first       { 50000000 };                          //!< Первая доступная частота
	const static quint32 m_step        { 10000 };                             //!< Шаг по частоте
	const static quint32 m_last        { m_first + ( m_size - 1 ) * m_step }; //!< Последняя доступная частота
	quint8               m_mask[m_size];                                      //!< Маска разрешённых / запрещённых частот
	quint32              m_endMarker   { C::FrequenciesMaskEndMarker };       //!< Маркер, записываемый в конец структуры
}; // class FrequenciesMask

#pragma pack(pop)

} // namespace veer::protocols::control::surok::receiver

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/control/surok/receiver/qt/frequencies_mask.hpp>
#endif

static_assert( sizeof( veer::protocols::control::surok::receiver::FrequenciesMask ) ==
               sizeof( veer::protocols::base::Header ) + 6 +
               veer::protocols::control::surok::receiver::FrequenciesMask::size(),
               "Invalid size of struct veer::protocols::control::surok::receiver::FrequenciesMask" );

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_FREQUENCIES_MASK_HPP_
