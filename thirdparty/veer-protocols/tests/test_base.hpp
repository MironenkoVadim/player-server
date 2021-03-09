#include <QtTest>

class TestBase : public QObject
{
	Q_OBJECT

private:
	Q_SLOT void testDataStream();
};
