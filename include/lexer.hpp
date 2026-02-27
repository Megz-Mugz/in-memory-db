#pragma once

#include "token_type.hpp"
#include <optional>
#include <string>

class Lexer {

public:
    using Lexeme = std::string;
    using Token = std::pair<TokenType, Lexeme>;

    Lexer(const std::string& query);
    Token get_next_token(void);

    // TODO if something weird breaks, adding this public function might've caused it
    std::size_t get_word_count(void);
    void increase_word_count(void);

    Lexeme get_current_lexeme(void);
    

private:
    void skip_whitespace();
    
    std::string uppercase_string(const std::string& original_str);
    
    std::optional<Token> tokenize_operators();
    
    std::optional<Token> tokenize_keywords_and_identifiers();

    std::optional<Token> tokenize_strings();

    bool check_cursor_bounds();

    std::string _query;
    std::size_t word_count;
    std::size_t cursor;

    Lexeme current_lexeme;

    void set_current_lexeme(const Lexeme& curr_lexeme);

};