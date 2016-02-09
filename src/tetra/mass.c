
#include "tinternal.h"

// b* functions by me, k?

void * bnew (byte item_size, byte item_incr)
{
 struct bulkmem * bmem = (struct bulkmem *)
  malloc(sizeof(struct bulkmem)) ; 
 bmem->item_size = item_size ;
 bmem->item_incr = item_incr ;
 bmem->amount_used = 0 ;
 bmem->max_avail = 0 ;
 return to_ptr(bmem) ;
}

void * bpalloc (void ** ptr, dword count)
{
 struct bulkmem * bmem = to_bmem(*ptr) ;
 dword index = bmem->amount_used ;

 bmem->max_avail  += (count / bmem->item_incr + 1) * bmem->item_incr ;
 
 bmem = (struct bulkmem *) realloc(bmem, 
  bmem->max_avail * bmem->item_size + sizeof(struct bulkmem)) ;

 *ptr = to_ptr(bmem) ;

 return element(*ptr,bmem,index) ;
}

void * balloc (void ** ptr)
{
 struct bulkmem * bmem = to_bmem(*ptr) ;
 dword index = bmem->amount_used++ ;

 if (bmem->amount_used > bmem->max_avail)
 {
  bmem->max_avail += bmem->item_incr ;

  bmem = (struct bulkmem *) realloc(bmem, 
   bmem->max_avail * bmem->item_size + sizeof(struct bulkmem)) ;
 }

 *ptr = to_ptr(bmem) ;

 return element(*ptr,bmem,index) ;
}

void * bfree (void ** ptr)
{
 struct bulkmem * bmem = to_bmem(*ptr) ;
 dword index = --bmem->amount_used - 1;

 if (bmem->max_avail-bmem->amount_used >= bmem->item_incr)
 {
  bmem->max_avail -= bmem->item_incr ;
  bmem = (struct bulkmem *) realloc(bmem, 
   bmem->max_avail * bmem->item_size + sizeof(struct bulkmem)) ;
 }

 *ptr = to_ptr(bmem) ;

 return element(*ptr,bmem,index) ;
}

void bdelete (void * ptr)
{
 free(to_bmem(ptr)) ;
}