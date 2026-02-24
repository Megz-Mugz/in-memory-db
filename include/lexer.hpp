#pragma once

#include "token_type.hpp"
#include <optional>
#include <string>

class Lexer {

public:
    Lexer(const std::string& query);
    TokenType get_next_token(void);

private:

    void skip_whitespace();

    std::optional<TokenType> tokenize_operators();

    std::optional<TokenType> tokenize_keywords_and_identifiers();

    std::optional<TokenType> tokenize_strings();

    bool check_cursor_bounds();

    std::string _query;
    std::size_t word_count;
    std::size_t cursor;





};