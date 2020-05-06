#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "principals.h"
#include "name.h"
#include "binary.h"

struct array *get_principals(char *directory){
  char *path;
  char *filename;
  char *column, *tconst, *nconst, *characters;
  struct title_principals *principals;
  struct array *ptr;
  FILE *fp;
  char buff[1024];
  char *found;
  int col;
  unsigned long lines, i;


  ptr = malloc(sizeof(struct array));
  filename = "/title.principals.tsv";


  path = malloc(strlen(directory) + strlen(filename) +1);

  strcpy(path, directory);

  strcat(path, filename);

  lines = 0;
  fp = fopen(path, "r");

  while(!feof(fp)){

    if(fgets(buff, 2040, fp) == NULL){
      break;
    }
    column = malloc(strlen(buff));
    get_column(buff, column, 4);
    found = strstr(column, "actor");
    if(!found){
      found = strstr(column, "actress");
    }

    if(found){
      lines++;
    }

  }


  fseek(fp, 0, SEEK_SET);

  principals = malloc(sizeof(struct title_principals) * lines);


  i = 0;
  while(!feof(fp) && i < lines){
    if(i == lines){
      break;
    }

    if(fgets(buff, 2040, fp) == NULL){
      break;
    }
    tconst = malloc(strlen(buff));
    nconst = malloc(strlen(buff));
    characters = malloc(strlen(buff));
    column = malloc(strlen(buff));


    get_column(buff, column, 4);
    found = strstr(column, "actor");
    if(!found){
      found = strstr(column, "actress");
    }

    if(found){

     get_column(buff, tconst, 1);
     tconst = reverse(tconst);
     principals[i].tconst = duplicate(tconst);

     get_column(buff, nconst, 3);
     nconst = reverse(nconst);
     principals[i].nconst = duplicate(nconst);
     found = NULL;

     col = 6;

     get_column(buff, characters, col);

     if (strcmp(characters, "\\N") == 0) get_column(buff, characters, col + 1);
     principals[i].characters = duplicate(characters);



   i++;

   }


 }

  ptr->nitems = lines;
  ptr->arrptr = principals;
  ptr->index1 = 0;
  ptr->index2 = 0;

  free(column);
  free(tconst);
  free(nconst);
  free(characters);
  fclose(fp);

  return ptr;
}
void build_tindex_tp(struct array *ptr){
  int i;
  struct title_principals *tp;
  char *string;
   tp = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = tp[i].tconst;
      add_node(&(ptr->index1), string,
                &(tp[i]));
  }
}

struct tree *find_tconst_tp(struct array *ptr, char *key){
  struct tree *found;

  found = find(ptr->index1, key);

  return found;
}
void build_nindex_tp(struct array *ptr){
  int i;
  struct title_principals *tp;
  char *string;
   tp = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = tp[i].nconst;
      add_node(&(ptr->index2), string,
                &(tp[i]));
  }
}

struct tree *find_nconst_tp(struct array *ptr, char *key){
  struct tree *found;

  found = find(ptr->index2, key);
  return found;
}
