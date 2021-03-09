#include "test_error.hpp"

#include <veer/protocols/base/error.hpp>

#include <QDebug>

namespace TC  = veer::types::common;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;

void TestError::testDataStream()
{
	TC::ErrorCode code = TC::ErrorCode::Error;
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );
	uint32_t info = 0xAA3355CC;

	PB::Error errorIn;
	errorIn.setCode( code );
	errorIn.setInfo( info );

	// Проверка инициализации по умолчанию
	QVERIFY( errorIn.marker()      == PBC::HeaderMarker );
	QVERIFY( errorIn.baseVersion() == PBC::HeaderInfoVersion );
	QVERIFY( errorIn.type()        == TC::CodogramType::Error );
	QVERIFY( errorIn.size()        == sizeof( PB::Error ) );
	QVERIFY( errorIn.dataSize()    == sizeof( PB::Error ) - sizeof( PB::Header ) );

	QVERIFY( errorIn.version()     == PBC::ErrorVersion );
	QVERIFY( errorIn.code()        == code );
	QVERIFY( errorIn.info()        == info );
	QVERIFY( errorIn.endMarker()   == PBC::ErrorEndMarker );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << errorIn;
	ds.device()->reset();

	PB::Error errorOut;

	// Полная чистка структуры
	char* eraser = reinterpret_cast< char* >( &errorOut );
	memset( eraser, 0, sizeof( errorOut ) );

	QVERIFY( errorOut.marker()      == 0 );
	QVERIFY( errorOut.baseVersion() == 0 );
	QVERIFY( errorOut.type()        == TC::CodogramType::Zero );
	QVERIFY( errorOut.size()        == sizeof( PB::Header ) );
	QVERIFY( errorOut.dataSize()    == 0 );

	QVERIFY( errorOut.version()     == 0 );
	QVERIFY( errorOut.code()        == TC::ErrorCode::OK );
	QVERIFY( errorOut.info()        == 0 );
	QVERIFY( errorOut.endMarker()   == 0 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> errorOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	// Проверка на соответствие оригиналу
	QVERIFY( errorOut.marker()      == errorIn.marker() );
	QVERIFY( errorOut.baseVersion() == errorIn.baseVersion() );
	QVERIFY( errorOut.type()        == errorIn.type() );
	QVERIFY( errorOut.size()        == errorIn.size() );
	QVERIFY( errorOut.dataSize()    == errorIn.dataSize() );

	QVERIFY( errorOut.version()     == errorIn.version() );
	QVERIFY( errorOut.code()        == errorIn.code() );
	QVERIFY( errorOut.info()        == errorIn.info() );
	QVERIFY( errorOut.endMarker()   == errorIn.endMarker() );
} // TestError::testDataStream


void TestError::testString()
{
	QVERIFY( TC::errorCodeToQString( TC::ErrorCode::OK ) == "OK" );
	QVERIFY( TC::errorCodeToQString( TC::ErrorCode::Error ) == "Error" );
}


QTEST_MAIN( TestError )
