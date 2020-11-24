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
   a_seq->m_prev  = NULL;
   a_seq->m_next  = NULL;
   /*---(master)---------------*/
   a_seq->pred    = NULL;
   a_seq->p_prev  = NULL;
   a_seq->p_next  = NULL;
   a_seq->succ    = NULL;
   a_seq->s_prev  = NULL;
   a_seq->s_next  = NULL;
   /*---(complete)-------------*/
   return 1;
}

char*
ydlst_seq__memory       (tSEQ *a_seq)
{
   strlcpy (s_print, "[__.___.___]", LEN_RECD);
   if (a_seq->m_prev  != NULL)  s_print [ 1] = 'X';
   if (a_seq->m_next  != NULL)  s_print [ 2] = 'X';
   if (a_seq->pred    != NULL)  s_print [ 4] = 'X';
   if (a_seq->p_prev  != NULL)  s_print [ 5] = 'X';
   if (a_seq->p_next  != NULL)  s_print [ 6] = 'X';
   if (a_seq->succ    != NULL)  s_print [ 8] = 'X';
   if (a_seq->s_prev  != NULL)  s_print [ 9] = 'X';
   if (a_seq->s_next  != NULL)  s_print [10] = 'X';
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
   DEBUG_INPT   yLOG_spoint  (a_new);
   --rce;  if (a_new == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_spoint  (*a_new);
   --rce;  if (*a_new != NULL) {
      DEBUG_INPT   yLOG_snote   ("already set");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_INPT   yLOG_sint    (x_tries);
   DEBUG_INPT   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
      x_new->m_prev  = s_tail;
      s_tail->m_next = x_new;
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
   DEBUG_INPT   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_INPT   yLOG_snote   ("never set");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(simplify)-----------------------*/
   x_old = *a_old;
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (x_old->m_next != NULL)  x_old->m_next->m_prev = x_old->m_prev;
   else                        s_tail                = x_old->m_prev;
   if (x_old->m_prev != NULL)  x_old->m_prev->m_next = x_old->m_next;
   else                        s_head                = x_old->m_next;
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
   x_seq = a_pred->s_head;
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->succ, x_seq->succ->title);
      if (x_seq->succ == a_succ) {
         if (a_seq != NULL)  *a_seq = x_seq;
         DEBUG_YDLST  yLOG_snote   ("FOUN");
         return 1;
      }
      x_seq = x_seq->s_next;
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
   a_seq->succ       = a_succ;
   a_seq->s_next     = NULL;
   a_seq->s_prev     = NULL;
   if (a_pred->s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first on pred");
      a_pred->s_head         = a_seq;
      a_pred->s_tail         = a_seq;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to pred");
      a_seq->s_prev          = a_pred->s_tail;
      a_pred->s_tail->s_next = a_seq;
      a_pred->s_tail         = a_seq;
   }
   /*---(update count)-------------------*/
   ++a_pred->s_count;
   DEBUG_YDLST  yLOG_sint    (a_pred->s_count);
   /*---(into predecessor)------------*/
   a_seq->pred       = a_pred;
   a_seq->p_next     = NULL;
   a_seq->p_prev     = NULL;
   if (a_succ->p_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first on pred");
      a_succ->p_head         = a_seq;
      a_succ->p_tail         = a_seq;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to pred");
      a_seq->p_prev          = a_succ->p_tail;
      a_succ->p_tail->p_next = a_seq;
      a_succ->p_tail         = a_seq;
   }
   /*---(update count)-------------------*/
   ++a_succ->p_count;
   DEBUG_YDLST  yLOG_sint    (a_succ->p_count);
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
   x_pred = a_seq->pred;
   DEBUG_YDLST  yLOG_spoint  (x_pred);
   --rce;  if (x_pred  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(successor)----------------------*/
   x_succ = a_seq->succ;
   DEBUG_YDLST  yLOG_spoint  (x_succ);
   --rce;  if (x_succ  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove from predecessor)--------*/
   DEBUG_YDLST  yLOG_snote   ("remove from pred");
   if (a_seq->p_next != NULL)  a_seq->p_next->p_prev = a_seq->p_prev;
   else                        x_succ->p_tail        = a_seq->p_prev;
   if (a_seq->p_prev != NULL)  a_seq->p_prev->p_next = a_seq->p_next;
   else                        x_succ->p_head        = a_seq->p_next;
   /*---(remove from successr)-----------*/
   DEBUG_YDLST  yLOG_snote   ("remove from succ");
   if (a_seq->s_next != NULL)  a_seq->s_next->s_prev = a_seq->s_prev;
   else                        x_pred->s_tail        = a_seq->s_prev;
   if (a_seq->s_prev != NULL)  a_seq->s_prev->s_next = a_seq->s_next;
   else                        x_pred->s_head        = a_seq->s_next;
   /*---(update count)-------------------*/
   --x_pred->s_count;
   DEBUG_YDLST  yLOG_sint    (x_pred->s_count);
   --x_succ->p_count;
   DEBUG_YDLST  yLOG_sint    (x_succ->p_count);
   /*---(ground predecessor)-------------*/
   a_seq->pred       = NULL;
   a_seq->p_next     = NULL;
   a_seq->p_prev     = NULL;
   /*---(ground successor)---------------*/
   a_seq->succ       = NULL;
   a_seq->s_next     = NULL;
   a_seq->s_prev     = NULL;
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
   DEBUG_YDLST  yLOG_info    ("title"     , a_pred->title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("title"     , a_succ->title);
   /*---(prepare)------------------------*/
   x_seq = a_pred->s_head;
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->succ, x_seq->succ->title);
      if (x_seq->succ == a_succ) {
         ydlst_seq__unhook (x_seq);
         DEBUG_YDLST   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      x_seq = x_seq->s_next;
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
   DEBUG_YDLST  yLOG_point   ("s_head"    , s_alpha->s_head);
   o = s_alpha->s_head;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->succ, o->succ->title);
      if (o->succ == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (o);
         ydlst_seq__free   (&o);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      o = o->s_next;
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
   DEBUG_YDLST  yLOG_point   ("p_head"    , s_omega->p_head);
   o = s_omega->p_head;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->pred, o->pred->title);
      if (o->pred == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (o);
         ydlst_seq__free   (&o);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      }
      o = o->p_next;
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
   DEBUG_YDLST  yLOG_point   ("p_head"    , a_curr->p_head);
   o = a_curr->p_head;
   /*---(walk)---------------------------*/
   while (o != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", o, o->pred, o->pred->title);
      if (o->pred == a_look) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      } else {
         rc = ydlst_seq__cycle (a_lvl + 1, o->pred, a_look);
         if (rc > 0)  return rc;
      }
      o = o->p_next;
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
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(predecessors)-------------------*/
   if (a_scope != 0 && strchr ("[<" , a_scope) != NULL) {
      DEBUG_YDLST   yLOG_snote   ("predecessors");
      DEBUG_YDLST  yLOG_sint    (x_list->p_count);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return x_list->p_count;
   }
   /*---(successors)---------------------*/
   if (a_scope != 0 && strchr (">]" , a_scope) != NULL) {
      DEBUG_YDLST   yLOG_snote   ("successors");
      DEBUG_YDLST  yLOG_sint    (x_list->s_count);
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return x_list->s_count;
   }
   /*---(return)-------------------------*/
   DEBUG_YDLST   yLOG_snote   ("scope not understood");
   --rce;
   DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

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
      DEBUG_YDLST  yLOG_snote   (x_list->title);
   }
   /*---(start)--------------------------*/
   switch (x_scope) {
   case '*' :  x_seq = s_head;            break;
   case '<' :  x_seq = x_list->p_head;    break;
   case '>' :  x_seq = x_list->s_head;    break;
   }
   /*---(walk)---------------------------*/
   while (x_seq != NULL) {
      if (c >= n)  break;
      switch (x_scope) {
      case '*' :  x_seq = x_seq->m_next;    break;
      case '<' :  x_seq = x_seq->p_next;    break;
      case '>' :  x_seq = x_seq->s_next;    break;
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
      if (a_list != NULL)  *a_list = x_seq->pred;
      if (a_data != NULL)  *a_data = x_seq->pred->data;
      break;
   case ']' : case '>' :
      if (a_list != NULL)  *a_list = x_seq->succ;
      if (a_data != NULL)  *a_data = x_seq->succ->data;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_seq_by_cursor     (char a_scope, char a_move, void **a_seq, void **a_list, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_scope     =  '-';
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_seq  != NULL)  *a_seq  = NULL;
   if (a_list != NULL)  *a_list = NULL;
   if (a_data != NULL)  *a_data = NULL;
   /*---(defense)------------------------*/
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
      DEBUG_YDLST  yLOG_snote   (x_list->title);
   }
   /*---(switch)-------------------------*/
   DEBUG_YDLST  yLOG_schar   (a_move);
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   --rce;  switch (a_move) {
   case '[' :
      DEBUG_YDLST  yLOG_snote   ("head");
      switch (x_scope) {
      case '*' :  s_curr = s_head;            break;
      case '<' :  s_curr = x_list->p_head;    break;
      case '>' :  s_curr = x_list->s_head;    break;
      }
      break;
   case '<' :
      DEBUG_YDLST  yLOG_snote   ("prev");
      if (s_curr != NULL) {
         switch (x_scope) {
         case '*' :  s_curr = s_curr->m_prev;    break;
         case '<' :  s_curr = s_curr->p_prev;    break;
         case '>' :  s_curr = s_curr->s_prev;    break;
         }
      }
      break;
   case '-' :
      DEBUG_YDLST  yLOG_snote   ("curr");
      break;
   case '>' :
      DEBUG_YDLST  yLOG_snote   ("next");
      if (s_curr != NULL) {
         switch (x_scope) {
         case '*' :  s_curr = s_curr->m_next;    break;
         case '<' :  s_curr = s_curr->p_next;    break;
         case '>' :  s_curr = s_curr->s_next;    break;
         }
      }
      break;
   case ']' :
      DEBUG_YDLST  yLOG_snote   ("tail");
      switch (x_scope) {
      case '*' :  s_curr = s_tail;            break;
      case '<' :  s_curr = x_list->p_tail;    break;
      case '>' :  s_curr = x_list->s_tail;    break;
      }
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(bounce off ends)----------------*/
   --rce;  if (s_curr == NULL) {
      if (a_move == '<') {
         switch (x_scope) {
         case '*' :  s_curr = s_head;            break;
         case '<' :  s_curr = x_list->p_head;    break;
         case '>' :  s_curr = x_list->s_head;    break;
         }
      }
      else {
         switch (x_scope) {
         case '*' :  s_curr = s_tail;            break;
         case '<' :  s_curr = x_list->p_tail;    break;
         case '>' :  s_curr = x_list->s_tail;    break;
         }
      }
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   if (a_seq  != NULL)  *a_seq  = s_curr;
   switch (a_scope) {
   case '[' : case '<' : case '*' :
      if (a_list != NULL)  *a_list = s_curr->pred;
      if (a_data != NULL)  *a_data = s_curr->pred->data;
      break;
   case ']' : case '>' :
      if (a_list != NULL)  *a_list = s_curr->succ;
      if (a_data != NULL)  *a_data = s_curr->succ->data;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
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
   DEBUG_YDLST  yLOG_info    ("title"     , a_pred->title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("title"     , a_succ->title);
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
    *>    yDLST_list_by_ptr  (a_succ);                                                <* 
    *> }                                                                              <*/
   /*> if (strcmp (a_succ, "SEQ_OMEGA") != 0) {                                       <* 
    *>    DEBUG_YDLST  yLOG_note    ("adding new one before a named list");           <* 
    *>    rc = ydlst_seq__omega  (a_pred);                                            <* 
    *>    yDLST_list_by_ptr  (a_pred);                                                <* 
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
   DEBUG_YDLST  yLOG_info    ("title"     , a_pred->title);
   DEBUG_YDLST  yLOG_point   ("a_succ"    , a_succ);
   --rce;  if (a_succ  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("title"     , a_succ->title);
   /*---(check match)--------------------*/
   --rce;  if (a_pred == a_succ) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_seq = a_pred->s_head;
   /*---(walk)---------------------------*/
   --rce;  while (x_seq != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", x_seq, x_seq->succ, x_seq->succ->title);
      if (x_seq->succ == a_succ) {
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
      x_seq = x_seq->s_next;
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
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(check for alpha)----------------*/
   if (strcmp (a_before, "SEQ_ALPHA") == 0) {
      x_before = s_alpha;
   }
   /*---(find predecessor)---------------*/
   else {
      /*---(find)------------------------*/
      yDLST_list_by_name (a_before, &x_before, NULL);
      DEBUG_YDLST  yLOG_point   ("x_before"  , x_before);
      --rce;  if (x_before == NULL) {
         yDLST_list_by_ptr  (x_list);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(check for cycle)-------------*/
      rc = ydlst_seq__cycle  (0, x_list, x_before);
      DEBUG_YDLST  yLOG_value   ("cycle"     , rc);
      --rce;  if (rc > 0) {
         yDLST_list_by_ptr  (x_list);
         DEBUG_YDLST   yLOG_note    ("found a cycle");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(reset)-----------------------*/
      yDLST_list_by_ptr (x_list);
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
   /*> yDLST_list_by_ptr  (x_list);                                                   <*/
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
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(find list)----------------------*/
   if (strcmp (a_after , "SEQ_OMEGA") == 0) {
      x_after  = s_omega;
   }
   /*---(find successor)-----------------*/
   else {
      /*---(find)------------------------*/
      yDLST_list_by_name (a_after, &x_after, NULL);
      DEBUG_YDLST  yLOG_point   ("x_after"   , x_after);
      --rce;  if (x_after == NULL) {
         yDLST_list_by_ptr  (x_list);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(check for cycle)-------------*/
      rc = ydlst_seq__cycle  (0, x_after, x_list);
      DEBUG_YDLST  yLOG_value   ("cycle"     , rc);
      --rce;  if (rc > 0) {
         yDLST_list_by_ptr  (x_list);
         DEBUG_YDLST   yLOG_note    ("found a cycle");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(reset)-----------------------*/
      yDLST_list_by_ptr (x_list);
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
   /*> yDLST_list_by_ptr  (x_list);                                                   <*/
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
   ydlst_list_float (&s_alpha);
   s_alpha->title = strdup ("SEQ_ALPHA");
   ydlst_list_float (&s_omega);
   s_omega->title = strdup ("SEQ_OMEGA");
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
   ydlst_list_free (&s_alpha);
   ydlst_list_free (&s_omega);
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
      o = s_head; while (o != NULL) { ++x_fore; o = o->m_next; }
      o = s_tail; while (o != NULL) { ++x_back; o = o->m_prev; }
      snprintf (unit_answer, LEN_RECD, "SEQ count        : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = s_curr;
      if (o != NULL) {
         if (o->pred != NULL)  sprintf  (s, "[%.20s]", o->pred->title);
         else                  sprintf  (s, "[?]");
         if (o->succ != NULL)  sprintf  (t, "[%s]"   , o->succ->title);
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
      o = o->m_next;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         if (o->pred != NULL)  sprintf  (s, "[%.20s]", o->pred->title);
         else                  sprintf  (s, "[?]");
         if (o->succ != NULL)  sprintf  (t, "[%s]"   , o->succ->title);
         else                  sprintf  (t, "[?]");
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : %-22.22s -> %s", a_num, s, t);
      } else {
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : []                     -> []", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




