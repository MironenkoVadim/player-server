#include <QtTest>

class TestTrack : public QObject
{
	Q_OBJECT

private:
	Q_SLOT void testTarget();
	Q_SLOT void testBaseTrack();
};
