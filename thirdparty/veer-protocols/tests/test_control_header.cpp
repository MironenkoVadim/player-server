#include "test_control_header.hpp"

#include <veer/protocols/control/gate/header.hpp>

#include <QDebug>

namespace PC = veer::protocols::control::gate;

void TestControlHeader::testDataStream()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	PC::Header bhIn;

	// Проверка инициализации по умолчанию
	QVERIFY( bhIn.senderId()         == UINT64_MAX );
	QVERIFY( bhIn.receiverId()       == UINT64_MAX );
	QVERIFY( bhIn.messageTypeId()    == UINT64_MAX );
	QVERIFY( bhIn.messageSeqNumber() == UINT64_MAX );
	QVERIFY( bhIn.packetSize()       == UINT16_MAX );
	QVERIFY( bhIn.packetNumber()     == UINT16_MAX >> 1 );
	QVERIFY( bhIn.isLastPart()       == true );
	QVERIFY( bhIn.magic()            == UINT32_MAX );

	bhIn.setLastPart( false );
	QVERIFY( bhIn.isLastPart()       == false );
	bhIn.setPacketNumber( 1000 );
	QVERIFY( bhIn.packetNumber()     == 1000 );

	bhIn.setLastPart( true );
	QVERIFY( bhIn.isLastPart()       == true );
	bhIn.setPacketNumber( 100 );
	QVERIFY( bhIn.packetNumber()     == 100 );

	bhIn.setLastPart( false );
	QVERIFY( bhIn.isLastPart()       == false );
	bhIn.setPacketNumber( 30000 );
	QVERIFY( bhIn.packetNumber()     == 30000 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << bhIn;
	ds.device()->reset();

	PC::Header bhOut;

	// Полная чистка структуры
	char* eraser = reinterpret_cast< char* >( &bhOut );
	memset( eraser, 0, sizeof( bhOut ) );

	QVERIFY( bhOut.senderId()         == 0 );
	QVERIFY( bhOut.receiverId()       == 0 );
	QVERIFY( bhOut.messageTypeId()    == 0 );
	QVERIFY( bhOut.messageSeqNumber() == 0 );
	QVERIFY( bhOut.packetSize()       == 0 );
	QVERIFY( bhOut.packetNumber()     == 0 );
	QVERIFY( bhOut.isLastPart()       == false );
	QVERIFY( bhOut.magic()            == 0 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> bhOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	// Проверка на соответствие оригиналу
	QVERIFY( bhOut.senderId()         == bhIn.senderId() );
	QVERIFY( bhOut.receiverId()       == bhIn.receiverId() );
	QVERIFY( bhOut.messageTypeId()    == bhIn.messageTypeId() );
	QVERIFY( bhOut.messageSeqNumber() == bhIn.messageSeqNumber() );
	QVERIFY( bhOut.packetSize()       == bhIn.packetSize() );
	QVERIFY( bhOut.packetNumber()     == bhIn.packetNumber() );
	QVERIFY( bhOut.isLastPart()       == bhIn.isLastPart() );
	QVERIFY( bhOut.magic()            == bhIn.magic() );
} // TestControlHeader::testDataStreambhOut.senderId()


QTEST_MAIN( TestControlHeader )
