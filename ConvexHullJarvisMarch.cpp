#include "ConvexHullJarvisMarch.h"
#include <iostream>
using namespace std;

Number orientation(SimplePoint2D p, SimplePoint2D q, SimplePoint2D r)
{   
    Number turn = (q.y - p.y) * (r.x -q.x) - (q.x - p.x) * (r.y - q.y);
    return turn;
}

Region2D ConvexHullJarvisMarch(Point2D pointset){
    vector<SimplePoint2D> points;
    
    for(Point2D::Iterator ptr = pointset.begin(); ptr != pointset.end(); ptr++)
    {
        points.push_back(*ptr);
    }

    if(pointset.count() < 3)
    {
        return Region2D();
    }

    vector<SimplePoint2D> hull;

    int left = 0;
    for(int i = 1; i < points.size(); i++)
    {
        if(points[i].x <= points[left].x)
        {
            left = i;
        }
    }

    int p = left;
    int q = (p + 1) % points.size();
    int finish = 0;
    while(finish < 1)
    {
        hull.push_back(points[p]);
        for(int j = 0; j < points.size(); j++)
        {
            if(orientation(points[p], points[j], points[q]) > Number("0"))
            {
                q = j;
            }
            
        }
        p = q;
        if(p == left)
        {
            finish++;
        }
        q = (p + 1) % points.size();
    }

    for(int k=0; k<hull.size(); k++){
        cout<<"("<<hull[k].x<<", "<<hull[k].y<<")"<<endl;
    }

    vector<Segment2D> hullSegments;

    for(int n=0; n<hull.size(); n++){
        if(n == hull.size()-1){
            hullSegments.push_back(Segment2D(hull[n],hull[0]));
        }
        else
        {
            hullSegments.push_back(Segment2D(hull[n],hull[n+1]));
        }
        
    }

    return Region2D(hullSegments);
}