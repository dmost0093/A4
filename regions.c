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
    r_size_t sizeOfBlock;//size of the block been allocated
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
//function that return the name of the currently-chosen region
const char *rchosen()
{
    return currNode->data.name;
}
/*Function to choose a previously-initialized memory region 
for other functions. Return false on error.*/
Boolean rchoose(const char *region_name)
{
    Boolean result = false;
    struct Node *curr = head;
    if(head == NULL)
    {//case the list of the region is empty
        return result;
    }
    //navigate through list
    while(curr->data.name != region_name)
    {
        //if it is last element(node) in list of regions
        if(curr->next == NULL)
        {
            return result;
        }
        else
        {//go to next next element(node)
            curr = curr->next;
        }
    }
    //if data found, update the currently chosen region
    currNode = curr;
    result = true;
    return result;

}
//Allocate a block that is the given number of bytes.
void *ralloc(r_size_t block_size)
{
    void *result_ptr;
    struct Node *curr = currNode;
    if(block_size <= 0 || curr->data.size < curr->data.occupied + block_size)
    {//case the given size of the block is 0
    //case that occupied memory size reach or will over the maximum size of memory
        return NULL;
    }
    else
    {
        if(curr->data.occupied == 0)
        {
            curr->data.memory->sizeOfBlock = block_size;
            curr->data.occupied += block_size;
        }
        else
        {
            struct Node_m *newBlock = (struct Node_m*) malloc(sizeOf(struct Node_m));
            newBlock->sizeOfBlock = block_size;
            newBlock->next = NULL;
            curr->data.memory->next = newBlock;
            curr->data.occupied += block_size;
            result_ptr = newBlock;
        }
        
    }
    return result_ptr;
}
