/**
 * Select definitions
 */

/* undname.c doesn't do it */
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

/* winnt.h */
typedef char            CHAR,       *PCHAR;

/* windef.h */
typedef int             BOOL,       *PBOOL,    *LPBOOL;
#define FALSE 0
#define TRUE  1

#define CDECL       __cdecl

/* msvcrt.h */
/* typedef unsigned long MSVCRT_size_t; */
/* malloc's type is (void *malloc)(size_t), not this nonsense */
typedef size_t MSVCRT_size_t;

typedef void* (__cdecl *malloc_func_t)(MSVCRT_size_t);
typedef void  (__cdecl *free_func_t)(void*);

/* __unDName/__unDNameEx flags */
#define UNDNAME_COMPLETE                 (0x0000)
#define UNDNAME_NO_LEADING_UNDERSCORES   (0x0001) /* Don't show __ in calling convention */
#define UNDNAME_NO_MS_KEYWORDS           (0x0002) /* Don't show calling convention at all */
#define UNDNAME_NO_FUNCTION_RETURNS      (0x0004) /* Don't show function/method return value */
#define UNDNAME_NO_ALLOCATION_MODEL      (0x0008)
#define UNDNAME_NO_ALLOCATION_LANGUAGE   (0x0010)
#define UNDNAME_NO_MS_THISTYPE           (0x0020)
#define UNDNAME_NO_CV_THISTYPE           (0x0040)
#define UNDNAME_NO_THISTYPE              (0x0060)
#define UNDNAME_NO_ACCESS_SPECIFIERS     (0x0080) /* Don't show access specifier (public/protected/private) */
#define UNDNAME_NO_THROW_SIGNATURES      (0x0100)
#define UNDNAME_NO_MEMBER_TYPE           (0x0200) /* Don't show static/virtual specifier */
#define UNDNAME_NO_RETURN_UDT_MODEL      (0x0400)
#define UNDNAME_32_BIT_DECODE            (0x0800)
#define UNDNAME_NAME_ONLY                (0x1000) /* Only report the variable/method name */
#define UNDNAME_NO_ARGUMENTS             (0x2000) /* Don't show method arguments */
#define UNDNAME_NO_SPECIAL_SYMS          (0x4000)
#define UNDNAME_NO_COMPLEX_TYPE          (0x8000)

/* Don't look below. */
static char* lstrcpynA(char* dst, const char* src, int n) {
    return strncpy(dst, src, n);
}

struct parsed_symbol;

void* und_alloc(struct parsed_symbol*, unsigned int);

void und_free_all(struct parsed_symbol* sym);
    
