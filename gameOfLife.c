#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The maximum height of the table in which the colony is stored */
#define M 10   /* = number of lines */
/* The maximum width of the table in which the colony is stored */
#define N 10   /* = number of columns */
//* The value of the table cells representing living cells */
#define LIVE 1
/* The value of the table cells representing dead cells */
#define DEAD 0
#define MAXSTEPS 200

/* Function statement */
void  display(int field[][N]);
int load(int field[][N]);
int count_neighbors(int arr[][N], int r, int c);
int nextfield (int field[][N]);


int main()
{
	int field[M][N] = { DEAD };
	int count = 0;
	int steady  = 0;

	/* Initialization of the colony */
	load(field);

	/* Up to a maximum number of repetitions or until the colony stabilizes */
	while (count < MAXSTEPS && !steady)
	{
		display(field);
		steady = nextfield(field);
		if (steady)
			printf("\n\tReached a steady state.\n");
		count ++;
		system("pause");
	}
	if (count >= MAXSTEPS )
		printf ("Max number of steps reached");
	return  count;
}


/* Initial state of the colony */
/* example of a colony measuring 10 by 10 */
int load(int field[][N])
{
	int temp[3][5] = { {DEAD, LIVE, LIVE, LIVE, LIVE },
					   {DEAD, LIVE, DEAD, LIVE, DEAD},
					   {DEAD, LIVE, LIVE, LIVE, DEAD} };
	int i, j;

	for (i=0; i<3; i++)
		for (j=0; j<5; j++)
			/* Position the temp panel just starting from the center point
of the colony  */
			field[M/2+i][N/2+j] = temp[i][j];
	return 0;
}


/* Colony printing */
void  display(int field[][N])
{
	int x, y;			
	for (x=0; x<M; x++)	
	{
		for (y=0; y<N; y++)
		{				/* if the item is equal to 0 print (-) */
			if (field[x][y] == 0)
				printf("-");
			else		/* otherwise print (*) */
				printf("*");
		}
			printf("\n"); 
	}
		
}


/* Count the number of neighbors in cell r, c that are alive*/
int count_neighbors(int arr[][N], int r, int c)
{
	int x1, y1, q, w, count1;
	if (1+r==10)		/* check the position of the item */
		q=9;			/* in relation to the right and bottom   */
	else 				/* able limits so as not to     */
		q=(1+r);		/* overcome during check     */
	if (1+c==10)		/* of neighboring elements.	   */
		w=9;
	else 
		w=(1+c);
	count1=0;			
	for (x1=((-1)+r); x1<=(q); x1++)
	{ 					/*access part of the table with adjacent elements*/
	  if (x1<0)			/* left border control */
	  	x1=0;  
  	  for (y1=((-1)+c); y1<=(w); y1++)
  	  { 
	  	if (y1<0)		/* upper limit check */
	  		y1=0; 	
  	  	if (arr[x1][y1]==1) /* count live  */
		 	count1++; 		/* neighboring cells */
	  }
    }
  if (arr[r][c]==1)	/* because we check the very */ 
  	count1-=1;		/* cell, we remove it from the counter*/
  	
  return count1;	/* return of a multitude of the living */ 

}	


int nextfield (int field[][N])
{
  int x, y, d;			/*auxiliary variables */
  int temp[M][N];		
  for (x=0; x<=9; x++)	/* table access */
  	for (y=0; y<=9; y++)
  	{  
  	  if (field[x][y]==1) /*if the cell is alive*/
  	  {                   /*if it has 2 or 3 living neighboring cells*/
  	    if ((count_neighbors(field, x, y)==2) || (count_neighbors(field, x, y)==3))
  	    	temp[x][y]=1; /* remains alive */
  	    else 	  		  /* otherwise   */
  	        temp[x][y]=0; /* is dying */
	  }
	  else				 /*otherwise (if dead)*/
	   if ((count_neighbors(field, x, y)==3)) 
	    temp[x][y]=1;	 /* with 3 live neighbors, comes to life */
	   else				 /*otherwise */
	    temp[x][y]=0;	 /*remains dead*/
	  }
	for (x=0; x<=9; x++)			/*panel access and control */
	 for (y=0; y<=9; y++)  			/*compared to the previous one */
	  if (temp[x][y]==field[x][y])  /*status for changes */
	   d=1;							/*if no changes have been made*/ 
	  else 							/*otherwise */
	 { 
	   d=0;
	   for (x=0; x<=9; x++)		   /*if changes have been made*/
  	    for (y=0; y<=9; y++)       /* copy temporary */
  	     field[x][y]=temp[x][y];   /* in a regular table*/
  	  }
  	  		
		/*if we have any change d will get value 0 
		otherwise will get the value 1, the function returns d*/
  	
  	    return d;
	

}
