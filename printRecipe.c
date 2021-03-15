#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"

void print_all(){
  int i;
  for (i = 0; i < numOfRecipes; i++){
    print_summary(i);
  }
}

void print_prep(){
  int h, m, validInput;

  /* Getting valid time */
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
