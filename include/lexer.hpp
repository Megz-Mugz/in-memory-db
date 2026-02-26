#pragma once

#include "token_type.hpp"
#include <optional>
#include <string>

class Lexer {

public:
    Lexer(const std::string& query);
    TokenType get_next_token(void);

    // TODO if something weird breaks, adding this public function might've caused it
    std::size_t get_word_count(void);
    void increase_word_count(void);

private:

    void skip_whitespace();

    std::string uppercase_string(const std::string& original_str);

    std::optional<TokenType> tokenize_operators();

    std::optional<TokenType> tokenize_keywords_and_identifiers();

    std::optional<TokenType> tokenize_strings();

    bool check_cursor_bounds();

    std::string _query;
    std::size_t word_count;
    std::size_t cursor;





};