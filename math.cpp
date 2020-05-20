#include "math.hpp"

bool Ray::CULLING = true;
bool Ray::EPSILON = 0.000001;

Ray::Ray(Vec3<f32> origin, Vec3<f32> direction) {
    this->origin = origin;
    this->direction = direction;
}

std::string Ray::to_string() {
    return "Ray(origin=" + origin.to_string() + ", position=" + origin.to_string() + ")";
}

Vec3<f32>* Ray::intersect_triangle(Vec3<f32> a, Vec3<f32> b, Vec3<f32> c) {
    Vec3<f32> edge1 = b - a;
    Vec3<f32> edge2 = c - a;
    
    Vec3<f32> pvec = direction.cross(edge2);
    float det = edge1.dot(pvec);
    
    if (Ray::CULLING) {
        if (det < Ray::EPSILON) {
            return nullptr;
        }
    }
    else {
        if (fabs(det) < Ray::EPSILON) {
            return nullptr;
        }
    }
    
    Vec3<f32> tvec = origin - a;
    float u = tvec.dot(pvec);
    
    if (u < 0 || u > det) {
        return nullptr;
    }
    
    Vec3<f32> qvec = tvec.cross(edge1);
    float v = direction.dot(qvec);
    
    if (v < 0 || u + v > det) {
        return nullptr;
    }
    
    float t = edge2.dot(qvec) / det;
    Vec3<f32> out = origin + direction * t;
    return new Vec3<f32>(out.x, out.y, out.z);
}
