#ifndef SUROK_ADSB_READER_HPP_
#define SUROK_ADSB_READER_HPP_

#pragma once

#include "base_reader.hpp"

#include <cstdint>

#include <QString>


class SurokAdsbReader : public BaseReader
{
	Q_OBJECT
public:

	SurokAdsbReader();
	~SurokAdsbReader() override {}
	bool hasIndex() override { return( true ); }
	bool checkIndex() override { return( true ); }
	bool createIndex() override { return( true ); }

	/*QByteArray*/ void readFromFileTimer() override;
	QMultiHash < int, QPair< VTC::TimeSpec64, int > > readCreateIndex() override;

private:
	QFile          m_idxFile;
	QDataStream    m_dstream;

	bool        m_indexDebug { false };
	int         m_number { 0 };
	int64_t     m_currentPos { 0 };
//	QMultiHash < int, QPair< VTC::TimeSpec64, int > > m_mHash;
};


#endif // ifndef SUROK_ADSB_READER_HPP_
