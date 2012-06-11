#ifndef _CPARSED_H_
#define _CPARSED_H_

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

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

static inline bool is_match(struct nl_blob const *match)
{
        return match->begin;
}

struct parsed_input
{
        int (*more)(struct parsed_input *);
        int (*reset)(struct parsed_input *);
        char const *begin;
        char const *end;
};

struct parsed_ctx
{
        struct parsed_input *input;
        char const *in_pos;

        int more_rc;
        char *out;
        int out_size;
        int out_pos;
};

static inline int parsed_input_remained(struct parsed_ctx *ctx)
{
        return (ctx->input->end - ctx->in_pos);
}

static inline int parsed_input_more(struct parsed_ctx *ctx)
{
        ctx->more_rc = ctx->input->more(ctx->input);
        return ctx->more_rc;
}

static inline char const *
parsed_next_char(struct parsed_ctx *ctx)
{
        int rc;
        if (ctx->more_rc <= 0)
                return NULL;

        if (parsed_input_remained(ctx) > 0)
                return ctx->in_pos;

        rc = parsed_input_more(ctx);
        if (rc <= 0)
                return NULL;
        assert(ctx->in_pos < ctx->input->end);
        return ctx->in_pos;
}

static inline struct nl_blob mk_match(char const *begin, int len)
{
        struct nl_blob res = { .begin = begin, .len = len };
        return res;
}

static inline struct nl_blob mk_no_match(void)
{
        struct nl_blob res = { .begin = NULL, .len = 0 };
        return res;
}

static inline struct nl_blob
parsed_match_char(struct parsed_ctx *ctx, char c)
{
        char const *src = parsed_next_char(ctx);
        return (src && *src == c)
                ? mk_match(src, 1)
                : mk_no_match();
}

static inline struct nl_blob
parsed_match_any_byte(struct parsed_ctx *ctx, char const *p, size_t len)
{
        char const *src = parsed_next_char(ctx);
        char const *end = p + len;
        if (src) {
                while (p != end) {
                        if (*src == *p++)
                                return mk_match(src, 1);
                }
        }
        return mk_no_match();
}


struct parsed_env
{
};


typedef struct cell * (*parsed_action_t)
        (struct parsed_env *, struct cell *);

typedef struct cell * (*parsed_parser_fn)(struct parsed_ctx *);

struct parsed_parser
{
        parsed_parser_fn fn;
        char const *name;
        parsed_action_t action;
};

struct parsed_rule;

typedef struct parsed_parser * (*parsed_generator_t)(struct parsed_rule *);

struct parsed_rule
{
        parsed_generator_t get;
        char const *name;
        parsed_action_t action;
};

typedef struct parsed_parser * (*parsed_gen_t)
        (char const *name, parsed_action_t action);

#define PARSED_TEMPLATE_GET_FN(name) \
        struct parsed_rule const * parsed_tpl_##name(void);

#define PARSED_TEMPLATE_GET_DEF(name, var)          \
struct parsed_rule const * parsed_tpl_##name(void)  \
{                                                   \
        return &var;                                \
}

PARSED_TEMPLATE_GET_FN(seq);
PARSED_TEMPLATE_GET_FN(choice);
PARSED_TEMPLATE_GET_FN(maybe);
PARSED_TEMPLATE_GET_FN(range);
PARSED_TEMPLATE_GET_FN(range_noconv);
PARSED_TEMPLATE_GET_FN(char);
PARSED_TEMPLATE_GET_FN(char_blob);
PARSED_TEMPLATE_GET_FN(char_str);


#endif /* _CPARSED_H_ */
