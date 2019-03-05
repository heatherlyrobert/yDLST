/*============================----beg-of-source---============================*/

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YDLST_priv_hguard
#define YDLST_priv_hguard loaded



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "ds (data structures)"
#define     P_PURPOSE   "clean, resiliant, reusable quad/doubly linked list w/deps"

#define     P_NAMESAKE  "kratos-daimon (strength)"
#define     P_HERITAGE  "kratos personified strength and sibling to force, zeal, and victory"
#define     P_IMAGERY   "angel-like winged being wearing a battle helm and sheild"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2011-05"
#define     P_DEPENDS   "none"

#define     P_VERNUM    "0.3f"
#define     P_VERTXT    "updated due to changes iny yLOG"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/



/*===[[ PUBLIC HEADERS ]]=====================================================*/
#define   _GNU_SOURCE           /* to allow asprintf()                        */
/*---(big standards)------------*/
#include  <stdio.h>             /* printf, scanf                              */
#include  <stdlib.h>            /* exit()                                     */
#include  <string.h>            /* strcat, strcpy, strlen, ...                */
#include  <malloc.h>            /* malloc(), free()                           */

#include  <yURG.h>
#include  <ySTR.h>
#include  <yLOG.h>



typedef struct cDLST_LIST  tDLST_LIST;
typedef struct cDLST_LINE  tDLST_LINE;
typedef struct cDLST_SEQ   tDLST_SEQ;


typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;




#define   PRIV           static


extern char      unit_answer [LEN_RECD];



#define   YDLST_LINKED    'y'
#define   YDLST_FLOATER   '-'


struct  cDLST_LIST {
   /*---(master)---------------*/
   char       *title;               /* name of list                             */
   void       *data;                /* pointer to data payload                  */
   /*---(lists)----------------*/
   tDLST_LIST *prev;
   tDLST_LIST *next;
   /*---(lines)----------------*/
   tDLST_LINE *head;                /* head of lists links                      */
   tDLST_LINE *tail;                /* tail of lists links                      */
   int         count;               /* number of lists links                    */
   /*---(sequencing)-----------*/
   tDLST_SEQ  *p_head;
   tDLST_SEQ  *p_tail;
   int         p_count;
   tDLST_SEQ  *s_head;
   tDLST_SEQ  *s_tail;
   int         s_count;
   /*---(done)-----------------*/
};

struct  cDLST_LINE {
   /*---(ref name)-------------*/
   char       *title;               /* name of list                             */
   void       *data;                /* pointer to data payload                  */
   /*---(lines)----------------*/
   tDLST_LIST *prev;
   tDLST_LIST *next;
   /*---(lists)----------------*/
   tDLST_LIST *parent;              /* pointer to the owning list               */
   tDLST_LINE *p_next;              /* forward  link in lists links             */
   tDLST_LINE *p_prev;              /* backward link in lists links             */
   /*---(focus)----------------*/
   char        focus;               /* flag to indicate focused 'y' or not '-'  */
   tDLST_LINE *f_prev;              /* backward link in list of focus links     */
   tDLST_LINE *f_next;              /* forward  link in list of focus links     */
   /*---(active)---------------*/
   char        active;              /* flag to indicate active  'y' or not '-'  */
   tDLST_LINE *a_prev;              /* backward link in list of active links    */
   tDLST_LINE *a_next;              /* forward  link in list of active links    */
   /*---(done)-----------------*/
};


struct   cDLST_SEQ {
   /*---(seq)------------------*/
   tDLST_SEQ  *prev;
   tDLST_SEQ  *next;
   /*---(predecessor)----------*/
   tDLST_LIST *pred;
   tDLST_SEQ  *p_prev;
   tDLST_SEQ  *p_next;
   /*---(successor)------------*/
   tDLST_LIST *succ;
   tDLST_SEQ  *s_prev;
   tDLST_SEQ  *s_next;
   /*---(done)-----------------*/
};




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
tDLST_LIST *ydlst_list_new          (char a_link);
char        ydlst_list_del          (tDLST_LIST *a_old, char a_link);
tDLST_LIST *ydlst_list_getcurr      (void);
char*       ydlst_list__unit        (char *a_question, int a_num);

tDLST_LINE *ydlst_line_getcurr      (void);
char        ydlst_line_setcurr      (tDLST_LINE *a_curr);
char        ydlst_line__purgelist   (tDLST_LIST *a_list);
char*       ydlst_line__unit        (char *a_question, int a_num);

char        ydlst__test_quiet    (void);
char        ydlst__test_loud     (void);
char        ydlst__test_end      (void);

char*       ydlst_focus__unit       (char *a_question, int a_num);
char*       ydlst_active__unit      (char *a_question, int a_num);

char        yDLST_seq_before        (char *a_after);
char*       ydlst_seq__unit         (char *a_question, int a_num);

char        ydlst_seq_init          (void);
char        ydlst_seq_wrap          (void);



#endif
/*============================----end-of-source---============================*/
