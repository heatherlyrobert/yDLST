/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLINE      *S_head      = NULL;
static      tLINE      *S_tail      = NULL;
static      tLINE      *S_curr      = NULL;
static      int         S_count     =    0;



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
   DEBUG_YDLST  yLOG_schar   (a_line->n_active);
   --rce;  if (a_line->n_active == YDLST_ON) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->n_aprev    = NULL;
   a_line->n_anext    = NULL;
   /*---(hook it up)------------------*/
   DEBUG_YDLST  yLOG_snote   ("hook it up");
   if (S_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first");
      S_head          = a_line;
      S_tail          = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("append");
      a_line->n_aprev = S_tail;
      S_tail->n_anext = a_line;
      S_tail          = a_line;
   }
   /*---(update count)----------------*/
   ++S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(mark active)-----------------*/
   a_line->n_active = YDLST_ON;
   DEBUG_YDLST  yLOG_schar   (a_line->n_active);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 1;
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
   DEBUG_YDLST  yLOG_schar   (a_line->n_active);
   --rce;  if (a_line->n_active == YDLST_OFF) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->n_anext != NULL)  a_line->n_anext->n_aprev = a_line->n_aprev;
   else                          S_tail                   = a_line->n_aprev;
   if (a_line->n_aprev != NULL)  a_line->n_aprev->n_anext = a_line->n_anext;
   else                          S_head                   = a_line->n_anext;
   /*---(ground links)----------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->n_aprev    = NULL;
   a_line->n_anext    = NULL;
   /*---(update count)----------------*/
   --S_count;
   DEBUG_YDLST  yLOG_sint    (S_count);
   /*---(mark inactive)---------------*/
   a_line->n_active = YDLST_OFF;
   DEBUG_YDLST  yLOG_schar   (a_line->n_active);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 1;
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
   x_line = yDLST_line_current ();
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
   return 1;
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
   x_line = yDLST_line_current ();
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
   return 1;
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
   DEBUG_YDLST  yLOG_spoint  (S_head);
   --rce;  if (S_head == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   /*---(move)---------------------------*/
   x_line = S_head;
   while (x_line != NULL) {
      if (x_line->n_title != NULL) {
         if (strcmp (x_line->n_title, a_title) == 0) break;
      }
      x_line = x_line->n_anext;
   }
   /*---(trouble)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (S_curr);
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   /*---(update list)--------------------*/
   return 1;
}

int  yDLST_active_count  (void) { return S_count; }

char
yDLST_active_by_cursor  (char a_move, void **a_curr, void **a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_curr != NULL)  *a_curr = NULL;
   if (a_data != NULL)  *a_data = NULL;
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
   --rce;  switch (a_move) {
   case YDLST_HEAD : case YDLST_DHEAD :
      x_curr = S_head;
      break;
   case YDLST_PREV : case YDLST_DPREV :
      x_curr = x_curr->n_aprev;
      break;
   case YDLST_CURR : case YDLST_DCURR :
      x_curr = x_curr;
      break;
   case YDLST_NEXT : case YDLST_DNEXT :
      x_curr = x_curr->n_anext;
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
   /*---(normal result)------------------*/
   S_curr = x_curr;
   if (a_curr != NULL)  *a_curr = S_curr;
   if (a_data != NULL)  *a_data = S_curr->n_data;
   DEBUG_YDLST  yLOG_snote   (S_curr->n_title);
   /*---(update list/line)---------------*/
   yDLST_list_restore (S_curr->n_parent);
   yDLST_line_restore (S_curr);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return rc;
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
   x_line = S_head;
   while (x_line != NULL) {
      rc = ydlst_active__unhook  (x_line);
      x_line  = S_head;
   }
   /*---(complete)-----------------------*/
   return 1;
}

char
ydlst_active_init       (void)
{
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   S_head    = NULL;
   S_tail    = NULL;
   S_count   =    0;
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
   S_head    = NULL;
   S_tail    = NULL;
   S_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

tLINE* ydlst_active_current (void)          { return S_curr; }
char   ydlst_active_restore (tLINE *x_line) { S_curr = x_line;  return 0; }



/*====================------------------------------------====================*/
/*===----                    reporting and output                      ----===*/
/*====================------------------------------------====================*/
static void  o___REPORTING_______o () { return; }

char*
ydlst_active_audit      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tLINE      *o           = NULL;
   o = S_head; while (o != NULL) { ++x_fore; o = o->n_anext; }
   o = S_tail; while (o != NULL) { ++x_back; o = o->n_aprev; }
   snprintf (unit_answer, LEN_RECD, "actv audit ::  ····  ····  %3dc  %3df  %3db", S_count, x_fore, x_back);
   o = S_head;
   ystrlcat (unit_answer, "  å ", LEN_RECD);
   while (o != NULL) {
      ystrlcat (unit_answer, o->n_title, LEN_RECD);
      ystrlcat (unit_answer, " "       , LEN_RECD);
      o = o->n_anext;
   }
   ystrlcat (unit_answer, "æ", LEN_RECD);
   return unit_answer;
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
      o = S_head; while (o != NULL) { ++x_fore; o = o->n_anext; }
      o = S_tail; while (o != NULL) { ++x_back; o = o->n_aprev; }
      snprintf (unit_answer, LEN_RECD, "ACTIVE count     : %3dc  %3df  %3db", S_count, x_fore, x_back);
      return unit_answer;
   }
   else if (strcmp (a_question, "current")     == 0) {
      o = S_curr;
      if (o != NULL) {
         x_len = strlen (o->n_title);
         sprintf  (t, "[%.20s]", o->n_title);
         snprintf (unit_answer, LEN_RECD, "ACTIVE current   : %2d%-22.22s   %c  %c  %c", x_len, t, (o->n_parent == NULL) ? YDLST_OFF : YDLST_ON, o->n_focus, o->n_active);
      } else {
         snprintf (unit_answer, LEN_RECD, "ACTIVE current   :  0[]                       -  -  -");
      }
      return unit_answer;
   }
   o = S_head;
   while (o != NULL) {
      if (c >= a_num)  break;
      ++c;
      o = o->n_anext;
   }
   if (strcmp (a_question, "entry"     )     == 0) {
      if (o != NULL) {
         x_len = strlen (o->n_title);
         sprintf  (t, "[%.20s]", o->n_title);
         snprintf (unit_answer, LEN_RECD, "ACTIVE entry(%2d) : %2d%-22.22s   %c  %c  %c", a_num, x_len, t, (o->n_parent == NULL) ? YDLST_OFF : YDLST_ON, o->n_focus, o->n_active);
      } else {
         snprintf (unit_answer, LEN_RECD, "ACTIVE entry(%2d) :  0[]                       -  -  -", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



