/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2011 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*---(list of all links)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLINE      *S_head      = NULL;  /* head node pointer                   */
static      tLINE      *S_tail      = NULL;  /* tail node pointer                   */
static      tLINE      *S_curr      = NULL;  /* pointer to current link             */
static      int         S_count     =    0;  /* number of links                     */

static      tLINE      *S_rptg      = NULL;  /* pointer to current reporting link   */

static      char      (*S_linewipe)      (void *a_data) = NULL;



/*====================------------------------------------====================*/
/*===----                    cleansing and cleaning                    ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSE_________o () { return; }

char
ydlst_line__wipe        (tLINE *a_line)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_snote   ("null pointer");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(master)-------------------------*/
   DEBUG_INPT   yLOG_snote   ("master");
   a_line->n_title   = NULL;
   a_line->n_data    = NULL;
   /*---(line list)------------*/
   DEBUG_INPT   yLOG_snote   ("full lines");
   a_line->n_mprev   = NULL;
   a_line->n_mnext   = NULL;
   /*---(list)-----------------*/
   DEBUG_INPT   yLOG_snote   ("list lines");
   a_line->n_parent  = NULL;
   a_line->n_lprev   = NULL;
   a_line->n_lnext   = NULL;
   /*---(focus)----------------*/
   DEBUG_INPT   yLOG_snote   ("focus lines");
   a_line->n_focus   = YDLST_OFF;
   a_line->n_fprev   = NULL;
   a_line->n_fnext   = NULL;
   /*---(active)---------------*/
   DEBUG_INPT   yLOG_snote   ("active lines");
   a_line->n_active  = YDLST_OFF;
   a_line->n_aprev   = NULL;
   a_line->n_anext   = NULL;
   /*---(complete)-------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 1;
}


char*
ydlst_line__memory      (tLINE *a_line)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_line == NULL)  return rce;
   /*---(header)-------------------------*/
   yENV_check_beg    ();
   /*---(master)-------------------------*/
   yENV_check_ptr    (a_line->n_title);
   yENV_check_ptr    (a_line->n_data);
   yENV_check_spacer ();
   /*---(master list of lines)-*/
   yENV_check_ptr    (a_line->n_mprev);
   yENV_check_ptr    (a_line->n_mnext);
   yENV_check_spacer ();
   /*---(list of list lines)---*/
   yENV_check_ptr    (a_line->n_parent);
   yENV_check_ptr    (a_line->n_lprev);
   yENV_check_ptr    (a_line->n_lnext);
   yENV_check_spacer ();
   /*---(focus)----------------*/
   yENV_check_char   (a_line->n_focus);
   yENV_check_ptr    (a_line->n_fprev);
   yENV_check_ptr    (a_line->n_fnext);
   yENV_check_spacer ();
   /*---(focus)----------------*/
   yENV_check_char   (a_line->n_active);
   yENV_check_ptr    (a_line->n_aprev);
   yENV_check_ptr    (a_line->n_anext);
   yENV_check_end    ();
   /*---(complete)-----------------------*/
   return yENV_check ();
}

char
ydlst_line__rando        (tLINE *a_line)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_line == NULL)  return rce;
   /*---(master)-------------------------*/
   a_line->n_title       = 0x01;
   a_line->n_data        = 0x02;
   /*---(list of lists)--------*/
   a_line->n_mprev       = 0x03;
   a_line->n_mnext       = 0x04;
   /*---(list of lines)--------*/
   a_line->n_parent      = 0x05;
   a_line->n_lprev       = 0x06;
   a_line->n_lnext       = 0x07;
   /*---(list of lines)--------*/
   a_line->n_focus       = 'a';
   a_line->n_fprev       = 0x06;
   a_line->n_fnext       = 0x07;
   /*---(list of lines)--------*/
   a_line->n_active      = 'b';
   a_line->n_aprev       = 0x06;
   a_line->n_anext       = 0x07;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char ydlst_line__new   (tLINE **r_new) { return yENV_new  ("line", sizeof (tLINE), r_new, NULL, '-', ydlst_line__wipe); }
