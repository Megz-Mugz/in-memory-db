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

std::size_t Lexer::get_word_count(){
    return word_count;
}

void Lexer::increase_word_count(){
    word_count++;
}


TokenType Lexer::get_next_token(){

        // skip white space
        skip_whitespace();

        // match for single characters
        if (auto token = tokenize_operators()) return *token;
        
        // match for identifiers
        if (auto token = tokenize_keywords_and_identifiers()) return *token;

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

    // TODO check for * = < > or the compounds >= <= != & increment cursor
    char curr_char = _query[cursor];
    

    switch (curr_char){
        case '*':
            cursor++;
            return TokenType::STAR_T;
            
        case '=':
            cursor++;
            return TokenType::EQUALS_T;
        
        case ',':
            cursor++;
            return TokenType::COMMA_T;

        case '<':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor++;
                return TokenType::LESS_THAN_EQ_T;
            } else{
                cursor++;
                return TokenType::LESS_THAN_T;
            }

        case '>':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor++;
                return TokenType::GREATER_THAN_EQ_T;
            } else {
                cursor++;
                return TokenType::GREATER_THAN_T;
            }
            
        case '!':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor++;
                return TokenType::NOT_EQUAL;
            }
    
    default:
        return std::nullopt;
    }

    // catch all case
    return std::nullopt; 
}

std::optional<TokenType> Lexer::tokenize_keywords_and_identifiers(){

    std::size_t starting_pos{};

    // check if first character is a-z or A-Z
    if ((std::isalpha(_query[cursor]))) {
        starting_pos = cursor++;
    }

    // read until character is not alpha-numeric
    while (std::isalnum(_query[cursor])){
        cursor++;
    }

    // TODO might need the original_str later
    auto original_str = _query.substr(starting_pos, cursor - starting_pos);
    
    auto upper_str = uppercase_string(original_str);
    auto lookup = special_symbols.find(upper_str);

    if (lookup != special_symbols.end()){
        return lookup->second;
    } else {
        return TokenType::IDENTIFIER_T;
    }

    return std::nullopt;
}

std::optional<TokenType> Lexer::tokenize_strings(){
    // TODO implement later w/ where clauses
    return std::nullopt;
}


std::string Lexer::uppercase_string(const std::string& original_str){
    std::string lowercase_str = original_str;
    
    std::transform(
        lowercase_str.begin(),
        lowercase_str.end(),
        lowercase_str.begin(),
        [](unsigned char c){
            return std::toupper(c);
        }
    );
    
    return lowercase_str;
}

bool Lexer::check_cursor_bounds() {return cursor + 1 < _query.size();}