
#define to_str(x) (char *) \
 (((byte*)(x)) + sizeof(struct stringvalue))

#define to_sv(x) (struct stringvalue *) \
 (((byte*)(x)) - sizeof(struct stringvalue))


#define FAST_string_length(sv) (sv)->length
dword string_length (TSTRING * string) ;

TSTRING * find_string (TPROGRAM * program, char * string) ;

#define FSE_ZERO_RESULTS 1
#define FSE_CREATE 2

byte find_multiple_strings (TPROGRAM * program,
					 char ** strings,
					 dword * lengths,
					 TSTRING * * results,
					 dword item_count,
					 dword flags) ;

TSTRING * find_string_from_index (TPROGRAM * program,
							   dword index) ;

TSTRING * create_string (dword length) ;

TSTRING * new_string (char * string, dword length) ;

byte add_string (TPROGRAM * program, TSTRING * string) ;

TSTRING * reserve_string (TPROGRAM * program, dword length) ;

#define FAST_free_string(sv) free (sv)
void free_string (TSTRING * TSTRING *) ;

#define FAST_new_string_ref(sv) (sv)->ref++

void new_string_ref (TSTRING * TSTRING *) ;

#define FAST_del_string_ref(sv) \
 (sv)->ref-- ; \
 if (!sv->ref) \
  FAST_free_string(sv)

void del_string_ref (TSTRING * TSTRING *) ;
