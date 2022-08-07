#ifndef __TOKEN_TYPES_H__
#define __TOKEN_TYPES_H__

#include "compiler/util/Stream.hpp"

namespace token_util
{
    char *get_comment(Stream<char> *stream);
    bool is_whitespace(char c);
}

#endif