/*===========================[[ start-of-code ]]==============================*/

#include   "yDLST.h"
#include   "yDLST_priv.h"



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2011 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/




/*===[ DEBUGGING MACROS ]===------------------------------*/
#define   DEBUG_TIES(BODY)    /* BODY */
/*> #define   DEBUG_TIES(BODY)    BODY                                                <*/




static char      yDLST_ver [200] = "";

char    (*G_listwipe)      (void *a_data)  = NULL;
char    (*G_linewipe)      (void *a_data)  = NULL;



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
   snprintf (yDLST_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yDLST_ver;
}


/*====================------------------------------------====================*/
/*===----                     program level                            ----===*/
/*====================------------------------------------====================*/
PRIV void  o___PROGRAM_________o () { return; }

char       /*----: prepare the list library for use --------------------------*/
yDLST_init              (char *f_listwipe (void *), char f_linewipe (void *))
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(purge, just-inr-case)-----------*/
   rc = ydlst_line_purge_all ();
   DEBUG_YDLST  yLOG_value   ("line_purge", rc);
   rc = ydlst_list_purge     ();
   DEBUG_YDLST  yLOG_value   ("list_purge", rc);
   /*---(initialize)---------------------*/
   rc = ydlst_list_init   (f_listwipe);
   DEBUG_YDLST  yLOG_value   ("list_init" , rc);
   rc = ydlst_line_init   (f_linewipe);
   DEBUG_YDLST  yLOG_value   ("line_init" , rc);
   rc = ydlst_focus_init  ();
   DEBUG_YDLST  yLOG_value   ("focus_init", rc);
   rc = ydlst_active_init ();
   DEBUG_YDLST  yLOG_value   ("actv_init" , rc);
   rc = ydlst_seq_init    ();
   DEBUG_YDLST  yLOG_value   ("seq_init"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /*----: prepare the list library for use --------------------------*/
yDLST_config            (char *f_listwipe (void *), char f_linewipe (void *))
{
   ydlst_list_config (f_listwipe);
   ydlst_line_config (f_linewipe);
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_purge             (void)
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   rc = ydlst_seq__purge ();
   DEBUG_YDLST  yLOG_value   ("seq_wrap"  , rc);
   rc = ydlst_line_wrap  ();
   DEBUG_YDLST  yLOG_value   ("line_wrap" , rc);
   rc = ydlst_list_wrap  ();
   DEBUG_YDLST  yLOG_value   ("list_wrap" , rc);
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_wrap              (void)
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ydlst_focus_wrap  ();
   rc = ydlst_active_wrap ();
   rc = yDLST_purge       ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

static tLIST*   s_list   = NULL;
static tLINE*   s_line   = NULL;
static tLINE*   s_active = NULL;
static tLINE*   s_focus  = NULL;
static tSEQ*    s_seq    = NULL;



/*====================------------------------------------====================*/
/*===----                      pushing and popping                     ----===*/
/*====================------------------------------------====================*/
static void  o___PUSHPOP_________o () { return; }

char
yDLST_backup            (void)
{
   s_list   = yDLST_list_current ();
   s_line   = yDLST_line_current ();
   s_active = ydlst_active_current (NULL);
   s_focus  = ydlst_focus_current (NULL);
   s_seq    = ydlst_seq_current ();
   return 0;
}

char
yDLST_restore           (void)
{
   yDLST_list_restore   (s_list);
   yDLST_line_restore   (s_line);
   ydlst_active_restore (s_active, NULL);
   ydlst_focus_restore  (s_focus, NULL);
   ydlst_seq_restore    (s_seq);
   return 0;
}







/*=============================[[ end-of-code ]]==============================*/
