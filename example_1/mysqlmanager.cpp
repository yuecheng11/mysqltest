#include "mysqlmanager.h"

MysqlManager::MysqlManager(string host,string userName,string password,string dbName,unsigned int port)
{
	IsConnected = false;
	
	this->setHost(host);
	this->setDBName(dbName);
	this->setPassword(password);
	this->setPort(port);
	this->setUserName(userName);
}

MysqlManager::~MysqlManager()
{
	this->destroyConnection();
}

void MysqlManager::setUserName(string userName)
{
	if(userName.empty())
	{
		cout<<"username is null, default as root"<<endl;
		this->USERNAME = new char[5];
		strcpy(this->USERNAME,"root");
	}
	else
	{
		this->USERNAME = new char[userName.length() + 1];
		strcpy(this->USERNAME,userName.c_str());
	}
}

void MysqlManager::setHost(string hosts)
{
	 if ( hosts.empty() )    
        {
        	std::cout << "Hosts is null! Used default value: localhost" << std::endl;    
            this ->HOSTS = new char[10];    
            strcpy(this ->HOSTS, "localhost");    
        }    
        else    
        {    
                this ->HOSTS = new char[hosts.length() + 1];    
                strcpy(this ->HOSTS, hosts.c_str());    
        } 
}

void MysqlManager::setPassword(string password)
{
	if ( password.empty() )    
    {    
            std::cout << "Password is null! Used default value: " << std::endl;    
            this ->PASSWORD = new char[1];    
            strcpy(this ->PASSWORD, "");    
    }    
    else    
    {    
            this ->PASSWORD = new char[password.length() + 1];    
            strcpy(this ->PASSWORD, password.c_str());    
    } 
}

void MysqlManager::setDBName(string dbName)
{
	if ( dbName.empty() )    
    { 
            std::cout << "DBName is null! Used default value: mysql" << std::endl;    
            this ->DBNAME = new char[6];    
            strcpy(this ->DBNAME, "mysql");    
    }    
    else    
    {    
            this ->DBNAME = new char[dbName.length() + 1];    
            strcpy(this ->DBNAME, dbName.c_str());    
    }    
}
void MysqlManager::setPort(unsigned int port)
{
	if ( port <= 0 )    
    {    
            std::cout << "Port number is null! Used default value: 0" << std::endl;    
            this->DEFAULTPORT = 0;
    }    
    else    
    {    
            this ->DEFAULTPORT = port;    
    }    
}

void MysqlManager::initConnection()
{
	if(IsConnected)
	{
		cout<<"is connected to server"<<endl;
		return ;
	}

	mysql_init(&mySQLClient);

	if(!mysql_real_connect(&mySQLClient,HOSTS,USERNAME,PASSWORD,DBNAME,DEFAULTPORT,NULL,0))
	{
		cout<<"HHHHHHHHHHHHHHHH"<<endl;
		cout<<"Error connection to database: \n"<<mysql_error(&mySQLClient)<<endl;
	}
	
	IsConnected = true;
}

bool MysqlManager::runSQLCommand(string sql)
{
	if(!IsConnected)
	{
		cout<<"Not connect to database!"<<endl;
		return false;
	}
	if(sql.empty())
	{
		cout<<"sql is null!"<<endl;

		return false;
	}

	MYSQL_RES* res;
	MYSQL_ROW row;

	int i,j;
	
	i = mysql_real_query(&mySQLClient,sql.c_str(),(unsigned int)strlen(sql.c_str()));
	if(i < 0)
	{
		std::cout << "Error query from database: \n" << mysql_error(&mySQLClient) << std::endl;    
        return false; 
	}

	res = mysql_store_result(&mySQLClient);

	vector<string> objectValue;
	while((row = mysql_fetch_row(res)))
	{
		objectValue.clear();
		for(j = 0;j<mysql_num_fields(res);j++)
		{
			objectValue.push_back(row[j]);
		}

		this->resultList.push_back(objectValue);
	}
	
	mysql_free_result(res);

	return true;
}

unsigned int MysqlManager::insert(string sql)
{
	if(!IsConnected)
	{
		cout<<""<<endl;
		return -1;
	}
	if(sql.empty())
	{
		cout<<"sql is null!"<<endl;

		return -1;
	}

	int rows = -1;
	int res = mysql_query(&mySQLClient,sql.c_str());
	if(res >= 0)
	{
		rows = mysql_affected_rows(&mySQLClient);
		cout<<"Insert "<<rows<<"rows\n";
		return rows;
	}
	else
	{
		cout<<"insert error "<<mysql_errno(&mySQLClient)<<", "<<mysql_error(&mySQLClient)<<endl;
		return -1;
	}
}

vector< vector<string> > MysqlManager::getResult()
{
	return resultList;
}

void MysqlManager::destroyConnection()
{
	mysql_close(&mySQLClient);
	this->IsConnected = false;
}

bool MysqlManager::getConnectionStatus()
{
	return IsConnected;
}

