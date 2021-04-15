#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include <fcgi_stdio.h>

#define DB_HOST   "192.168.254.17"
#define DB_PORT   "5432"
#define DB_USER   "doc"
#define DB_PASS   "censored"
#define DB_NAME   "docdb"

#define TBL_TODO  "doccrm_todo"
#define TBL_CUST  "doccrm_cust"
#define TBL_TECH  "doccrm_tech"
#define TBL_CUSTTECH "doccrm_custtech"
#define TBL_JOURNAL "doccrm_journal"
#define TBL_OEM   "doccrm_oem"
#define TBL_DISTY "doccrm_disty"

#define REDIR_LOC "https://your.web.server.local/doccrm"

#define true    1
#define false   0

#define FAIL    1
#define SUCCESS 0

struct globals
{
  PGconn *dbconn;
};

struct genid
{
  int id;
  char *name;
};
