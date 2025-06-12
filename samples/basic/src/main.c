/*
 * Copyright (c) 2011 Petteri Aimonen
 * Copyright (c) 2021 Basalte bv
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "src/request.pb.h"
#include "src/response.pb.h"

#include <zslice.h>

static void handle_add(const Request *req, Response *resp, void *user_data)
{
    (void)user_data;
}

static void handle_subtract(const Request *req, Response *resp, void *user_data)
{
    (void)user_data;
}

/*
 * =========================================================================
 * zslice Service Table
 * =========================================================================
 */
ZSLICE_SERVICE_DEFINE(math_service, DT_CHOSEN(zslice_uart), 128, sizeof(Request_msg), NULL,
    ZSLICE_HANDLER(
        RequestTypes_ADD,
        &Request_msg,
        &Response_msg,
        handle_add,
        ZSLICE_FLAG_NONE
    ),
    ZSLICE_HANDLER(
        RequestTypes_SUBTRACT,
        &Request_msg,
        &Response_msg,
        handle_subtract,
        ZSLICE_FLAG_NONE
    ),
);
