/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all links)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLINE      *s_head      = NULL;  /* head node pointer                   */
static      tLINE      *s_tail      = NULL;  /* tail node pointer                   */
static      tLINE      *s_curr      = NULL;  /* pointer to current link             */
static      int         s_count     =    0;  /* number of links                     */
static      char        s_print     [LEN_RECD] = "";



/*====================------------------------------------====================*/
/*===----                    cleansing and cleaning                    ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSE_________o () { return; }

char
ydlst_line__wipe        (tLINE *a_line)
{
   /*---(defense)--------------*/
   if (a_line == NULL)  return -1;
   /*---(master)---------------*/
   a_line->title   = NULL;
   a_line->data    = NULL;
   /*---(lines)----------------*/
   a_line->m_prev  = NULL;
   a_line->m_next  = NULL;
   /*---(list)-----------------*/
   a_line->parent  = NULL;
   a_line->p_prev  = NULL;
   a_line->p_next  = NULL;
   /*---(focus)----------------*/
   a_line->focus   = YDLST_OFF;
   a_line->f_prev  = NULL;
   a_line->f_next  = NULL;
   /*---(active)---------------*/
   a_line->active  = YDLST_OFF;
   a_line->a_prev  = NULL;
   a_line->a_next  = NULL;
   /*---(complete)-------------*/
   return 1;
}

