//-PB::550,2008

#include "test_ping.hpp"

#include <veer/protocols/base/ping.hpp>

#include <QDebug>


namespace TC  = veer::types::common;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;

void TestPing::testDataStream()
{
	const int   code = 1357;
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	PB::Ping pingIn;
	pingIn.setCode( code );

	// Проверка инициализации по умолчанию
	QVERIFY( pingIn.marker()      == PBC::HeaderMarker );
	QVERIFY( pingIn.baseVersion() == PBC::HeaderInfoVersion );
	QVERIFY( pingIn.type()        == TC::CodogramType::Ping );
	QVERIFY( pingIn.size()        == sizeof( PB::Ping ) );
	QVERIFY( pingIn.dataSize()    == sizeof( PB::Ping ) - sizeof( PB::Header ) );

	QVERIFY( pingIn.version()     == PBC::PingVersion );
	QVERIFY( pingIn.code()        == code );
	QVERIFY( pingIn.endMarker()   == PBC::PingEndMarker );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << pingIn;
	ds.device()->reset();

	PB::Ping pingOut;

	// Полная чистка структуры
	char* eraser = reinterpret_cast< char* >( &pingOut );
	memset( eraser, 0, sizeof( pingOut ) );

	QVERIFY( pingOut.marker()      == 0 );
	QVERIFY( pingOut.baseVersion() == 0 );
	QVERIFY( pingOut.type()        == TC::CodogramType::Zero );
	QVERIFY( pingOut.size()        == sizeof( PB::Header ) );
	QVERIFY( pingOut.dataSize()    == 0 );

	QVERIFY( pingOut.version()     == 0 );
	QVERIFY( pingOut.code()        == 0 );
	QVERIFY( pingOut.endMarker()   == 0 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> pingOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	// Проверка на соответствие оригиналу
	QVERIFY( pingOut.marker()      == pingIn.marker() );
	QVERIFY( pingOut.baseVersion() == pingIn.baseVersion() );
	QVERIFY( pingOut.type()        == pingIn.type() );
	QVERIFY( pingOut.size()        == pingIn.size() );
	QVERIFY( pingOut.dataSize()    == pingIn.dataSize() );

	QVERIFY( pingOut.version()     == pingIn.version() );
	QVERIFY( pingOut.code()        == pingIn.code() );
	QVERIFY( pingOut.endMarker()   == pingIn.endMarker() );
} // TestPing::testDataStream


QTEST_MAIN( TestPing )
