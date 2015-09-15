/*
 * Author		      :	Nikhil Gopalakrishna (ngopalak@usc.edu)
 * File			         :	my402list.c
 * Description 	:	The file implements the warmup assignment 1, Section (A) : Doubly Circular Linked List
 *
 */

/*****************************************************************
 *                     INCLUDES
 *****************************************************************/

 #include "cs402.h"
 #include "my402list.h"
 #include <stdlib.h>
 #include <string.h>

 /****************************************************************
 *                    DEFINES
 *****************************************************************/

 /****************************************************************
 *                   Globals
 *****************************************************************/

 /****************************************************************
 * 					FUNCTION DEFINITIONS
 *****************************************************************/
/*****************************************************************
Procedure 		:	My402ListLength
Description		:   Returns the number of elements in the list
Input 			      :	*list
Returns			   :   Length of the list (int)
*****************************************************************/
int  My402ListLength(My402List *list)
{
    return(list->num_members);
}

/*****************************************************************
Procedure 		:	My402ListEmpty
Description		:   Returns TRUE if the list is empty. Returns FALSE otherwise.
Input 			      :	*list
Returns			   :    1(TRUE)/ 0(FALSE)
*****************************************************************/
int  My402ListEmpty(My402List *list)
{

    if(!(My402ListLength(list)))
    	return(TRUE);

    return(FALSE);

}


/*****************************************************************
Procedure 		:	My402ListAppend
Description		:   If list is empty, just add obj to the list. Otherwise, add obj after Last().
                            This function returns TRUE if the operation is performed successfully and returns FALSE otherwise.
Input 			      :	*list, *obj
Returns		    	:   1(TRUE)/ 0(FALSE)
*****************************************************************/
int  My402ListAppend(My402List *list, void *obj)
{
    My402ListElem *anchor = &(list->anchor);

    My402ListElem *new = (My402ListElem*)malloc(sizeof(My402ListElem));
    new->next = NULL;
    new->prev = NULL;
    new->obj = obj;


    if(My402ListEmpty(list))
    {
       new->next = anchor;
       new->prev = anchor;
       anchor->next = new;
       anchor->prev = new;
       list->num_members++;
       return(TRUE);
    }
    else
    {
      My402ListElem *last = My402ListLast(list);

       	 last->next = new;
     	 new->prev = last;
         last = new;
      	 last->next = anchor;
      	 anchor->prev = last;
      	 list->num_members++;

      	 return(TRUE);
     }


     return (FALSE);

}


/*****************************************************************
Procedure 		:	 My402ListPrepend
Description		:   If list is empty, just add obj to the list. Otherwise, add obj before First().
                            This function returns TRUE if the operation is performed successfully and returns FALSE otherwise
Input 			      :	*list, *obj
Returns			   :   1(TRUE)/ 0(FALSE)
*****************************************************************/
int  My402ListPrepend(My402List *list, void *obj)
{
   My402ListElem *new = (My402ListElem*)malloc(sizeof (My402ListElem));
    new->next = NULL;
    new->prev = NULL;
    new->obj = obj;

    My402ListElem *anchor = &(list->anchor);

    if(My402ListEmpty(list))
    {
       new->next = anchor;
       new->prev = anchor;
       anchor->next = new;
       anchor->prev = new;
       list->num_members++;
       return(TRUE);
    }
    else
    {
      My402ListElem *first = My402ListFirst(list);

       	 new->next = first;
     	 first->prev = new;
      	 first = new;
      	 first->prev = anchor;
      	 anchor->next = first;
         list->num_members++;

      	 return(TRUE);

    }

     return (FALSE);
}

/*****************************************************************
Procedure 		:	My402ListUnlink
Description		:   Unlink and delete elem from the list.
Input 		        	:	*list, *elem
Returns	    		:   void
*****************************************************************/
void My402ListUnlink(My402List *list, My402ListElem *elem)
{

      (elem->prev)->next = elem->next;
      (elem->next)->prev = elem->prev;
      free(elem);
      list->num_members--;

}

/*****************************************************************
Procedure 		:	My402ListUnlink
Description		:   Unlink and delete all elements from the list and make the list empty..
Input 		        	:	*list
Returns		    	:   void
*****************************************************************/
void My402ListUnlinkAll(My402List *list)
{

  My402ListElem *elem = NULL;
  My402ListElem *anchor = &(list->anchor);

   while(My402ListLength(list) > 0)
   {
      elem = anchor->next;
      anchor->next = elem->next;
      (elem->next)->prev = anchor;
      free(elem);
      list->num_members--;
    }
}

