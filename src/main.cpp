#include <iostream>
#include "../include/parser.hpp"

int main(){
    std::string query = "SELECT * FROM USERS WHERE id = 1;";
    
    Parser parser;
    parser.parse_query(query);

    std::cout << "finished main" << std::endl;
    return EXIT_SUCCESS;
}