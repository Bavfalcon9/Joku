#include "compiler/lex/Tokenize.h"
#include "compiler/lex/TokenTypes.h"
#include "compiler/lex/Util.h"
#include <vector>
#include <iostream>
#include <optional>

using namespace joku::compiler;
using namespace joku::compiler::lexer;

Stream<Token> *joku::compiler::tokenizer::tokenize_str(char *str, int len)
{
    // Stream of chars
    Stream<char> *source_buff = Stream<char>::from_ptr(str, len);
    // who needs token streams anyway???
    // TokenStream *stream = new TokenStream();
    Stream<Token> *stream = new Stream<Token>();

    int last_pos = 0;

    while (!source_buff->is_eof())
    {
        std::optional<Token> token = std::nullopt;

        if (last_pos == source_buff->get_position())
        {
            source_buff->peek();
            printf("BUG! Forcing peek!\n");
        }

        last_pos = source_buff->get_position();

        // debug source_buff->get_position();
        printf("Line: %d = %c\n", source_buff->get_position(), *source_buff->first());

        if (
            (token = consume_whitespace(source_buff)).has_value() ||
            (token = consume_comment(source_buff)).has_value() ||
            (token = consume_op(source_buff)).has_value())
        {
            printf("Token [%s]: %s\n", token.value().get_value().c_str(), token.value().get_name().c_str());
            stream->push(token.value());
        }
        else
        {
            // we need to peek it anyway!
            char v = source_buff->peek().value();

            Token tk = Token(std::string{v}, TokenType::UNKNOWN, source_buff->get_position()-1, source_buff->get_position());
        }
    }
    return stream;
}