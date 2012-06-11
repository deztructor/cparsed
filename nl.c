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

#include "nl.h"
#include "util.h"

#include <errno.h>
#include <error.h>

struct aux_info {
        bool is_exists;
        char const *name;
};

static struct aux_info nl_aux[1024];

int nl_aux_id_get(char const *name)
{
        int i;
        for (i = 0; i < ARRAY_SIZE(nl_aux); ++i) {
                if (!nl_aux[i].is_exists) {
                        nl_aux[i].is_exists = true;
                        nl_aux[i].name = name;
                        return i;
                }
        }
        return -1;
}

static int nl_aux_id_check_exists(int id)
{
        if (id >= ARRAY_SIZE(nl_aux)) {
                error(0, -ERANGE, " bad aux id %d\n", id);
                return -ERANGE;
        }
        if (!nl_aux[id].is_exists) {
                error(0, -EINVAL, " aux id %d is free\n", id);
                return -EINVAL;
        }
        return 0;
}

void nl_aux_id_put(int id)
{
        if (!nl_aux_id_check_exists(id))
                return;
        nl_aux[id].is_exists = false;
}

char const * nl_aux_id_name(int id)
{
        if (!nl_aux_id_check_exists(id))
                return NULL;
        return nl_aux[id].name;
}
