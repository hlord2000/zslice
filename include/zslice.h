#ifndef ZSLICE_INCLUDE_ZSLICE_H_
#define ZSLICE_INCLUDE_ZSLICE_H_

#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/linker/sections.h>
#include <zephyr/toolchain.h>
#include <zephyr/sys/util.h>

#include <pb.h>

// Generic handler callback signature.
typedef void (*zslice_handler_cb_t)(const void *req, void *resp, void *user_data);

// zslice handler flags.
#define ZSLICE_FLAG_NONE (0)
#define ZSLICE_FLAG_ACK  BIT(0)

// Internal struct defining a single packet handler.
struct zslice_handler {
    uint16_t packet_index;
    const pb_msgdesc_t *request_msg;
    const pb_msgdesc_t *response_msg;
    zslice_handler_cb_t callback;
    uint32_t flags;
};

// Internal struct defining a zslice communication service.
struct zslice_service {
    const struct device *dev;
    const struct zslice_handler *handlers;
    size_t num_handlers;
    void *user_data;
};

#define ZSLICE_HANDLER(_index, _req_type, _resp_type, _cb, _flags, ...) \
    {                                                                   \
        .packet_index = (_index),                                       \
        .request_msg = (_req_type),                                     \
        .response_msg = (_resp_type),                                   \
        .callback = (zslice_handler_cb_t)(_cb),                         \
        .flags = (_flags),                                              \
    }

#define ZSLICE_SERVICE_DEFINE(_name, _dt_node_id, _user_data, ...)       \
    static const struct zslice_handler _name##_handlers[] = {            \
        __VA_ARGS__                                                      \
    };                                                                   \
    const STRUCT_SECTION_ITERABLE(zslice_service, _name) = {             \
        .dev = DEVICE_DT_GET(_dt_node_id),                               \
        .handlers = _name##_handlers,                                    \
        .num_handlers = ARRAY_SIZE(_name##_handlers),                    \
        .user_data = _user_data,                                         \
    };

#endif /* ZSLICE_INCLUDE_ZSLICE_H_ */
