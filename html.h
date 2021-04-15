#include "common.h"

extern struct globals global;
extern PGresult *db_query(const char *, ...);
extern int find_id(const struct genid[], const int);
