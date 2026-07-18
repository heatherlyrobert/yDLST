/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"
#include    "unit_code.h"




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }


char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_quiet    (void)
{
   yLOGS_begin ("yDLST" , YLOG_SYS, YLOG_QUIET);
   yDLST_init (NULL, NULL);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_loud  (void)
{
   yLOGS_begin ("yDLST" , YLOG_SYS, YLOG_NOISE);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ydlst"        , YURG_ON);
   DEBUG_YDLST  yLOG_info     ("yDLST"   , yDLST_version   ());
   yDLST_init (NULL, NULL);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ydlst__test_end    (void)
{
   yDLST_wrap   ();
   yLOGS_end     ();
   return 0;
}
