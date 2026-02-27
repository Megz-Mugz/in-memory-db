#include "../include/parser.hpp"
#include "../include/lexer.hpp"
#include <print>

Parser::Parser(const std::string& query)
    : _lexer(query),
    curr_lookahead{_lexer.get_next_token().first}
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
        parse_column_list();
        match(TokenType::FROM_T);
        match(TokenType::IDENTIFIER_T); // usually a table name
        
        parse_where_clause();
    }
    
    
}

void Parser::match(TokenType expected_symbol){
    if (curr_lookahead == expected_symbol){
        // TODO just for debugging purposes while developing
        std::print("Successfully matched on <{} -> {}>\n", 
            token_to_string(expected_symbol), 
            _lexer.get_current_lexeme());

        curr_lookahead = _lexer.get_next_token().first;
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
        std::print("Unknown error occurred on word {}\n", _lexer.get_word_count());
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
    if (curr_lookahead == TokenType::STAR_T){
        match(TokenType::STAR_T);
    } else if (curr_lookahead == TokenType::IDENTIFIER_T){
        match(TokenType::IDENTIFIER_T);
        parse_column_list_helper();
    } else {
        return show_error();
    }
}

void Parser::parse_where_clause(){
    // TODO
}

/**
 * Helper method for parsing the column list, used to eliminate a common prefix with id , 
 */
void Parser::parse_column_list_helper(){

    if (curr_lookahead == TokenType::COMMA_T){
        match(TokenType::COMMA_T);
        match(TokenType::IDENTIFIER_T);
        parse_column_list_helper();
    // epsilon state transition
    } else if (curr_lookahead == TokenType::FROM_T){
        return;
    } else {
        show_error();
    }
}


TokenType Parser::get_curr_lookahead(void){
    return curr_lookahead;
}