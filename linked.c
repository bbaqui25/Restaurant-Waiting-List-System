#include "head.h"

//addToList() adds a new Restaurant to the end of the linked list.  This is to be used when the a and c commands are given as input. 
void addToList(Restaurant **head, Restaurant *last, char* name, int size, int inRestaurantStatus)
{
	//allocate Restaurant
	Restaurant *newNode = (Restaurant *)malloc(sizeof(Restaurant));
	last = *head;

	//put in the data
	strcpy(newNode->name,name);
	newNode->size = size;
	newNode->inRestaurantStatus = inRestaurantStatus;

	//this new Restaurant is going to be the last Restaurant, so make next of it as NULL
	newNode->next = NULL;

	//if the linked list is empty, then make the new Restaurant as head
	if(*head == NULL)
	{
		*head = newNode;
		return;
	}

	//Else traverse till the last Restaurant
	while(last->next != NULL)
		last = last->next;

	//change the next of last Restaurant
	last->next = newNode;
	return;
}//end of addToList()

//doesNameExist() function indicates whether a name already exist or not
int doesNameExist(Restaurant *head, char *name, int inRestaurantStatus)
{
	while(1)
	{
		if(debug == 1)
			debugInfo(head);
		if(head == NULL)
			return 0;
		if(strcmp(head->name, name) == 0)
		{
			if(head->inRestaurantStatus == 1)
			{
				if(inRestaurantStatus == 1)
				{
					head->inRestaurantStatus = 0;
					printf("%s is waiting for a table.\n", head->name);
				}
				return 1;
			}
			else if(head->inRestaurantStatus == 0)
			{
				printf("%s is on the waiting list.\n", head->name);
				return 1;
			}
		}

		head = head->next;
	}
}//end of doesNameExist

//updateStatus() function changes the in-Restaurant status when a call-ahead group arrives at the restaurant.
void updateStatus(Restaurant *head, char *name)
{
	if(doesNameExist(head, name, 1) == 0)
		printf("%s is not on the list.\n", name);
}//end of updateStatus()

//retrieveAndRemove() function finds the first in-restaurant group that can fit at a given table
void retrieveAndRemove(Restaurant **head, int tableSize, Restaurant *last)
{
	Restaurant *RestaurantPtr;
	Restaurant *temp = *head;

	if(debug == 1)
		debugInfo(*head);
	if((*head)->size <= tableSize)
	{
		RestaurantPtr = *head;
		*head = (*head)->next;
		free(RestaurantPtr);
		return;
	}
	while(temp->next != NULL)
	{
		RestaurantPtr = temp;
		temp = temp->next;

		if(temp->size <= tableSize)
		{
			if(temp == last)
				last = RestaurantPtr;
			RestaurantPtr->next = temp->next;
			free(temp);
			return;
		}
	}
}//end of retrieveAndRemove()

//countGroupsAhead() function returns the number of groups waiting ahead of a group with a specific name
int countGroupsAhead(Restaurant *head, char *name)
{
	int countGroupsAhead = 0;
	while(1)
	{
		if(strcmp(head->name, name) == 0)
			return countGroupsAhead;
		
		countGroupsAhead++;
		
		if(debug == 1)
			debugInfo(head);
		
		if(head == NULL)
			break;
		head = head->next;
	}
}//end of countGroupsAhead()

//displayGroupSizeAhead() function traverses down the list until a specific group name is encountered
void displayGroupSizeAhead(Restaurant *head, char *name)
{
	while(1)
	{
		if(strcmp(head->name, name) == 0)
			return;
		printf("%s has a group of %d.\n", head->name, head->size);
		if(head == NULL)
			break;
		head = head->next;
	}	
}//end of displayGroupSizeAhead()

//isplayListInformation() function traverses down the entire list from beginning to end
void displayListInformation(Restaurant *head)
{
	int countGroup = 0;
	if(head == NULL)
	{
		printf("There is no list available\n");
		return;
	}
	while(1)
	{
		if(head == NULL)
			break;
		if(debug == 1)
			debugInfo(head);
		
		countGroup++;
		
		printf("\t%s", head->name);
		printf("\t%d", head->size);
		
		if(head->inRestaurantStatus == 0)
			printf("\tWaiting in list.\n");
		else
			printf("\tCalled in list.\n");
		head = head->next;
	}
	
	if(countGroup == 1)
		printf("\nThere is %d group.\n", countGroup);
	else
		printf("\nThere are %d groups.\n", countGroup );
}//end of isplayListInformation()
