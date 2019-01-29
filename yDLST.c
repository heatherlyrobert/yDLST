/*===========================[[ start-of-code ]]==============================*/

#include   "yDLST.h"
#include   "yDLST_priv.h"


tLOCAL    its;



/*===[ DEBUGGING MACROS ]===------------------------------*/
#define   DEBUG_TIES(BODY)    /* BODY */
/*> #define   DEBUG_TIES(BODY)    BODY                                                <*/


static char     *nada      = "(na)";


/*---(list of all lists)--------------*/
/*> tLIST    *h_lists   = NULL;            /+ head node pointer                   +/   <* 
 *> tLIST    *t_lists   = NULL;            /+ tail node pointer                   +/   <* 
 *> int       n_lists   = 0;               /+ number of lists                     +/   <* 
 *> int       i_lists   = 0;               /+ next sequential list id             +/   <* 
 *> int       c_lists   = -1;              /+ id of current list                  +/   <* 
 *> tLIST    *p_lists   = NULL;            /+ pointer to current list             +/   <* 
 *> tLIST    *x_lists [INDEX_LIST];        /+ hash index to list of all lists     +/   <*/

/*---(list of all links)--------------*/
/*> tLINK    *h_links   = NULL;            /+ head node pointer                   +/   <* 
 *> tLINK    *t_links   = NULL;            /+ tail node pointer                   +/   <* 
 *> int       n_links   = 0;               /+ number of links                     +/   <* 
 *> int       i_links   = 0;               /+ next sequential link id             +/   <* 
 *> int       c_links   = -1;              /+ id of current link                  +/   <* 
 *> tLINK    *p_links   = NULL;            /+ pointer to current link             +/   <* 
 *> tLINK    *x_links [INDEX_LINK];        /+ hash index to list of all links     +/   <*/

/*---(sub list)-----------------------*/
/*> tLINK    *h_focus   = NULL;  /+ head  +/                                          <* 
 *> tLINK    *t_focus   = NULL;  /+ tail  +/                                          <* 
 *> int       n_focus   = 0;     /+ num   +/                                          <* 
 *> int       c_focus   = -1;    /+ current focus link                +/              <* 
 *> tLINK    *p_focus   = NULL;                                                       <*/

/*---(active list)--------------------*/
/*> tLINK    *h_active  = NULL;  /+ head  +/                                          <* 
 *> tLINK    *t_active  = NULL;  /+ tail  +/                                          <* 
 *> int       n_active  = 0;     /+ num   +/                                          <* 
 *> int       c_active  = -1;    /+ current active link               +/              <* 
 *> tLINK    *p_active  = NULL;                                                       <*/

/*---(full ties list)-----------------*/
/*> tTIES    *h_ties    = NULL;                                                       <* 
 *> tTIES    *t_ties    = NULL;                                                       <* 
 *> int       n_ties    = 0;                                                          <* 
 *> tTIES    *p_ties    = NULL;                                                       <*/

/*---(dependency tree)----------------*/
/*> tLINK    *h_tree    = NULL;                                                       <* 
 *> tLINK    *t_tree    = NULL;                                                       <*/


static char      yDLST_ver [200] = "";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yDLST_version      (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yDLST_ver, 100, "%s   %s : %s", t, YDLST_VER_NUM, YDLST_VER_TXT);
   return yDLST_ver;
}


/*====================------------------------------------====================*/
/*===----                   dlst setup and teardown                    ----===*/
/*====================------------------------------------====================*/
PRIV void  o___DLST____________o () { return; }

