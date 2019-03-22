/*******************************************************************************
 Program to test the Data structure by reading the Data file provided on
 the command line into the structure, printing out the first and last five
 elements and total number of elements.

 Where: int argc     - the number of parameters on the command line
        char *argv[] - Pointer to the command line parameters
 Returns: 0 - success, 
          2 - can't open input file
          1 - Invalid number of parameters
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "LinkedLists.h"

int main(int argc, char* argv[])
  {
    int numWords = 0;
    char str[MAX_STR_LENGTH];
    LinkedLists TestLinkedList;
    
  
 
   /* One command line argument is required: the file name     */
   if (3 == argc) /* note that argc 2 means one argument given */
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

          
        while (EOF != fscanf(DataFile, "%s", str))
        {
          /* Insert code here to make sure the input data is not too long*/
          /* Read all Data from text file */
           node = (ElementStructs*)malloc(sizeof(ElementStructs));
           node->position = numWords;
           strcpy(node->String,str);
           AddToBackOfLinkedList(&TestLinkedList,node);
           //free(node);
        }
         
         /* Close the Data file */
         fclose(DataFile);

         node = SearchList(&TestLinkedList,argv[2]);
        
         if( node == NULL )
          {
            printf("%s not found in file %s \n",argv[2],argv[1]);
          }
          else
          {
            printf("Found the word %s in file %s\n",argv[2],argv[1]);
          }
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
      fprintf(stderr, "USAGE: ./TestSearch inputfile wordToSearch\n");
      exit(1);
     } /* if...else() */

   return 0;
  } /* main() */
