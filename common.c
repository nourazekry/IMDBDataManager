#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

void get_column(char *line, char *column, int ncol){
  int col, myCol, count, i;

  if(ncol == 1){
    col = 0;
    for(i = 0; i < strlen(line); i++){
      if(line[i] == '\t'){
        myCol = i;
        break;
      }
    }

  }else{

    count = 0;
    for(i = 0; i < strlen(line); i++){

      if(line[i] == '\t'){
        count++;
        if(count == (ncol)){
          myCol = i;
          break;
        }
        if(count == (ncol - 1)){

          col = i + 1;
        }
      }
    }

  }

  if(count != ncol && ncol != 1){
	for(i = 0; i < strlen(line); i++){
	  if(line[i] == '\n'){
         	myCol = i;
		break;
         }
	} 
  }

  line = line + col;
  strncpy(column, line, myCol - col);
  column[(myCol - col)] = '\0';
  for(i = 0; i < strlen(column); i++){
	if(column[i] == '\n'){
		column[i]= '\0';
	}
 }

}

char *reverse(char *string){
 int i, end;
	char *reversed;
        reversed = malloc(strlen(string)+1);
        end = strlen(string) - 1;
        for(i = 0; i < strlen(string); i++)
        {
                reversed[i] = string[end];
                end--;
        }
        reversed[i] = '\0';
 return reversed;
}
