#include <iostream>
#include "../include/parser.hpp"
#include "../include/database.hpp"
#include <print>

int main(){
    
    std::string query = "  select * from users";
    
    Parser parser(query);
    Database db;
    parser.parse_query();

    std::print("Query Successfully executed\n");
    return EXIT_SUCCESS;
}