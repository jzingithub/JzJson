#pragma once

namespace JzJson
{
    enum class Type
    {
        TYPE_NULL = 0,
        TYPE_FALSE,
        TYPE_TRUE,
        TYPE_NUMBER,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_OBJECT
    };

    enum class ParseReturnCode
    {
        PARSE_OK = 0,
        PARSE_EXPECT_VALUE,
        PARSE_INVALID_VALUE,
        PARSE_ROOT_NOT_SINGULAR
    };

    struct Value
    {
        Type type;
    };

    // Reduce the number of parameters passed between parser functions
    struct Context
    {
        const char* json = nullptr;
    };

    ParseReturnCode Parse(Value* value, const char* json);

    Type GetType(const Value* value);
}