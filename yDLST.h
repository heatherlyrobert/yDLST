/*============================----beg-of-source---============================*/

/*===[[ HEADER ]]=============================================================*

 *   focus         : (PS) programming support
 *   niche         : (ds) data structures
 *   application   : yDLST
 *   purpose       : clean, resiliant, reusable quad/doubly linked list w/deps
 *
 *   base_system   : gnu/linux  (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : gnu/ansi-c (right, just, best, universal, and everlasting)
 *   dependencies  : none
 *   size goal     : small      (approximately 1,000 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2011-05
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 * 
 */
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



#define   CURR               -1
#define   HEAD               -2
#define   NEXT               -3


char*       yDLST_version      (void);

/*---(act on the whole library)-----------------*/
char        yDLST_begin        (void);
char        yDLST_end          (void);

/*---(act on a whole list)----------------------*/
char        yDLST_create       (int  *a_list, char *a_name, void *a_data);
char        yDLST_purge        (int   a_list);
char        yDLST_destroy      (int   a_list);
void       *yDLST_lists        (int   a_index);
int         yDLST_find         (char *a_name);

/*---(act on specific link)---------------------*/
char        yDLST_new          (int   a_list, int  *a_link, char *a_name, void *a_data);
char        yDLST_free         (int   a_link);
void       *yDLST_links        (int   a_index);
void       *yDLST_list         (int   a_list, int a_index);
int         yDLST_search       (char *a_name);
void       *yDLST_index        (int   a_index);

/*---(manage the focus list)--------------------*/
char        yDLST_focus_on     (int   a_link);
char        yDLST_focus_off    (int   a_link);
void       *yDLST_focus        (int   a_index);

/*---(manage the active list)-------------------*/
char        yDLST_active_on    (int   a_link);
char        yDLST_active_off   (int   a_link);
void       *yDLST_active       (int   a_index);

/*---(manage the ties list)---------------------*/
char        yDLST_tie          (int   a_up, int a_down, void *a_data);
char        yDLST_untie        (int   a_up, int a_down);
void       *yDLST_ties         (int   a_index);
void       *yDLST_ups          (int   a_link, int a_index);
void       *yDLST_downs        (int   a_link, int a_index);

/*---(show current structure)-------------------*/
char        yDLST_showlist     (char  a_header, void *a_file);
char        yDLST_showlink     (void *a_file);


#endif
/*============================----end-of-source---============================*/
