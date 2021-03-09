#include <QtTest>

class TestError : public QObject
{
	Q_OBJECT

private:
	Q_SLOT void testDataStream();
	Q_SLOT void testString();
};
