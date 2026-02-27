#include <iostream>
#include "../include/parser.hpp"
#include "../include/database.hpp"
#include <print>

int main(){
    
    std::string query = "  SELECT name, age, dob from users";
    
    Parser parser(query);
    Database db;
    parser.parse_query(); 

    if (parser.get_curr_lookahead() == TokenType::END_OF_FILE_T){
        std::print("Query Successfully executed\n");
    } else {
        std::print("you messed up lol");
    }

    return EXIT_SUCCESS;
}