#ifndef VEER_TYPES_TRACKING_IFF_HPP_
#define VEER_TYPES_TRACKING_IFF_HPP_

#pragma once

#include <veer/backports/cpp/helpers.hpp>
#include <veer/common/config.hpp>
#include <veer/common/limits.hpp>

namespace veer::types::tracking {

#pragma pack(push, 1)

namespace VC = veer::common;

/*!
 * \brief Режимы запроса / ответа от НРЗ
 */
enum class IffMode : quint8
{
	Mode1  = 1,                              //!< Признак ответа в режиме 1
	Mode2  = 2,                              //!< Признак ответа в режиме 2
	Mode4  = 4,                              //!< Признак ответа в режиме 4 (номер борта)
	Mode6  = 6,                              //!< Признак ответа в режиме 6 (высота и остаток топлива)
	Mode46 = 46,                             //!< Признак ответа в режиме 4/6 (номер борта, высота и остаток топлива)
};

/*!
 * \brief Результат опознавания от НРЗ
 */
enum class IffTag : quint8
{
	Unknown          = 1,                    //!< Не опознан
	FriendIndividual = 2,                    //!< Свой ГО (пароль режим 2)
	FriendGeneral    = 3,                    //!< Свой ОО (пароль режим 1)
	Foe              = 4                     //!< Чужой
};

/*!
 * \brief Информация, полученная от НРЗ
 */
class IffInfo
{
public:
	quint32 id() const { return( m_id ); }
	void setId( quint32 id ) { m_id = id; }

	float fuelLoad() const { return( m_fuelLoad ); }
	void setFuelLoad( float fuelLoad ) { m_fuelLoad = fuelLoad; }

	IffMode mode() const { return( m_mode ); }
	void setMode( IffMode mode ) { m_mode = mode; }

	IffTag tag() const { return( m_tag ); }
	void setTag( IffTag tag ) { m_tag = tag; }

	bool isRequest() const { return( m_isRequest != 0 ); }
	void setIsRequest( bool isRequest ) { m_isRequest = static_cast< quint8 >( isRequest ); }

	bool isUpdate() const { return( m_isUpdate != 0 ); }
	void setIsUpdate( bool isUpdate ) { m_isUpdate = static_cast< quint8 >( isUpdate ); }

	bool isAlert() const { return( m_isAlert != 0 ); }
	void setIsAlert( bool isAlert ) { m_isAlert = static_cast< quint8 >( isAlert ); }

	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const IffInfo& value );
	friend QDataStream& operator>>( QDataStream& ds, IffInfo& value );
	#endif

private:
	quint32 m_id        { UINT32_MAX };      //!< Номер борта, если не определён - UINT32_MAX
	float   m_fuelLoad  { VC::FloatNAN };    //!< Запас топлива, если не определён - NAN
	IffMode m_mode      { IffMode::Mode1 };  //!< Режим запроса / ответа
	IffTag  m_tag       { IffTag::Unknown }; //!< Результат опознавания
	quint8  m_isRequest { 0 };               //!< Признак наличия запроса по трассе в данном обзоре
	quint8  m_isUpdate  { 0 };               //!< Признак полётной информации
	quint8  m_isAlert   { 0 };               //!< Бедствие в пароле
	quint8  m_stub1     { UINT8_MAX };
	quint8  m_stub2     { UINT8_MAX };
	quint8  m_stub3     { UINT8_MAX };
}; // class IffInfo

#pragma pack(pop)

} // namespace veer::types::tracking

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/types/tracking/qt/iff.hpp>
#endif

static_assert( sizeof( veer::types::tracking::IffInfo ) ==  16,
               "Invalid size of class veer::types::tracking::IffInfo" );

#endif // ifndef VEER_TYPES_TRACKING_IFF_HPP_
