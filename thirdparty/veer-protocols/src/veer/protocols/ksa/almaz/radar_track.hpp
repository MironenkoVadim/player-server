#ifndef VEER_PROTOCOLS_KSA_ALMAZ_RADAR_TRACK_HPP_
#define VEER_PROTOCOLS_KSA_ALMAZ_RADAR_TRACK_HPP_

#pragma once

#include <veer/common/config.hpp>
#include <veer/protocols/ksa/almaz/header.hpp>

namespace veer::protocols::ksa::almaz {

namespace constants
{

} // namespace constants

namespace C = constants;

#pragma pack(push, 1)

/*!
 * \brief Кодограмма для отправки тестовых ответов
 */
class RadarTrack : public Header
{
public:
	RadarTrack()
	{
		setMessageType( MessageType::RadarTrack );
	}

	quint16 id() const { return( m_u3.id ); }
	void setId( quint16 value ) { m_u3.id = value; }

	quint8 ciPlane() const { return( m_u3.ciPlane ); }
	void setCiPlane( quint8 value ) { m_u3.ciPlane = ( value & 0b1111 ); }

	quint8 count() const { return( m_u3.count ); }
	void setCount( quint8 value ) { m_u3.count = ( value & 0b111 ); }

	bool isTraining() const { return ( m_u4.isTraining == 1 ); }
	void setTraining( bool value ) { value ? m_u4.isTraining = 1 : 0; }

	float x() const
	{
		if ( m_u4.xSign == 0 ) { return ( m_u4.x * 0.1 ); }
		else { return ( m_u4.x * -0.1 ); }
	}

	void setX( float value )
	{
		( value >= 0 ) ? m_u4.xSign = 0 : 1;
		value                       = std::abs( value );
		if ( Q_UNLIKELY( value >= ( 0x3FFF * 0.1F ) ) ) { m_u4.x = 0x3FFF; }
		else { m_u4.x = std::lroundf( value * 10.0F ); }
	}

	bool isAffilationUpdated() const { return ( m_u5.isAffilationUpdated == 1 ); }
	void setAffilationUpdated( bool value ) { value ? m_u5.isAffilationUpdated = 1 : 0; }

	float y() const
	{
		if ( m_u5.ySign == 0 ) { return ( m_u5.y * 0.1 ); }
		else { return ( m_u5.y * -0.1 ); }
	}

	void setY( float value )
	{
		( value >= 0 ) ? m_u5.ySign = 0 : 1;
		value                       = std::abs( value );
		if ( Q_UNLIKELY( value >= ( 0x3FFF * 0.1F ) ) ) { m_u5.y = 0x3FFF; }
		else { m_u5.y = std::lroundf( value * 10.0F ); }
	}

	quint8 status() const { return( m_u6.status ); }
	void setStatus( quint8 value ) { m_u6.status = ( value & 0b111 ); }

	quint8 affilation() const { return( m_u6.affilation ); }
	void setAffilation( quint8 value ) { m_u6.affilation = ( value & 0b11 ); }


	float h() const { return ( m_u6.h * 0.1 ); }
	void setH( float value )
	{
		if ( value < 0.0 ) { value = 0.0; }
		if ( Q_UNLIKELY( value >= ( 0x7FF * 0.1F ) ) ) { m_u6.h = 0x7FF; }
		else { m_u6.h = std::lroundf( value * 10.0F ); }
	}

	float vx() const
	{
		if ( m_u7.vxSign == 0 ) { return ( m_u7.vx * 10.0 ); }
		else { return ( m_u7.vx * -10.0 ); }
	}

	void setVX( float value )
	{
		( value >= 0 ) ? m_u7.vxSign = 0 : 1;
		value                        = std::abs( value );
		if ( Q_UNLIKELY( value >= ( 0x1FF * 10.0F ) ) ) { m_u7.vx = 0x1FF; }
		else { m_u7.vx = std::lroundf( value * 0.1F ); }
	}

	quint8 ciHeight() const { return( m_u7.ciHeight ); }
	void setCiHeight( quint8 value ) { m_u7.ciHeight = ( value & 0b111 ); }

	quint8 maneuver() const { return( m_u7.maneuver ); }
	void setManeuver( quint8 value ) { m_u7.maneuver = ( value & 0b111 ); }


	float vy() const
	{
		if ( m_u8.vySign == 0 ) { return ( m_u8.vy * 10.0 ); }
		else { return ( m_u8.vy * -10.0 ); }
	}

	void setVY( float value )
	{
		( value >= 0 ) ? m_u8.vySign = 0 : 1;
		value                        = std::abs( value );
		if ( Q_UNLIKELY( value >= ( 0x1FF * 10.0F ) ) ) { m_u8.vy = 0x1FF; }
		else { m_u8.vy = std::lroundf( value * 0.1F ); }
	}

