#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary.h"
#include "title.h"


void add_node(struct tree **root, char *string, void *element){
   if(*root){
     if(strcmp(string, (*root)->key) < 0){
      add_node(&((*root)->children[0]), string, element);
     }else{
      add_node(&((*root)->children[1]), string, element);
     }
   }else{
     (*root) = malloc(sizeof(struct tree));
     (*root)->key = string;
     (*root)->data = element;
     (*root)->children[0] = NULL;
     (*root)->children[1] = NULL;
   }
}

struct tree *find(struct tree *root, char *target){

   if(root){
     if(strcmp((root->key), target) == 0){

      	return root;
     }

     if(strcmp(target, (root->key))<0){
         return find(root->children[0], target);
     }else{
       return find(root->children[1], target);
     }
   }else{
     return NULL;
   }
}
