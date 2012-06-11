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

#include "parsed.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


/* choice, seq, repetition, not_equal, lookahead */
struct parsed_rule_seq
{
        struct parsed_rule rule;
        struct parsed_rule *children[0];
};

struct parsed_rule_char
{
        struct parsed_rule rule;
        char c;
};

struct parsed_rule_char_blob
{
        struct parsed_rule rule;
        struct nl_blob blob;
};

struct parsed_rule_char_str
{
        struct parsed_rule rule;
        char const *str;
};

struct parsed_parser * parsed_mk_parser(char const *name,
                                        struct parsed_parser *src,
                                        parsed_action_t action)
{
        src->name = name;
        src->action = action;
        return src;
}

static void * alloc_rule(struct parsed_rule const *template, size_t size)
{
        void *res = malloc(size);
        if (!res)
                return NULL;
        memcpy(&res, template, sizeof(template[0]));
        return res;
}

struct parsed_rule * parsed_mk_rule_vec(struct parsed_rule const *template, ...)
{
        struct parsed_rule_seq *res;
        struct parsed_rule *p;
        va_list ap;
        int i;

        if (!template)
                return NULL;

        va_start(ap, template);
        i = 0;
        for(p = va_arg(ap, struct parsed_rule *);p;
            p = va_arg(ap, struct parsed_rule *)) ++i;
        va_end(ap);

        res = alloc_rule(template, sizeof(res[0])
                         + sizeof(res->children[0]) * i);
        if (!res)
                return NULL;

        va_start(ap, template);
        for (p = va_arg(ap, struct parsed_rule *), i = 0; p;
             p = va_arg(ap, struct parsed_rule *)) {
                res->children[i] = p;
                ++i;
        }
        va_end(ap);
        return &res->rule;
}

struct parsed_rule * parsed_mk_modifier(struct parsed_rule const *template,
                                        struct parsed_rule *rule)
{
        struct parsed_rule_seq *res;
        struct parsed_rule *p;

        if (!template)
                return NULL;

        res = alloc_rule(template, sizeof(res[0])
                         + sizeof(res->children[0]));
        if (!res)
                return NULL;

        res->children[0] = rule;
        return &res->rule;
}

struct parsed_rule * parsed_mk_parser_char(char c)
{
        struct parsed_rule_char *res;
        int i;

        res = alloc_rule(parsed_tpl_char, sizeof(char));
        if (!res)
                return NULL;

        
        return &res->rule;
}

static struct parsed_rule *
parsed_mk_parser_many(int from, int to, struct parsed_rule *tgt)
{
        if (tgt->action == parsed_action_value
            || tgt->action == parsed_action_suppress)
}

struct parsed_rule *
parsed_mk_parser_repetition(int from, int to, struct parsed_rule *tgt)
{
        if (!tgt)
                return NULL;

        if (from < 0 || to == 0 || (to >= 0 && to <= from))
                return NULL;

        if (from == 1 && to == 1)
                return tgt;

        if (from == 0 && to == 1)
                return parsed_mk_parser_maybe(tgt);

        return parsed_mk_parser_many(from, to, tgt);
}
