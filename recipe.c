#include <stdio.h>
#include <stdlib.h>
#include "recipe.h"

FILE *database;

void main(){

  /* Get valid database and read it */
  int valid_database = FALSE;
  while (!valid_database){
    valid_database = get_valid_database();
  }

  /* Parse Database */
  parseDatabase();

  /* Get valid function option and perform it */
  int valid_option;
  while (TRUE){
    valid_option = FALSE;
    printf("1.  Print summary\n2.  Print summary by prep time\n3.  Print summary by category\n4.  Print recipe\n5.  Exit\n");

    while(!valid_option){
      valid_option = get_valid_option();
    }
  }
}



/* Gets input for database and opens it if valid */
int get_valid_database(){
  int input;
  printf("Enter database (0, 1, 2):  ");
  scanf("%d", &input);
  switch(input){
      case 0:
	database = fopen(FIRST_DATABASE, "r");
	break;

      case 1:
	database = fopen(SECOND_DATABASE, "r");
	break;

      case 2:
	database = fopen(THIRD_DATABASE, "r");
	break;

      default:
	invalid_input();
	return(FALSE);
  }

  return(TRUE);
}

/* Gets input for action and performs it if valid */
int get_valid_option(){
  int input;
  printf("Enter option:  ");
  scanf("%d", &input);
  switch(input){
    case 1:
      // print_all()
      break;
      
    case 2:
      // print_prep()
      break;

    case 3:
      // print_category()
      break;

    case 4:
      // print_recipe()
      break;

    case 5:
      exit(1);

    default:
      invalid_input();
      return(FALSE);
  }

  return(TRUE);
}


/* Outputs invalid input if given */
void invalid_input(){
  printf("Invalid input\n");
}
