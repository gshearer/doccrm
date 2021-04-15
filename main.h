#include "common.h"

struct globals global;

extern void db_close(void);
extern void parse_query(const char *);
extern void parse_form(char *);