char ydlst_line__force (tLINE **r_new) { return yENV_new  ("line", sizeof (tLINE), r_new, NULL, 'y', ydlst_line__wipe); }
char ydlst_line__free  (tLINE **b_old) { return yENV_free ("line", b_old, NULL); }

/*> char                                                                              <* 
 *> ydlst_line__new_OLD     (tLINE **a_new)                                           <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    int         rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    int         x_tries     =    0;                                                <* 
 *>    tLINE      *x_new       = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_senter  (__FUNCTION__);                                      <* 
 *>    /+---(check return)-------------------+/                                       <* 
 *>    DEBUG_YDLST   yLOG_spoint  (a_new);                                            <* 
 *>    --rce;  if (a_new == NULL) {                                                   <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_YDLST   yLOG_spoint  (*a_new);                                           <* 
 *>    --rce;  if (*a_new != NULL) {                                                  <* 
 *>       DEBUG_YDLST   yLOG_snote   ("already set");                                 <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(default)------------------------+/                                       <* 
 *>    *a_new = NULL;                                                                 <* 
 *>    /+---(allocate)-----------------------+/                                       <* 
 *>    while (x_new == NULL) {                                                        <* 
 *>       ++x_tries;                                                                  <* 
 *>       x_new = (tLINE *) malloc (sizeof (tLINE));                                  <* 
 *>       if (x_tries > 3)   break;                                                   <* 
 *>    }                                                                              <* 
 *>    DEBUG_YDLST   yLOG_sint    (x_tries);                                          <* 
 *>    DEBUG_YDLST   yLOG_spoint  (x_new);                                            <* 
 *>    --rce;  if (x_new == NULL) {                                                   <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(wipe)---------------------------+/                                       <* 
 *>    ydlst_line__wipe (x_new);                                                      <* 
 *>    /+---(save return)--------------------+/                                       <* 
 *>    *a_new = x_new;                                                                <* 
 *>    /+---(add to list)--------------------+/                                       <* 
 *>    if (S_head == NULL) {                                                          <* 
 *>       DEBUG_YDLST  yLOG_snote   ("add first");                                    <* 
 *>       S_head          = x_new;                                                    <* 
 *>       S_tail          = x_new;                                                    <* 
 *>    } else {                                                                       <* 
 *>       DEBUG_YDLST  yLOG_snote   ("append to end");                                <* 
 *>       x_new->n_mprev  = S_tail;                                                   <* 
 *>       S_tail->n_mnext = x_new;                                                    <* 
 *>       S_tail          = x_new;                                                    <* 
 *>    }                                                                              <* 
 *>    /+---(update count)-------------------+/                                       <* 
 *>    ++S_count;                                                                     <* 
 *>    DEBUG_YDLST  yLOG_sint    (S_count);                                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> ydlst_line__free_OLD    (tLINE **a_old, char a_freedata)                          <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    int         rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    tLINE      *x_old       = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_senter  (__FUNCTION__);                                      <* 
 *>    /+---(check return)-------------------+/                                       <* 
 *>    DEBUG_YDLST   yLOG_spoint  (a_old);                                            <* 
 *>    --rce;  if (a_old == NULL) {                                                   <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_YDLST   yLOG_spoint  (*a_old);                                           <* 
 *>    --rce;  if (*a_old == NULL) {                                                  <* 
 *>       DEBUG_YDLST   yLOG_snote   ("never set");                                   <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(simplify)-----------------------+/                                       <* 
 *>    x_old = *a_old;                                                                <* 
 *>    /+---(remove from lists)--------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_snote   ("remove from list");                                <* 
 *>    if (x_old->n_mnext != NULL)  x_old->n_mnext->n_mprev = x_old->n_mprev;         <* 
 *>    else                        S_tail                = x_old->n_mprev;            <* 
 *>    if (x_old->n_mprev != NULL)  x_old->n_mprev->n_mnext = x_old->n_mnext;         <* 
 *>    else                        S_head                = x_old->n_mnext;            <* 
 *>    /+---(free title)---------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_spoint  (x_old->n_title);                                    <* 
 *>    if (x_old->n_title != NULL)  free (x_old->n_title);                            <* 
 *>    x_old->n_title == NULL;                                                        <* 
 *>    /+---(free data)----------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_spoint  (x_old->n_data);                                     <* 
 *>    if (a_freedata == 'y' && x_old->n_data  != NULL)  free (x_old->n_data);        <* 
 *>    x_old->n_data = NULL;                                                          <* 
 *>    /+---(clear and return)---------------+/                                       <* 
 *>    free (x_old);                                                                  <* 
 *>    *a_old = NULL;                                                                 <* 
 *>    /+---(update count)-------------------+/                                       <* 
 *>    --S_count;                                                                     <* 
 *>    DEBUG_YDLST  yLOG_sint    (S_count);                                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                     hooking and unhooking                    ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
ydlst_line__hook        (tLIST *a_list, tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_list->l_title);
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_line->n_title);
   DEBUG_YDLST  yLOG_spoint  (a_line->n_parent);
   --rce;  if (a_line->n_parent != NULL) {
      DEBUG_YDLST   yLOG_snote   ("already hooked");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(add to line inventory)----------*/
   if (S_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("add first");
      S_head          = a_line;
      S_tail          = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to end");
      a_line->n_mprev = S_tail;
      S_tail->n_mnext = a_line;
      S_tail          = a_line;
   }
   /*---(update count)-------------------*/
   ++S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(tie to parent)---------------*/
   DEBUG_YDLST  yLOG_snote   ("n_parent");
   a_line->n_parent   = a_list;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->n_lnext    = NULL;
   a_line->n_lprev    = NULL;
   /*---(into lists links)------------*/
   if (a_list->l_nhead == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first line");
      a_list->l_nhead          = a_line;
      a_list->l_ntail          = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append line");
      a_line->n_lprev          = a_list->l_ntail;
      a_list->l_ntail->n_lnext = a_line;
      a_list->l_ntail          = a_line;
   }
   /*---(update count)-------------------*/
   ++a_list->l_ncount;
   DEBUG_YDLST  yLOG_sint    (a_list->l_ncount);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_line__unhook      (tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_line->n_title);
   x_list = a_line->n_parent;
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("not hooked to parent");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   /*---(into lists links)------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->n_lnext != NULL)  a_line->n_lnext->n_lprev = a_line->n_lprev;
   else                          x_list->l_ntail          = a_line->n_lprev;
   if (a_line->n_lprev != NULL)  a_line->n_lprev->n_lnext = a_line->n_lnext;
   else                          x_list->l_nhead          = a_line->n_lnext;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("ground");
   a_line->n_lnext    = NULL;
   a_line->n_lprev    = NULL;
   a_line->n_parent   = NULL;
   /*---(update count)-------------------*/
   --x_list->l_ncount;
   DEBUG_YDLST  yLOG_sint    (x_list->l_ncount);
   /*---(remove from line inventory)-----*/
   DEBUG_YDLST  yLOG_snote   ("remove from line inventory");
   if (a_line->n_mnext != NULL)  a_line->n_mnext->n_mprev = a_line->n_mprev;
   else                          S_tail                   = a_line->n_mprev;
   if (a_line->n_mprev != NULL)  a_line->n_mprev->n_mnext = a_line->n_mnext;
   else                          S_head                   = a_line->n_mnext;
   /*---(update count)-------------------*/
   --S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      finding a line                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

