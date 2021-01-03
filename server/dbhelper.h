#ifndef __DB__HELPER__HEADER__
#define __DB__HELPER__HEADER__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <search.h>
#include <mysql.h>

#define MYSQL_MAX_SQL_LEN 4096 //���ݿ�������ĳ���

/* ��¼���ݿ������Ľṹ��*/
struct DbResult
{
char*** rows;
unsigned long nrow;
unsigned long ncol;
char**headers;//reserved for header name
void * resource;//used for holding data.
};

/*��ʼ��MYSQL����*/
void* InitDbCon2(const char *host, const char *user,const char *passwd, int port,const char *db);

/*�ͷŽ����*/
void FreeDbResult(struct DbResult*dbResult);

/*���������,��memset*/
struct DbResult*  CreateDbResult();


/*ִ�����ݿ��ѯ���*/
int db_QuerySql(void*conn,struct DbResult* dbResult,const char*sql,...);
int db_VQuerySql(void*conn,struct DbResult* dbResult,const char*sql,const va_list ap);


int HasError(void*conn);

/*ִ�����ݿ�������*/
int db_ExecSql(void* conn,const char*sql);

/*��ȡ������Ϣ*/
const char* GetError(void*conn);

/*�ж�MYSQL����*/
int ConnectedCon(void *conn);

/*�ر�MYSQL����*/
void CloseDbCon(void*conn);

#endif
