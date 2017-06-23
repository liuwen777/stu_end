#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";
char * stuname = "stu.html";

int cgiMain()
{

	FILE * fd;
	char stuId[32] = "\0";
	int status = 0;

	char ch;
//	fprintf(cgiOut, "Content-type:text/html;charset=utf-7\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);
	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);


	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	int ret;
	MYSQL *db;
	char sql[128] = "\0";
	sprintf(sql, "select * from  information where stuId ='%d'", atoi(stuId));
	//初始化
	//mysql_options(db, MYSQL_SET_CHARSET_NAME, "utf8");
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
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}

 int num=(int)res->row_count;
  if(num>=1)
  {
     char ch1;
     fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
     if(!(fd = fopen(stuname, "r"))){
     fprintf(cgiOut, "Cannot open file, %s\n", stuname);
     return -1;
     }
    ch1 = fgetc(fd);
    while(ch1 != EOF){
     fprintf(cgiOut, "%c", ch1);
     ch1 = fgetc(fd);
    }
   }
  else{
    fprintf(cgiOut, "此学生不存在");
  }


	return 0;
}
