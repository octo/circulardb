/*
 * $Id$
 *
 * CircularDB implementation for time series data.
 *
 */

#ifndef __CIRCULARDB_INTERFACE_H__
#define __CIRCULARDB_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CDB_VERSION

#include <float.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define CDB_EXTENSION "cdb"
#define CDB_VERSION "1.0"
#define CDB_DEFAULT_DATA_TYPE "gauge"
#define CDB_DEFAULT_DATA_UNIT "absolute"
#define CDB_DEFAULT_RECORDS 180000

typedef struct cdb_header_s {
    char name[80];
    char description[120];
    char units[80];
    char type[40];
    char version[10];
    uint64_t max_records;
    uint64_t num_records;
    uint64_t start_record;
    time_t last_updated;
} cdb_header_t;

typedef struct cdb_record_s {
    time_t time;
    double value;
} cdb_record_t;

typedef struct cdb_s {
    int fd;
    short synced;
    char *filename;
    cdb_header_t *header;
} cdb_t;

#define RECORD_SIZE sizeof(cdb_record_t)
#define HEADER_SIZE sizeof(cdb_header_t)

cdb_t* cdb_new(void);
void cdb_free(cdb_t *cdb);

void cdb_generate_header(cdb_t *cdb, char* name, uint64_t max_records, char* type, char* units, char* description);

int cdb_read_header(cdb_t *cdb);
int cdb_write_header(cdb_t *cdb);

uint64_t cdb_write_records(cdb_t *cdb, cdb_record_t *records, uint64_t len);
bool cdb_write_record(cdb_t *cdb, time_t time, double value);

/* Update particular record(s) in the DB after they have already been written. */
uint64_t cdb_update_records(cdb_t *cdb, cdb_record_t *records, uint64_t len);
bool cdb_update_record(cdb_t *cdb, time_t time, double value);

uint64_t cdb_discard_records_in_time_range(cdb_t *cdb, time_t start, time_t end);

uint64_t cdb_read_records(cdb_t *cdb, time_t start, time_t end, int64_t num_requested, cdb_record_t **records);

double cdb_aggregate_using_function_for_records(cdb_t *cdb, char *function, time_t start, time_t end, int64_t num_requested);

void cdb_print_header(cdb_t * cdb);

void cdb_print_records(cdb_t *cdb, time_t start, time_t end, int64_t num_requested, FILE *fh, 
        char *date_format, int cooked, time_t *first_time, time_t *last_time);

void cdb_print(cdb_t *cdb);

/* Bones testing */
extern int circulardb_run(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

/* -*- Mode: C; tab-width: 4 -*- */
/* vim: set tabstop=4 expandtab shiftwidth=4: */
