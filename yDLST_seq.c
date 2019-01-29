/*===========================[[ start-of-code ]]==============================*/
#include   "yDLST.h"
#include   "yDLST_priv.h"



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
static      tSEQ       *s_head      = NULL;
static      tSEQ       *s_tail      = NULL;
static      int         s_count     =    0;



/*====================------------------------------------====================*/
/*===----                      fundamental actions                     ----===*/
/*====================------------------------------------====================*/
static void  o___PRIMATIVE_______o () { return; }

char
ydlst_seq__wipe          (tSEQ *a_dst)
{
   /*---(defense)--------------*/
   if (a_dst == NULL)  return -1;
   /*---(master)---------------*/
   a_dst->pred  = NULL;
   a_dst->same  = NULL;
   a_dst->succ  = NULL;
   /*---(seq)------------------*/
   a_dst->prev  = NULL;
   a_dst->next  = NULL;
   /*---(complete)-------------*/
   return 0;
}

tSEQ*
ydlst_seq__new          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   int         rc          =    0;
   int         x_tries     =    0;
   tSEQ       *x_new       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(create)-------------------------*/
   while (++x_tries < 10) {
      x_new = (tSEQ *) malloc (sizeof (tSEQ));
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
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return x_new;
}

char
ydlst_seq__del          (tSEQ *a_old)
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
   DEBUG_YDLST  yLOG_spoint  (a_old);
   free (a_old);
   /*---(update count)-------------------*/
   --s_count;
   DEBUG_YDLST  yLOG_sint    (s_count);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        major actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ATTACH__________o () { return; }