/*****************************************************************
Procedure 		:	My402ListInsertBefore
Description		:   Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend().
                            This function returns TRUE if the operation is performed successfully and returns FALSE otherwise.
Input 		        	:	*list, *obj, *elem
Returns	    		:   1(TRUE) / 0(FALSE)
*****************************************************************/
int  My402ListInsertBefore(My402List* list, void* obj, My402ListElem* elem)
{
      if(elem == NULL)
      	My402ListPrepend(list, obj);

      else
      {
         My402ListElem *new = (My402ListElem*)malloc(sizeof (My402ListElem));
         new->next = NULL;
  		 new->prev = NULL;
    	 new->obj = obj;

    	 (elem->prev)->next = new;
    	 new->prev = elem->prev;
    	 new->next = elem;
    	 elem->prev = new;
         list->num_members++;

    	 return(TRUE);
     }

     return(FALSE);

}

/*****************************************************************
Procedure 		:	My402ListInsertAfter
Description		:   Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append().
Input 		        	:	*list, *obj, *elem
Returns	    		:   1(TRUE) / 0(FALSE)
*****************************************************************/
int  My402ListInsertAfter(My402List *list, void *obj, My402ListElem *elem)
{
      if(elem == NULL)
      	My402ListAppend(list, obj);

      else
      {
         My402ListElem *new = (My402ListElem*)malloc(sizeof (My402ListElem));
         new->next = NULL;
  		 new->prev = NULL;
    	 new->obj = obj;

    	 (elem->next)->prev = new;
    	 new->next = elem->next;
    	 new->prev = elem;
    	 elem->next = new;
         list->num_members++;

    	 return(TRUE);
     }

     return(FALSE);
}

/*****************************************************************
Procedure 		:	My402ListFirst
Description		:   Returns the first list element or NULL if the list is empty.
Input 		        	:	*list
Returns		    	:    Returns the first list element or NULL if the list is empty.
*****************************************************************/
My402ListElem* My402ListFirst(My402List* list)
{
	My402ListElem *anchor = &list->anchor;

    if(My402ListEmpty(list))
    	return(NULL);
    else
      	return(anchor->next);
}

/*****************************************************************
Procedure 		:	My402ListLast
Description		:   Returns the last list element or NULL if the list is empty
Input 			      :	*list
Returns		    	:   Returns the last list element or NULL if the list is empty
*****************************************************************/
My402ListElem* My402ListLast(My402List *list)
{
    My402ListElem *anchor = &(list->anchor);

    if(My402ListEmpty(list))
    	return(NULL);
    else
      	return(anchor->prev);
}

/*****************************************************************
Procedure 		:	My402ListNext
Description		:   Returns elem->next or NULL if elem is the last item on the list.
Input 		        	:	*list, *elem
Returns		    	:   Returns elem->next or NULL if elem is the last item on the list.
*****************************************************************/
My402ListElem* My402ListNext(My402List *list, My402ListElem *elem)
{

    //My402listElem *anchor = &(list->anchor);

	if(elem == My402ListLast(list))
	  return(NULL);
	else
	  return(elem->next);

}

/*****************************************************************
Procedure 		:	My402ListPrev
Description		:   Returns elem->prev or NULL if elem is the first item on the list
Input 		        	:	*list, *elem
Returns		    	:   Returns elem->prev or NULL if elem is the first item on the list
*****************************************************************/
My402ListElem *My402ListPrev(My402List *list, My402ListElem *elem)
{

    //My402listElem *anchor = &(list->anchor);

	if(elem == My402ListFirst(list))
	  return(NULL);
	else
	  return(elem->prev);

}

/*****************************************************************
Procedure 		:	My402ListFind
Description		:   Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found.
Input 		        	:	*list, *obj
Returns		    	:   Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found.
*****************************************************************/
My402ListElem* My402ListFind(My402List *list, void *obj)
{
	 if(My402ListEmpty(list))
    	return(NULL);
     else
     {
       	My402ListElem *elem = NULL;
        int i =0;

        elem = My402ListFirst(list);

        for(i = My402ListLength(list) ; i>0 ; i--)
     	{

     	    if(elem->obj == obj)
     	     return(elem);

     	    elem = elem->next;
     	}
     }

     return(NULL);
}

/*****************************************************************
Procedure 		:	My402ListInit
Description		:   Initialize the list into an empty list.
Input 		        	:	*list
Returns		    	:   Returns TRUE if all is well and returns FALSE if there is an error initializing the list.
*****************************************************************/
int My402ListInit(My402List *list)
{
         My402List  *list1 = (My402List*)malloc(sizeof(My402List));
         memset(list1, 0, sizeof(My402List));
         My402ListElem *anchor = &(list1->anchor);
         anchor->next = anchor->prev = anchor;
         list->num_members = 0;
         list = list1;
         free(list1);

        My402ListElem *anchor1 = &(list->anchor);

         if((anchor1->next == anchor) && (anchor1->prev == anchor))
         return(TRUE);

         return(FALSE);

}






