/******************************************************************************
 Implementation to test the LinkedLists module.  
 Reads in a large list of words and puts them into the data structure, 
 then prints out the first and last six elements in the data structure as 
 well as the total number of words.
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "LinkedLists.h"

/* Local functions */
/******************************************************************************
 Program to test the Data structure by reading the Data file provided on
 the command line into the structure, printing out the first and last five
 elements and total number of elements.

 Where: int argc     - the number of parameters on the command line
        char *argv[] - Pointer to the command line parameters
 Returns: 0 - success, 
          2 - can't open input file
          1 - Invalid number of parameters
******************************************************************************/
int main(int argc, char* argv[])
  {
  /* declare local variables */
	int numWords = 0;
 	int i = 0;
    	char str[MAX_STR_LENGTH];
	LinkedLists TestLinkedList;
 
   /* One command line argument is required: the file name     */
   if (2 == argc) /* note that argc 2 means one argument given */
     {
      /* Print out an opening message with the file name 
         then try to open the Data file for input (read mode)   */
	fprintf(stdout, "%s is the file being used for testing\n",argv[1]);
        FILE *DataFile = NULL;
        DataFile = fopen(argv[1],"r"); 

      /* Verify that file was opened correctly */
      if (NULL != DataFile)
        {
         /* Initialize the linked list */
	 InitLinkedList(&TestLinkedList);
         ElementStructs *node = NULL;
         
         /* Read all Data from text file */
	
	while (EOF != fscanf(DataFile, "%s", str))
    	{
           node = (ElementStructs*)malloc(sizeof(ElementStructs));
           node->position = numWords;
           strcpy(node->String,str);
           AddToBackOfLinkedList(&TestLinkedList,node);
           //free(node);
    	}
         
         /* Close the Data file */
  	 fclose(DataFile);

         /* Print the first 6 entries */
         fprintf(stdout, "First 6 words in linked list:\n");
	 for(i=0; i<6; i++)
          {
           	printf("%d: %s\n",i+1,TestLinkedList.FrontPtr->ElementPtr->String);
           	TestLinkedList.FrontPtr = TestLinkedList.FrontPtr->Next;
          }
	 for(i=0; i<6; i++)
          {
          	TestLinkedList.FrontPtr = TestLinkedList.FrontPtr->Previous;
          }         
 
         /* Print the last 6 entries */
         fprintf(stdout, "Last 6 words in linked list:\n");
         
	for(i=0; i<6; i++)
         {
          	TestLinkedList.BackPtr = TestLinkedList.BackPtr->Previous;
         }

         for(i=0; i<6; i++)
         {
         	printf("%d: %s\n",TestLinkedList.NumElements-5+i,TestLinkedList.BackPtr->ElementPtr->String);
         	TestLinkedList.BackPtr = TestLinkedList.BackPtr->Next;
	 }

         /* Print total number of words read */
         fprintf(stdout, "Number of words: %d \n", TestLinkedList.NumElements);
         
         /* Remove from front of list, print a message */
	 node = RemoveFromFrontOfLinkedList(&TestLinkedList);    
	 
	 fprintf(stdout, "Remove from front of list, new front is: %s \n", TestLinkedList.FrontPtr->ElementPtr->String);
         fprintf(stdout, "Removed value is: %s \n", node->String);

         
         /* Remove from back of list, print a message */
	 node = RemoveFromBackOfLinkedList(&TestLinkedList);
         
	 fprintf(stdout, "Remove from back of list, new back is: %s \n", TestLinkedList.BackPtr->ElementPtr->String);
         fprintf(stdout, "Removed value is: %s \n", node->String);
           
            
         /* De-allocate the linked list */
         fprintf(stdout, "Destroying the linked list\n"); 
	 DestroyLinkedList(&TestLinkedList);

        } /* if() */
      else
      { /* Error message */
	fprintf(stderr, "Could not open %s\n",argv[1] );
   	exit(2);
   
      } /* if...else() */
     } /* if() */
   else
     { /* Usage message */
  	fprintf(stderr, "Incorrect number of argumets\n");
     	fprintf(stderr, "USAGE: ./TestList inputfile \n");
     	exit(1);

     } /* if...else() */

   return 0;
  } /* main() */

