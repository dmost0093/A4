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
#include <string.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
typedef enum BOOL{false, true} Boolean;
typedef unsigned short r_size_t;
typedef struct REGION Region;
struct REGION
{
    const char *name;//name of the memory region
    r_size_t size;//maximum memory that can be store
    r_size_t occupied;//total memory that been occupied
    struct Node_m *memory;//momory of the region store(head of list)
};
struct Node 
{
   Region data;//data that stored in the node
   struct Node *next;
};
struct Node_m
{//link list for the memory block 
    struct Node_m *next;
    r_size_t memory;
};
//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static struct Node *currNode = NULL;//currently chosen region
static struct Node *head = NULL;//head of the region list
static int numOfr = 0;//number of the region created
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
    Boolean result = false; //return value
    //check the name of the region is already used or not    
    if (head == NULL)
    { //case 0 number of region.
        result = true;
        //create new region
        Region newRegion;
        newRegion.name = region_name;
        newRegion.size = region_size;
        newRegion.occupied = 0;
        struct Node_m *newMemory = (struct Node_m*) malloc(sizeof(struct Node_m));
        newMemory->memory = 0;
        newMemory->next = NULL;
        newRegion.memory = newMemory;
        //create new node
        struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->data = newRegion;
        newNode->next = head;
        head = newNode;
        currNode = newNode;
        numOfr++;
        return result;
    }
    else
    {//case there are more than 0 number of region
        struct Node *curr = head;
        Region check = curr->data; //data store in the current node
        while (curr->next != NULL)
        {//check the name of region is unique
            if (check.name == region_name)
            { //case the region name used already.
                printf("The region name (%s) has been already used\n", region_name);
                return result; //return false
            }
            //update the current node and data stored in node
            curr = curr->next;
            check = curr->data;
        }
        
        //create new region
        Region newRegion;
        newRegion.name = region_name;
        newRegion.size = region_size;
        newRegion.occupied = 0;
        struct Node_m *newMemory = (struct Node_m*) malloc(sizeof(struct Node_m));
        newMemory->memory = 0;
        newMemory->next = NULL;
        newRegion.memory = newMemory;
        //create new node
        struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->data = newRegion;
        newNode->next = head;
        head = newNode;
        currNode = newNode;
        numOfr++;
        result = true;
        return result;
    }
}

