#include <iostream>
#include "../include/parser.hpp"
#include "../include/database.hpp"
#include <print>

int main(){
    
    std::string query = "SELECT * FROM USERS WHERE id = 1;";
    
    Parser parser(query);
    Database db;
    parser.parse_query();

    std::print("Query Successfully executed\n");
    return EXIT_SUCCESS;
}