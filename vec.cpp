#include "vec.h"

using std::cout;
using std::endl;

vec::vec() {
    m_data = new double[3];
    m_data[0] = 0;
    m_data[1] = 0;
    m_data[2] = 0;
}

vec::vec(std::vector<double> a) {
    m_data = new double[3];
    m_data[0] = at(a,0);
    m_data[1] = at(a,1);
    m_data[2] = at(a,2);
}

vec::vec(double a, double b, double c) {
    m_data = new double[3];
    m_data[0] = a;
    m_data[1] = b;
    m_data[2] = c;
}



vec::vec(double* a) {
    m_data = new double[3];
    m_data[0] = a[0];
    m_data[1] = a[1];
    m_data[2] = a[2];
}

vec::vec(double a) {
    m_data = new double[3];
    m_data[0] = a;
    m_data[1] = a;
    m_data[2] = a;
}

vec vec::operator+(vec x) {
    vec result = vec(m_data);
    double* resultData = new double[3];

    double* xData = x.getData();
    for (int i = 0; i < 3; i++) {
        resultData[i] = m_data[i] + xData[i];
    }
    result.setData(resultData);
    //delete [] resultData;
    return result;
}

vec operator*(double a, vec x) {
    return x.operator *(a);
}

vec vec::operator+(double a) {
    vec result = vec(m_data);
    double* resultData = new double[3];

    for (int i=0; i < 3;i++) {
        resultData[i] = m_data[i] + a;
    }
    result.setData(resultData);
    //delete [] resultData;
    return result;
}

vec operator+(double a, vec x) {
    return x.operator +(a);
}

vec vec::operator*(double a) {
    vec result = vec(m_data);
    double* resultData = new double[3];

    for (int i=0; i < 3; i++) {
        resultData[i] = m_data[i]*a;
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
    //delete [] m_data;
    m_data = new double[3];

    for (int i=0; i<3; i++) {
        m_data[i] = xData[i];
    }

}

void vec::set(double a, int index) {
    m_data[index] = a;
}

double vec::operator[](int i) {
    return m_data[i];
}



std::ostream& operator<<(std::ostream& os, vec a) {
    double* data = a.getData();
    os << "["  << data[0] << ", " << data[1]
       << ", " << data[2] << "]";
    return os;
}

void vec::setData(double* data) {
    m_data = data;
}

void vec::setX(double x) {
    m_data[0] = x;
}

void vec::setY(double y) {
    m_data[1] = y;
}

void vec::setZ(double z) {
    m_data[2] = z;
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
    double* x = m_data;
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
    double* x = m_data;
    double* y = a.getData();

    double lengthSquared = 0;
    for (int i = 0; i < 3; i++) {
        lengthSquared += (x[i]-y[i])*(x[i]-y[i]);
    }
    return lengthSquared;
}



double vec::computeLengthSquared() {
    return m_data[0]*m_data[0] +
           m_data[1]*m_data[1] +
           m_data[2]*m_data[2];
    //return m_computeLengthSquared(vec());
}


double* vec::getData() {
    return m_data;
}



