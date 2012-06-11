#ifndef _PARSED_NL_CELL_H_
#define _PARSED_NL_CELL_H_

/* Copyright (C) 2012 Denis Zalevskiy */

/* Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions: */

/* The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software. */

/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <stdbool.h>
#include <stddef.h>


typedef enum nl_cell_id
{
        nl_cell_bool = 0,
        nl_cell_char,
        nl_cell_short,
        nl_cell_int,
        nl_cell_long,
        nl_cell_long_long,
        nl_cell_float,
        nl_cell_double,
        nl_cell_str,
        nl_cell_subr,
        nl_cell_blob,
        nl_cell_cons,

        nl_cell_ids_end
} nl_cell_id;

struct nl_cell;
typedef struct nl_cell * (*subr_t)(struct nl_cell *, struct nl_cell *);

struct nl_blob
{
        char const *begin;
        size_t len;
};

struct nl_cons
{
        struct nl_cell *a;
        struct nl_cell *d;
};

struct nl_aux
{
        int aux_id;
        void const *data;
};

int nl_aux_id_get(char const *name);
void nl_aux_id_put(int);
char const * nl_aux_id_name(int id);

struct nl_cell
{
        nl_cell_id id;
        union {
                bool b;
                char ic;
                short is;
                int ii;
                long il;
                long long ill;
                float ff;
                double fd;
                char const *str;
                subr_t subr;
                struct nl_blob blob;
                struct nl_cons cons;
                struct nl_aux aux;
        };
};


#endif /* _PARSED_NL_CELL_H_ */
