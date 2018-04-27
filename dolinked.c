#include "head.h"

void doAdd(Restaurant **head, Restaurant *last)
{
	//get group size from input
	int size = getPostInt();
	if(size < 1)
	{
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: a <size> <name>\n");
		printf(" where: <size> is the size of the group making the inRestaurantStatus\n");
		printf(" 		<name> is the name of the group making the inRestaurantStatus\n");

		return;
	}

	//get group name from input
	char *name = getName();
	if(NULL == name)
	{
		printf("Error: Add command requires a name to be given\n");
		printf("Add command is of form: a <size> <name>\n");
		printf(" where: <size> is the size of the group making the inRestaurantStatus\n");
		printf("        <name> is the name of the group making the inRestaurantStatus\n");
		return;
	}

	printf("Adding group \"%s\" of size %d\n", name, size);
	
	addToList(&(*head), last, name, size, 0);
}

void doCallAhead(Restaurant **head, Restaurant *last)
{
	//get group size from input
	int size = getPostInt();
	if(size < 1)
	{
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: c <size> <name>\n");
		printf(" where: <size> is the size of the group making the inRestaurantStatus\n");
		printf(" 		<name> is the name of the group making the inRestaurantStatus\n");

		return;
	}

	//get group name from input
	char *name = getName();
	if(NULL == name)
	{
		printf("Error: Call-ahead command requires a name to be given\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf(" where: <size> is the size of the group making the inRestaurantStatus\n");
		printf(" 		<name> is the name of the group making the inRestaurantStatus\n");

		return;
	}

	printf("Call-ahead group \"%s\" of size %d\n", name, size);

	addToList(&(*head), last, name, size, 1);
}

void doWaiting(Restaurant *head)
{
	//get group name from input
	char *name = getName();
	if(NULL == name)
	{
		printf("Error: Waiting command requires a name to be given\n");
		printf("Waiting command is of form: w <name>\n");
		printf(" where: <name> is the name of the group that is now waiting\n");
			
		return;
	}
	
	updateStatus(head, name);
}

void doRetrieve(Restaurant **head, Restaurant *last)
{
	//get table size from input
	int size = getPostInt();
	if(size < 1)
	{
		printf("Error: Retrieve requires an integer value of at least 1\n");
		printf("Retrieve command is of form: r <size>\n");
		printf(" where: <size> is the size of the group making the inRestaurantStatus\n");
		
		return;
	}

	clearToEoln();
	
	printf("Retrieve (and remove) the first group that can fit at a label of size %d\n", size);

	retrieveAndRemove(&(*head), size, last);
}

void doList(Restaurant *head)
{
	//get group name from input
	char *name = getName();
	
	if(NULL == name)
	{
		printf("Error: List command requires a name to be given\n");
		printf("List command is of form: l <name>\n");
		printf(" where: <name> is the name of the group to inquire about\n");
		
		return;
	}

	printf("Group \"%s\" is behind the following groups\n", name);

	displayGroupSizeAhead(head, name);
	
	printf("\nThere are %d groups ahead of %s", countGroupsAhead(head, name), name);
}

void doDisplay(Restaurant *head)
{
	clearToEoln();
	
	printf("Display information about all groups\n\n");

	displayListInformation(head);
}
