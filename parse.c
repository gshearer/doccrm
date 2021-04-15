#include "parse.h"

void
parse_query(const char *t)
{
  char cmdbuf[50], *args[20], *vals[20];
  int numargs;

  if(t == NULL || *t == 0 || *t == '\0')
    return;

  strncpy(cmdbuf, t, 49);

  if((numargs = parse_qs_opts(cmdbuf, args, vals, 20)))
  {
    int x = 0, y = 0;

    /* ?todo */
    if(numargs == 1 && !strncasecmp(args[0], "todo", 4) && vals[0] == NULL)
    {
      html_header("Todo list", 1);
      html_todo(0);
      html_form_todo(0);
      html_trailer();
      return;
    }

    /* ?customers */
    if(numargs == 1 && !strncasecmp(args[0], "customers", 9) && vals[0] == NULL)
    {
      html_header("Customers", 2);
      html_form_addcust();
      html_cust();
      html_form_addcust();
      html_trailer();
      return;
    }

    /* ?editcust */
    if(numargs == 1 && !strncasecmp(args[0], "editcust", 8) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      html_header("Edit Customer", 2);
      html_form_cust(x);
      html_todo(x);
      html_form_todo(x);
      html_form_custtech(x);
      html_form_journal(x);
      html_journal(x);
      html_trailer();
      return;
    }

    /* ?editoem */
    if(numargs == 1 && !strncasecmp(args[0], "editoem", 7) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      html_header("Edit Manufacturer", 4);
      html_form_editoem(x);
      html_trailer();
      return;
    }

    /* ?manufacturers */
    if(numargs == 1 && !strcasecmp(args[0], "manufacturers") && vals[0] == NULL)
    {
      html_header("Manufacturers", 4);
      html_oem();
      html_form_addoem();
      html_trailer();
      return;
    }

    /* ?editdist */
    if(numargs == 1 && !strncasecmp(args[0], "editdist", 8) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      html_header("Edit Distributor", 5);
      html_form_editdist(x);
      html_trailer();
      return;
    }

    /* ?distributors */
    if(numargs == 1 && !strncasecmp(args[0], "distributors", 12) && vals[0] == NULL)
    {
      html_header("Distributors", 5);
      html_disty();
      html_form_adddist();
      html_trailer();
      return;
    }

    /* ?technologies */
    if(numargs == 1 && !strncasecmp(args[0], "technologies", 12) && vals[0] == NULL)
    {
      html_header("Technologies", 3);
      html_tech();
      html_form_addtech();
      html_trailer();
      return;
    }

    /* ?edittech */
    if(numargs == 1 && !strncasecmp(args[0], "edittech", 8) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      html_header("Edit technology", 3);
      html_form_edittech(x);
      html_trailer();
      return;
    }

    /* ?deloem=x */
    if(numargs == 1 && !strncasecmp(args[0], "deloem", 6) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_OEM, x);
      if(res != NULL)
        PQclear(res);
      http_redir("?manufacturers");
      return;
    }

    /* ?deldist=x */
    if(numargs == 1 && !strncasecmp(args[0], "deldist", 7) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_DISTY, x);
      if(res != NULL)
        PQclear(res);
      if((res = db_query("UPDATE %s SET disty='0' WHERE disty='%d';", TBL_TECH, x)) != NULL)
        PQclear(res);
      http_redir("?distributors");
      return;
    }

    /* ?deltech=x */
    if(numargs == 1 && !strncasecmp(args[0], "deltech", 7) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_TECH, x);
      if(res != NULL)
        PQclear(res);
      if((res = db_query("DELETE FROM %s WHERE tech='%d';", TBL_CUSTTECH, x)) != NULL)
        PQclear(res);
      http_redir("?technologies");
      return;
    }

    /* ?delcust=x */
    if(numargs == 1 && !strncasecmp(args[0], "delcust", 7) && vals[0] != NULL && (x = atoi(vals[0])))
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_CUST, x);
      if(res != NULL)
        PQclear(res);
      if((res = db_query("DELETE FROM %s WHERE customer='%d';", TBL_TODO, x)) != NULL)
        PQclear(res);
      if((res = db_query("DELETE FROM %s WHERE cust='%d';", TBL_CUSTTECH, x)) != NULL)
        PQclear(res);
      if((res = db_query("DELETE FROM %s WHERE customer='%d';", TBL_JOURNAL, x)) != NULL)
        PQclear(res);
      http_redir("?customers");
      return;
    }

    /* ?deltodo=x&cust=y */
    if(numargs == 2 && !strncasecmp(args[0], "deltodo", 7) && vals[0] != NULL && (x = atoi(vals[0])) && !strncasecmp(args[1], "cust", 4) && vals[1] != NULL)
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_TODO, x);

      y = atoi(vals[1]);

      if(res != NULL)
        PQclear(res);

      if(y)
      {
        sprintf(cmdbuf, "?editcust=%d", y);
        http_redir(cmdbuf);
      }
      else
        http_redir("?todo");
      return;
    }

    /* ?deljournal=x&cust=y */
    if(numargs == 2 && !strncasecmp(args[0], "deljournal", 10) && vals[0] != NULL && (x = atoi(vals[0])) && !strncasecmp(args[1], "custid", 6) && vals[1] != NULL)
    {
      PGresult *res = db_query("DELETE FROM %s WHERE id='%d';", TBL_JOURNAL, x);

      y = atoi(vals[1]);

      if(res != NULL)
        PQclear(res);

      if(y)
      {
        sprintf(cmdbuf, "?editcust=%d", y);
        http_redir(cmdbuf);
      }
      else
        http_redir("?customers");
      return;
    }
  }
}

