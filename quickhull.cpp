#include "quickhull.h"

#include <QDebug>
#include <set>
#include <algorithm>

std::set<iPair> hull;

QuickHull::QuickHull(QObject *parent) : QObject(parent)
{

}

// Returns the side of point p with respect to line
// joining points p1 and p2.
int QuickHull::findSide(iPair p1, iPair p2, iPair p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
            (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

// Returns the square of distance between
// p1 and p2.
int QuickHull::dist(iPair p, iPair q)
{
    return (p.second - q.second) * (p.second - q.second) +
            (p.first - q.first) * (p.first - q.first);
}

// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int QuickHull::lineDist(iPair p1, iPair p2, iPair p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
                (p2.second - p1.second) * (p.first - p1.first));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void QuickHull::quickHull(iPair a[], int n, iPair p1, iPair p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        //hull.push_back(p1);
        //hull.push_back(p2);

        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

QVariantList QuickHull::printHull(QVariantList arg, bool side)
{

    int n = arg.size();
    if (n < 3)
    {
        qDebug() << "Convex hull not possible\n";
        return QVariantList();
    }

    iPair* a = new iPair[n];
    for(int i = 0; i < n; i++)
    {
        QList <QVariant> p = arg[i].toList();

        a[i].first = p[0].toInt();
        a[i].second = p[1].toInt();
    }

    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i=1; i<n; i++)
    {
        if (a[i].first < a[min_x].first)
            min_x = i;
        if (a[i].first > a[max_x].first)
            max_x = i;
    }

    auto myList = QVariantList{};
    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    if(side)
    {
        quickHull(a, n, a[min_x], a[max_x], 1);
        for(auto it = hull.begin(); it != hull.end(); it++)
        {
            qDebug() << it->first << ", " << it->second;
            myList << QVariant::fromValue(QVariantList{it->first, it->second});
        }
        hull.clear();
    }
    else
    {
        qDebug() << "SecondPart";
        // Recursively find convex hull points on
        // other side of line joining a[min_x] and
        // a[max_x]
        quickHull(a, n, a[min_x], a[max_x], -1);
        for(auto it = hull.begin(); it != hull.end(); it++)
        {
            qDebug() << it->first << ", " << it->second;
            myList << QVariant::fromValue(QVariantList{it->first, it->second});
        }
        hull.clear();
    }

    delete[] a;
    return myList;
}
