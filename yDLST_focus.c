/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tDLST_LINE *s_head      = NULL;
static      tDLST_LINE *s_tail      = NULL;
static      int         s_count     =    0;



/*====================------------------------------------====================*/
/*===----                       attach and detach                      ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

char
ydlst_focus__hook       (tDLST_LINE *a_line)
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
   /*---(check for already on)-----------*/
   DEBUG_YDLST  yLOG_schar   (a_line->focus);
   --rce;  if (a_line->focus == 'y') {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare links)------------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_line->f_next    = NULL;
   a_line->f_prev    = NULL;
   /*---(hook it up)---------------------*/
   DEBUG_YDLST  yLOG_snote   ("hook it up");
   if (s_head == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first");
      s_head         = a_line;
      s_tail         = a_line;
   } else {
      DEBUG_YDLST  yLOG_snote   ("appende");
      a_line->f_prev = s_tail;
      s_tail->f_next = a_line;
      s_tail         = a_line;
   }
   /*---(update count)-------------------*/
   ++s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(mark focused)-------------------*/
   a_line->focus = 'y';
   DEBUG_YDLST  yLOG_schar   (a_line->focus);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_focus__unhook     (tDLST_LINE *a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for already off)----------*/
   DEBUG_YDLST  yLOG_schar   (a_line->focus);
   --rce;  if (a_line->focus == '-') {
      DEBUG_YDLST   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   DEBUG_YDLST  yLOG_snote   ("unhook");
   if (a_line->f_next != NULL)  a_line->f_next->f_prev = a_line->f_prev;
   else                         s_tail                 = a_line->f_prev;
   if (a_line->f_prev != NULL)  a_line->f_prev->f_next = a_line->f_next;
   else                         s_head                 = a_line->f_next;
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(mark unfocused)-----------------*/
   a_line->focus = '-';
   DEBUG_YDLST  yLOG_schar   (a_line->focus);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

char       /*-->-: add the link to the focus list ----------------------------*/
yDLST_focus_on          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get current line)---------------*/
   x_line = ydlst_line_getcurr  ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no line is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_focus__hook    (x_line);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: remove the link to the focus list -------------------------*/
yDLST_focus_off         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get current line)---------------*/
   x_line = ydlst_line_getcurr  ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_YDLST   yLOG_note    ("no line is selected");
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_focus__unhook  (x_line);
   DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YDLST   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*--> verify line is focused --------------------------------------*/
yDLST_focus_check       (char *a_title, void **a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YDLST  yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title == NULL) {
      DEBUG_YDLST  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_info    ("a_title"   , a_title);
   /*---(walk actives)-------------------*/
   for (x_line = s_head; x_line != NULL; x_line = x_line->f_next) {
      DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
      DEBUG_YDLST  yLOG_info    ("->title"   , x_line->title);
      if (x_line->title [0] != a_title [0])      continue;
      if (strcmp (x_line->title, a_title) != 0)  continue;
      DEBUG_YDLST  yLOG_note    ("FOUND");
      DEBUG_YDLST  yLOG_point   ("file"      , x_line->parent);
      DEBUG_YDLST  yLOG_info    ("->title"   , x_line->parent->title);
      DEBUG_YDLST  yLOG_point   ("->data"    , x_line->parent->data);
      if (a_list != NULL)  *a_list = x_line->parent->data;
      DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      cursor positioning                      ----===*/
/*====================------------------------------------====================*/
static void  o___CURSOR__________o () { return; }

int  yDLST_focus_count   (void) { return s_count; }

void*      /*--> find an focus entry -----------------------------------------*/
yDLST_focus_seek        (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(get current line)---------------*/
   x_line = ydlst_line_getcurr  ();
   /*---(prepare)------------------------*/
   DEBUG_YDLST  yLOG_spoint  (s_head);
   DEBUG_YDLST  yLOG_spoint  (x_line);
   DEBUG_YDLST  yLOG_spoint  (s_tail);
   /*---(switch)-------------------------*/
   switch (a_pos) {
   case YDLST_HEAD :
      x_line = s_head;
      break;
   case YDLST_PREV :
      if (x_line != NULL)   x_line = x_line->f_prev;
      else                  rc = -1;
      break;
   case YDLST_CURR :
      break;
   case YDLST_NEXT :
      if (x_line != NULL)   x_line = x_line->f_next;
      else                  rc = -2;
      break;
   case YDLST_TAIL :
      x_line = s_tail;
      break;
   default         :
      x_line = NULL;
      rc = -3;
      break;
   }
   DEBUG_YDLST  yLOG_spoint  (x_line);
   /*---(update current)-----------------*/
   ydlst_line_setcurr (x_line);
   if (x_line != NULL)  ydlst_list_setcurr (x_line->parent);
   else                 ydlst_list_setcurr (NULL);
   /*---(check)--------------------------*/
   if (rc < 0) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rc);
      return NULL;
   }
   --rce;  if (x_line == NULL) {
      DEBUG_YDLST  yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return x_line->data;
}



char       /*----: clear all focus from lines --------------------------------*/
yDLST_focus_clearall    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tDLST_LINE *x_line      = NULL;
   /*---(walk through attached links)----*/
   x_line = s_head;
   while (x_line != NULL) {
      rc = ydlst_focus__unhook  (x_line);
      x_line  = s_head;
   }
   /*---(complete)-----------------------*/
   return 0;
}



char
ydlst_focus_init        (void)
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
ydlst_focus_wrap        (void)
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



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ydlst_focus__unit       (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_fore      =    0;
   int         x_back      =    0;
   tDLST_LINE *u           = NULL;
   int         c           =    0;
   char        t           [LEN_RECD]  = "[]";
   int         x_len       =    0;
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "FOCUS unit       : question unknown");
   /*---(simple)-------------------------*/
   if  (strcmp (a_question, "count"     )     == 0) {
      u = s_head; while (u != NULL) { ++x_fore; u = u->f_next; }
      u = s_tail; while (u != NULL) { ++x_back; u = u->f_prev; }
      snprintf (unit_answer, LEN_RECD, "FOCUS count      : %3dc  %3df  %3db", s_count, x_fore, x_back);
      return unit_answer;
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


