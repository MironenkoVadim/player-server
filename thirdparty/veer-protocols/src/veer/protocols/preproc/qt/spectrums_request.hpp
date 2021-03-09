#ifndef VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_REQUEST_HPP_
#define VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_REQUEST_HPP_

#pragma once

#include <veer/protocols/preproc/spectrums_request.hpp>

namespace veer::protocols::preproc {

inline QDataStream& operator<<( QDataStream& ds, const SpectrumsRequest& value )
{
	const VPB::Header& bh { value };
	ds << bh;

	ds << value.m_version;
	ds << value.m_stub;
	ds << value.m_primaryChannelsMask;
	ds << value.m_secondaryChannelsMask;
	ds << value.m_requestTime;
	ds << value.m_endMarker;

	return( ds );
}


inline QDataStream& operator>>( QDataStream& ds, SpectrumsRequest& value )
{
	VPB::Header& bh { static_cast< VPB::Header& >( value ) };
	ds >> bh;

	ds >> value.m_version;
	ds >> value.m_stub;
	ds >> value.m_primaryChannelsMask;
	ds >> value.m_secondaryChannelsMask;
	ds >> value.m_requestTime;
	ds >> value.m_endMarker;

	return( ds );
}

} // namespace veer::protocols::preproc

#endif // ifndef VEER_PROTOCOLS_PREPROC_QT_SPECTRUMS_REQUEST_HPP_
