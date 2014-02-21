/* You are given a deck containing N cards.  While holding the deck:

1. Take the top card off the deck and set it on the table
2. Take the next card off the top and put it on the bottom of the deck
in your hand.
3. Continue steps 1 and 2 until all cards are on the table.  This is a
round.
4. Pick up the deck from the table and repeat steps 1-3 until the deck
is in the original order.

Write a program to determine how many rounds it will take to put a
deck back into the original order.  This will involve creating a data
structure to represent the order of the cards. Do not use an array.
This program should be written in C only. It should take a number of
cards in the deck as a command line argument and write the result to
stdout.  */

#include<stdio.h>
#include<stdlib.h>

// One node is one card
struct p{
	int data;
	struct p* next;
};

// Initial creation of deck given the number of cards
struct p* create_deck(int N)
{
	int i;
	struct p *start, *end;
	start = NULL;
	for (i=0;i<N;i++)
	{
		struct p* new_node = (struct p*) malloc(sizeof(struct p));
		new_node->data = i;
		new_node->next = NULL;
		if (start==NULL)
			start = new_node;
		else
			end->next = new_node;
		end  = new_node;
	}
	return start;
}

// Round of placing cards on table
struct p* shuffle(struct p* start)
{
	struct p *start_t, *temp, *end;

	//Find the end node of the deck at hand
	for (temp=start;temp->next!=NULL;temp=temp->next);
	end = temp;

	// Start the round
	start_t = NULL;
	while(start!=NULL)
	{
		if (start_t==NULL)
		{
			start_t = start;
			start = start->next;
			start_t->next = NULL;
		}
		else
		{
			temp = start_t;
			start_t = start;
			start = start->next;
			start_t->next = temp;
		}
		if ((start!=NULL) && (start->next!=NULL))
		{
			end->next = start;
			end = start;
			start = start->next;
			end->next = NULL;
		}
	}
	return start_t;
}

// Checks whether deck is in initial order
int check_order(struct p* start)
{
	struct p* temp;
	int d;
	d = start->data;
	for (temp=start->next;temp!=NULL;temp=temp->next)
	{
		if (d>temp->data)
		{
			return(0);
		}
		d = temp->data;
	}
	return(1);
}

// Main function
int main ( int argc, char *argv[] )
{
	int N, num_rounds;
	int sorted;
	struct p *start, *end;
	if ( argc != 2 )
	{
		printf("Argument missing!! Exiting...");
		exit(1);
	}
	sscanf(argv[1],"%d",&N);
	if (N<=1)
	{
		printf("Please input a number greater than 1.. Exiting...");
		exit(2);
	}
	start = create_deck(N);		// Initial creation of deck in hand
	start = shuffle(start);		// Round of placing deck on table
	num_rounds = 1;

	// Do multiple rounds to arrive at initial order
	while(1)
	{
		sorted = check_order(start);
		if (sorted)
			break;
		start = shuffle(start);
		num_rounds = num_rounds + 1;
	}

	// Print result
	printf("Number of rounds to arrive at the initial order = %d",num_rounds);

	// Free memory
	while(start!=NULL)
	{
		end = start;
		start = start->next;
		free(end);
	}
	return 0;
}