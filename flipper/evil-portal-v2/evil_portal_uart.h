#pragma once

#include "furi_hal.h"

#define RX_BUF_SIZE 320

typedef struct Evil_PortalUart Evil_PortalUart;

typedef void (*handle_rx_data_fct)(uint8_t *, size_t, void *);

void evil_portal_uart_set_handle_rx_data_cb(Evil_PortalUart *uart, handle_rx_data_fct handle_rx_data_cb);
void evil_portal_uart_tx(uint8_t *data, size_t len);
Evil_PortalUart *evil_portal_uart_init(Evil_PortalApp *app);
void evil_portal_uart_free(Evil_PortalUart *uart);
