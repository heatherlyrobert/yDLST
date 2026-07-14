/*============================----beg-of-source---============================*/

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YDLST_priv_hguard
#define YDLST_priv_hguard loaded



/*===[[ BEG_HEADER ]]=========================================================*/

/*===[[ ONE_LINERS ]]=========================================================*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "ds (data structures)"
#define     P_SUBJECT   "sequenced double-double list"
#define     P_PURPOSE   "clean, resiliant, reusable quad/doubly linked list w/deps"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "kratos-daimon (strength)"
#define     P_PRONOUNCE "krah·tohs day·muhn"
#define     P_HERITAGE  "kratos personified strength and sibling to force, zeal, and victory"
#define     P_BRIEFLY   "durable strength and backbone"
#define     P_IMAGERY   "angel-like winged being wearing a battle helm and sheild"
#define     P_REASON    "strength represents the rock-solid requirements for process launching"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yDLST.doubly_linked_with_dependencies"
#define     P_BASENAME  "libyDLST.so"
#define     P_FULLPATH  "/usr/local/lib64/libyDLST.so"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2011-05"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "1.--, production"
#define     P_VERMINOR  "1.1-, modernize code practices"
#define     P_VERNUM    "1.1a"
#define     P_VERTXT    "updated yDLST_list and unit test"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
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
#include  <yENV.h>



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

#define   YDLST_ON        'y'
#define   YDLST_OFF       '-'


struct  cLIST {   /*   all list members begin with "l_"   */
   /*---(master)---------------*/
   char       *l_title;                /* name of list                   */
   void       *l_data;                 /* data payload                   */
   /*---(lists)----------------*/
   char        l_linked;               /* tied to master list            */
   tLIST      *l_mprev;                /* master list prev               */
   tLIST      *l_mnext;                /* master list next               */
   /*---(lines)----------------*/
   tLINE      *l_nhead;                /* child line head                */
   tLINE      *l_ntail;                /* child line tail                */
   int         l_ncount;               /* child line count               */
   /*---(comes before)---------*/
   tSEQ       *l_phead;                /* pred head                      */
   tSEQ       *l_ptail;                /* pred tail                      */
   int         l_pcount;               /* pred count                     */
   /*---(comes after)----------*/
   tSEQ       *l_shead;                /* succ head                      */
   tSEQ       *l_stail;                /* succ tail                      */
   int         l_scount;               /* succ count                     */
   /*---(done)-----------------*/
};

struct  cLINE {   /*   all line members begin with "n_"   */
   /*---(ref name)-------------*/
   char       *n_title;                /* name of list                             */
   void       *n_data;                 /* pointer to data payload                  */
   /*---(lines)----------------*/
   tLINE      *n_mprev;                /* line master prev                         */
   tLINE      *n_mnext;                /* line master next                         */
   /*---(lists)----------------*/
   tLIST      *n_parent;               /* pointer to the owning list               */
   tLINE      *n_lprev;                /* backward link in lists links             */
   tLINE      *n_lnext;                /* forward  link in lists links             */
   /*---(focus)----------------*/
   char        n_focus;                /* flag to indicate focused 'y' or not '-'  */
   tLINE      *n_fprev;                /* backward link in list of focus links     */
   tLINE      *n_fnext;                /* forward  link in list of focus links     */
   /*---(active)---------------*/
   char        n_active;               /* flag to indicate active  'y' or not '-'  */
   tLINE      *n_aprev;                /* backward link in list of active links    */
   tLINE      *n_anext;                /* forward  link in list of active links    */
   /*---(done)-----------------*/
};


struct   cSEQ {   /*   all sequence members begin with "q_"   */
   /*---(seq)------------------*/
   tSEQ       *q_mprev;
   tSEQ       *q_mnext;
   /*---(predecessor)----------*/
   tLIST      *q_pred;
   tSEQ       *q_pprev;
   tSEQ       *q_pnext;
   /*---(successor)------------*/
   tLIST      *q_succ;
   tSEQ       *q_sprev;
   tSEQ       *q_snext;
   /*---(done)-----------------*/
};



