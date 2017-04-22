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
#include <assert.h>
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
    struct Node_m *block;//block of the memory store(head of blocks)
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
    if(region_size <= 0)
    {//case the regions_size is less than or equal to 0
        return result;
    }   
        if(region_size % 8 != 0)
        {//check the size of the region is multiple of 8
        region_size = region_size + (8 - region_size % 8);//round the size if region size is not a multiple of 8
        
        }  
    if (head == NULL)
    { //case 0 number of region.
        result = true;
        //create new region
        Region newRegion;
        newRegion.name = region_name;
        newRegion.size = region_size;
        newRegion.occupied = 0;
        struct Node_m *newBlock = (struct Node_m*) malloc(sizeof(struct Node_m));
        newBlock->sizeOfBlock = 0;
        newBlock->next = NULL;
        newRegion.block = newBlock;
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
        struct Node_m *newBlock = (struct Node_m*) malloc(sizeof(struct Node_m));
        newBlock->sizeOfBlock = 0;
        newBlock->next = NULL;
        newRegion.block = newBlock;
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
    if(block_size % 8 != 0)
    {//check the size of the region is multiple of 8
        block_size = block_size + (8 - block_size % 8);//round the size if region size is not a multiple of 8
    }  
    void *result_ptr = (struct Node_m*) malloc(sizeof(struct Node_m));
    struct Node *curr = currNode;    
    r_size_t max, occupiedSize;
    max = curr->data.size;
    occupiedSize = curr->data.occupied + block_size;
    if(block_size <= 0 || max < occupiedSize)
    {//case the given size of the block is 0
    //case that occupied memory size reach or will over the maximum size of memory
        return NULL;
    }
    else
    {
        if(curr->data.occupied == 0)
        {//case the head(block) is empty
            curr->data.block->sizeOfBlock = block_size;
            curr->data.occupied = block_size;
            result_ptr = curr->data.block;
        }
        else
        {   
            //create new block
            struct Node_m *newBlock = (struct Node_m*) malloc(sizeof(struct Node_m));  
                 
            newBlock->sizeOfBlock = block_size;
            newBlock->next = curr->data.block;
            curr->data.block = newBlock;
            //search for last block in the list
            curr->data.occupied = occupiedSize;
            result_ptr = newBlock;
        }
        
    }
    return result_ptr;  
}
//Find out how many of memory been allocated inside a block
r_size_t rsize(void *block_ptr)
{
    struct Node_m *pointer = block_ptr;
    if(pointer == NULL)
    {
        return 0;
    }
    r_size_t result = pointer->sizeOfBlock;
    return result;
}
//Frees the block identified by the given pointer in the currently chosen region
Boolean rfree(void *block_ptr)
{
    Boolean result;
    result = false;
    
    if(block_ptr == NULL||head == NULL)
    {//case the given pointer is NULL or the list of block is empty
        
        return result;
    }
    struct Node_m* temp = (struct Node_m*)block_ptr;
    struct Node_m* curr = currNode->data.block;//point the head of the block list
    struct Node_m* prev = NULL;//point the previous block
    while(temp != curr)
    {
        if(curr->next == NULL)
        {//case the last block
            return result;
        }
        else
        {
            //save the reference to current block
            prev = curr;
            //move to next block
            curr = curr->next;
        }
    }
    //found the match
    //update the block
    if(currNode->data.block == temp)
    {//case first block
        //update the data in region
        currNode->data.occupied = (currNode->data.occupied)-(temp->sizeOfBlock);
        //update the link
        currNode->data.block = currNode->data.block->next;
        result = true;
    }
    else
    {
        //update the data in region
        currNode->data.occupied = (currNode->data.occupied)-(temp->sizeOfBlock);
        //update the link
        prev->next = curr->next;
        result = true;
    }
    free(block_ptr);
    return result;
}
//Destroy the region with the given name, freeing all memory associated with it. 
void rdestroy(const char *region_name)
{
    Boolean stop = true;
    if(head == NULL)
    {//case there is 0 regions.
        stop = false;
    }
    struct Node* curr = head;
    struct Node* prev;
    
    while(curr->data.name != region_name||stop)
    {
        if(curr->next == NULL)
        {
           
            stop = false;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
    //found the region
    if(curr->data.name == region_name)
    {
        //case last region
        if(head->next == NULL)
        {
            curr = head;
            head = NULL;
            currNode = NULL;
        }
        //case first region
        if(curr == head && head->next != NULL)
        {
            if(curr == currNode)
            {//case currently selected region are same as first region in the list
                currNode = head->next;
                head = head->next;
            }
            else
            {
                head = head->next;
            }
        }
        else
        {
            currNode = prev;
            currNode->next = curr->next;
        }
        free(curr);
    }
}
//Print all data structures, but not block contents.
void rdump(void)
{
    
    if(head == NULL || currNode == NULL)
    {//case there is no region to print
        printf("There is no region to print\n");
        return ;
    }
    struct Node *curr = head;
    struct Node_m *block;
    int freeSpace;
    int count = 1;
    while(curr != NULL)
    {
        //print basic information
        block = curr->data.block;
       freeSpace = curr->data.size - curr->data.occupied;
       printf("Name of Region: %s\nMaximum Size of Region: %d\nMemory been occuppied: %d\n", curr->data.name, curr->data.size, curr->data.occupied);
       printf("Free space: %d\n",freeSpace);
       while(block != NULL)
       {
           printf("Block #%d:\n",count);
           printf("Address: %p\n",curr->data.block);
           printf("Size of block: %d\n",curr->data.block->sizeOfBlock);
           count++;
           block = block->next;
       }
       count = 1;
       curr = curr->next;
       
    }
    return ;
}
