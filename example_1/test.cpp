#include "mysqlmanager.h"

int main()
{
	MysqlManager *mysql = new MysqlManager("127.0.0.1","root","1","mytest",(unsigned int)3306);
	mysql->initConnection();
	if(mysql->getConnectionStatus())
	{
		if(mysql->runSQLCommand("select * from student"))
		{
			vector< vector<string> > result = mysql->getResult();
			for(vector< vector<string> >::iterator it = result.begin();
				it != result.end(); ++it)
			{
				for(vector<string>::iterator itet = (*it).begin();
					itet != (*it).end(); ++itet)
				{
					cout<<(*itet).c_str()<<" ";
				}
					cout<<endl;
			}
		}
		else
		{
			cout<<"execute failed"<<endl;
		}
	}
	else
	{
		cout<<"not connect"<<endl;
	}

	return 0;
}

