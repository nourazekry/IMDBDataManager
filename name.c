#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "name.h"
#include "common.h"
#include "binary.h"

struct array *get_name(char *directory){
  char *path;
  char *filename;
  char *column, *nconst, *name;
  struct name_basics *arr;
  struct array *ptr;
  FILE *fp;
  char buff[256];
  char *found;
  unsigned long lines, i;


  ptr = malloc(sizeof(struct array));
  filename = "/name.basics.tsv";

  path = malloc(strlen(directory) + strlen(filename) +1);

  strcpy(path, directory);

  strcat(path, filename);

  lines = 0;
  fp = fopen(path, "r");

  while(!feof(fp)){

    if(fgets(buff, 256, fp) == NULL){
      break;
    }


    column = malloc(strlen(buff));
    get_column(buff, column, 5);
    found = strstr(column, "actor");

    if(found == NULL){
      found = strstr(column, "actress");
    }

    if(found){
      lines++;
    }

  }

  fseek(fp, 0, SEEK_SET);

  arr = malloc(sizeof(struct name_basics) * lines);


  i = 0;
  while(!feof(fp) && i < lines){

    if(fgets(buff, 256, fp) == NULL){
      break;
    }
    nconst = malloc(strlen(buff));
    name = malloc(strlen(buff));
    column = malloc(strlen(buff));


    get_column(buff, column, 5);
    found = strstr(column, "actor");
    if(!found){
      found = strstr(column, "actress");
    }

    if(found){


     get_column(buff, nconst, 1);
     nconst = reverse(nconst);
     arr[i].nconst = duplicate(nconst);

    get_column(buff, name, 2);
    arr[i].primaryName = duplicate(name);


     i++;

   }
   if(i == lines){
     break;
   }


  }

  ptr->arrptr = arr;
  ptr->nitems = lines;
  ptr->index1 = 0;
  ptr->index2 = 0;

  free(column);
  free(nconst);
  free(name);
  fclose(fp);

  return ptr;
}

char *duplicate(char *string){
  char *new;

  new = malloc(strlen(string) + 1);
  strcpy(new, string);

  return new;

}
void build_pnindex(struct array *ptr){
  int i;
  struct name_basics *names;
  char *string;
   names = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = names[i].primaryName;
      add_node(&(ptr->index1), string,
                &(names[i]));
  }
}
struct name_basics *find_name(struct array *ptr, char *key){
  struct name_basics *found;

  found = (find(ptr->index1, key))->data;
  return found;
}
void build_nindex(struct array *ptr){
  int i;
  struct name_basics *names;
  char *string;
   names = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = names[i].nconst;
      add_node(&(ptr->index2), string,
                &(names[i]));
  }
}
struct name_basics *find_nconst(struct array *ptr, char *key){
  struct name_basics *found;

  found = (find(ptr->index2, key))->data;
  return found;
}
