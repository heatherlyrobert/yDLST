/*============================----beg-of-source---============================*/


#include   "yDLST.h"

/*===[[ PUBLIC HEADERS ]]=====================================================*/
#define   _GNU_SOURCE           /* to allow asprintf()                        */
/*---(big standards)------------*/
#include  <stdio.h>             /* printf, scanf                              */
#include  <stdlib.h>            /* exit()                                     */
#include  <string.h>            /* strcat, strcpy, strlen, ...                */
#include  <malloc.h>            /* malloc(), free()                           */



/* rapidly evolving version number to aid with visual change confirmation     */
#define YDLST_VER_NUM   "0.2c"
#define YDLST_VER_TXT   "moved to make_program makefile enhancement"



typedef struct cLIST  tLIST;
typedef struct cLINK  tLINK;
typedef struct cTIES  tTIES;


typedef long   long      llong;
typedef const  int       cint;
typedef const  long      clong;
typedef const  char      cchar;



#define   MAX_RECD      1000
#define   MAX_FIELD      100

#define   PRIV           static





#define   INDEX_LIST          100
#define   INDEX_LINK          1000

struct  cLIST
{
   /*---(ref name)-------------*/
   char     *name;                /* name of list                             */
   /*---(list DLL)-------------*/
   tLIST    *f_lists;             /* forward  link in list of lists           */
   tLIST    *b_lists;             /* backward link in list of lists           */
   /*---(hash index)-----------*/
   int       id;                  /* unique list id                           */
   tLIST    *x_lists;             /* next list in same index position         */
   /*---(link DLL)-------------*/
   tLINK    *head;                /* head of lists links                      */
   tLINK    *tail;                /* tail of lists links                      */
   int       num;                 /* number of lists links                    */
   /*---(data playload)--------*/
   void     *data;                /* pointer to data payload                  */
};

struct  cLINK
{
   /*---(parent)---------------*/
   tLIST    *list;                /* pointer to the owning list               */
   /*---(ref name)-------------*/
   char     *name;                /* name of list                             */
   /*---(links dll)------------*/
   tLINK    *f_links;             /* forward  link in list of all links       */
   tLINK    *b_links;             /* backward link in list of all links       */
   /*---(hash index)-----------*/
   int       id;                  /* unique link id                           */
   tLINK    *x_links;             /* next list in same index position         */
   /*---(links dll)------------*/
   tLINK    *fore;                /* forward  link in lists links             */
   tLINK    *back;                /* backward link in lists links             */
   /*---(focus dll)------------*/
   char      focus;               /* flag to indicate focused 'y' or not '-'  */
   tLINK    *f_focus;             /* forward  link in list of focus links     */
   tLINK    *b_focus;             /* backward link in list of focus links     */
   /*---(run  DLL)-------------*/
   char      active;              /* flag to indicate active  'y' or not '-'  */
   tLINK    *f_active;            /* forward  link in list of active links    */
   tLINK    *b_active;            /* backward link in list of active links    */
   /*---(deps SLL)-------------*/
   tTIES    *h_ups;               /* pointer to first upstream link           */
   int       n_ups;               /* number of upstream links                 */
   tTIES    *h_downs;             /* pointer to first downstream link         */
   int       n_downs;             /* number of downstream links               */
   /*---(data playload)--------*/
   void     *data;                /* pointer to data payload                  */
};

struct  cTIES
{
   /*---(links)----------------*/
   tLINK    *up;
   tLINK    *down;
   /*---(dep/req SLL)----------*/
   tTIES    *f_ups;
   tTIES    *f_downs;
   /*---(all deps DLL)---------*/
   tTIES    *f_ties;
   tTIES    *b_ties;
   /*---(data playload)--------*/
   void     *data;                /* pointer to data payload                  */
};



/*---(list of all lists)--------------*/
extern    tLIST    *h_lists;           /* head node pointer                   */
extern    tLIST    *t_lists;           /* tail node pointer                   */
extern    int       n_lists;           /* number of lists                     */
extern    int       i_lists;           /* next sequential list id             */
extern    int       c_lists;           /* id of current list                  */
extern    tLIST    *p_lists;           /* pointer to current list             */
extern    tLIST    *x_lists [INDEX_LIST];  /* hash index to list of all lists */

/*---(list of all links)--------------*/
extern    tLINK    *h_links;           /* head node pointer                   */
extern    tLINK    *t_links;           /* tail node pointer                   */
extern    int       n_links;           /* number of links                     */
extern    int       i_links;           /* next sequential link id             */
extern    int       c_links;           /* id of current link                  */
extern    tLINK    *p_links;           /* pointer to current link             */
extern    tLINK    *x_links [INDEX_LINK];  /* hash index to list of all links */

/*---(sub list)-----------------------*/
extern    tLINK    *h_focus;
extern    tLINK    *t_focus;
extern    int       n_focus;
extern    int       c_focus;
extern    tLINK    *p_focus;

/*---(active list)--------------------*/
extern    tLINK    *h_active;
extern    tLINK    *t_active;
extern    int       n_active;
extern    int       c_active;
extern    tLINK    *p_active;

/*---(full ties list)-----------------*/
extern    tTIES    *h_ties;
extern    tTIES    *t_ties;
extern    int       n_ties;
extern    tTIES    *p_ties;

/*---(dependency tree)----------------*/
extern    tLINK    *h_tree;
extern    tLINK    *t_tree;



/*---(unit testing)-----------------------------*/
char     *yDLST_greybox      (char *a_question, int a_index);

/*---(setup specific)---------------------------*/
char      yDLST__float       (tLINK **a_link, char *a_name, void  *a_data);
char      yDLST__unfloat     (tLINK **a_link);

/*---(list indexing)----------------------------*/
char      yDLST__list_index  (tLIST  *a_list);
char      yDLST__list_uindex (tLIST  *a_list);
tLIST    *yDLST__list_find   (int     a_index, char a_change);

/*---(link indexing)----------------------------*/
char      yDLST__link_index  (tLINK  *a_link);
char      yDLST__link_uindex (tLINK  *a_link);
tLINK    *yDLST__link_find   (int     a_index, char a_change);

/*---(tie finding)------------------------------*/
tTIES    *yDLST__tie_find    (tLINK *a_up, tLINK *a_down);



typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char      status;
   char      full  [MAX_RECD];
   /*---(parsing)-----------*/
   char      recd  [MAX_RECD];
};
extern  tLOCAL its;



/*============================----end-of-source---============================*/
