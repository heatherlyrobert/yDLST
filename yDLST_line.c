/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all links)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tDLST_LINE *s_head      = NULL;  /* head node pointer                   */
static      tDLST_LINE *s_tail      = NULL;  /* tail node pointer                   */
static      tDLST_LINE *s_curr      = NULL;  /* pointer to current link             */
static      int         s_count     =    0;  /* number of links                     */



/*====================------------------------------------====================*/
/*===----                      fundamental actions                     ----===*/
/*====================------------------------------------====================*/
static void  o___PRIMATIVE_______o () { return; }

char
ydlst_line__wipe         (tDLST_LINE *a_dst)
{
   /*---(defense)--------------*/
   if (a_dst == NULL)  return -1;
   /*---(master)---------------*/
   a_dst->title   = NULL;
   a_dst->data    = NULL;
   /*---(lines)----------------*/
   a_dst->prev    = NULL;
   a_dst->next    = NULL;
   /*---(list)-----------------*/
   a_dst->parent  = NULL;
   a_dst->p_prev  = NULL;
   a_dst->p_next  = NULL;
   /*---(focus)----------------*/
   a_dst->focus   =  '-';
   a_dst->f_prev  = NULL;
   a_dst->f_next  = NULL;
   /*---(active)---------------*/
   a_dst->active  =  '-';
   a_dst->a_prev  = NULL;
   a_dst->a_next  = NULL;
   /*---(complete)-------------*/
   return 0;
}

tDLST_LINE*
ydlst_line__new         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tDLST_LINE *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(create)-------------------------*/
   while (++x_tries < 10) {
      x_new = (tDLST_LINE *) malloc (sizeof (tDLST_LINE));
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
   ydlst_line__wipe (x_new);
   /*---(add to list)--------------------*/
   if (s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("add first");
      s_head         = x_new;
      s_tail         = x_new;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append to end");
      x_new->prev    = s_tail;
      s_tail->next   = x_new;
      s_tail         = x_new;
   }
   /*---(update count)-------------------*/
   ++s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_new;
}

