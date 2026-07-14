/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tSEQ       *s_head      = NULL;
static      tSEQ       *s_tail      = NULL;
static      tSEQ       *s_curr      = NULL;
static      int         s_count     =    0;

static      tLIST      *s_alpha     = NULL;
static      tLIST      *s_omega     = NULL;


static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                      clearing and wiping                     ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSE_________o () { return; }

char
ydlst_seq__wipe          (tSEQ *a_seq)
{
   /*---(defense)--------------*/
   if (a_seq == NULL)  return -1;
   /*---(seq)------------------*/
   a_seq->q_mprev  = NULL;
   a_seq->q_mnext  = NULL;
   /*---(master)---------------*/
   a_seq->q_pred    = NULL;
   a_seq->q_pprev  = NULL;
   a_seq->q_pnext  = NULL;
   a_seq->q_succ    = NULL;
   a_seq->q_sprev  = NULL;
   a_seq->q_snext  = NULL;
   /*---(complete)-------------*/
   return 1;
}

char*
ydlst_seq__memory       (tSEQ *a_seq)
{
   strlcpy (s_print, "[__.___.___]", LEN_RECD);
   if (a_seq->q_mprev  != NULL)  s_print [ 1] = 'X';
   if (a_seq->q_mnext  != NULL)  s_print [ 2] = 'X';
   if (a_seq->q_pred    != NULL)  s_print [ 4] = 'X';
   if (a_seq->q_pprev  != NULL)  s_print [ 5] = 'X';
   if (a_seq->q_pnext  != NULL)  s_print [ 6] = 'X';
   if (a_seq->q_succ    != NULL)  s_print [ 8] = 'X';
   if (a_seq->q_sprev  != NULL)  s_print [ 9] = 'X';
   if (a_seq->q_snext  != NULL)  s_print [10] = 'X';
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                    allocating and freeing                    ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ydlst_seq__new          (tSEQ **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tSEQ       *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YDLST   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST   yLOG_spoint  (*a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_YDLST   yLOG_snote   ("already set");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   *a_new = NULL;
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tSEQ *) malloc (sizeof (tSEQ));
      if (x_tries > 3)   break;
   }
   DEBUG_YDLST   yLOG_sint    (x_tries);
   DEBUG_YDLST   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   ydlst_seq__wipe (x_new);
   /*---(save return)--------------------*/
   *a_new = x_new;
   /*---(add to list)--------------------*/
   if (s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("add first");
      s_head         = x_new;
      s_tail         = x_new;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to end");
      x_new->q_mprev  = s_tail;
      s_tail->q_mnext = x_new;
      s_tail         = x_new;
   }
   /*---(update count)-------------------*/
   ++s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq__free         (tSEQ **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tSEQ       *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YDLST   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_YDLST   yLOG_snote   ("never set");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(simplify)-----------------------*/
   x_old = *a_old;
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (x_old->q_mnext != NULL)  x_old->q_mnext->q_mprev = x_old->q_mprev;
   else                        s_tail                = x_old->q_mprev;
   if (x_old->q_mprev != NULL)  x_old->q_mprev->q_mnext = x_old->q_mnext;
   else                        s_head                = x_old->q_mnext;
   /*---(clear and return)---------------*/
   free (x_old);
   *a_old = NULL;
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     hooking and unhooking                    ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
ydlst_seq__confirm      (tLIST *a_pred, tLIST *a_succ, tSEQ **a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_seq       = NULL;
   /*---(prepare)------------------------*/
   x_seq = a_pred->l_shead;
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->q_succ, x_seq->q_succ->l_title);
      if (x_seq->q_succ == a_succ) {
         if (a_seq != NULL)  *a_seq = x_seq;
         DEBUG_YDLST  yLOG_snote   ("FOUN");
         return 1;
      }
      x_seq = x_seq->q_snext;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_snote   ("nothing");
   return 0;
}

char
ydlst_seq__hook         (tLIST *a_pred, tLIST *a_succ, tSEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_pred);
   --rce;  if (a_pred  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (a_seq);
   --rce;  if (a_seq  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for existing)----------*/
   ydlst_seq__confirm (a_pred, a_succ, &x_seq);
   DEBUG_YDLST  yLOG_spoint  (x_seq);
   --rce;  if (x_seq != NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(into successsor)-------------*/
   a_seq->q_succ       = a_succ;
   a_seq->q_snext     = NULL;
   a_seq->q_sprev     = NULL;
   if (a_pred->l_shead == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first on pred");
      a_pred->l_shead         = a_seq;
      a_pred->l_stail         = a_seq;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to pred");
      a_seq->q_sprev          = a_pred->l_stail;
      a_pred->l_stail->q_snext = a_seq;
      a_pred->l_stail         = a_seq;
   }
   /*---(update count)-------------------*/
   ++a_pred->l_scount;
   DEBUG_YDLST  yLOG_sint    (a_pred->l_scount);
   /*---(into predecessor)------------*/
   a_seq->q_pred       = a_pred;
   a_seq->q_pprev     = NULL;
   a_seq->q_pnext     = NULL;
   if (a_succ->l_phead == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first on pred");
      a_succ->l_phead         = a_seq;
      a_succ->l_ptail         = a_seq;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to pred");
      a_seq->q_pprev          = a_succ->l_ptail;
      a_succ->l_ptail->q_pnext = a_seq;
      a_succ->l_ptail         = a_seq;
   }
   /*---(update count)-------------------*/
   ++a_succ->l_pcount;
   DEBUG_YDLST  yLOG_sint    (a_succ->l_pcount);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq__unhook       (tSEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tLIST      *x_pred      = NULL;
   tLIST      *x_succ      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_seq);
   --rce;  if (a_seq  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(predecessor)--------------------*/
   x_pred = a_seq->q_pred;
   DEBUG_YDLST  yLOG_spoint  (x_pred);
   --rce;  if (x_pred  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(successor)----------------------*/
   x_succ = a_seq->q_succ;
   DEBUG_YDLST  yLOG_spoint  (x_succ);
   --rce;  if (x_succ  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove from predecessor)--------*/
   DEBUG_YDLST  yLOG_snote   ("remove from pred");
   if (a_seq->q_pnext != NULL)  a_seq->q_pnext->q_pprev = a_seq->q_pprev;
   else                        x_succ->l_ptail        = a_seq->q_pprev;
   if (a_seq->q_pprev != NULL)  a_seq->q_pprev->q_pnext = a_seq->q_pnext;
   else                        x_succ->l_phead        = a_seq->q_pnext;
   /*---(remove from successr)-----------*/
   DEBUG_YDLST  yLOG_snote   ("remove from succ");
   if (a_seq->q_snext != NULL)  a_seq->q_snext->q_sprev = a_seq->q_sprev;
   else                        x_pred->l_stail        = a_seq->q_sprev;
   if (a_seq->q_sprev != NULL)  a_seq->q_sprev->q_snext = a_seq->q_snext;
   else                        x_pred->l_shead        = a_seq->q_snext;
   /*---(update count)-------------------*/
   --x_pred->l_scount;
   DEBUG_YDLST  yLOG_sint    (x_pred->l_scount);
   --x_succ->l_pcount;
   DEBUG_YDLST  yLOG_sint    (x_succ->l_pcount);
   /*---(ground predecessor)-------------*/
   a_seq->q_pred       = NULL;
   a_seq->q_pnext     = NULL;
   a_seq->q_pprev     = NULL;
   /*---(ground successor)---------------*/
   a_seq->q_succ       = NULL;
   a_seq->q_snext     = NULL;
   a_seq->q_sprev     = NULL;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq__unhook_ends  (tLIST *a_pred, tLIST *a_succ)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_point   ("a_pred"    , a_pred);
   --rce;  if (a_pred  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_pred->l_title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_succ->l_title);
   /*---(prepare)------------------------*/
   x_seq = a_pred->l_shead;
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->q_succ, x_seq->q_succ->l_title);
      if (x_seq->q_succ == a_succ) {
         ydlst_seq__unhook (x_seq);
         DEBUG_YDLST   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      x_seq = x_seq->q_snext;
   }
   /*---(complete)-----------------------*/
   --rce;
   DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                    alpha and omega lists                     ----===*/
/*====================------------------------------------====================*/
static void  o___ENDPOINTS_______o () { return; }

char
ydlst_seq__alpha  (tLIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *o           = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_list"    , a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_point   ("s_head"    , s_alpha->l_shead);
   o = s_alpha->l_shead;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->q_succ, o->q_succ->l_title);
      if (o->q_succ == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (o);
         ydlst_seq__free   (&o);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      o = o->q_snext;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_seq__omega  (tLIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *o           = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_list"    , a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_point   ("l_phead"    , s_omega->l_phead);
   o = s_omega->l_phead;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->q_pred, o->q_pred->l_title);
      if (o->q_pred == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (o);
         ydlst_seq__free   (&o);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      o = o->q_pnext;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_seq__cycle  (int a_lvl, tLIST *a_curr, tLIST *a_look)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *o           = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   DEBUG_YDLST  yLOG_value   ("a_lvl"     , a_lvl);
   /*---(current)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(target)-------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_look"    , a_look);
   --rce;  if (a_look == NULL) {
      DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check match)--------------------*/
   if (a_curr == a_look) {
      DEBUG_YDLST   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_point   ("l_phead"    , a_curr->l_phead);
   o = a_curr->l_phead;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->q_pred, o->q_pred->l_title);
      if (o->q_pred == a_look) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      } else {
         rc = ydlst_seq__cycle (a_lvl + 1, o->q_pred, a_look);
         if (rc > 0)  return rc;
      }
      o = o->q_pnext;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    searching and finding                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int
yDLST_seq_count      (char a_scope)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   DEBUG_YDLST  yLOG_schar   (a_scope);
   /*---(global)-------------------------*/
   if (a_scope != 0 && strchr ("Aa*", a_scope) != NULL) {
      DEBUG_YDLST   yLOG_snote   ("all sequence nodes");
      DEBUG_YDLST  yLOG_sint    (s_count);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return s_count;
   }
   /*---(get list)-----------------------*/
   x_list = yDLST_list_current ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   /*---(predecessors)-------------------*/
   if (a_scope != 0 && strchr ("[<" , a_scope) != NULL) {
      DEBUG_YDLST   yLOG_snote   ("predecessors");
      DEBUG_YDLST  yLOG_sint    (x_list->l_pcount);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return x_list->l_pcount;
   }
   /*---(successors)---------------------*/
   if (a_scope != 0 && strchr (">]" , a_scope) != NULL) {
      DEBUG_YDLST   yLOG_snote   ("successors");
      DEBUG_YDLST  yLOG_sint    (x_list->l_scount);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return x_list->l_scount;
   }
   /*---(return)-------------------------*/
   DEBUG_YDLST   yLOG_snote   ("scope not understood");
   --rce;
   DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

int yDLST_alpha_count    (void) { return s_alpha->l_scount; }
int yDLST_omega_count    (void) { return s_omega->l_pcount; }

char       /*--> find a list using sequential pos ----------------------------*/
yDLST_seq_by_index      (char a_scope, int n, void **a_seq, void **a_list, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_scope     =  '-';
   int         c           =    0;
   tLIST      *x_list      = NULL;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_seq  != NULL)  *a_seq  = NULL;
   if (a_list != NULL)  *a_list = NULL;
   if (a_data != NULL)  *a_data = NULL;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_sint    (n);
   DEBUG_YDLST  yLOG_sint    (s_count);
   --rce;  if (n < 0 || n >= s_count) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (s_head);
   --rce;  if (s_head == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check scope)--------------------*/
   DEBUG_YDLST  yLOG_schar   (a_scope);
   --rce;  if (a_scope == 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if      (strchr ("*[]", a_scope) != NULL)  x_scope = '*';
   else if (strchr ("<"  , a_scope) != NULL)  x_scope = '<';
   else if (strchr (">"  , a_scope) != NULL)  x_scope = '>';
   /*---(get list)-----------------------*/
   if (x_scope != '*') {
      x_list = yDLST_list_current ();
      DEBUG_YDLST  yLOG_spoint  (x_list);
      --rce;  if (x_list  == NULL) {
         DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
         return NULL;
      }
      DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   }
   /*---(start)--------------------------*/
   switch (x_scope) {
   case '*' :  x_seq = s_head;            break;
   case '<' :  x_seq = x_list->l_phead;    break;
   case '>' :  x_seq = x_list->l_shead;    break;
   }
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      if (c >= n)  break;
      switch (x_scope) {
      case '*' :  x_seq = x_seq->q_mnext;    break;
      case '<' :  x_seq = x_seq->q_pnext;    break;
      case '>' :  x_seq = x_seq->q_snext;    break;
      }
      ++c;
   }
   /*---(check)--------------------------*/
   DEBUG_YDLST  yLOG_sint    (c);
   --rce;  if (c != n) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_seq);
   --rce;  if (x_seq == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   s_curr  = x_seq;
   if (a_seq  != NULL)  *a_seq  = x_seq;
   switch (a_scope) {
   case '[' : case '<' : case '*' :
      if (a_list != NULL)  *a_list = x_seq->q_pred;
      if (a_data != NULL)  *a_data = x_seq->q_pred->l_data;
      break;
   case ']' : case '>' :
      if (a_list != NULL)  *a_list = x_seq->q_succ;
      if (a_data != NULL)  *a_data = x_seq->q_succ->l_data;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_seq_by_cursor     (char a_scope, char a_move, void **a_curr, void **a_list, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_scope     =  '-';
   tLIST      *x_list      = NULL;
   tSEQ       *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_curr != NULL)  *a_curr = NULL;
   if (a_list != NULL)  *a_list = NULL;
   if (a_data != NULL)  *a_data = NULL;
   x_curr = s_curr;
   /*---(check scope)--------------------*/
   DEBUG_YDLST  yLOG_schar   (a_scope);
   --rce;  if (a_scope == 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce; if (strchr (YDLST_GLOBALS, a_scope) != NULL)  x_scope = YDLST_GLOBAL;
   else if   (a_scope == YDLST_LPRED)                   x_scope = YDLST_LPRED;
   else if   (a_scope == YDLST_LSUCC)                   x_scope = YDLST_LSUCC;
   else {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(get list)-----------------------*/
   --rce;  if (x_scope != YDLST_GLOBAL) {
      x_list = yDLST_list_current ();
      DEBUG_YDLST  yLOG_spoint  (x_list);
      if (x_list  == NULL) {
         DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   }
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   --rce;  if (x_curr == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr (YDLST_DREL, a_move) != NULL) {
         s_curr = x_curr;
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(bounce types)----------------*/
      switch (x_scope) {
      case YDLST_GLOBAL :  x_curr = s_head;            break;
      case YDLST_LPRED  :  x_curr = x_list->l_phead;    break;
      case YDLST_LSUCC  :  x_curr = x_list->l_shead;    break;
      }
      DEBUG_DATA   yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(switch)-------------------------*/
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      switch (x_scope) {
      case YDLST_GLOBAL :  x_curr = s_head;            break;
      case YDLST_LPRED  :  x_curr = x_list->l_phead;    break;
      case YDLST_LSUCC  :  x_curr = x_list->l_shead;    break;
      }
      break;
   case YDLST_PREV : case YDLST_DPREV :
      switch (x_scope) {
      case YDLST_GLOBAL :  x_curr = x_curr->q_mprev;    break;
      case YDLST_LPRED  :  x_curr = x_curr->q_pprev;    break;
      case YDLST_LSUCC  :  x_curr = x_curr->q_sprev;    break;
      }
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      switch (x_scope) {
      case YDLST_GLOBAL :  x_curr = x_curr->q_mnext;    break;
      case YDLST_LPRED  :  x_curr = x_curr->q_pnext;    break;
      case YDLST_LSUCC  :  x_curr = x_curr->q_snext;    break;
      }
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      switch (x_scope) {
      case YDLST_GLOBAL :  x_curr = s_tail;            break;
      case YDLST_LPRED  :  x_curr = x_list->l_ptail;    break;
      case YDLST_LSUCC  :  x_curr = x_list->l_stail;    break;
      }
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV) {
         switch (x_scope) {
         case YDLST_GLOBAL :  x_curr = s_head;            break;
         case YDLST_LPRED  :  x_curr = x_list->l_phead;    break;
         case YDLST_LSUCC  :  x_curr = x_list->l_shead;    break;
         }
      }
      if (a_move == YDLST_NEXT) {
         switch (x_scope) {
         case YDLST_GLOBAL :  x_curr = s_tail;            break;
         case YDLST_LPRED  :  x_curr = x_list->l_ptail;    break;
         case YDLST_LSUCC  :  x_curr = x_list->l_stail;    break;
         }
      }
      /*---(no bounce)-------------------*/
      if (x_curr == NULL) {
         s_curr = x_curr;
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(mark trouble)----------------*/
      DEBUG_DATA   yLOG_snote   ("BOUNCE");
      rc = rce;
      /*---(done)------------------------*/
   }
   /*---(normal result)------------------*/
   s_curr = x_curr;
   /*---(save back)----------------------*/
   if (a_curr  != NULL)  *a_curr  = s_curr;
   if (strchr (YDLST_PREDS, a_scope) != NULL) {
      if (a_list != NULL)  *a_list = s_curr->q_pred;
      if (a_data != NULL)  *a_data = s_curr->q_pred->l_data;
   } else {
      if (a_list != NULL)  *a_list = s_curr->q_succ;
      if (a_data != NULL)  *a_data = s_curr->q_succ->l_data;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yDLST_seq_for_list      (void *a_list, short *r_npred, char r_preds [LEN_FULL], char *r_nsucc, char r_succs [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tSEQ       *x_curr      = NULL;
   short       n           =    0;
   short       c           =    0;
   tLIST      *x_list      = NULL;
   char        x_rptg      [LEN_FULL]  = "";
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_npred != NULL)  *r_npred = 0;
   if (r_preds != NULL)  strcpy (r_preds, "");
   if (r_nsucc != NULL)  *r_nsucc = 0;
   if (r_succs != NULL)  strcpy (r_preds, "");
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_list = (tLIST *)  a_list;
   DEBUG_YDLST  yLOG_snote   (x_list->l_title);
   /*---(preds)--------------------------*/
   strcpy (x_rptg, "");
   n      = x_list->l_pcount;
   x_curr = x_list->l_phead;
   while (x_curr != NULL) {
      if (c != 0)  ystrlcpy (x_rptg, ","   , LEN_FULL);
      ystrlcpy (x_rptg, x_curr->q_pred->l_title, LEN_FULL);
      ++c;
      x_curr = x_curr->q_pnext;
   }
   if (r_npred != NULL)  *r_npred = c;
   if (r_preds != NULL)  ystrlcpy (r_preds, x_rptg, LEN_FULL);
   /*---(succs)--------------------------*/
   strcpy (x_rptg, "");
   n      = x_list->l_scount;
   x_curr = x_list->l_shead;
   while (x_curr != NULL) {
      if (c != 0)  ystrlcpy (x_rptg, ","   , LEN_FULL);
      ystrlcpy (x_rptg, x_curr->q_succ->l_title, LEN_FULL);
      ++c;
      x_curr = x_curr->q_snext;
   }
   if (r_nsucc != NULL)  *r_nsucc = c;
   if (r_succs != NULL)  ystrlcpy (r_succs, x_rptg, LEN_FULL);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*----: prepare a new list for use --------------------------------*/
ydlst_seq__create       (tLIST *a_pred, tLIST *a_succ)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_point   ("a_pred"    , a_pred);
   --rce;  if (a_pred  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_pred->l_title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_succ->l_title);
   /*---(check match)--------------------*/
   --rce;  if (a_pred == a_succ) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   ydlst_seq__new (&x_new);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook)---------------------------*/
   rc = ydlst_seq__hook (a_pred, a_succ, x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha and omega)----------------*/
   /*> if (strcmp (a_pred, "SEQ_ALPHA") != 0) {                                       <* 
    *>    DEBUG_YDLST  yLOG_note    ("adding new one after a named list");            <* 
    *>    rc = ydlst_seq__alpha  (a_succ);                                            <* 
    *>    rc = ydlst_seq__omega  (a_pred);                                            <* 
    *>    yDLST_list_by_ptr  (a_succ, NULL);                                          <* 
    *> }                                                                              <*/
   /*> if (strcmp (a_succ, "SEQ_OMEGA") != 0) {                                       <* 
    *>    DEBUG_YDLST  yLOG_note    ("adding new one before a named list");           <* 
    *>    rc = ydlst_seq__omega  (a_pred);                                            <* 
    *>    yDLST_list_by_ptr  (a_pred, NULL);                                          <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_seq__destroy      (tLIST *a_pred, tLIST *a_succ)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_point   ("a_pred"    , a_pred);
   --rce;  if (a_pred  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_pred->l_title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("l_title"   , a_succ->l_title);
   /*---(check match)--------------------*/
   --rce;  if (a_pred == a_succ) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_seq = a_pred->l_shead;
   /*---(walk)---------------------------*/
   --rce;  while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->q_succ, x_seq->q_succ->l_title);
      if (x_seq->q_succ == a_succ) {
         rc = ydlst_seq__unhook (x_seq);
         DEBUG_YDLST  yLOG_value   ("hook"      , rc);
         if (rc < 0) {
            DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         rc = ydlst_seq__free   (&x_seq);
         DEBUG_YDLST  yLOG_value   ("free"      , rc);
         if (rc < 0) {
            DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_YDLST   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      x_seq = x_seq->q_snext;
   }
   /*---(complete)-----------------------*/
   --rce;
   DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char       /*----: prepare a new list for use --------------------------------*/
yDLST_seq_after         (char *a_before)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_new       = NULL;
   tLIST      *x_list      = NULL;
   tLIST      *x_before    = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_before"  , a_before);
   --rce;  if (a_before  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get list)-----------------------*/
   x_list = yDLST_list_current ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_note    (x_list->l_title);
   /*---(check for alpha)----------------*/
   if (strcmp (a_before, "SEQ_ALPHA") == 0) {
      x_before = s_alpha;
   }
   /*---(find predecessor)---------------*/
   else {
      /*---(find)------------------------*/
      yDLST_list_by_name (a_before, &x_before, NULL, NULL);
      DEBUG_YDLST  yLOG_point   ("x_before"  , x_before);
      --rce;  if (x_before == NULL) {
         yDLST_list_by_ptr  (x_list, NULL);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(check for cycle)-------------*/
      rc = ydlst_seq__cycle  (0, x_list, x_before);
      DEBUG_YDLST  yLOG_value   ("cycle"     , rc);
      --rce;  if (rc > 0) {
         yDLST_list_by_ptr  (x_list, NULL);
         DEBUG_YDLST   yLOG_note    ("found a cycle");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(reset)-----------------------*/
      yDLST_list_by_ptr (x_list, NULL);
      /*---(done)------------------------*/
   }
   /*---(create)-------------------------*/
   rc = ydlst_seq__create (x_before, x_list);
   DEBUG_YDLST  yLOG_value   ("create"    , rc);
   --rce;  if (rc > 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha and omega)----------------*/
   if (strcmp (a_before, "SEQ_ALPHA") != 0) {
      rc = ydlst_seq__alpha  (x_list);
      rc = ydlst_seq__omega  (x_before);
   }
   /*---(make current)-------------------*/
   /*> yDLST_list_by_ptr  (x_list, NULL);                                             <*/
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: prepare a new list for use --------------------------------*/
yDLST_seq_before        (char *a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSEQ       *x_new       = NULL;
   tLIST      *x_list      = NULL;
   tLIST      *x_after     = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_after"   , a_after);
   --rce;  if (a_after  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get list)-----------------------*/
   x_list = yDLST_list_current ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_note    (x_list->l_title);
   /*---(find list)----------------------*/
   if (strcmp (a_after , "SEQ_OMEGA") == 0) {
      x_after  = s_omega;
   }
   /*---(find successor)-----------------*/
   else {
      /*---(find)------------------------*/
      yDLST_list_by_name (a_after, &x_after, NULL, NULL);
      DEBUG_YDLST  yLOG_point   ("x_after"   , x_after);
      --rce;  if (x_after == NULL) {
         yDLST_list_by_ptr  (x_list, NULL);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(check for cycle)-------------*/
      rc = ydlst_seq__cycle  (0, x_after, x_list);
      DEBUG_YDLST  yLOG_value   ("cycle"     , rc);
      --rce;  if (rc > 0) {
         yDLST_list_by_ptr  (x_list, NULL);
         DEBUG_YDLST   yLOG_note    ("found a cycle");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(reset)-----------------------*/
      yDLST_list_by_ptr (x_list, NULL);
      /*---(done)------------------------*/
   }
   /*---(create)-------------------------*/
   rc = ydlst_seq__create (x_list, x_after);
   DEBUG_YDLST  yLOG_value   ("create"    , rc);
   --rce;  if (rc > 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha and omega)----------------*/
   if (strcmp (a_after, "SEQ_OMEGA") != 0) {
      rc = ydlst_seq__alpha  (x_after);
      rc = ydlst_seq__omega  (x_list);
   }
   /*---(make current)-------------------*/
   /*> yDLST_list_by_ptr  (x_list, NULL);                                             <*/
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
ydlst_seq_init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   s_head    = NULL;
   s_tail    = NULL;
   s_count   =    0;
   ydlst_list_create ("SEQ_ALPHA", NULL, &s_alpha);
   ydlst_list_create ("SEQ_OMEGA", NULL, &s_omega);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_seq__purge        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(move)---------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   x_seq = s_head;
   while (x_seq != NULL) {
      ydlst_seq__unhook (x_seq);
      ydlst_seq__free   (&x_seq);
      x_seq = s_head;
   }
   s_head    = NULL;
   s_tail    = NULL;
   s_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   ydlst_seq__purge ();
   ydlst_list_destroy (s_alpha->l_title, &s_alpha);
   ydlst_list_destroy (s_omega->l_title, &s_omega);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

tSEQ*  ydlst_seq_current    (void)          { return s_curr; }
char   ydlst_seq_restore    (tSEQ  *x_seq)  { s_curr = x_seq;   return 0; }



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ydlst_seq__unit         (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tSEQ       *o           = NULL;
   int         c           =    0;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "SEQ unit         : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      o = s_tail; while (o != NULL) { ++x_back; o = o->q_mprev; }
      o = s_head; while (o != NULL) { ++x_fore; o = o->q_mnext; }
      snprintf (unit_answer, LEN_RECD, "SEQ count        : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = s_curr;
      if (o != NULL) {
         if (o->q_pred != NULL)  sprintf  (s, "[%.20s]", o->q_pred->l_title);
         else                  sprintf  (s, "[?]");
         if (o->q_succ != NULL)  sprintf  (t, "[%s]"   , o->q_succ->l_title);
         else                  sprintf  (t, "[?]");
         snprintf (unit_answer, LEN_RECD, "SEQ current      : %-22.22s -> %s", s, t);
      } else {
         snprintf (unit_answer, LEN_RECD, "SEQ current      : []                     -> []");
      }
      return unit_answer;
   }
   /*---(complex)------------------------*/
   o = s_head;
   while (o != NULL) {
      if (c >= a_num)  break;
      ++c;
      o = o->q_mnext;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         if (o->q_pred != NULL)  sprintf  (s, "[%.20s]", o->q_pred->l_title);
         else                  sprintf  (s, "[?]");
         if (o->q_succ != NULL)  sprintf  (t, "[%s]"   , o->q_succ->l_title);
         else                  sprintf  (t, "[?]");
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : %-22.22s -> %s", a_num, s, t);
      } else {
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : []                     -> []", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




