//-CT::550,2008

#include "test_points.hpp"

#include <veer/types/common/points.hpp>

#include <QDebug>

namespace TC = veer::types::common;

void TestPoints::testArrayDataStream()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	TC::Array3F aIn { 0, 0, 0 };
	QVERIFY( aIn[0] == 0 );
	QVERIFY( aIn[1] == 0 );
	QVERIFY( aIn[2] == 0 );

	aIn[0] = 1;
	aIn[1] = 2;
	aIn[2] = 3;

	QVERIFY( aIn[0] == 1 );
	QVERIFY( aIn[1] == 2 );
	QVERIFY( aIn[2] == 3 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << aIn;
	ds.device()->reset();

	TC::Array3F aOut { 5, 5, 5 };
	QVERIFY( aOut[0] == 5 );
	QVERIFY( aOut[1] == 5 );
	QVERIFY( aOut[2] == 5 );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> aOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	QVERIFY( aOut[0] == aIn[0] );
	QVERIFY( aOut[1] == aIn[1] );
	QVERIFY( aOut[2] == aIn[2] );
} // TestPoints::testArrayDataStream


void TestPoints::testRadarPointDataStream()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	TC::Array3F array { 8, 8, 8 };

	TC::RadarPoint3F rpIn;

	rpIn.setArray( array );

	QVERIFY( rpIn.r()  == array[0] );
	QVERIFY( rpIn.az() == array[1] );
	QVERIFY( rpIn.el() == array[2] );

	rpIn = { 9, 9, 9 };

	QVERIFY( rpIn.r()  == 9 );
	QVERIFY( rpIn.az() == 9 );
	QVERIFY( rpIn.el() == 9 );

	rpIn.setR( 1 );
	rpIn.setAz( 2 );
	rpIn.setEl( 3 );

	QVERIFY( rpIn.r()  == 1 );
	QVERIFY( rpIn.az() == 2 );
	QVERIFY( rpIn.el() == 3 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << rpIn;
	ds.device()->reset();

	TC::RadarPoint3F rpOut { 4, 4, 4 };

	rpOut.setArray( array );

	QVERIFY( rpOut.r()  == array[0] );
	QVERIFY( rpOut.az() == array[1] );
	QVERIFY( rpOut.el() == array[2] );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> rpOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	QVERIFY( rpOut.r()  ==  rpIn.r() );
	QVERIFY( rpOut.az() ==  rpIn.az() );
	QVERIFY( rpOut.el() ==  rpIn.el() );
} // TestPoints::testRadarPointDataStream


void TestPoints::testCartesianPointDataStream()
{
	QByteArray  data;
	QDataStream ds( &data, QIODevice::ReadWrite );

	TC::Array3F array { 7, 7, 7 };

	TC::CartesianPoint3F cpIn;

	cpIn.setArray( array );

	QVERIFY( cpIn.x() == array[0] );
	QVERIFY( cpIn.y() == array[1] );
	QVERIFY( cpIn.h() == array[2] );

	cpIn = { -1, -1, -1 };

	QVERIFY( cpIn.x() == -1 );
	QVERIFY( cpIn.y() == -1 );
	QVERIFY( cpIn.h() == -1 );

	cpIn.setX( 1 );
	cpIn.setY( 2 );
	cpIn.setH( 3 );

	QVERIFY( cpIn.x() == 1 );
	QVERIFY( cpIn.y() == 2 );
	QVERIFY( cpIn.h() == 3 );

	// Запись в поток и сброс указателя на начало потока для последующего чтения
	ds << cpIn;
	ds.device()->reset();

	TC::CartesianPoint3F cpOut { 2, 2, 2 };

	cpOut.setArray( array );

	QVERIFY( cpOut.x() == array[0] );
	QVERIFY( cpOut.y() == array[1] );
	QVERIFY( cpOut.h() == array[2] );

	// Чтение из потока
	#if QT_VERSION >= 50700
	ds.startTransaction();
	#endif
	ds >> cpOut;
	#if QT_VERSION >= 50700
	if ( !ds.commitTransaction() ) { QFAIL( "Can't read from QDataStream" ); }
	#endif

	QVERIFY( cpOut.x() ==  cpIn.x() );
	QVERIFY( cpOut.y() ==  cpIn.y() );
	QVERIFY( cpOut.h() ==  cpIn.h() );
} //


QTEST_MAIN( TestPoints )
