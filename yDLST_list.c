/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all lists)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLIST      *S_head      = NULL;   /* head node pointer                   */
static      tLIST      *S_tail      = NULL;   /* tail node pointer                   */
static      tLIST      *S_curr      = NULL;   /* pointer to current list             */
static      int         S_count     =    0;   /* number of lists linked              */
static      int         S_all       =    0;   /* number of lists incl float          */
static      int         S_seq       =    0;   /* number of sequencing lists          */

static      char      (*S_listwipe)      (void *a_data) = NULL;



/*====================------------------------------------====================*/
/*===----                    cleansing and cleaning                    ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSE_________o () { return; }

char
ydlst_list__wipe        (tLIST *a_list)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_INPT   yLOG_snote   ("null pointer");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(master)-------------------------*/
   DEBUG_INPT   yLOG_snote   ("master");
   a_list->l_title   = NULL;
   a_list->l_data    = NULL;
   /*---(list of lists)--------*/
   DEBUG_INPT   yLOG_snote   ("list-of-lists");
   a_list->l_linked  = YDLST_FLOATER;
   a_list->l_mprev   = NULL;
   a_list->l_mnext   = NULL;
   /*---(list of lines)--------*/
   DEBUG_INPT   yLOG_snote   ("list-of-lines");
   a_list->l_nhead   = NULL;
   a_list->l_ntail   = NULL;
   a_list->l_ncount  =    0;
   /*---(comes before)---------*/
   DEBUG_INPT   yLOG_snote   ("preds");
   a_list->l_phead   = NULL;
   a_list->l_ptail   = NULL;
   a_list->l_pcount  =    0;
   /*---(comes after)----------*/
   DEBUG_INPT   yLOG_snote   ("succs");
   a_list->l_shead   = NULL;
   a_list->l_stail   = NULL;
   a_list->l_scount  =    0;
   /*---(complete)-------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char*
ydlst_list__memory       (tLIST *a_list)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_list == NULL)  return rce;
   /*---(header)-------------------------*/
   yENV_check_beg    ();
   /*---(master)-------------------------*/
   yENV_check_ptr    (a_list->l_title);
   yENV_check_ptr    (a_list->l_data);
   yENV_check_spacer ();
   /*---(list of lists)--------*/
   yENV_check_char   (a_list->l_linked);
   yENV_check_ptr    (a_list->l_mprev);
   yENV_check_ptr    (a_list->l_mnext);
   yENV_check_spacer ();
   /*---(list of lines)--------*/
   yENV_check_ptr    (a_list->l_nhead);
   yENV_check_ptr    (a_list->l_ntail);
   yENV_check_num    (a_list->l_ncount);
   yENV_check_spacer ();
   /*---(comes before)---------*/
   yENV_check_ptr    (a_list->l_phead);
   yENV_check_ptr    (a_list->l_ptail);
   yENV_check_num    (a_list->l_pcount);
   yENV_check_spacer ();
   /*---(comes after)----------*/
   yENV_check_ptr    (a_list->l_shead);
   yENV_check_ptr    (a_list->l_stail);
   yENV_check_num    (a_list->l_scount);
   yENV_check_end    ();
   /*---(complete)-----------------------*/
   return yENV_check ();
}

char
ydlst_list__rando        (tLIST *a_list)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(defense)------------------------*/
   --rce;  if (a_list == NULL)  return rce;
   /*---(master)-------------------------*/
   a_list->l_title       = 0x01;
   a_list->l_data        = 0x02;
   /*---(list of lists)--------*/
   a_list->l_linked      =  'a';
   a_list->l_mprev       = 0x03;
   a_list->l_mnext       = 0x04;
   /*---(list of lines)--------*/
   a_list->l_nhead       = 0x05;
   a_list->l_ntail       = 0x06;
   a_list->l_ncount      = 0x07;
   /*---(comes before)---------*/
   a_list->l_phead       = 0x05;
   a_list->l_ptail       = 0x06;
   a_list->l_pcount      = 0x07;
   /*---(comes after)----------*/
   a_list->l_shead       = 0x05;
   a_list->l_stail       = 0x06;
   a_list->l_scount      = 0x07;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char ydlst_list__new   (tLIST **r_new) { return yENV_new  ("list", sizeof (tLIST), r_new, NULL, '-', ydlst_list__wipe); }
