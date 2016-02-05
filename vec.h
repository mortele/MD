#pragma once
#include <iostream>
#include <vector>

typedef double real;

template <typename T>
T& at(std::vector<T> &vec, int index) {
    //return vec.at(index);
    return vec[index];
}


class vec {
public:
    vec();
    vec(std::vector<real> a);
    vec(real* a);
    vec(real a);
    vec(real a, real b, real c);

    vec operator+(vec x);
    vec operator+(real a);
    vec operator*(real a);
    vec operator-(vec a);
    real operator[](int i);
    friend vec operator+(real a, vec x);
    friend vec operator*(real a, vec x);
    friend std::ostream& operator<<(std::ostream& os, vec a);

    void setData(real* data);
    void set(vec x);
    void set(real a, int index);
    void setX(real x);
    void setY(real y);
    void setZ(real z);
    real computeLengthSquared(vec a, vec systemSize);
    real computeLengthSquared(vec a);
    real computeLengthSquared();
    static vec computeLength(vec x, vec y, vec systemSize);

private:
    real* m_data = nullptr;
    //real m_data[3];

    real* getData();


};
