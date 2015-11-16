
#define BOOST_TEST_MAIN
#if !defined(WIN32)
    #define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "BigInt.h"


BOOST_AUTO_TEST_CASE(ADD)
{
    BigInt m1 = "1";
    BigInt m2 = "2";

    BigInt m3 = m1 + m2;
    BOOST_CHECK_EQUAL(m3.toString(), "3");
}

BOOST_AUTO_TEST_CASE(SUB)
{

    BigInt m1 = "1";
    BigInt m2 = "2";

    BigInt m3 = m2 - m1;
    BOOST_CHECK_EQUAL(m3.toString(), "1");
}
