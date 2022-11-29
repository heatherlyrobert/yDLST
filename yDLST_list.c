/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all lists)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLIST      *s_head      = NULL;   /* head node pointer                   */
static      tLIST      *s_tail      = NULL;   /* tail node pointer                   */
static      tLIST      *s_curr      = NULL;   /* pointer to current list             */
static      int         s_count     =    0;   /* number of lists                     */
static      char        s_print     [LEN_RECD] = "";





/*====================------------------------------------====================*/
/*===----                      clearing and wiping                     ----===*/
/*====================------------------------------------====================*/
static void  o___CLEANSE_________o () { return; }

char
ydlst_list__wipe         (tLIST *a_list)
{
   /*---(defense)--------------*/
   if (a_list == NULL)  return -1;
   /*---(master)---------------*/
   a_list->title   = NULL;
   a_list->data    = NULL;
   /*---(list of lists)--------*/
   a_list->linked  = YDLST_FLOATER;
   a_list->m_prev  = NULL;
   a_list->m_next  = NULL;
   /*---(list of lines)--------*/
   a_list->c_head  = NULL;
   a_list->c_tail  = NULL;
   a_list->c_count =    0;
   /*---(comes before)---------*/
   a_list->p_head  = NULL;
   a_list->p_tail  = NULL;
   a_list->p_count =    0;
   /*---(comes after)----------*/
   a_list->s_head  = NULL;
   a_list->s_tail  = NULL;
   a_list->s_count =    0;
   /*---(complete)-------------*/
   return 1;
}

char*
ydlst_list__memory       (tLIST *a_list)
{
   strlcpy (s_print, "[__.___.___.___.___]", LEN_RECD);
   if (a_list->title   != NULL)            s_print [ 1] = 'X';
   if (a_list->data    != NULL)            s_print [ 2] = 'X';
   if (a_list->linked  != YDLST_FLOATER)   s_print [ 4] = 'X';
   if (a_list->m_prev  != NULL)            s_print [ 5] = 'X';
   if (a_list->m_next  != NULL)            s_print [ 6] = 'X';
   if (a_list->c_head  != NULL)            s_print [ 8] = 'X';
   if (a_list->c_tail  != NULL)            s_print [ 9] = 'X';
   if (a_list->c_count != 0)               s_print [10] = 'X';
   if (a_list->p_head  != NULL)            s_print [12] = 'X';
   if (a_list->p_tail  != NULL)            s_print [13] = 'X';
   if (a_list->p_count != 0)               s_print [14] = 'X';
   if (a_list->s_head  != NULL)            s_print [16] = 'X';
   if (a_list->s_tail  != NULL)            s_print [17] = 'X';
   if (a_list->s_count != 0)               s_print [18] = 'X';
   return s_print;
}



