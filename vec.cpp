#include "vec.h"

using std::cout;
using std::endl;

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

vec::vec(double a) {
    this->data = new double[3];
    this->data[0] = a;
    this->data[1] = a;
    this->data[2] = a;
}

vec vec::operator+(vec x) {
    vec result = vec(this->data);
    double* resultData = new double[3];

    double* xData = x.getData();
    for (int i = 0; i < 3; i++) {
        resultData[i] = this->data[i] + xData[i];
    }
    result.setData(resultData);
    //delete [] resultData;
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
    //delete [] resultData;
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
    //delete [] resultData;
    return result;
}

vec vec::operator-(vec a) {
    double* aData = a.getData();
    return vec(-aData[0], -aData[1], -aData[2]);
}

void vec::set(vec x) {
    double* xData = x.getData();
    //delete [] this->data;
    this->data = new double[3];

    for (int i=0; i<3; i++) {
        this->data[i] = xData[i];
    }

}

void vec::set(double a, int index) {
    this->data[index] = a;
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

void vec::setX(double x) {
    this->data[0] = x;
}

void vec::setY(double y) {
    this->data[1] = y;
}

void vec::setZ(double z) {
    this->data[2] = z;
}

vec vec::computeLength(vec x, vec y, vec systemSize) {
    double* xData = x.getData();
    double* yData = y.getData();
    double* systemSizeData = systemSize.getData();
    vec     result = vec();

    for (int i=0; i<3; i++) {
        double dx = xData[i] - yData[i];
        if (dx > systemSizeData[i]/2.0) {
            dx = - systemSizeData[i] + dx;
        } else if (dx < -systemSizeData[i]/2.0) {
            dx = systemSizeData[i] + dx;
        }
        result.set(dx, i);
    }
    return result;
}


double vec::computeLengthSquared(vec a, vec systemSize) {
    double* x = this->data;
    double* y = a.getData();

    double lengthSquared = 0;
    for (int i = 0; i < 3; i++) {
        double diff = x[i]-y[i];
        if (diff > systemSize[i]/2.0) {
            diff = diff - systemSize[i]/2.0;
        }
        lengthSquared += diff*diff;
    }
    return lengthSquared;
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



double vec::computeLengthSquared() {
    return this->data[0]*this->data[0] +
           this->data[1]*this->data[1] +
           this->data[2]*this->data[2];
    //return this->computeLengthSquared(vec());
}


double* vec::getData() {
    return this->data;
}



