/*------------------------------------------------------------------------------
* qxwz_typdes.h : type definitions
*          Copyright (C) 2015-2017 by QXSI, All rights reserved.
*/
#ifndef QXWZ_TYPES_H__
#define QXWZ_TYPES_H__

#include <stddef.h> /* NULL */

/* base type definitions start */
/* character */
#ifndef QXWZ_CHAR_T
#define QXWZ_CHAR_T
typedef char qxwz_char_t;
#endif

/* 8bits signed integer */
#ifndef QXWZ_INT8_T
#define QXWZ_INT8_T
typedef signed char qxwz_int8_t;
#endif

/* 8bits unsigned integer */
#ifndef QXWZ_UINT8_T
#define QXWZ_UINT8_T
typedef unsigned char qxwz_uint8_t;
#endif

/* 16bits signed integer */
#ifndef QXWZ_INT16_T
#define QXWZ_INT16_T
typedef signed short qxwz_int16_t;
#endif

/* 16bits unsigned integer */
#ifndef QXWZ_UINT16_T
#define QXWZ_UINT16_T
typedef unsigned short qxwz_uint16_t;
#endif

/* 32bits signed integer */
#ifndef QXWZ_INT32_t
#define QXWZ_INT32_t
typedef signed int qxwz_int32_t;
#endif

/* 32bits unsigned integer */
#ifndef QXWZ_UINT32_T
#define QXWZ_UINT32_T
typedef unsigned int qxwz_uint32_t;
#endif

/* 64bits signed integer */
#ifndef QXWZ_INT64_T
#define QXWZ_INT64_T
typedef signed long long qxwz_int64_t;
#endif

/* 64bits unsigned integer */
#ifndef QXWZ_UINT64_T
#define QXWZ_UINT64_T
typedef unsigned long long qxwz_uint64_t;
#endif

/* single precision float number */
#ifndef QXWZ_FLOAT32_T
#define QXWZ_FLOAT32_T
typedef float qxwz_float32_t;
#endif

/* double precision float number */
#ifndef QXWZ_FLOAT64_T
#define QXWZ_FLOAT64_T
typedef double qxwz_float64_t;
#endif

/* void */
#ifndef QXWZ_VOID_T
#define QXWZ_VOID_T
typedef void qxwz_void_t;
#endif

/* NULL */
#ifndef QXWZ_NULL
#define QXWZ_NULL    ( void * ) 0
#endif

/* boolean representation */
#ifndef QXWZ_BOOT_T
#define QXWZ_BOOT_T
typedef enum {
    /* FALSE value */
    QXWZ_FALSE,
    /* TRUE value */
    QXWZ_TRUE
} qxwz_bool_t;
#endif

/* MISRA-C[pm098] */
#if !defined(NULL)
#define NULL    ((void*)0)
#endif
/* base type definitions end */

typedef struct {
    const qxwz_char_t *key;
    const qxwz_char_t *value;
} qxwz_kv_t;

typedef struct {
    qxwz_kv_t *kvs;
    qxwz_uint32_t count;
} qxwz_pairs_t;

#define QXWZ_MAX_KEY_LEN            32
#define QXWZ_MAX_KEY_NUM            2
#define QXWZ_MAX_HOST_LEN           128

typedef struct {
    qxwz_uint32_t week_num;    /* week number */
    qxwz_uint32_t week_sec;    /* second of the week */
} qxwz_gnss_time_t;

typedef struct {
    qxwz_uint64_t start_time;
    qxwz_uint64_t expire_time;
    qxwz_gnss_time_t start_gpstime;   /* key start time in gps time format */
    qxwz_gnss_time_t expire_gpstime;  /* key expire time in gps time format */
    qxwz_uint8_t raw_key[QXWZ_MAX_KEY_LEN];
} qxwz_key_t;

typedef struct {
    qxwz_uint8_t keys_num;
    qxwz_uint16_t key_bits;
    qxwz_key_t keys[QXWZ_MAX_KEY_NUM];
} qxwz_key_info_t;

typedef struct {
    qxwz_uint8_t proto_type;
    qxwz_uint16_t port;
    qxwz_char_t host[QXWZ_MAX_HOST_LEN];
} qxwz_serv_info_t;

typedef struct {
    qxwz_uint8_t state;
    qxwz_uint8_t act_method;
    qxwz_uint64_t expire_time;
} qxwz_cap_info_t;

typedef struct {
    qxwz_serv_info_t serv_info;
    qxwz_uint8_t level;
    qxwz_uint8_t service_area;
    qxwz_key_info_t key_info;
} qxwz_cap_config_t;

typedef struct {
    qxwz_uint32_t cap_id;

    qxwz_cap_info_t cap_info;
    qxwz_cap_config_t cap_config;
} qxwz_cap_struct_t;

#define MAX_ALG_NAME_LEN 20
#define MAX_ALG_SWIT_TYPE_LEN 10
#define MAX_ALG_SWIT_STATUS_LEN 5
#define MAX_ALG_SWIT_DATA_TYPE_CNT 5
#define MAX_ALG_SWIT_DATA_TYPE_LEN 20
#define MAX_ALG_SWIT_MSG_LEN 100
typedef struct {
    qxwz_uint32_t data_req_count;
    qxwz_char_t alg[MAX_ALG_NAME_LEN];
    qxwz_char_t type[MAX_ALG_SWIT_TYPE_LEN];
    qxwz_char_t status[MAX_ALG_SWIT_STATUS_LEN];
    qxwz_char_t data_req[MAX_ALG_SWIT_DATA_TYPE_CNT][MAX_ALG_SWIT_DATA_TYPE_LEN];
    qxwz_char_t msg[MAX_ALG_SWIT_MSG_LEN];
} qxwz_algo_swit_conf_t;

typedef struct {
    qxwz_void_t *data;
    qxwz_int32_t code;
} qxwz_algo_swit_err_t;

#endif /* QXWZ_TYPES_H__ */

