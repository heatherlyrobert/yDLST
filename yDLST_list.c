/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"



/*---(list of all lists)--------------*/
static tLIST    *s_head   = NULL;   /* head node pointer                   */
static tLIST    *s_tail   = NULL;   /* tail node pointer                   */
static tLIST    *s_curr   = NULL;   /* pointer to current list             */
static int       s_count  =    0;   /* number of lists                     */





/*====================------------------------------------====================*/
/*===----                      fundamental actions                     ----===*/
/*====================------------------------------------====================*/
static void  o___PRIMATIVE_______o () { return; }

char
ydlst_list__wipe         (tLIST *a_dst)
{
   /*---(defense)--------------*/
   if (a_dst == NULL)  return -1;
   /*---(master)---------------*/
   a_dst->title = NULL;
   a_dst->data  = NULL;
   /*---(list of lists)--------*/
   a_dst->prev  = NULL;
   a_dst->next  = NULL;
   /*---(list of lines)--------*/
   a_dst->head  = NULL;
   a_dst->tail  = NULL;
   a_dst->count =    0;
   /*---(list of lines)--------*/
   a_dst->preds = NULL;
   a_dst->npred =    0;
   a_dst->succs = NULL;
   a_dst->nsucc =    0;
   /*---(complete)-------------*/
   return 0;
}

tLIST*
ydlst_list__new         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tLIST      *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(create)-------------------------*/
   while (++x_tries < 10) {
      x_new = (tLIST *) malloc (sizeof (tLIST));
      if (x_new != NULL)     break;
   }
   DEBUG_YDLST  yLOG_sint    (x_tries);
   DEBUG_YDLST  yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(wipe)---------------------------*/
   DEBUG_YDLST  yLOG_snote   ("wipe");
   ydlst_list__wipe (x_new);
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
ydlst_list__del         (tLIST *a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(remove from main DLL)-----------*/
   DEBUG_YDLST  yLOG_snote   ("remove from list");
   if (a_old->next != NULL)  a_old->next->prev = a_old->prev;
   else                      s_tail            = a_old->prev;
   if (a_old->prev != NULL)  a_old->prev->next = a_old->next;
   else                      s_head            = a_old->next;
   /*---(free data)----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_old->title);
   if (a_old->title)    free (a_old->title);
   DEBUG_YDLST  yLOG_spoint  (a_old);
   free (a_old);
   DEBUG_YDLST  yLOG_spoint  (a_old);
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      external accessor                       ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESS__________o () { return; }

tLIST      *ydlst_list_getcurr      (void)           { return s_curr; }
char        ydlst_list_setcurr      (tLIST *a_curr)  { s_curr = a_curr;  return 0; }



/*====================------------------------------------====================*/
/*===----                      finding a list                          ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

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
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_curr = NULL;
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
   --rce;
   if (s_curr == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return s_curr->data;
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
   tLIST      *x_new       = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_list_find  (a_title);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr != NULL) {
      DEBUG_INPT   yLOG_note    ("list already exists");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_title);
   --rce;  if (a_title  == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_snote   (a_title);
   /*---(create)-------------------------*/
   x_new = ydlst_list__new ();
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->title  = strdup (a_title);
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
yDLST_list_destroy      (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(find list)----------------------*/
   yDLST_list_find  (a_title);
   DEBUG_YDLST  yLOG_point   ("s_curr"    , s_curr);
   --rce;  if (s_curr == NULL) {
      DEBUG_INPT   yLOG_note    ("list could not be found");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear the lines)-------------*/
   /*> rc = yDLST_purge (s_curr);                                                     <*/
   DEBUG_YDLST  yLOG_value   ("purge"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(delete)-------------------------*/
   rc = ydlst_list__del (s_curr);
   DEBUG_YDLST  yLOG_value   ("del"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
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
ydlst_list__purge       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(walk through attached links)----*/
   x_list = s_head;
   while (x_list != NULL) {
      /*> rc = ydlst_line_purge (x_list);                                             <*/
      rc = ydlst_list__del  (x_list);
      x_list  = s_head;
   }
   /*---(complete)-----------------------*/
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
   ydlst_list__purge ();
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
   tLIST      *u           = NULL;
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




