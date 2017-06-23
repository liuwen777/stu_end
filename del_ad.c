#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char stuId[32] = "\0";
  //char statusdel[4] = "\0";
	int status = 0;


	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	int ret;
	char sql[128] = "\0";

	 MYSQL *db;
   sprintf(sql, "select * from  information where stuId ='%d'", atoi(stuId));
	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	MYSQL_RES *res;
	res = mysql_store_result(db);//mysql_store_result是一个不会导致任何伤害或性能降低的返回函数。
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_srore_query fail:%s\n", mysql_error(db));
		return -1;
	}


	int num=(int)res->row_count;
	if(num>=1){
       sprintf(sql, "delete from information  where stuId = %d", atoi(stuId));
			 if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
		 	{
		 		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		 		mysql_close(db);
		 		return -1;
		 	}
				fprintf(cgiOut, "delete stu ok!\n");
	}else{
		fprintf(cgiOut, "此学生在数据库不存在!\n");
	}

	mysql_close(db);
	return 0;
}

