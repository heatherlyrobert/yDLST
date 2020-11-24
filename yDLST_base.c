/*===========================[[ start-of-code ]]==============================*/

#include   "yDLST.h"
#include   "yDLST_priv.h"




/*===[ DEBUGGING MACROS ]===------------------------------*/
#define   DEBUG_TIES(BODY)    /* BODY */
/*> #define   DEBUG_TIES(BODY)    BODY                                                <*/




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
   snprintf (yDLST_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yDLST_ver;
}


/*====================------------------------------------====================*/
/*===----                     program level                            ----===*/
/*====================------------------------------------====================*/
PRIV void  o___PROGRAM_________o () { return; }

char       /*----: prepare the list library for use --------------------------*/
yDLST_init         (void)
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ydlst_list_init   ();
   rc = ydlst_line_init   ();
   rc = ydlst_focus_init  ();
   rc = ydlst_active_init ();
   rc = ydlst_seq_init    ();
   /*---(complete)-----------------------*/
   DEBUG_YDLST  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_purge        (void)
{
   ydlst_seq__purge ();
   ydlst_list_wrap  ();
   ydlst_line_wrap  ();
   return 0;
}

char         /*----: make sure all memory is freed at the end ----------------*/
yDLST_wrap         (void)
{
   /*---(locals)-------*-----------------*/
   int       rc        = 0;
   /*---(header)-------------------------*/
   DEBUG_YDLST  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = yDLST_purge       ();
   rc = ydlst_list_wrap   ();
   rc = ydlst_line_wrap   ();
   rc = ydlst_focus_wrap  ();
   rc = ydlst_active_wrap ();
   rc = ydlst_seq_wrap    ();
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
   s_active = ydlst_active_current ();
   s_focus  = ydlst_focus_current ();
   s_seq    = ydlst_seq_current ();
   return 0;
}

char
yDLST_restore           (void)
{
   yDLST_list_restore   (s_list);
   yDLST_line_restore   (s_line);
   ydlst_active_restore (s_active);
   ydlst_focus_restore  (s_focus);
   ydlst_seq_restore    (s_seq);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }


char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_quiet    (void)
{
   yLOGS_begin ("yDLST" , YLOG_SYS, YLOG_QUIET);
   yDLST_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_loud  (void)
{
   yLOGS_begin ("yDLST" , YLOG_SYS, YLOG_NOISE);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ydlst"        , YURG_ON);
   DEBUG_YDLST  yLOG_info     ("yDLST"   , yDLST_version   ());
   yDLST_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ydlst__test_end    (void)
{
   yDLST_wrap   ();
   yLOGS_end     ();
   return 0;
}







/*=============================[[ end-of-code ]]==============================*/
