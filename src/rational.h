#ifndef RATIONAL_H
#define RATIONAL_H

#include <utility>
#include <iostream>

#include <boost/smart_ptr.hpp>

#include "ffmpeg.h"

namespace av
{

using namespace std::rel_ops;
using namespace std;

class Rational;

typedef boost::shared_ptr<Rational> RationalPtr;
typedef boost::weak_ptr<Rational> RationalWPtr;


enum
{
    RationalMaxPrecision = 5
};

class Rational
{
public:
    Rational();
    Rational(int numerator, int denominator);
    Rational(const AVRational &value);
    Rational(double value, int maxPrecision = RationalMaxPrecision);

    AVRational& getValue() { return value; }
    const AVRational& getValue() const { return value; }
    void setValue(const AVRational &newValue) { value = newValue; }

    void setNumerator(int numerator) { value.num = numerator; }
    void setDenominator(int denominator) { value.den = denominator; }

    int    getNumerator() const { return value.num; }
    int    getDenominator() const { return value.den; }
    double getDouble() const { return (double)value.num / (double)value.den; }

    static Rational fromDouble(double value, int maxPrecision = RationalMaxPrecision);

    int64_t rescale(int64_t srcValue, const Rational &dstBase) const;

    void dump() const;

    bool      operator== (const Rational   &other) const;
    bool      operator<  (const Rational   &other) const;
    Rational& operator=  (const AVRational &value);
    Rational& operator=  (double value);
    Rational  operator+  (const Rational   &value);
    Rational  operator-  (const Rational   &value);
    Rational  operator*  (const Rational   &value);
    Rational  operator/  (const Rational   &value);

    double    operator() () const;


private:
    AVRational value;
};


inline ostream& operator<< (ostream &stream, const Rational &value)
{
    stream << value.getNumerator() << "/" << value.getDenominator();
    return stream;

}

inline istream& operator>> (istream &stream, Rational &value)
{
    char       ch;
    AVRational temp;

    try
    {
        stream >> temp.num >> ch >> temp.den;
        if (ch == '/')
        {
            value.setNumerator(temp.num);
            value.setDenominator(temp.den);
        }
    }
    catch (const exception &e)
    {}

    return stream;
}


} // ::av

#endif // RATIONAL_H