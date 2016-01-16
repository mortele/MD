#pragma once
#include <iostream>


class vec {
public:
    vec();
    vec(double* a);
    vec(double a);
    vec(double a, double b, double c);

    vec operator+(vec x);
    vec operator+(double a);
    vec operator*(double a);
    vec operator-(vec a);
    double operator[](int i);
    friend vec operator+(double a, vec x);
    friend vec operator*(double a, vec x);
    friend std::ostream& operator<<(std::ostream& os, vec a);

    void setData(double* data);
    void set(vec x);
    void set(double a, int index);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    double computeLengthSquared(vec a, vec systemSize);
    double computeLengthSquared(vec a);
    double computeLengthSquared();
    static vec computeLength(vec x, vec y, vec systemSize);

private:
    double* data;

    double* getData();


};