#define     IF_LOCAL  (x_local) ? 

int
yDLST_line_count        (char a_scope)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(check scope)--------------------*/
   if (a_scope != 0 && strchr ("Aa*", a_scope) != NULL) {
      DEBUG_YDLST  yLOG_snote   ("global");
      DEBUG_YDLST  yLOG_sint    (S_count);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return S_count;
   }
   /*---(get list)-----------------------*/
   DEBUG_YDLST  yLOG_snote   ("local");
   x_list = yDLST_list_current ();
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   DEBUG_YDLST  yLOG_sint    (x_list->l_ncount);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->l_ncount;
}

char
ydlst_line__scope       (char a_scope, char *a_local, tLIST **a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(check scope)--------------------*/
   DEBUG_YDLST  yLOG_schar   (a_scope);
   if (a_scope != 0 && strchr ("Aa*", a_scope) != NULL)  {
      DEBUG_YDLST  yLOG_snote   ("global");
      *a_local = 0;
   } else {
      DEBUG_YDLST  yLOG_snote   ("local");
      *a_local = 1;
   }
   /*---(start)--------------------------*/
   --rce;  if (*a_local) {
      *a_list = yDLST_list_current ();
      DEBUG_YDLST  yLOG_spoint  (*a_list);
      if (*a_list == NULL) {
         DEBUG_YDLST  yLOG_snote   ("no current");
         return rce;
      }
      DEBUG_YDLST  yLOG_snote   ((*a_list)->l_title);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ydlst_line__parent      (char a_local)
{
   if (!a_local) {
      yDLST_list_restore (S_curr->n_parent);
      DEBUG_YDLST  yLOG_snote   (S_curr->n_parent->l_title);
   }
   return 0;
}

char
ydlst_line__default     (void **r_line, void ** r_data, char d_entry [LEN_RECD])
{
   if (r_line  != NULL)  *r_line = NULL;
   if (r_data  != NULL)  *r_data = NULL;
   if (d_entry != NULL)  ystrlcpy (d_entry, ydlst_line__entry (NULL), LEN_RECD);
   return 0;
}

char
ydlst_line__save_back   (void *a_line, void *a_data, void **r_line, void **r_data, char d_entry [LEN_RECD])
{
   S_curr  = (tLINE *) a_line;
   if (r_line  != NULL)  *r_line  = a_line;
   if (r_data  != NULL)  *r_data  = a_data;
   if (d_entry != NULL)  ystrlcpy (d_entry, ydlst_line__entry (a_line), LEN_RECD);
   return 0;
}

char       /*--> find a list using sequential pos ----------------------------*/
yDLST_line_by_index     (char a_scope, int n, void **r_line, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_local     =    0;
   int         c           =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_line__default (r_line, r_data, d_entry);
   /*---(defaults)-----------------------*/
   if (r_line != NULL)  *r_line = NULL;
   if (r_data != NULL)  *r_data = NULL;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_sint    (n);
   DEBUG_YDLST  yLOG_sint    (S_count);
   --rce;  if (n < 0 || n >= S_count) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (S_head);
   --rce;  if (S_head == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check scope)--------------------*/
   rc = ydlst_line__scope (a_scope, &x_local, &x_list);
   DEBUG_YDLST  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(move)---------------------------*/
   if (x_local)  x_line = x_list->l_nhead;
   else          x_line = S_head;
   while (x_line != NULL) {
      if (c >= n)  break;
      if (x_local)  x_line = x_line->n_lnext;
      else          x_line = x_line->n_mnext;
      ++c;
   }
   /*---(check)--------------------------*/
   DEBUG_YDLST  yLOG_sint    (c);
   --rce;  if (c != n) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_line);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   ydlst_line__save_back (x_line, x_line->n_data, r_line, r_data, d_entry);
   DEBUG_YDLST  yLOG_snote   (S_curr->n_title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
yDLST_line_by_cursor    (char a_scope, char a_move, void **r_line, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    1;
   char        x_local     =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_line__default (r_line, r_data, d_entry);
   /*---(defaults)-----------------------*/
   if (r_line != NULL)  *r_line = NULL;
   if (r_data != NULL)  *r_data = NULL;
   /*---(defense)------------------------*/
   x_curr = S_curr;
   DEBUG_YDLST  yLOG_schar   (a_move);
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YDLST  yLOG_snote   ("starting at NULL");
      /*---(non-bounce)------------------*/
      if (strchr (YDLST_DREL, a_move) != NULL) {
         DEBUG_YDLST  yLOG_snote   ("non-bounce");
         S_curr = x_curr;
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(curr/show)-------------------*/
      if (a_move == YDLST_CURR || a_move == YDLST_DCURR) {
         DEBUG_YDLST  yLOG_snote   ("current-only, quick-out");
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(bounce types)----------------*/
      DEBUG_YDLST  yLOG_snote   ("bounce, reset to head");
      x_curr = S_head;
      DEBUG_DATA   yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check scope)--------------------*/
   rc = ydlst_line__scope (a_scope, &x_local, &x_list);
   DEBUG_YDLST  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_sint    (x_local);
   rc = 1;
   /*---(switch)-------------------------*/
   DEBUG_YDLST  yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      DEBUG_YDLST  yLOG_snote   ("HEAD");
      x_curr = IF_LOCAL x_list->l_nhead : S_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      DEBUG_YDLST  yLOG_snote   ("PREV");
      x_curr = IF_LOCAL x_curr->n_lprev : x_curr->n_mprev;;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      DEBUG_YDLST  yLOG_snote   ("CURR");
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      DEBUG_YDLST  yLOG_snote   ("NEXT");
      x_curr = IF_LOCAL x_curr->n_lnext : x_curr->n_mnext;;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      DEBUG_YDLST  yLOG_snote   ("TAIL");
      x_curr = IF_LOCAL x_list->l_ntail : S_tail;
      break;
   default         :
      DEBUG_YDLST  yLOG_snote   ("UNKNOWN");
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      DEBUG_YDLST  yLOG_snote   ("currently at NULL");
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV) {
         DEBUG_YDLST  yLOG_snote   ("bounce-prev");
         x_curr = IF_LOCAL x_list->l_nhead : S_head;
      }
      if (a_move == YDLST_NEXT) {
         DEBUG_YDLST  yLOG_snote   ("bounce-next");
         x_curr = IF_LOCAL x_list->l_ntail : S_tail;
      }
      DEBUG_YDLST  yLOG_spoint  (x_curr);
      /*---(no bounce)-------------------*/
      if (x_curr == NULL) {
         DEBUG_YDLST  yLOG_snote   ("non-bounce");
         S_curr = x_curr;
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(mark trouble)----------------*/
      DEBUG_DATA   yLOG_snote   ("BOUNCE");
      rc = rce;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   ydlst_line__save_back (x_curr, x_curr->n_data, r_line, r_data, d_entry);
   DEBUG_YDLST  yLOG_snote   (S_curr->n_title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char       /*--> find a list using its title ---------------------------------*/
yDLST_line_by_name      (char a_scope, char *a_title, void **r_line, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   char        x_local     =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_line__default (r_line, r_data, d_entry);
   /*---(defaults)-----------------------*/
   if (r_line != NULL)  *r_line = NULL;
   if (r_data != NULL)  *r_data = NULL;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_title);
   DEBUG_YDLST  yLOG_spoint  (S_head);
   --rce;  if (S_head == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check scope)--------------------*/
   rc = ydlst_line__scope (a_scope, &x_local, &x_list);
   DEBUG_YDLST  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(move)---------------------------*/
   if (x_local)   x_line = x_list->l_nhead;
   else           x_line = S_head;
   while (x_line != NULL) {
      if (x_line->n_title != NULL) {
         if (strcmp (x_line->n_title, a_title) == 0) break;
      }
      if (x_local)   x_line = x_line->n_lnext;
      else           x_line = x_line->n_mnext;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (S_curr);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   ydlst_line__save_back (x_line, x_line->n_data, r_line, r_data, d_entry);
   DEBUG_YDLST  yLOG_snote   (S_curr->n_title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 1;
}

char
ydlst_line_by_ptr       (tLINE *a_line, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_line__default (NULL  , NULL  , d_entry);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(key data)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (S_head);
   DEBUG_YDLST  yLOG_spoint  (S_tail);
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(search)-------------------------*/
   x_line = S_head;
   while (x_line != NULL) {
      if (x_line == a_line)   break;
      x_line = x_line->n_mnext;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_line);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   S_curr = a_line;
   DEBUG_YDLST  yLOG_snote   (S_curr->n_title);
   /*---(update list)--------------------*/
   yDLST_list_restore (S_curr->n_parent);
   DEBUG_YDLST  yLOG_snote   (S_curr->n_parent->l_title);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 1;
}

char
yDLST_line_list         (void **a_list, void **r_data)
{
   char        rce         =  -10;
   if (a_list != NULL)  *a_list == NULL;
   if (r_data != NULL)  *r_data == NULL;
   --rce;  if (S_curr == NULL)   return rce;
   if (a_list != NULL)  *a_list = S_curr->n_parent;
   if (r_data != NULL && S_curr->n_parent != NULL)  *r_data = S_curr->n_parent->l_data;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*----: prepare a new line for use --------------------------------*/
yDLST_line_create       (char *a_title, void *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = yDLST_list_current ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   /*---(find list)----------------------*/
   yDLST_line_by_name (YDLST_DCURR, a_title, &x_new, NULL, NULL);
   DEBUG_YDLST  yLOG_point   ("existing"  , x_new);
   --rce;  if (x_new != NULL) {
      DEBUG_YDLST   yLOG_note    ("line already exists");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_title);
   /*---(create)-------------------------*/
   rc = ydlst_line__new (&x_new);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook to list)-------------------*/
   rc = ydlst_line__hook (x_list, x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->n_title = strdup (a_title);
   x_new->n_data  = a_data;
   /*---(make current)-------------------*/
   S_curr       = x_new;
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char       /*----: teardown the list after use ---------------------------*/
yDLST_line_destroy      (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_line_by_name (YDLST_DCURR, a_title, NULL, NULL, NULL);
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   --rce;  if (S_curr == NULL) {
      DEBUG_YDLST   yLOG_note    ("line could not be found");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear focus)-----------------*/
   rc = yDLST_focus_off  ();
   DEBUG_YDLST  yLOG_value   ("focus"     , rc);
   rc = yDLST_active_off ();
   DEBUG_YDLST  yLOG_value   ("active"    , rc);
   /*---(unhook)----------------------*/
   rc = ydlst_line__unhook (S_curr);
   DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_point  ("n_data"     , S_curr->n_data);
   DEBUG_YDLST  yLOG_point   ("S_linewipe", S_linewipe);
   --rce;  if (S_curr->n_data != NULL && S_linewipe != NULL) {
      rc = S_linewipe (S_curr->n_data);
      DEBUG_YDLST  yLOG_value   ("listwipe"  , rc);
      if (rc < 0) {
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   S_curr->n_data = NULL;
   DEBUG_YDLST  yLOG_point  ("l_data"     , S_curr->n_data);
   /*---(reset current)------------------*/
   if (S_rptg == S_curr)  S_rptg = NULL;
   /*---(delete)-------------------------*/
   rc = ydlst_line__free (&S_curr);
   DEBUG_YDLST  yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char       /*----: clear all links from a list -------------------------------*/
ydlst_line_purge        (tLIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(walk through attached links)----*/
   S_curr = a_list->l_nhead;
   DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   while (S_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (S_curr->n_title);
      rc = yDLST_line_destroy (S_curr->n_title);
      DEBUG_YDLST  yLOG_value   ("destroy"   , rc);
      S_curr  = a_list->l_nhead;
      DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_line_purge_all    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(walk through attached links)----*/
   S_curr = S_head;
   DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   while (S_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (S_curr->n_title);
      rc = yDLST_line_destroy (S_curr->n_title);
      DEBUG_YDLST  yLOG_value   ("destroy"   , rc);
      S_curr  = S_head;
      DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: clear all links from a list -------------------------------*/
yDLST_line_clearlist    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = yDLST_list_current ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_note    (x_list->l_title);
   /*---(walk through attached links)----*/
   S_curr = x_list->l_nhead;
   DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   while (S_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (S_curr->n_title);
      yDLST_focus_off  ();
      yDLST_active_off ();
      rc = ydlst_line__unhook (S_curr);
      /*> rc = ydlst_line__free   (&S_curr, 'y');                                     <*/
      rc = ydlst_line__free   (&S_curr);
      S_curr  = x_list->l_nhead;
      DEBUG_YDLST   yLOG_point   ("S_curr"    , S_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_line_config       (char f_linewipe (void *))
{
   S_linewipe = f_linewipe;
   return 1;
}

char
ydlst_line_init         (char f_linewipe (void *))
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   S_head     = NULL;
   S_tail     = NULL;
   S_curr     = NULL;
   S_count    =    0;
   S_rptg     = NULL;
   ydlst_line_config (f_linewipe);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_line_wrap         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   ydlst_line_purge_all ();
   /*---(initialize)---------------------*/
   S_head     = NULL;
   S_tail     = NULL;
   S_curr     = NULL;
   S_count    =    0;
   S_rptg     = NULL;
   ydlst_line_config (NULL);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    reporting and output                      ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char*
ydlst_line__entry       (tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND]  = "";
   /*---(short-cuts)---------------------*/
   if (a_line == NULL) return "´·············· ´···········  ´·············· ´··············  ´·············· ´·············· ´··············  - ´·············· ´··············  - ´·············· ´··············  Ï";
   if (a_line == 0x01) return "---title------- ---data-----  ---mprev------- ---mnext-------  ---parent------ ---lprev------- ---lnext-------  F ---fprev------- ---fnext-------  A ---aprev------- ---anext-------  Ï";
   /*---(prepare)------------------------*/
   strcpy (unit_answer, "");
   /*---(master)-------------------------*/
   ystrlcat (unit_answer, ystrlpadquick  (a_line->n_title         , '<', '.', 15), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick    ((double) ((int) (a_line->n_data)), '<', 'x', 0, '-', '.', '-', '-', 12), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   /*---(main list)----------------------*/
   if (a_line->n_mprev != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_mprev->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_line->n_mnext != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_mnext->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, " ", LEN_RECD);
   /*---(parent)-------------------------*/
   if (a_line->n_parent != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_parent->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_line->n_lprev != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_lprev->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_line->n_lnext != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_lnext->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, " ", LEN_RECD);
   /*---(focus)--------------------------*/
   sprintf (t, "%c ", a_line->n_focus);
   ystrlcat (unit_answer, t  , LEN_RECD);
   if (a_line->n_fprev != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_fprev->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_line->n_fnext != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_fnext->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, " ", LEN_RECD);
   /*---(active)-------------------------*/
   sprintf (t, "%c ", a_line->n_active);
   ystrlcat (unit_answer, t  , LEN_RECD);
   if (a_line->n_aprev != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_aprev->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_line->n_anext != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_line->n_anext->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, " ", LEN_RECD);
   /*---(final)--------------------------*/
   ystrlcat (unit_answer, "Ï", LEN_RECD);
   /*---(complete)-----------------------*/
   return unit_answer;
}

char*
ydlst_line_entry        (char a_dir)
{
   char        rc          =    0;
   tLINE      *x_save      = NULL;
   tLINE      *x_curr      = NULL;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(save-list)----------------------*/
   x_list = yDLST_list_current ();
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   if (S_curr != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_curr->n_title);
   }
   x_save = S_curr;
   DEBUG_YDLST  yLOG_point   ("x_save"    , x_save);
   if (x_save != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , x_save->n_title);
   }
   DEBUG_YDLST  yLOG_char    ("a_dir"     , a_dir);
   DEBUG_YDLST  yLOG_point   ("S_rptg"    , S_rptg);
   if (S_rptg != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_rptg->n_title);
   }
   /*---(fix)----------------------------*/
   if (a_dir == YDLST_CURR || a_dir == YDLST_DCURR) S_rptg = S_curr;
   else                                             S_curr = S_rptg;
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   if (S_curr != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_curr->n_title);
   }
   DEBUG_YDLST  yLOG_point   ("S_rptg"    , S_rptg);
   if (S_rptg != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_rptg->n_title);
   }
   /*---(cursor)-------------------------*/
   if (a_dir == 'T')  x_curr = 0x01;
   else  rc = yDLST_line_by_cursor (YDLST_GLOBAL, a_dir, &x_curr, NULL, NULL);
   if (rc < 0)  x_curr = NULL;
   DEBUG_YDLST  yLOG_point   ("x_curr"    , x_curr);
   if (x_curr >  0x1) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , x_curr->n_title);
   }
   /*---(save-back)----------------------*/
   if (x_curr > 0x1) S_rptg = x_curr;
   DEBUG_YDLST  yLOG_point   ("S_rptg"    , S_rptg);
   if (S_rptg != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_rptg->n_title);
   }
   S_curr = x_save;
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   if (S_curr != NULL) {
      DEBUG_YDLST  yLOG_info    ("->n_title" , S_curr->n_title);
   }
   /*---(restore-list)-------------------*/
   yDLST_list_restore (x_list);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return ydlst_line__entry (x_curr);
}

char*
ydlst_line_audit        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLINE      *o           = NULL;
   o = S_tail; while (o != NULL) { ++x_back; o = o->n_mprev; }
   o = S_head; while (o != NULL) { ++x_fore; o = o->n_mnext; }
   snprintf (unit_answer, LEN_RECD, "line audit ::  ····  ····  %3dc  %3df  %3db", S_count, x_fore, x_back);
   o = S_head;
   ystrlcat (unit_answer, "  å ", LEN_RECD);
   while (o != NULL) {
      ystrlcat (unit_answer, o->n_title, LEN_RECD);
      ystrlcat (unit_answer, " "       , LEN_RECD);
      o = o->n_mnext;
   }
   ystrlcat (unit_answer, "æ", LEN_RECD);
   return unit_answer;
}



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

void*  yDLST_line_current   (void)          { return S_curr; }
char   yDLST_line_restore   (void *a_line)  { S_curr = (tLINE*) a_line;  return 0; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ydlst_line__unit        (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLINE      *o           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "LINE unit        : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      o = S_head; while (o != NULL) { ++x_fore; o = o->n_mnext; }
      o = S_tail; while (o != NULL) { ++x_back; o = o->n_mprev; }
      snprintf (unit_answer, LEN_RECD, "LINE count       : %3dc  %3df  %3db", S_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = S_curr;
      if (o != NULL) {
         x_len = strlen (o->n_title);
         sprintf  (t, "[%.20s]", o->n_title);
         snprintf (unit_answer, LEN_RECD, "LINE current     : %2d%-22.22s   %c  %c  %c", x_len, t, (o->n_parent == NULL) ? YDLST_OFF : YDLST_ON, o->n_focus, o->n_active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE current     :  0[]                       -  -  -");
      }
      return unit_answer;
   }
   /*---(complex)------------------------*/
   o = S_head;
   while (o != NULL) {
      if (c >= a_num)  break;
      ++c;
      o = o->n_mnext;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         x_len = strlen (o->n_title);
         sprintf  (t, "[%.20s]", o->n_title);
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) : %2d%-22.22s   %c  %c  %c", a_num, x_len, t, (o->n_parent == NULL) ? YDLST_OFF : YDLST_ON, o->n_focus, o->n_active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) :  0[]                       -  -  -", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




