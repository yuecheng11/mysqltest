#ifndef _MYSQLMANAGER_H_
#define _MYSQLMANAGER_H_

#include <mysql.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

class MysqlManager
{
public:
	MysqlManager(string host,string userName,string password,string dbName,unsigned int port);
	~MysqlManager();

	void initConnection();
	bool runSQLCommand(string sql);
	unsigned int insert(string sql);
	void destroyConnection();
	bool getConnectionStatus();
	vector< vector<string> > getResult();

protected:
	void setUserName(string userName);
	void setHost(string hosts);
	void setPassword(string password);    
    void setDBName(string dbName);    
    void setPort(unsigned int port);    
private:    
        bool IsConnected;    
        vector< vector<string> > resultList;    
        MYSQL mySQLClient;  
		
        unsigned int DEFAULTPORT;    
        char * HOSTS;    
        char * USERNAME;    
        char * PASSWORD;    
        char * DBNAME;   
	
};

#endif