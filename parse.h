#include "common.h"

extern struct globals global;

extern void convert_postdata(char *, char *, int);
extern PGresult *db_query(const char *, ...);
extern void http_redir(const char *);
extern void html_cust(void);
extern void html_form_todo(const int);
extern void html_form_addtech(void);
extern void html_form_addcust(void);
extern void html_form_adddist(void);
extern void html_form_addoem(void);
extern void html_form_cust(const int);
extern void html_form_custtech(const int);
extern void html_form_editdist(const int);
extern void html_form_editoem(const int);
extern void html_form_edittech(const int);
extern void html_form_journal(const int);
extern void html_header(const char *, const int);
extern void html_disty(void);
extern void html_journal(const int);
extern void html_oem(void);
extern void html_tech(void);
extern void html_todo(const int);
extern void html_trailer(void);
extern int parse_form_vars(char *[], const char **, char *, const int num_parsers);
extern int parse_qs_opts(char *, char *[], char *[], int);
extern char *str_split(char **, const char *);
