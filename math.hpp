#ifndef MATH_CORE_H
#define MATH_CORE_H

#include <iostream>
#include <cmath>

#define TO_RADIANS 3.141592 / 180
#define TO_DEGREES 180 / 3.141592

typedef char i8;
typedef short i16;
typedef int i32;
typedef long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int u64;

typedef float f32;
typedef double f64;

template<typename T>
class Vec2 {
public:
    T x, y;
    
    Vec2() {
        x = 0;
        y = 0;
    }
    
    Vec2(T _x) {
        x = _x;
        y = 0;
    }
    
    Vec2(T _x, T _y) {
        x = _x;
        y = _y;
    }
    
    T dot(const Vec2<T> &v) {
        return x * v.x + y * v.y;
    }

    T length() {
        return sqrt(dot(*this));
    }
    
    Vec2<T> rot(T _r) {
        T r = atan2(this->y, this->x) + _r * TO_RADIANS;
        T m = this->length();
        
        return Vec2<T>(cos(r) * m, sin(r) * m);
    }
    
    Vec2<T> unlit() {
        T m = length();
        if (!m) return Vec2<T>();
        return Vec2<T>(x / m, y / m);
    }
    
	T cross(const Vec2<T> &v)
	{
		return x * v.y - y * v.x;
	}
    
    Vec2<T> xy() {return Vec2<T>(x, y);}
    
    Vec2<T> yx() {return Vec2<T>(y, x);}
    
    std::string to_string() {
        return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
    
    T* to_array() {
        return this;
    }
    
    template<typename A>
    Vec2<T> operator +(const Vec2<A> &v) {return Vec2<T>(v.x + x, v.y + y);}
    Vec2<T> operator +(T v) {return Vec2<T>(v + x, v + y);}
    
    template<typename A>
    void operator +=(const Vec2<A> &v) {x += v.x;y += v.y;}
    void operator +=(T v) {x += v;y += v;}
    
    template<typename A>
    void operator -=(const Vec2<A> &v) {x -= v.x;y -= v.y;}
    void operator -=(T v) {x -= v;y -= v;}
    
    template<typename A>
    Vec2<T> operator -(const Vec2<A> &v) {return Vec2<T>(x - v.x, y - v.y);}
    Vec2<T> operator -(T v) {return Vec2<T>(x - v, y - v);}
    
    template<typename A>
    Vec2<T> operator *(Vec2<A> v) {return Vec2<T>(x * v.x, y * v.y);}
    Vec2<T> operator *(T v) {return Vec2<T>(x * v, y * v);}
    
    template<typename A>
    Vec2<T> operator /(const Vec2<A> &v) {return Vec2<T>(x / v.x, y / v.y);}
    Vec2<T>operator /(T v) {return Vec2<T>(x / v, y / v);}
    
    template<typename A>
    operator ==(const Vec2<A> &v) {return x == v.x && y == v.y;};
    
    template<typename A>
    void operator =(const Vec2<A> &v) {
        x = v.x;
        y = v.y;
    };
};

template<typename T>
class Vec3 {
public:
    T x, y, z;
    
    Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }
    
    Vec3(T _x) {
        x = _x;
        y = 0;
        z = 0;
    }
    
    Vec3(T _x, T _y) {
        x = _x;
        y = _y;
        z = 0;
    }
    
    Vec3(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
    }
    
    float dot(const Vec3<T> &v) {
        return x * v.x + y * v.y + z * v.z;
    }

    float length() {
        return sqrt(dot(*this));
    }
    
    Vec3<T> rot(const Vec3<T> &_r) {
        Vec3<T> res = *this, t;
        Vec3<T> r = _r;
        r = r * TO_RADIANS;
        
        t = res;
        res.y = t.y * cos(r.x) - t.z * sin(r.x);
        res.z = t.y * sin(r.x) + t.z * cos(r.x);
        
        t = res;
        res.x = t.x * cos(r.y) + t.z * sin(r.y);
        res.z = t.z * cos(r.y) - t.x * sin(r.y);
        
        t = res;
        res.x = t.x * cos(r.z) - t.y * sin(r.z);
        res.y = t.x * sin(r.z) + t.y * cos(r.z);
        
        return res;
    }
    
