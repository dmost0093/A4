//-----------------------------------------
// NAME: Sangil Han 
// STUDENT NUMBER: 7722421
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: question 1
// 
// REMARKS: The program to implement memory regions.
//
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
typedef enum BOOL{false, true} Boolean;
typedef unsigned short r_size_t;
typedef struct NODE node;
typedef struct REGION Region;
struct NODE
{
    Region data;//data that stored in the node
    struct Node * next;//next Node
}
struct REGION
{
    const char *name;//name of the memory region
    r_size_t size;//maximum memory that can be store
    r_size_t occupied;//total memory that been occupied
    char **memory;//momory of the region store
}
//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static struct Node *curr = NULL;//currently chosen region
static struct Node *head = NULL;//head of the region list
//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
Boolean rinit(const char *region_name, r_size_t region_size);
Boolean rchoose(const char *region_name);
const char *rchosen();
void *ralloc(r_size_t block_size);
r_size_t rsize(void *block_ptr);
Boolean rfree(void *block_ptr);
void rdestroy(const char *region_name);
void rdump(void);
//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

//Create and initialize a region with the given name and the given size
Boolean rinit(const char * region_name, r_size_t region_size)
{
    Boolean result;//return value
    //check the name of the region is already used or not
    struct Node *curr = head;
    Region *check = &curr->data;//datat store in the current node
    if(curr == NULL)
    {//list is empty
        result = true;
    }
    else
    {
        while(curr->next != NULL)
        {
            if(check->name == region_name)
            {//case the region name used already.
                printf("The region name %s is already used", region_name);
                result = false;
                return result;//return false
            }
            //update the current node and data stored in node
            curr = curr->next;
            check = &curr->data;
        }
    }
    //create new region
    Region newRegion;
    newRegion.name = region_name;
    newRegion.size = region_size;
    newRegion.occupied = 0;

    //create new node
    struct Node *newNode = (struct Node) malloc(sizeof(struct Node));
    newNode.data = newRegion;
    newNode.next = head;
    head = newNode;
    result = true;
    return result;
}
