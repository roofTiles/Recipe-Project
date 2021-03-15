/* ENEE 150 Project 2 (Recipe Project) Header File */


/* Boolean Constants */
#define TRUE 1
#define FALSE 0

/* Size Constants */
#define NUM_RECIPES 10000
#define CHAR_SIZE 101
#define CATEGORIES_PER_RECIPE 8
#define CATEGORIES_SIZE 500

/* Output Constants */
#define ID 3
#define NAME 15
#define AUTHOR 15
#define HOUR 1
#define MINUTE 2
#define CATEGORY_DESCRIPTORS 30

/* Database files */
#define FIRST_DATABASE "recipes0.data"
#define SECOND_DATABASE "recipes1.data"
#define THIRD_DATABASE "recipes2.data"

/* Recipe Data Structures */

typedef struct Recipes{
  int id;
  char title[CHAR_SIZE], author[CHAR_SIZE], categories[CATEGORIES_PER_RECIPE][CHAR_SIZE];
  char *ingredients, *instructions;
  int prep_time[2];
} Recipe;

extern FILE *database;
extern Recipe recipes[NUM_RECIPES];
extern char all_categories[CATEGORIES_SIZE][CHAR_SIZE];
extern int numOfRecipes;

/* Handling Input */

int get_valid_database();
int get_valid_option();
int get_valid_type(int *, int *);
void invalid_input();


/* Option Functionality */

void print_all();
void print_prep();
void print_category();
void print_summary(int);
void printChars(char*, int);
void print_recipe(int);

/* Parsing Database */

void parseDatabase();
void parseRecipeHeaders();
int parseRecipeBodies();
int addLinesUntil(char**, char*);
void addLine(char**, char*);
void parseLine(char**);
void addCategory(char*);
