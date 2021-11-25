#ifndef __DEBUG_PRINT_H__
#define __DEBUG_PRINT_H__

#define _C_BLACK 	"\033[30m"
#define _C_RED 		"\033[31m"
#define _C_GREEN 	"\033[32m"
#define _C_YELLOW 	"\033[33m"
#define _C_BLUE 	"\033[34m"
#define _C_MAGENTA	"\033[35m"
#define _C_CYAN 	"\033[36m"
#define _C_WHITE 	"\033[37m"
#define _C_END 		"\033[0m"
#define _C_YELLOWRED	"\033[1;33;41m"
#define _C_WHITEBLUE	"\033[1;37;44m"

#define debug_printf(color, fmt, arg...) \
	do { \
		fprintf(stderr, color "%s:%s:%d>" _C_END " " fmt , __FILE__, __func__, __LINE__, ##arg); \
	} while(0)

#if !defined (__DEBUG_ON__)
#define _DBG(fmt, arg...)
#define _DBG_R(fmt, arg...)
#define _DBG_G(fmt, arg...)
#define _DBG_B(fmt, arg...)
#define _DBG_Y(fmt, arg...)
#define _DBG_C(fmt, arg...)
#else	/* __DEBUG_ON__ */
#define _DBG(fmt, arg...) debug_printf(_C_END, fmt, ##arg)
#define _DBG_R(fmt, arg...) debug_printf(_C_RED, fmt, ##arg)
#define _DBG_G(fmt, arg...) debug_printf(_C_GREEN, fmt, ##arg)
#define _DBG_B(fmt, arg...) debug_printf(_C_BLUE, fmt, ##arg)
#define _DBG_Y(fmt, arg...) debug_printf(_C_YELLOW, fmt, ##arg)
#define _DBG_C(fmt, arg...) debug_printf(_C_CYAN, fmt, ##arg)
#endif	/* __DEBUG_ON__ */

#define _ERR(fmt, arg...) debug_printf(_C_YELLOWRED, fmt, ##arg)
#define _REL_OUT(fmt, arg...) debug_printf(_C_END, fmt, ##arg)

#endif	/* __DEBUG_PRINT_H__ */