void
parse_form_edittech(char *input_buf)
{
  const char *form_parsers[] = { "id", "name", "disty", "notes" };
  char *form_vars[4], genbuf[50000], sql_name[80], sql_notes[100000];
  PGresult *res = NULL;
  int id, disty;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 4) != 4)
    return;

  id = atoi(form_vars[0]);
  disty = atoi(form_vars[2]);

  convert_postdata(genbuf, form_vars[1], 39);
  PQescapeString(sql_name, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[3], 99999);
  PQescapeString(sql_notes, genbuf, strlen(genbuf));

  res = db_query("UPDATE %s SET name='%s', disty='%d', notes='%s' WHERE id='%d';", TBL_TECH, sql_name, disty, sql_notes, id);
  
  if(res != NULL)
    PQclear(res);

  http_redir("?technologies");
}

void
parse_form_adddist(char *input_buf)
{
  const char *form_parsers[] = { "disty" };
  char *form_vars[1], genbuf[2500], sql_dist[100];
  PGresult *res = NULL;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 1) != 1)
    return;

  convert_postdata(genbuf, form_vars[0], 49);
  PQescapeString(sql_dist, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (timestamp, name) VALUES (NOW(), '%s');", TBL_DISTY, sql_dist);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK)
    fprintf(stderr, "parse_form_adddist(): insert error\n");
  else
    http_redir("?distributors");
  
  PQclear(res);
}

void
parse_form_editdist(char *input_buf)
{
  const char *form_parsers[] = { "id", "name", "contacts", "notes" };
  char *form_vars[4], genbuf[50000], sql_name[50], sql_contacts[50000], sql_notes[100000];
  PGresult *res = NULL;
  int id;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 4) != 4)
    return;

  id = atoi(form_vars[0]);

  convert_postdata(genbuf, form_vars[1], 49);
  PQescapeString(sql_name, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[2], 49999);
  PQescapeString(sql_contacts, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[3], 99999);
  PQescapeString(sql_notes, genbuf, strlen(genbuf));

  res = db_query("UPDATE %s SET name='%s', contacts='%s', notes='%s' WHERE id='%d';", TBL_DISTY, sql_name, sql_contacts, sql_notes, id);
  PQclear(res);
  http_redir("?distributors");
}