    Vec3<T> unlit() {
        float m = length();
        if (!m) return Vec3<T>();
        return Vec3<T>(x / m, y / m, z / m);
    }
    
	Vec3<T> cross(const Vec3<T> &v)
	{
		return Vec3(
            y * v.z - v.y * z,
            z * v.x - v.z * x,
            x * v.y - v.x * y
        );
	}
    
    std::string to_string() {
        return "Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
    
    template<typename A>
    Vec3<T> operator +(const Vec3<A> &v) {return Vec3<T>(v.x + x, v.y + y, v.z + z);}
    Vec3<T> operator +(T v) {return Vec3<T>(v + x, v + y, v + z);}
    
    template<typename A>
    Vec3<T> operator -(const Vec3<A> &v) {return Vec3<T>(x - v.x, y - v.y, z - v.z);}
    Vec3<T> operator -(T v) {return Vec3<T>(x - v, y - v, z - v);}
    
    template<typename A>
    Vec3<T> operator *(const Vec3<A> &v) {return Vec3<T>(x * v.x, y * v.y, z * v.z);}
    Vec3<T> operator *(T v) {return Vec3<T>(x * v, y * v, z * v);}
    
    template<typename A>
    Vec3<T> operator /(const Vec3<A> &v) {return Vec3<T>(x / v.x, y / v.y, z / v.z);}
    Vec3<T>operator /(T v) {return Vec3<T>(x / v, y / v, z / v);}
    
    template<typename A>
    bool operator ==(const Vec3<A> &v) {return x == v.x && y == v.y && z == v.z;};
    bool operator ==(T v) {return x == v && y == v && z == v;};
    
    template<typename A>
    void operator =(const Vec3<A> &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    };
};

template<typename T>
class Vec4 {
public:
    T x, y, z, w;
    
    Vec4() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
    
    Vec4(T _x) {
        x = _x;
        y = 0;
        z = 0;
        w = 0;
    }
    
    Vec4(T _x, T _y) {
        x = _x;
        y = _y;
        z = 0;
        w = 0;
    }
    
    Vec4(T _x, T _y, T _z) {
        x = _x;
        y = _y;
        z = _z;
        w = 0;
    }
    
    Vec4(T _x, T _y, T _z, T _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
    
    float dot(const Vec4<T> &v) {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }

    float length() {
        return sqrt(dot(this));
    }
    
    Vec4<T> unlit() {
        float m = length();
        if (!m) return Vec4<T>();
        return Vec4<T>(x / m, y / m, z / m, w / m);
    }
    
    std::string to_string() {
        return "Vec4(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
    }
    
    template<typename A>
    Vec4<T> operator +(const Vec4<A> &v) {return Vec4<T>(v.x + x, v.y + y, v.z + z, v.w + w);}
    Vec4<T> operator +(T v) {return Vec4<T>(v + x, v + y, v + z, v + z, v + w);}
    
    template<typename A>
    Vec4<T> operator -(const Vec4<A> &v) {return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);}
    Vec4<T> operator -(T v) {return Vec4<T>(x - v, y - v, z - v, w - v);}
    
    template<typename A>
    Vec4<T> operator *(const Vec4<A> &v) {return Vec4<T>(x * v.x, y * v.y, z / v.z, w / v.w);}
    Vec4<T> operator *(T v) {return Vec4<T>(x * v, y * v, z * v, w * v);}
    
    template<typename A>
    Vec4<T> operator /(const Vec4<A> &v) {return Vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);}
    Vec4<T>operator /(T v) {return Vec4<T>(x / v, y / v, z / v, w / v);}
    
    template<typename A>
    operator ==(const Vec4<A> &v) {return x == v.x && y == v.y && z == v.z && w == v.w;};
    operator ==(T v) {return x == v && y == v && z == v && w == v;};
    
    template<typename A>
    void operator =(const Vec4<A> &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    };
};

class Ray {
public:
    static bool CULLING;
    static bool EPSILON;
    
    Vec3<f32> origin;
    Vec3<f32> direction;
    
    Ray(Vec3<f32> origin, Vec3<f32> direction);
    
    std::string to_string();
    
    Vec3<f32>* intersect_triangle(Vec3<f32> a, Vec3<f32> b, Vec3<f32> c);
};

#endif // MATH_CORE_H