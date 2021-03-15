#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recipe.h"

void print_all(){
  int i;
  for (i = 0; i < numOfRecipes; i++){
    print_summary(i);
  }
}

void print_summary(int recipeNum){
  Recipe currentRecipe = recipes[recipeNum];
  printf("%*d.  ", ID, recipeNum%1000); // ensures ID is less than 3 characters even if recipeNum > 999
  printChars(currentRecipe.title, NAME);
  printf("  ");
  printChars(currentRecipe.author, AUTHOR);
  printf("  %*d:%0*d  ", HOUR, currentRecipe.prep_time[0] % 10, MINUTE, currentRecipe.prep_time[1]); // printing prep time

  char* categories;
  int descriptorLength, i;
  strcpy(categories, currentRecipe.categories[0]);
  descriptorLength = strlen(currentRecipe.categories[0]);
  i = 1;
  while ((descriptorLength + (int) strlen(currentRecipe.categories[i]) + 1) < CATEGORY_DESCRIPTORS && i < CATEGORIES_PER_RECIPE){
    if (*(currentRecipe.categories[i]) != '\0'){
      strcat(categories, ",");
      strcat(categories, currentRecipe.categories[i]);
      descriptorLength += strlen(currentRecipe.categories[i]) + 1;
      i++;
    }else{
      break;
    }
  }
  printf("%s", categories);
  printf("\n");
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