void
parse_form_addcust(char *input_buf)
{
  const char *form_parsers[] = { "cust" };
  char *form_vars[1], genbuf[2500], sql_cust[100];
  PGresult *res = NULL;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 1) != 1)
    return;

  convert_postdata(genbuf, form_vars[0], 49);
  PQescapeString(sql_cust, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (timestamp, name) VALUES (NOW(), '%s');", TBL_CUST, sql_cust);
  PQclear(res);
 
  http_redir("?customers");
}

void
parse_form_editcust(char *input_buf)
{
  const char *form_parsers[] = { "id", "name", "contacts", "notes" };
  char *form_vars[4], genbuf[50000], sql_name[50], sql_contacts[50000], sql_notes[100000];
  PGresult *res = NULL;
  int id;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 4) != 4)
    return;

  id = atoi(form_vars[0]);

  convert_postdata(genbuf, form_vars[1], 49);
  PQescapeString(sql_name, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[2], 49999);
  PQescapeString(sql_contacts, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[3], 99999);
  PQescapeString(sql_notes, genbuf, strlen(genbuf));

  res = db_query("UPDATE %s SET name='%s', contacts='%s', notes='%s' WHERE id='%d';", TBL_CUST, sql_name, sql_contacts, sql_notes, id);
  PQclear(res);
  sprintf(genbuf, "?editcust=%d", id);
  http_redir(genbuf);
}

void
parse_form_addoem(char *input_buf)
{
  const char *form_parsers[] = { "oem" };
  char *form_vars[1], genbuf[2500], sql_oem[100];
  PGresult *res = NULL;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 1) != 1)
    return;

  convert_postdata(genbuf, form_vars[0], 49);
  PQescapeString(sql_oem, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (timestamp, name) VALUES (NOW(), '%s');", TBL_OEM, sql_oem);
  
  if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK)
    fprintf(stderr, "parse_form_addoem(): insert error\n");
  else
    http_redir("?manufacturers");
  
  PQclear(res);
}

void
parse_form_editoem(char *input_buf)
{
  const char *form_parsers[] = { "id", "name", "contacts", "notes" };
  char *form_vars[4], genbuf[50000], sql_name[50], sql_contacts[50000], sql_notes[100000];
  PGresult *res = NULL;
  int id;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 4) != 4)
    return;

  id = atoi(form_vars[0]);

  convert_postdata(genbuf, form_vars[1], 49);
  PQescapeString(sql_name, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[2], 49999);
  PQescapeString(sql_contacts, genbuf, strlen(genbuf));

  convert_postdata(genbuf, form_vars[3], 99999);
  PQescapeString(sql_notes, genbuf, strlen(genbuf));

  res = db_query("UPDATE %s SET name='%s', contacts='%s', notes='%s' WHERE id='%d';", TBL_OEM, sql_name, sql_contacts, sql_notes, id);
  
  http_redir("?manufacturers");
  PQclear(res);
}

void
parse_form_todo(char *input_buf)
{
  const char *form_parsers[] = { "redircust", "priority", "customer", "todo" };
  char *form_vars[4], genbuf[2500], sql_todo[200];
  PGresult *res = NULL;
  int custnum, prio, redircust = 0;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 4) != 4)
    return;

  redircust = atoi(form_vars[0]);
  prio = atoi(form_vars[1]);
  custnum = atoi(form_vars[2]);

  convert_postdata(genbuf, form_vars[3], 100);
  PQescapeString(sql_todo, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (timestamp, customer, priority, todo) VALUES (NOW(), '%d', '%d', '%s');", TBL_TODO, custnum, prio, sql_todo);
  
  if(redircust)
    sprintf(genbuf, "?editcust=%d", custnum);
  else
    strcpy(genbuf, "?todo");
  http_redir(genbuf);
  PQclear(res);
}

