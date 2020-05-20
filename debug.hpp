#ifndef DEBUG_CORE_H
#define DEBUG_CORE_H

#include "math.hpp"

#include <iostream>
#include <chrono>

inline std::string _to_string(std::string v) {return v;}

inline std::string _to_string(char v) {return std::string(1, v);}
inline std::string _to_string(char* v) {return v;}
inline std::string _to_string(const char* v) {return v;}
inline std::string _to_string(short v) {return std::to_string(v);}
inline std::string _to_string(int v) {return std::to_string(v);}
inline std::string _to_string(long int v) {return std::to_string(v);}
inline std::string _to_string(long long int v) {return std::to_string(v);}

inline std::string _to_string(unsigned char v) {return std::to_string(v);}
inline std::string _to_string(unsigned short v) {return std::to_string(v);}
inline std::string _to_string(unsigned int v) {return std::to_string(v);}
inline std::string _to_string(unsigned long int v) {return std::to_string(v);}
inline std::string _to_string(unsigned long long int v) {return std::to_string(v);}

inline std::string _to_string(float v) {return std::to_string(v);}
inline std::string _to_string(double v) {return std::to_string(v);}

inline std::string _to_string(bool v) {return std::to_string(v);}

template<typename T> 
inline std::string _to_string(Vec2<T> v) {return v.to_string();}

template<typename T> 
inline std::string _to_string(Vec3<T> v) {return v.to_string();}

template<typename T> 
inline std::string _to_string(Vec4<T> v) {return v.to_string();}

template<typename T> 
inline std::string _to_string(T o) {return o.to_string();}

inline void print() {}

template<typename T>
void print(T t) {
    std::cout << _to_string(t);
}

template<typename T, typename... A>
void print(T t, A... a) {
    print(t);
    std::cout << " ";
    print(a...);
}

template<typename... A>
inline void log(A... a) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    std::cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " - ";
    print(a..., "\n");
}

#endif // DEBUG_CORE_H