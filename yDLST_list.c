/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all lists)--------------*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tDLST_LIST *s_head      = NULL;   /* head node pointer                   */
static      tDLST_LIST *s_tail      = NULL;   /* tail node pointer                   */
static      tDLST_LIST *s_curr      = NULL;   /* pointer to current list             */
static      int         s_count     =    0;   /* number of lists                     */





/*====================------------------------------------====================*/
/*===----                      fundamental actions                     ----===*/
/*====================------------------------------------====================*/
static void  o___PRIMATIVE_______o () { return; }

char
ydlst_list__wipe         (tDLST_LIST *a_dst)
{
   /*---(defense)--------------*/
   if (a_dst == NULL)  return -1;
   /*---(master)---------------*/
   a_dst->title   = NULL;
   a_dst->data    = NULL;
   /*---(list of lists)--------*/
   a_dst->prev    = NULL;
   a_dst->next    = NULL;
   /*---(list of lines)--------*/
   a_dst->head    = NULL;
   a_dst->tail    = NULL;
   a_dst->count   =    0;
   /*---(list of lines)--------*/
   a_dst->p_head  = NULL;
   a_dst->p_tail  = NULL;
   a_dst->p_count =    0;
   a_dst->s_head  = NULL;
   a_dst->s_tail  = NULL;
   a_dst->s_count =    0;
   /*---(complete)-------------*/
   return 0;
}

tDLST_LIST*
ydlst_list_new          (char a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tDLST_LIST *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(create)-------------------------*/
   while (++x_tries < 10) {
      x_new = (tDLST_LIST *) malloc (sizeof (tDLST_LIST));
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
   ydlst_list__wipe (x_new);
   /*---(check for floater)--------------*/
   if (a_link == YDLST_FLOATER) {
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return x_new;
   }
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
ydlst_list_del          (tDLST_LIST *a_old, char a_link)
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
      return rce;
   }
   /*---(check for floater)--------------*/
   if (a_link == YDLST_FLOATER) {
      DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(remove from lists)--------------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (a_old->next != NULL)  a_old->next->prev = a_old->prev;
   else                      s_tail            = a_old->prev;
   if (a_old->prev != NULL)  a_old->prev->next = a_old->next;
   else                      s_head            = a_old->next;
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old->data);
   if (a_old->data != NULL)  free (a_old->data);
   a_old->data = NULL;
   /*---(free list)----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old);
   free (a_old);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      external accessor                       ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESS__________o () { return; }

tDLST_LIST *ydlst_list_getcurr      (void)           { return s_curr; }
char        ydlst_list_setcurr      (tDLST_LIST *a_curr)  { s_curr = a_curr;  return 0; }



/*====================------------------------------------====================*/
/*===----                      finding a list                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  yDLST_list_count     (void) { return s_count; }

void*      /*--> find a list using its title ---------------------------------*/
yDLST_list_seek         (char a_pos)
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
yDLST_list_find         (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tDLST_LIST *x_list      = NULL;
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
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   x_list = s_head;
   /*---(search)-------------------------*/
   while (x_list != NULL) {
      if (strcmp (x_list->title, a_title) == 0) {
         s_curr = x_list;
         break;
      }
      x_list = x_list->next;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(trouble)------------------------*/
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->data;
}

void*      /*--> find a list using sequential pos ----------------------------*/
yDLST_list_entry        (int a_pos, int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_sint    (a_pos);
   /*---(move)---------------------------*/
   x_list = s_head;
   while (x_list != NULL) {
      if (c >= a_pos)  break;
      x_list = x_list->next;
      ++c;
   }
   DEBUG_YDLST  yLOG_spoint  (x_list);
   DEBUG_YDLST  yLOG_sint    (c);
   /*---(check)--------------------------*/
   if (c != a_pos) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (x_list == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(save)---------------------------*/
   if (a_count != NULL)  *a_count = x_list->count;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_list->data;
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
   tDLST_LIST *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_list_find  (a_title);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr != NULL) {
      DEBUG_YDLST   yLOG_note    ("list already exists");
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
   x_new = ydlst_list_new (YDLST_LINKED);
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
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
   /*---(sequence)-----------------------*/
   yDLST_seq_after  ("SEQ_ALPHA");
   ydlst_seq_before ("SEQ_OMEGA");
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
   tDLST_LIST *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_list_find  (a_title);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr == NULL) {
      DEBUG_YDLST   yLOG_note    ("list could not be found");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear the lines)-------------*/
   rc = yDLST_line_clearlist ();
   DEBUG_YDLST  yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(delete)-------------------------*/
   rc = ydlst_list_del (s_curr, YDLST_LINKED);
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
      rc = ydlst_list_del  (s_curr, YDLST_LINKED);
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
   tDLST_LIST *u           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "LIST unit        : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      u = s_head; while (u != NULL) { ++x_fore; u = u->next; }
      u = s_tail; while (u != NULL) { ++x_back; u = u->prev; }
      snprintf (unit_answer, LEN_RECD, "LIST count       : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      u = s_curr;
      if (u != NULL) {
         x_len = strlen (u->title);
         sprintf  (t, "[%.20s]", u->title);
         snprintf (unit_answer, LEN_RECD, "LIST current     : %2d%-22.22s %3d", x_len, t, u->count);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST current     :  0[]                       0");
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
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) : %2d%-22.22s %3d", a_num, x_len, t, u->count);
      } else {
         snprintf (unit_answer, LEN_RECD, "LIST entry  (%2d) :  0[]                       0", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}




