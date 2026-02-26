#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include <print>

Parser::Parser(const std::string& query)
    : _lexer(query),
    curr_lookahead{_lexer.get_next_token()}
    {}

void Parser::parse_query(){

    std::print("Parsing Query...\n");

    switch (curr_lookahead){

        case TokenType::SELECT_T:
            parse_select_statement();
            break;
        case TokenType::CREATE_T:
            parse_create_statement();
            break;
        case TokenType::UPDATE_T:
            parse_update_statement();
            break;
        case TokenType::DELETE_T:
            parse_delete_statement();
            break;
    
    default:
        show_error();
        break;
    }

}

void Parser::parse_select_statement(){
    
    if (curr_lookahead == TokenType::SELECT_T){
        match(TokenType::SELECT_T);
        
        // parse_column_list();
        match(TokenType::STAR_T);

        match(TokenType::FROM_T);
        match(TokenType::IDENTIFIER_T); // usually a table name
        
        // parse_where_clause();
        match(TokenType::END_OF_FILE_T);
        return;
    }
    
    
}

void Parser::match(TokenType expected_symbol){
    if (curr_lookahead == expected_symbol){
        std::print("Successfully matched on {}\n", token_to_string(expected_symbol).c_str());
        curr_lookahead = _lexer.get_next_token();
        _lexer.increase_word_count();
    } else {
        show_error(expected_symbol);
    }
}

void Parser::show_error(std::optional<TokenType> expected_symbol){
    if (expected_symbol) {
        
        std::print("Expected {}, but saw {} instead\n", 
                                token_to_string(*expected_symbol), 
                                token_to_string(curr_lookahead));
                        
    } else {
        std::print("Unknown error occurred on word {}", _lexer.get_word_count());
    }

    exit(EXIT_FAILURE);
}


void Parser::parse_create_statement(){
    // TODO
}
void Parser::parse_update_statement(){
    // TODO
}
void Parser::parse_delete_statement(){
    // TODO
}

void Parser::parse_column_list(){
    // TODO
}

void Parser::parse_where_clause(){
    // TODO
}