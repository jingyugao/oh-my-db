
#include<sys/types.h>
#include<unistd.h>
struct block{
    size_t size;
    block *next;
    int free;
    int padding;
    char data[1];
};
#define BLOCK_SIZE 24
block *first_block=0;

block* find_block(block **last,size_t size){
    
    block *b=first_block;
    while(b&&!(b->free&&b->size>=size)){
        *last=b;
        b=b->next;
    }
    return b;
}
block* extend_heap(block *last,size_t s){
    block* b;
    b=sbrk(0);
    if(sbrk(BLOCK_SIZE+s)==(void*)-1)
        return NULL;// failed to alloc page 
    b->size=s;
    b->next=NULL;
    if(last)
        last->next=b;
    b->free=0;
    return b;
}

int main(int argc,char *argv[])
{
    return 0;
}