char
ydlst_seq__hook         (tLIST *a_list, tSEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_list);
   --rce;  if (a_list  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YDLST  yLOG_spoint  (a_seq);
   --rce;  if (a_seq  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare links)---------------*/
   DEBUG_YDLST  yLOG_snote   ("clear");
   a_seq->same       = NULL;
   /*---(into lists links)------------*/
   if (a_list->preds == NULL) {
      DEBUG_YDLST  yLOG_snote   ("first seq");
      a_list->preds        = a_seq;
   } else {
      DEBUG_YDLST  yLOG_snote   ("prepend seq");
      a_seq->same          = a_list->preds;
      a_list->preds        = a_seq;
   }
   /*---(update count)-------------------*/
   ++a_list->npred;
   DEBUG_YDLST  yLOG_sint    (a_list->npred);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ydlst_seq__unhook       (tSEQ *a_seq)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rce         =  -10;
   tLIST      *x_list      = NULL;
   tSEQ       *x_seq       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_senter  (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YDLST  yLOG_spoint  (a_seq);
   --rce;  if (a_seq  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_list = a_seq->pred;
   DEBUG_YDLST  yLOG_spoint  (x_list);
   --rce;  if (x_list  == NULL) {
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find seq)--------------------*/
   x_seq = x_list->preds;
   if (x_seq == a_seq) {
      DEBUG_YDLST  yLOG_snote   ("at head");
      x_list->preds = a_seq->same;
   } else {
      DEBUG_YDLST  yLOG_snote   ("find");
      while (x_seq != NULL) {
         if (x_seq->same == a_seq)  break;
         x_seq = x_seq->same;
      }
      DEBUG_YDLST  yLOG_spoint  (x_seq);
      if (x_seq == NULL) {
         DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_seq->same = x_seq->next;
   }
   /*---(update count)-------------------*/
   --x_list->npred;
   DEBUG_YDLST  yLOG_sint    (x_list->npred);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_sexit   (__FUNCTION__);
   return 0;
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
   tSEQ       *x_new       = NULL;
   tLIST      *x_list      = NULL;
   tLIST      *x_before    = NULL;
   /*---(begin)--------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(get list)-----------------------*/
   x_list = ydlst_list_getcurr  ();
   --rce;  if (x_list  == NULL) {
      DEBUG_INPT   yLOG_snote   ("no list is selected");
      DEBUG_INPT   yLOG_sexitr  (__FUNCTION__, rce);
      return NULL;
   }
   DEBUG_YDLST  yLOG_snote   (x_list->title);
   /*---(find list)----------------------*/
   yDLST_list_find  (a_before);
   x_before = ydlst_list_getcurr  ();
   DEBUG_YDLST  yLOG_point   ("x_before"  , x_before);
   --rce;  if (x_before == NULL) {
      ydlst_list_setcurr  (x_list);
      DEBUG_INPT   yLOG_note    ("could not find before list");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(create)-------------------------*/
   x_new = ydlst_seq__new ();
   DEBUG_YDLST  yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   x_new->pred = x_before;
   x_new->succ = x_list;
   /*---(hook)---------------------------*/
   rc = ydlst_seq__hook (x_before, x_new);
   DEBUG_YDLST  yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make current)-------------------*/
   ydlst_list_setcurr  (x_list);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}



char
ydlst_seq_init          (void)
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
ydlst_seq_wrap          (void)
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
/*===----                            ties list                         ----===*/
/*====================------------------------------------====================*/
static void  o___TIES____________o () { return; }

/*> char       /+----: tie to links together (directionally) --------------------+/                                          <* 
 *> yDLST_tie          (int a_up, int a_down, void *a_data)                                                                  <* 
 *> {                                                                                                                        <* 
 *>    /+---(locals)-------------------------+/                                                                              <* 
 *>    tLINK    *xup       = NULL;                                                                                           <* 
 *>    tLINK    *xdown     = NULL;                                                                                           <* 
 *>    tTIES    *xtie      = NULL;                                                                                           <* 
 *>    tTIES    *curr      = NULL;                                                                                           <* 
 *>    tTIES    *next      = NULL;                                                                                           <* 
 *>    int       i         = 0;                                                                                              <* 
 *>    /+---(defence : circular)-------------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("begin TIE (%4d) to (%4d)\n", a_up, a_down); )                                                   <* 
 *>       if (a_up  == a_down)                          return -1;                                                           <* 
 *>    /+---(sort out upstream)--------------+/                                                                              <* 
 *>    if (a_up   == -1) {                                                                                                   <* 
 *>       xup   = h_tree;                                                                                                    <* 
 *>    } else {                                                                                                              <* 
 *>       if (p_links == NULL || a_up   != c_links) {                                                                        <* 
 *>          xup   = yDLST__link_find (a_up  , 'n');                                                                         <* 
 *>          if (xup   == NULL)                      return -2;                                                              <* 
 *>       } else  xup   = p_links;                                                                                           <* 
 *>    }                                                                                                                     <* 
 *>    DEBUG_TIES ( printf ("   1) found up link   (%4d) %9p\n", a_up, xup); )                                               <* 
 *>       /+---(sort out downstream)------------+/                                                                           <* 
 *>       if (a_down == -1) {                                                                                                <* 
 *>          xdown = t_tree;                                                                                                 <* 
 *>       } else {                                                                                                           <* 
 *>          if (p_links == NULL || a_down != c_links) {                                                                     <* 
 *>             xdown = yDLST__link_find (a_down, 'n');                                                                      <* 
 *>             if (xdown == NULL)                      return -3;                                                           <* 
 *>          } else  xdown = p_links;                                                                                        <* 
 *>       }                                                                                                                  <* 
 *>    DEBUG_TIES ( printf ("   2) found down link (%4d) %9p\n", a_down, xdown); )                                           <* 
 *>       /+---(check for endpoint links)-------+/                                                                           <* 
 *>       if (xup == h_tree || xdown == t_tree) {                                                                            <* 
 *>          if (xup   == h_tree && xdown->n_ups > 0) {                                                                      <* 
 *>             DEBUG_TIES ( printf ("   3) unnecessary h_tree link request, stop\n"); )                                     <* 
 *>                return -4;                                                                                                <* 
 *>          } else if (xdown == t_tree && xup->n_downs > 0) {                                                               <* 
 *>             DEBUG_TIES ( printf ("   3) unnecessary t_tree link request, stop\n"); )                                     <* 
 *>                return -5;                                                                                                <* 
 *>          }                                                                                                               <* 
 *>          DEBUG_TIES ( printf ("   3) h_tree/t_tree fine, continue\n"); )                                                 <* 
 *>       } else {                                                                                                           <* 
 *>          DEBUG_TIES ( printf ("   3) not a h_tree or t_tree link request\n"); )                                          <* 
 *>       }                                                                                                                  <* 
 *>    /+---(look for existing link)---------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("   4) look for existing link :: "); )                                                           <* 
 *>       next = xup->h_downs;                                                                                               <* 
 *>    while (next != NULL) {                                                                                                <* 
 *>       if (next->down == xdown) {                                                                                         <* 
 *>          DEBUG_TIES ( printf ("exists, stop\n"); )                                                                       <* 
 *>             return  1;                                                                                                   <* 
 *>       }                                                                                                                  <* 
 *>       next = next->f_downs;                                                                                              <* 
 *>    }                                                                                                                     <* 
 *>    DEBUG_TIES ( printf ("not found, continue\n"); )                                                                      <* 
 *>       /+---(create link)--------------------+/                                                                           <* 
 *>       DEBUG_TIES ( printf ("   5) malloc the tie\n"); )                                                                  <* 
 *>       for (i = 0; i < 3; ++i) {                                                                                          <* 
 *>          xtie  = (tTIES *) malloc(sizeof(tTIES));                                                                        <* 
 *>          if (xtie  != NULL) break;                                                                                       <* 
 *>       }                                                                                                                  <* 
 *>    if (xtie  == NULL)                            return -6;                                                              <* 
 *>    /+---(into list of all links)---------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("   6) attach tie into dll\n"); )                                                                <* 
 *>       xtie->f_ties   = NULL;                                                                                             <* 
 *>    xtie->b_ties   = NULL;                                                                                                <* 
 *>    if (t_ties == NULL) {    /+ first link +/                                                                             <* 
 *>       h_ties            = xtie;                                                                                          <* 
 *>       t_ties            = xtie;                                                                                          <* 
 *>    } else {                /+ link 2-n   +/                                                                              <* 
 *>       xtie->b_ties      = t_ties;                                                                                        <* 
 *>       t_ties->f_ties    = xtie;                                                                                          <* 
 *>       t_ties            = xtie;                                                                                          <* 
 *>    }                                                                                                                     <* 
 *>    ++n_ties;                                                                                                             <* 
 *>    /+---(tie upstream)-------------------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("   7) tie to up link down sll\n"); )                                                            <* 
 *>       xtie->up        = xup;                                                                                             <* 
 *>    xtie->f_downs   = NULL;                                                                                               <* 
 *>    if (xup->h_downs == NULL) xup->h_downs = xtie;                                                                        <* 
 *>    else {                                                                                                                <* 
 *>       next = xup->h_downs;                                                                                               <* 
 *>       while (next != NULL) {                                                                                             <* 
 *>          curr = next;                                                                                                    <* 
 *>          next = next->f_downs;                                                                                           <* 
 *>       }                                                                                                                  <* 
 *>       curr->f_downs = xtie;                                                                                              <* 
 *>    }                                                                                                                     <* 
 *>    ++xup->n_downs;                                                                                                       <* 
 *>    /+---(tie downstream)-----------------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("   8) tie to down links up sll\n"); )                                                           <* 
 *>       xtie->down      = xdown;                                                                                           <* 
 *>    xtie->f_ups     = NULL;                                                                                               <* 
 *>    if (xdown->h_ups == NULL) xdown->h_ups = xtie;                                                                        <* 
 *>    else {                                                                                                                <* 
 *>       next = xdown->h_ups;                                                                                               <* 
 *>       while (next != NULL) {                                                                                             <* 
 *>          curr = next;                                                                                                    <* 
 *>          next = next->f_ups;                                                                                             <* 
 *>       }                                                                                                                  <* 
 *>       curr->f_ups = xtie;                                                                                                <* 
 *>    }                                                                                                                     <* 
 *>    ++xdown->n_ups;                                                                                                       <* 
 *>    /+---(attach data)--------------------+/                                                                              <* 
 *>    DEBUG_TIES ( printf ("   9) attach data\n"); )                                                                        <* 
 *>       if (a_data != NULL)  xtie->data    = a_data;                                                                       <* 
 *>       else                 xtie->data    = nada;                                                                         <* 
 *>    DEBUG_TIES ( printf ("   A) DONE\n"); )                                                                               <* 
 *>       /+---(fix other attachments)----------+/                                                                           <* 
 *>       if (a_up   != -1 && a_down != -1) {                                                                                <* 
 *>          /+---(fix up downstream)--------------+/                                                                        <* 
 *>          if (a_down != -1) {                                                                                             <* 
 *>             DEBUG_TIES ( printf ("--------------------\n"); )                                                            <* 
 *>                DEBUG_TIES ( printf ("I)   check so see if down (%4d) is attached to h_tree (with untie)\n", a_down); )   <* 
 *>                yDLST_untie ( -1, a_down);                                                                                <* 
 *>             DEBUG_TIES ( printf ("--------------------\n"); )                                                            <* 
 *>                DEBUG_TIES ( printf ("II)  check to see if down (%4d) needs a t_tree link\n", a_down); )                  <* 
 *>                yDLST_tie (a_down,   -1  , "to_tail");                                                                    <* 
 *>          }                                                                                                               <* 
 *>          /+---(fix up upstream)----------------+/                                                                        <* 
 *>          if (a_up   != -1) {                                                                                             <* 
 *>             DEBUG_TIES ( printf ("--------------------\n"); )                                                            <* 
 *>                DEBUG_TIES ( printf ("III) check to see if up   (%4d) is attached to t_tree (with untie)\n", a_up); )     <* 
 *>                yDLST_untie (a_up, -1);                                                                                   <* 
 *>             DEBUG_TIES ( printf ("--------------------\n"); )                                                            <* 
 *>                DEBUG_TIES ( printf ("IV)  check to see if up   (%4d) needs a h_tree link\n", a_up); )                    <* 
 *>                yDLST_tie (  -1  , a_up  , "from_head");                                                                  <* 
 *>          }                                                                                                               <* 
 *>       }                                                                                                                  <* 
 *>    /+---(complete)-----------------------+/                                                                              <* 
 *>    return 0;                                                                                                             <* 
 *> }                                                                                                                        <*/

/*> char       /+----: tie to links together (directionally) --------------------+/                        <* 
 *> yDLST_untie        (int a_up, int a_down)                                                              <* 
 *> {                                                                                                      <* 
 *>    /+---(locals)-------------------------+/                                                            <* 
 *>    tLINK    *xup       = NULL;                                                                         <* 
 *>    tLINK    *xdown     = NULL;                                                                         <* 
 *>    tTIES    *xtie      = NULL;                                                                         <* 
 *>    tTIES    *curr      = NULL;                                                                         <* 
 *>    tTIES    *next      = NULL;                                                                         <* 
 *>    /+---(defence : circular)-------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("begin UNTIE (%4d) to (%4d)\n", a_up, a_down); )                               <* 
 *>       if (a_up  == a_down)                          return -1;                                         <* 
 *>    /+---(sort out upstream)--------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("   a) sort upstream...\n"); )                                                 <* 
 *>       if (a_up   == -1) {                                                                              <* 
 *>          xup   = h_tree;                                                                               <* 
 *>       } else {                                                                                         <* 
 *>          if (p_links == NULL || a_up   != c_links) {                                                   <* 
 *>             xup   = yDLST__link_find (a_up  , 'n');                                                    <* 
 *>             if (xup   == NULL)                      return -2;                                         <* 
 *>          } else  xup   = p_links;                                                                      <* 
 *>       }                                                                                                <* 
 *>    /+---(sort out downstream)------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("   b) sort downstream...\n"); )                                               <* 
 *>       if (a_down == -1) {                                                                              <* 
 *>          xdown = t_tree;                                                                               <* 
 *>       } else {                                                                                         <* 
 *>          if (p_links == NULL || a_down != c_links) {                                                   <* 
 *>             xdown = yDLST__link_find (a_down, 'n');                                                    <* 
 *>             if (xdown == NULL)                      return -3;                                         <* 
 *>          } else  xdown = p_links;                                                                      <* 
 *>       }                                                                                                <* 
 *>    /+---(find tie)-----------------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("   c) xup  = (%4d) %9p, xdown= (%4d) %9p :: ", a_up, xup, a_down, xdown); )   <* 
 *>       xtie = yDLST__tie_find (xup, xdown);                                                             <* 
 *>    if (xtie == NULL) {                                                                                 <* 
 *>       DEBUG_TIES ( printf ("not found, stop\n"); )                                                     <* 
 *>          return -4;                                                                                    <* 
 *>    }                                                                                                   <* 
 *>    DEBUG_TIES ( printf ("found, continue\n"); )                                                        <* 
 *>       /+---(remove from dll)----------------+/                                                         <* 
 *>       DEBUG_TIES ( printf ("   d) remove from dll...\n"); )                                            <* 
 *>       if (xtie->f_ties != NULL)  xtie->f_ties->b_ties  = xtie->b_ties;                                 <* 
 *>       else                       t_ties                = xtie->b_ties;                                 <* 
 *>    if (xtie->b_ties != NULL)  xtie->b_ties->f_ties  = xtie->f_ties;                                    <* 
 *>    else                       h_ties                = xtie->f_ties;                                    <* 
 *>    --n_ties;                                                                                           <* 
 *>    /+---(untie upstream)-----------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("   e) untie upstream link...\n"); )                                           <* 
 *>       curr   = xup->h_downs;                                                                           <* 
 *>    if      (curr == NULL)  ;                                                                           <* 
 *>    else if (curr->down == xdown)  xup->h_downs = curr->f_downs;                                        <* 
 *>    else {                                                                                              <* 
 *>       next = curr->f_downs;                                                                            <* 
 *>       while (next != NULL) {                                                                           <* 
 *>          if (next->down == xdown) {                                                                    <* 
 *>             curr->f_downs = next->f_downs;                                                             <* 
 *>             break;                                                                                     <* 
 *>          }                                                                                             <* 
 *>          curr = next;                                                                                  <* 
 *>          next = curr->f_downs;                                                                         <* 
 *>       }                                                                                                <* 
 *>    }                                                                                                   <* 
 *>    --xup->n_downs;                                                                                     <* 
 *>    /+---(untie downstream)---------------+/                                                            <* 
 *>    DEBUG_TIES  ( printf ("   f) untie downstream link...\n"); )                                        <* 
 *>       curr   = xdown->h_ups;                                                                           <* 
 *>    if      (curr == NULL)  ;                                                                           <* 
 *>    else if (curr->up   == xup) xdown->h_ups = curr->f_ups;                                             <* 
 *>    else {                                                                                              <* 
 *>       next = curr->f_ups;                                                                              <* 
 *>       while (next != NULL) {                                                                           <* 
 *>          DEBUG_TIES ( printf ("      up=%9p, dn=%9p\n", next->up, next->down); )                       <* 
 *>             if (next->up == xup) {                                                                     <* 
 *>                curr->f_ups = next->f_ups;                                                              <* 
 *>                break;                                                                                  <* 
 *>             }                                                                                          <* 
 *>          curr = next;                                                                                  <* 
 *>          next = curr->f_downs;                                                                         <* 
 *>       }                                                                                                <* 
 *>    }                                                                                                   <* 
 *>    --xdown->n_ups;                                                                                     <* 
 *>    /+---(free tie)-----------------------+/                                                            <* 
 *>    DEBUG_TIES ( printf ("   h) DONE...\n"); )                                                          <* 
 *>       /+---(fix other attachments)----------+/                                                         <* 
 *>       char   up_ups   = 'y';                                                                           <* 
 *>    char   up_downs = 'y';                                                                              <* 
 *>    char   dn_ups   = 'y';                                                                              <* 
 *>    char   dn_downs = 'y';                                                                              <* 
 *>    if (a_up   != -1 && a_down != -1) {                                                                 <* 
 *>       /+---(test linkage)-------------------+/                                                         <* 
 *>       if (xup->h_ups     == NULL || xup->h_ups->up       == h_tree) up_ups   = '-';                    <* 
 *>       if (xdown->h_ups   == NULL || xdown->h_ups->up     == h_tree) dn_ups   = '-';                    <* 
 *>       if (xup->h_downs   == NULL || xup->h_downs->down   == t_tree) up_downs = '-';                    <* 
 *>       if (xdown->h_downs == NULL || xdown->h_downs->down == t_tree) dn_downs = '-';                    <* 
 *>       /+---(floating links)-----------------+/                                                         <* 
 *>       if (up_ups == '-' && up_downs == '-') {                                                          <* 
 *>          yDLST_untie (  -1   , a_up   );                                                               <* 
 *>          yDLST_untie ( a_up  ,  -1    );                                                               <* 
 *>       }                                                                                                <* 
 *>       if (dn_ups == '-' && dn_downs == '-') {                                                          <* 
 *>          yDLST_untie (  -1   , a_down );                                                               <* 
 *>          yDLST_untie ( a_down, -1    );                                                                <* 
 *>       }                                                                                                <* 
 *>       /+---(check half ties)----------------+/                                                         <* 
 *>       if        (up_ups == '-' && up_downs == 'y') {                                                   <* 
 *>          yDLST_tie   (  -1   , a_up   , "from_head");                                                  <* 
 *>       } else if (up_ups == 'y' && up_downs == '-') {                                                   <* 
 *>          yDLST_tie   ( a_up  ,  -1    , "to_tail");                                                    <* 
 *>       }                                                                                                <* 
 *>       if        (dn_ups == '-' && dn_downs == 'y') {                                                   <* 
 *>          yDLST_tie   (  -1   , a_down , "from_head");                                                  <* 
 *>       } else if (dn_ups == 'y' && dn_downs == '-') {                                                   <* 
 *>          yDLST_tie   ( a_down,  -1    , "to_tail");                                                    <* 
 *>       }                                                                                                <* 
 *>    }                                                                                                   <* 
 *>    /+---(complete)-----------------------+/                                                            <* 
 *>    return 0;                                                                                           <* 
 *> }                                                                                                      <*/

/*> void*      /+----: get a tie from the ties list ------------------------------+/   <* 
 *> yDLST_ties         (int a_index)                                                   <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------*-----------------+/                                        <* 
 *>    int       i         = 0;                                                        <* 
 *>    /+---(for head link)------------------+/                                        <* 
 *>    if      (a_index == HEAD)  {                                                    <* 
 *>       if (h_ties == NULL)        return NULL;                                      <* 
 *>       p_ties = h_ties;                                                             <* 
 *>    }                                                                               <* 
 *>    /+---(for next link)------------------+/                                        <* 
 *>    else if (a_index == NEXT) {                                                     <* 
 *>       while (p_ties != NULL) {                                                     <* 
 *>          p_ties = p_ties->f_ties;                                                  <* 
 *>          if (p_ties == NULL)        return NULL;                                   <* 
 *>          if (p_ties->up   == h_tree) continue;                                     <* 
 *>          if (p_ties->down == t_tree) continue;                                     <* 
 *>          break;                                                                    <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for curr link)------------------+/                                        <* 
 *>    else if (a_index == CURR) {                                                     <* 
 *>       ;                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for specific link)--------------+/                                        <* 
 *>    else {                                                                          <* 
 *>       p_ties  = h_ties;                                                            <* 
 *>       if (p_ties == NULL)     return NULL;                                         <* 
 *>       while (i < a_index) {                                                        <* 
 *>          p_ties = p_ties->f_ties;                                                  <* 
 *>          if (p_ties == NULL)     return NULL;                                      <* 
 *>          if (p_ties->up   == h_tree) continue;                                     <* 
 *>          if (p_ties->down == t_tree) continue;                                     <* 
 *>          ++i;                                                                      <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(defense for dereference)--------+/                                        <* 
 *>    if (p_ties == NULL) return NULL;                                                <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return p_ties->data;                                                            <* 
 *> }                                                                                  <*/

/*> void*      /+----: get a downward link ---------------------------------------+/   <* 
 *> yDLST_downs        (int a_link, int a_index)                                       <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------*-----------------+/                                        <* 
 *>    int       i         = 0;                                                        <* 
 *>    tLINK    *xlink     = NULL;                                                     <* 
 *>    /+---(sort out which link)------------+/                                        <* 
 *>    if (p_links == NULL || a_link != c_links) {                                     <* 
 *>       xlink = yDLST__link_find (a_link, 'y');                                      <* 
 *>       if (xlink == NULL)     return NULL;                                          <* 
 *>    } else  xlink = p_links;                                                        <* 
 *>    /+---(for head link)------------------+/                                        <* 
 *>    if      (a_index == HEAD)  {                                                    <* 
 *>       if (xlink->h_downs == NULL)        return NULL;                              <* 
 *>       p_ties = xlink->h_downs;                                                     <* 
 *>       if (p_ties->down   == t_tree)      return NULL;                              <* 
 *>    }                                                                               <* 
 *>    /+---(for next link)------------------+/                                        <* 
 *>    else if (a_index == NEXT) {                                                     <* 
 *>       while (p_ties != NULL) {                                                     <* 
 *>          p_ties = p_ties->f_downs;                                                 <* 
 *>          if (p_ties == NULL)        return NULL;                                   <* 
 *>          if (p_ties->down == t_tree) continue;                                     <* 
 *>          break;                                                                    <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for curr link)------------------+/                                        <* 
 *>    else if (a_index == CURR) {                                                     <* 
 *>       ;                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for specific link)--------------+/                                        <* 
 *>    else {                                                                          <* 
 *>       p_ties  = xlink->h_downs;                                                    <* 
 *>       if (p_ties == NULL)     return NULL;                                         <* 
 *>       if (p_ties->down == t_tree) return NULL;                                     <* 
 *>       while (i < a_index) {                                                        <* 
 *>          p_ties = p_ties->f_downs;                                                 <* 
 *>          if (p_ties == NULL)     return NULL;                                      <* 
 *>          if (p_ties->down == t_tree) continue;                                     <* 
 *>          ++i;                                                                      <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(defense for dereference)--------+/                                        <* 
 *>    if (p_ties == NULL) return NULL;                                                <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return p_ties->down->data;                                                      <* 
 *> }                                                                                  <*/

/*> void*      /+----: get an upward link ----------------------------------------+/   <* 
 *> yDLST_ups          (int a_link, int a_index)                                       <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------*-----------------+/                                        <* 
 *>    int       i         = 0;                                                        <* 
 *>    tLINK    *xlink     = NULL;                                                     <* 
 *>    /+---(sort out which link)------------+/                                        <* 
 *>    if (p_links == NULL || a_link != c_links) {                                     <* 
 *>       xlink = yDLST__link_find (a_link, 'y');                                      <* 
 *>       if (xlink == NULL)     return NULL;                                          <* 
 *>    } else  xlink = p_links;                                                        <* 
 *>    /+---(for head link)------------------+/                                        <* 
 *>    if      (a_index == HEAD)  {                                                    <* 
 *>       if (xlink->h_ups == NULL)        return NULL;                                <* 
 *>       p_ties = xlink->h_ups;                                                       <* 
 *>       if (p_ties->up   == h_tree)      return NULL;                                <* 
 *>    }                                                                               <* 
 *>    /+---(for next link)------------------+/                                        <* 
 *>    else if (a_index == NEXT) {                                                     <* 
 *>       while (p_ties != NULL) {                                                     <* 
 *>          p_ties = p_ties->f_ups;                                                   <* 
 *>          if (p_ties == NULL)        return NULL;                                   <* 
 *>          if (p_ties->up   == h_tree) continue;                                     <* 
 *>          break;                                                                    <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for curr link)------------------+/                                        <* 
 *>    else if (a_index == CURR) {                                                     <* 
 *>       ;                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(for specific link)--------------+/                                        <* 
 *>    else {                                                                          <* 
 *>       p_ties  = xlink->h_ups;                                                      <* 
 *>       if (p_ties == NULL)     return NULL;                                         <* 
 *>       if (p_ties->up   == h_tree) return NULL;                                     <* 
 *>       while (i < a_index) {                                                        <* 
 *>          p_ties = p_ties->f_ups;                                                   <* 
 *>          if (p_ties == NULL)     return NULL;                                      <* 
 *>          if (p_ties->up   == h_tree) continue;                                     <* 
 *>          ++i;                                                                      <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    /+---(defense for dereference)--------+/                                        <* 
 *>    if (p_ties == NULL) return NULL;                                                <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return p_ties->up->data;                                                        <* 
 *> }                                                                                  <*/

/*> tTIES*     /+----: find a tie based on two indexes ---------------------------+/            <* 
 *> yDLST__tie_find    (tLINK* a_up, tLINK *a_down)                                             <* 
 *> {                                                                                           <* 
 *>    /+---(locals)-------------------------+/                                                 <* 
 *>    tTIES    *next     = NULL;                                                               <* 
 *>    /+---(defenses)-----------------------+/                                                 <* 
 *>    if (a_up   == NULL)            return NULL;                                              <* 
 *>    if (a_down == NULL)            return NULL;                                              <* 
 *>    /+---(see if we're the hash head)-----+/                                                 <* 
 *>    /+> printf ("         so into the find (past defenses)\n");                        <+/   <* 
 *>    next = a_up->h_downs;                                                                    <* 
 *>    /+> printf ("         looking for    %9p\n", a_down);                              <+/   <* 
 *>    /+> printf ("         downs header = %9p\n", next);                                <+/   <* 
 *>    if (next       == NULL  )      return NULL;                                              <* 
 *>    if (next->down == NULL  )      return NULL;                                              <* 
 *>    /+> printf ("         header points  %9p\n", next->down);                          <+/   <* 
 *>    if (next->down == a_down) {                                                              <* 
 *>       /+> printf ("         FOUND\n");                                                <+/   <* 
 *>       return next;                                                                          <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("         through simple checks\n");                                   <+/   <* 
 *>    next = next->f_downs;                                                                    <* 
 *>    while (next != NULL) {                                                                   <* 
 *>       /+> printf ("         next points at %9p\n", next->down);                       <+/   <* 
 *>       if (next->down == a_down) {                                                           <* 
 *>          /+> printf ("         FOUND\n");                                             <+/   <* 
 *>          return next;                                                                       <* 
 *>       }                                                                                     <* 
 *>       next = next->f_downs;                                                                 <* 
 *>    }                                                                                        <* 
 *>    /+> printf ("         no more\n");                                                 <+/   <* 
 *>    /+---(complete)-----------------------+/                                                 <* 
 *>    return NULL;                                                                             <* 
 *> }                                                                                           <*/
