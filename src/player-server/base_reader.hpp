#ifndef BASE_READER_HPP_
#define BASE_READER_HPP_

#pragma once

#include "file_format.hpp"

#include <veer/protocols/preproc/marks_packet.hpp>
#include <veer/protocols/preproc/spectrums_packet.hpp>
#include <veer/protocols/tracking/adsb_tracks_packet.hpp>

#include <cstdint>

#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <QTimer>
#include <QTcpSocket>
#include <QDataStream>

namespace VPB = veer::protocols::base;
namespace VTC = veer::types::common;

class BaseReader : public QObject
{
	Q_OBJECT
public:

	using MarksData      = veer::protocols::preproc::MarksData;
	using SpectrumData      = veer::protocols::preproc::SpectrumsData;
	using AdsbTracksData = veer::protocols::tracking::AdsbTracksData;

	virtual ~BaseReader() {}
	const QString& extension() { return( m_extension ); }
	FileFormat id() { return( m_id ); }

	bool active() { return( m_active ); }
	bool dirWriteAble() { return( m_dirWriteAble ); }

	/**
	 * @brief Размер файла
	 */
	virtual size_t fileSize() { return( 0 ); }

	/**
	 * @brief Проверка, есть ли индекс у файла
	 */
	virtual bool hasIndex() { return( false ); }

	/**
	 * @brief Проверка корректности индекса
	 */
	virtual bool checkIndex() { return( false ); }

	/**
	 * @brief Создание индекса
	 */
	virtual bool createIndex() { return( false ); }

	/**
	 * @brief Быстрая проверка формата файла (первый заголовок)
	 */
	virtual bool fastCheck() { return( false ); }

	/**
	 * @brief Полная проверка формата файла (первый заголовок)
	 */
	virtual bool fullCheck() { return( false ); }

public:
	void setActive( bool value ) { m_active = value; }
	void setDirWriteAble( bool value ) { m_dirWriteAble = value; }

	void setId( FileFormat value ) { m_id = value; }
	void setExtension( QString value ) { m_extension = value; }

	bool indexDebug() { return( m_indexDebug ); }

	QFile& file() { return( m_file ); }
	QFile& idxFile() { return( m_idxFile ); }
	QStringList& fileList() { return( m_fileList ); }

	Q_SIGNAL void signalMarks();
	virtual void /*QByteArray*/ readFromFileTimer() = 0;
	virtual QMultiHash < int, QPair< VTC::TimeSpec64, int > > readCreateIndex() = 0;

	template< typename T >
	void readFromFile( T& data )
	{
		m_dstream.setDevice( &file() );
		while ( !m_dstream.device()->atEnd() )
		{
			m_dstream >> data;
			qDebug() << "Записан пакет" << m_idxFile.pos();
		}
		qDebug() << "Чтение завершено";
		return;
	}

	/*QByteArray*/QString checkDir( QString path );
	void shiftFile( int );
	void debugEvent();
	QByteArray fillingJsonObject( QString key, QString value );
	QByteArray fillingJsonObject( QStringList key, QStringList value );

	void setTimeOffset( int timeOffset ) { m_timeOffset = timeOffset; }

	void setCoordinateOffset( int coordinateOffset ) { m_coordinateOffset = coordinateOffset; }

	QPair<QByteArray, QByteArray> returnValue();
	// 1 qb: data, 2 qb: value_slider
	void setReturnValue( const QPair<QByteArray, QByteArray> &returnValue );

	QTimer* timerMarks();
	QTimer* timerAdsb();

	int boostRead();
	void setBoostRead( int boostRead );

	QMultiHash<int, QPair<VTC::TimeSpec64, int> >& mHash();
	void setMHash( const QMultiHash<int, QPair<VTC::TimeSpec64, int> > &mHash );

	QHash<int, QPair<VTC::TimeSpec64, int> >& hash();
	void setHash(const QHash<int, QPair<VTC::TimeSpec64, int> > &hash);

	QDataStream& dstream();
	void setDstream( QDataStream &dstream);

protected:
	int         m_timeOffset { 0 };
	int         m_coordinateOffset { 0 };

	int         m_boostRead{ 1 };

	QTimer      m_timerMarks;
	QTimer      m_timerAdsb;

	QPair< QByteArray, QByteArray > m_returnValue;
	/*QMultiHash*/QHash < int, QPair< VTC::TimeSpec64, int > > m_hash;
private:
	QFile       m_file;
	QFile       m_idxFile;
	FileFormat  m_id { FileFormat::None };
	QString     m_extension;

	bool        m_dirWriteAble { false };
	bool        m_active { false };

	bool        m_indexDebug { false };
	int         m_number { 0 };
	int64_t     m_currentPos { 0 };
	QStringList m_fileList;
	QDataStream m_dstream;
}; // class BaseReader


#endif // ifndef BASE_READER_HPP_
