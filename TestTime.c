#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "Timers.h"
#include "LinkedLists.h"
#include "DynamicArrays.h"
#define INITIAL_SIZE (1000)
#define ITER_DATA (100)
#define ITER_CALCULATION (5000)

DECLARE_REPEAT_VAR(0)

void ReadData(FILE *InputFile, DArray *DynamicArrayPtr);

int main(int argc, char* argv[])
  {
  /* declare local variables */
   int ErrorCode = 0;              
   DArray TestDynamicArray;     
   ElementStructs *node = NULL;
   FILE *DataFile = NULL;          
   int numWords = 0;
   char str[MAX_STR_LENGTH];
   LinkedLists TestLinkedList;

   DECLARE_TIMER(DataInputTimer);
   DECLARE_TIMER(SearchTimer); 
   printf("\nData read time for Dynamic Array\n");

   if (3 == argc) 
     {

      DataFile = fopen(argv[1], "r"); 

      if (NULL != DataFile)
        {
          START_TIMER(DataInputTimer);
      	  BEGIN_REPEAT_TIMING(ITER_DATA,V);

          CreateDArray(&TestDynamicArray,INITIAL_SIZE);
          
          ReadData(DataFile,&TestDynamicArray);
          
          rewind(DataFile);
          END_REPEAT_TIMING;
		      STOP_TIMER(DataInputTimer);
		      PRINT_TIMER(DataInputTimer);
	        PRINT_RTIMER(DataInputTimer,ITER_DATA);

          RESET_TIMER(DataInputTimer);
	  printf("\nData read time for Linked List\n");
		        	 
          DataFile = fopen(argv[1], "r");
          InitLinkedList(&TestLinkedList);
         
          START_TIMER(DataInputTimer);
      	  BEGIN_REPEAT_TIMING(ITER_DATA,V);
          
        while (EOF != fscanf(DataFile, "%s", str))
        {

           node = (ElementStructs*)malloc(sizeof(ElementStructs));
           node->position = numWords;
           strcpy(node->String,str);
           AddToBackOfLinkedList(&TestLinkedList,node);
        }
          rewind(DataFile);

          END_REPEAT_TIMING;
		      STOP_TIMER(DataInputTimer);

		    PRINT_TIMER(DataInputTimer);
	      PRINT_RTIMER(DataInputTimer,ITER_DATA);

         fclose(DataFile);

         Data *value = (Data*)malloc(sizeof(Data));

         printf("\nDynamic Array word search timing\n");
         START_TIMER(SearchTimer);
    	 BEGIN_REPEAT_TIMING(ITER_CALCULATION,V);

         value =(Data*)SearchDArray(&TestDynamicArray,argv[2]);

         END_REPEAT_TIMING;
         STOP_TIMER(SearchTimer);
          
          if( value == NULL )
          {
            printf("%s not found in file %s \n",argv[2],argv[1]);
          }
          else
          {
            printf("Found the word %s in file %s\n",argv[2],argv[1]);
          }

          PRINT_TIMER(SearchTimer);
          PRINT_RTIMER(SearchTimer, ITER_CALCULATION);

          DestroyDArray(&TestDynamicArray);

          printf("\nLinked List word search timing\n");

         START_TIMER(SearchTimer);
    	   BEGIN_REPEAT_TIMING(ITER_CALCULATION,V);

         node =(ElementStructs*)SearchList(&TestLinkedList,argv[2]);
        
         END_REPEAT_TIMING;
         STOP_TIMER(SearchTimer);


         if( node == NULL )
          {
            printf("%s not found in file %s \n",argv[2],argv[1]);
          }
          else
          {
            printf("Found the word %s in file %s\n",argv[2],argv[1]);
          }

          PRINT_TIMER(SearchTimer);
          PRINT_RTIMER(SearchTimer, ITER_CALCULATION);


          DestroyLinkedList(&TestLinkedList);

		} /* if() */
     
      else
        {
         fprintf(stderr,"%s could not open file %s at line %d\n",__FILE__,argv[1],__LINE__);
         fflush(stderr);
         ErrorCode = 2;
         return ErrorCode;
        } /* if...else() */

     } /* if() */
   else
     {
      fprintf(stderr, "USAGE: ./TestTime inputfile wordToSearch\n");
      exit(1);
      
     } /* if...else() */

   return 0;
  } /* main() */

 void ReadData(FILE *InputFile, DArray *DynamicArrayPtr)
  {
   Data TempData;             
   int lcv = 1;               
   int strLen;               
   char String[MAX_STR_LEN];      

   while (EOF != fscanf(InputFile, "%s", String))
     {

      strLen = strlen(String);
      if(strLen >= MAX_STR_LEN){
        fprintf(stderr, "Word consists more than %d characters\n", MAX_STR_LEN);
      }
      else{
        TempData.Num = lcv++;
        strcpy(TempData.String, String);
        PushToDArray(DynamicArrayPtr, &TempData);
      }
     } 
  } 
