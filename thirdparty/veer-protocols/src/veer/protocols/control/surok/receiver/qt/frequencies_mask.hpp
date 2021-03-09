#ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_FREQUENCIES_MASK_HPP_
#define VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_FREQUENCIES_MASK_HPP_

#pragma once

#include <veer/protocols/control/surok/receiver/frequencies_mask.hpp>

namespace veer::protocols::control::surok::receiver {

inline QDataStream& operator<<( QDataStream& ds, const FrequenciesMask& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_size;
	ds << value.m_first;
	ds << value.m_step;
	for ( auto i = 0; i < value.m_size; ++i )
	{
		ds << value.m_mask[i];
	}

	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, FrequenciesMask& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;
	quint16 size { 0 };
	quint32 first { 0 };
	quint32 step { 0 };

	ds >> value.m_version;
	ds >> size;
	ds >> first;
	ds >> step;

	if ( ( value.m_size == size ) &&
	     ( value.m_first == first ) &&
	     ( value.m_step == step ) )
	{
		for ( auto i = 0; i < value.m_size; ++i )
		{
			ds >> value.m_mask[i];
		}
		ds >> value.m_endMarker;
	}
	else
	{
		ds.resetStatus();
	}

	return( ds );
} // >>

} // namespace veer::protocols::control::surok::receiver

#endif // ifndef VEER_PROTOCOLS_CONTROL_SUROK_RECEIVER_QT_FREQUENCIES_MASK_HPP_
