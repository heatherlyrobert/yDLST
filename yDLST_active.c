/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tLINE      *s_head      = NULL;
static      tLINE      *s_tail      = NULL;
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
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for already on)--------*/
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   --rce;  if (a_line->active == 'y') {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
      DEBUG_YDLST  yLOG_snote   ("appende");
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
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(defense)---------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_line);
   --rce;  if (a_line == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for already off)-------*/
   DEBUG_YDLST  yLOG_schar   (a_line->active);
   --rce;  if (a_line->active == '-') {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
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
   x_line = ydlst_line_getcurr  ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_INPT   yLOG_note    ("no line is selected");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_active__hook   (x_line);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
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
   x_line = ydlst_line_getcurr  ();
   DEBUG_YDLST  yLOG_point   ("x_line"    , x_line);
   --rce;  if (x_line  == NULL) {
      DEBUG_INPT   yLOG_note    ("no line is selected");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ydlst_active__unhook (x_line);
   DEBUG_YDLST  yLOG_value   ("unhook"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      cursor positioning                      ----===*/
/*====================------------------------------------====================*/
static void  o___CURSOR__________o () { return; }

void*      /*--> find an active entry ----------------------------------------*/
yDLST_active_seek       (char a_pos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINE      *x_line      = NULL;
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
      if (x_line != NULL)   x_line = x_line->a_prev;
      else                  rc = -1;
      break;
   case YDLST_CURR :
      break;
   case YDLST_NEXT :
      if (x_line != NULL)   x_line = x_line->a_next;
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
   s_head    = NULL;
   s_tail    = NULL;
   s_count   =    0;
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



