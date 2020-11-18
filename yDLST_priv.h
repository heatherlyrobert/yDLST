/*============================----beg-of-source---============================*/

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YDLST_priv_hguard
#define YDLST_priv_hguard loaded



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "ds (data structures)"
#define     P_SUBJECT   "double-double linked list"
#define     P_PURPOSE   "clean, resiliant, reusable quad/doubly linked list w/deps"

#define     P_NAMESAKE  "kratos-daimon (strength)"
#define     P_HERITAGE  "kratos personified strength and sibling to force, zeal, and victory"
#define     P_IMAGERY   "angel-like winged being wearing a battle helm and sheild"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2011-05"

#define     P_VERMAJOR  "0.--, pre-production"
#define     P_VERMINOR  "0.8-, working out final issues"
#define     P_VERNUM    "0.8b"
#define     P_VERTXT    "finished sequencing update and unit testing.  looks nice."

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



typedef struct cLIST       tLIST;
typedef struct cLINE       tLINE;
typedef struct cSEQ        tSEQ;


typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;




#define   PRIV           static


extern char      unit_answer [LEN_RECD];



#define   YDLST_LINKED    'y'
#define   YDLST_FLOATER   '-'


struct  cLIST {
   /*---(master)---------------*/
   char       *title;                       /* name of list                   */
   void       *data;                        /* data payload                   */
   /*---(lists)----------------*/
   char        linked;                      /* tied to master list            */
   tLIST      *m_prev;                      /* master list prev               */
   tLIST      *m_next;                      /* master list next               */
   /*---(lines)----------------*/
   tLINE      *c_head;                      /* child head                     */
   tLINE      *c_tail;                      /* child tail                     */
   int         c_count;                     /* child count                    */
   /*---(comes before)---------*/
   tSEQ       *p_head;                      /* pred head                      */
   tSEQ       *p_tail;                      /* pred tail                      */
   int         p_count;                     /* pred count                     */
   /*---(comes after)----------*/
   tSEQ       *s_head;                      /* succ head                      */
   tSEQ       *s_tail;                      /* succ tail                      */
   int         s_count;                     /* succ count                     */
   /*---(done)-----------------*/
};

struct  cLINE {
   /*---(ref name)-------------*/
   char       *title;               /* name of list                             */
   void       *data;                /* pointer to data payload                  */
   /*---(lines)----------------*/
   tLINE      *m_prev;
   tLINE      *m_next;
   /*---(lists)----------------*/
   tLIST      *parent;              /* pointer to the owning list               */
   tLINE      *p_next;              /* forward  link in lists links             */
   tLINE      *p_prev;              /* backward link in lists links             */
   /*---(focus)----------------*/
   char        focus;               /* flag to indicate focused 'y' or not '-'  */
   tLINE      *f_prev;              /* backward link in list of focus links     */
   tLINE      *f_next;              /* forward  link in list of focus links     */
   /*---(active)---------------*/
   char        active;              /* flag to indicate active  'y' or not '-'  */
   tLINE      *a_prev;              /* backward link in list of active links    */
   tLINE      *a_next;              /* forward  link in list of active links    */
   /*---(done)-----------------*/
};


struct   cSEQ {
   /*---(seq)------------------*/
   tSEQ       *m_prev;
   tSEQ       *m_next;
   /*---(predecessor)----------*/
   tLIST      *pred;
   tSEQ       *p_prev;
   tSEQ       *p_next;
   /*---(successor)------------*/
   tLIST      *succ;
   tSEQ       *s_prev;
   tSEQ       *s_next;
   /*---(done)-----------------*/
};




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cleanse)--------------*/
char        ydlst_list__wipe        (tLIST *a_list);
char*       ydlst_list__memory      (tLIST *a_list);
/*---(memory)---------------*/
char        ydlst_list_new          (tLIST **a_new);
char        ydlst_list_float        (tLIST **a_new);
char        ydlst_list_free         (tLIST **a_old);
/*---(search)---------------*/
tLIST*      ydlst_list_current      (void);
char        ydlst_list_force        (tLIST *a_list);
/*---(unittest)-------------*/
char*       ydlst_list__unit        (char *a_question, int a_num);
/*---(done)-----------------*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cleanse)--------------*/
char        ydlst_line__wipe        (tLINE *a_line);
char*       ydlst_line__memory      (tLINE *a_line);
/*---(memory)---------------*/
char        ydlst_line__new         (tLINE **a_new);
char        ydlst_line__free        (tLINE **a_new);
/*---(hooking)--------------*/
char        ydlst_line__hook        (tLIST *a_list, tLINE *a_line);
char        ydlst_line__unhook      (tLINE *a_line);
/*---(search)---------------*/
char        ydlst_line_by_ptr       (tLINE *a_curr);
tLINE*      ydlst_line_current      (void);
char        ydlst_line_force        (tLINE *x_line);
/*---(program)--------------*/
char        ydlst_line_purge        (tLIST *a_list);
/*---(unittest)-------------*/
char*       ydlst_line__unit        (char *a_question, int a_num);
/*---(done)-----------------*/


char        ydlst_line__purgelist   (tLIST *a_list);

char        ydlst__test_quiet    (void);
char        ydlst__test_loud     (void);
char        ydlst__test_end      (void);

char*       ydlst_focus__unit       (char *a_question, int a_num);
char*       ydlst_active__unit      (char *a_question, int a_num);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cleanse)--------------*/
char        ydlst_seq__wipe         (tSEQ *a_seq);
char*       ydlst_seq__memory       (tSEQ *a_seq);
/*---(memory)---------------*/
char        ydlst_seq__new          (tSEQ **a_new);
char        ydlst_seq__free         (tSEQ **a_new);
/*---(hooking)--------------*/
char        ydlst_seq__confirm      (tLIST *a_pred, tLIST *a_succ, tSEQ **a_seq);
char        ydlst_seq__hook         (tLIST *a_pred, tLIST *a_succ, tSEQ *a_seq);
char        ydlst_seq__unhook       (tSEQ *a_seq);
char        ydlst_seq__unhook_ends  (tLIST *a_pred, tLIST *a_succ);
/*---(hooking)--------------*/
char        ydlst_seq__alpha        (tLIST *a_list);
char        ydlst_seq__omega        (tLIST *a_list);
char        ydlst_seq__cycle        (int a_lvl, tLIST *a_curr, tLIST *a_look);
/*---(hooking)--------------*/
char        ydlst_seq__create       (tLIST *a_pred, tLIST *a_succ);

char        ydlst_seq__purge        (void);
char*       ydlst_seq__unit         (char *a_question, int a_num);

char        ydlst_seq_init          (void);
char        ydlst_seq_wrap          (void);



#endif
/*============================----end-of-source---============================*/
