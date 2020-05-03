#include <gtest/gtest.h>
#include "../src/linkedlist.c"

//
class Linkedlist : public testing::Test
{
    public:
        struct node * list = NULL;

    void SetUp() override {
        list = linkedlist_newNode(0);
    }

    void TearDown() override {
        free(list);
    }
};

// Constructor Test
TEST_F(Linkedlist, create_new_node) 
{
    ASSERT_EQ(list->data, 0);
    ASSERT_EQ(list->next, nullptr);
}

// Insertion Tests
TEST_F(Linkedlist, insert_data_to_end) 
{
    linkedlist_insertAfter(&list, 10);
    ASSERT_NE(list->next, nullptr);
    ASSERT_EQ(list->next->next, nullptr);
    ASSERT_EQ(list->next->data, 10);
}

TEST_F(Linkedlist, insert_data_to_end_null_list) 
{
    struct node * null_list = NULL;
    linkedlist_insertAfter(&null_list, 0);
    
    ASSERT_EQ(null_list->data, 0);
    ASSERT_EQ(null_list->next, nullptr);
}

TEST_F(Linkedlist, insert_data_to_head) 
{
    struct node * temporary = list;
    int i = 0;

    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&list, i * 10);
    }

    i = 5;
    temporary = list;

    while(temporary != NULL) {
        ASSERT_EQ(temporary->data, i * 10);
        i--;
        temporary = temporary->next;
    }
}

TEST_F(Linkedlist, insert_data_to_head_null_list) 
{
    struct node * null_list = NULL;

    linkedlist_insertBefore(&null_list, 10);

    ASSERT_NE(null_list, nullptr);
    
    ASSERT_EQ(null_list->next, nullptr);
    ASSERT_EQ(null_list->data, 10);
}

TEST_F(Linkedlist, insert_data_to_any_position) 
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    linkedlist_insertAtAnyPosition(&temporary, 70, 4);

    ASSERT_EQ(linkedlist_getSizeofList(&temporary), 7);
    ASSERT_EQ(linkedlist_getDataFromAnyPosition(&temporary, 4), 70);
}

TEST_F(Linkedlist, insert_data_to_any_position_null_list) 
{
    struct node * temporary = NULL;

    int retval = linkedlist_insertAtAnyPosition(&temporary, 70, 4);

    ASSERT_EQ(retval, SUCCESS);
    ASSERT_EQ(temporary->next, nullptr);
    ASSERT_EQ(temporary->data, 70);
}

TEST_F(Linkedlist, insert_data_to_any_position_boundries_check)
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    int retval = linkedlist_insertAtAnyPosition(&temporary, 70, -1);

    ASSERT_EQ(retval, BOUNDRY_FAIL);

    retval = linkedlist_insertAtAnyPosition(&temporary, 70, 10);
    
    ASSERT_EQ(retval, BOUNDRY_FAIL);
}

TEST_F(Linkedlist, insert_data_to_any_position_at_zero)
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    int retval = linkedlist_insertAtAnyPosition(&temporary, 70, 0);

    ASSERT_EQ(retval, SUCCESS);
    ASSERT_EQ(temporary->data, 70);
}

// Get Methods Tests
TEST_F(Linkedlist, get_size_of_list) 
{   
    int retVal = 0;

    retVal = linkedlist_getSizeofList(&list);
    ASSERT_EQ(retVal, 1);

    linkedlist_insertAfter(&list, 10);
    retVal = linkedlist_getSizeofList(&list);
    ASSERT_EQ(retVal, 2);

    linkedlist_insertBefore(&list, 20);
    retVal = linkedlist_getSizeofList(&list);
    ASSERT_EQ(retVal, 3);
}

TEST_F(Linkedlist, get_size_of_null_list) 
{   
    int retVal = 0;
    struct node * null_list = NULL;

    retVal = linkedlist_getSizeofList(&null_list);
    ASSERT_EQ(retVal, NULL_LIST);
}

TEST_F(Linkedlist, get_data_from_any_position) 
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    linkedlist_insertAtAnyPosition(&temporary, 70, 4);
    ASSERT_EQ(linkedlist_getDataFromAnyPosition(&temporary, 4), 70);
}

TEST_F(Linkedlist, get_data_from_any_position_boundries_check) 
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    linkedlist_insertAtAnyPosition(&temporary, 70, 4);

    ASSERT_EQ(linkedlist_getDataFromAnyPosition(&temporary, -1), -1);
    ASSERT_EQ(linkedlist_getDataFromAnyPosition(&temporary, linkedlist_getSizeofList(&temporary) + 1), -1);
}

