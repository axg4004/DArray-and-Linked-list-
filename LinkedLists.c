/******************************************************************************
 Implementation of doubly linked lists that holds elements containing 
 a 256 character string and a sequence number.
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "LinkedLists.h"


/******************************************************************************
 Initialize the linked list data structure.  Points to nothing, no entries.

 Where: LinkedLists *ListPtr - Pointer to the linked list to create
 Returns: nothing
 Errors: none
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr)
{
	ListPtr->NumElements = 0;
	ListPtr->FrontPtr = NULL;
	ListPtr->BackPtr = NULL;
}


/******************************************************************************
 Adds a node to the back of the list.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to add to
        ElementStructs *DataPtr - Pointer to the data to add to the list
 Returns: nothing
 Errors: Prints to stderr and exits
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, ElementStructs *DataPtr)
{
	struct LinkedListNodes* node = (struct LinkedListNodes*)malloc(sizeof(LinkedListNodes));
	
	//MALLOC_DEBUG(ListPtr);

	node->ElementPtr = DataPtr;
	node->Next = NULL;
	node->Previous = ListPtr->BackPtr;
	ListPtr->NumElements = ListPtr->NumElements + 1;
	if(ListPtr->FrontPtr != NULL || ListPtr->BackPtr != NULL)
	{
		ListPtr->BackPtr->Next = node;
	}
	else
	{
		ListPtr->FrontPtr = node;
	}
	ListPtr->BackPtr = node;
}

/******************************************************************************
 Removes a node from the front of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.
  
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the node removed or NULL for none
 Errors: none
******************************************************************************/
ElementStructs *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr)
{
	LinkedListNodes *toBeRemoved;
	ElementStructs *data;
	if (ListPtr->FrontPtr == NULL && ListPtr->BackPtr == NULL)
	{
		//printf("List is empty\n");
		return NULL;
	}
	else
	{
		ListPtr->NumElements = ListPtr->NumElements - 1;
		data = ListPtr->FrontPtr->ElementPtr;
		toBeRemoved = ListPtr->FrontPtr;
		ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
		//Sets the back pointer to null
		if(ListPtr->FrontPtr == NULL)
		{
			ListPtr->BackPtr = NULL;
		}
		free(toBeRemoved);
		//FREE_DEBUG(ListPtr);
	
		return data;//Pointer to removed node is returned
	}
}

/******************************************************************************
 Removes a node from the back of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.
 
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the node removed or NULL for none
 Errors: none
******************************************************************************/
ElementStructs *RemoveFromBackOfLinkedList(LinkedLists *ListPtr)
{

	LinkedListNodes *toBeRemoved;
	ElementStructs *data;
	
	if (ListPtr->FrontPtr == NULL && ListPtr->BackPtr == NULL)//ListPtr == NULL?
	{
		//printf("List is empty\n");
		return NULL;
	}

	else
	{
		ListPtr->NumElements = ListPtr->NumElements - 1;
		data = ListPtr->BackPtr->ElementPtr;
		toBeRemoved = ListPtr->BackPtr;
		ListPtr->BackPtr = ListPtr->BackPtr->Previous;
		if(ListPtr->BackPtr == NULL)
		{
			ListPtr->FrontPtr = NULL;
		}
		
		free(toBeRemoved);
		//FREE_DEBUG(ListPtr);
		return data;
	}

}

/******************************************************************************
 De-allocates the linked list and resets the struct fields (in the header) 
 to indicate that the list is empty.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to destroy
 Returns: nothing
 Errors: none
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr)
{
	ElementStructs* freeStruct = NULL;
	//Removes each node one by one till none is left
	while(ListPtr->NumElements)
	{
		freeStruct = RemoveFromBackOfLinkedList(ListPtr);
		free(freeStruct);
	}
	ListPtr->FrontPtr = NULL;
}


/******************************************************************************
 Searches the linked list for a provided word. If found, returns the pointer
 to the element struct. If not found, returns a NULL pointer
 
 Where: LinkedLists *ListPtr - Pointer to the linked list to search
        char *String         - Pointer to the string to search
 Returns: Pointer to the element if found, NULL otherwise
 Errors: none
 * ***************************************************************************/
ElementStructs *SearchList(LinkedLists *ListPtr, char *String)
{
	LinkedListNodes *strList;
	if(ListPtr == NULL)
	{
		return NULL;
	}
	
	else
	{
		strList = ListPtr->FrontPtr;
		while(strList != NULL)
		{

			if(strcmp(strList->ElementPtr->String,String) == 0)
			{
				return strList->ElementPtr;
			}
			strList = strList->Next;
		}
		return NULL;
	}
}
