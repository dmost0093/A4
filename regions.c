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

int main( int argc, char *argv[] )
{
  return EXIT_SUCCESS;
}