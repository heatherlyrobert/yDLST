/*============================----beg-of-source---============================*/

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YDLST_priv_hguard
#define YDLST_priv_hguard loaded


/*===[[ PUBLIC HEADERS ]]=====================================================*/
#define   _GNU_SOURCE           /* to allow asprintf()                        */
/*---(big standards)------------*/
#include  <stdio.h>             /* printf, scanf                              */
#include  <stdlib.h>            /* exit()                                     */
#include  <string.h>            /* strcat, strcpy, strlen, ...                */
#include  <malloc.h>            /* malloc(), free()                           */

#include  <yURG.h>
#include  <yLOG.h>


/* rapidly evolving version number to aid with visual change confirmation     */
#define YDLST_VER_NUM   "0.3b"
#define YDLST_VER_TXT   "linet create, destroy is nicely unit tested, lots of fixes"



typedef struct cLIST  tLIST;
typedef struct cLINE  tLINE;
typedef struct cSEQ   tSEQ;


typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;



#define   LEN_RECD      1000
#define   MAX_FIELD      100

#define   PRIV           static


extern char      unit_answer [LEN_RECD];




#define   INDEX_LIST          100
#define   INDEX_LINK          1000

struct  cLIST
{
   /*---(master)---------------*/
   char     *title;               /* name of list                             */
   void     *data;                /* pointer to data payload                  */
   /*---(lists)----------------*/
   tLIST    *prev;
   tLIST    *next;
   /*---(lines)----------------*/
   tLINE    *head;                /* head of lists links                      */
   tLINE    *tail;                /* tail of lists links                      */
   int       count;               /* number of lists links                    */
   /*---(sequencing)-----------*/
   tSEQ     *preds;
   int       npred;
   tSEQ     *succs;
   int       nsucc;
   /*---(done)-----------------*/
};

struct  cLINE
{
   /*---(ref name)-------------*/
   char     *title;               /* name of list                             */
   void     *data;                /* pointer to data payload                  */
   /*---(lines)----------------*/
   tLIST    *prev;
   tLIST    *next;
   /*---(lists)----------------*/
   tLIST    *parent;              /* pointer to the owning list               */
   tLINE    *p_next;              /* forward  link in lists links             */
   tLINE    *p_prev;              /* backward link in lists links             */
   /*---(focus)----------------*/
   char      focus;               /* flag to indicate focused 'y' or not '-'  */
   tLINE    *f_prev;              /* backward link in list of focus links     */
   tLINE    *f_next;              /* forward  link in list of focus links     */
   /*---(active)---------------*/
   char      active;              /* flag to indicate active  'y' or not '-'  */
   tLINE    *a_prev;              /* backward link in list of active links    */
   tLINE    *a_next;              /* forward  link in list of active links    */
   /*---(done)-----------------*/
};


struct   cSEQ
{
   /*---(predecessor)----------*/
   tLIST      *pred;
   tSEQ       *same;
   /*---(successor)------------*/
   tLIST      *succ;
   /*---(seq)------------------*/
   tSEQ       *prev;
   tSEQ       *next;
   /*---(done)-----------------*/
};






/*---(dependency tree)----------------*/
extern    tLINE    *h_tree;
extern    tLINE    *t_tree;



/*---(unit testing)-----------------------------*/
char     *yDLST_greybox      (char *a_question, int a_index);

/*---(setup specific)---------------------------*/
char      yDLST__float       (tLINE **a_link, char *a_name, void  *a_data);
char      yDLST__unfloat     (tLINE **a_link);

/*---(list indexing)----------------------------*/
char      yDLST__list_index  (tLIST  *a_list);
char      yDLST__list_uindex (tLIST  *a_list);
tLIST    *yDLST__list_find   (int     a_index, char a_change);

/*---(link indexing)----------------------------*/
char      yDLST__link_index  (tLINE  *a_link);
char      yDLST__link_uindex (tLINE  *a_link);
tLINE    *yDLST__link_find   (int     a_index, char a_change);




typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char      status;
   char      full  [LEN_RECD];
   /*---(parsing)-----------*/
   char      recd  [LEN_RECD];
};
extern  tLOCAL its;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
tLIST      *ydlst_list_getcurr      (void);

tLINE*      ydlst_line_getcurr      (void);
char        ydlst_line_setcurr      (tLINE *a_curr);

char        ydlst__test_quiet    (void);
char        ydlst__test_loud     (void);
char        ydlst__test_end      (void);


#endif
/*============================----end-of-source---============================*/