char       /*----: prepare the list library for use --------------------------*/
yDLST_begin        (void)
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(initialize)---------------------*/
   rc = ydlst_list_init   ();
   rc = ydlst_line_init   ();
   rc = ydlst_focus_init  ();
   rc = ydlst_active_init ();
   rc = ydlst_seq_init    ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_end          (void)
{
   /*---(locals)-------*-----------------*/
   /*> tLIST    *xlist     = NULL;                                                    <* 
    *> tLIST    *xnext     = NULL;                                                    <* 
    *> tTIES    *xtie      = NULL;                                                    <* 
    *> tTIES    *xtien     = NULL;                                                    <*/
   int       rc        = 0;
   /*---(kills all ties)-----------------*/
   /*
    *
    *
    *
    */
   /*---(wipe out the ties)--------------*/
   /*> xtie  = h_ties;                                                                <* 
    *> while (xtie  != NULL) {                                                        <* 
    *>    xtien  = xtie->f_ties;                                                      <* 
    *>    free (xtie);                                                                <* 
    *>    xtie = xtien;                                                               <* 
    *> }                                                                              <*/
   /*---(wipe out the lists/links)-------*/
   /*> xnext = h_lists;                                                               <* 
    *> while (xnext != NULL) {                                                        <* 
    *>    xlist  = xnext;                                                             <* 
    *>    xnext  = xlist->next;                                                       <* 
    *>    yDLST_destroy (xlist->id);                                                  <* 
    *> }                                                                              <*/
   /*---(tree head and tail)-------------*/
   /*> rc = yDLST__unfloat (&h_tree);                                                 <* 
    *> if (rc != 0) return -1;                                                        <* 
    *> rc = yDLST__unfloat (&t_tree);                                                 <* 
    *> if (rc != 0) return -2;                                                        <*/
   /*---(initialize)---------------------*/
   rc = ydlst_list_wrap   ();
   rc = ydlst_line_wrap   ();
   rc = ydlst_focus_wrap  ();
   rc = ydlst_active_wrap ();
   rc = ydlst_seq_wrap    ();
   /*---(complete)-----------------------*/
   return 0;
}

