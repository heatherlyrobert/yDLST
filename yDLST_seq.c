/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tDLST_SEQ  *s_head      = NULL;
static      tDLST_SEQ  *s_tail      = NULL;
static      tDLST_SEQ  *s_curr      = NULL;
static      int         s_count     =    0;

static      tDLST_LIST *s_alpha     = NULL;
static      tDLST_LIST *s_omega     = NULL;

/*====================------------------------------------====================*/
/*===----                      fundamental actions                     ----===*/
/*====================------------------------------------====================*/
static void  o___PRIMATIVE_______o () { return; }

char
ydlst_seq__wipe          (tDLST_SEQ *a_dst)
{
   /*---(defense)--------------*/
   if (a_dst == NULL)  return -1;
   /*---(seq)------------------*/
   a_dst->prev  = NULL;
   a_dst->next  = NULL;
   /*---(master)---------------*/
   a_dst->pred    = NULL;
   a_dst->p_prev  = NULL;
   a_dst->p_next  = NULL;
   a_dst->succ    = NULL;
   a_dst->s_prev  = NULL;
   a_dst->s_next  = NULL;
   /*---(complete)-------------*/
   return 0;
}

tDLST_SEQ*
ydlst_seq__new          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tDLST_SEQ  *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(create)-------------------------*/
   while (++x_tries < 10) {
      x_new = (tDLST_SEQ *) malloc (sizeof (tDLST_SEQ));
      if (x_new != NULL)     break;
   }
   DEBUG_YDLST  yLOG_sint    (x_tries);
   DEBUG_YDLST  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(wipe)---------------------------*/
   DEBUG_YDLST  yLOG_snote   ("wipe");
   ydlst_seq__wipe (x_new);
   /*---(add to list)--------------------*/
   if (s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("add first");
      s_head       = x_new;
      s_tail       = x_new;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to end");
      x_new->prev  = s_tail;
      s_tail->next = x_new;
      s_tail       = x_new;
   }
   /*---(update count)-------------------*/
   ++s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_new;
}

char
ydlst_seq__del          (tDLST_SEQ *a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(remove from main DLL)-----------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (a_old->next != NULL)  a_old->next->prev = a_old->prev;
   else                      s_tail            = a_old->prev;
   if (a_old->prev != NULL)  a_old->prev->next = a_old->next;
   else                      s_head            = a_old->next;
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old);
   free (a_old);
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

