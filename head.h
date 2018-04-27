#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef struct Restaurant
{
	char name[31];
	int size;
	int inRestaurantStatus;
	struct Restaurant *next;
}Restaurant;

extern int debug;

void debugInfo(Restaurant *head);
void clearToEoln();
int getPostInt();
char *getName();
int getNextNWSChar();
void addToList(Restaurant **head, Restaurant *last, char* name, int size, int inRestaurantStatus);
void doCallAhead(Restaurant **head, Restaurant *last);
void doAdd(Restaurant **head, Restaurant *last);
int doesNameExist(Restaurant *head, char *name, int inRestaurantStatus);
void updateStatus(Restaurant *head, char *name);
void doWaiting(Restaurant *head);
void retrieveAndRemove(Restaurant **head, int tableSize, Restaurant *last);
void doRetrieve(Restaurant **head, Restaurant *last);
void displayListInformation(Restaurant *head);
void doDisplay(Restaurant *head);
void displayGroupSizeAhead(Restaurant *head, char *name);
int countGroupsAhead(Restaurant *head, char *name);
void doList(Restaurant *head);
void printCommands();
