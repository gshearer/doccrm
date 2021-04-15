#include "html.h"

void
http_redir(char *location)
{
  printf("Location: %s%s\n\n", REDIR_LOC, location);
}

void
html_header(char *title, int abar)
{
  puts("Content-type: text/html\n"
       "Pragma-directive: no-cache\n"
       "Cache-directive: no-cache\n"
       "Cache-control: no-cache\n"
       "Pragma: no-cache\n"
       "Expires: 0\n\n"
       "<!DOCTYPE html>\n"
       "<html>\n"
       "  <head>\n"
       "    <meta http-equiv=\"Content-Style-Type\" content=\"text/css\">\n"
       "    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n"
       "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\n"
       "    <!-- bulma -->\n"
       "    <link href=\"https://fonts.googleapis.com/css?family=Roboto:300,400,500,700\" rel=\"stylesheet\">\n"
       "    <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/normalize/6.0.0/normalize.min.css\">\n"
       "    <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bulma@0.9.2/css/bulma.min.css\">\n"
       "    <link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">\n\n"
       "    <!-- custom -->\n"
       "    <link rel=\"stylesheet\" href=\"https://shearer.tech/css/p0.css\">\n");

  printf("    <title>George's CRM %s</title>\n"
         "  </head>\n\n"
         "  <body>\n\n"
         "    <div id=\"linkbar\">\n"
         "      <table>\n"
         "        <tbody>\n"
         "          <tr>\n", title);

  if(abar == 1)
    puts("            <td><a href=\"?todo\" class=\"linkbar__active\">TODO</a></td>");
  else
    puts("            <td><a href=\"?todo\">TODO</a></td>");

  if(abar == 2)
    puts("            <td><a href=\"?customers\" class=\"linkbar__active\">Customers</a></td>");
  else
    puts("            <td><a href=\"?customers\">Customers</a></td>");

  if(abar == 3)
    puts("            <td><a href=\"?technologies\" class=\"linkbar__active\">Technologies</a></td>");
  else
    puts("            <td><a href=\"?technologies\">Technologies</a></td>");

  if(abar == 4)
    puts("            <td><a href=\"?manufacturers\" class=\"linkbar__active\">Manufacturers</a></td>");
  else
    puts("            <td><a href=\"?manufacturers\">Manufacturers</a></td>");

  if(abar == 5)
    puts("            <td><a href=\"?distributors\" class=\"linkbar__active\">Distributors</a></td>");
  else
    puts("            <td><a href=\"?distributors\">Distributors</a></td>");

  printf("          </tr>\n"
         "        </tbody>\n"
         "      </table>\n"
         "    </div>\n\n"
         "    <header>\n"
         "      <h1>%s</h1>\n"
         "    </header>\n\n"
         "    <div id=\"page\">\n"
         "      <div class=\"page-inner content\">\n\n", title);
}

void
html_trailer(void)
{
    puts("      </div> <!-- /page-inner -->\n"
         "    </div> <!-- /page -->\n"
         "  </body>\n"
         "</html>");
}

void
html_form_addcust(void)
{
  puts("      <div id=\"addcust\" class=\"add-wrap\">\n"
       "        <form action=\"doccrm\" method=\"post\">\n"
       "          <input type=\"hidden\" name=\"datatype\" value=\"addcust\">\n"
       "          <div class=\"add-entity\">\n"
       "            <label class=\"label\" for=\"add-cust-input\">Add customer</label>\n"
       "            <div class=\"field is-grouped\">\n"
       "              <p class=\"control\">\n"
       "                <input id=\"add-cust-input\" name=\"cust\" class=\"input\" type=\"text\" placeholder=\"Add customer\" size=\"50\">\n"
       "              </p>\n"
       "              <p class=\"control\">\n"
       "                <button class=\"button is-info\" type=\"submit\" value=\"Submit\" id=\"submit\">Add</button>\n"
       "              </p>\n"
       "            </div>\n"
       "          </div>\n"
       "        </form>\n"
       "      </div>\n");
}

