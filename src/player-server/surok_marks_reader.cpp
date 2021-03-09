#include "surok_marks_reader.hpp"

SurokMarksReader::SurokMarksReader()
{
	setId( FileFormat::SurokMarks );
	setExtension( "marks" );
//	m_idxFile.setFileName( "myfile" );
//	m_idxFile.open( QIODevice::ReadWrite );
//	connect( &m_timerMarks, &QTimer::timeout, this, &SurokMarksReader::readFromFileTimer, Qt::QueuedConnection );
}


void /*QByteArray*/ SurokMarksReader::readFromFileTimer()
{
	MarksData data;
	m_returnValue.first.clear();
	QDataStream ds( &m_returnValue.first, QIODevice::WriteOnly );
	m_dstream.setDevice( &file() );
	if ( !m_dstream.device()->atEnd() )
	{
		m_dstream >> data;
		qDebug() << "time before: " << data.header().periodStartTime().seconds() << m_timeOffset;
		data.header().periodStartTime().setSeconds( data.header().periodStartTime().seconds() + m_timeOffset );
		qDebug() << "time later: " << data.header().periodStartTime().seconds();
		for ( auto& it : data.zones() )
		{
			for ( auto& itt : std::get< 1 > ( it ) )
			{
				qDebug() << "position before: " << itt.position().r() << itt.position().az() << itt.position().el();
				itt.setPosition( VTC::RadarPoint3F(
								 itt.position().r() + m_coordinateOffset,
								 itt.position().az() + m_coordinateOffset,
								 itt.position().el() + m_coordinateOffset ) );
				qDebug() << "position later: " << itt.position().r() << itt.position().az() << itt.position().el();
			}
		}
		qDebug() << "Записан пакет Marks" << sizeof( file() ) << data.header().sendingTime() << static_cast< double >( ( file().pos() + 0.0 ) / file().size() );
		m_returnValue.second = fillingJsonObject( "value_slider", QString::number(
							( static_cast< double >( ( file().pos() + 0.0 ) / file().size() ) ) * 100 ) );
		qDebug() << "----------size---------" << data.size() << sizeof( MarksData );
		ds << data;
		qDebug() << "----------m_returnValue---------" << m_returnValue.first.size();
		m_timerMarks.start( static_cast< int > ( data.header().periodTime() * 1000 / m_boostRead ) );
		Q_EMIT signalMarks();
	}
}


QMultiHash < int, QPair< VTC::TimeSpec64, int > > SurokMarksReader::readCreateIndex()
{
	MarksData data;
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
