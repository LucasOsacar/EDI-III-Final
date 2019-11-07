/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#ifdef __unix__
    #include "sqlite3.h" // require sqlite3 install on GNU/LINUX
#elif __APPLE__
    #include "sqlite3.h"
#elif defined(_WIN32) || defined(WIN32)
    #include "sqlite3.h"
#endif // defined

#include "IDatabaseHandler.h"

typedef std::shared_ptr<IDatabaseHandler> IDatabaseHandlerPtr;

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class SqliteDatabaseHandler : public IDatabaseHandler
{
    private:
        sqlite3* pDB;
        sqlite3_stmt* stmt;
        bool errorStatus;
        Row row;
        Table table;
        std::string columnName;
        std::string columnValue;
        int columnCount;

    public:
        SqliteDatabaseHandler()
        {
            errorStatus = false;
            std::string path = "./test.db";

            int iReturn = sqlite3_open(path.c_str(), &pDB);
            if (iReturn != SQLITE_OK) 
            {  
                errorStatus = true;
                std::cerr << "Error open DB " << sqlite3_errmsg(pDB) << std::endl; 
                exit(-1);
            }
            stmt = nullptr;
        }
        
        ~SqliteDatabaseHandler()
        {
            sqlite3_finalize(stmt);
            sqlite3_close(pDB);
        }
        
        bool getErrorStatus()
        { 
            return this->errorStatus; 
        } 

        void prepareQuery( std::string query )
        {
            int iReturn = sqlite3_prepare_v2(pDB, query.c_str(), query.size() + 1, &stmt, 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; sqlite3_close(pDB); exit(-1); }
        }

        void addParameter( int index, std::string value )
        {
            int iReturn = sqlite3_bind_text(stmt, index, value.c_str(), value.size(), 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; exit(-1); }
        }

        void execute()
        {
            //sqlite3_reset(stmt);
            //sqlite3_clear_bindings(stmt);
            sqlite3_step(stmt);
        }

        Row fetch()
        {
            row.clear();
            sqlite3_step(stmt);
            columnCount = sqlite3_column_count(stmt);
            for( int i = 0; i < columnCount; i++ )
            {
                columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                row[columnName] = columnValue;           
            }   
            return row; 
        }

        Table fetchAll()
        {
            table.clear();
            row.clear();
            columnCount = sqlite3_column_count(stmt);
            while(sqlite3_step(stmt)==SQLITE_ROW)
            {
                row.clear();
                for( int i = 0; i < columnCount; i++ )
                {
                    columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                    columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                    row[columnName] = columnValue;
                } 
                table.push_back(row);
            }

            return table;
        }
};
extern "C" IDatabaseHandlerPtr create(std::string);

IDatabaseHandlerPtr create(std::string typeinfo)
{
	/*PARA QUE SE ENTIENDA EL IF LÓGICO ES LO MISMO:*/
	// if ( typeid(TestInterface).name() == typeinfo ) return std::make_shared<Test>();
	// return nullptr;

	/*Y TAMBIÉN ES LO MISMO:*/
	// if ( typeid(TestInterface).name() == typeinfo ) 
	// {
	// 	return std::make_shared<Test>();
	// }
	// else
	// {
	// 	return nullptr;
	// }

	return ( typeid(IDatabaseHandler).name() == typeinfo )? std::make_shared<SqliteDatabaseHandler>() : nullptr;
}
