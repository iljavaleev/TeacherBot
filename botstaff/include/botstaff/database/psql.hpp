#ifndef psql_h
#define psql_h
#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>

namespace SQL
{
pqxx::result insert_into_table(const std::string&);

void update(const std::string&);

pqxx::result select_from_table(const std::string&);

void destroy(const std::string&);
}


#endif 
