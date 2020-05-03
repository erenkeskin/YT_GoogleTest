#include <stdio.h>
#include <stdlib.h>
#include "../inc/linkedlist.h"

//
struct node * linkedlist_newNode(int data)
{
    struct node * newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

//
int linkedlist_insertBefore(struct node ** list, int data)
{
    struct node * iterator = linkedlist_newNode(data);
    struct node * temporary = *list;

    iterator->next = temporary;
    *list = iterator;

    return SUCCESS;
}

//
int linkedlist_insertAfter(struct node ** list, int data)
{
    struct node * iterator = *list;

    if(iterator == NULL) {
        iterator = linkedlist_newNode(data);
        *list = iterator;
        return SUCCESS;
    }

    while(iterator->next != NULL) {
        iterator = iterator->next;
    }

    iterator->next = linkedlist_newNode(data);

    return SUCCESS;

}

//
int linkedlist_insertAtAnyPosition(struct node ** list, int data, int position) 
{
    
    struct node * iterator = *list;
    struct node * newNode = linkedlist_newNode(data);

    if(iterator == NULL) {
        iterator = linkedlist_newNode(data);
        *list = iterator;
        return SUCCESS;
    }

    if ((position < 0) || (position > linkedlist_getSizeofList(&iterator))) {
        return BOUNDRY_FAIL;
    }

    if((position == 0)) {
        linkedlist_insertBefore(&iterator, data);
        *list = iterator;
        return SUCCESS;
    }

    

    for (int i = 0; i < (position - 1); i++) {
        iterator = iterator->next;
    }

    newNode->next = iterator->next;
    iterator->next = newNode;
    
    return SUCCESS;
}

//
int linkedlist_removeFromHead(struct node ** list)
{
    struct node * iterator = *list;
    struct node * temporary = (struct node *) malloc(sizeof(struct node));

    if(iterator == NULL) {
        return NULL_LIST;
    }

    if(linkedlist_getSizeofList(&iterator) == 1) {
        free(*list);
        *list = NULL;
        return SUCCESS;
    }

    temporary = iterator->next;
    free(iterator);
    *list = temporary;

    return SUCCESS;
}

//
int linkedlist_removeFromEnd(struct node ** list)
{
    struct node * iterator = *list;
    struct node * temporary = (struct node *) malloc(sizeof(struct node));

    if(iterator == NULL) {
        return NULL_LIST;
    }

    if(linkedlist_getSizeofList(&iterator) == 1) {
        free(*list);
        *list = NULL;
        return SUCCESS;
    }

    while(iterator->next != NULL) {
        temporary = iterator;
        iterator = iterator->next;
    }

    temporary->next = NULL;
    free(iterator);    

    return SUCCESS;
}

//
int linkedlist_removeAtAnyPosition(struct node ** list, int position)
{   
    struct node * iterator = *list;

    if(iterator == NULL) {
        return NULL_LIST;
    }

    if ((position < 0) || (position > linkedlist_getSizeofList(&iterator))) {
        return BOUNDRY_FAIL;
    }

    if((position == 0)) {
        linkedlist_removeFromHead(&iterator);
        *list = iterator;
        return SUCCESS;
    }

    struct node * nextList = (struct node *) malloc(sizeof(struct node));

    for(int i = 0; i < (position - 1); i++) {
        iterator = iterator->next;
    }

    nextList = iterator->next->next;
    free(iterator);
    iterator->next = nextList;

    return SUCCESS;
}

//
int linkedlist_getSizeofList(struct node ** list)
{
    struct node * iterator = *list;
    int size = 0;

    if(iterator == NULL) {
        return NULL_LIST;
    }

    while(iterator != NULL) {
        size++;
        iterator = iterator->next;
    }

    return size;
}

//
int linkedlist_getDataFromAnyPosition(struct node ** list, int position)
{
    struct node * iterator = *list;

    //
    if((position < 0) || (position > linkedlist_getSizeofList(&iterator))) {
        return BOUNDRY_FAIL;
    }

    //
    if (position == linkedlist_getSizeofList(&iterator)) {
        position -= 1;
    }

    for (int i = 0; i < position; i++) {
        iterator = iterator->next;
    }

    return iterator->data;
}

//
void linkedlist_printList(struct node ** list)
{
    struct node * iterator = *list;

    if(iterator == NULL) {
        return;
    }

    while(iterator != NULL) {
        printf("%d\n", iterator->data);
        iterator = iterator->next;
    }
}