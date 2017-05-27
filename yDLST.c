/*===========================[[ start-of-code ]]==============================*/

#include   "yDLST.h"
#include   "yDLST_priv.h"


tLOCAL    its;



/*===[ DEBUGGING MACROS ]===------------------------------*/
#define   DEBUG_TIES(BODY)    /* BODY */
/*> #define   DEBUG_TIES(BODY)    BODY                                                <*/


static char     *nada      = "(na)";


/*---(list of all lists)--------------*/
tLIST    *h_lists   = NULL;            /* head node pointer                   */
tLIST    *t_lists   = NULL;            /* tail node pointer                   */
int       n_lists   = 0;               /* number of lists                     */
int       i_lists   = 0;               /* next sequential list id             */
int       c_lists   = -1;              /* id of current list                  */
tLIST    *p_lists   = NULL;            /* pointer to current list             */
tLIST    *x_lists [INDEX_LIST];        /* hash index to list of all lists     */

/*---(list of all links)--------------*/
tLINK    *h_links   = NULL;            /* head node pointer                   */
tLINK    *t_links   = NULL;            /* tail node pointer                   */
int       n_links   = 0;               /* number of links                     */
int       i_links   = 0;               /* next sequential link id             */
int       c_links   = -1;              /* id of current link                  */
tLINK    *p_links   = NULL;            /* pointer to current link             */
tLINK    *x_links [INDEX_LINK];        /* hash index to list of all links     */

/*---(sub list)-----------------------*/
tLINK    *h_focus   = NULL;  /* head  */
tLINK    *t_focus   = NULL;  /* tail  */
int       n_focus   = 0;     /* num   */
int       c_focus   = -1;    /* current focus link                */
tLINK    *p_focus   = NULL;

/*---(active list)--------------------*/
tLINK    *h_active  = NULL;  /* head  */
tLINK    *t_active  = NULL;  /* tail  */
int       n_active  = 0;     /* num   */
int       c_active  = -1;    /* current active link               */
tLINK    *p_active  = NULL;

/*---(full ties list)-----------------*/
tTIES    *h_ties    = NULL;
tTIES    *t_ties    = NULL;
int       n_ties    = 0;
tTIES    *p_ties    = NULL;

