#include "../include/parser.hpp"

Parser::Parser(){
    curr_lookahead = get_next_token();
}
void Parser::parse_query(std::string_view query) {

    std::cout << "Parsing Query..." << std::endl;

    switch (curr_lookahead){

    case TokenType::SELECT_T:
        parse_select_statement();
        break;
    // case TokenType::CREATE_T:
    //     parse_create_statement();
    //     break;
    // case TokenType::UPDATE_T:
    //     parse_update_statement();
    //     break;
    // case TokenType::DELETE_T:
    //     parse_update_statement();
    //     break;
    
    default:
        show_error();
        break;
    }


}

void Parser::parse_select_statement(){
    
    if (curr_lookahead == TokenType::SELECT_T){
        match(TokenType::SELECT_T);
        // parse_column_list();
        // match(TokenType::FROM_T);
        // match(TokenType::IDENTIFIER_T);
        // parse_where_clause();
        return;
    }
    
    
}

void Parser::match(TokenType expected_symbol) {
    if (curr_lookahead == expected_symbol){
        printf("Successfully matched on %s\n", token_to_string(expected_symbol));
        curr_lookahead = get_next_token();
    } else {
        show_error(expected_symbol);
    }
}


TokenType Parser::get_next_token() {
    // TODO build out lexer
    return TokenType::SELECT_T;
}

void Parser::show_error(std::optional<TokenType> expected_symbol) {
    if (expected_symbol) {
        printf("Expected %s\n", token_to_string(*expected_symbol));
    }
}