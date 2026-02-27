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


Lexer::Token Lexer::get_next_token(){

        // skip white space
        skip_whitespace();

        // match for special characters/symbols
        if (auto token = tokenize_operators()){
            set_current_lexeme((*token).second);
            return *token;
        } 
        
        // match for keywords & identifiers
        if (auto token = tokenize_keywords_and_identifiers()){
            set_current_lexeme((*token).second);
            return *token;
        } 

        // match for strings
        if (auto token = tokenize_strings()){
            set_current_lexeme((*token).second);
            return *token;
        }
    
    // similar to other flavors of SQL, putting a semicolon won't be mandated by the language
    return Token{TokenType::END_OF_FILE_T, "$"}; 
};

void Lexer::skip_whitespace(){
    if (cursor >= _query.size()) return;

    while (cursor < _query.size() && 
            std::isspace(static_cast<unsigned char>(_query[cursor]))){
        cursor++;
    }
}

std::optional<Lexer::Token> Lexer::tokenize_operators(){
    if (cursor >= _query.size()) return std::nullopt;

    // TODO check for * = < > or the compounds >= <= != & increment cursor
    char curr_char = _query[cursor];
    

    switch (curr_char){
        case '*':
            cursor++;
            set_current_lexeme("*");
            return Token{TokenType::STAR_T, "*"};
            
        case '=':
            cursor++;
            set_current_lexeme("=");
            return Token{TokenType::EQUALS_T, "="};
        
        case ',':
            cursor++;
            set_current_lexeme(",");
            return Token{TokenType::COMMA_T, ","};

        case '<':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor+=2;
                set_current_lexeme("<=");
                return Token{TokenType::LESS_THAN_EQ_T, "<="};
            } else{
                cursor+=2;
                set_current_lexeme("<");
                return Token{TokenType::LESS_THAN_T, "<"};
            }

        case '>':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor+=2;
                set_current_lexeme(">=");
                return Token{TokenType::GREATER_THAN_EQ_T, ">="};
            } else {
                cursor+=2;
                set_current_lexeme(">");
                return Token{TokenType::GREATER_THAN_T, ">"};
            }
            
        case '!':
            if (check_cursor_bounds() && _query[cursor+1] == '='){
                cursor+=2;
                set_current_lexeme("!=");
                return Token{TokenType::NOT_EQUAL, "!="};
            }
        
    default:
        return std::nullopt;
    }

    // catch all case
    return std::nullopt; 
}

std::optional<Lexer::Token> Lexer::tokenize_keywords_and_identifiers(){

    std::optional<std::size_t> starting_pos{};

    // check if first character is a-z or A-Z
    if (cursor < _query.size() && (std::isalpha(_query[cursor]))) {
        starting_pos = cursor++;
    }

    // read until character is not alpha-numeric
    while (cursor < _query.size() && std::isalnum(_query[cursor])){
        cursor++;
    }

    if (starting_pos.has_value()){
        auto original_str = _query.substr(*starting_pos, cursor - *starting_pos);
    
        auto upper_str = uppercase_string(original_str);
        auto lookup = special_symbols.find(upper_str);

        if (lookup != special_symbols.end()){
            return Token{lookup->second, lookup->first};
        }
        return Token{TokenType::IDENTIFIER_T, original_str};
    }
    

    return std::nullopt;
}

std::optional<Lexer::Token> Lexer::tokenize_strings(){
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

Lexer::Lexeme Lexer::get_current_lexeme(void){
    return current_lexeme;
}

void Lexer::set_current_lexeme(const Lexer::Lexeme& curr_lexeme){
    current_lexeme = curr_lexeme;
}