/*---(dependency tree)----------------*/
tLINK    *h_tree    = NULL;
tLINK    *t_tree    = NULL;


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
   int       i         = 0;
   int       rc        = 0;
   /*---(make sure its clean)------------*/
   yDLST_end ();
   /*---(basic defaults)-----------------*/
   i_lists  = 0;
   c_lists  = -1;
   p_lists  = NULL;
   i_links  = 0;
   c_links  = -1;
   p_links  = NULL;
   c_focus  = -1;
   p_focus  = NULL;
   c_active = -1;
   p_active = NULL;
   /*---(cleanse indexes)----------------*/
   for (i = 0; i < INDEX_LIST; ++i)  x_lists [i] = NULL;
   for (i = 0; i < INDEX_LINK; ++i)  x_links [i] = NULL;
   /*---(tree head and tail)-------------*/
   rc = yDLST__float (&h_tree, "tree_head", NULL);
   if (rc != 0) return -1;
   rc = yDLST__float (&t_tree, "tree_tail", NULL);
   if (rc != 0) return -2;
   /*---(complete)-----------------------*/
   return 0;
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_end          (void)
{
   /*---(locals)-------*-----------------*/
   tLIST    *xlist     = NULL;
   tLIST    *xnext     = NULL;
   tTIES    *xtie      = NULL;
   tTIES    *xtien     = NULL;
   int       rc        = 0;
   /*---(kills all ties)-----------------*/
   /*
    *
    *
    *
    */
   /*---(wipe out the ties)--------------*/
   xtie  = h_ties;
   while (xtie  != NULL) {
      xtien  = xtie->f_ties;
      free (xtie);
      xtie = xtien;
   }
   /*---(wipe out the lists/links)-------*/
   xnext = h_lists;
   while (xnext != NULL) {
      xlist  = xnext;
      xnext  = xlist->f_lists;
      yDLST_destroy (xlist->id);
   }
   /*---(tree head and tail)-------------*/
   rc = yDLST__unfloat (&h_tree);
   if (rc != 0) return -1;
   rc = yDLST__unfloat (&t_tree);
   if (rc != 0) return -2;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    list setup and teardown                   ----===*/
/*====================------------------------------------====================*/
PRIV void  o___LISTS___________o () { return; }

char       /*----: prepare a new list for use --------------------------------*/
yDLST_create       (int *a_list, char *a_name, void *a_data)
{
   /*---(defenses)-----------------------*/
   if (a_list  == NULL)      return -1;   /* must take back new list pointer  */
   if (a_name  == NULL)      return -2;   /* gotta name it                    */
   /*---(locals)-------------------------*/
   tLIST    *xlist     = NULL;
   int       i         = 0;
   int       rc        = 0;
   /*---(create)-------------------------*/
   for (i = 0; i < 3; ++i) {
      xlist = (tLIST *) malloc(sizeof(tLIST));
      if (xlist != NULL)     break;
   }
   if (xlist == NULL)        return -3;
   /*---(index list)------------------*/
   rc = yDLST__list_index (xlist);
   if (rc != 0)              return -4;
   /*---(into list DLL)------------------*/
   xlist->f_lists = NULL;
   xlist->b_lists = NULL;
   if (t_lists == NULL) {    /* first list */
      h_lists          = xlist;
      t_lists          = xlist;
   } else {                /* list 2-n   */
      xlist->b_lists   = t_lists;
      t_lists->f_lists = xlist;
      t_lists          = xlist;
   }
   ++n_lists;
   /*---(initialize)---------------------*/
   xlist->head    = NULL;
   xlist->tail    = NULL;
   xlist->num     = 0;
   /*---(name the list)------------------*/
   xlist->name    = strdup(a_name);
   /*---(attach data)--------------------*/
   if (a_data != NULL)  xlist->data    = a_data;
   else                 xlist->data    = nada;
   /*---(save key values)----------------*/
   *a_list        = xlist->id;
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: clear all links from a list -------------------------------*/
yDLST_purge        (int a_list)
{
   /*---(locals)-------*-----------------*/
   tLIST    *xlist     = NULL;
   tLINK    *xlink     = NULL;
   tLINK    *xnext     = NULL;
   /*---(sort out which list)------------*/
   if (p_lists == NULL || a_list != c_lists) {
      xlist = yDLST__list_find (a_list, 'y');
      if (xlist == NULL)     return -1;
   } else  xlist = p_lists;
   /*---(walk through attached links)----*/
   xnext = xlist->head;
   while (xnext != NULL) {
      xlink  = xnext;
      xnext  = xlink->fore;
      yDLST_free (xlink->id);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: teardown the list after use ---------------------------*/
yDLST_destroy      (int a_list)
{
   /*---(locals)-------------------------*/
   tLIST    *xlist     = NULL;
   int       rc        = 0;
   /*---(sort out which list)------------*/
   if (p_lists == NULL || a_list != c_lists) {
      xlist = yDLST__list_find (a_list, 'y');
      if (xlist == NULL)     return -1;
   } else  xlist = p_lists;
   /*---(clear the links)-------------*/
   yDLST_purge (a_list);
   /*---(remove from index)-----------*/
   rc = yDLST__list_uindex (xlist);
   if (rc != 0)              return -4;
   /*---(remove from main DLL)-----------*/
   if (xlist->f_lists != NULL)  xlist->f_lists->b_lists = xlist->b_lists;
   else                         t_lists                 = xlist->b_lists;
   if (xlist->b_lists != NULL)  xlist->b_lists->f_lists = xlist->f_lists;
   else                         h_lists                 = xlist->f_lists;
   --n_lists;
   /*---(free main)----------------------*/
   if (xlist->name) free (xlist->name);
   free (xlist);
   xlist = NULL;    /* no danglers  */
   /*---(complete)-----------------------*/
   return 0;
}

void*      /*----: get a list from the list of all lists ---------------------*/
yDLST_lists        (int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_lists == NULL)        return NULL;
      p_lists = h_lists;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      if (p_lists == NULL)        return NULL;
      p_lists = p_lists->f_lists;
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_lists  = h_lists;
      while (i < a_index) {
         if (p_lists == NULL)     return NULL;
         p_lists = p_lists->f_lists;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_lists == NULL) {
      c_lists = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_lists = p_lists->id;
   /*---(complete)-----------------------*/
   return p_lists->data;
}

int        /*----: get a lists index from its name ---------------------------*/
yDLST_find         (char *a_name)
{
   /*---(locals)-------------------------*/
   tLIST    *xnext     = NULL;
   /*---(defenses)-----------------------*/
   if (a_name [0] == '\n')  return -1;
   /*---(search)-------------------------*/
   xnext = h_lists;
   while (xnext != NULL) {
      if (strcmp(xnext->name, a_name) == 0) return xnext->id;
      xnext = xnext->f_lists;
   }
   /*---(complete)-----------------------*/
   return -1;
}

char       /*----: add a list to the index -----------------------------------*/
yDLST__list_index  (tLIST *a_list)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLIST    *xnext     = NULL;
   /*---(initialize)---------------------*/
   a_list->id      = i_lists++;
   a_list->x_lists = NULL;
   /*---(get initial hash)---------------*/
   a = a_list->id % INDEX_LIST;
   xnext  = x_lists [a];
   if (xnext == NULL) {
      x_lists [a] = a_list;
      p_lists = a_list;
      c_lists = a_list->id;
      return 0;
   }
   /*---(follow list)--------------------*/
   while (xnext->x_lists != NULL) {
      if (xnext == a_list)   return -100;
      xnext = xnext->x_lists;
   }
   xnext->x_lists = a_list;
   /*---(save current keys)--------------*/
   p_lists = a_list;
   c_lists = a_list->id;
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: remove a list from the index ------------------------------*/
yDLST__list_uindex (tLIST *a_list)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLIST    *xcurr     = NULL;
   tLIST    *xnext     = NULL;
   /*---(get initial hash)---------------*/
   a = a_list->id % INDEX_LIST;
   xnext  = x_lists [a];
   if (xnext == NULL )  return -100;  /* couldn't find a real list in index!! */
   /*---(see if we're the hash head)-----*/
   if (xnext == a_list) {
      x_lists [a] = xnext->x_lists;
      p_lists = NULL;
      c_lists = -1;
      return 0;
   }
   /*---(else run the list)--------------*/
   while (xnext->x_lists != NULL) {
      xcurr  = xnext;
      xnext  = xnext->x_lists;
      if (xnext == a_list) {
         xcurr->x_lists = xnext->x_lists;
         p_lists = NULL;
         c_lists = -1;
         return 0;
      }
   }
   p_lists = NULL;
   c_lists = -1;
   /*---(complete)-----------------------*/
   return -2;
}

tLIST*     /*----: find a list based on index --------------------------------*/
yDLST__list_find   (int  a_index, char a_change)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLIST    *xnext     = NULL;
   /*---(look at index)------------------*/
   a      = a_index % INDEX_LIST;
   xnext  = x_lists [a];
   if (xnext == NULL )  return NULL;
   /*---(see if we're the hash head)-----*/
   while (xnext != NULL) {
      if (xnext->id == a_index)  {
         if (a_change == 'y') {
            p_lists = xnext;
            c_lists = a_index;
         }
         return xnext;
      }
      xnext = xnext->x_lists;
   }
   /*---(complete)-----------------------*/
   if (a_change == 'y') {
      p_lists = NULL;
      c_lists = -1;
   }
   return NULL;
}



/*====================------------------------------------====================*/
/*===----                        link management                       ----===*/
/*====================------------------------------------====================*/
PRIV void  o___LINKS___________o () { return; }

char       /*----: create a new, unattached link -------------------------*/
yDLST_new          (int a_list, int *a_link, char *a_name, void *a_data)
{
   /*---(locals)-------------------------*/
   tLIST    *xlist     = NULL;
   tLINK    *xlink     = NULL;
   int       i         = 0;
   int       rc        = 0;
   /*---(sort out which list)------------*/
   if (p_lists == NULL || a_list != c_lists) {
      xlist = yDLST__list_find (a_list, 'y');
      if (xlist == NULL)     return -1;
   } else  xlist = p_lists;
   /*---(create link)-----------------*/
   for (i = 0; i < 3; ++i) {
      xlink = (tLINK *) malloc(sizeof(tLINK));
      if (xlink != NULL) break;
   }
   if (xlink == NULL)        return -2;
   /*---(index list)------------------*/
   rc = yDLST__link_index (xlink);
   if (rc != 0)              return -4;
   /*---(into list of all links)------*/
   xlink->f_links   = NULL;
   xlink->b_links   = NULL;
   if (t_links == NULL) {    /* first link */
      h_links            = xlink;
      t_links            = xlink;
   } else {                /* link 2-n   */
      xlink->b_links     = t_links;
      t_links->f_links   = xlink;
      t_links            = xlink;
   }
   ++n_links;
   /*---(tie to its owner)------------*/
   xlink->list      = xlist;
   /*---(into lists links)------------*/
   xlink->fore      = NULL;
   xlink->back      = NULL;
   if (xlist->tail == NULL) {    /* first link */
      xlist->head       = xlink;
      xlist->tail       = xlink;
   } else {                /* link 2-n   */
      xlink->back        = xlist->tail;
      xlist->tail->fore = xlink;
      xlist->tail       = xlink;
   }
   ++xlist->num;
   /*---(sub lists)-------------------*/
   xlink->focus     = '-';
   xlink->f_focus   = NULL;
   xlink->b_focus   = NULL;
   xlink->active    = '-';
   xlink->f_active  = NULL;
   xlink->b_active  = NULL;
   /*---(dependencies)----------------*/
   xlink->h_ups     = NULL;
   xlink->n_ups     = 0;
   xlink->h_downs   = NULL;
   xlink->n_downs   = 0;
   /*---(name the link)------------------*/
   if (a_name != NULL)  xlink->name    = strdup(a_name);
   else                 xlink->name    = nada;
   /*---(attach data)--------------------*/
   if (a_data != NULL)  xlink->data    = a_data;
   else                 xlink->data    = nada;
   /*---(save key values)----------------*/
   if (a_link != NULL) *a_link = xlink->id;
   /*---(complete)--------------------*/
   return 0;
}

char       /*----: destroy a link ----------------------------------------*/
yDLST_free         (int  a_link)
{
   /*---(locals)-------------------------*/
   tLIST    *xlist     = NULL;
   tLINK    *xlink     = NULL;
   int       rc        = 0;
   /*---(defenses)-----------------------*/
   if (a_link     <   0  )   return -1;
   /*---(sort out which list)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'n');
      if (xlink == NULL)     return -2;
   } else  xlink = p_links;
   xlist  = xlink->list;
   /*---(check on focus and active)------*/
   yDLST_focus_off  (a_link);
   yDLST_active_off (a_link);
   /*---(remove from list of all links)--*/
   if (xlink->f_links != NULL)  xlink->f_links->b_links = xlink->b_links;
   else                         t_links                 = xlink->b_links;
   if (xlink->b_links != NULL)  xlink->b_links->f_links = xlink->f_links;
   else                         h_links                 = xlink->f_links;
   --n_links;
   /*---(remove from main DLL)-----------*/
   if (xlink->fore != NULL)  xlink->fore->back    = xlink->back;
   else                      xlist->tail          = xlink->back;
   if (xlink->back != NULL)  xlink->back->fore    = xlink->fore;
   else                      xlist->head          = xlink->fore;
   --xlist->num;
   /*---(remove from index)-----------*/
   yDLST__link_uindex (xlink);
   if (rc != 0)              return -4;
   /*---(free main)----------------------*/
   if (xlink->name != NULL && xlink->name != nada) free(xlink->name);
   free (xlink);
   /*---(complete)-----------------------*/
   return 0;
}

void*      /*----: get a link from the focus list ----------------------------*/
yDLST_links        (int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_links == NULL)        return NULL;
      p_links = h_links;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      if (p_links == NULL)        return NULL;
      p_links = p_links->f_links;
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_links  = h_links;
      while (i < a_index) {
         if (p_links == NULL)     return NULL;
         p_links = p_links->f_links;
         ++i;
      }
   }
   /*> else if (c_links != a_index) {                                                 <* 
    *>    while (i < a_index) {                                                       <* 
    *>       if (p_links == NULL)     return NULL;                                    <* 
    *>       p_links = p_links->f_links;                                              <* 
    *>       ++i;                                                                     <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*---(defense for dereference)--------*/
   if (p_links == NULL) {
      c_links = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_links = p_links->id;
   /*---(complete)-----------------------*/
   return p_links->data;
}

void*      /*----: get a link from a specific list ---------------------------*/
yDLST_list         (int a_list, int a_index)
{
   /*---(locals)-------*-----------------*/
   tLIST    *xlist     = NULL;
   int       i         = 0;
   /*---(sort out which list)------------*/
   if (a_list == CURR)  a_list = c_lists;
   if (p_lists == NULL || a_list != c_lists) {
      xlist = yDLST__list_find (a_list, 'y');
      if (xlist == NULL)     return NULL;
   } else  xlist = p_lists;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_links == NULL)        return NULL;
      p_links = xlist->head;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      if (p_links == NULL)        return NULL;
      p_links = p_links->fore;
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_links  = xlist->head;
      while (i < a_index) {
         if (p_links == NULL)     return NULL;
         p_links = p_links->fore;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_links == NULL) {
      c_links = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_links = p_links->id;
   /*---(complete)-----------------------*/
   return p_links->data;
}

int        /*----: get a links index from its name ---------------------------*/
yDLST_search       (char *a_name)
{
   /*---(locals)-------------------------*/
   tLINK    *xnext     = NULL;
   /*---(defenses)-----------------------*/
   if (a_name [0] == '\n')  return -1;
   /*---(search)-------------------------*/
   xnext = h_links;
   while (xnext != NULL) {
      if (strcmp(xnext->name, a_name) == 0) return xnext->id;
      xnext = xnext->f_links;
   }
   /*---(complete)-----------------------*/
   return -1;
}

void*      /*----: get a specifically indexed link from links ----------------*/
yDLST_index        (int a_index)
{
   /*---(for specific link)--------------*/
   p_links = h_links;
   while (p_links != NULL) {
      if (p_links->id == a_index) break;
      p_links = p_links->f_links;
   }
   /*---(defense for dereference)--------*/
   if (p_links == NULL) {
      c_links = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_links = p_links->id;
   /*---(complete)-----------------------*/
   return p_links->data;
}

char       /*----: specialty for creating tree head and tail -------------*/
yDLST__float       (tLINK **a_link, char *a_name, void *a_data)
{
   /*---(locals)-------------------------*/
   tLINK    *xlink     = NULL;
   int       i         = 0;
   /*---(defense)---------------------*/
   if ( a_link == NULL)      return -1;
   /*---(create link)-----------------*/
   for (i = 0; i < 3; ++i) {
      xlink = (tLINK *) malloc(sizeof(tLINK));
      if (xlink != NULL) break;
   }
   if (xlink == NULL)        return -2;
   /*---(index list)------------------*/
   xlink->id        = -1;
   /*---(into list of all links)------*/
   xlink->f_links   = NULL;
   xlink->b_links   = NULL;
   /*---(tie to its owner)------------*/
   xlink->list      = NULL;
   /*---(into lists links)------------*/
   xlink->fore      = NULL;
   xlink->back      = NULL;
   /*---(sub lists)-------------------*/
   xlink->focus     = '-';
   xlink->f_focus   = NULL;
   xlink->b_focus   = NULL;
   xlink->active    = '-';
   xlink->f_active  = NULL;
   xlink->b_active  = NULL;
   /*---(dependencies)----------------*/
   xlink->h_ups     = NULL;
   xlink->n_ups     = 0;
   xlink->h_downs   = NULL;
   xlink->n_downs   = 0;
   /*---(name the link)------------------*/
   if (a_name != NULL)  xlink->name    = strdup(a_name);
   else                 xlink->name    = nada;
   /*---(attach data)--------------------*/
   if (a_data != NULL)  xlink->data    = a_data;
   else                 xlink->data    = nada;
   /*---(save key values)----------------*/
   if (a_link != NULL) *a_link = xlink;
   /*---(complete)--------------------*/
   return 0;
}

char       /*----: create a new, unattached link -------------------------*/
yDLST__unfloat     (tLINK **a_link)
{
   /*---(defenses)-----------------------*/
   if (  a_link == NULL) return 0;
   if ( *a_link == NULL) return 0;
   tLINK    *xlink     = *a_link;
   /*---(free main)----------------------*/
   if (xlink->name != NULL && xlink->name != nada)  free(xlink->name);
   free (*a_link);
   *a_link = NULL;
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: add a list to the index -----------------------------------*/
yDLST__link_index  (tLINK *a_link)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLINK    *xnext     = NULL;
   /*---(initialize)---------------------*/
   a_link->id      = i_links++;
   a_link->x_links = NULL;
   /*---(get initial hash)---------------*/
   a = a_link->id % INDEX_LINK;
   xnext  = x_links [a];
   if (xnext == NULL) {
      x_links [a] = a_link;
      p_links = a_link;
      c_links = a_link->id;
      return 0;
   }
   /*---(follow list)--------------------*/
   while (xnext->x_links != NULL) {
      if (xnext == a_link)   return -100;
      xnext = xnext->x_links;
   }
   xnext->x_links = a_link;
   /*---(save current keys)--------------*/
   p_links = a_link;
   c_links = a_link->id;
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: remove a list from the index ------------------------------*/
yDLST__link_uindex (tLINK *a_link)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLINK    *xcurr     = NULL;
   tLINK    *xnext     = NULL;
   /*---(defenses)-----------------------*/
   if (a_link     == NULL)  return -1;
   if (a_link->id <   0  )  return -2;
   /*---(get initial hash)---------------*/
   a = a_link->id % INDEX_LINK;
   xnext  = x_links [a];
   if (xnext == NULL )  return -100;  /* couldn't find a real list in index!! */
   /*---(see if we're the hash head)-----*/
   if (xnext == a_link) {
      x_links [a] = xnext->x_links;
      p_links = NULL;
      c_links = -1;
      return 0;
   }
   /*---(else run the list)--------------*/
   while (xnext->x_links != NULL) {
      xcurr  = xnext;
      xnext  = xnext->x_links;
      if (xnext == a_link) {
         xcurr->x_links = xnext->x_links;
         p_links = NULL;
         c_links = -1;
         return 0;
      }
   }
   p_links = NULL;
   c_links = -1;
   /*---(complete)-----------------------*/
   return -2;
}

tLINK*     /*----: find a link based on index --------------------------------*/
yDLST__link_find   (int  a_index, char a_change)
{
   /*---(locals)-------------------------*/
   int       a         = 0;
   tLINK    *xnext     = NULL;
   /*---(defenses)-----------------------*/
   if (a_index    <   0  )  return NULL;
   /*---(look at index)------------------*/
   a      = a_index % INDEX_LINK;
   xnext  = x_links [a];
   if (xnext == NULL )  return NULL;
   /*---(see if we're the hash head)-----*/
   while (xnext != NULL) {
      if (xnext->id == a_index)  {
         if (a_change == 'y') {
            p_links = xnext;
            c_links = a_index;
         }
         return xnext;
      }
      xnext = xnext->x_links;
   }
   /*---(if not found)-------------------*/
   if (a_change == 'y') {
      p_links = NULL;
      c_links = -1;
   }
   /*---(complete)-----------------------*/
   return NULL;
}



/*====================------------------------------------====================*/
/*===----                          focus list                          ----===*/
/*====================------------------------------------====================*/
PRIV void  o___FOCUSES_________o () { return; }

char       /*----: add the link to the focus list ----------------------------*/
yDLST_focus_on     (int a_link)
{
   /*---(locals)-------------------------*/
   tLINK    *xlink     = NULL;
   /*---(sort out which link)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)     return -1;
   } else  xlink = p_links;
   /*---(check for already on)--------*/
   if (xlink->focus  == 'y') return -2;   /* stop deadly cycle creation */
   /*---(hook it up)------------------*/
   xlink->f_focus   = NULL;
   xlink->b_focus   = NULL;
   if (t_focus == NULL) {    /* first link */
      h_focus           = xlink;
      t_focus           = xlink;
   } else {                /* link 2-n   */
      xlink->b_focus   = t_focus;
      t_focus->f_focus  = xlink;
      t_focus           = xlink;
   }
   ++n_focus;
   xlink->focus = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: remove the link to the focus list -------------------------*/
yDLST_focus_off    (int  a_link)
{
   /*---(locals)-------------------------*/
   tLINK    *xlink     = NULL;
   /*---(sort out which list)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)     return -1;
   } else  xlink = p_links;
   /*---(check for already off)-------*/
   if (xlink->focus  == '-') return -2;   /* stop double off            */
   /*---(remove from dll)----------------*/
   if (xlink->f_focus != NULL)  xlink->f_focus->b_focus  = xlink->b_focus;
   else                         t_focus                  = xlink->b_focus;
   if (xlink->b_focus != NULL)  xlink->b_focus->f_focus  = xlink->f_focus;
   else                         h_focus                  = xlink->f_focus;
   --n_focus;
   xlink->focus = '-';
   /*---(complete)-----------------------*/
   return 0;
}

void*      /*----: get a link from the focus list ----------------------------*/
yDLST_focus        (int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_focus == NULL)        return NULL;
      p_focus = h_focus;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      if (p_focus == NULL)        return NULL;
      p_focus = p_focus->f_focus;
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_focus  = h_focus;
      while (i < a_index) {
         if (p_focus == NULL)     return NULL;
         p_focus = p_focus->f_focus;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_focus == NULL) {
      c_focus = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_focus = p_focus->id;
   /*---(complete)-----------------------*/
   return p_focus->data;
}



/*====================------------------------------------====================*/
/*===----                         active list                          ----===*/
/*====================------------------------------------====================*/
PRIV void  o___ACTIVES_________o () { return; }

char       /*----: add the link to the active list ---------------------------*/
yDLST_active_on    (int  a_link)
{
   /*---(locals)-------------------------*/
   tLINK    *xlink     = NULL;
   /*---(sort out which list)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)      return -1;
   } else  xlink = p_links;
   /*---(check for already on)--------*/
   if (xlink->active == 'y') return -2;   /* stop deadly cycle creation */
   /*---(hook it up)------------------*/
   xlink->f_active  = NULL;
   xlink->b_active  = NULL;
   if (t_active == NULL) {    /* first link */
      h_active           = xlink;
      t_active           = xlink;
   } else {                /* link 2-n   */
      xlink->b_active    = t_active;
      t_active->f_active = xlink;
      t_active           = xlink;
   }
   ++n_active;
   xlink->active = 'y';
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: remove the link to the active list ------------------------*/
yDLST_active_off   (int a_link)
{
   /*---(locals)-------------------------*/
   tLINK    *xlink     = NULL;
   /*---(sort out which list)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)     return -1;
   } else  xlink = p_links;
   /*---(check for already off)-------*/
   if (xlink->active == '-') return -2;   /* stop double off            */
   /*---(remove from dll)----------------*/
   if (xlink->f_active != NULL)  xlink->f_active->b_active  = xlink->b_active;
   else                           t_active                    = xlink->b_active;
   if (xlink->b_active != NULL)  xlink->b_active->f_active  = xlink->f_active;
   else                           h_active                    = xlink->f_active;
   --n_active;
   xlink->active = '-';
   /*---(complete)-----------------------*/
   return 0;
}

void*      /*----: get a link from the active list ---------------------------*/
yDLST_active       (int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_active == NULL)        return NULL;
      p_active = h_active;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      if (p_active == NULL)        return NULL;
      p_active = p_active->f_active;
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_active  = h_active;
      while (i < a_index) {
         if (p_active == NULL)     return NULL;
         p_active = p_active->f_active;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_active == NULL) {
      c_active = -1;
      return NULL;
   }
   /*---(save)---------------------------*/
   c_active = p_active->id;
   /*---(complete)-----------------------*/
   return p_active->data;
}



/*====================------------------------------------====================*/
/*===----                            ties list                         ----===*/
/*====================------------------------------------====================*/
PRIV void  o___TIES____________o () { return; }

char       /*----: tie to links together (directionally) --------------------*/
yDLST_tie          (int a_up, int a_down, void *a_data)
{
   /*---(locals)-------------------------*/
   tLINK    *xup       = NULL;
   tLINK    *xdown     = NULL;
   tTIES    *xtie      = NULL;
   tTIES    *curr      = NULL;
   tTIES    *next      = NULL;
   int       i         = 0;
   /*---(defence : circular)-------------*/
   DEBUG_TIES ( printf ("begin TIE (%4d) to (%4d)\n", a_up, a_down); )
      if (a_up  == a_down)                          return -1;
   /*---(sort out upstream)--------------*/
   if (a_up   == -1) {
      xup   = h_tree;
   } else {
      if (p_links == NULL || a_up   != c_links) {
         xup   = yDLST__link_find (a_up  , 'n');
         if (xup   == NULL)                      return -2;
      } else  xup   = p_links;
   }
   DEBUG_TIES ( printf ("   1) found up link   (%4d) %9p\n", a_up, xup); )
      /*---(sort out downstream)------------*/
      if (a_down == -1) {
         xdown = t_tree;
      } else {
         if (p_links == NULL || a_down != c_links) {
            xdown = yDLST__link_find (a_down, 'n');
            if (xdown == NULL)                      return -3;
         } else  xdown = p_links;
      }
   DEBUG_TIES ( printf ("   2) found down link (%4d) %9p\n", a_down, xdown); )
      /*---(check for endpoint links)-------*/
      if (xup == h_tree || xdown == t_tree) {
         if (xup   == h_tree && xdown->n_ups > 0) {
            DEBUG_TIES ( printf ("   3) unnecessary h_tree link request, stop\n"); )
               return -4;
         } else if (xdown == t_tree && xup->n_downs > 0) {
            DEBUG_TIES ( printf ("   3) unnecessary t_tree link request, stop\n"); )
               return -5;
         }
         DEBUG_TIES ( printf ("   3) h_tree/t_tree fine, continue\n"); )
      } else {
         DEBUG_TIES ( printf ("   3) not a h_tree or t_tree link request\n"); )
      }
   /*---(look for existing link)---------*/
   DEBUG_TIES ( printf ("   4) look for existing link :: "); )
      next = xup->h_downs;
   while (next != NULL) {
      if (next->down == xdown) {
         DEBUG_TIES ( printf ("exists, stop\n"); )
            return  1;
      }
      next = next->f_downs;
   }
   DEBUG_TIES ( printf ("not found, continue\n"); )
      /*---(create link)--------------------*/
      DEBUG_TIES ( printf ("   5) malloc the tie\n"); )
      for (i = 0; i < 3; ++i) {
         xtie  = (tTIES *) malloc(sizeof(tTIES));
         if (xtie  != NULL) break;
      }
   if (xtie  == NULL)                            return -6;
   /*---(into list of all links)---------*/
   DEBUG_TIES ( printf ("   6) attach tie into dll\n"); )
      xtie->f_ties   = NULL;
   xtie->b_ties   = NULL;
   if (t_ties == NULL) {    /* first link */
      h_ties            = xtie;
      t_ties            = xtie;
   } else {                /* link 2-n   */
      xtie->b_ties      = t_ties;
      t_ties->f_ties    = xtie;
      t_ties            = xtie;
   }
   ++n_ties;
   /*---(tie upstream)-------------------*/
   DEBUG_TIES ( printf ("   7) tie to up link down sll\n"); )
      xtie->up        = xup;
   xtie->f_downs   = NULL;
   if (xup->h_downs == NULL) xup->h_downs = xtie;
   else {
      next = xup->h_downs;
      while (next != NULL) {
         curr = next;
         next = next->f_downs;
      }
      curr->f_downs = xtie;
   }
   ++xup->n_downs;
   /*---(tie downstream)-----------------*/
   DEBUG_TIES ( printf ("   8) tie to down links up sll\n"); )
      xtie->down      = xdown;
   xtie->f_ups     = NULL;
   if (xdown->h_ups == NULL) xdown->h_ups = xtie;
   else {
      next = xdown->h_ups;
      while (next != NULL) {
         curr = next;
         next = next->f_ups;
      }
      curr->f_ups = xtie;
   }
   ++xdown->n_ups;
   /*---(attach data)--------------------*/
   DEBUG_TIES ( printf ("   9) attach data\n"); )
      if (a_data != NULL)  xtie->data    = a_data;
      else                 xtie->data    = nada;
   DEBUG_TIES ( printf ("   A) DONE\n"); )
      /*---(fix other attachments)----------*/
      if (a_up   != -1 && a_down != -1) {
         /*---(fix up downstream)--------------*/
         if (a_down != -1) {
            DEBUG_TIES ( printf ("--------------------\n"); )
               DEBUG_TIES ( printf ("I)   check so see if down (%4d) is attached to h_tree (with untie)\n", a_down); )
               yDLST_untie ( -1, a_down);
            DEBUG_TIES ( printf ("--------------------\n"); )
               DEBUG_TIES ( printf ("II)  check to see if down (%4d) needs a t_tree link\n", a_down); )
               yDLST_tie (a_down,   -1  , "to_tail");
         }
         /*---(fix up upstream)----------------*/
         if (a_up   != -1) {
            DEBUG_TIES ( printf ("--------------------\n"); )
               DEBUG_TIES ( printf ("III) check to see if up   (%4d) is attached to t_tree (with untie)\n", a_up); )
               yDLST_untie (a_up, -1);
            DEBUG_TIES ( printf ("--------------------\n"); )
               DEBUG_TIES ( printf ("IV)  check to see if up   (%4d) needs a h_tree link\n", a_up); )
               yDLST_tie (  -1  , a_up  , "from_head");
         }
      }
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: tie to links together (directionally) --------------------*/
yDLST_untie        (int a_up, int a_down)
{
   /*---(locals)-------------------------*/
   tLINK    *xup       = NULL;
   tLINK    *xdown     = NULL;
   tTIES    *xtie      = NULL;
   tTIES    *curr      = NULL;
   tTIES    *next      = NULL;
   /*---(defence : circular)-------------*/
   DEBUG_TIES ( printf ("begin UNTIE (%4d) to (%4d)\n", a_up, a_down); )
      if (a_up  == a_down)                          return -1;
   /*---(sort out upstream)--------------*/
   DEBUG_TIES ( printf ("   a) sort upstream...\n"); )
      if (a_up   == -1) {
         xup   = h_tree;
      } else {
         if (p_links == NULL || a_up   != c_links) {
            xup   = yDLST__link_find (a_up  , 'n');
            if (xup   == NULL)                      return -2;
         } else  xup   = p_links;
      }
   /*---(sort out downstream)------------*/
   DEBUG_TIES ( printf ("   b) sort downstream...\n"); )
      if (a_down == -1) {
         xdown = t_tree;
      } else {
         if (p_links == NULL || a_down != c_links) {
            xdown = yDLST__link_find (a_down, 'n');
            if (xdown == NULL)                      return -3;
         } else  xdown = p_links;
      }
   /*---(find tie)-----------------------*/
   DEBUG_TIES ( printf ("   c) xup  = (%4d) %9p, xdown= (%4d) %9p :: ", a_up, xup, a_down, xdown); )
      xtie = yDLST__tie_find (xup, xdown);
   if (xtie == NULL) {
      DEBUG_TIES ( printf ("not found, stop\n"); )
         return -4;
   }
   DEBUG_TIES ( printf ("found, continue\n"); )
      /*---(remove from dll)----------------*/
      DEBUG_TIES ( printf ("   d) remove from dll...\n"); )
      if (xtie->f_ties != NULL)  xtie->f_ties->b_ties  = xtie->b_ties;
      else                       t_ties                = xtie->b_ties;
   if (xtie->b_ties != NULL)  xtie->b_ties->f_ties  = xtie->f_ties;
   else                       h_ties                = xtie->f_ties;
   --n_ties;
   /*---(untie upstream)-----------------*/
   DEBUG_TIES ( printf ("   e) untie upstream link...\n"); )
      curr   = xup->h_downs;
   if      (curr == NULL)  ;
   else if (curr->down == xdown)  xup->h_downs = curr->f_downs;
   else {
      next = curr->f_downs;
      while (next != NULL) {
         if (next->down == xdown) {
            curr->f_downs = next->f_downs;
            break;
         }
         curr = next;
         next = curr->f_downs;
      }
   }
   --xup->n_downs;
   /*---(untie downstream)---------------*/
   DEBUG_TIES  ( printf ("   f) untie downstream link...\n"); )
      curr   = xdown->h_ups;
   if      (curr == NULL)  ;
   else if (curr->up   == xup) xdown->h_ups = curr->f_ups;
   else {
      next = curr->f_ups;
      while (next != NULL) {
         DEBUG_TIES ( printf ("      up=%9p, dn=%9p\n", next->up, next->down); )
            if (next->up == xup) {
               curr->f_ups = next->f_ups;
               break;
            }
         curr = next;
         next = curr->f_downs;
      }
   }
   --xdown->n_ups;
   /*---(free tie)-----------------------*/
   DEBUG_TIES ( printf ("   h) DONE...\n"); )
      /*---(fix other attachments)----------*/
      char   up_ups   = 'y';
   char   up_downs = 'y';
   char   dn_ups   = 'y';
   char   dn_downs = 'y';
   if (a_up   != -1 && a_down != -1) {
      /*---(test linkage)-------------------*/
      if (xup->h_ups     == NULL || xup->h_ups->up       == h_tree) up_ups   = '-';
      if (xdown->h_ups   == NULL || xdown->h_ups->up     == h_tree) dn_ups   = '-';
      if (xup->h_downs   == NULL || xup->h_downs->down   == t_tree) up_downs = '-';
      if (xdown->h_downs == NULL || xdown->h_downs->down == t_tree) dn_downs = '-';
      /*---(floating links)-----------------*/
      if (up_ups == '-' && up_downs == '-') {
         yDLST_untie (  -1   , a_up   );
         yDLST_untie ( a_up  ,  -1    );
      }
      if (dn_ups == '-' && dn_downs == '-') {
         yDLST_untie (  -1   , a_down );
         yDLST_untie ( a_down, -1    );
      }
      /*---(check half ties)----------------*/
      if        (up_ups == '-' && up_downs == 'y') {
         yDLST_tie   (  -1   , a_up   , "from_head");
      } else if (up_ups == 'y' && up_downs == '-') {
         yDLST_tie   ( a_up  ,  -1    , "to_tail");
      }
      if        (dn_ups == '-' && dn_downs == 'y') {
         yDLST_tie   (  -1   , a_down , "from_head");
      } else if (dn_ups == 'y' && dn_downs == '-') {
         yDLST_tie   ( a_down,  -1    , "to_tail");
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

void*      /*----: get a tie from the ties list ------------------------------*/
yDLST_ties         (int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (h_ties == NULL)        return NULL;
      p_ties = h_ties;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      while (p_ties != NULL) {
         p_ties = p_ties->f_ties;
         if (p_ties == NULL)        return NULL;
         if (p_ties->up   == h_tree) continue;
         if (p_ties->down == t_tree) continue;
         break;
      }
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_ties  = h_ties;
      if (p_ties == NULL)     return NULL;
      while (i < a_index) {
         p_ties = p_ties->f_ties;
         if (p_ties == NULL)     return NULL;
         if (p_ties->up   == h_tree) continue;
         if (p_ties->down == t_tree) continue;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_ties == NULL) return NULL;
   /*---(complete)-----------------------*/
   return p_ties->data;
}

void*      /*----: get a downward link ---------------------------------------*/
yDLST_downs        (int a_link, int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   tLINK    *xlink     = NULL;
   /*---(sort out which link)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)     return NULL;
   } else  xlink = p_links;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (xlink->h_downs == NULL)        return NULL;
      p_ties = xlink->h_downs;
      if (p_ties->down   == t_tree)      return NULL;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      while (p_ties != NULL) {
         p_ties = p_ties->f_downs;
         if (p_ties == NULL)        return NULL;
         if (p_ties->down == t_tree) continue;
         break;
      }
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_ties  = xlink->h_downs;
      if (p_ties == NULL)     return NULL;
      if (p_ties->down == t_tree) return NULL;
      while (i < a_index) {
         p_ties = p_ties->f_downs;
         if (p_ties == NULL)     return NULL;
         if (p_ties->down == t_tree) continue;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_ties == NULL) return NULL;
   /*---(complete)-----------------------*/
   return p_ties->down->data;
}

void*      /*----: get an upward link ----------------------------------------*/
yDLST_ups          (int a_link, int a_index)
{
   /*---(locals)-------*-----------------*/
   int       i         = 0;
   tLINK    *xlink     = NULL;
   /*---(sort out which link)------------*/
   if (p_links == NULL || a_link != c_links) {
      xlink = yDLST__link_find (a_link, 'y');
      if (xlink == NULL)     return NULL;
   } else  xlink = p_links;
   /*---(for head link)------------------*/
   if      (a_index == HEAD)  {
      if (xlink->h_ups == NULL)        return NULL;
      p_ties = xlink->h_ups;
      if (p_ties->up   == h_tree)      return NULL;
   }
   /*---(for next link)------------------*/
   else if (a_index == NEXT) {
      while (p_ties != NULL) {
         p_ties = p_ties->f_ups;
         if (p_ties == NULL)        return NULL;
         if (p_ties->up   == h_tree) continue;
         break;
      }
   }
   /*---(for curr link)------------------*/
   else if (a_index == CURR) {
      ;
   }
   /*---(for specific link)--------------*/
   else {
      p_ties  = xlink->h_ups;
      if (p_ties == NULL)     return NULL;
      if (p_ties->up   == h_tree) return NULL;
      while (i < a_index) {
         p_ties = p_ties->f_ups;
         if (p_ties == NULL)     return NULL;
         if (p_ties->up   == h_tree) continue;
         ++i;
      }
   }
   /*---(defense for dereference)--------*/
   if (p_ties == NULL) return NULL;
   /*---(complete)-----------------------*/
   return p_ties->up->data;
}

tTIES*     /*----: find a tie based on two indexes ---------------------------*/
yDLST__tie_find    (tLINK* a_up, tLINK *a_down)
{
   /*---(locals)-------------------------*/
   tTIES    *next     = NULL;
   /*---(defenses)-----------------------*/
   if (a_up   == NULL)            return NULL;
   if (a_down == NULL)            return NULL;
   /*---(see if we're the hash head)-----*/
   /*> printf ("         so into the find (past defenses)\n");                        <*/
   next = a_up->h_downs;
   /*> printf ("         looking for    %9p\n", a_down);                              <*/
   /*> printf ("         downs header = %9p\n", next);                                <*/
   if (next       == NULL  )      return NULL;
   if (next->down == NULL  )      return NULL;
   /*> printf ("         header points  %9p\n", next->down);                          <*/
   if (next->down == a_down) {
      /*> printf ("         FOUND\n");                                                <*/
      return next;
   }
   /*> printf ("         through simple checks\n");                                   <*/
   next = next->f_downs;
   while (next != NULL) {
      /*> printf ("         next points at %9p\n", next->down);                       <*/
      if (next->down == a_down) {
         /*> printf ("         FOUND\n");                                             <*/
         return next;
      }
      next = next->f_downs;
   }
   /*> printf ("         no more\n");                                                 <*/
   /*---(complete)-----------------------*/
   return NULL;
}



/*====================------------------------------------====================*/
/*===----                        debugging support                     ----===*/
/*====================------------------------------------====================*/
PRIV void  o___DEBUGGING_______o () { return; }

char       /*----: report the full structure ---------------------------------*/
yDLST_showlist     (char a_header, void *a_file)
{
   char        q         = '\x1F';
   char        x_one     [20];
   char        x_two     [20];
   if (a_file  == NULL)  return -1;
   if (p_lists == NULL)  return -2;
   if (a_header == 'y') {
      fprintf (a_file, "\n");
      fprintf (a_file, "---name---------------- %c -id- %c ---self----- %c ---owner---- %c ---prev----- %c ---next----- %c cnt %c ---head----- %c ---tail----- %c foc %c act %c ups %c ---h_ups---- %c dws %c --h_downs--- %c\n",
            q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q, q);
   }
   fprintf (a_file, "%-23.23s %c %4d %c"                               , p_lists->name, q, p_lists->id, q);
   if (p_lists->b_lists == NULL)  sprintf (x_one, "((null))    ");
   else                           sprintf (x_one, "%-10.10p", p_lists->b_lists);
   if (p_lists->f_lists == NULL)  sprintf (x_two, "((null))    ");
   else                           sprintf (x_two, "%-10.10p", p_lists->f_lists);
   fprintf (a_file, " %-10.10p %c %-12.12s %c %-12.12s %c %-12.12s %c" , p_lists, q, " ", q, x_one, q, x_two, q);
   if (p_lists->head    == NULL)  sprintf (x_one, "((null))    ");
   else                           sprintf (x_one, "%-10.10p", p_lists->head);
   if (p_lists->tail    == NULL)  sprintf (x_two, "((null))    ");
   else                           sprintf (x_two, "%-10.10p", p_lists->tail);
   fprintf (a_file, " %3d %c %-12.12s %c %-12.12s %c"                  , p_lists->num, q, x_one, q, x_two, q);
   fprintf (a_file, "  %c  %c  %c  %c"                                 , ' ', q, ' ', q);
   fprintf (a_file, "     %c %-12.12s %c     %c %-12.12s %c"           , q, " ", q, q, " ", q);
   fprintf (a_file, "\n");
   return 0;
}

char       /*----: report the full structure ---------------------------------*/
yDLST_showlink     (void *a_file)
{
   char        q         = '\x1F';
   char        x_one     [20];
   char        x_two     [20];
   if (a_file  == NULL)  return -1;
   if (p_lists == NULL)  return -2;
   if (p_links == NULL)  return -3;
   fprintf (a_file, "   %-20.20s %c %4d %c"                               , p_links->name, q, p_links->id, q);
   if (p_links->back    == NULL)  sprintf (x_one, "((null))    ");
   else                           sprintf (x_one, "%-10.10p", p_links->back);
   if (p_links->fore    == NULL)  sprintf (x_two, "((null))    ");
   else                           sprintf (x_two, "%-10.10p", p_links->fore);
   fprintf (a_file, " %-10.10p %c %-10.10p %c %-12.12s %c %-12.12s %c" , p_links, q, p_links->list, q, x_one, q, x_two, q);
   fprintf (a_file, "   - %c %-12.12s %c %-12.12s %c"                  , q, " ", q, " ", q);
   fprintf (a_file, "  %c  %c  %c  %c"                                 , p_links->focus, q, p_links->active, q);
   if (p_links->h_ups   == NULL)  sprintf (x_one, "((null))    ");
   else                           sprintf (x_one, "%-10.10p", p_links->h_ups);
   if (p_links->h_downs == NULL)  sprintf (x_two, "((null))    ");
   else                           sprintf (x_two, "%-10.10p", p_links->h_downs);
   fprintf (a_file, " %3d %c %-12.12s %c %3d %c %-10.10s %c"           , p_links->n_ups, q, x_one, q, p_links->n_downs, q, x_two, q);
   fprintf (a_file, "\n");
   return 0;
}







/*=============================[[ end-of-code ]]==============================*/