/*> char       /+----: specialty for creating tree head and tail -------------+/      <* 
 *> yDLST__float       (tLINK **a_link, char *a_name, void *a_data)                   <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-------------------------+/                                       <* 
 *>    tLINK    *xlink     = NULL;                                                    <* 
 *>    int       i         = 0;                                                       <* 
 *>    /+---(defense)---------------------+/                                          <* 
 *>    if ( a_link == NULL)      return -1;                                           <* 
 *>    /+---(create link)-----------------+/                                          <* 
 *>    for (i = 0; i < 3; ++i) {                                                      <* 
 *>       xlink = (tLINK *) malloc(sizeof(tLINK));                                    <* 
 *>       if (xlink != NULL) break;                                                   <* 
 *>    }                                                                              <* 
 *>    if (xlink == NULL)        return -2;                                           <* 
 *>    /+---(index list)------------------+/                                          <* 
 *>    xlink->id        = -1;                                                         <* 
 *>    /+---(into list of all links)------+/                                          <* 
 *>    xlink->f_links   = NULL;                                                       <* 
 *>    xlink->b_links   = NULL;                                                       <* 
 *>    /+---(tie to its owner)------------+/                                          <* 
 *>    xlink->list      = NULL;                                                       <* 
 *>    /+---(into lists links)------------+/                                          <* 
 *>    xlink->next      = NULL;                                                       <* 
 *>    xlink->prev      = NULL;                                                       <* 
 *>    /+---(sub lists)-------------------+/                                          <* 
 *>    xlink->focus     = '-';                                                        <* 
 *>    xlink->f_next    = NULL;                                                       <* 
 *>    xlink->b_focus   = NULL;                                                       <* 
 *>    xlink->active    = '-';                                                        <* 
 *>    xlink->f_active  = NULL;                                                       <* 
 *>    xlink->b_active  = NULL;                                                       <* 
 *>    /+---(dependencies)----------------+/                                          <* 
 *>    xlink->h_ups     = NULL;                                                       <* 
 *>    xlink->n_ups     = 0;                                                          <* 
 *>    xlink->h_downs   = NULL;                                                       <* 
 *>    xlink->n_downs   = 0;                                                          <* 
 *>    /+---(name the link)------------------+/                                       <* 
 *>    if (a_name != NULL)  xlink->name    = strdup(a_name);                          <* 
 *>    else                 xlink->name    = nada;                                    <* 
 *>    /+---(attach data)--------------------+/                                       <* 
 *>    if (a_data != NULL)  xlink->data    = a_data;                                  <* 
 *>    else                 xlink->data    = nada;                                    <* 
 *>    /+---(save key values)----------------+/                                       <* 
 *>    if (a_link != NULL) *a_link = xlink;                                           <* 
 *>    /+---(complete)--------------------+/                                          <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char       /+----: create a new, unattached link -------------------------+/      <* 
 *> yDLST__unfloat     (tLINK **a_link)                                               <* 
 *> {                                                                                 <* 
 *>    /+---(defenses)-----------------------+/                                       <* 
 *>    if (  a_link == NULL) return 0;                                                <* 
 *>    if ( *a_link == NULL) return 0;                                                <* 
 *>    tLINK    *xlink     = *a_link;                                                 <* 
 *>    /+---(free main)----------------------+/                                       <* 
 *>    if (xlink->name != NULL && xlink->name != nada)  free(xlink->name);            <* 
 *>    free (*a_link);                                                                <* 
 *>    *a_link = NULL;                                                                <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char       /+----: add a list to the index -----------------------------------+/   <* 
 *> yDLST__link_index  (tLINK *a_link)                                                 <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------------------------+/                                        <* 
 *>    int       a         = 0;                                                        <* 
 *>    tLINK    *xnext     = NULL;                                                     <* 
 *>    /+---(initialize)---------------------+/                                        <* 
 *>    a_link->id      = i_links++;                                                    <* 
 *>    a_link->x_links = NULL;                                                         <* 
 *>    /+---(get initial hash)---------------+/                                        <* 
 *>    a = a_link->id % INDEX_LINK;                                                    <* 
 *>    xnext  = x_links [a];                                                           <* 
 *>    if (xnext == NULL) {                                                            <* 
 *>       x_links [a] = a_link;                                                        <* 
 *>       p_links = a_link;                                                            <* 
 *>       c_links = a_link->id;                                                        <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(follow list)--------------------+/                                        <* 
 *>    while (xnext->x_links != NULL) {                                                <* 
 *>       if (xnext == a_link)   return -100;                                          <* 
 *>       xnext = xnext->x_links;                                                      <* 
 *>    }                                                                               <* 
 *>    xnext->x_links = a_link;                                                        <* 
 *>    /+---(save current keys)--------------+/                                        <* 
 *>    p_links = a_link;                                                               <* 
 *>    c_links = a_link->id;                                                           <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

/*> char       /+----: remove a list from the index ------------------------------+/   <* 
 *> yDLST__link_uindex (tLINK *a_link)                                                 <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------------------------+/                                        <* 
 *>    int       a         = 0;                                                        <* 
 *>    tLINK    *xcurr     = NULL;                                                     <* 
 *>    tLINK    *xnext     = NULL;                                                     <* 
 *>    /+---(defenses)-----------------------+/                                        <* 
 *>    if (a_link     == NULL)  return -1;                                             <* 
 *>    if (a_link->id <   0  )  return -2;                                             <* 
 *>    /+---(get initial hash)---------------+/                                        <* 
 *>    a = a_link->id % INDEX_LINK;                                                    <* 
 *>    xnext  = x_links [a];                                                           <* 
 *>    if (xnext == NULL )  return -100;  /+ couldn't find a real list in index!! +/   <* 
 *>    /+---(see if we're the hash head)-----+/                                        <* 
 *>    if (xnext == a_link) {                                                          <* 
 *>       x_links [a] = xnext->x_links;                                                <* 
 *>       p_links = NULL;                                                              <* 
 *>       c_links = -1;                                                                <* 
 *>       return 0;                                                                    <* 
 *>    }                                                                               <* 
 *>    /+---(else run the list)--------------+/                                        <* 
 *>    while (xnext->x_links != NULL) {                                                <* 
 *>       xcurr  = xnext;                                                              <* 
 *>       xnext  = xnext->x_links;                                                     <* 
 *>       if (xnext == a_link) {                                                       <* 
 *>          xcurr->x_links = xnext->x_links;                                          <* 
 *>          p_links = NULL;                                                           <* 
 *>          c_links = -1;                                                             <* 
 *>          return 0;                                                                 <* 
 *>       }                                                                            <* 
 *>    }                                                                               <* 
 *>    p_links = NULL;                                                                 <* 
 *>    c_links = -1;                                                                   <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return -2;                                                                      <* 
 *> }                                                                                  <*/

