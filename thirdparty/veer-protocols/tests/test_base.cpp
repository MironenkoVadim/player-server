#include "test_base.hpp"

#include <veer/protocols/base/header.hpp>

#include <QDebug>

namespace TC  = veer::types::common;
namespace PB  = veer::protocols::base;
namespace PBC = veer::protocols::base::constants;

void TestBase::testDataStream()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	PB::Header bhIn;

	// Проверка инициализации по умолчанию
	QVERIFY( bhIn.marker()      == PBC::HeaderMarker );
	QVERIFY( bhIn.baseVersion() == PBC::HeaderInfoVersion );
	QVERIFY( bhIn.type()        == TC::CodogramType::Undefined );
	QVERIFY( bhIn.size()        == sizeof( PB::Header ) );
	QVERIFY( bhIn.source()      == TC::Application::Any );
	QVERIFY( bhIn.destination() == TC::Application::Any );
	QVERIFY( bhIn.dataSize()    == 0 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << bhIn;
	ds.device()->reset();

	PB::Header bhOut;

	// Полная чистка структуры
	char* eraser = reinterpret_cast< char* >( &bhOut );
	memset( eraser, 0, sizeof( bhOut ) );

	QVERIFY( bhOut.marker()      == 0 );
	QVERIFY( bhOut.baseVersion() == 0 );
	QVERIFY( bhOut.type()        == TC::CodogramType::Zero );
	QVERIFY( bhOut.size()        == sizeof( PB::Header ) );
	QVERIFY( bhOut.source()      == TC::Application::None );
	QVERIFY( bhOut.destination() == TC::Application::None );
	QVERIFY( bhOut.dataSize()    == 0 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> bhOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	// Проверка на соответствие оригиналу
	QVERIFY( bhOut.marker()      == bhIn.marker() );
	QVERIFY( bhOut.baseVersion() == bhIn.baseVersion() );
	QVERIFY( bhOut.type()        == bhIn.type() );
	QVERIFY( bhOut.size()        == bhIn.size() );
	QVERIFY( bhOut.source()      == bhIn.source() );
	QVERIFY( bhOut.destination() == bhIn.destination() );
	QVERIFY( bhOut.dataSize()    == bhIn.dataSize() );
} // TestBase::testDataStream


QTEST_MAIN( TestBase )
