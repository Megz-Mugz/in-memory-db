#pragma once
#include <string>
#include <unordered_map>
#include <set>

using Token_str = std::string;

enum class TokenType {
    END_OF_FILE_T,
    SELECT_T,
    CREATE_T,
    UPDATE_T,
    DELETE_T,
    FROM_T,
    IDENTIFIER_T,
    STAR_T,
    WHERE_T,
    EQUALS_T,
    NOT_EQUAL,
    LESS_THAN_T,
    GREATER_THAN_T,
    GREATER_THAN_EQ_T,
    LESS_THAN_EQ_T,

    // TODO: add more here as needed
};

const std::unordered_map<Token_str, TokenType> special_symbols = {
    {"SELECT", TokenType::SELECT_T},
    {"FROM", TokenType::FROM_T},
    // TODO add more here
};

/**
 * Mainly for error reporting & debugging purposes
 */
inline std::string token_to_string(TokenType t) {
    switch (t) {
        case TokenType::END_OF_FILE_T: return "EOF";
        case TokenType::SELECT_T: return "SELECT";
        case TokenType::CREATE_T: return "CREATE";
        case TokenType::UPDATE_T: return "UPDATE";
        case TokenType::DELETE_T: return "DELETE";
        case TokenType::FROM_T: return "FROM";
        case TokenType::IDENTIFIER_T: return "IDENTIFIER";
        case TokenType::STAR_T: return "*";
        case TokenType::WHERE_T: return "WHERE";
        case TokenType::EQUALS_T: return "=";
        case TokenType::NOT_EQUAL: return "!=";
        case TokenType::LESS_THAN_T: return "<";
        case TokenType::GREATER_THAN_T: return ">";
        default: return "UNKNOWN_TOKEN";
    }
}