/*> tLINK*     /+----: find a link based on index --------------------------------+/   <* 
 *> yDLST__link_find   (int  a_index, char a_change)                                   <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-------------------------+/                                        <* 
 *>    int       a         = 0;                                                        <* 
 *>    tLINK    *xnext     = NULL;                                                     <* 
 *>    /+---(defenses)-----------------------+/                                        <* 
 *>    if (a_index    <   0  )  return NULL;                                           <* 
 *>    /+---(look at index)------------------+/                                        <* 
 *>    a      = a_index % INDEX_LINK;                                                  <* 
 *>    xnext  = x_links [a];                                                           <* 
 *>    if (xnext == NULL )  return NULL;                                               <* 
 *>    /+---(see if we're the hash head)-----+/                                        <* 
 *>    while (xnext != NULL) {                                                         <* 
 *>       if (xnext->id == a_index)  {                                                 <* 
 *>          if (a_change == 'y') {                                                    <* 
 *>             p_links = xnext;                                                       <* 
 *>             c_links = a_index;                                                     <* 
 *>          }                                                                         <* 
 *>          return xnext;                                                             <* 
 *>       }                                                                            <* 
 *>       xnext = xnext->x_links;                                                      <* 
 *>    }                                                                               <* 
 *>    /+---(if not found)-------------------+/                                        <* 
 *>    if (a_change == 'y') {                                                          <* 
 *>       p_links = NULL;                                                              <* 
 *>       c_links = -1;                                                                <* 
 *>    }                                                                               <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return NULL;                                                                    <* 
 *> }                                                                                  <*/



/*====================------------------------------------====================*/
/*===----                        debugging support                     ----===*/
/*====================------------------------------------====================*/
PRIV void  o___DEBUGGING_______o () { return; }

/*> char       /+----: report the full structure ---------------------------------+/                                                                                                                                                    <* 
 *> yDLST_showlist     (char a_header, void *a_file)                                                                                                                                                                                    <* 
 *> {                                                                                                                                                                                                                                   <* 
 *>    char        q         = '\x1F';                                                                                                                                                                                                  <* 
 *>    char        x_one     [20];                                                                                                                                                                                                      <* 
 *>    char        x_two     [20];                                                                                                                                                                                                      <* 
 *>    if (a_file  == NULL)  return -1;                                                                                                                                                                                                 <* 
 *>    if (p_lists == NULL)  return -2;                                                                                                                                                                                                 <* 
 *>    if (a_header == 'y') {                                                                                                                                                                                                           <* 
 *>       fprintf (a_file, "\n");                                                                                                                                                                                                       <* 
 *>       fprintf (a_file, "---name---------------- %c -id- %c ---self----- %c ---owner---- %c ---prev----- %c ---next----- %c cnt %c ---head----- %c ---tail----- %c foc %c act %c ups %c ---h_ups---- %c dws %c --h_downs--- %c\n",   <* 
 *>             q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q);                                                                                                                                    <* 
 *>    }                                                                                                                                                                                                                                <* 
 *>    fprintf (a_file, "%-23.23s %c %4d %c"                               , p_lists->name, q, p_lists->id, q);                                                                                                                         <* 
 *>    if (p_lists->prev == NULL)  sprintf (x_one, "((null))    ");                                                                                                                                                                     <* 
 *>    else                           sprintf (x_one, "%-10.10p", p_lists->prev);                                                                                                                                                       <* 
 *>    if (p_lists->next == NULL)  sprintf (x_two, "((null))    ");                                                                                                                                                                     <* 
 *>    else                           sprintf (x_two, "%-10.10p", p_lists->next);                                                                                                                                                       <* 
 *>    fprintf (a_file, " %-10.10p %c %-12.12s %c %-12.12s %c %-12.12s %c" , p_lists, q, " ", q, x_one, q, x_two, q);                                                                                                                   <* 
 *>    if (p_lists->head    == NULL)  sprintf (x_one, "((null))    ");                                                                                                                                                                  <* 
 *>    else                           sprintf (x_one, "%-10.10p", p_lists->head);                                                                                                                                                       <* 
 *>    if (p_lists->tail    == NULL)  sprintf (x_two, "((null))    ");                                                                                                                                                                  <* 
 *>    else                           sprintf (x_two, "%-10.10p", p_lists->tail);                                                                                                                                                       <* 
 *>    fprintf (a_file, " %3d %c %-12.12s %c %-12.12s %c"                  , p_lists->num, q, x_one, q, x_two, q);                                                                                                                      <* 
 *>    fprintf (a_file, "  %c  %c  %c  %c"                                 , ' ', q, ' ', q);                                                                                                                                           <* 
 *>    fprintf (a_file, "     %c %-12.12s %c     %c %-12.12s %c"           , q, " ", q, q, " ", q);                                                                                                                                     <* 
 *>    fprintf (a_file, "\n");                                                                                                                                                                                                          <* 
 *>    return 0;                                                                                                                                                                                                                        <* 
 *> }                                                                                                                                                                                                                                   <*/

