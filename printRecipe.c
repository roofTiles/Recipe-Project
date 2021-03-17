#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

/* Prints all recipe summaries */
void print_all(){
  int i;
  for (i = 0; i < numOfRecipes; i++){
    print_summary(i);
  }
}

/* Prints recipe summaries with prep time less than given */
void print_prep(){
  int h, m, validInput;

  // Getting valid time
  validInput = FALSE;
  while (!validInput){
    printf("Enter time (h m):  ");
    scanf("%d %d", &h, &m);
    if (h > -1 && m > -1 && m < 60){
      validInput = TRUE;
    }else{
      validInput = FALSE;
      invalid_input();
    }
  }

  // Printing recipes with prep time less than or equal to given
  int i;
  for (i = 0; i < numOfRecipes; i++){
    int* time;
    time = recipes[i].prep_time;
    if (h > *time){ // if greater hour
      print_summary(i);
    }

    else if (h == *time && m >= *(time + 1)){ // if equal hour but less minutes
      print_summary(i);
    }
  }
}

/* Prints recipe summaries with a given category */
void print_category(){
  char input[CHAR_SIZE];
  int validInput = FALSE;
  while (!validInput){
    printf("Enter category:  ");
    getchar(); // remove newline character in stdin buffer
    scanf("%[^\n]", input);
    int presentCategory = addCategory(input, FALSE); // check if category present in database
    if (presentCategory){ validInput = TRUE; }
    if (!presentCategory){ invalid_input(); }
  }

  // print recipe summaries with given category
  int i;
  for (i = 0; i < numOfRecipes; i++){
    Recipe currentRecipe = recipes[i];
    int j;
    for (j = 0; j < CATEGORIES_PER_RECIPE; j++){
      if (strcmp(currentRecipe.categories[j], input) == 0){ print_summary(i); }
    }
  }
}

/* Prints out an entire recipe */
void print_recipe(){

  // Getting valid recipe number
  int input, validInput;
  validInput = FALSE;
  while (!validInput){
    printf("Enter recipe number:  ");
    scanf("%d", &input);
    if (input >= 0 && input < numOfRecipes){ validInput = TRUE; }
    else{ invalid_input(); }
  }

  // Printing given recipe
  Recipe currentRecipe = recipes[input];
  printf("Recipe:      %s\n", currentRecipe.title);
  printf("By:          %s\n", currentRecipe.author);
  printf("Prep Time:   %d:%02d\n", currentRecipe.prep_time[0], currentRecipe.prep_time[1]);
  printf("Categories:  %s\n", currentRecipe.categories[0]);
  int i = 1;
  while (findDescriptorLength((char *) currentRecipe.categories[i]) != 0){
    printf("             %s\n", currentRecipe.categories[i]);
    i++;
  }
  printf("\n");
  printf("Ingredients:\n");
  printf("%s", currentRecipe.ingredients);
  printf("Instructions:\n");
  printf("%s", currentRecipe.instructions);
}

/* Prints short summaries for each recipe */
void print_summary(int recipeNum){
  Recipe currentRecipe = recipes[recipeNum];
  printf("%*d.  ", ID, recipeNum%1000); // ensures ID is less than 3 characters even if recipeNum > 999
  printChars(currentRecipe.title, NAME);
  printf("  ");
  printChars(currentRecipe.author, AUTHOR);
  printf("  %*d:%0*d  ", HOUR, currentRecipe.prep_time[0] % 10, MINUTE, currentRecipe.prep_time[1]); // printing prep time

  
  char categories[31];
  int length, c, index;
  length = 0;
  for (index = 0; index < CATEGORIES_PER_RECIPE; index++){
    char* currentCategory = (char*) (currentRecipe.categories + index);
    int currentLength = findDescriptorLength(currentCategory);

    // copy category descriptor if short
    if (currentLength + length + 1 <= 31 && currentLength != 0){
      copyChars(categories, currentCategory, length);
      categories[currentLength + length] = ',';
      length += currentLength + 1;
    }

    if (currentLength + length > 30){ // ensures no shorter subsequent descriptors added
      break;
    }
  }

  categories[length - 1] = '\0'; // replacing last comma with null terminator
  
  printf("%s", categories);
  printf("\n");
}


/* Finds length of given string */
int findDescriptorLength(char* category){
  int i = 0;
  while (*(category + i) != '\0'){
    i++;
  }
  return(i);
}

/* Copies characters to a string after an index */
void copyChars(char* dest, char* src, int index){
  int i = 0;
  while (*(src + i) != '\0'){
    *(dest + index + i) = *(src + i);
    i++;
  }
}


/* Prints n specific characters of a given string */

void printChars(char* str, int nChars){
  int i = 0;
  while (*(str + i) != '\0' && i < nChars){
    printf("%c", *(str + i));
    i++;
  }

  int spaces;
  for (spaces = i; spaces < nChars; spaces++){
    printf(" ");
  }

}
