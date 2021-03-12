#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

char all_categories[CATEGORIES_SIZE][CHAR_SIZE];
char recipeHeader[] = "                             ************************\n";
Recipe currentRecipe;
int allCategorySize = 0;

void parseDatabase(){
  int numOfRecipes = 0;
  char *line, ingredients, instructions;
    
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
  char categories[CATEGORIES_PER_RECIPE][CHAR_SIZE];
  
  parseLine(&line);
  sscanf(line, "Categories:  %[^\n]", currentRecipe.categories[0]);
  free(line);
  parseLine(&line);
  addCategory(currentRecipe.categories[0]); // add category to category list
  while(strcmp("\n", line) != 0){
    sscanf(line, "             %[^\n]", currentRecipe.categories[categoryIndex]);
    addCategory(currentRecipe.categories[categoryIndex]); // add category to category list
    categoryIndex++;
    free(line);
    parseLine(&line);
  }

  // resetting any categories not present in current recipe
  while(categoryIndex < CATEGORIES_PER_RECIPE){
    int c;
    for (c = 0; c < CHAR_SIZE; c++){
      currentRecipe.categories[categoryIndex][c] = 0;
    }
    categoryIndex++;
  }
}

/* Parses a line in database */
void parseLine(char** line){
  int size = 1;
  char c;
  *line = (char*) malloc(size * sizeof(char)); // changing address pointer refers to
  do{
    c = fgetc(database);
    *(*line + size - 1) = c; // adds current characters in line to array
    size++;
    *line = (char*) realloc(*line, size * sizeof(char)); // increases size of char array when necessary
  }while(c != '\n' && c != EOF);
  *(*line + size - 1) = '\0';  // add null terminator for string comparison
}

/* Adds a category descriptor to all_categories if not present */
void addCategory(char* category){
  int i;
  for (i = 0; i < allCategorySize; i++){
    if(strcmp(all_categories[i], category) == 0){
      return;
    }
  }

  // copying category if not present in all_categories
  int c;
  for (c = 0; c < CHAR_SIZE; c++){
    all_categories[allCategorySize][c] = *(category + c);
  }
  allCategorySize++;
}