char ydlst_list__force (tLIST **r_new) { return yENV_new  ("list", sizeof (tLIST), r_new, NULL, 'y', ydlst_list__wipe); }
char ydlst_list__free  (tLIST **b_old) { return yENV_free ("list", b_old, NULL); }



/*====================------------------------------------====================*/
/*===----                     hooking and unhooking                    ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
ydlst_list__hook        (tLIST *a_list)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_INPT   yLOG_snote   ("null pointer");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check for floater)--------------*/
   if (a_list->l_linked == YDLST_FLOATER) {
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(add to list)--------------------*/
   if (S_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("add first");
      S_head           = a_list;
      S_tail           = a_list;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to end");
      a_list->l_mprev  = S_tail;
      S_tail->l_mnext  = a_list;
      S_tail           = a_list;
   }
   /*---(update count)-------------------*/
   ++S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(done)---------------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
ydlst_list__unhook      (tLIST *a_list)
{
   /*---(lcoals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_INPT   yLOG_snote   ("null pointer");
      DEBUG_PROG   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(check for floater)--------------*/
   if (a_list->l_linked == YDLST_FLOATER) {
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (a_list->l_mnext != NULL)  a_list->l_mnext->l_mprev = a_list->l_mprev;
   else                          S_tail                   = a_list->l_mprev;
   if (a_list->l_mprev != NULL)  a_list->l_mprev->l_mnext = a_list->l_mnext;
   else                          S_head                   = a_list->l_mnext;
   /*---(update count)-------------------*/
   --S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(done)---------------------------*/
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 1;
}

/*> char                                                                              <* 
 *> ydlst_list__new          (char a_link, tLIST **a_new)                             <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    int         rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    int         x_tries     =    0;                                                <* 
 *>    tLIST      *x_new       = NULL;                                                <* 
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
 *>       x_new = (tLIST *) malloc (sizeof (tLIST));                                  <* 
 *>       if (x_tries > 3)   break;                                                   <* 
 *>    }                                                                              <* 
 *>    DEBUG_YDLST   yLOG_sint    (x_tries);                                          <* 
 *>    DEBUG_YDLST   yLOG_spoint  (x_new);                                            <* 
 *>    --rce;  if (x_new == NULL) {                                                   <* 
 *>       DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(wipe)---------------------------+/                                       <* 
 *>    ydlst_list__wipe (x_new);                                                      <* 
 *>    x_new->l_linked = a_link;                                                      <* 
 *>    /+---(save return)--------------------+/                                       <* 
 *>    *a_new = x_new;                                                                <* 
 *>    /+---(check for floater)--------------+/                                       <* 
 *>    if (a_link == YDLST_FLOATER) {                                                 <* 
 *>       DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);                                   <* 
 *>       return 0;                                                                   <* 
 *>    }                                                                              <* 
 *>    /+---(add to list)--------------------+/                                       <* 
 *>    if (S_head == NULL) {                                                          <* 
 *>       DEBUG_YDLST  yLOG_snote   ("add first");                                    <* 
 *>       S_head         = x_new;                                                     <* 
 *>       S_tail         = x_new;                                                     <* 
 *>    } else {                                                                       <* 
 *>       DEBUG_YDLST  yLOG_snote   ("append to end");                                <* 
 *>       x_new->l_mprev  = S_tail;                                                   <* 
 *>       S_tail->l_mnext = x_new;                                                    <* 
 *>       S_tail         = x_new;                                                     <* 
 *>    }                                                                              <* 
 *>    /+---(update count)-------------------+/                                       <* 
 *>    ++S_count;                                                                     <* 
 *>    DEBUG_YDLST  yLOG_sint    (S_count);                                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> ydlst_list_free         (tLIST **a_old)                                           <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    int         rce         =  -10;                                                <* 
 *>    int         rc          =    0;                                                <* 
 *>    tLIST      *x_old       = NULL;                                                <* 
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
 *>    if (x_old->l_mnext != NULL)  x_old->l_mnext->l_mprev = x_old->l_mprev;         <* 
 *>    else                        S_tail                = x_old->l_mprev;            <* 
 *>    if (x_old->l_mprev != NULL)  x_old->l_mprev->l_mnext = x_old->l_mnext;         <* 
 *>    else                        S_head                = x_old->l_mnext;            <* 
 *>    /+---(free title)---------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_spoint  (x_old->l_title);                                    <* 
 *>    if (x_old->l_title != NULL)  free (x_old->l_title);                            <* 
 *>    x_old->l_title == NULL;                                                        <* 
 *>    /+---(free data)----------------------+/                                       <* 
 *>    DEBUG_YDLST  yLOG_spoint  (x_old->l_data);                                     <* 
 *>    if (x_old->l_data  != NULL)  free (x_old->l_data);                             <* 
 *>    x_old->l_data = NULL;                                                          <* 
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
/*===----                   creation and destruction                   ----===*/
/*====================------------------------------------====================*/
static void  o___EXISTANCE_______o () { return; }

char
ydlst_list_create       (char *a_title, void *a_data, tLIST **b_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tLIST      *x_new       = NULL;
   char        x_linked    =  '-';
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (b_list != NULL)  *b_list = NULL;
   /*---(find list)----------------------*/
   rc = yDLST_list_by_name (a_title, b_list, NULL, NULL);
   DEBUG_YDLST  yLOG_value   ("existing"  , rc);
   --rce;  if (rc >= 0) {
      DEBUG_YDLST   yLOG_note    ("list already exists");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("a_title"   , a_title);
   l = strlen (a_title);
   DEBUG_YDLST  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_point   ("a_data"    , a_data);
   /*---(create)-------------------------*/
   rc = ydlst_list__new (&x_new);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update all)---------------------*/
   ++S_all;
   DEBUG_YDLST  yLOG_value   ("S_all"     , S_all);
   /*---(populate)-----------------------*/
   x_new->l_title = strdup (a_title);
   x_new->l_data  = a_data;
   /*---(handle linked)------------------*/
   if (strncmp (a_title, "SEQ_", 4) == 0)  x_new->l_linked = x_linked = YDLST_FLOATER;
   else                                    x_new->l_linked = x_linked = YDLST_LINKED;
   DEBUG_YDLST  yLOG_char    ("x_linked"  , x_linked);
   --rce;  if (x_linked == YDLST_LINKED) {
      /*---(hook to master list)---------*/
      rc = ydlst_list__hook (x_new);
      DEBUG_YDLST  yLOG_value   ("hook"      , rc);
      if (rc < 0) {
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(make current)----------------*/
      S_curr       = x_new;
      DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
      /*---(sequence)--------------------*/
      yDLST_seq_after  ("SEQ_ALPHA");
      yDLST_seq_before ("SEQ_OMEGA");
   }
   /*---(add sequencing)-----------------*/
   else {
      ++S_seq;
   }
   DEBUG_YDLST  yLOG_value   ("S_seq"     , S_seq);
   /*---(save-back)----------------------*/
   if (b_list != NULL)  *b_list = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char yDLST_list_create (char *a_title, void *a_data) { return ydlst_list_create (a_title, a_data, NULL); }

char
ydlst_list_destroy      (char *a_title, tLIST **b_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   char        x_linked    =  '-';
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   rc = yDLST_list_by_name (a_title, NULL, NULL, NULL);
   DEBUG_YDLST  yLOG_value   ("existing"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_note    ("list does not exist");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   DEBUG_YDLST  yLOG_info    ("l_title"   , S_curr->l_title);
   /*---(clear the lines)-------------*/
   rc = ydlst_line_purge (S_curr);
   DEBUG_YDLST  yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook from master)----------*/
   x_linked = S_curr->l_linked;
   DEBUG_YDLST  yLOG_char    ("x_linked"  , x_linked);
   --rce;  if (x_linked == YDLST_LINKED) {
      rc = ydlst_list__unhook (S_curr);
      DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
      if (rc < 0) {
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(update all)---------------------*/
   --S_all;
   DEBUG_YDLST  yLOG_value   ("S_all"     , S_all);
   /*---(free title)---------------------*/
   DEBUG_YDLST  yLOG_point   ("l_title"   , S_curr->l_title);
   if (S_curr->l_title != NULL) {
      free (S_curr->l_title);
      S_curr->l_title = NULL;
      DEBUG_YDLST  yLOG_point   ("l_title"   , S_curr->l_title);
   }
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_point  ("l_data"     , S_curr->l_data);
   DEBUG_YDLST  yLOG_point   ("S_listwipe", S_listwipe);
   --rce;  if (S_curr->l_data != NULL && S_listwipe != NULL) {
      rc = S_listwipe (S_curr->l_data);
      DEBUG_YDLST  yLOG_value   ("listwipe"  , rc);
      if (rc < 0) {
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   S_curr->l_data = NULL;
   DEBUG_YDLST  yLOG_point  ("l_data"     , S_curr->l_data);
   /*---(free)---------------------------*/
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   rc = ydlst_list__free (&S_curr);
   DEBUG_YDLST  yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset current)------------------*/
   if (x_linked == YDLST_LINKED) {
      S_curr = S_head;
      DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   }
   /*---(save-back)----------------------*/
   if (b_list != NULL)  *b_list = NULL;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char yDLST_list_destroy (char *a_title) { return ydlst_list_destroy (a_title, NULL); }



/*====================------------------------------------====================*/
/*===----                      finding a list                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yDLST_list_count     (void) { return S_count; }

char
ydlst_list__line        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         c           =    0;
   tLINE      *x_line      = NULL;
   /*---(check if already ok)------------*/
   x_line = yDLST_line_current ();
   DEBUG_YDLST  yLOG_spoint  (x_line);
   if (x_line != NULL && x_line->n_parent == S_curr) {
      DEBUG_YDLST  yLOG_snote   ("already safe line");
      return 0;
   }
   /*---(force)--------------------------*/
   DEBUG_YDLST  yLOG_spoint  (S_curr->l_nhead);
   yDLST_line_restore (S_curr->l_nhead);
   /*---(show)---------------------------*/
   x_line = yDLST_line_current ();
   if (x_line != NULL) {
      DEBUG_YDLST  yLOG_snote   (x_line->n_title);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ydlst_list_by_default   (void **r_list, void ** r_data, char d_entry [LEN_RECD])
{
   if (r_list  != NULL)   *r_list = NULL;
   if (r_data  != NULL)   *r_data = NULL;
   if (d_entry != NULL)  ystrlcpy (d_entry, ydlst_list__entry (NULL), LEN_RECD);
   return 0;
}

char
ydlst_list_save_back    (void *a_list, void *a_data, void **r_list, void **r_data, char d_entry [LEN_RECD])
{
   S_curr  = (tLIST *) a_list;
   ydlst_list__line ();
   if (r_list  != NULL)  *r_list  = a_list;
   if (r_data  != NULL)  *r_data  = a_data;
   if (d_entry != NULL)  ystrlcpy (d_entry, ydlst_list__entry (a_list), LEN_RECD);
   return 0;
}

char       /*--> find a list using sequential pos ----------------------------*/
yDLST_list_by_index     (int n, void **r_list, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_list_by_default (r_list, r_data, d_entry);
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
   /*---(move)---------------------------*/
   x_list = S_head;
   while (x_list != NULL) {
      if (c >= n)  break;
      x_list = x_list->l_mnext;
      ++c;
   }
   /*---(check)--------------------------*/
   DEBUG_YDLST  yLOG_sint    (c);
   --rce;  if (c != n) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   ydlst_list_save_back (x_list, x_list->l_data, r_list, r_data, d_entry);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_list_by_cursor    (char a_move, void **r_list, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   DEBUG_YDLST  yLOG_spoint  (r_data);
   /*---(defaults)-----------------------*/
   ydlst_list_by_default (r_list, r_data, d_entry);
   x_curr = S_curr;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr (YDLST_DREL, a_move) != NULL) {
         S_curr = x_curr;
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(bounce types)----------------*/
      x_curr = S_head;
      DEBUG_DATA   yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(switch)-------------------------*/
   DEBUG_YDLST  yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_curr = S_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_curr = x_curr->l_mprev;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      x_curr = x_curr->l_mnext;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_curr = S_tail;
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV)   x_curr = S_head;
      if (a_move == YDLST_NEXT)   x_curr = S_tail;
      /*---(no bounce)-------------------*/
      if (x_curr == NULL) {
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
   ydlst_list_save_back (x_curr, x_curr->l_data, r_list, r_data, d_entry);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char       /*--> find a list using its title ---------------------------------*/
yDLST_list_by_name      (char *a_title, void **r_list, void **r_data, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_list_by_default (r_list, r_data, d_entry);
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
   /*---(search)-------------------------*/
   x_list = S_head;
   while (x_list != NULL) {
      if (x_list->l_title != NULL) {
         if (strcmp (x_list->l_title, a_title) == 0) break;
      }
      x_list = x_list->l_mnext;
   }
   DEBUG_YDLST  yLOG_spoint  (S_curr);
   /*---(trouble)------------------------*/
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   ydlst_list_save_back (x_list, x_list->l_data, r_list, r_data, d_entry);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_list_by_ptr       (void *a_list, char d_entry [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   ydlst_list_by_default (NULL  , NULL  , d_entry);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(search)-------------------------*/
   x_list = S_head;
   while (x_list != NULL) {
      if (x_list == a_list)   break;
      x_list = x_list->l_mnext;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   ydlst_list_save_back (x_list, NULL, NULL, NULL, d_entry);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char       /*----: clear all links from a list -------------------------------*/
ydlst_list_purge        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(walk through attached links)----*/
   S_curr = S_head;
   DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   while (S_curr != NULL) {
      DEBUG_YDLST  yLOG_info    ("->l_title" , S_curr->l_title);
      rc = yDLST_line_clearlist ();
      DEBUG_YDLST  yLOG_value   ("clearlist" , rc);
      rc = yDLST_list_destroy (S_curr->l_title);
      DEBUG_YDLST  yLOG_value   ("destroy"   , rc);
      S_curr  = S_head;
      DEBUG_YDLST  yLOG_point   ("S_curr"    , S_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ydlst_list_config       (char f_listwipe (void *))
{
   S_listwipe = f_listwipe;
   return 1;
}

char
ydlst_list_init         (char f_listwipe (void *))
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   S_head     = NULL;
   S_tail     = NULL;
   S_curr     = NULL;
   S_count    =    0;
   S_all      =    0;
   S_seq      =    0;
   ydlst_list_config (f_listwipe);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ydlst_list_wrap         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   ydlst_list_purge ();
   /*---(initialize)---------------------*/
   S_head     = NULL;
   S_tail     = NULL;
   S_curr     = NULL;
   S_count    =    0;
   S_all      =    0;
   S_seq      =    0;
   ydlst_list_config (NULL);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

void*  yDLST_list_current   (void)          { return S_curr; }
char   yDLST_list_restore   (void *a_list)  { S_curr = (tLIST*) a_list;  return 0; }



/*====================------------------------------------====================*/
/*===----                        reporting                             ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }


/*   123456789-12345   -c - ´  åmemberæ      1000     0     0 -    -1  -     0     0 -     0   - - - -       */

/*   -----group----- lin t ------proc----- ---desc-----------------------  I T R user------ --uid dur-- ---est  beg---------  rpid-- y rc-- S lower------- upper------- R  t c d n  end--------- dur-------  ---run-------------------------------------------- */
/*   my_group······· ··2 d normal········· unit_daemon···················  c - ´ member···· ·1000 0s··· ·····0  y ········21  ·····- y ···- - - ·········- - ·········- -  - - - -  y ······2050 ······2029  /usr/local/bin/unit_daemon --long················· */
/*   ´·············· ··- - ´·············· ´·····························  - - - ´········· ····- ´···· ·····-  - ·········-  ·····- - ···- - - ·········- - ·········- -  - - - -  - ·········- ·········-  ´·········´·········´·········´·········´········· */

/*>                                                                                   <* 
 *> struct  cLIST {   /+   all list members begin with "l_"   +/                      <* 
 *>    /+---(master)---------------+/                                                 <* 
 *>    char       *l_title;                /+ name of list                   +/       <* 
 *>    void       *l_data;                 /+ data payload                   +/       <* 
 *>    /+---(lists)----------------+/                                                 <* 
 *>    char        l_linked;               /+ tied to master list            +/       <* 
 *>    tLIST      *l_mprev;                /+ master list prev               +/       <* 
 *>    tLIST      *l_mnext;                /+ master list next               +/       <* 
 *>    /+---(lines)----------------+/                                                 <* 
 *>    tLINE      *l_nhead;                /+ child line head                +/       <* 
 *>    tLINE      *l_ntail;                /+ child line tail                +/       <* 
 *>    int         l_ncount;               /+ child line count               +/       <* 
 *>    /+---(comes before)---------+/                                                 <* 
 *>    tSEQ       *l_phead;                /+ pred head                      +/       <* 
 *>    tSEQ       *l_ptail;                /+ pred tail                      +/       <* 
 *>    int         l_pcount;               /+ pred count                     +/       <* 
 *>    /+---(comes after)----------+/                                                 <* 
 *>    tSEQ       *l_shead;                /+ succ head                      +/       <* 
 *>    tSEQ       *l_stail;                /+ succ tail                      +/       <* 
 *>    int         l_scount;               /+ succ count                     +/       <* 
 *>    /+---(done)-----------------+/                                                 <* 
 *> };                                                                                <* 
 *>                                                                                   <*/

/*   ---title------- ---data---  l ---mprev------- ---mnext-------  ---nhead------- ---ntail------- cnt  ---phead------- ---ptail------- cnt  ---shead------- ---stail------- cnt  */
/*   ´·············· ´·········  - ´·············· ´··············  ´·············· ´·············· ··-  ´·············· ´·············· ··-  ´·············· ´·············· ··-  */

char*
ydlst_list__entry       (tLIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND]  = "";
   /*---(short-cuts)---------------------*/
   if (a_list == NULL) return "´·············· -···········  - ´·············· ´··············  ´·············· ´·············· ··-  ´·············· ´·············· ··-  ´·············· ´·············· ··-  Ï";
   if (a_list == 0x01) return "---title------- ---data-----  l ---full-mprev-- ---mnext-------  ---line-nhead-- ---ntail------- cnt  ---pred-phead-- ---ptail------- cnt  ---succ-shead-- ---stail------- cnt  Ï";
   /*---(prepare)------------------------*/
   strcpy (unit_answer, "");
   /*---(master)-------------------------*/
   ystrlcat (unit_answer, ystrlpadquick  (a_list->l_title         , '<', '.', 15), LEN_RECD);
   ystrlcat (unit_answer, " ", LEN_RECD);
   ystrlcat (unit_answer, ystrl4quick    ((double) ((int) (a_list->l_data)), '<', 'x', 0, '-', '.', '-', '-', 12), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   /*---(main list)----------------------*/
   sprintf (t, "%c ", a_list->l_linked);
   ystrlcat (unit_answer, t  , LEN_RECD);
   if (a_list->l_mprev != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_mprev->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   if (a_list->l_mnext != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_mnext->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, " ", LEN_RECD);
   /*---(lines)--------------------------*/
   if (a_list->l_nhead != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_nhead->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_ntail->n_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, ystrl4quick ((double) a_list->l_ncount, '>', ',', 0, '-', '.', '-', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   /*---(preds)--------------------------*/
   if (a_list->l_phead != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_phead->q_pred->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_ptail->q_pred->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, ystrl4quick ((double) a_list->l_pcount, '>', ',', 0, '-', '.', '-', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   /*---(succs)--------------------------*/
   if (a_list->l_shead != NULL) {
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_shead->q_succ->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
      ystrlcat (unit_answer, ystrlpadquick  (a_list->l_stail->q_succ->l_title, '<', '.', 15), LEN_RECD);
      ystrlcat (unit_answer, " ", LEN_RECD);
   } else {
      ystrlcat (unit_answer, "´·············· ´·············· ", LEN_RECD);
   }
   ystrlcat (unit_answer, ystrl4quick ((double) a_list->l_scount, '>', ',', 0, '-', '.', '-', '-',  3), LEN_RECD);
   ystrlcat (unit_answer, "  ", LEN_RECD);
   /*---(final)--------------------------*/
   ystrlcat (unit_answer, "Ï", LEN_RECD);
   /*---(complete)-----------------------*/
   return unit_answer;
}

char*
ydlst_list_entry        (char a_dir)
{
   char        rc          =    0;
   tLIST      *x_curr      = NULL;
   if (a_dir == 'T')  x_curr = 0x01;
   else               rc = yDLST_list_by_cursor (a_dir, &x_curr, NULL, NULL);
   if (rc < 0)  x_curr = NULL;
   return ydlst_list__entry (x_curr);
}

char*
ydlst_list_audit        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLIST      *o           = NULL;
   o = S_tail; while (o != NULL) { ++x_back; o = o->l_mprev; }
   o = S_head; while (o != NULL) { ++x_fore; o = o->l_mnext; }
   snprintf (unit_answer, LEN_RECD, "list audit ::  %3dA  %3dQ  %3dc  %3df  %3db", S_all, S_seq, S_count, x_fore, x_back);
   o = S_head;
   ystrlcat (unit_answer, "  å ", LEN_RECD);
   while (o != NULL) {
      ystrlcat (unit_answer, o->l_title, LEN_RECD);
      ystrlcat (unit_answer, " "       , LEN_RECD);
      o = o->l_mnext;
   }
   ystrlcat (unit_answer, "æ", LEN_RECD);
   return unit_answer;
}


/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char      unit_answer [LEN_RECD];

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ydlst_list__unit        (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLIST      *o           = NULL;
   int         c           =    0;
   char        t           [LEN_HUND]  = "[]";
   char        s           [LEN_HUND]  = "[]";
   char        r           [LEN_HUND]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "LIST unit        : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      o = S_tail; while (o != NULL) { ++x_back; o = o->l_mprev; }
      o = S_head; while (o != NULL) { ++x_fore; o = o->l_mnext; }
      snprintf (unit_answer, LEN_RECD, "LIST count       : %3dc  %3df  %3db", S_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = S_curr;
      if (o != NULL) {
         x_len = strlen (o->l_title);
         sprintf  (t, "[%.20s]", o->l_title);
         snprintf (unit_answer, LEN_RECD, "LIST current     : %2d%-22.22s %3d", x_len, t, o->l_ncount);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST current     :  0[]                       0");
      }
      return unit_answer;
   }
   /*---(complex)------------------------*/
   o = S_head;
   while (o != NULL) {
      if (c >= a_num)  break;
      ++c;
      o = o->l_mnext;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         x_len = strlen (o->l_title);
         sprintf  (t, "[%.20s]", o->l_title);
         if (o->l_nhead != NULL) {
            sprintf  (s, "[%.20s]", o->l_nhead->n_title);
            sprintf  (r, "[%.20s]", o->l_ntail->n_title);
         }
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) : %2d%-22.22s %3d  %-22.22s  %s", a_num, x_len, t, o->l_ncount, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) :  0[]                       0  []                      []", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




