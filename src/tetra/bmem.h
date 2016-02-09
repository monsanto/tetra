

#define to_ptr(x) (void*) \
 (((byte*)(x)) + sizeof(struct bulkmem))

#define to_bmem(x) (struct bulkmem*) \
 (((byte*)(x)) - sizeof(struct bulkmem))

#define element(x,y,i) (void*) \
 (((byte*)(x)) + (i) * (y)->item_size)

#define bget(ptr,index) \
 (element(ptr,to_bmem(ptr),index))

#define bgetlast(ptr) \
 (element(ptr,to_bmem(ptr),bcount(ptr)))

#define bcount(ptr) \
 ((to_bmem(ptr))->amount_used)

void * bnew (byte item_size, byte item_incr) ;
void * bpalloc (void ** ptr, dword count) ;
void * balloc (void ** ptr) ;
void * bfree (void ** ptr) ;
void bdelete (void * ptr) ;