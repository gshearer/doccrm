#include "db.h"

void
db_close(void)
{
  if(global.dbconn != NULL)
    PQfinish(global.dbconn);
  global.dbconn = NULL;
}

int
db_connect(void)
{
  char psql_conn_info[1000];
  
  if(global.dbconn != NULL)
  { 
    if(PQstatus(global.dbconn) == CONNECTION_OK)
      return(SUCCESS);
    PQfinish(global.dbconn);
  }

  snprintf(psql_conn_info, 999, "host=%s port=%s user=%s password=%s dbname=%s connect_timeout=5", DB_HOST, DB_PORT, DB_USER, DB_PASS, DB_NAME);
  
  global.dbconn = PQconnectdb(psql_conn_info);
  
  if(PQstatus(global.dbconn) == CONNECTION_OK)
    return(SUCCESS);
  return(FAIL);
}

PGresult *
db_query(const char *format, ...)
{
  char sql[500000];
  PGresult *res;
  va_list ptr;

  if(db_connect() == FAIL)
    return(NULL);

  va_start(ptr, format);
  vsprintf(sql, format, ptr);
  va_end(ptr);

  res = PQexec(global.dbconn, sql);

  if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "db_query(): %s", PQerrorMessage(global.dbconn));
    PQclear(res);
    return(NULL);
  }
  return(res);
}
