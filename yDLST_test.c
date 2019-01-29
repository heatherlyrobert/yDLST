/*============================----beg-of-source---============================*/

#include   "yDLST.h"
#include   "yDLST_priv.h"



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};


/*> char*      /+----: provide grey-box insight to the unit test -----------------+/                                                                                                               <* 
 *> yDLST_greybox      (char *a_question, int  a_index)                                                                                                                                            <* 
 *> {                                                                                                                                                                                              <* 
 *>    /+---(locals)-------------------------+/                                                                                                                                                    <* 
 *>    int       xfore  = 0, xback  = 0;  /+ counts to verify doubly-linked list +/                                                                                                                <* 
 *>    int       xups   = 0, xdowns = 0;                                                                                                                                                           <* 
 *>    tLIST    *xlist    = NULL;                                                                                                                                                                  <* 
 *>    tLINK    *xlink    = NULL;                                                                                                                                                                  <* 
 *>    tTIES    *xtie     = NULL;                                                                                                                                                                  <* 
 *>    /+---(sort out which list)------------+/                                                                                                                                                    <* 
 *>    if (p_lists == NULL || a_index != c_lists) {                                                                                                                                                <* 
 *>       xlist = yDLST__list_find (a_index, 'n');                                                                                                                                                 <* 
 *>    } else  xlist = p_lists;                                                                                                                                                                    <* 
 *>    /+---(sort out which link)------------+/                                                                                                                                                    <* 
 *>    if (p_links == NULL || a_index != c_links) {                                                                                                                                                <* 
 *>       xlink = yDLST__link_find (a_index, 'n');                                                                                                                                                 <* 
 *>    } else  xlink = p_links;                                                                                                                                                                    <* 
 *>    /+---(list of lists)------------------+/                                                                                                                                                    <* 
 *>    if        (strncmp(a_question, "list_end_ptr" , 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LIST End Ptrs    : n=%4d, h=%9p, t=%9p", n_lists, h_lists, t_lists);                                                                                    <* 
 *>    } else if (strncmp(a_question, "list_end_int" , 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LIST End Ints    : n=%4d, h=%4d, t=%4d", n_lists, ((h_lists != NULL) ? h_lists->id : -1), ((t_lists != NULL) ? t_lists->id : -1));                      <* 
 *>    } else if (strncmp(a_question, "list_count"   , 20)   == 0) {                                                                                                                               <* 
 *>       xlist = h_lists; while (xlist != NULL) { ++xfore; xlist = xlist->next; }                                                                                                                 <* 
 *>       xlist = t_lists; while (xlist != NULL) { ++xback; xlist = xlist->prev; }                                                                                                                 <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LIST Counts      : n=%4d, f=%4d, b=%4d", n_lists, xfore, xback);                                                                                        <* 
 *>    } else if (strncmp(a_question, "list_name"    , 20)   == 0) {                                                                                                                               <* 
 *>       if (xlist == NULL) return "NULL LIST";                                                                                                                                                   <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LIST Name        : %-.35s", xlist->name);                                                                                                               <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(all links dll)------------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "all_end_ptr"  , 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "ALL End Ptrs     : n=%4d, h=%9p, t=%9p", n_links, h_links, t_links);                                                                                    <* 
 *>    } else if (strncmp(a_question, "all_end_int"  , 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "ALL End Ints     : n=%4d, h=%4d, t=%4d", n_links, ((h_links != NULL) ? h_links->id : -1), ((t_links != NULL) ? t_links->id : -1));                      <* 
 *>    } else if (strncmp(a_question, "all_count"    , 20)   == 0) {                                                                                                                               <* 
 *>       xlink = h_links; while (xlink != NULL) { ++xfore; xlink = xlink->f_links; }                                                                                                              <* 
 *>       xlink = t_links; while (xlink != NULL) { ++xback; xlink = xlink->b_links; }                                                                                                              <* 
 *>       snprintf(unit_answer, LEN_TEXT, "ALL Counts       : n=%4d, f=%4d, b=%4d", n_links, xfore, xback);                                                                                        <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(focus link dll)-----------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "focus_end_ptr", 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Focus End Ptrs   : n=%4d, h=%9p, t=%9p", n_focus, h_focus, t_focus);                                                                                    <* 
 *>    } else if (strncmp(a_question, "focus_end_int", 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Focus End Ints   : n=%4d, h=%4d, t=%4d", n_focus, ((h_focus != NULL) ? h_focus->id : -1), ((t_focus != NULL) ? t_focus->id : -1));                      <* 
 *>    } else if (strncmp(a_question, "focus_count"  , 20)   == 0) {                                                                                                                               <* 
 *>       xlink = h_focus; while (xlink != NULL) { ++xfore; xlink = xlink->f_focus; }                                                                                                              <* 
 *>       xlink = t_focus; while (xlink != NULL) { ++xback; xlink = xlink->b_focus; }                                                                                                              <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Focus Counts     : n=%4d, f=%4d, b=%4d", n_focus, xfore, xback);                                                                                        <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(active link dll)----------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "active_ends"  , 20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Active Endpoints : n=%4d, h=%9p, t=%9p", n_active, h_active, t_active);                                                                                 <* 
 *>    } else if (strncmp(a_question, "active_end_int",20)   == 0) {                                                                                                                               <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Active End Ints  : n=%4d, h=%4d, t=%4d", n_active, ((h_active != NULL) ? h_active->id : -1), ((t_active != NULL) ? t_active->id : -1));                 <* 
 *>    } else if (strncmp(a_question, "active_count" , 20)   == 0) {                                                                                                                               <* 
 *>       xlink = h_active; while (xlink != NULL) { ++xfore; xlink = xlink->f_active; }                                                                                                            <* 
 *>       xlink = t_active; while (xlink != NULL) { ++xback; xlink = xlink->b_active; }                                                                                                            <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Active Counts    : n=%4d, f=%4d, b=%4d", n_active, xfore, xback);                                                                                       <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(list link dll)------------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "link_end_ptr" , 20)   == 0) {                                                                                                                               <* 
 *>       if (xlist == NULL) return "LINK End Ptrs    : NULL LIST";                                                                                                                                <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LINK End Ptrs    : n=%4d, h=%9p, t=%9p", xlist->num, xlist->head, xlist->tail);                                                                         <* 
 *>    } else if (strncmp(a_question, "link_end_int" , 20)   == 0) {                                                                                                                               <* 
 *>       if (xlist == NULL) return "LINK End Ints    : NULL LIST";                                                                                                                                <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LINK End Ints    : n=%4d, h=%4d, t=%4d", xlist->num, ((xlist->head != NULL) ? xlist->head->id : -1), ((xlist->tail != NULL) ? xlist->tail->id : -1));   <* 
 *>    } else if (strncmp(a_question, "link_count"   , 20)   == 0) {                                                                                                                               <* 
 *>       if (xlist == NULL) return "LINK Counts      : NULL LIST";                                                                                                                                <* 
 *>       xlink = xlist->head; while (xlink != NULL) { ++xfore; xlink = xlink->next; }                                                                                                             <* 
 *>       xlink = xlist->tail; while (xlink != NULL) { ++xback; xlink = xlink->prev; }                                                                                                             <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LINK Counts      : n=%4d, f=%4d, b=%4d", xlist->num, xfore, xback);                                                                                     <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(list ties dll)------------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "ties_all"     , 20)   == 0) {                                                                                                                               <* 
 *>       xtie  = h_ties; while (xtie != NULL) { ++xfore; xtie = xtie->f_ties; }                                                                                                                   <* 
 *>       xtie  = t_ties; while (xtie != NULL) { ++xback; xtie = xtie->b_ties; }                                                                                                                   <* 
 *>       snprintf(unit_answer, LEN_TEXT, "TIES All Counts  : n=%4d, f=%4d, b=%4d", n_ties, xfore, xback);                                                                                         <* 
 *>    } else if (strncmp(a_question, "ties_count"   , 20)   == 0) {                                                                                                                               <* 
 *>       xtie  = h_ties; while (xtie != NULL) { if (xtie->up   == h_tree) ++xups  ; xtie = xtie->f_ties; }                                                                                        <* 
 *>       xtie  = h_ties; while (xtie != NULL) { if (xtie->down == t_tree) ++xdowns; xtie = xtie->f_ties; }                                                                                        <* 
 *>       xtie  = h_ties; while (xtie != NULL) { ++xfore; xtie = xtie->f_ties; }                                                                                                                   <* 
 *>       xtie  = t_ties; while (xtie != NULL) { ++xback; xtie = xtie->b_ties; }                                                                                                                   <* 
 *>       snprintf(unit_answer, LEN_TEXT, "TIES Counts      : n=%4d, f=%4d, b=%4d", n_ties - xups - xdowns, xfore - xups - xdowns, xback - xups - xdowns);                                         <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(individual link)----------------+/                                                                                                                                                    <* 
 *>    else if   (strncmp(a_question, "link_member"  , 20)   == 0) {                                                                                                                               <* 
 *>       if (xlink == NULL) return "NULL LINK";                                                                                                                                                   <* 
 *>       snprintf(unit_answer, LEN_TEXT, "Link Membership  : f=%c%c, l=%c%c, f=%c%c, a=%c%c", ((xlink->b_links != NULL) ? 'y' : 'n'), 'n', 'n', 'n', 'n', 'n', 'n', 'n');                         <* 
 *>    } else if (strncmp(a_question, "link_tie_count",20)   == 0) {                                                                                                                               <* 
 *>       if (xlink == NULL) return "NULL LINK";                                                                                                                                                   <* 
 *>       xtie  = xlink->h_downs; while (xtie != NULL) { if (xtie->down == t_tree) ++xdowns; xtie = xtie->f_downs; }                                                                               <* 
 *>       xtie  = xlink->h_ups  ; while (xtie != NULL) { if (xtie->up   == h_tree) ++xups  ; xtie = xtie->f_ups; }                                                                                 <* 
 *>       xtie  = xlink->h_downs; while (xtie  != NULL) { ++xfore; xtie  = xtie->f_downs; }                                                                                                        <* 
 *>       xtie  = xlink->h_ups  ; while (xtie  != NULL) { ++xback; xtie  = xtie->f_ups  ; }                                                                                                        <* 
 *>       snprintf(unit_answer, LEN_TEXT, "LINK Tie Counts  : nup=%4d, fup=%4d, ndn=%4d, fdn=%4d", xlink->n_ups - xups, xback - xups, xlink->n_downs - xdowns, xfore - xdowns);                    <* 
 *>    }                                                                                                                                                                                           <* 
 *>    /+---(locals)-------------------------+/                                                                                                                                                    <* 
 *>    else {                                                                                                                                                                                      <* 
 *>       snprintf(unit_answer, LEN_TEXT, "unknown          : unit_accessor question not defined");                                                                                                <* 
 *>    }                                                                                                                                                                                           <* 
 *>    return unit_answer;                                                                                                                                                                         <* 
 *> }                                                                                                                                                                                              <*/


/*============================----end-of-source---============================*/