char
ydlst_seq__hook         (tDLST_LIST *a_pred, tDLST_LIST *a_succ, tDLST_SEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
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
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_seq->p_next     = NULL;
   a_seq->p_prev     = NULL;
   a_seq->s_next     = NULL;
   a_seq->s_prev     = NULL;
   /*---(into predecessor)------------*/
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
ydlst_seq__unhook       (tDLST_SEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tDLST_LIST *x_pred      = NULL;
   tDLST_LIST *x_succ      = NULL;
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
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from pred");
   if (a_seq->s_next != NULL)  a_seq->s_next->s_prev = a_seq->s_prev;
   else                        x_pred->s_tail        = a_seq->s_prev;
   if (a_seq->s_prev != NULL)  a_seq->s_prev->s_next = a_seq->s_next;
   else                        x_pred->s_head        = a_seq->s_next;
   /*---(update count)-------------------*/
   --x_pred->s_count;
   DEBUG_YDLST  yLOG_sint    (x_pred->s_count);
   /*---(predecessor)--------------------*/
   x_succ = a_seq->succ;
   DEBUG_YDLST  yLOG_spoint  (x_succ);
   --rce;  if (x_succ  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from succ");
   if (a_seq->p_next != NULL)  a_seq->p_next->p_prev = a_seq->p_prev;
   else                        x_succ->p_tail        = a_seq->p_prev;
   if (a_seq->p_prev != NULL)  a_seq->p_prev->p_next = a_seq->p_next;
   else                        x_succ->p_head        = a_seq->p_next;
   /*---(update count)-------------------*/
   --x_succ->p_count;
   DEBUG_YDLST  yLOG_sint    (x_succ->p_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq__alpha  (tDLST_LIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_SEQ  *u           = NULL;
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
   u = s_alpha->s_head;
   /*---(walk)---------------------------*/
   while (u != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", u, u->succ, u->succ->title);
      if (u->succ == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (u);
         ydlst_seq__del    (u);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      u = u->s_next;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, -1);
   return -1;
}

char
ydlst_seq__omega  (tDLST_LIST *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_SEQ  *u           = NULL;
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
   u = s_omega->p_head;
   /*---(walk)---------------------------*/
   while (u != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", u, u->pred, u->pred->title);
      if (u->pred == a_list) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         ydlst_seq__unhook (u);
         ydlst_seq__del    (u);
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 0;
      }
      u = u->p_next;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, -1);
   return -1;
}

char
ydlst_seq__cycle  (int a_lvl, tDLST_LIST *a_curr, tDLST_LIST *a_look)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_SEQ  *u           = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   DEBUG_YDLST  yLOG_value   ("a_lvl"     , a_lvl);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_look"    , a_look);
   --rce;  if (a_look == NULL) {
      DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(touched front)------------------*/
   DEBUG_YDLST  yLOG_point   ("a_curr"    , a_curr);
   --rce;  if (a_curr == NULL) {
      DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_point   ("p_head"    , a_curr->p_head);
   u = a_curr->p_head;
   /*---(walk)---------------------------*/
   while (u != NULL) {
      DEBUG_YDLST  yLOG_complex ("check"     , "%-10p, %-10p, %s", u, u->pred, u->pred->title);
      if (u->pred == a_look) {
         DEBUG_YDLST  yLOG_note    ("FOUND IT");
         DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
         return 1;
      } else {
         rc = ydlst_seq__cycle (a_lvl + 1, u->pred, a_look);
         if (rc > 0)  return rc;
      }
      u = u->p_next;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, -1);
   return -1;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*----: prepare a new list for use --------------------------------*/
yDLST_seq_after         (char *a_before)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_SEQ  *x_new       = NULL;
   tDLST_LIST *x_list      = NULL;
   tDLST_LIST *x_before    = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_before"  , a_before);
   --rce;  if (a_before  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(find list)----------------------*/
   if (strcmp (a_before, "SEQ_ALPHA") == 0)   x_before = s_alpha;
   else {
      yDLST_list_find  (a_before);
      x_before = ydlst_list_getcurr  ();
      DEBUG_YDLST  yLOG_point   ("x_before"  , x_before);
      --rce;  if (x_before == NULL) {
         ydlst_list_setcurr  (x_list);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = ydlst_seq__cycle  (0, x_list, x_before);
      DEBUG_YDLST  yLOG_value   ("cycle"     , rc);
      --rce;  if (rc > 0) {
         ydlst_list_setcurr  (x_list);
         DEBUG_YDLST   yLOG_note    ("found a cycle");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check match)--------------------*/
   --rce;  if (x_list == x_before) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   x_new = ydlst_seq__new ();
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->pred = x_before;
   x_new->succ = x_list;
   /*---(hook)---------------------------*/
   rc = ydlst_seq__hook (x_before, x_list, x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha and omega)----------------*/
   if (strcmp (a_before, "SEQ_ALPHA") != 0) {
      rc = ydlst_seq__alpha  (x_list);
      rc = ydlst_seq__omega  (x_before);
   }
   /*---(make current)-------------------*/
   ydlst_list_setcurr  (x_list);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: prepare a new list for use --------------------------------*/
ydlst_seq_before        (char *a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_SEQ  *x_new       = NULL;
   tDLST_LIST *x_list      = NULL;
   tDLST_LIST *x_after     = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_after"   , a_after);
   --rce;  if (a_after  == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(find list)----------------------*/
   if (strcmp (a_after , "SEQ_OMEGA") == 0)   x_after  = s_omega;
   else {
      yDLST_list_find  (a_after);
      x_after = ydlst_list_getcurr  ();
      DEBUG_YDLST  yLOG_point   ("x_after"   , x_after);
      --rce;  if (x_after == NULL) {
         ydlst_list_setcurr  (x_list);
         DEBUG_YDLST   yLOG_note    ("could not find before list");
         DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(create)-------------------------*/
   x_new = ydlst_seq__new ();
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->pred = x_list;
   x_new->succ = x_after;
   /*---(hook)---------------------------*/
   rc = ydlst_seq__hook (x_list, x_after, x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha and omega)----------------*/
   if (strcmp (a_after , "SEQ_OMEGA") != 0)  rc = ydlst_seq__omega  (x_list);
   /*---(make current)-------------------*/
   ydlst_list_setcurr  (x_list);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

void*      /*--> find a seq using sequential pos -----------------------------*/
yDLST_seq_entry         (int a_pos, void **a_after)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tDLST_SEQ  *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   DEBUG_YDLST  yLOG_sint    (a_pos);
   /*---(prepare)------------------------*/
   if (a_after != NULL)  *a_after = NULL;
   /*---(move)---------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   x_seq = s_head;
   while (x_seq != NULL) {
      if (c >= a_pos)  break;
      x_seq = x_seq->next;
      ++c;
   }
   DEBUG_YDLST  yLOG_spoint  (x_seq);
   DEBUG_YDLST  yLOG_sint    (c);
   /*---(check)--------------------------*/
   if (c != a_pos) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (x_seq == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(save)---------------------------*/
   if (a_after != NULL && x_seq->succ != NULL)  *a_after = x_seq->succ->data;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   if (x_seq->pred == NULL) return NULL;
   return x_seq->pred->data;
}

int
yDLST_pred_count     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   DEBUG_YDLST  yLOG_sint    (x_list->p_count);
   /*---(return)-------------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->p_count;
}

void*      /*--> find a list using its title ---------------------------------*/
yDLST_pred_seek         (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   tDLST_SEQ  *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_list->p_head);
   DEBUG_YDLST  yLOG_sint    (x_list->p_count);
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   DEBUG_YDLST  yLOG_spoint  (x_list->p_tail);
   /*---(switch)-------------------------*/
   switch (a_pos) {
   case YDLST_HEAD :
      s_curr = x_list->p_head;
      break;
   case YDLST_PREV :
      if (s_curr != NULL)   s_curr = s_curr->p_prev;
      else                  rc = -1;
      break;
   case YDLST_NEXT :
      if (s_curr != NULL)   s_curr = s_curr->p_next;
      else                  rc = -2;
      break;
   case YDLST_TAIL :
      s_curr = x_list->p_tail;
      break;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(check)--------------------------*/
   if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   --rce;  if (s_curr->pred == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->pred->data;
}

int
yDLST_succ_count     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   DEBUG_YDLST  yLOG_sint    (x_list->s_count);
   /*---(return)-------------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->s_count;
}

void*      /*--> find a list using its title ---------------------------------*/
yDLST_succ_seek         (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   tDLST_SEQ  *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_list->s_head);
   DEBUG_YDLST  yLOG_sint    (x_list->s_count);
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   DEBUG_YDLST  yLOG_spoint  (x_list->s_tail);
   /*---(switch)-------------------------*/
   switch (a_pos) {
   case YDLST_HEAD :
      s_curr = x_list->s_head;
      break;
   case YDLST_PREV :
      if (s_curr != NULL)   s_curr = s_curr->s_prev;
      else                  rc = -1;
      break;
   case YDLST_NEXT :
      if (s_curr != NULL)   s_curr = s_curr->s_next;
      else                  rc = -2;
      break;
   case YDLST_TAIL :
      s_curr = x_list->s_tail;
      break;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(check)--------------------------*/
   if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   --rce;  if (s_curr->succ == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->succ->data;
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
   s_alpha   = ydlst_list_new (YDLST_FLOATER);
   s_alpha->title = strdup ("SEQ_ALPHA");
   s_omega   = ydlst_list_new (YDLST_FLOATER);
   s_omega->title = strdup ("SEQ_OMEGA");
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_seq_wrap          (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   s_head    = NULL;
   s_tail    = NULL;
   s_count   =    0;
   free (s_alpha->title);
   ydlst_list_del (s_alpha, YDLST_FLOATER);
   free (s_omega->title);
   ydlst_list_del (s_omega, YDLST_FLOATER);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



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
   tDLST_SEQ  *u           = NULL;
   int         c           =    0;
   char        s           [LEN_RECD]  = "[]";
   char        t           [LEN_RECD]  = "[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "SEQ unit         : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      u = s_head; while (u != NULL) { ++x_fore; u = u->next; }
      u = s_tail; while (u != NULL) { ++x_back; u = u->prev; }
      snprintf (unit_answer, LEN_RECD, "SEQ count        : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   /*---(complex)------------------------*/
   u = s_head;
   while (u != NULL) {
      if (c >= a_num)  break;
      ++c;
      u = u->next;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (u != NULL) {
         sprintf  (s, "[%.20s]", u->pred->title);
         sprintf  (t, "[%s]"   , u->succ->title);
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : %-22.22s -> %s", a_num, s, t);
      } else {
         snprintf (unit_answer, LEN_RECD, "SEQ entry   (%2d) : []                     -> []", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




