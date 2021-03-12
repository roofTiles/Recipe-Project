#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

char recipeHeader[] = "                             ************************\n";

void parseDatabase(){
  int numOfRecipes = 0;
  char *line;
  parseLine(&line);
  while (*(line) != EOF){
    if (strcmp(line, recipeHeader) == 0){
      numOfRecipes++;
    }
    free(line);
    parseLine(&line);
  }
  printf("Parsed %d recipes\n", numOfRecipes);
  
}


/* Parses a line in database */
void parseLine(char** line){
  int size = 1;
  char c;
  *line = (char*) malloc(size); // changing address pointer refers to
  do{
    c = fgetc(database);
    *(*line + size - 1) = c; // adds current characters in line to array
    size++;
    *line = (char*) realloc(*line, size); // increases size of char array when necessary
  }while(c != '\n' && c != EOF);
  *(*line + size-1) = '\0';  // add null terminator for string comparison
}
