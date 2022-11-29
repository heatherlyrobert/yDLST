/*
 *
 *  i did not implement two kinds of cursoring just for fun.  i found i used
 *  slight variations in cursoring depending on the application type.
 *
 *  in indendendent lists, it was traditional and easy and i called this type
 *  non-bounce lists.  going past the end results in a null pointer.  its easy
 *  to catch and handles like programmers expect.
 *
 *  but, in interdependent lists, i found i needed to be very careful the top
 *  level lists ALWAYS had a valid pointer as many other functions dereferenced
 *  the current location.  i called these bounce lists where going past the end
 *  "bounced" and stayed at the end.
 *
 *  other programmers are likely much smarter, experienced, and masterful.  they
 *  will likely have a more elegant and effective method.  congratulations !!!
 *  BUT, this is mine, it works nicely, and i own every byte ;))  i learn by
 *  doing and evolving, not stealing and parroting.
 *
 */

/*---(scope types)-------------*/
#define     YDLST_GLOBAL   '*'
#define     YDLST_GPRED    '['
#define     YDLST_GSUCC    ']'
#define     YDLST_GLOBALS  "*[]"

#define     YDLST_LOCAL    '-'
#define     YDLST_LPRED    '<'
#define     YDLST_LSUCC    '>'
#define     YDLST_LOCALS   "-<>"

#define     YDLST_PREDS    "[<*"
#define     YDLST_SUCCS    ">]"



/*---(bounce types)------------*/
/*
 *  if a list has at least one item, bounce cursoring will always return
 *  a valid pointer, e.g., prev from head will return the head.  but, a
 *  negative return code will show that a bounce was required.
 *
 *  this type of cursoring is more forgiving in loops as the pointers 
 *  are more trustable.  but, you must check the return code explicitly.
 *  if you do not check the return code, a loop can be infinite as next on
 *  the tail will be keep giving the tail.
 *
 *  this method is excellent for reporting to avoid lost of error checking
 *  and allow PREV and NEXT to see if categories changed.  it allows PREV/NEXT
 *  to correct themselves automatically.
 *
 *  SOME POINTERS MUST ALWAYS HAVE A VALUE to avoid onerous error checking.
 *  in interdependent situations (multiple levels of lists), this is the best
 *  to use on the master list.
 *
 */

#define     YDLST_HEAD     '['
#define     YDLST_TOPP     '('
#define     YDLST_PREV     '<'
#define     YDLST_CURR     '.'
#define     YDLST_NEXT     '>'
#define     YDLST_BOTT     ')'
#define     YDLST_TAIL     ']'
#define     YDLST_LUSED    ','
#define     YDLST_REL      "<.,>"
#define     YDLST_BOUNCES  "[(<.,>)]"



/*---(non-bounce types)--------*/
/*
 *  in any list, a non-bounce cursor will perfectly reflect the current
 *  position by returning null at the ends.
 *
 *  this type of cursoring is less forgiving in loops as the pointers 
 *  can go null.  but, it is simple to implement as the pointer and return
 *  code failures are always in sync.
 *
 *  this method is great for searching and traditional uses.  with independent
 *  or low-level dependent list, this is the best to use.
 * 
 */

#define     YDLST_DHEAD    'º'
#define     YDLST_DTOPP    '¸'
#define     YDLST_DPREV    '×'
#define     YDLST_DCURR    '´'
#define     YDLST_DNEXT    'Ö'
#define     YDLST_DBOTT    '¹'
#define     YDLST_DTAIL    '»'
#define     YDLST_DLUSED   ';'
#define     YDLST_DREL     "×´;Ö"
#define     YDLST_DANGERS  "º¸×´;Ö¹»"


