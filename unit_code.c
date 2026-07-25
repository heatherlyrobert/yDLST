/*===========================[[ start-of-code ]]==============================*/
#include    "yDLST.h"
#include    "yDLST_priv.h"
#include    "unit_code.h"



static char u_home  [LEN_FULL]  = "";



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }


char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_quiet    (void)
{
   char        rc          =    0;
   char        x_argc      =    1;
   char       *x_argv [1]  = { "yDLST" };
   getcwd (u_home, LEN_PATH);
   rc = yURG_logger  (x_argc, x_argv);
   DEBUG_PROG   yLOG_value   ("logger"    , rc);
   rc = yURG_urgs    (x_argc, x_argv);
   DEBUG_PROG   yLOG_value   ("urgs"      , rc);
   yDLST_init (NULL, NULL);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ydlst__test_loud  (void)
{
   char        rc          =    0;
   char        x_argc      =    3;
   char       *x_argv [3]  = { "yDLST_unit", "@@kitchen", "@@ydlst" };
   getcwd (u_home, LEN_PATH);
   rc = yURG_logger  (x_argc, x_argv);
   DEBUG_PROG   yLOG_value   ("logger"    , rc);
   rc = yURG_urgs    (x_argc, x_argv);
   DEBUG_PROG   yLOG_value   ("urgs"      , rc);
   DEBUG_YDLST  yLOG_info   ("yDLST"   , yDLST_version   ());
   yDLST_init (NULL, NULL);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ydlst__test_end    (void)
{
   chdir (u_home);
   yDLST_wrap    ();
   yLOGS_end     ();
   return 0;
}