/*===[[ yDLST_list.c ]]=======================================================*/
/*········´ ´·············cleanse·´ ´·········································*/
char        ydlst_list__wipe        (tLIST *a_list);
char*       ydlst_list__memory      (tLIST *a_list);
char        ydlst_list__rando       (tLIST *a_list);
/*········´ ´··············memory·´ ´·········································*/
char        ydlst_list__new         (tLIST **r_new);
char        ydlst_list__force       (tLIST **r_new);
char        ydlst_list__free        (tLIST **b_old);
/*········´ ´·············hooking·´ ´·········································*/
char        ydlst_list__hook        (tLIST *a_list);
char        ydlst_list__unhook      (tLIST *a_list);
/*········´ ´···········existance·´ ´·········································*/
char        ydlst_list_create       (char *a_title, void *a_data, tLIST **b_list);
char        yDLST_list_create       (char *a_title, void *a_data);
char        ydlst_list_destroy      (char *a_title, tLIST **b_list);
char        yDLST_list_destroy      (char *a_title);
/*········´ ´··············search·´ ´·········································*/
int         yDLST_list_count        (void);
char        ydlst_list_by_default   (void **r_list, void **r_data, char d_entry [LEN_RECD]);
char        yDLST_list_by_index     (int  n       , void **r_list, void **r_data, char d_entry [LEN_RECD]);
char        yDLST_list_by_cursor    (char a_move  , void **r_list, void **r_data, char d_entry [LEN_RECD]);
char        yDLST_list_by_name      (char *a_title, void **r_list, void **r_data, char d_entry [LEN_RECD]);
char        yDLST_list_by_ptr       (void *a_list , char d_entry [LEN_RECD]);
char        ydlst_list_save_back    (void *a_list, void *a_data, void **r_list, void **r_data, char d_entry [LEN_RECD]);
/*········´ ´·············program·´ ´·········································*/
char        ydlst_list_purge        (void);
char        ydlst_list_init         (void);
char        ydlst_list_wrap         (void);
/*········´ ´··············saving·´ ´·········································*/
void*       yDLST_list_current      (void);
char        yDLST_list_restore      (void *a_list);
/*········´ ´··············report·´ ´·········································*/
char*       ydlst_list__entry       (tLIST *a_list);
char*       ydlst_list_entry        (char a_dir);
char*       ydlst_list_audit        (void);
/*········´ ´···········unit-test·´ ´·········································*/
char*       ydlst_list__unit        (char *a_question, int a_num);
/*········´ ´················DONE·´ ´·········································*/



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(cleanse)--------------*/
char        ydlst_line__wipe        (tLINE *a_line);
char*       ydlst_line__memory      (tLINE *a_line);
/*---(memory)---------------*/
char        ydlst_line__new         (tLINE **a_new);
char        ydlst_line__free        (tLINE **a_new, char a_freedata);
/*---(hooking)--------------*/
char        ydlst_line__hook        (tLIST *a_list, tLINE *a_line);
char        ydlst_line__unhook      (tLINE *a_line);
/*---(search)---------------*/
char        ydlst_line_by_ptr       (tLINE *a_curr);
/*---(program)--------------*/
char        ydlst_line_purge        (tLIST *a_list);
/*---(pushpop)--------------*/
tLINE*      yDLST_line_current      (void);
char        yDLST_line_restore      (tLINE *a_line);
/*---(unittest)-------------*/
char*       ydlst_line__unit        (char *a_question, int a_num);
/*---(done)-----------------*/


char        ydlst_line__purgelist   (tLIST *a_list);

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
/*---(pushpop)--------------*/
tSEQ*       ydlst_seq_current       (void);
char        ydlst_seq_restore       (tSEQ *a_seq);
/*---(unittest)-------------*/
char*       ydlst_seq__unit         (char *a_question, int a_num);

char        ydlst_seq_init          (void);
char        ydlst_seq_wrap          (void);


/*---(pushpop)--------------*/
tLINE*      ydlst_active_current    (void);
char        ydlst_active_restore    (tLINE *a_line);


/*---(pushpop)--------------*/
tLINE*      ydlst_focus_current     (void);
char        ydlst_focus_restore     (tLINE *a_line);


#endif
/*============================----end-of-source---============================*/
