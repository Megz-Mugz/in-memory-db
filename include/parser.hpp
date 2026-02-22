#pragma once

#include <iostream>
#include "token_type.hpp"

class Parser {

public:
    Parser();
    void parse_query(std::string_view query);
    TokenType curr_lookahead;
    
private:
    void match(const TokenType expected_symbol);
    void show_error(std::optional<TokenType> expected_symbol = std::nullopt);
    void parse_select_statement();
    // void parse_create_statement();
    // void parse_update_statement();
    // void parse_update_statement();
    TokenType get_next_token();
};