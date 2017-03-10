#include "JzJson.h"
#include <cstdio>
#include <cstdlib>

using namespace JzJson;
using namespace std;

namespace
{
    int main_ret = 0;    // return value of main function
    int test_count = 0;  // counter of test cases
    int test_pass = 0;   // number of cases that pass the test
}

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do \
    { \
        ++test_count; \
        if (equality) \
        { \
            ++test_pass; \
        } \
        else \
        { \
            fprintf(stderr \
                , "%s:%d: expect: " format " actual: " format "\n" \
                , __FILE__ \
                , __LINE__ \
                , expect \
                , actual); \
            main_ret = 1; \
        } \
    } while(0)

#define EXPECT_EQ_INT(expect, actual) \
    EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

void TestParseNull()
{
    Value value;
    value.type = Type::TYPE_TRUE;
    EXPECT_EQ_INT(ParseReturnCode::PARSE_OK, Parse(&value, "null"));
    EXPECT_EQ_INT(Type::TYPE_NULL, GetType(&value));
}

void TestParse()
{
    TestParseNull();
}

int main(int argc, char* argv[])
{
    TestParse();
    printf("%d/%d (%3.2f%%) passed\n"
        , test_pass
        , test_count
        , test_pass * 100.0 / test_count);

    system("pause");
    return main_ret;
}