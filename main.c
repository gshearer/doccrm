#include "main.h"

void
exit_graceful(int status)
{
  db_close();
  exit(status);
}

void
init_globals(void)
{
  global.dbconn = NULL;
}

int
main(void)
{
  init_globals();

  while(FCGI_Accept() >= 0)
  {
    char *qs = getenv("QUERY_STRING");

    if(qs == NULL || *qs == '\0')
    {
      char buf[500000];

      if(fgets(buf, 500000, stdin) != NULL)
      {
        int x = strlen(buf) - 1;
        FILE *fp = fopen("/tmp/blah.txt", "w");
        fprintf(fp, "length: %d\n---------\n%s\n----------\n", x + 1, buf);
        fclose(fp);
        if(buf[x] == '\r' || buf[x] == '\n')
          buf[x] = '\0';
        parse_form(buf);
      }
     /* else
        html_todo(); */
    }
    else
      parse_query(qs);
  }

  exit_graceful(SUCCESS);
}
