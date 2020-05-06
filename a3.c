#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "name.h"
#include "principals.h"
#include "binary.h"
#include "common.h"
#include "title.h"

int main(int argc, char* argv[]){
  struct array *title_basics, *name_basics, *title_principals;
  struct title_basics *title;
  struct tree *principals;
  struct name_basics *name;

  char buff[256];
  char *command, *search;
  int i;

  if(argc < 2){
    fprintf( stderr, "Usage:  %s directory\n", argv[0] );
    return -1;
  }
  printf("> ");
  fgets(buff, 256, stdin);
  for(i = 0; i < strlen(buff); i++){
     if(buff[i] == ' '){
       command = malloc(i);
       search = malloc(strlen(buff) - i);
       strncpy(command, buff, i);
       break;
     }

  }
  search = buff + strlen(command) + 1;
  search[strlen(search) - 1] = '\0';
  command[i+1] = '\0';

  title_basics = get_title( argv[1] );

  build_ptindex( title_basics );


  build_tindex( title_basics );


  name_basics = get_name( argv[1] );

  build_pnindex( name_basics );

  build_nindex( name_basics );




  title_principals = get_principals( argv[1] );

  build_tindex_tp( title_principals );

  build_nindex_tp( title_principals );



  if(strcmp(command, "name") == 0){
    name = find_name( name_basics, search);

    principals = find_nconst_tp( title_principals, name->nconst );
      while(1){
        if(principals){
          title = find_tconst( title_basics, ((struct title_principals*)(principals->data))->tconst);
          printf("%s\n", title->primaryTitle );
          printf("%s\n",((struct title_principals*)(principals->data))->characters);
          principals = principals->children[1];
          principals = find(principals, name->nconst);

        }else break;
      }
  }else if(strcmp(command, "title") == 0){

      title = find_primary_title( title_basics, search);
      principals = find_tconst_tp( title_principals, title->tconst);
      while(1){
         if(principals){
           name = find_nconst( name_basics, ((struct title_principals*)(principals->data))->nconst);
           printf("%s\n", name->primaryName );
           printf("%s\n",((struct title_principals*)(principals->data))->characters);
           principals = principals->children[1];
           principals = find(principals, title->tconst);

         }else break;
      }
  }


  free(name_basics);
  free(title_principals);
  free(title_basics);
  free(principals);
  return 0;
}
