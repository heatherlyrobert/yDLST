/*============================----beg-of-source---============================*/

/*===[[ SUMMARY ]]============================================================*

 *   yDLST is a specialty data structure that combines a quad/doubly linked
 *   list (full, list, focus, and active) with a dependency/requirement linking
 *   system to enable our more complex programs, e.g., khronos, eos, and s.
 *
 */
/*===[[ PURPOSE ]]============================================================*

 *   yDLST is a very specific data structure surrounded by a set of shared
 *   functions to provide clean, consistent, and a reliable quad/doubly linked
 *   list that can be built, tested, and maintained once.  its primary goals are
 *   reusability, resiliance, and reliability; not performance and generality.
 *
 *   somewhere after building both khronos and s, i realized that i was using a
 *   very similar structure for job/cell organization and was about to replicate
 *   it in other programs (including eos) -- worst case.
 *
 *   so, even though there are packaged options out there, i must continue to
 *   learn the art of abstracting interface from implementation as well as
 *   refine my theories on proper library design.
 *
 *   yDLST overriding principles (library design)...
 *      - don't want to clutter our using programs with pointers and such
 *      - so, no yDLST related pointers ever leave the library (safer)
 *      - use completely invisible/private data structures (clean)
 *
 *    yDLST will provide for...
 *      - creation of any number of lists
 *      - creation of any number of links tied to those lists (but one each)
 *      - easy iterator access to the links in a specific list
 *      - alternatively, iterator access to all links as a single larger list
 *      - ability to add links to two different sub lists, focus and active
 *      - iterator access to either of those two lists
 *      - requirement/dependecy framework (could also act like edges)
 *      - ability to access down from a link throught requirements
 *      - ability to access up from a link through dependencies
 *      - all iterators return the data payload pointer (for clarity/speed)
 *      - hash indexing of both lists and links to make lookup faster
 *
 *   yDLST will not...
 *      - any sorting which is not required for my use
 *      - any data/context type searching as that's invisible to the library
 *      - focus on any speed tweaking that would make it more complex
 *
 *   as always, there are many, stable, accepted, existing programs and
 *   utilities built by better programmers that are likely superior in speed,
 *   size, capability, and reliability; BUT, i would not have learned nearly as
 *   much using them, so i follow the adage...
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 *   the underlying idea is to use this build process to learn new programming
 *   capabilities and put additional pressure on me to improve my standards,
 *   maintenance, and coding environment.  just using programs and ideas does
 *   not lead to understanding -- so get messy ;)
 *
 *   any one who wishes to become a good writer [programmer] should endeavour,
 *   before he allows himself to be tempted by the more showy qualities, to be
 *   direct, simple, brief, vigourous, and lucid -- henry watson fowler (1908)
 *
 *   simplicity is prerequisite for reliability and security
 *
 */
/*============================================================================*/



/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YDLST_hguard
#define YDLST_hguard loaded

#define     YDLST_HEAD   '['
#define     YDLST_PREV   '<'
#define     YDLST_CURR   '-'
#define     YDLST_NEXT   '>'
#define     YDLST_TAIL   ']'




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char*       yDLST_version           (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yDLST_init              (void);
char        yDLST_purge             (void);
char        yDLST_wrap              (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
void*       yDLST_list_seek         (char a_pos);
void*       yDLST_list_find         (char *a_title);
void*       yDLST_list_entry        (int a_pos, int *a_count);
int         yDLST_list_count        (void);
char        yDLST_list_create       (char *a_title, void *a_data);
char        yDLST_list_destroy      (char *a_title);
char        ydlst_list_purge        (void);
char        ydlst_list_init         (void);
char        ydlst_list_wrap         (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
void*       yDLST_line_seek         (char a_pos);
void*       yDLST_line_fullseek     (char a_pos);
void*       yDLST_line_find         (char *a_title);
void*       yDLST_line_entry        (int a_pos, void **a_file);
void*       yDLST_line_list         (void);
int         yDLST_line_allcount     (void);
int         yDLST_line_count        (void);
char        yDLST_line_create       (char *a_title, void *a_data);
char        yDLST_line_destroy      (char *a_title);
char        yDLST_line_clearlist    (void);
char        ydlst_line_init         (void);
char        ydlst_line_wrap         (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yDLST_focus_on          (void);
char        yDLST_focus_off         (void);
char        yDLST_focus_check       (char *a_title, void **a_list);
char        yDLST_focus_clearall    (void);
char        yDLST_focus_list        (void);
int         yDLST_focus_count       (void);
void*       yDLST_focus_seek        (char a_pos);
char        ydlst_focus_init        (void);
char        ydlst_focus_wrap        (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yDLST_active_on         (void);
char        yDLST_active_off        (void);
char        yDLST_active_check      (char *a_title, void **a_list);
char        yDLST_active_clearall   (void);
int         yDLST_active_count      (void);
void*       yDLST_active_seek       (char a_pos);
char        ydlst_active_init       (void);
char        ydlst_active_wrap       (void);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yDLST_seq_after         (char *a_before);
void*       yDLST_seq_entry         (int a_pos, void **a_after);
void*       yDLST_pred_seek         (char a_pos);
int         yDLST_pred_count        (void);
void*       yDLST_succ_seek         (char a_pos);
int         yDLST_succ_count        (void);

/*---(show current structure)-------------------*/
/*> char        yDLST_showlist     (char  a_header, void *a_file);                    <*/
/*> char        yDLST_showlink     (void *a_file);                                    <*/


#endif
/*============================----end-of-source---============================*/
