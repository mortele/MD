#include "vec.h"

vec::vec() {
    this->data = new double[3];
    this->data[0] = 0;
    this->data[1] = 0;
    this->data[2] = 0;
}

vec::vec(double a, double b, double c) {
    this->data = new double[3];
    this->data[0] = a;
    this->data[1] = b;
    this->data[2] = c;
}

vec::vec(double* a) {
    this->data = new double[3];
    this->data[0] = a[0];
    this->data[1] = a[1];
    this->data[2] = a[2];
}

vec vec::operator+(vec x) {
    vec result = vec(this->data);
    double* resultData = new double[3];

    double* xData = x.getData();
    for (int i = 0; i < 3; i++) {
        resultData[i] = this->data[i] + xData[i];
    }
    result.setData(resultData);
    return result;
}

vec operator*(double a, vec x) {
    return x.operator *(a);
}

vec vec::operator+(double a) {
    vec result = vec(this->data);
    double* resultData = new double[3];

    for (int i=0; i < 3;i++) {
        resultData[i] = this->data[i] + a;
    }
    result.setData(resultData);
    return result;
}

vec operator+(double a, vec x) {
    return x.operator +(a);
}

vec vec::operator*(double a) {
    vec result = vec(this->data);
    double* resultData = new double[3];

    for (int i=0; i < 3; i++) {
        resultData[i] = this->data[i]*a;
    }
    result.setData(resultData);
    return result;
}

double vec::operator[](int i) {
    return this->data[i];
}



std::ostream& operator<<(std::ostream& os, vec a) {
    double* data = a.getData();
    os << "["  << data[0] << ", " << data[1]
       << ", " << data[2] << "]";
    return os;
}

void vec::setData(double* data) {
    this->data = data;
}

double vec::computeLengthSquared(vec a) {
    double* x = this->data;
    double* y = a.getData();

    double lengthSquared = 0;
    for (int i = 0; i < 3; i++) {
        lengthSquared += (x[i]-y[i])*(x[i]-y[i]);
    }
    return lengthSquared;
}

double* vec::getData() {
    return this->data;
}