void
html_form_adddist(void)
{
  puts("      <div id=\"adddist\" class=\"add-wrap\">\n"
       "        <form action=\"doccrm\" method=\"post\">\n"
       "          <input type=\"hidden\" name=\"datatype\" value=\"adddist\">\n"
       "          <div class=\"add-entity\">\n"
       "            <label class=\"label\" for=\"add-dist-input\">Add distributor</label>\n"
       "            <div class=\"field is-grouped\">\n"
       "              <p class=\"control\">\n"
       "                <input id=\"add-dist-input\" name=\"disty\" class=\"input\" type=\"text\" placeholder=\"Add distributor\" size=\"50\">\n"
       "              </p>\n"
       "              <p class=\"control\">\n"
       "                <button class=\"button is-info\" type=\"submit\" value=\"Submit\" id=\"submit\">Add</button>\n"
       "              </p>\n"
       "            </div>\n"
       "          </div>\n"
       "        </form>\n"
       "      </div>\n");
}

void
html_form_addoem(void)
{
  puts("      <div id=\"addoem\" class=\"add-wrap\">\n"
       "        <form action=\"doccrm\" method=\"post\">\n"
       "          <input type=\"hidden\" name=\"datatype\" value=\"addoem\">\n"
       "          <div class=\"add-entity\">\n"
       "            <label class=\"label\" for=\"add-oem-input\">Add manufacturer</label>\n"
       "            <div class=\"field is-grouped\">\n"
       "              <p class=\"control\">\n"
       "                <input id=\"add-oem-input\" name=\"oem\" class=\"input\" type=\"text\" placeholder=\"Add Manufacturer\" size=\"50\">\n"
       "              </p>\n"
       "              <p class=\"control\">\n"
       "                <button class=\"button is-info\" type=\"submit\" value=\"Submit\" id=\"submit\">Add</button>\n"
       "              </p>\n"
       "            </div>\n"
       "          </div>\n"
       "        </form>\n"
       "      </div>\n");
}

