#ifndef SUROK_MARKS_READER_HPP_
#define SUROK_MARKS_READER_HPP_

#pragma once

#include "base_reader.hpp"

#include <cstdint>

#include <QString>

class SurokMarksReader : public BaseReader
{
	Q_OBJECT

public:
	SurokMarksReader();
	~SurokMarksReader() override {}
	bool hasIndex() override { return( false ); }
	bool checkIndex() override { return( false ); }
	bool createIndex() override { return( false ); }

	void /*QByteArray*/ readFromFileTimer() override;
	QMultiHash < int, QPair< VTC::TimeSpec64, int > > readCreateIndex() override;

private:
	QFile          m_idxFile;
//	QTimer         m_timerMarks;
	QDataStream    m_dstream;

	bool        m_indexDebug { false };
	int         m_number { 0 };
	int64_t     m_currentPos { 0 };
//	QMultiHash < int, QPair< VTC::TimeSpec64, int > > m_number;
};


#endif // ifndef SUROK_MARKS_READER_HPP_
