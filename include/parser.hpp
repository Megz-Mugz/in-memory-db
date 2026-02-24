#pragma once

#include <iostream>
#include <optional>
#include "token_type.hpp"
#include "lexer.hpp"

class Parser {
public:
    explicit Parser(const std::string& query);
    void parse_query();

private:
    Lexer _lexer;
    TokenType curr_lookahead;     

    void match(TokenType expected_symbol);
    void show_error(std::optional<TokenType> expected_symbol = std::nullopt);

    void parse_select_statement();
    void parse_create_statement();
    void parse_update_statement();
    void parse_delete_statement();

    void parse_column_list();
    void parse_where_clause();
};