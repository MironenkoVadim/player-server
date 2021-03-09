#ifndef FILE_FORMAT_HPP_
#define FILE_FORMAT_HPP_

#pragma once

#include <cstdint>

enum FileFormat : uint32_t
{
	None            = 0,
	SurokMarks      = 0x0001,
	SurokNoiseMarks = 0x0002,
	SurokAdsb       = 0x0003,
	SurokNoiseAdsb  = 0x0004,
};


#endif
