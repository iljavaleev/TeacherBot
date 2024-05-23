#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <vector>
#include "botstaff/database/psql.hpp"


const std::string URI = "postgresql://postgres:postgres@localhost:5432/cppbot"; 

namespace SQL
{
void insert_into_table(const std::string& query)
{   

    try
    {
        pqxx::connection c{URI};
        if (c.is_open())
        {
            std::cout << "db is open";
        }
        else
        {
            std::cout << "closed";
        }
        std::cout << std::endl;

        pqxx::work wrk(c);

        wrk.exec(query);
        wrk.commit();
        std::cout << "Records created successfully" << std::endl;
        c.close();

    }   
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

pqxx::result select_from_table(const std::string& query)
{   
    pqxx::result R;
    try
    {
        pqxx::connection c{URI};
        if (c.is_open())
        {
            std::cout << "db is open";
        }
        else
        {
            std::cout << "closed";
        }
        std::cout << std::endl;

        pqxx::nontransaction N(c);

        R = N.exec(query);
    
        c.close();
    }   
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return R;      
}

void update(const std::string& query)
{
    try {
        pqxx::connection C(URI);
        if (C.is_open()) 
        {
        std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } 
        else 
        {
            std::cout << "Can't open database" << std::endl;
        }
        
        
        pqxx::work W(C);
        W.exec(query);
        W.commit();
        C.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void destroy(const std::string& query)
{

    try {
        pqxx::connection C(URI);
        if (C.is_open()) 
        {
        std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } 
        else 
        {
        std::cout << "Can't open database" << std::endl;
        }
        
        
        pqxx::work W(C);
        
        W.exec(query);
        W.commit();
        C.close();
    } 
    catch (const std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
    }
}
}
