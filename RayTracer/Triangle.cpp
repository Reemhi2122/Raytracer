#include "Triangle.h"

bool Triangle::IsIntersect(Ray& r)
{
    // compute plane's normal
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;
    // no need to normalize
    Vec3 N = v0v1.Cross(v0v2); // N 
    //float area2 = N.length();

    // Step 1: finding P

    // check if ray and plane are parallel ?
    float NdotRayDirection = N.dot(r.m_Direction);
    if (fabs(NdotRayDirection) < 0.0001) // almost 0 
        return false; // they are parallel so they don't intersect ! 

    // compute d parameter using equation 2
    float d = N.dot(v0);

    // compute t (equation 3)
    float t = (N.dot(r.m_Origin) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind 

    // compute the intersection point using equation 1
    Vec3 P = r.m_Origin + t * r.m_Direction;

    // Step 2: inside-outside test
    Vec3 C; // vector perpendicular to triangle's plane 

    // edge 0
    Vec3 edge0 = v1 - v0;
    Vec3 vp0 = P - v0;
    C = edge0.Cross(vp0);
    if (N.dot(C) < 0) return false; // P is on the right side 

    // edge 1
    Vec3 edge1 = v2 - v1;
    Vec3 vp1 = P - v1;
    C = edge1.Cross(vp1);
    if (N.dot(C) < 0)  return false; // P is on the right side 

    // edge 2
    Vec3 edge2 = v0 - v2;
    Vec3 vp2 = P - v2;
    C = edge2.Cross(vp2);
    if (N.dot(C) < 0) return false; // P is on the right side; 

    return true; // this ray hits the triangle 
}
