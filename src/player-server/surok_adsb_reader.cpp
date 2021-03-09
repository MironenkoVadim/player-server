#include "surok_adsb_reader.hpp"

SurokAdsbReader::SurokAdsbReader()
{
	setId( FileFormat::SurokAdsb );
	setExtension( "sbs" );
//	connections();
//	m_idxFile.setFileName( "myfile" );
//	m_idxFile.open( QIODevice::ReadWrite );
//	connect( &m_timerSbs, &QTimer::timeout, this, &SurokAdsbReader::readFromFileTimer );
}


void /*QByteArray*/ SurokAdsbReader::readFromFileTimer()
{
	AdsbTracksData data;
	m_returnValue.first.clear();
	QDataStream ds( &m_returnValue.first, QIODevice::WriteOnly );
	m_dstream.setDevice( &file() );
	if ( !m_dstream.device()->atEnd() )
	{
		m_dstream >> data;
		qDebug() << "Записан пакет Adsb" << sizeof( file() ) << data.header().sendingTime() << static_cast< double >( ( file().pos() + 0.0 ) / file().size() );
		m_returnValue.second = fillingJsonObject( "value_slider", QString::number(
							( static_cast< double >( ( file().pos() + 0.0 ) / file().size() ) ) * 100 ) );
		ds << data;
		m_timerAdsb.start( 3000 / m_boostRead );
	}
}


QMultiHash < int, QPair< VTC::TimeSpec64, int > > SurokAdsbReader::readCreateIndex()
{
	AdsbTracksData data;
	m_dstream.setDevice( &file() );
	while ( !m_dstream.device()->atEnd() )
	{
		m_dstream >> data;
		m_hash.insert( m_number, qMakePair( data.header().sendingTime(), m_currentPos ) );
		m_number++;
		m_currentPos += data.size();
	}
	qDebug() << "Индексирование завершено";
	return m_hash;
}
