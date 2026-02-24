#include "../include/token_type.hpp"
#include "../include/lexer.hpp"
#include <cctype>
#include <algorithm>


Lexer::Lexer(const std::string& query)
    : _query{query},
    word_count{0},
    cursor{0}
{
}

TokenType Lexer::get_next_token(){

        // skip white space
        skip_whitespace();

        // match for single characters
        if (auto token = tokenize_operators()) return *token;
        
        // match for identifiers


        // match for strings

    return TokenType::END_OF_FILE_T;
};

void Lexer::skip_whitespace(){
    if (cursor >= _query.size()) return;

    while (cursor < _query.size() && 
            std::isspace(static_cast<unsigned char>(_query[cursor]))){
        cursor++;
    }
}

std::optional<TokenType> Lexer::tokenize_operators(){
    if (cursor >= _query.size()) return std::nullopt;

    // TODO check for * = < > or the compounds >= <= != 
    char curr_char = _query[cursor];
    

    switch (curr_char){
        case STAR:
            return TokenType::STAR_T;
            break;
            
        case EQUALS:
            return TokenType::EQUALS_T;
            break;

        case LESS_THAN:
            if (check_cursor_bounds() && _query[cursor+1] == EQUALS)
                return TokenType::LESS_THAN_EQ_T;
            else
                return TokenType::LESS_THAN_T;
            break;

        case GREATER_THAN:
            if (check_cursor_bounds() && _query[cursor+1] == EQUALS)
                return TokenType::GREATER_THAN_EQ_T;
            else
                return TokenType::GREATER_THAN_T;
            break;
            
        case EXCLAMATION:
            if (check_cursor_bounds() && _query[cursor+1] == EQUALS)
                return TokenType::NOT_EQUAL;
            break;
    
    default:
        return std::nullopt;
        break;
    }
}

std::optional<TokenType> Lexer::tokenize_keywords_and_identifiers(){


    return std::nullopt;
}

std::optional<TokenType> Lexer::tokenize_strings(){

    return std::nullopt;
}

bool Lexer::check_cursor_bounds() {
    return cursor + 1 < _query.size();
}