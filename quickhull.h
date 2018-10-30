#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <QObject>
#include <QVector>
#include <QVariant>

#define iPair std::pair<int, int>

class QuickHull : public QObject
{
    Q_OBJECT
public:
    explicit QuickHull(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList printHull(QVariantList arg, bool side);

private:
    void quickHull(iPair a[], int n, iPair p1, iPair p2, int side);
    int lineDist(iPair p1, iPair p2, iPair p);
    int dist(iPair p, iPair q);
    int findSide(iPair p1, iPair p2, iPair p);

signals:

public slots:
};

#endif // QUICKHULL_H
