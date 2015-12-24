#pragma once
#include <iostream>


class vec {
public:
    vec();
    vec(double* a);
    vec(double a, double b, double c);

    vec operator+(vec x);
    vec operator+(double a);
    vec operator*(double a);
    double operator[](int i);
    friend vec operator+(double a, vec x);
    friend vec operator*(double a, vec x);
    friend std::ostream& operator<<(std::ostream& os, vec a);

    void setData(double* data);
    double computeLengthSquared(vec a);

private:
    double* data;

    double* getData();


};