	bool isAntiradar() const { return ( m_u8.isAntiradar == 1 ); }
	void setAntiradar( bool value ) { value ? m_u8.isAntiradar = 1 : 0; }

	quint8 sourceType() const { return( m_u8.sourceType ); }
	void setSourceType( quint8 value ) { m_u8.sourceType = ( value & 0b111 ); }


	float vh() const
	{
		if ( m_u9.vhSign == 0 ) { return ( m_u9.vh * 10.0 ); }
		else { return ( m_u9.vh * -10.0 ); }
	}

	void setVH( float value )
	{
		( value >= 0 ) ? m_u9.vhSign = 0 : 1;
		value                        = std::abs( value );
		if ( Q_UNLIKELY( value >= ( 0xFF * 10.0F ) ) ) { m_u9.vh = 0xFF; }
		else { m_u9.vh = std::lroundf( value * 0.1F ); }
	}

	quint8 objectType() const { return( m_u9.objectType ); }
	void setObjectType( quint8 value ) { m_u9.objectType = ( value & 0x7F ); }


	#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
	friend QDataStream& operator<<( QDataStream& ds, const RadarTrack& value );
	friend QDataStream& operator>>( QDataStream& ds, RadarTrack& value );
	friend QDebug operator<<( QDebug dbg, const RadarTrack value );
	#endif

private:
	union
	{
		quint16 m_w3;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned id      : 9;              //!< Номер трассы
			unsigned ciPlane : 4;              //!< Номер доверительного интервала для плоскостных координат
			unsigned count   : 3;              //!< Количественный состав ВО
			#endif
		} m_u3;
	};
	union
	{
		quint16 m_w4;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned isTraining : 1;           //!< Признак тренажной трассы. [реальная=0, тренажная=1]
			unsigned xSign      : 1;           //!< Знак координаты X. [+=0, -=1]
			unsigned x          : 14;          //!< Координата X км.
			#endif
		} m_u4;
	};
	union
	{
		quint16 m_w5;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned isAffilationUpdated : 1;  //!< Признак обновления ОГП для трека. [нет=0, есть=1]
			unsigned ySign               : 1;  //!< Знак координаты Y. [+=0, -=1]
			unsigned y                   : 14; //!< Координата Y км.
			#endif
		} m_u5;
	};
	union
	{
		quint16 m_w6;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned status     : 3;           //!< Признак сопровождения. [новая=001, экстраполированная=011, обновление по x&y=100, обновление по h=101, по х&y&h=110, сброс=111]
			unsigned affilation : 2;           //!< Признак результата ОГП. [не опр=00, чужой=01, свой(общ)=10, свой(гарант)=11]
			unsigned h          : 11;          //!< Высота полёта, км.
			#endif
		} m_u6;
	};
	union
	{
		quint16 m_w7;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned vxSign   : 1;             //!< Знак вектора скорости по оси X. [+=0, -=1]
			unsigned vx       : 9;             //!< Вектор скорости по оси X м/с.
			unsigned ciHeight : 3;             //!< Номер дов. интервала для высоты.[]
			unsigned maneuver : 3;             //!< Признак манёвра [отсутствует=000, по курсу=100, по высоте=010, по скорости=001}
			#endif
		} m_u7;
	};
	union
	{
		quint16 m_w8;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned vySign      : 1;          //!< Знак вектора скорости по оси Y. [+=0, -=1]
			unsigned vy          : 9;          //!< Вектор скорости по оси Y м/с.
			unsigned stub1       : 1;          //!<
			unsigned isAntiradar : 1;          //!< Признак противорадиолокационного средства. [!ПРС=0, ПРС=1]
			unsigned stub2       : 1;          //!<
			unsigned sourceType  : 3;          //!< Вид источника о ТВО. [Не определён=000, присвоен лицом боевого расчета=001, данные сигнально-траекторного распознавания=011]
			#endif
		} m_u8;
	};
	union
	{
		quint16 m_w9;
		struct
		{
			#ifdef LITTLE_ENDIAN
			unsigned vhSign     : 1;           //!< Знак вектора скорости по оси H. [+=0, -=1]
			unsigned vh         : 8;           //!< Скорость изменения высоты м/с.
			unsigned objectType : 7;           //!< Тип ВО.
			#endif
		} m_u9;
	};
}; // class RadarTrack

#pragma pack(pop)

} // namespace veer::protocols::ksa::almaz

#if !defined( VEER_PROTOCOLS_WITHOUT_QT )
#include <veer/protocols/ksa/almaz/qt/radar_track.hpp>
#endif

static_assert( sizeof( veer::protocols::ksa::almaz::RadarTrack ) == sizeof( veer::protocols::ksa::almaz::Header ) + 14,
               "Invalid size of struct veer::protocols::ksa::almaz::RadarTrack" );

#endif // ifndef VEER_PROTOCOLS_KSA_ALMAZ_RADAR_TRACK_HPP_
