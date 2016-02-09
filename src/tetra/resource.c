
#include "tinternal.h"

struct tresource * new_resource (void * function_id,
							         void * resource,
                                     CLEANUPFUNCTION cleanup_func) 
{
 struct tresource * resource = (struct tresource*) 
  malloc (sizeof(struct tresource)) ;

 if (!resource)
  return 0 ;

 resource->function_id = function_id ;
 resource->resource = resource;
 resource->cleanup_func = cleanup_func;
 resource->ref = 0 ;

 return resource ;
}

#define new_resource_ref(resource) (resource)->ref++

void del_resource_ref (struct tresource * resource)
{
 resource->ref-- ;
 if (!resource->ref)
  free_resource (resource) ;
}

void free_resource (struct tresource * resource)
{
 if (resource->cleanup_func)
  resource->cleanup_func(resource->resource) ;
 free(resource) ;
}