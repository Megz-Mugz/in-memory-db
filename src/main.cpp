#include <iostream>
#include "../include/parser.hpp"
#include "../include/database.hpp"

int main(){
    
    std::string query = "SELECT * FROM USERS WHERE id = 1;";
    
    Parser parser;
    Database db;
    parser.parse_query(query);

    if (parser.curr_lookahead == TokenType::END_OF_FILE_T){
        db.execute_query();
    } else {
        return EXIT_FAILURE;
    }

    std::cout << "Query Successfully executed" << std::endl;
    return EXIT_SUCCESS;
}