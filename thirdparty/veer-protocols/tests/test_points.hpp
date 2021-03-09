#include <QtTest>

class TestPoints : public QObject
{
	Q_OBJECT

private:
	Q_SLOT void testArrayDataStream();
	Q_SLOT void testRadarPointDataStream();
	Q_SLOT void testCartesianPointDataStream();
};
