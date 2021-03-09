#ifndef VEER_TYPES_TRACKING_ADSB_HPP_
#define VEER_TYPES_TRACKING_ADSB_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/common/limits.hpp>

namespace veer::types::tracking {

namespace VC = veer::common;

#pragma pack(push, 1)

/*!
 * \brief Информация, полученная от АЗН-В
 */
class AdsbInfo
{
public:
	quint32 id() const { return( m_id ); }
	void setId( quint32 id ) { m_id = id; }

	float barHeight() const { return( m_barHeight ); }
	void setBarHeight( float barHeight ) { m_barHeight = barHeight; }

	bool isAnswer() const { return( m_isAnswer != 0 ); }
	void setIsAnswer( bool isAnswer ) { m_isAnswer = static_cast< quint8 >( isAnswer ); }

	bool isUpdate() const { return( m_isUpdate != 0 ); }
	void setIsUpdate( bool isUpdate ) { m_isUpdate = static_cast< quint8 >( isUpdate ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const AdsbInfo& value );
	friend QDataStream& operator>>( QDataStream& ds, AdsbInfo& value );
	friend QDebug operator<<( QDebug dbg, AdsbInfo value );
	#endif

private:
	quint32 m_id           { UINT32_MAX };   //!< Идентификатор цели
	float   m_barHeight    { VC::FloatNAN }; //!< Барометрическая высота
	float   m_stubf        { VC::FloatNAN };
	quint8  m_isAnswer     { 0 };
	quint8  m_isUpdate     { 0 };
	quint16 m_stub         { 0 };
}; // class AdsbInfo

#pragma pack(pop)

} // namespace veer::types::tracking
#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/adsb.hpp>
#endif

static_assert( sizeof( veer::types::tracking::AdsbInfo ) ==  16,
               "Invalid size of class veer::types::tracking::AdsbInfo" );

#endif // ifndef VEER_TYPES_TRACKING_ADSB_HPP_
