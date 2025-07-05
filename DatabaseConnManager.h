#pragma once

#include <string>

#include "nanodbc/nanodbc.h"

namespace DatabaseConnManager
{
    // private namespace to prevent direct access of static variables
    namespace
    {
        std::string ACCOUNT_DSN_NAME;
        std::string ACCOUNT_DSN_USER;
        std::string ACCOUNT_DSN_PASS;
    
        std::string GAME_DSN_NAME;
        std::string GAME_DSN_USER;
        std::string GAME_DSN_PASS;
    
        std::string LOG_DSN_NAME;
        std::string LOG_DSN_USER;
        std::string LOG_DSN_PASS;
    }
    
    // Get a connection to the database using the code-generated DbType enum.  Can throw an exception
    static nanodbc::connection GetConnectionTo(const std::string& databaseType) noexcept(false)
    {
        if (databaseType == "ACCOUNT")
        {
            return nanodbc::connection(ACCOUNT_DSN_NAME, ACCOUNT_DSN_USER, ACCOUNT_DSN_PASS);
        }
        if (databaseType == "GAME")
        {
            return nanodbc::connection(GAME_DSN_NAME, GAME_DSN_USER, GAME_DSN_PASS);
        }
        if (databaseType == "LOG")
        {
            return nanodbc::connection(LOG_DSN_NAME, LOG_DSN_USER, LOG_DSN_PASS);
        }
        
        throw std::runtime_error("Invalid database type");
    }
    
    static void SetAccountDsn(const std::string& dsnName, const std::string& user, const std::string& pass)
    {
        ACCOUNT_DSN_NAME = dsnName;
        ACCOUNT_DSN_USER = user;
        ACCOUNT_DSN_PASS = pass;
    }

    static void SetGameDsn(const std::string& dsnName, const std::string& user, const std::string& pass)
    {
        GAME_DSN_NAME = dsnName;
        GAME_DSN_USER = user;
        GAME_DSN_PASS = pass;
    }

    static void SetLogDsn(const std::string& dsnName, const std::string& user, const std::string& pass)
    {
        LOG_DSN_NAME = dsnName;
        LOG_DSN_USER = user;
        LOG_DSN_PASS = pass;
    }
}
;
