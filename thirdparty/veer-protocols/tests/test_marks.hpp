#include <QtTest>

class TestMarks : public QObject
{
	Q_OBJECT

private:
	Q_SLOT void testActiveDirections();
	Q_SLOT void testMarksHeaderPack();
	Q_SLOT void testMarks();
};