char
ydlst_line__del         (tDLST_LINE *a_old)
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
   DEBUG_YDLST  yLOG_spoint  (a_old->data);
   if (a_old->data != NULL)  free (a_old->data);
   /*---(free line)----------------------*/
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
/*===----                        attach/detach                         ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

char
ydlst_line__hook        (tDLST_LINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(tie to parent)---------------*/
   DEBUG_YDLST  yLOG_snote   ("parent");
   a_line->parent    = x_list;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->p_next    = NULL;
   a_line->p_prev    = NULL;
   /*---(into lists links)------------*/
   if (x_list->head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first line");
      x_list->head         = a_line;
      x_list->tail         = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append line");
      a_line->p_prev       = x_list->tail;
      x_list->tail->p_next = a_line;
      x_list->tail         = a_line;
   }
   /*---(update count)-------------------*/
   ++x_list->count;
   DEBUG_YDLST  yLOG_sint    (x_list->count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_line__unhook      (tDLST_LINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = a_line->parent;
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("not hooked to list");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(into lists links)------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->p_next != NULL)  a_line->p_next->p_prev = a_line->p_prev;
   else                         x_list->tail           = a_line->p_prev;
   if (a_line->p_prev != NULL)  a_line->p_prev->p_next = a_line->p_next;
   else                         x_list->head           = a_line->p_next;
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->p_next    = NULL;
   a_line->p_prev    = NULL;
   a_line->parent    = NULL;
   /*---(update count)-------------------*/
   --x_list->count;
   DEBUG_YDLST  yLOG_sint    (x_list->count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      external accessor                       ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESS__________o () { return; }

tDLST_LINE *ydlst_line_getcurr      (void)                { return s_curr; }
char        ydlst_line_setcurr      (tDLST_LINE *a_curr)  { s_curr = a_curr; return 0; }



/*====================------------------------------------====================*/
/*===----                      finding a list                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yDLST_line_allcount  (void) { return s_count; }

int
yDLST_line_count     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   DEBUG_YDLST  yLOG_sint    (x_list->count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->count;
}

void*
yDLST_line_list         (void)
{
   if (s_curr != NULL)   return s_curr->parent->data;
   return NULL;
}

void*      /*--> find a list using its title ---------------------------------*/
yDLST_line_seek         (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
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
   DEBUG_YDLST  yLOG_spoint  (x_list->head);
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   DEBUG_YDLST  yLOG_spoint  (x_list->tail);
   /*---(switch)-------------------------*/
   switch (a_pos) {
   case YDLST_HEAD :
      s_curr = x_list->head;
      break;
   case YDLST_PREV :
      if (s_curr != NULL && s_curr->parent != x_list) {
         s_curr = NULL;
         rc = -4;
      }
      else if (s_curr != NULL)   s_curr = s_curr->p_prev;
      else                       rc = -1;
      break;
   case YDLST_CURR :
      if (s_curr != NULL && s_curr->parent != x_list)  {
         s_curr = NULL;
         rc = -4;
      }
      break;
   case YDLST_NEXT :
      if (s_curr != NULL && s_curr->parent != x_list) {
         s_curr = NULL;
         rc = -4;
      }
      else if (s_curr != NULL)   s_curr = s_curr->p_next;
      else                       rc = -2;
      break;
   case YDLST_TAIL :
      s_curr = x_list->tail;
      break;
   default         :
      s_curr = NULL;
      rc = -3;
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
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->data;
}

void*      /*--> find a list using its title ---------------------------------*/
yDLST_line_fullseek     (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   DEBUG_YDLST  yLOG_spoint  (s_tail);
   /*---(switch)-------------------------*/
   switch (a_pos) {
   case YDLST_HEAD :
      s_curr = s_head;
      break;
   case YDLST_PREV :
      if (s_curr != NULL)   s_curr = s_curr->prev;
      else                  rc = -1;
      break;
   case YDLST_CURR :
      break;
   case YDLST_NEXT :
      if (s_curr != NULL)   s_curr = s_curr->next;
      else                  rc = -2;
      break;
   case YDLST_TAIL :
      s_curr = s_tail;
      break;
   default         :
      s_curr = NULL;
      rc = -3;
      break;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(save)---------------------------*/
   if (s_curr != NULL)  ydlst_list_setcurr (s_curr->parent);
   else                 ydlst_list_setcurr (NULL);
   /*---(check)--------------------------*/
   if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->data;
}

void*      /*--> find a list using its title ---------------------------------*/
yDLST_line_find         (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tDLST_LIST *x_list      = NULL;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_curr = NULL;
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (a_title);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (x_list->head);
   x_line = x_list->head;
   /*---(search)-------------------------*/
   while (x_line != NULL) {
      if (strcmp (x_line->title, a_title) == 0) {
         s_curr = x_line;
         break;
      }
      x_line = x_line->p_next;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(trouble)------------------------*/
   --rce;
   if (s_curr == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->data;
}

void*      /*--> find a list using sequential pos ----------------------------*/
yDLST_line_entry        (int a_pos, void **a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_sint    (a_pos);
   /*---(move)---------------------------*/
   x_line = s_head;
   while (x_line != NULL) {
      if (c >= a_pos)  break;
      x_line = x_line->next;
      ++c;
   }
   DEBUG_YDLST  yLOG_spoint  (x_line);
   DEBUG_YDLST  yLOG_sint    (c);
   /*---(check)--------------------------*/
   if (c != a_pos) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(save)---------------------------*/
   if (a_list != NULL)  *a_list = x_line->parent->data;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_line->data;
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
   tDLST_LIST *x_list      = NULL;
   tDLST_LINE *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_snote   ("no list is selected");
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(find list)----------------------*/
   yDLST_line_find  (a_title);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr != NULL) {
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
   x_new = ydlst_line__new ();
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(hook to list)-------------------*/
   rc = ydlst_line__hook (x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->title = a_title;
   DEBUG_YDLST  yLOG_info    ("->title"   , x_new->title);
   x_new->data  = a_data;
   DEBUG_YDLST  yLOG_point   ("->data"    , x_new->data);
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
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_line_find  (a_title);
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
   rc = ydlst_line__del (s_curr);
   DEBUG_YDLST  yLOG_value   ("del"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(depopulate)---------------------*/
   s_curr = NULL;
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
yDLST_line_clearlist    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LIST *x_list      = NULL;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no list is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_note    (x_list->title);
   /*---(walk through attached links)----*/
   s_curr = x_list->head;
   DEBUG_YDLST   yLOG_point   ("s_curr"    , s_curr);
   while (s_curr != NULL) {
      DEBUG_YDLST  yLOG_note    (s_curr->title);
      yDLST_focus_off  ();
      yDLST_active_off ();
      rc = ydlst_line__unhook (s_curr);
      rc = ydlst_line__del    (s_curr);
      s_curr  = x_list->head;
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
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ydlst_line__unit        (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tDLST_LINE *u           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "LINE unit        : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      u = s_head; while (u != NULL) { ++x_fore; u = u->next; }
      u = s_tail; while (u != NULL) { ++x_back; u = u->prev; }
      snprintf (unit_answer, LEN_RECD, "LINE count       : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      u = s_curr;
      if (u != NULL) {
         x_len = strlen (u->title);
         sprintf  (t, "[%.20s]", u->title);
         snprintf (unit_answer, LEN_RECD, "LINE current     : %2d%-22.22s   %c  %c", x_len, t, u->focus, u->active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE current     :  0[]                       -  -");
      }
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
         x_len = strlen (u->title);
         sprintf  (t, "[%.20s]", u->title);
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) : %2d%-22.22s   %c  %c", a_num, x_len, t, u->focus, u->active);
      } else {
         snprintf (unit_answer, LEN_RECD, "LINE entry  (%2d) :  0[]                       -  -", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




