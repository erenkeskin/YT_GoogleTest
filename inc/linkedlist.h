#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node {
    int data;
    struct node * next;
};

enum RETURN_CODES {
    SUCCESS = 0,
    BOUNDRY_FAIL = -1,
    NULL_LIST = -2
};

//
struct node * linkedlist_newNode(int data);

int linkedlist_insertBefore(struct node ** list, int data);
int linkedlist_insertAfter(struct node ** list, int data);
int linkedlist_insertAtAnyPosition(struct node ** list, int data, int position);

int linkedlist_removeFromHead(struct node ** list);
int linkedlist_removeFromEnd(struct node ** list);
int linkedlist_removeAtAnyPosition(struct node ** list, int position);

int linkedlist_getSizeofList(struct node ** list);
int linkedlist_getDataFromAnyPosition(struct node ** list, int position);

void linkedlist_printList(struct node ** list);


#endif // LINKEDLIST_H