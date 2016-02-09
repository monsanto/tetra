
struct tresource * new_resource (void * function_id,
							         void * resource,
                                     CLEANUPFUNCTION cleanup_func) ;

#define new_resource_ref(resource) (resource)->ref++

void del_resource_ref (struct tresource * resource) ;

void free_resource (struct tresource * resource) ;