void
parse_form_journal(char *input_buf)
{
  const char *form_parsers[] = { "custid", "journal" };
  char *form_vars[2], genbuf[50000], sql_journal[100000];
  int custid;

  PGresult *res = NULL;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 2) != 2 || !(custid = atoi(form_vars[0])))
    return;

  convert_postdata(genbuf, form_vars[1], 49999);
  PQescapeString(sql_journal, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (timestamp, customer, entry) VALUES (NOW(), '%d', '%s');", TBL_JOURNAL, custid, sql_journal);
  
  if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK)
  {
    sprintf(genbuf, "?editcust=%d", custid);
    http_redir(genbuf);
  }
  
  PQclear(res);
}

void
parse_form_tech(char *input_buf)
{
  const char *form_parsers[] = { "tech" };
  char *form_vars[4], genbuf[2500], sql_tech[40];
  PGresult *res = NULL;

  if(parse_form_vars(form_vars, form_parsers, input_buf, 1) != 1)
    return;

  convert_postdata(genbuf, form_vars[0], 39);
  PQescapeString(sql_tech, genbuf, strlen(genbuf));

  res = db_query("INSERT INTO %s (name) VALUES ('%s');", TBL_TECH, sql_tech);
  
  if(PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_COMMAND_OK)
    http_redir("?technologies");
  
  PQclear(res);
}


void
parse_form_custtech(char *input_buf)
{
  char *id = input_buf, *t, *x, *y, redir[50];
  PGresult *res = NULL;

  if((str_split(&id, "=")) == NULL)
    return;

  if((y = strchr(id, '&')) == NULL)
  {
    sprintf(redir, "?editcust=%s", id);
    http_redir(redir);
    if((res = db_query("DELETE FROM %s WHERE cust='%s';", TBL_CUSTTECH, id)) != NULL)
      PQclear(res);
    return;
  }

  *y++ = '\0';
  sprintf(redir, "?editcust=%s", id);

  if((res = db_query("DELETE FROM %s WHERE cust='%s';", TBL_CUSTTECH, id)) == NULL)
    return;
  PQclear(res);

 
  while(y != NULL)
  {
    if(y == NULL)
      break;

    if(strchr(y, '&') == NULL)
    {
      x = y;
      y = NULL;
    }
    else
      x = strsep(&y, "&");

    if((t = strchr(x, '=')) == NULL)
      return;
    *t = '\0';

    if(*(t+2) == 'n')
    {
      if((res = db_query("INSERT INTO %s (cust, tech) values (%s, %s) ON CONFLICT(cust, tech) DO NOTHING;", TBL_CUSTTECH, id, x)) == NULL)
        return;
      PQclear(res);
    }
  }
  http_redir(redir);
}

void
parse_form(char *data)
{
  char *datatype, *z = data;

  if((datatype = str_split(&z, "=")) && !strncasecmp(datatype, "datatype", 8))
  {
    if((datatype = str_split(&z, "&")) != NULL)
    {
      if(!strncasecmp(datatype, "tech", 4))
      {
        parse_form_tech(z);
        return;
      }

      if(!strncasecmp(datatype, "edittech", 8))
      {
        parse_form_edittech(z);
        return;
      }

      if(!strncasecmp(datatype, "addcust", 7))
      {
        parse_form_addcust(z);
        return;
      }
      
      if(!strncasecmp(datatype, "custtech", 8))
      {
        parse_form_custtech(z);
        return;
      }

      if(!strncasecmp(datatype, "editcust", 8))
      {
        parse_form_editcust(z);
        return;
      }

      if(!strncasecmp(datatype, "todo", 4))
      {
        parse_form_todo(z);
        return;
      }

      if(!strncasecmp(datatype, "journal", 7))
      {
        parse_form_journal(z);
        return;
      }

      if(!strncasecmp(datatype, "adddist", 7))
      {
        parse_form_adddist(z);
        return;
      }

      if(!strncasecmp(datatype, "editdist", 8))
      {
        parse_form_editdist(z);
        return;
      }

      if(!strncasecmp(datatype, "addoem", 7))
      {
        parse_form_addoem(z);
        return;
      }

      if(!strncasecmp(datatype, "editoem", 7))
      {
        parse_form_editoem(z);
        return;
      }
    }
  }
}
