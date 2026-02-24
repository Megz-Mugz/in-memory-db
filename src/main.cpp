#include <iostream>
#include "../include/parser.hpp"
#include "../include/database.hpp"

int main(){
    
    std::string query = "SELECT * FROM USERS WHERE id = 1;";
    
    Parser parser(query);
    Database db;
    parser.parse_query();

    std::cout << "Query Successfully executed" << std::endl;
    return EXIT_SUCCESS;
}