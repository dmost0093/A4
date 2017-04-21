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
    void *result_ptr = (struct Node_m*) malloc(sizeof(struct Node_m));
    struct Node *curr = currNode;
    assert(curr != NULL);
    if(block_size <= 0 || curr->data.size < curr->data.occupied + block_size)
    {//case the given size of the block is 0
    //case that occupied memory size reach or will over the maximum size of memory
        return NULL;
    }
    else
    {
        if(curr->data.occupied == 0)
        {
            curr->data.block->sizeOfBlock = block_size;
            curr->data.occupied += block_size;
        }
        else
        {
            struct Node_m *newBlock = (struct Node_m*) malloc(sizeof(struct Node_m));
            newBlock->sizeOfBlock = block_size;
            newBlock->next = NULL;
            curr->data.block->next = newBlock;
            curr->data.occupied += block_size;
            result_ptr = newBlock;
        }
        
    }
    return result_ptr;
}
//Find out how many of memory been allocated inside a block
r_size_t rsize(void *block_ptr)
{
    struct Node_m *pointer = (struct Node_m*)block_ptr;
    printf("Occupied(stored in block): %d\n", pointer->sizeOfBlock);
    r_size_t result = pointer->sizeOfBlock;
    return result;
}
//Destroy the region with the given name, freeing all memory associated with it. 
void rdestroy(const char *region_name)
{
    if(head == NULL)
    {//case there is 0 regions.
        return ;
    }
    struct Node *temp = head;//the node from list that store data for region
    struct Node_m *blockD;//block that will be destroyed
    Region regionD; //region that will be destroyed
    if(head->data.name == region_name||currNode->data.name == region_name)
    {//case destroying head or currently selected region
        //change the head to next node.
        if(head->data.name == region_name)
        {
            temp = head;
            regionD = temp->data;
            head = head->next;
        }
        //change the currNode(currently selected region) to head.
        if(currNode->data.name == region_name)
        {
            temp = currNode;
            regionD = temp->data;
            currNode = head;
        }
        
        //destroy the all the block in the region
        while(regionD.block->next != NULL)
        {
            blockD = regionD.block;
            regionD.block = regionD.block->next;
            free(blockD);
        }
        free(temp);
    }
    else
    {
        //find the region that given by the region name
        while(temp->data.name != region_name)
        {
            //if it is last node
            if(temp->next == NULL)
            {
                printf("Enter wrong region name or regions is not appear in the list");
                return ;
            }
            else
            {
                temp = temp->next;
            }
        }
        //update the region and block need to be destroy
        regionD = temp->data;
        blockD = regionD.block;
        //destroy the block in region
        while(regionD.block->next != NULL)
        {
            blockD = regionD.block;
            regionD.block = regionD.block->next;
            free(blockD);
        }
        free(temp);
    }
    return ;
}
void rdump(void)
{
    if(head == NULL)
    {//case there is no region to print
        printf("There is no region to print");
        return ;
    }
    struct Node *curr = head;
    int freeSpace = curr->data.size - curr->data.occupied;
    int freeSpaceP = (freeSpace / curr->data.size) * 100;
    while(curr != NULL)
    {
        //print basic information
        printf("Name of Region: %s, Maximum Size of Region: %d, Memory been occuppied: %d", curr->data.name, curr->data.size, curr->data.occupied);
        printf("Free space: %d(%d%%)",freeSpace, freeSpaceP);
        curr = curr->next;
    }
    
}
