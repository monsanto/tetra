%{
 #include "tc.h"
 #include "yygrammar.h"
 #pragma warning(disable:4267)
 
 char string_buf[255];
 char *string_buf_ptr;
%}

%x comment
%x string
%x lcomment

DIGIT    [0-9]
ID       [_a-zA-Z][_a-zA-Z0-9]*

%%

"/*"         BEGIN(comment);
"//"         BEGIN(lcomment);
"#"         BEGIN(lcomment);
\"  { string_buf_ptr = string_buf; BEGIN(string); }


{DIGIT}+    {
                yylval.number = atoi(yytext) ;
                return NUMBER ;
            }
            
{DIGIT}+"."{DIGIT}*        {
                yylval.real = atof( yytext ) ;
                return REAL ;
                }
                
"register" return REGISTER;
"infinity" return INFINITY ;
"function" return FUNCTION ;
"string" return CAST_STRING ;
"number" return CAST_NUMBER ;
"real" return CAST_REAL ;
"if" return IF ;
"else" return ELSE ;
"return" return RETURN ;
"for" return FOR ;
"while" return WHILE ;
"break" return BREAK ;
"switch" return SWITCH ;
"case" return CASE ;
"continue" return CONTINUE ;
"with" return WITH ;
"until" return UNTIL ;
"default" return DEFAULT ;
"new" return NEW ;
"member" return MEMBER ;

"+" return '+' ;
"-" return '-' ;
"*" return '*' ;
"/" return '/' ;
"%" return '%' ;
"<" return '<' ;
">" return '>' ;
"=" return '=' ;
"[" return '[' ;
"]" return ']' ;
"." return '.' ;
"(" return '(' ;
")" return ')' ;
"!" return '!' ;
"^" return '^' ;
"&" return '&' ;
"|" return '|' ;
"{" return '{' ;
"}" return '}' ;
"," return ',' ;
"?" return '?' ;
":" return ':' ;
";" return ';' ;
"$" return '$' ;
                
{ID}        {
       yylval.index = sp_add(yytext, (dword)yyleng);
       return ID ;
}
                
[ \t\r]+

\n     { yypos++; /* adjust linenumber and skip newline */ }
.      { yyerror("illegal token"); }

<comment>{
    [^*\n]*        
    "*"+[^*/\n]*   
    \n             yypos++;
    "*"+"/"        BEGIN(INITIAL);
}

<string>{
    \"  { 
            BEGIN(INITIAL);
            *string_buf_ptr = '\0';
         
            yylval.index = sp_add(string_buf,(dword)(string_buf_ptr-string_buf)) ;
            return STRING ;
         }

    \n        {
             yyerror("Newline in string...");
             return 0;
            }

    \\[0-7]{1,3} {
            

            sscanf( yytext + 1, "%o", &yylval.number );

            if ( yylval.number > 0xff )
             yyerror("Octal escape is out of bounds.");
            
            *string_buf_ptr++ = (char)yylval.number;
            }

    \\[0-9]+ {
            yyerror("Invalid octal escape.");
            }

    \\n  *string_buf_ptr++ = '\n';
    \\t  *string_buf_ptr++ = '\t';
    \\r  *string_buf_ptr++ = '\r';
    \\b  *string_buf_ptr++ = '\b';
    \\f  *string_buf_ptr++ = '\f';

    \\(.|\n)  *string_buf_ptr++ = yytext[1];

    [^\\\n\"]+        {
            char *yptr = yytext;

            while ( *yptr )
                    *string_buf_ptr++ = *yptr++;
            }
}

<lcomment>{
 [^\n]+ 
 \n BEGIN(INITIAL) ;
}