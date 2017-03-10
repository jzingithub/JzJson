#include "JzJson.h"
#include <cassert>

using namespace std;
using namespace JzJson;

inline void Expect(Context* context, char c)
{
    assert(*(context->json) == c);
    ++context->json;
}

void ParseWhiteSpace(Context* context)
{
    const char* temp_json = context->json;
    while (*temp_json == ' '
        || *temp_json == '\t'
        || *temp_json == '\r'
        || *temp_json == '\n')
    {
        ++temp_json;
    }
    context->json = temp_json;
}

ParseReturnCode ParseNull(Context* context, Value* value)
{
    Expect(context, 'n');
    if (context->json[0] != 'u'
        || context->json[1] != 'l'
        || context->json[2] != 'l')
    {
        return ParseReturnCode::PARSE_INVALID_VALUE;
    }
    context->json += 3;
    value->type = Type::TYPE_NULL;
    return ParseReturnCode::PARSE_OK;
}

ParseReturnCode ParseTrue(Context* context, Value* value)
{
    Expect(context, 't');
    if (context->json[0] != 'r'
        || context->json[1] != 'u'
        || context->json[2] != 'e')
    {
        return ParseReturnCode::PARSE_INVALID_VALUE;
    }
    context->json += 3;
    value->type = Type::TYPE_TRUE;
    return ParseReturnCode::PARSE_OK;
}

ParseReturnCode ParseFalse(Context* context, Value* value)
{
    Expect(context, 'f');
    if (context->json[0] != 'a'
        || context->json[1] != 'l'
        || context->json[2] != 's'
        || context->json[3] != 'e')
    {
        return ParseReturnCode::PARSE_INVALID_VALUE;
    }
    context->json += 4;
    value->type = Type::TYPE_FALSE;
    return ParseReturnCode::PARSE_OK;
}

ParseReturnCode ParseValue(Context* context, Value* value)
{
    switch (*(context->json))
    {
    case 'n':
        return ParseNull(context, value);
    case 't':
        return ParseTrue(context, value);
    case 'f':
        return ParseFalse(context, value);
    case '\0':
        return ParseReturnCode::PARSE_EXPECT_VALUE;
    default:
        return ParseReturnCode::PARSE_INVALID_VALUE;
    }
}

namespace JzJson
{
    ParseReturnCode Parse(Value* value, const char* json)
    {
        ParseReturnCode ret_code;
        Context context;
        assert(value != nullptr);
        context.json = json;
        value->type = Type::TYPE_NULL;
        ParseWhiteSpace(&context);
        if ((ret_code = ParseValue(&context, value))
            == ParseReturnCode::PARSE_OK)
        {
            ParseWhiteSpace(&context);
            if (*(context.json) != '\0')
            {
                ret_code = ParseReturnCode::PARSE_ROOT_NOT_SINGULAR;
            }
        }
        return ret_code;
    }

    Type GetType(const Value* value)
    {
        assert(value != nullptr);
        return value->type;
    }
}