#include "vec.h"

using std::cout;
using std::endl;

vec::vec() {
    m_data = new real[3];
    m_data[0] = 0;
    m_data[1] = 0;
    m_data[2] = 0;
}

vec::vec(std::vector<real> a) {
    m_data = new real[3];
    m_data[0] = at(a,0);
    m_data[1] = at(a,1);
    m_data[2] = at(a,2);
}

vec::vec(real a, real b, real c) {
    m_data = new real[3];
    m_data[0] = a;
    m_data[1] = b;
    m_data[2] = c;
}



vec::vec(real* a) {
    m_data = new real[3];
    m_data[0] = a[0];
    m_data[1] = a[1];
    m_data[2] = a[2];
}

vec::vec(real a) {
    m_data = new real[3];
    m_data[0] = a;
    m_data[1] = a;
    m_data[2] = a;
}

vec vec::operator+(vec x) {
    vec result = vec(m_data);
    real* resultData = new real[3];

    real* xData = x.getData();
    for (int i = 0; i < 3; i++) {
        resultData[i] = m_data[i] + xData[i];
    }
    result.setData(resultData);
    //delete [] resultData;
    return result;
}

vec operator*(real a, vec x) {
    return x.operator *(a);
}

vec vec::operator+(real a) {
    vec result = vec(m_data);
    real* resultData = new real[3];

    for (int i=0; i < 3;i++) {
        resultData[i] = m_data[i] + a;
    }
    result.setData(resultData);
    //delete [] resultData;
    return result;
}

vec operator+(real a, vec x) {
    return x.operator +(a);
}

vec vec::operator*(real a) {
    vec result = vec(m_data);
    real* resultData = new real[3];

    for (int i=0; i < 3; i++) {
        resultData[i] = m_data[i]*a;
    }
    result.setData(resultData);
    //delete [] resultData;
    return result;
}

vec vec::operator-(vec a) {
    real* aData = a.getData();
    return vec(-aData[0], -aData[1], -aData[2]);
}

void vec::set(vec x) {
    real* xData = x.getData();
    //delete [] m_data;
    m_data = new real[3];

    for (int i=0; i<3; i++) {
        m_data[i] = xData[i];
    }

}

void vec::set(real a, int index) {
    m_data[index] = a;
}

real vec::operator[](int i) {
    return m_data[i];
}



std::ostream& operator<<(std::ostream& os, vec a) {
    real* data = a.getData();
    os << "["  << data[0] << ", " << data[1]
       << ", " << data[2] << "]";
    return os;
}

void vec::setData(real* data) {
    m_data = data;
}

void vec::setX(real x) {
    m_data[0] = x;
}

void vec::setY(real y) {
    m_data[1] = y;
}

void vec::setZ(real z) {
    m_data[2] = z;
}

vec vec::computeLength(vec x, vec y, vec systemSize) {
    real* xData = x.getData();
    real* yData = y.getData();
    real* systemSizeData = systemSize.getData();
    vec     result = vec();

    for (int i=0; i<3; i++) {
        real dx = xData[i] - yData[i];
        if (dx > systemSizeData[i]/2.0) {
            dx = - systemSizeData[i] + dx;
        } else if (dx < -systemSizeData[i]/2.0) {
            dx = systemSizeData[i] + dx;
        }
        result.set(dx, i);
    }
    return result;
}


real vec::computeLengthSquared(vec a, vec systemSize) {
    real* x = m_data;
    real* y = a.getData();

    real lengthSquared = 0;
    for (int i = 0; i < 3; i++) {
        real diff = x[i]-y[i];
        if (diff > systemSize[i]/2.0) {
            diff = diff - systemSize[i]/2.0;
        }
        lengthSquared += diff*diff;
    }
    return lengthSquared;
}


real vec::computeLengthSquared(vec a) {
    real* x = m_data;
    real* y = a.getData();

    real lengthSquared = 0;
    for (int i = 0; i < 3; i++) {
        lengthSquared += (x[i]-y[i])*(x[i]-y[i]);
    }
    return lengthSquared;
}



real vec::computeLengthSquared() {
    return m_data[0]*m_data[0] +
           m_data[1]*m_data[1] +
           m_data[2]*m_data[2];
    //return m_computeLengthSquared(vec());
}


real* vec::getData() {
    return m_data;
}



