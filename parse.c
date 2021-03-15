#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

char all_categories[CATEGORIES_SIZE][CHAR_SIZE];
char recipeHeader[] = "                             ************************\n";
Recipe recipes[NUM_RECIPES];
Recipe currentRecipe;
int allCategorySize = 0;
int bodySize, lineSize;
int recipeNumber = 0;
int numOfRecipes;

void parseDatabase(){
  char *line;
  int endOfFile = FALSE;
  parseLine(&line);
  free(line);
  
  while (!endOfFile){
    parseRecipeHeaders();
    endOfFile = parseRecipeBodies();
    currentRecipe.id = recipeNumber;
    
    recipes[recipeNumber] = currentRecipe;
    recipeNumber++;
  }
 
  printf("Parsed %d recipes\n", recipeNumber);
  numOfRecipes = recipeNumber;
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
      currentRecipe.categories[categoryIndex][c] = '\0';
    }
    categoryIndex++;
  }
}

/* Parses Recipe Bodies */
int parseRecipeBodies(){
  char* line;
  parseLine(&line); // skipping empty line
  free(line);
  
  bodySize = 0;

  /* Parsing Ingredients List */
  char* ingredients = (char*) malloc(0);
  addLinesUntil(&ingredients, "Instructions:\n");
  currentRecipe.ingredients = ingredients;
  free(ingredients);
  
  bodySize = 0;
  
  /* Parsing Recipe Instructions */
  char* instructions = (char*) malloc(0);
  int endOfFile;
  endOfFile = addLinesUntil(&instructions, recipeHeader); // see if EOF char reached yet
  currentRecipe.instructions = instructions;
  free(instructions);
  return(endOfFile);
}

/* Adds lines to a recipe body pointer until a given string */
int addLinesUntil(char** recipeBody, char* endLine){
  char* line;
  parseLine(&line);
  do{
    addLine(recipeBody, line);
    free(line);
    parseLine(&line);
  } while(strcmp(line, endLine) != 0 && *line != EOF);

  // adding null terminator to ingredients
  *recipeBody = (char*) realloc(*recipeBody, sizeof(char) * (bodySize + 1));
  *(*recipeBody + bodySize) = '\0';

  if (*line == EOF){
    return(TRUE);
  }

  return(FALSE);
} 

/* Adds a line to given recipe body pointer */
void addLine(char** body, char* line){
  // increase size of recipe body array
  *body = (char*) realloc(*body, sizeof(char) * (bodySize + lineSize - 1));

  // copying line to end of recipe body
  int i;
  for (i = bodySize; i < (bodySize + lineSize - 1); i++){
    *(*body + i) = *(line + i - bodySize);
  }
  bodySize += lineSize - 1;
}

/* Parses a line in database */
void parseLine(char** line){
  int size = 1;
  char c;
  *line = (char*) calloc(size, sizeof(char)); // changing address pointer refers to
  do{
    c = fgetc(database);
    *(*line + size - 1) = c; // adds current characters in line to array
    size++;
    *line = (char*) realloc(*line, size * sizeof(char)); // increases size of char array when necessary
  }while(c != '\n' && c != EOF);
  *(*line + size - 1) = '\0';  // add null terminator for string comparison
  lineSize = size; // update lineSize
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
