#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(3);        
}

int main(int argc, char **argv)
{      
	MYSQL *con = mysql_init(NULL);
	MYSQL_RES* res_ptr;
	int i;
	int res;

    char sensorId[20];
    int illu;
    double temp;
    double humi;
	char sql_cmd[200] = { 0 };

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
		exit(1);
	}  

	if(argc != 5)
	{
		printf("Usage : %s sensorId illu temp humi\n",argv[0]);
		exit(2);
	}
    strcpy(sensorId,argv[1]);
    illu = atoi(argv[2]);
    temp = atof(argv[3]);
    humi = atof(argv[4]);

  	if (mysql_real_connect(con, "127.0.0.1", "iot", "pwiot", 
				"iotdb", 0, NULL, 0) == NULL) 
	{
		finish_with_error(con);
	}    

 	sprintf(sql_cmd, "insert into sensor(name, date, time,illu, temp, humi) values(\"%s\",now(),now(),%d,%lf,%lf)",sensorId, illu, temp, humi);

	res = mysql_query(con, sql_cmd);
	if (!res)
		printf("inserted %lu rows\n", (unsigned long)mysql_affected_rows(con));
	else
	{
		fprintf(stderr, "ERROR: %s[%d]\n", mysql_error(con), mysql_errno(con));
		finish_with_error(con);
	}

	mysql_close(con);

	exit(0);
}
