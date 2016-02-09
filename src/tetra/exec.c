
#include "tinternal.h"

// extremely useful :p
#define val(type) *((type*)binary) ; binary += sizeof(type)

byte _tetra_exec (TPROGRAM * program, byte * binary, TARG * retval)
{
 byte * start = binary ;

 while (1)
 {
  switch (*program->chunk_ptr++)
  {
  case TPUSH1:
   {
	char val = val(char) ;
	IF_NOT_POP {
	 TARG * arg = ta_new (program) ;
	 arg->type = TYPE_NUMBER ;
	 arg->number = val ;
	 push (program, arg) ;
	} ELSE_SKIP_POP ; ;
	break ;
   }
  case TPUSH2:
   {
	short val = val(short) ;
	IF_NOT_POP {
	 TARG * arg = ta_new (program) ;
	 arg->type = TYPE_NUMBER ;
	 arg->number = val;
	 push (program, arg) ;
	} ELSE_SKIP_POP ;
	 break ;
   }
  case TPUSH4:
   {
	long val = val(long) ;
	IF_NOT_POP {
	 TARG * arg = ta_new (program) ;
	 FAST_set_number(TYPE_NUMBER, val) ;
	 push (program, arg) ;
	} ELSE_SKIP_POP ;
	 break ;
   }
  case TPUSHSTR:
   {
	char * TSTRING * ;
	word index = val(word) ;
	IF_NOT_POP {
	 TARG * arg = ta_new (program) ;
	 TSTRING * = find_string_from_index (program, TSTRING *) ; // error check, ok
	 FAST_set_sv (arg, TSTRING *) ;
	 push (program, arg) ;
	} ELSE_SKIP_POP ; ;  ;
	break; 
   }
  case TPUSHREAL:
   {
	double val = val(double) ;
	IF_NOT_POP {
	 TARG * arg = ta_new (program) ;
	 FAST_set_real(arg,val) ;
	 push (program, arg) ;
	} ELSE_SKIP_POP ;
	break ;
   }
  case TPUSHSYM:
   {
	TARG * var_name = pop(program);
	IF_NOT_POP {
	 TARG * arg = get_variable (program, to_string(var_name,0,0)) ;
	 push (program, arg) ;
	} ELSE_SKIP_POP ;
	 del_arg_ref(program,var_name) ;
	break ;
   }
  case TSET:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;
	TARG * result ;
	IF_NOT_POP {
	 result = ta_new (program) ;
	}
	copy_arg (arg1,arg2) ;
	IF_NOT_POP {
	 FAST_copy_arg (result,arg1) ;
	}
	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;
	IF_NOT_POP {
	 push(program,result) ;
	} ELSE_SKIP_POP ;
	 break ;
   }
  case TADD:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_add_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TSUB:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_sub_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TMUL:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_mul_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TDIV:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_div_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TPOW:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_pow_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TMOD:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_mod_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TCAT:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_cat_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TEQ:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_eq_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TNQ:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_nq_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TLT:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_lt_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TGT:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_gt_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TLTEQ:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_lteq_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TGTEQ:
   {
	TARG * arg2 = pop (program) ;
	TARG * arg1 = pop (program) ;

	IF_NOT_POP {
	 TARG * result = ta_new (program) ;
	 FAST_gteq_args (arg1,arg2,result) ;
	 push(program, result) ;
	} ELSE_SKIP_POP ;

	del_arg_ref(program,arg1) ;
	del_arg_ref(program,arg2) ;

	break ;
   }
  case TIF:
   {
	TARG * arg = pop (program) ;
	byte result = to_bool(arg) ;
	dword skip_to = val(dword) ;
	if (!result)
	 binary = start+skip_to ;
	del_arg_ref(program,arg) ;
	break ;
   }
  case TCALL:
   {
	TARG * func_ret = 0, args = 0, sym = pop (program) ; 
	struct tfunction * fd = to_function (sym) ;
	byte i, ret, arg_count = val(byte) ;

	if (!fd)
	{
	 // yeah, if this function doesn't exist we blast all the tstack
	 // args quickly without a malloc.
	 pop_multiple(program,arg_count,0) ;
	 throw_exception(program,"FunctionError","Function not found.", TE_ERROR) ;
	 return ; // some value 
	}

	if (arg_count)
	{
	 args = (TARG**) malloc(arg_count*sizeof(TARG*)) ;
	 pop_multiple(program,arg_count,args) ;
	}

	IF_NOT_POP {
	 ret = ta_new (program) ; // dont know if anyone is gonna return or not.
	}

	ret = call_function (program, fd, arg_count, args, ret) ;

	if (arg_count)
	{
	 for (i = 0; i < arg_count; i++)
	  del_arg_ref(program,args[i]) ;

	 free(args) ;
	}

	del_arg_ref(program, sym) ;

	IF_NOT_POP {
	 push(program,ret) ;
	} ELSE_SKIP_POP ;

	break ;
   }
  case TGOTO:
   {
	dword new_pos = val(dword) ;
	binary = start + new_pos ;
	break ;
   }
  case TRETURN:
   {
	TARG * arg = pop(program) ;
	if (retval)
	 copy_arg (retval,arg) ;
	del_arg_ref(program,arg) ;
	return TE_RETURN ;
   } 
  }
 }
}