TEST_F(Linkedlist, get_data_from_any_position_sizeof_list) 
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    linkedlist_insertAtAnyPosition(&temporary, 70, 4);

    ASSERT_EQ(linkedlist_getDataFromAnyPosition(&temporary, linkedlist_getSizeofList(&temporary)), 0);
}

// Remove Item Tests
TEST_F(Linkedlist, remove_from_head) 
{   
    int retVal = 0;
    
    linkedlist_insertAfter(&list, 10);
    linkedlist_insertAfter(&list, 20);
    linkedlist_insertAfter(&list, 30);

    ASSERT_EQ(list->data, 0);
    ASSERT_EQ(linkedlist_getSizeofList(&list), 4);

    retVal = linkedlist_removeFromHead(&list);

    ASSERT_NE(list->data, 0);
    ASSERT_EQ(list->data, 10);
    ASSERT_EQ(linkedlist_getSizeofList(&list), 3);
    ASSERT_EQ(retVal, SUCCESS);
}

TEST_F(Linkedlist, remove_from_head_one_item_list) 
{   
    int retVal = 0;

    ASSERT_EQ(list->data, 0);
    ASSERT_EQ(linkedlist_getSizeofList(&list), 1);

    retVal = linkedlist_removeFromHead(&list);

    ASSERT_EQ(list, nullptr);

    ASSERT_EQ(retVal, SUCCESS);
}

TEST_F(Linkedlist, remove_from_head_null_list) 
{   
    int retVal = 0;
    struct node * null_list = NULL;

    retVal = linkedlist_removeFromHead(&null_list);

    ASSERT_EQ(retVal, NULL_LIST);
}

TEST_F(Linkedlist, remove_from_end_null_list) 
{   
    int retVal = 0;
    struct node * null_list = NULL;

    retVal = linkedlist_removeFromEnd(&null_list);

    ASSERT_EQ(retVal, NULL_LIST);
}

TEST_F(Linkedlist, remove_from_end_one_item_list) 
{   
    int retVal = 0;

    ASSERT_EQ(list->data, 0);
    ASSERT_EQ(linkedlist_getSizeofList(&list), 1);

    retVal = linkedlist_removeFromEnd(&list);

    ASSERT_EQ(list, nullptr);

    ASSERT_EQ(retVal, SUCCESS);
}

TEST_F(Linkedlist, remove_from_end) 
{   
    int retVal = 0;
    
    linkedlist_insertAfter(&list, 10);
    linkedlist_insertAfter(&list, 20);
    linkedlist_insertAfter(&list, 30);

    ASSERT_EQ(linkedlist_getSizeofList(&list), 4);

    retVal = linkedlist_removeFromEnd(&list);

    ASSERT_EQ(linkedlist_getSizeofList(&list), 3);
    ASSERT_EQ(retVal, SUCCESS);
}

TEST_F(Linkedlist, remove_from_any_position) 
{   
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    ASSERT_EQ(linkedlist_getSizeofList(&temporary), 6);
    int retval = linkedlist_removeAtAnyPosition(&temporary, 4);
    ASSERT_EQ(retval, SUCCESS);
    ASSERT_EQ(linkedlist_getSizeofList(&temporary), 5);
    ASSERT_NE(linkedlist_getDataFromAnyPosition(&temporary, 4), 10);
}

TEST_F(Linkedlist, remove_from_any_position_null_list) 
{   
    struct node * temporary = NULL;
    
    int retval = linkedlist_removeAtAnyPosition(&temporary, 4);
    ASSERT_EQ(retval, NULL_LIST);
}
 
TEST_F(Linkedlist, remove_from_any_position_boundries_check)
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    int retval = linkedlist_removeAtAnyPosition(&temporary, -1);

    ASSERT_EQ(retval, BOUNDRY_FAIL);

    retval = linkedlist_removeAtAnyPosition(&temporary, 10);
    
    ASSERT_EQ(retval, BOUNDRY_FAIL);
}

TEST_F(Linkedlist, remove_from_any_position_at_zero)
{
    struct node * temporary = list;
    int i = 0;

    // 50 40 30 20 10 0
    for (i = 1; i <= 5; i++) {
        linkedlist_insertBefore(&temporary, i * 10);
    }

    int retval = linkedlist_removeAtAnyPosition(&temporary, 0);

    ASSERT_EQ(retval, SUCCESS);
    ASSERT_EQ(temporary->data, 40);
}

// Printing Test
TEST_F(Linkedlist, DISABLED_print_list) 
{   
    linkedlist_printList(&list);
    printf("---------------\n");

    linkedlist_insertAfter(&list, 10);
    linkedlist_insertAfter(&list, 20);
    linkedlist_insertAfter(&list, 30);

    linkedlist_printList(&list);
}