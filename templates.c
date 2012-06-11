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

static const struct parsed_rule seq_ = {
        .get = parsed_mk_parse_seq,
        .name = "a_sequence",
        .action = parsed_action_value
};
PARSED_TEMPLATE_GET_DEF(seq, seq_);


static const struct parsed_rule choice_ = {
        .get = parsed_mk_parse_choice,
        .name = "a_choice",
        .action = parsed_action_value
};
PARSED_TEMPLATE_GET_DEF(choice, choice_);

static const struct parsed_rule maybe_ = {
        .get = parsed_mk_parse_maybe,
        .name = "a_maybe",
        .action = parsed_action_value
};
PARSED_TEMPLATE_GET_DEF(maybe, maybe_);

static const struct parsed_rule range_ = {
        .get = parsed_mk_parse_range,
        .name = "a_range",
        .action = parsed_action_value
};
PARSED_TEMPLATE_GET_DEF(range, range_);

static const struct parsed_rule range_noconv_ = {
        .get = parsed_mk_parse_range_noconv,
        .name = "a_range_noconv",
        .action = parsed_action_value
};
PARSED_TEMPLATE_GET_DEF(range_noconv, range_noconv__);

static const struct parsed_rule tpl_char_ = {
        .get = parsed_mk_parse_char,
        .name = "a_char",
        .action = parsed_action_suppress
};
PARSED_TEMPLATE_GET_DEF(char, tpl_char_);

static const struct parsed_rule char_blob_ = {
        .get = parsed_mk_parse_char_blob,
        .name = "a_char_blob",
        .action = parsed_action_suppress
};
PARSED_TEMPLATE_GET_DEF(char_blob, char_blob_);

static const struct parsed_rule char_str_ = {
        .get = parsed_mk_parse_char_str,
        .name = "a_char_str",
        .action = parsed_action_suppress
};
PARSED_TEMPLATE_GET_DEF(char_str, char_str_);
