#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

char recipeHeader[] = "                             ************************\n";
Recipe currentRecipe;

void parseDatabase(){
  int numOfRecipes = 0;
  char *line, ingredients, instructions;
  //char name[CHAR_SIZE], author[CHAR_SIZE], categories[CATEGORIES_PER_RECIPE][CHAR_SIZE];
  
  parseLine(&line);
  while (*(line) != EOF){
    if (strcmp(line, recipeHeader) == 0){
      numOfRecipes++;
      parseRecipeHeaders();
    }
    
    free(line);
    parseLine(&line);
    
  }
  printf("Parsed %d recipes\n", numOfRecipes);
  
}

/* Parses Recipe Headers */
void parseRecipeHeaders(){
  char *line;
  parseLine(&line); //empty line
  free(line);
  
  /* Dish Name Header */
  parseLine(&line);
  sscanf(line, "Recipe:      %[^\n]", currentRecipe.title);
  free(line);

  /* Author Name Header */
  parseLine(&line);
  sscanf(line, "By:          %[^\n]", currentRecipe.author);
  free(line);

  /* Prep Time Header */
  parseLine(&line);
  sscanf(line, "Prep Time:   %d:%d\n", &currentRecipe.prep_time[0], &currentRecipe.prep_time[1]);
  free(line);

  /* Category Headers */
  int categoryIndex = 1;
  parseLine(&line);
  sscanf(line, "Categories:  %[^\n]", currentRecipe.categories[0]);
  free(line);
  parseLine(&line);
  while(strcmp("\n", line) != 0){
    sscanf(line, "             %[^\n]", currentRecipe.categories[categoryIndex]);
    categoryIndex++;
    free(line);
    parseLine(&line);
  }
  printf("%s\n", currentRecipe.categories[1]);
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
  *(*line + size - 1) = '\0';  // add null terminator for string comparison
}
