
#ifndef INFINT_H_
#define INFINT_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include <limits.h>
#include <stdlib.h>



//#define INFINT_USE_EXCEPTIONS
//#define INFINT_USE_SHORT_BASE

#ifdef INFINT_USE_EXCEPTIONS
#include <exception>
#endif


#ifdef INFINT_USE_SHORT_BASE // uses 10^4 (short) as the base
typedef short ELEM_TYPE;
typedef int PRODUCT_TYPE;
static const ELEM_TYPE BASE = 10000;
static const ELEM_TYPE UPPER_BOUND = 9999;
static const ELEM_TYPE DIGIT_COUNT = 4;
static const int powersOfTen[] = { 1, 10, 100, 1000};
#else // uses 10^9 (int) as the base
typedef int ELEM_TYPE;
typedef long long PRODUCT_TYPE;
static const ELEM_TYPE BASE = 1000000000;
static const ELEM_TYPE UPPER_BOUND = 999999999;
static const ELEM_TYPE DIGIT_COUNT = 9;
static const int powersOfTen[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
#endif

#ifdef INFINT_USE_EXCEPTIONS
class InfIntException: public std::exception
{
public:
    InfIntException(const std::string& txt) throw ();
    ~InfIntException() throw ();
    const char* what() const throw ();
private:
    std::string txt;
};

InfIntException::InfIntException(const std::string& txt) throw () :
std::exception(), txt(txt)
{
}

InfIntException::~InfIntException() throw ()
{
}

const char* InfIntException::what() const throw ()
{
    return txt.c_str();
}
#endif

class BigInt
{
    friend std::ostream& operator<<(std::ostream &s, const BigInt &n);
    friend std::istream& operator>>(std::istream &s, BigInt &val);

public:

    static const BigInt zero;
    static const BigInt one;
    static const BigInt two;


    BigInt();
    BigInt(const char* c);
    BigInt(const std::string& s);
    BigInt(int l);
    BigInt(long l);
    BigInt(long long l);
    BigInt(unsigned int l);
    BigInt(unsigned long l);
    BigInt(unsigned long long l);


    const BigInt & operator=(const char* c);
    const BigInt & operator=(const std::string& s);
    const BigInt & operator=(int l);
    const BigInt & operator=(long l);
    const BigInt & operator=(long long l);
    const BigInt & operator=(unsigned int l);
    const BigInt & operator=(unsigned long l);
    const BigInt & operator=(unsigned long long l);


    const BigInt & operator++();
    const BigInt & operator--();
    BigInt operator++(int);
    BigInt operator--(int);


    const BigInt & operator+=(const BigInt & rhs);
    const BigInt & operator-=(const BigInt & rhs);


    BigInt operator-() const;
    BigInt operator+(const BigInt & rhs) const;
    BigInt operator-(const BigInt & rhs) const;


    char digitAt(size_t i) const; // throw
    size_t numberOfDigits() const;

    size_t size() const;

    std::string toString() const;

private:

    void correct(bool justCheckLeadingZeros = false, bool hasValidSign = false);
    void fromString(const std::string& s);
    void truncateToBase();
    bool equalizeSigns();
    void removeLeadingZeros();

    std::vector<ELEM_TYPE> val; // number with base FACTOR
    bool pos; // true if number is positive
};

const BigInt BigInt::zero = 0;
const BigInt BigInt::one = 1;
const BigInt BigInt::two = 2;

inline BigInt::BigInt() : pos(true)
{
    val.push_back((ELEM_TYPE) 0);
}

inline BigInt::BigInt(const char* c)
{
    fromString(c);
}

inline BigInt::BigInt(const std::string& s)
{
    fromString(s);
}

inline BigInt::BigInt(int l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}

inline BigInt::BigInt(long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
}

inline BigInt::BigInt(long long l) : pos(l >= 0)
{
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef _WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
}

inline BigInt::BigInt(unsigned int l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline BigInt::BigInt(unsigned long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline BigInt::BigInt(unsigned long long l) : pos(true)
{
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
}

inline const BigInt &BigInt::operator=(const char* c)
{
    fromString(c);
    return *this;
}

inline const BigInt &BigInt::operator=(const std::string& s)
{
    fromString(s);
    return *this;
}

inline const BigInt &BigInt::operator=(int l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        div_t dt = div(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator=(long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
        ldiv_t dt = ldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator=(long long l)
{
    pos = l >= 0;
    val.clear();
    if (!pos)
    {
        l = -l;
    }
    do
    {
#ifndef _WIN32
        lldiv_t dt = lldiv(l, BASE);
        val.push_back((ELEM_TYPE) dt.rem);
        l = dt.quot;
#else
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
#endif
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator=(unsigned int l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator=(unsigned long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator=(unsigned long long l)
{
    pos = true;
    val.clear();
    do
    {
        val.push_back((ELEM_TYPE) (l % BASE));
        l = l / BASE;
    } while (l > 0);
    return *this;
}

inline const BigInt &BigInt::operator++()
{
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline const BigInt &BigInt::operator--()
{
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return *this;
}

inline BigInt BigInt::operator++(int)
{
    BigInt result = *this;
    val[0] += (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline BigInt BigInt::operator--(int)
{
    BigInt result = *this;
    val[0] -= (pos ? 1 : -1);
    this->correct(false, true);
    return result;
}

inline const BigInt &BigInt::operator+=(const BigInt & rhs)
{
    if (rhs.val.size() > val.size())
    {
        val.resize(rhs.val.size(), 0);
    }
    for (size_t i = 0; i < val.size(); ++i)
    {
        val[i] = (pos ? val[i] : -val[i]) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    correct();
    return *this;
}

inline const BigInt &BigInt::operator-=(const BigInt & rhs)
{
    if (rhs.val.size() > val.size())
    {
        val.resize(rhs.val.size(), 0);
    }
    for (size_t i = 0; i < val.size(); ++i)
    {
        val[i] = (pos ? val[i] : -val[i]) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    correct();
    return *this;
}

inline BigInt BigInt::operator-() const
{
    BigInt result = *this;
    result.pos = !pos;
    return result;
}

inline BigInt BigInt::operator+(const BigInt & rhs) const
{
    BigInt result;
    result.val.resize(val.size() > rhs.val.size() ? val.size() : rhs.val.size(), 0);
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val[i] = (i < val.size() ? (pos ? val[i] : -val[i]) : 0) + (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    result.correct();
    return result;
}

inline BigInt BigInt::operator-(const BigInt & rhs) const
{
    BigInt result;
    result.val.resize(val.size() > rhs.val.size() ? val.size() : rhs.val.size(), 0);
    for (size_t i = 0; i < val.size() || i < rhs.val.size(); ++i)
    {
        result.val[i] = (i < val.size() ? (pos ? val[i] : -val[i]) : 0) - (i < rhs.val.size() ? (rhs.pos ? rhs.val[i] : -rhs.val[i]) : 0);
    }
    result.correct();
    return result;
}



inline char BigInt::digitAt(size_t i) const
{
    if (numberOfDigits() <= i)
    {
#ifdef INFINT_USE_EXCEPTIONS
        throw InfIntException("invalid digit index");
#else
        std::cerr << "Invalid digit index: " << i << std::endl;
        return -1;
#endif
    }
    return (val[i / DIGIT_COUNT] / powersOfTen[i % DIGIT_COUNT]) % 10;
}

inline size_t BigInt::numberOfDigits() const
{
    return (val.size() - 1) * DIGIT_COUNT
#ifdef INFINT_USE_SHORT_BASE
    + (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1)));
#else
    + (val.back() > 99999999 ? 9 : (val.back() > 9999999 ? 8 : (val.back() > 999999 ? 7 : (val.back() > 99999 ? 6 :
                                                                                           (val.back() > 9999 ? 5 : (val.back() > 999 ? 4 : (val.back() > 99 ? 3 : (val.back() > 9 ? 2 : 1))))))));
#endif
}

inline std::string BigInt::toString() const
{
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

inline size_t BigInt::size() const
{
    return val.size() * sizeof(ELEM_TYPE) + sizeof(bool);
}

inline void BigInt::truncateToBase()
{
    for (size_t i = 0; i < val.size(); ++i) // truncate each
    {
        if (val[i] >= BASE || val[i] <= -BASE)
        {
            div_t dt = div(val[i], BASE);
            val[i] = dt.rem;
            if (i + 1 >= val.size())
            {
                val.push_back(dt.quot);
            }
            else
            {
                val[i + 1] += dt.quot;
            }
        }
    }
}

inline bool BigInt::equalizeSigns()
{
    bool isPositive = true;
    int i = (int) ((val.size())) - 1;
    for (; i >= 0; --i)
    {
        if (val[i] != 0)
        {
            isPositive = val[i--] > 0;
            break;
        }
    }

    if (isPositive)
    {
        for (; i >= 0; --i)
        {
            if (val[i] < 0)
            {
                int k = 0, index = i + 1;
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); // count adjacent zeros on left
                //if ((size_t)(index) < val.size() && val[index] > 0)
                { // number on the left is positive
                    val[index] -= 1;
                    val[i] += BASE;
                    for (; k > 0; --k)
                    {
                        val[i + k] = UPPER_BOUND;
                    }
                }
            }
        }
    }
    else
    {
        for (; i >= 0; --i)
        {
            if (val[i] > 0)
            {
                int k = 0, index = i + 1;
                for (; (size_t)(index) < val.size() && val[index] == 0; ++k, ++index); // count adjacent zeros on right
                //if ((size_t)(index) < val.size() && val[index] < 0)
                { // number on the left is negative
                    val[index] += 1;
                    val[i] -= BASE;
                    for (; k > 0; --k)
                    {
                        val[i + k] = -UPPER_BOUND;
                    }
                }
            }
        }
    }

    return isPositive;
}

inline void BigInt::removeLeadingZeros()
{
    for (int i = (int) (val.size()) - 1; i > 0; --i) // remove leading 0's
    {
        if (val[i] != 0)
        {
            return;
        }
        else
        {
            val.erase(val.begin() + i);
        }
    }
}

inline void BigInt::correct(bool justCheckLeadingZeros, bool hasValidSign)
{
    if (!justCheckLeadingZeros)
    {
        truncateToBase();
        
        if (equalizeSigns())
        {
            pos = ((val.size() == 1 && val[0] == 0) || !hasValidSign) ? true : pos;
        }
        else
        {
            pos = hasValidSign ? !pos : false;
            for (size_t i = 0; i < val.size(); ++i)
            {
                val[i] = abs(val[i]);
            }
        }
    }
    
    removeLeadingZeros();
}

inline void BigInt::fromString(const std::string& s)
{
    pos = true;
    val.clear();
    val.reserve(s.size() / DIGIT_COUNT + 1);
    int i = (int) s.size() - DIGIT_COUNT;
    for (; i >= 0; i -= DIGIT_COUNT)
    {
        val.push_back(atoi(s.substr(i, DIGIT_COUNT).c_str()));
    }
    if (i > -DIGIT_COUNT)
    {
        std::string ss = s.substr(0, i + DIGIT_COUNT);
        if (ss.size() == 1 && ss[0] == '-')
        {
            pos = false;
        }
        else
        {
            val.push_back(atoi(ss.c_str()));
        }
    }
    if (val.back() < 0)
    {
        val.back() = -val.back();
        pos = false;
    }
    correct(true);
}



inline std::istream& operator>>(std::istream &s, BigInt &n)
{
    std::string str;
    s >> str;
    n.fromString(str);
    return s;
}

inline std::ostream& operator<<(std::ostream &s, const BigInt &n)
{
    if (!n.pos)
    {
        s << '-';
    }
    bool first = true;
    for (int i = (int) n.val.size() - 1; i >= 0; --i)
    {
        if (first)
        {
            s << n.val[i];
            first = false;
        }
        else
        {
            s << std::setfill('0') << std::setw(DIGIT_COUNT) << n.val[i];
        }
    }
    return s;
}

#endif
