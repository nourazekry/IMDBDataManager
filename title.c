#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "title.h"
#include "name.h"
#include "binary.h"

struct array *get_title(char *directory){
  char *path;
  char *filename;
  char *column, *tconst, *title;
  struct title_basics *arr;
  struct array *ptr;
  FILE *fp;
  char buff[1024];
  char *found, *isAdult;
  unsigned long lines, i;


  ptr = malloc(sizeof(struct array));
  filename = "/title.basics.tsv";

  path = malloc(strlen(directory) + strlen(filename) +1);

  strcpy(path, directory);

  strcat(path, filename);

  lines = 0;
  fp = fopen(path, "r");

  while(!feof(fp)){

    if(fgets(buff, 1024, fp) == NULL){
      break;
    }

    column = malloc(strlen(buff));
    get_column(buff, column, 2);
    found = strstr(column, "movie");
    get_column(buff, column, 5);
    isAdult = strstr(column, "0");


    if(found && isAdult){

      lines++;
    }

  }

  fseek(fp, 0, SEEK_SET);

  arr = malloc(sizeof(struct title_basics) * lines);


  i = 0;
  while(!feof(fp) && i < lines){

    if(fgets(buff, 1024, fp) == NULL){
      break;
    }
    tconst = malloc(strlen(buff));
    title = malloc(strlen(buff));
    column = malloc(strlen(buff));


    get_column(buff, column, 2);
    found = strstr(column, "movie");
    get_column(buff, column, 5);
    isAdult = strstr(column, "0");


    if(found && isAdult){



     get_column(buff, tconst, 1);
     tconst = reverse(tconst);
     arr[i].tconst = duplicate(tconst);

     get_column(buff, title, 3);
     arr[i].primaryTitle = duplicate(title);


     i++;

   }
   if(i == lines){
     break;
   }


  }

  ptr->nitems = lines;
  ptr->arrptr = arr;
  ptr->index1 = 0;
  ptr->index2 = 0;

  free(column);
  free(tconst);
  free(title);
  fclose(fp);

  return ptr;
}

void build_tindex(struct array *ptr){
  int i;
  struct title_basics *titles;
  char *string;
   titles = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = titles[i].tconst;
      add_node(&(ptr->index2), string,
                &(titles[i]));
  }
}

struct title_basics *find_tconst(struct array *ptr, char *key){
  struct title_basics *found;
  
  found = (find(ptr->index2, key))->data;
  return found;
}

void build_ptindex(struct array *ptr){
  int i;
  struct title_basics *titles;
  char *string;
   titles = (ptr->arrptr);
   for(i = 0; i < ptr->nitems; i++){
    string = titles[i].primaryTitle;
      add_node(&(ptr->index1), string,
                &(titles[i]));
  }
}

struct title_basics *find_primary_title(struct array *ptr, char *key){
  struct title_basics *found;

  found = (find(ptr->index1, key))->data;
  return found;
}