/*====================------------------------------------====================*/
/*===----                    allocating and freeing                    ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ydlst_list__new          (char a_link, tLIST **a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tLIST      *x_new       = NULL;
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
      x_new = (tLIST *) malloc (sizeof (tLIST));
      if (x_tries > 3)   break;
   }
   DEBUG_YDLST   yLOG_sint    (x_tries);
   DEBUG_YDLST   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   ydlst_list__wipe (x_new);
   /*---(save return)--------------------*/
   *a_new = x_new;
   /*---(check for floater)--------------*/
   if (a_link == YDLST_FLOATER) {
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
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

char ydlst_list_new   (tLIST **a_new) { return ydlst_list__new (YDLST_LINKED , a_new); }
char ydlst_list_float (tLIST **a_new) { return ydlst_list__new (YDLST_FLOATER, a_new); }

char
ydlst_list_free         (tLIST **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_old       = NULL;
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
/*===----                      finding a list                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yDLST_list_count     (void) { return s_count; }

char
ydlst_list__line        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         c           =    0;
   tLINE      *x_line      = NULL;
   /*---(check if already ok)------------*/
   x_line = yDLST_line_current ();
   DEBUG_YDLST  yLOG_spoint  (x_line);
   if (x_line != NULL && x_line->parent == s_curr) {
      DEBUG_YDLST  yLOG_snote   ("already safe line");
      return 0;
   }
   /*---(force)--------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_curr->c_head);
   yDLST_line_restore (s_curr->c_head);
   /*---(show)---------------------------*/
   x_line = yDLST_line_current ();
   if (x_line != NULL) {
      DEBUG_YDLST  yLOG_snote   (x_line->title);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*--> find a list using sequential pos ----------------------------*/
yDLST_list_by_index     (int n, void **a_list, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_list != NULL)  *a_list = NULL;
   if (a_data != NULL)  *a_data = NULL;
   if (s_curr == NULL)   s_curr = s_head;
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
   /*---(move)---------------------------*/
   x_list = s_head;
   while (x_list != NULL) {
      if (c >= n)  break;
      x_list = x_list->m_next;
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
   /*---(save)---------------------------*/
   s_curr  = x_list;
   if (a_list != NULL)  *a_list = x_list;
   if (a_data != NULL)  *a_data = x_list->data;
   /*---(update line)--------------------*/
   ydlst_list__line ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_list_by_cursor    (char a_move, void **a_curr, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   DEBUG_YDLST  yLOG_spoint  (a_data);
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
   /*---(switch)-------------------------*/
   DEBUG_YDLST  yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_curr = s_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_curr = x_curr->m_prev;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      x_curr = x_curr->m_next;
      break;
   case YDLST_TAIL : case YDLST_DTAIL :
      x_curr = s_tail;
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (x_curr);
   /*---(check end)----------------------*/
   --rce;  if (x_curr == NULL) {
      /*---(bounce off ends)-------------*/
      if (a_move == YDLST_PREV)   x_curr = s_head;
      if (a_move == YDLST_NEXT)   x_curr = s_tail;
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
   /*---(update line)--------------------*/
   ydlst_list__line ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
}

char       /*--> find a list using its title ---------------------------------*/
yDLST_list_by_name      (char *a_title, void **a_list, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_list != NULL)  *a_list = NULL;
   if (a_data != NULL)  *a_data = NULL;
   if (s_curr == NULL)   s_curr = s_head;
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
   /*---(key data)-----------------------*/
   /*> DEBUG_YDLST  yLOG_spoint  (s_curr);                                            <*/
   /*> DEBUG_YDLST  yLOG_spoint  (s_tail);                                            <*/
   /*> DEBUG_YDLST  yLOG_sint    (s_count);                                           <*/
   /*---(search)-------------------------*/
   x_list = s_head;
   while (x_list != NULL) {
      if (x_list->title != NULL) {
         if (strcmp (x_list->title, a_title) == 0) break;
      }
      x_list = x_list->m_next;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(trouble)------------------------*/
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   s_curr  = x_list;
   if (a_list != NULL)  *a_list = s_curr;
   if (a_data != NULL)  *a_data = s_curr->data;
   /*---(update line)--------------------*/
   ydlst_list__line ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yDLST_list_by_ptr       (void *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_list);
   --rce;  if (a_list == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(key data)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_spoint  (s_tail);
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(search)-------------------------*/
   x_list = s_head;
   while (x_list != NULL) {
      if (x_list == a_list)   break;
      x_list = x_list->m_next;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   s_curr = (tLIST *) a_list;
   /*---(update line)--------------------*/
   ydlst_list__line ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*----: prepare a new list for use --------------------------------*/
yDLST_list_create       (char *a_title, void *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   tLIST      *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   rc = yDLST_list_by_name (a_title, NULL, NULL);
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
   rc = ydlst_list_new (&x_new);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->title = strdup (a_title);
   x_new->data  = a_data;
   /*---(make current)-------------------*/
   s_curr       = x_new;
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   /*---(sequence)-----------------------*/
   yDLST_seq_after  ("SEQ_ALPHA");
   yDLST_seq_before ("SEQ_OMEGA");
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: teardown the list after use ---------------------------*/
yDLST_list_destroy      (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   rc = yDLST_list_by_name (a_title, NULL, NULL);
   DEBUG_YDLST  yLOG_value   ("existing"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_note    ("list does not exist");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear the lines)-------------*/
   rc = ydlst_line_purge (s_curr);
   DEBUG_YDLST  yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(delete)-------------------------*/
   rc = ydlst_list_free (&s_curr);
   DEBUG_YDLST  yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(reset current)------------------*/
   s_curr = s_head;
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
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
   s_curr = s_head;
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   while (s_curr != NULL) {
      rc = yDLST_line_clearlist ();
      DEBUG_YDLST  yLOG_value   ("clearlist" , rc);
      rc = ydlst_list_free (&s_curr);
      DEBUG_YDLST  yLOG_value   ("del"       , rc);
      s_curr  = s_head;
      DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_list_init         (void)
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
ydlst_list_wrap         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   ydlst_list_purge ();
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

tLIST* yDLST_list_current   (void)          { return s_curr; }
char   yDLST_list_restore   (tLIST *x_list) { s_curr = x_list;  return 0; }



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
      o = s_head; while (o != NULL) { ++x_fore; o = o->m_next; }
      o = s_tail; while (o != NULL) { ++x_back; o = o->m_prev; }
      snprintf (unit_answer, LEN_RECD, "LIST count       : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = s_curr;
      if (o != NULL) {
         x_len = strlen (o->title);
         sprintf  (t, "[%.20s]", o->title);
         snprintf (unit_answer, LEN_RECD, "LIST current     : %2d%-22.22s %3d", x_len, t, o->c_count);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST current     :  0[]                       0");
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
         if (o->c_head != NULL) {
            sprintf  (s, "[%.20s]", o->c_head->title);
            sprintf  (r, "[%.20s]", o->c_tail->title);
         }
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) : %2d%-22.22s %3d  %-22.22s  %s", a_num, x_len, t, o->c_count, s, r);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) :  0[]                       0  []                      []", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