void
html_oem(void)
{
  PGresult *res = NULL;
  int rows = 0;

  if((res = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), name FROM %s ORDER BY name;", TBL_OEM)) == NULL)
    return;

  if((rows = PQntuples(res)) >= 1)
  {
    int row = 0;

    puts("      <div id=\"oem\">\n"
         "        <div class=\"table-container\">\n"
         "          <table class=\"table is-hoverable\">\n"
         "            <thead><tr><th>&nbsp;</th><th>Manufacturer Name</th><th>Date Time added</th></tr></thead>\n"
         "            <tbody>");

    for(; row < rows; row++)
    {
      int id = atoi(PQgetvalue(res, row, 0));
      char *timestamp = PQgetvalue(res, row, 1);
      char *name = PQgetvalue(res, row, 2);

      printf("              <tr>\n"
             "                <td><a href=\"?deloem=%d\" title=\"Delete oem %d\"><button class=\"delete\"></button></a></td>\n"
             "                <td><a href=\"?editoem=%d\">%s</a></td>\n"
             "                <td>%s</td>\n"
             "              </tr>\n", id, id, id, name, timestamp);
    }

    puts("            </tbody>\n"
         "          </table>\n"
         "        </div> <!-- /table-container -->\n"
         "      </div> <!-- /oem -->\n");
  }

  if(res != NULL)
    PQclear(res);
}

void
html_disty(void)
{
  PGresult *res = NULL;
  int rows = 0;

  if((res = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), name FROM %s ORDER BY name;", TBL_DISTY)) == NULL)
    return;

  if((rows = PQntuples(res)) >= 1)
  {
    int row = 0;

    puts("      <div id=\"disty\">\n"
         "        <div class=\"table-container\">\n"
         "          <table class=\"table is-hoverable\">\n"
         "            <thead><tr><th>&nbsp;</th><th>Distributor Name</th><th>Date Time added</th></tr></thead>\n"
         "            <tbody>");

    for(; row < rows; row++)
    {
      int id = atoi(PQgetvalue(res, row, 0));
      char *timestamp = PQgetvalue(res, row, 1);
      char *name = PQgetvalue(res, row, 2);

      printf("              <tr>\n"
             "                <td><a href=\"?deldist=%d\" title=\"Delete distributor %d\"><button class=\"delete\"></button></a></td>\n"
             "                <td><a href=\"?editdist=%d\">%s</a></td>\n"
             "                <td>%s</td>\n"
             "              </tr>\n", id, id, id, name, timestamp);
    }

    puts("            </tbody>\n"
         "          </table>\n"
         "        </div> <!-- /table-container -->\n"
         "      </div> <!-- /cust -->\n");
  }

  if(res != NULL)
    PQclear(res);
}

void
html_cust(void)
{
  PGresult *res = NULL;
  int rows = 0;

  if((res = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), name FROM %s ORDER BY UPPER(name);", TBL_CUST)) == NULL)
    return;

  if((rows = PQntuples(res)) >= 1)
  {
    int row = 0;

    puts("      <div id=\"cust\">\n"
         "        <div class=\"table-container\">\n"
         "          <table class=\"table is-hoverable\">\n"
         "            <thead><tr><th>&nbsp;</th><th>Customer name</th><th>Date Time added</th></tr></thead>\n"
         "            <tbody>");

    for(; row < rows; row++)
    {
      int id = atoi(PQgetvalue(res, row, 0));
      char *timestamp = PQgetvalue(res, row, 1);
      char *name = PQgetvalue(res, row, 2);

      printf("              <tr>\n"
             "                <td><a href=\"?delcust=%d\" title=\"Delete customer %d\"><button class=\"delete\"></button></a></td>\n"
             "                <td><a href=\"?editcust=%d\">%s</a></td>\n"
             "                <td>%s</td>\n"
             "              </tr>\n", id, id, id, name, timestamp);
    }

    puts("            </tbody>\n"
         "          </table>\n"
         "        </div> <!-- /table-container -->\n"
         "      </div> <!-- /cust -->\n");
  }

  if(res != NULL)
    PQclear(res);
}

void
html_journal(int custid)
{
  PGresult *res = NULL;
  int row = 0, rows;

  if((res = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), entry FROM %s WHERE customer='%d' ORDER BY timestamp DESC;", TBL_JOURNAL, custid)) == NULL)
    return;

  if((rows = PQntuples(res)) >= 1)
  {

    puts("<br>\n"
         "<div id=\"journal\">\n"
         "  <h3>Journal</h3>\n"
         "  <div class=\"table-container2\">\n"
         "    <table class=\"table is-hoverable\">\n"
         "      <thead><tr><th>&nbsp;</th><th>Create date</th><th>Journal entry</th></tr></thead>\n"
         "      <tbody>");

    for(; row < rows; row++)
    {
      int id = atoi(PQgetvalue(res, row, 0));
      char *timestamp = PQgetvalue(res, row, 1);
      char *entry = PQgetvalue(res, row, 2);


      printf("              <tr>\n"
             "                <td><a href=\"?deljournal=%d&custid=%d\" title=\"Delete entry %d\"><button class=\"delete\"></button></a></td>\n"
             "                <td><p>%s</p></td>\n"
             "                <td><p><pre>%s</pre></p></td>\n"
             "              </tr>\n", id, custid, id, timestamp, entry);
    }

    puts("      </tbody>\n"
         "    </table>\n"
         "  </div> <!-- /table-container -->\n"
         "</div> <!-- /journal -->\n");
  }

  if(res != NULL)
    PQclear(res);
}

void
html_form_journal(const int custid)
{
  printf("<div id=\"addjournal\">\n"
         "<br>\n"
         "<h3>Add journal</h3>\n"
         "<form action=\"doccrm\" method=\"post\">\n"
         "  <input type=\"hidden\" name=\"datatype\" value=\"journal\">\n"
         "  <input type=\"hidden\" name=\"custid\" value=\"%d\">\n"
         "    <div class=\"field\">\n"
         "      <div class=\"control\">\n"
         "        <textarea id=\"jentry\" name=\"journal\" class=\"textarea\"></textarea>\n"
         "      </div>\n"
         "    </div>\n"
         "    <div class=\"field has-addons\">\n"
         "      <div class=\"control\">\n"
         "        <button id=\"addjournal\" class=\"button is-link\">Add entry</button>\n"
         "      </div>\n"
         "    </div>\n"
         "  </form>\n"
         "</div> <!-- /addjournal -->\n\n", custid);
}

void
html_form_editoem(const int id)
{
  PGresult *res = NULL;

  if((res = db_query("SELECT name, contacts, notes FROM %s WHERE id='%d';", TBL_OEM, id)) == NULL)
    return;

  if(PQntuples(res))
  {
    char *name = PQgetvalue(res, 0, 0);
    char *contacts = PQgetvalue(res, 0, 1);
    char *notes = PQgetvalue(res, 0, 2);

    printf("<div id=\"editoem\">\n"
           "  <form action=\"doccrm\" method=\"post\">\n"
           "    <input type=\"hidden\" name=\"datatype\" value=\"editoem\">\n"
           "    <input type=\"hidden\" name=\"id\" value=\"%d\">\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Manufacturer Name</label>\n"
           "      <div class=\"control\">\n"
           "        <input id=\"name\" class=\"input\" type=\"text\" name=\"name\" placeholder=\"Text input\" title=\"Manufacturer name\" size=\"50\" value=\"%s\" tabindex=\"1\">\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Contacts</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"contacts\" name=\"contacts\" class=\"textarea\" tabindex=\"2\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Notes</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"notes\" name=\"notes\" class=\"textarea\" tabindex=\"3\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field has-addons\">\n"
           "      <div class=\"control\">\n"
           "        <button id=\"savedist\" class=\"button is-link\" tabindex=\"4\">Save</button>\n"
           "      </div>\n"
           "    </div>\n\n"
           "  </form>\n"
           "</div> <!-- /editoem -->\n\n", id, name, contacts, notes);
  }
  PQclear(res);
}

void
html_form_editdist(const int id)
{
  PGresult *res = NULL;

  if((res = db_query("SELECT name, contacts, notes FROM %s WHERE id='%d';", TBL_DISTY, id)) == NULL)
    return;

  if(PQntuples(res))
  {
    char *name = PQgetvalue(res, 0, 0);
    char *contacts = PQgetvalue(res, 0, 1);
    char *notes = PQgetvalue(res, 0, 2);

    printf("<div id=\"editdist\">\n"
           "  <form action=\"doccrm\" method=\"post\">\n"
           "    <input type=\"hidden\" name=\"datatype\" value=\"editdist\">\n"
           "    <input type=\"hidden\" name=\"id\" value=\"%d\">\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Name</label>\n"
           "      <div class=\"control\">\n"
           "        <input id=\"name\" class=\"input\" type=\"text\" name=\"name\" placeholder=\"Text input\" title=\"Distributor name\" size=\"50\" value=\"%s\" tabindex=\"1\">\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Contacts</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"contacts\" name=\"contacts\" class=\"textarea\" tabindex=\"2\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Notes</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"notes\" name=\"notes\" class=\"textarea\" tabindex=\"3\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field has-addons\">\n"
           "      <div class=\"control\">\n"
           "        <button id=\"savedist\" class=\"button is-link\" tabindex=\"4\">Save</button>\n"
           "      </div>\n"
           "    </div>\n\n"
           "  </form>\n"
           "</div> <!-- /editdist -->\n\n", id, name, contacts, notes);
  }
  PQclear(res);
}

void
html_form_cust(const int id)
{
  PGresult *res = NULL;

  if((res = db_query("SELECT name, contacts, notes FROM %s WHERE id='%d';", TBL_CUST, id)) == NULL)
    return;

  if(PQntuples(res))
  {
    char *name = PQgetvalue(res, 0, 0);
    char *contacts = PQgetvalue(res, 0, 1);
    char *notes = PQgetvalue(res, 0, 2);

    printf("<div id=\"editcust\">\n"
           "  <form action=\"doccrm\" method=\"post\">\n"
           "    <input type=\"hidden\" name=\"datatype\" value=\"editcust\">\n"
           "    <input type=\"hidden\" name=\"id\" value=\"%d\">\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Name</label>\n"
           "      <div class=\"control\">\n"
           "        <input id=\"name\" class=\"input\" type=\"text\" name=\"name\" placeholder=\"Text input\" title=\"Customer name\" size=\"50\" value=\"%s\" tabindex=\"1\">\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Contacts</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"contacts\" name=\"contacts\" class=\"textarea\" tabindex=\"2\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field\">\n"
           "      <label class=\"label\">Notes</label>\n"
           "      <div class=\"control\">\n"
           "        <textarea id=\"notes\" name=\"notes\" class=\"textarea\" tabindex=\"3\">%s</textarea>\n"
           "      </div>\n"
           "    </div>\n\n"
           "    <div class=\"field has-addons\">\n"
           "      <div class=\"control\">\n"
           "        <button id=\"savecust\" class=\"button is-link\" tabindex=\"4\">Save</button>\n"
           "      </div>\n"
           "    </div>\n\n"
           "  </form>\n"
           "</div> <!-- /editcust -->\n\n", id, name, contacts, notes);
  }
  PQclear(res);
}

void
html_form_edittech(const int id)
{
  struct genid dists[1000];
  PGresult *res, *res2;
  int row = 0, rows, x = 0, y = 0, disty;
  char *name, *notes;

  memset((void *)dists, 0, sizeof(struct genid) * 1000);

  if((res = db_query("SELECT id, name FROM %s;", TBL_DISTY)) == NULL)
    return;
  
  if((rows = PQntuples(res)))
  {
    for(; row < rows && row < 1000; row++)
    {
      dists[x].id = atoi(PQgetvalue(res, row, 0));
      dists[x++].name = PQgetvalue(res, row, 1);
    }
  }

  if((res2 = db_query("SELECT name, notes, disty FROM %s WHERE id='%d';", TBL_TECH, id)) == NULL)
    return;

  if(!PQntuples(res2))
  {
    PQclear(res);
    PQclear(res2);
    return;
  }

  name = PQgetvalue(res2, 0, 0);
  notes = PQgetvalue(res2, 0, 1);
  disty = atoi(PQgetvalue(res2, 0, 2));

  printf("<div id=\"edittech\">\n"
         "<form action=\"doccrm\" method=\"post\">\n"
         "  <input type=\"hidden\" name=\"datatype\" value=\"edittech\">\n"
         "  <input type=\"hidden\" name=\"id\" value=\"%d\">\n"
         "  <div class=\"field\">\n"
         "    <label class=\"label\">Technology name</label>\n"
         "    <div class=\"control\">\n"
         "      <input type=\"text\" class=\"input\" id=\"name\" tabindex=\"1\" name=\"name\" title=\"Technology name\" size=\"50\" value=\"%s\">\n"
         "    </div>\n"
         "  </div>\n"
         "  <div class=\"field\">\n"
         "    <label class=\"label\">Distributor</label>\n"
         "    <p class=\"control\">\n"
         "      <span class=\"select\">\n"
         "        <select tabindex=\"2\" id=\"disty\" name=\"disty\">\n", id, name);

  if(disty)
  {
    if((y = find_id(dists, disty)) != -1)
      printf("          <option value=\"%d\">%s</option>\n", disty, dists[y].name);
    else
      printf("          <option value=\"%d\">Unknown</option>\n", disty);
  }
  else
    puts("          <option value=\"0\">None</option>\n");

  for(y = 0; y < x; y++)
  {
    if(dists[y].id == disty)
      continue;
    printf("          <option value=\"%d\">%s</option>\n", dists[y].id, dists[y].name);
  }

  printf("        </select>\n"
         "      </span>\n"
         "    </p>\n"
         "  </div>\n"
         "  <div class=\"field\">\n"
         "    <label class=\"label\">Notes</label>\n"
         "    <div class=\"control\">\n"
         "      <textarea id=\"tnotes\" name=\"notes\" class=\"textarea\" cols=\"100\" rows=\"20\" tabindex=\"3\">%s</textarea>\n"
         "    </div>\n"
         "  </div>\n"
         "  <div class=\"field has-addons\">\n"
         "    <div class=\"control\">\n"
         "      <button id=\"submit\" class=\"button is-link\" tabindex=\"4\">Save</button>\n"
         "    </div>\n"
         "  </div>\n"
         "</form>\n"
         "</div>\n\n", notes);

  PQclear(res2);
  PQclear(res);
}


void
html_form_todo(int custnum)
{
  PGresult *res = NULL;

  printf("<div id=\"addtodo\">\n"
         "<h3>Add Todo</h3>\n"
         "<form action=\"doccrm\" method=\"post\">\n"
         "  <input type=\"hidden\" name=\"datatype\" value=\"todo\"/>\n"
         "  <input type=\"hidden\" name=\"redircust\" value=\"%d\"/>\n"
         "  <div class=\"field has-addons\">\n"
         "    <p class=\"control\">\n"
         "      <span class=\"select\">\n"
         "        <select id=\"priority\" name=\"priority\">\n"
         "          <option value=\"2\">Medium</option>\n"
         "          <option value=\"1\">High</option>\n"
         "          <option value=\"3\">Low</option>\n"
         "        </select>\n"
         "      </span>\n"
         "    </p>\n"
         "    <p class=\"control\">\n"
         "      <span class=\"select\">\n"
         "        <select id=\"customer\" name=\"customer\">\n", (custnum == 0) ? 0 : 1);

  if((res = db_query("SELECT id, name FROM %s ORDER BY name;", TBL_CUST)) != NULL)
  {
    int row = 0, rows = PQntuples(res), custid[1000];
    char *custname[1000];

    memset((void *)custid, 0, sizeof(int) * 1000);
    memset((void *)custname, 0, sizeof(char *) * 1000);

    for(; row < rows && row < 1000; row++)
    {
      custid[row] = atoi(PQgetvalue(res, row, 0));
      custname[row] = PQgetvalue(res, row, 1);
    }

    if(custnum)
    {
      for(row = 0; row < rows && row < 1000 && custid[row] != custnum; row++);
      if(custid[row] == custnum)
        printf("          <option value=\"%d\">%s</option>\n", custnum, custname[row]);
    }
    else
        puts("          <option value=\"0\">None</option>");

    for(row = 0; row < rows && row < 1000; row++)
    {
      if(custnum && custid[row] == custnum)
        continue;
      printf("          <option value=\"%d\">%s</option>\n", custid[row], custname[row]);
    }

    PQclear(res);
  }
  else
    return;

  puts("        </select>\n"
       "      </span>\n"
       "    </p>\n"
       "    <p class=\"control\">\n"
       "      <input class=\"input\" placeholder=\"Todo item\" type=\"text\" id=\"todo\" tabindex=\"1\" name=\"todo\" title=\"TODO item\" size=\"100\" />\n"
       "    </p>\n"
       "    <p class=\"control\">\n"
       "      <button id=\"addtodo\" class=\"button is-link\" tabindex=\"2\">Add</button>\n"
       "    </p>\n"
       "  </div> <!-- /field -->\n"
       "</form>\n"
       "</div> <!-- /addtodo -->\n");
}

void
html_todo(const int custnum)
{
  struct genid customers[1000];
  PGresult *res, *res2;
  int row = 0, rows, x = 0;

  memset((void *)customers, 0, sizeof(struct genid) * 1000);

  if((res = db_query("SELECT id, name FROM %s;", TBL_CUST)) == NULL)
    return;
  
  if(!(rows = PQntuples(res)))
  {
    PQclear(res);
    return;
  }

  for(; row < rows && row < 1000; row++)
  {
    customers[x].id = atoi(PQgetvalue(res, row, 0));
    customers[x++].name = PQgetvalue(res, row, 1);
  }

  if(custnum)
    res2 = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), customer, priority, todo FROM %s WHERE customer='%d' ORDER BY priority;", TBL_TODO, custnum);
  else
    res2 = db_query("SELECT id, TO_CHAR(timestamp, 'MM/DD/YYYY HH:MI:SS'), customer, priority, todo FROM %s ORDER BY priority;", TBL_TODO);

  if(res2 == NULL)
  {
    PQclear(res);
    return;
  }

  if(!(rows = PQntuples(res2)))
  {
    PQclear(res);
    PQclear(res2);
    return;
  }

  puts("<div id=\"todo\">\n"
       "  <h3>TODO list</h3>\n"
       "  <div class=\"table-container\">\n"
       "    <table class=\"table is-hoverable\">\n"
       "      <thead><tr><th>&nbsp;</th><th>Create date</th><th>Customer</th><th>Priority</th><th>Todo item</th></tr></thead>\n"
       "      <tbody>");

  for(row = 0; row < rows; row++)
  {
    int id = atoi(PQgetvalue(res2, row, 0));
    int custid = atoi(PQgetvalue(res2, row, 2));
    int prio = atoi(PQgetvalue(res2, row, 3));
    char *timestamp = PQgetvalue(res2, row, 1);
    char *todo = PQgetvalue(res2, row, 4);
    char *custn;

    if(custid)
    {
      if((x = find_id(customers, custid)) != -1)
        custn = customers[x].name;
      else
        custn = "unknown";
    }
    else
      custn = "none";

    printf("        <tr>\n"
           "          <td><a href=\"?deltodo=%d&cust=%d\" title=\"Delete todo id %d\"><button class=\"delete\"></button></a></td>\n"
           "          <td>%s</td>\n"
           "          <td>", id, (custnum) ? custnum : 0, id, timestamp);

    if(custid == 0)
      printf("&nbsp;");
    else
      printf("<a href=\"?editcust=%d\" title=\"Edit customer %d\">%s</a>", custid, custid, custn);

    printf("</td>"
           "          <td><span class=\"tag is-primary ");

    switch(prio)
    {
      case 1:
        printf("is-danger\">high");
        break;
      case 2:
        printf("is-warning\">medium");
        break;
      case 3:
        printf("is-primary is-light\">low");
        break;
      default:
        printf("is-info\">%d", prio);
        break;
    }

    printf("</span></td>\n"
           "          <td>%s</td>\n"
           "        </tr>\n", todo);

  }

  puts("      </tbody>\n"
       "    </table>\n"
       "  </div> <!-- /table-container -->\n"
       "</div> <!-- /todo -->\n");

  PQclear(res);
  PQclear(res2);
}

void
html_form_custtech(int id)
{
  int row = 0, rows = 0;
  PGresult *res = NULL;
  char havetech[1000];

  if((res = db_query("SELECT tech FROM %s WHERE cust='%d';", TBL_CUSTTECH, id)) == NULL)
    return;

  memset((void *)havetech, 0, 1000);

  if((rows = PQntuples(res)))
  {
    for(; row < rows; row++)
    {
      int z = atoi(PQgetvalue(res, row, 0));
      havetech[z] = 1;
    }
  }

  if((res = db_query("SELECT id, name FROM %s ORDER BY name;", TBL_TECH)) == NULL)
    return;

  if((rows = PQntuples(res)))
  {
    int col = 0;

    printf("<div id=\"custtech\">\n"
           "<br>\n"
           "<h3>Associated Technologies</h3>\n"
           "<form class=\"cust-tech-form\" action=\"doccrm\" method=\"post\">\n"
           "  <input type=\"hidden\" name=\"datatype\" value=\"custtech\">\n"
           "  <input type=\"hidden\" name=\"id\" value=\"%d\">\n"
           "  <table class=\"control checkboxes\">\n", id);

    for(row = 0; row < rows; row++)
    {
      int techid = atoi(PQgetvalue(res, row, 0));
      char *tech = PQgetvalue(res, row, 1);

      if(!col)
        puts("  <tr>");

      printf("    <td><label class=\"checkbox\"><input type=\"checkbox\" id=\"%d\" name=\"%d\"", techid, techid);

      if(havetech[techid] == 1)
        printf(" checked");

      printf(">&nbsp;<a href=\"?edittech=%d\">%s</a></label></td>\n", techid, tech);

      if(++col == 8)
      {
        col = 0;
        puts("  </tr>\n");
      }
    }

    if(col)
      puts("  </tr>\n");

    puts("  </table>\n"
         "  <p class=\"control\">\n"
         "    <button id=\"savetech\" class=\"button is-link\">Save tech</button>\n"
         "  </p>\n"
         "</form>\n"
         "</div> <!-- custtech -->\n");
  }
  PQclear(res);
}

void
html_form_addtech(void)
{
  puts("<div id=\"addtech\" class=\"add-wrap\">\n"
       "<form action=\"doccrm\" method=\"post\">\n"
       "  <input type=\"hidden\" name=\"datatype\" value=\"tech\" />\n"
       "  <div class=\"add-entity\">\n"
       "    <label class=\"label\" for=\"add-tech-input\">Add technology</label>\n"
       "    <div class=\"field is-grouped\">\n"
       "      <p class=\"control\">\n"
       "        <input id=\"add-tech-input\" class=\"input\" type=\"text\" tabindex=\"1\" name=\"tech\" placeholder=\"Add tech\" size=\"40\">\n"
       "      </p>\n"
       "      <p class=\"control\">\n"
       "        <button class=\"button is-info\" type=\"submit\" value=\"Submit\" id=\"submit\" tabindex=\"2\">Add</button>\n"
       "      </p>\n"
       "    </div>\n"
       "  </div>\n"
       "</form>\n"
       "</div>\n");
}

void
html_tech(void)
{
  PGresult *res;

  if((res = db_query("SELECT id, name FROM %s ORDER BY name;", TBL_TECH)) != NULL)
  {
    int row = 0, rows = PQntuples(res);
    int col = 0;

    puts("<div id=\"tech\">\n"
         "  <div class=\"field is-grouped is-grouped-multiline\">\n"
         "  <table>");

    for(; row < rows; row++)
    {
      int id = atoi(PQgetvalue(res, row, 0));
      char *name = PQgetvalue(res, row, 1);

      if(col == 0)
        puts("    <tr>");

      printf("      <td>\n"
             "        <div class=\"control\">\n"
             "          <div class=\"tags has-addons are-medium\">\n"
             "            <a href=\"?deltech=%d\" class=\"tag is-delete is-info\"></a>\n"
             "            <a href=\"?edittech=%d\" class=\"tag is-info is-light\">%s</a>\n"
             "          </div>\n"
             "        </div>\n"
             "      </td>\n", id, id, name);

      if(++col == 8)
      {
        col = 0;
        puts("    </tr>\n");
      }
    }

    if(col)
      puts("    </tr>");

    puts("  </table>\n"
         "  </div> <!-- /field -->\n"
         "</div> <!-- /tech -->\n");

    puts("<div id=\"talking\">\n"
         "  <br><br>\n"
         "  <h1>Talking Points</h1>\n"
         "  <table class=\"table is-hoverable\">\n"
         "    <thead><tr><td>Customer</td><td>Technology</td><td>Talking Point</td></tr></thead>\n"
         "    <tbody>\n"
         "    <tr><td>Initech</td><td>Xerox Copiers</td><td>CVE 04-15-01 Vulnerability in Xerox Firmware</td></tr>\n"
         "    <tr><td>Wonka Industries</td><td>MPLS</td><td>VeloCloud SD-WAN Promotion</td></tr>\n"
         "  </table>\n"
         "</div>\n");

  }
  PQclear(res);
}
