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
   snprintf (yDLST_ver, 100, "%s   %s : %s", t, YDLST_VER_NUM, YDLST_VER_TXT);
   return yDLST_ver;
}


/*====================------------------------------------====================*/
/*===----                   dlst setup and teardown                    ----===*/
/*====================------------------------------------====================*/
PRIV void  o___DLST____________o () { return; }

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
   ydlst_list_purge ();
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


char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_quiet    (void)
{
   yLOG_begin ("yDLST" , yLOG_SYSTEM, yLOG_QUIET);
   yDLST_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_loud  (void)
{
   yLOG_begin ("yDLST" , yLOG_SYSTEM, yLOG_NOISE);
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
   yLOG_end     ();
   return 0;
}







/*=============================[[ end-of-code ]]==============================*/
