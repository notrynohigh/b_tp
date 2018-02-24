#ifndef __B_TP_CONFIG_H__
#define __B_TP_CONFIG_H__

/**
 * @addtogroup B_TP
 * @{
 */


/**
 * @defgroup B_TP_CONFIG global configuration
 * @{
 */

/**
 * @defgroup B_TP_VA_TYPE variable type 
 * @{
 */
typedef unsigned char      b_TPU8;
typedef unsigned short     b_TPU16;
typedef unsigned int       b_TPU32;

typedef signed char        b_TPS8;
typedef signed short       b_TPS16;
typedef signed int         b_TPS32;

#define b_TP_NULL          ((void *)0)
/**
 * @}
 */


/** | B_TP_HEAD | B_TP_FRAME_NUMBER | TOTAL_LEN | DATA (N) | CHECK */
/**  configure start  ----------------------------------------------------------*/
#define B_TP_HEAD_TYPE            b_TPU8
#define B_TP_FRAME_NUMBER_TYPE    b_TPU8
#define B_TP_TOTAL_LEN_TYPE       b_TPU8
#define B_TP_CHECK_SELECT         B_TP_CRC32         /**< @ref b_tp_checkout_t  */


#define B_TP_HEAD                 0XA5
#define B_TP_MTU                  20
/** configure end ---------------------------------------------*/

#pragma pack(1)

typedef struct
{
    B_TP_HEAD_TYPE          head;
	B_TP_FRAME_NUMBER_TYPE  f_num;
	B_TP_TOTAL_LEN_TYPE     total_len;
}b_tp_head_t;

#pragma pack()

/**
 * @}
 */


/**
 * @}
 */


#endif
