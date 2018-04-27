/* --------------------------------------------------------------------------
*  To Do: implement a customer waiting list that might be used by a restaurant
*  ---------------------------------------------------------------------------
*/

#include "head.h"

int debug = 1;

//debugInfo() function is used when the program is to run in debug mode
void debugInfo(Restaurant *head)
{
	printf("\n");
	printf("Name of group: %s\n", head->name);
	printf("Size of group: %d\n", head->size);

	if(head->inRestaurantStatus == 0)
		printf("Waiting in line.\n");
	else
		printf("Called ahead in line.\n");
}//end of debugInfo()

//clearToEoln() function clears input until next End of Line Character - \n 
void clearToEoln()
{
	int ch;
	do
		ch = getc(stdin);
	while((ch != '\n') && (ch != EOF));
}//end of clearToEoln()

//getNextNWSChar() function reads in until the first Non-White-Space character is read 
//The white space characters are: space, tab \t, newline \n, vertical tab \v, form feed \f, and carriage return \r
int getNextNWSChar()
{
	int ch = getc(stdin);
	
	if(ch == EOF)
		return ch;
	
	while(isspace(ch))
	{
		ch = getc(stdin);
		if(ch == EOF)
			return ch;
	}
	return ch;
}

//getPostInt() function reads in the next Positive Integer or error: 
//This is based on the mathematical definition of a positive integer.
//zero is not counted as a positive number
int getPostInt()
{
	int value = 0;

	//clear white space characters
	int ch = getc(stdin);
	while(!isdigit(ch))
	{
		if('\n' == ch)		//error \n: no integer given
			return 0;
		if(!isspace(ch))	//error non white space: integer not given next
		{
			clearToEoln();
			return 0;
		}
		ch = getc(stdin);
	}

	value = ch - '0';
	ch = getc(stdin);
	
	while(isdigit(ch))
	{
		value = value * 10 + ch - '0';
		ch = getc(stdin);
	}

	ungetc(ch, stdin);		//put the last read character back in input stream

	//Integer value of 0 is an error in this program
	if(value == 0)
		clearToEoln();

	return value;
}//end of getPostInt()

//getName() function reads in the name until the end of the input 
char *getName()
{
	//skip over the white space characters
	int ch = getc(stdin);
	while(isspace(ch))
	{
		if('\n' == ch)		//error \n: no integer given
			return NULL;
		ch = getc(stdin);
	}

	int size = 10;
	char *word = (char *)malloc(sizeof(char) * size);

	//read in character-by-character until the newline is encountered
	int count = 0;

	while(ch != '\n')
	{
		if(count + 1 >= size)
		{
			//to grow n array to make it "dynamically sized" using malloc
			int i;
			size = size* 2;
			char *temp = (char *)malloc(sizeof(char) * size);

			//copy the characters to the new array
			for(i = 0; i < count; i++)
				temp[i] = word[i];

			free(word);
			word = temp;
		}

		word[count] = ch;
		count++;
		word[count] = '\0';

		//read next character
		ch = getc(stdin);
	}

	if(count > 30)
	{
		count = 30;
		word[count] = '\0';
	}

	//clear ending white space characters
	while(isspace(word[count - 1]))
	{
		count--;
		word[count] = '\0';
	}

	return word;
}//end of getName()

//printCommands() function prints out a list of the commands for this program 
void printCommands()
{
	printf("\nThe commands for this program are:\n");
	printf("q - to quit the program\n");
	printf("? - to list the accepted commands\n");
	printf("a <size> <name> - to add a group to the wait list\n");
	printf("c <size> <name> - to add a call-ahead group to the wait list\n");
	printf("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
	printf("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
	printf("l <name> - list how many groups are ahead of the named group\n");
	printf("d - display the wait list information\n");

	//clear input to End of Line
	clearToEoln();
}//end of printCommands()

int main(int argc, char **argv)
{
	Restaurant *head = NULL;
	Restaurant *last = NULL;
	char *input;
	int ch;

	if(argc >= 2)
	{
		if(strcmp(argv[1], "-d") == 0)
		{
			printf("\nDebugging Information: \n");
			debug = 1;
		}
	}

	printf("\n\t\tStarting Restaurant Wait List Program\n\n");
	printf("Enter command: ");

	while((ch = getNextNWSChar ()) != EOF)
	{
		//check for the various commands
		if('q' == ch)
		{
			printf("\nQuitting Program\n");
			return(0);
		}
		else if('?' == ch)
			printCommands();
		else if('a' == ch)
			doAdd(&head, last);
		else if('c' == ch)
			doCallAhead(&head, last);
		else if('w' == ch)
			doWaiting(head);
		else if('r' == ch)
			doRetrieve(&head, last);
		else if('l' == ch)
			doList(head);
		else if('d' == ch)
			doDisplay(head);
		else
		{
			printf("%c - in not a valid command\n", ch);
			printf("For a list of valid commands, type ?\n");
			clearToEoln();
		}
		
		printf("\nEnter commnad: ");
	}

	printf("Quitting Program - EOF reached\n");
	return 1;
}