char*
ydlst_line__memory       (tLINE *a_line)
{
   strlcpy (s_print, "[__.__.___.___.___]", LEN_RECD);
   if (a_line->title   != NULL)       s_print [ 1] = 'X';
   if (a_line->data    != NULL)       s_print [ 2] = 'X';
   if (a_line->m_prev  != NULL)       s_print [ 4] = 'X';
   if (a_line->m_next  != NULL)       s_print [ 5] = 'X';
   if (a_line->parent  != NULL)       s_print [ 7] = 'X';
   if (a_line->p_prev  != NULL)       s_print [ 8] = 'X';
   if (a_line->p_next  != NULL)       s_print [ 9] = 'X';
   if (a_line->focus   != YDLST_OFF)  s_print [11] = 'X';
   if (a_line->f_prev  != NULL)       s_print [12] = 'X';
   if (a_line->f_next  != NULL)       s_print [13] = 'X';
   if (a_line->active  != YDLST_OFF)  s_print [15] = 'X';
   if (a_line->a_prev  != NULL)       s_print [16] = 'X';
   if (a_line->a_next  != NULL)       s_print [17] = 'X';
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                    allocating and freeing                    ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ydlst_line__new         (tLINE **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tLINE      *x_new       = NULL;
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
      x_new = (tLINE *) malloc (sizeof (tLINE));
      if (x_tries > 3)   break;
   }
   DEBUG_INPT   yLOG_sint    (x_tries);
   DEBUG_INPT   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   ydlst_line__wipe (x_new);
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
ydlst_line__free        (tLINE **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLINE      *x_old       = NULL;
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
   /*---(free title)---------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_old->title);
   if (x_old->title != NULL)  free (x_old->title);
   x_old->title == NULL;
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_old->data);
   if (x_old->data  != NULL)  free (x_old->data);
   x_old->data = NULL;
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
   DEBUG_YDLST  yLOG_snote   (a_list->title);
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_line->title);
   DEBUG_YDLST  yLOG_spoint  (a_line->parent);
   --rce;  if (a_line->parent != NULL) {
      DEBUG_YDLST   yLOG_snote   ("already hooked");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(tie to parent)---------------*/
   DEBUG_YDLST  yLOG_snote   ("parent");
   a_line->parent    = a_list;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->p_next    = NULL;
   a_line->p_prev    = NULL;
   /*---(into lists links)------------*/
   if (a_list->c_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first line");
      a_list->c_head         = a_line;
      a_list->c_tail         = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append line");
      a_line->p_prev         = a_list->c_tail;
      a_list->c_tail->p_next = a_line;
      a_list->c_tail         = a_line;
   }
   /*---(update count)-------------------*/
   ++a_list->c_count;
   DEBUG_YDLST  yLOG_sint    (a_list->c_count);
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
   DEBUG_YDLST  yLOG_snote   (a_line->title);
   x_list = a_line->parent;
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("not hooked to parent");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(into lists links)------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->p_next != NULL)  a_line->p_next->p_prev = a_line->p_prev;
   else                         x_list->c_tail         = a_line->p_prev;
   if (a_line->p_prev != NULL)  a_line->p_prev->p_next = a_line->p_next;
   else                         x_list->c_head         = a_line->p_next;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("ground");
   a_line->p_next    = NULL;
   a_line->p_prev    = NULL;
   a_line->parent    = NULL;
   /*---(update count)-------------------*/
   --x_list->c_count;
   DEBUG_YDLST  yLOG_sint    (x_list->c_count);
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
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return s_count;
   }
   /*---(get list)-----------------------*/
   DEBUG_YDLST  yLOG_snote   ("local");
   x_list = yDLST_list_current ();
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   DEBUG_YDLST  yLOG_sint    (x_list->c_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->c_count;
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
      DEBUG_YDLST  yLOG_snote   ((*a_list)->title);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ydlst_line__parent      (char a_local)
{
   if (!a_local) {
      yDLST_list_restore (s_curr->parent);
      DEBUG_YDLST  yLOG_snote   (s_curr->parent->title);
   }
   return 0;
}

char       /*--> find a list using sequential pos ----------------------------*/
yDLST_line_by_index     (char a_scope, int n, void **a_line, void **a_data)
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
   if (a_line != NULL)  *a_line = NULL;
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
   rc = ydlst_line__scope (a_scope, &x_local, &x_list);
   DEBUG_YDLST  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(move)---------------------------*/
   if (x_local)  x_line = x_list->c_head;
   else          x_line = s_head;
   while (x_line != NULL) {
      if (c >= n)  break;
      if (x_local)  x_line = x_line->p_next;
      else          x_line = x_line->m_next;
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
   /*---(save)---------------------------*/
   s_curr  = x_line;
   if (a_line != NULL)  *a_line = x_line;
   if (a_data != NULL)  *a_data = x_line->data;
   DEBUG_YDLST  yLOG_snote   (s_curr->title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_line_by_cursor   (char a_scope, char a_move, void **a_curr, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_local     =    0;
   tLIST      *x_list      = NULL;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_curr != NULL)  *a_curr = NULL;
   if (a_data != NULL)  *a_data = NULL;
   x_curr = s_curr;
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
      x_curr = s_head;
      DEBUG_DATA   yLOG_spoint  (x_curr);
      if (x_curr == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check scope)--------------------*/
   rc = ydlst_line__scope (a_scope, &x_local, &x_list);
   DEBUG_YDLST  yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(switch)-------------------------*/
   DEBUG_YDLST  yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DEAD :
      x_curr = IF_LOCAL x_list->c_head : s_head;
      break;
   case YDLST_PREV : case YDLST_DREV :
      x_curr = IF_LOCAL x_curr->p_prev : x_curr->m_prev;;
      break;
   case YDLST_CURR : case YDLST_DURR :
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DEXT :
      x_curr = IF_LOCAL x_curr->p_next : x_curr->m_next;;
      break;
   case YDLST_TAIL : case YDLST_DAIL :
      x_curr = IF_LOCAL x_list->c_tail : s_tail;
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV)   x_curr = IF_LOCAL x_list->c_head : s_head;
      if (a_move == YDLST_NEXT)   x_curr = IF_LOCAL x_list->c_tail : s_tail;
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
   if (a_curr != NULL)  *a_curr = s_curr;
   if (a_data != NULL)  *a_data = s_curr->data;
   DEBUG_YDLST  yLOG_snote   (s_curr->title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char       /*--> find a list using its title ---------------------------------*/
yDLST_line_by_name      (char a_scope, char *a_title, void **a_line, void **a_data)
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
   if (a_line != NULL)  *a_line = NULL;
   if (a_data != NULL)  *a_data = NULL;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_title);
   DEBUG_YDLST  yLOG_spoint  (s_head);
   --rce;  if (s_head == NULL) {
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
   if (x_local)   x_line = x_list->c_head;
   else           x_line = s_head;
   while (x_line != NULL) {
      if (x_line->title != NULL) {
         if (strcmp (x_line->title, a_title) == 0) break;
      }
      if (x_local)   x_line = x_line->p_next;
      else           x_line = x_line->m_next;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   s_curr  = x_line;
   if (a_line != NULL)  *a_line = s_curr;
   if (a_data != NULL)  *a_data = s_curr->data;
   DEBUG_YDLST  yLOG_snote   (s_curr->title);
   /*---(update list)--------------------*/
   ydlst_line__parent (x_local);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 0;
}

char
ydlst_line_by_ptr       (tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(key data)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_spoint  (s_tail);
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(search)-------------------------*/
   x_line = s_head;
   while (x_line != NULL) {
      if (x_line == a_line)   break;
      x_line = x_line->m_next;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_line);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   s_curr = a_line;
   DEBUG_YDLST  yLOG_snote   (s_curr->title);
   /*---(update list)--------------------*/
   yDLST_list_restore (s_curr->parent);
   DEBUG_YDLST  yLOG_snote   (s_curr->parent->title);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 0;
}

char
yDLST_line_list         (void **a_list, void **a_data)
{
   char        rce         =  -10;
   if (a_list != NULL)  *a_list == NULL;
   if (a_data != NULL)  *a_data == NULL;
   --rce;  if (s_curr == NULL)   return rce;
   if (a_list != NULL)  *a_list = s_curr->parent;
   if (a_data != NULL && s_curr->parent != NULL)  *a_data = s_curr->parent->data;
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
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(find list)----------------------*/
   yDLST_line_by_name (YDLST_DURR, a_title, &x_new, NULL);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
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
   x_new->title = strdup (a_title);
   x_new->data  = a_data;
   /*---(make current)-------------------*/
   s_curr       = x_new;
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
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
   yDLST_line_by_name (YDLST_DURR, a_title, NULL, NULL);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST   yLOG_note    ("line could not be found");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear focus)-----------------*/
   yDLST_focus_off  ();
   yDLST_active_off ();
   /*---(unhook)----------------------*/
   rc = ydlst_line__unhook (s_curr);
   DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(delete)-------------------------*/
   rc = ydlst_line__free (&s_curr);
   DEBUG_YDLST  yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
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
   s_curr = a_list->c_head;
   DEBUG_YDLST   yLOG_point   ("s_curr"    , s_curr);
   while (s_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (s_curr->title);
      yDLST_focus_off  ();
      yDLST_active_off ();
      rc = ydlst_line__unhook (s_curr);
      rc = ydlst_line__free   (&s_curr);
      s_curr  = a_list->c_head;
      DEBUG_YDLST   yLOG_point   ("s_curr"    , s_curr);
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
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(walk through attached links)----*/
   s_curr = x_list->c_head;
   DEBUG_YDLST   yLOG_point   ("s_curr"    , s_curr);
   while (s_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (s_curr->title);
      yDLST_focus_off  ();
      yDLST_active_off ();
      rc = ydlst_line__unhook (s_curr);
      rc = ydlst_line__free   (&s_curr);
      s_curr  = x_list->c_head;
      DEBUG_YDLST   yLOG_point   ("s_curr"    , s_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_line_init         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   s_head    = NULL;
   s_tail    = NULL;
   s_curr    = NULL;
   s_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_line_wrap         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   s_head    = NULL;
   s_tail    = NULL;
   s_curr    = NULL;
   s_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

tLINE* yDLST_line_current   (void)          { return s_curr; }
char   yDLST_line_restore   (tLINE *x_line) { s_curr = x_line;  return 0; }



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
      o = s_head; while (o != NULL) { ++x_fore; o = o->m_next; }
      o = s_tail; while (o != NULL) { ++x_back; o = o->m_prev; }
      snprintf (unit_answer, LEN_RECD, "LINE count       : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = s_curr;
      if (o != NULL) {
         x_len = strlen (o->title);
         sprintf  (t, "[%.20s]", o->title);
         snprintf (unit_answer, LEN_RECD, "LINE current     : %2d%-22.22s   %c  %c  %c", x_len, t, (o->parent == NULL) ? YDLST_OFF : YDLST_ON, o->focus, o->active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE current     :  0[]                       -  -  -");
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
         x_len = strlen (o->title);
         sprintf  (t, "[%.20s]", o->title);
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) : %2d%-22.22s   %c  %c  %c", a_num, x_len, t, (o->parent == NULL) ? YDLST_OFF : YDLST_ON, o->focus, o->active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) :  0[]                       -  -  -", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