/*> char       /+----: report the full structure ---------------------------------+/                                                        <* 
 *> yDLST_showlink     (void *a_file)                                                                                                       <* 
 *> {                                                                                                                                       <* 
 *>    char        q         = '\x1F';                                                                                                      <* 
 *>    char        x_one     [20];                                                                                                          <* 
 *>    char        x_two     [20];                                                                                                          <* 
 *>    if (a_file  == NULL)  return -1;                                                                                                     <* 
 *>    if (p_lists == NULL)  return -2;                                                                                                     <* 
 *>    if (p_links == NULL)  return -3;                                                                                                     <* 
 *>    fprintf (a_file, "   %-20.20s %c %4d %c"                               , p_links->name, q, p_links->id, q);                          <* 
 *>    if (p_links->prev    == NULL)  sprintf (x_one, "((null))    ");                                                                      <* 
 *>    else                           sprintf (x_one, "%-10.10p", p_links->prev);                                                           <* 
 *>    if (p_links->next    == NULL)  sprintf (x_two, "((null))    ");                                                                      <* 
 *>    else                           sprintf (x_two, "%-10.10p", p_links->next);                                                           <* 
 *>    fprintf (a_file, " %-10.10p %c %-10.10p %c %-12.12s %c %-12.12s %c" , p_links, q, p_links->list, q, x_one, q, x_two, q);             <* 
 *>    fprintf (a_file, "   - %c %-12.12s %c %-12.12s %c"                  , q, " ", q, " ", q);                                            <* 
 *>    fprintf (a_file, "  %c  %c  %c  %c"                                 , p_links->focus, q, p_links->active, q);                        <* 
 *>    if (p_links->h_ups   == NULL)  sprintf (x_one, "((null))    ");                                                                      <* 
 *>    else                           sprintf (x_one, "%-10.10p", p_links->h_ups);                                                          <* 
 *>    if (p_links->h_downs == NULL)  sprintf (x_two, "((null))    ");                                                                      <* 
 *>    else                           sprintf (x_two, "%-10.10p", p_links->h_downs);                                                        <* 
 *>    fprintf (a_file, " %3d %c %-12.12s %c %3d %c %-10.10s %c"           , p_links->n_ups, q, x_one, q, p_links->n_downs, q, x_two, q);   <* 
 *>    fprintf (a_file, "\n");                                                                                                              <* 
 *>    return 0;                                                                                                                            <* 
 *> }                                                                                                                                       <*/

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_quiet    (void)
{
   yLOG_begin ("yDLST" , yLOG_SYSTEM, yLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_loud  (void)
{
   yLOG_begin ("yDLST" , yLOG_SYSTEM, yLOG_NOISE);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ydlst"        , YURG_ON);
   DEBUG_YDLST  yLOG_info     ("yDLST"   , yDLST_version   ());
   yDLST_begin ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ydlst__test_end    (void)
{
   yDLST_end   ();
   yLOG_end     ();
   return 0;
}







/*=============================[[ end-of-code ]]==============================*/
