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
    GREATER_THAN_T
    // TODO: add more here as needed
};



inline const char* token_to_string(TokenType token) {
    switch (token) {
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