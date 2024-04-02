#pragma once

#include "evil_portal_app.h"
#include "evil_portal_custom_event.h"
#include "evil_portal_uart.h"
#include "scenes/evil_portal_scene.h"
//#include "helpers/command_queue.h"
#include "helpers/server_config.h"

#include <gui/gui.h>
#include <gui/modules/text_box.h>
#include <gui/modules/variable_item_list.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>

#define NUM_MENU_ITEMS 4

#define TEXT_BOX_STORE_SIZE 4096
#define UART_CH FuriHalUartIdUSART1

struct Evil_PortalApp {
  Gui *gui;
  ViewDispatcher *view_dispatcher;
  SceneManager *scene_manager;

  // Array of logs that store messages from the esp32
  FuriString *portal_logs;

  FuriString *text_box_store;
  size_t text_box_store_strlen;
  TextBox *text_box;

  VariableItemList *var_item_list;
  Evil_PortalUart *uart;

  int selected_menu_item;
  int selected_option_index[NUM_MENU_ITEMS];
  const char *selected_tx_string;
  int BAUDRATE;

  // TODO: Do  this command queue later
  //CommandQueue *command_queue;

  ServerConfig *config;
};

typedef enum {
  Evil_PortalAppViewVarItemList,
  Evil_PortalAppViewConsoleOutput,
  Evil_PortalAppViewStartPortal,
} Evil_PortalAppView;
