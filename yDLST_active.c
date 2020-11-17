/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLINE      *s_head      = NULL;
static      tLINE      *s_tail      = NULL;
static      tLINE      *s_curr      = NULL;
static      int         s_count     =    0;



/*====================------------------------------------====================*/
/*===----                       attach and detach                      ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

char
ydlst_active__hook      (tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)---------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for already on)--------*/
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   --rce;  if (a_line->active == 'y') {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->a_next    = NULL;
   a_line->a_prev    = NULL;
   /*---(hook it up)------------------*/
   DEBUG_YDLST  yLOG_snote   ("hook it up");
   if (s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first");
      s_head         = a_line;
      s_tail         = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append");
      a_line->a_prev = s_tail;
      s_tail->a_next = a_line;
      s_tail         = a_line;
   }
   /*---(update count)----------------*/
   ++s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(mark active)-----------------*/
   a_line->active = 'y';
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_active__unhook    (tLINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)---------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for already off)-------*/
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   --rce;  if (a_line->active == '-') {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->a_next != NULL)  a_line->a_next->a_prev = a_line->a_prev;
   else                         s_tail                 = a_line->a_prev;
   if (a_line->a_prev != NULL)  a_line->a_prev->a_next = a_line->a_next;
   else                         s_head                 = a_line->a_next;
   /*---(update count)----------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(mark inactive)---------------*/
   a_line->active = '-';
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*-->-: add the link to the active list ---------------------------*/
yDLST_active_on         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get current line)---------------*/
   x_line = ydlst_line_current ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no line is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_active__hook   (x_line);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: remove the link to the active list ------------------------*/
yDLST_active_off        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get current line)---------------*/
   x_line = ydlst_line_current ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no line is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_active__unhook (x_line);
   DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char       /*--> find a list using its title ---------------------------------*/
yDLST_active_check      (char *a_title)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tLINE      *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
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
      return 0;
   }
   /*---(move)---------------------------*/
   x_line = s_head;
   while (x_line != NULL) {
      if (x_line->title != NULL) {
         if (strcmp (x_line->title, a_title) == 0) break;
      }
      x_line = x_line->a_next;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 1;
}

int  yDLST_active_count  (void) { return s_count; }

char
yDLST_active_by_cursor  (char a_move, void **a_curr, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLIST      *x_list      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_curr != NULL)  *a_curr = NULL;
   if (a_data != NULL)  *a_data = NULL;
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   --rce;  if (s_head == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(switch)-------------------------*/
   --rce;  switch (a_move) {
   case '[' :
      s_curr = s_head;
      break;
   case '<' :
      if (s_curr != NULL)  s_curr = s_curr->a_prev;
      break;
   case '-' :
      break;
   case '>' :
      if (s_curr != NULL)  s_curr = s_curr->a_next;
      break;
   case ']' :
      s_curr = s_tail;
      break;
   default         :
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (s_curr);
   /*---(bounce off ends)----------------*/
   --rce;  if (s_curr == NULL) {
      if (a_move == '<')  s_curr = s_head;
      if (a_move == '>')  s_curr = s_tail;
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   if (a_curr != NULL)  *a_curr = s_curr;
   if (a_data != NULL)  *a_data = s_curr->data;
   DEBUG_YDLST  yLOG_snote   (s_curr->title);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     program level                            ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char       /*----: clear all active from lines -------------------------------*/
yDLST_active_clearall   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tLINE      *x_line      = NULL;
   /*---(walk through attached links)----*/
   x_line = s_head;
   while (x_line != NULL) {
      rc = ydlst_active__unhook  (x_line);
      x_line  = s_head;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ydlst_active_init       (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   s_head    = NULL;
   s_tail    = NULL;
   s_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ydlst_active_wrap       (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   yDLST_active_clearall ();
   s_head    = NULL;
   s_tail    = NULL;
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
ydlst_active__unit      (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLINE      *o           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "ACTIVE unit      : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      o = s_head; while (o != NULL) { ++x_fore; o = o->a_next; }
      o = s_tail; while (o != NULL) { ++x_back; o = o->a_prev; }
      snprintf (unit_answer, LEN_RECD, "ACTIVE count     : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   o = s_head;
   while (o != NULL) {
      if (c >= a_num)  break;
      ++c;
      o = o->a_next;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         x_len = strlen (o->title);
         sprintf  (t, "[%.20s]", o->title);
         snprintf (unit_answer, LEN_RECD, "ACTIVE entry(%2d) : %2d%-22.22s   %c  %c  %c", a_num, x_len, t, (o->parent == NULL) ? '-' : 'y', o->focus, o->active);
      } else {
         snprintf (unit_answer, LEN_RECD, "ACTIVE entry(%2d) :  0[]                       -  -  -", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



