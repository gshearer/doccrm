#include "misc.h"

char *
str_split(char **string, const char *seperator)
{
  if(string && *string && **string)
  {
    char *firsthalf = *string;

    if((*string = strpbrk(*string, seperator)))
    {
      *(*string) = '\0';
      (*string) += strlen(seperator);
      return(firsthalf);
    }
    else
      *string = firsthalf;
  }
  return(NULL);
}

int
parse_qs_opts(char *str, char *args[], char *vals[], int maxargs)
{
  char *z = str;
  int x = 0;

  for(; x < maxargs; x++)
    args[x] = vals[x] = NULL;

  x = 0;

  while(x < maxargs)
  {
    char *t = strchr(z, '&'), *u;

    args[x] = z;

    if(t)
    {
      *t = '\0';
      z = t + 1;
    }

    if((u = strchr(args[x], '=')))
    {
      *u = '\0';
      vals[x] = u + 1;
    }

    x++;

    if(t == NULL)
      break;
  }
  return(x);
}

int
parse_form_vars(char *result_array[], const char *parsers[], char *data, const int num_parsers)
{
  char *z = data, *z_tag;
  int x = 0;

  for(; x < num_parsers; x++)
  {
    int parser_len = strlen(parsers[x]);

    if(!strncasecmp(z, parsers[x], parser_len))
    {
      z += parser_len;

      if(*z == '=')
      {
        result_array[x] = z + 1;
        if((z_tag = strchr(z + 1, '&')))
        {
          z = z_tag + 1;
          *z_tag = '\0';
        }
        else
          z += strlen(z);
      }
      else
        break;
    }
    else
      break;
  }
  return(x);
}

void
convert_postdata(char *d, char *s, int len)
{
  char temphex[3];
  int hex;

  do {
    if(*s == '%') 
    {
      temphex[0] = *++s;
      temphex[1] = *++s;
      temphex[2] = '\0';

      sscanf(temphex, "%x", &hex);

      if(hex!=13)
        *d++ = (char)hex;
    }
    else if(*s == '+')
      *d++ = ' ';
    else
      *d++ = *s;

  } while(*s++ && len--);
}

int
find_id(const struct genid genids[], const int id)
{
  int x = 0;
  for(;x < 1000 && genids[x].id != id; x++);
  return((x == 1000) ? -1 : x);
}
