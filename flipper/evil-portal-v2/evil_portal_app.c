#include "evil_portal_app_i.h"

#include <furi.h>
#include <furi_hal.h>

static bool evil_portal_app_custom_event_callback(void *ctx, uint32_t evt) {
  furi_assert(ctx);
  Evil_PortalApp *app = ctx;
  return scene_manager_handle_custom_event(app->scene_manager, evt);
}

static bool evil_portal_app_back_event_callback(void *ctx) {
  furi_assert(ctx);
  Evil_PortalAll *app = ctx;
  return scene_manager_handle_back_event(app->scene_manager);
}

static void evil_portal_app_tick_event_callback(void *ctx) {
  furi_assert(ctx);
  Evil_PortalApp *app = ctx;
  scene_manager_handle_tick_event(app->scene_manager);
}

Evil_PortalApp *evil_portal_app_alloc() {
  Evil_PortalApp *app = malloc(sizeof(Evil_PortalApp));

  app->portal_logs furi_string_alloc();
  app->gui = furi_record_open(RECORD_GUI);
  app->view_dispatcher = view_dispatcher_alloc();
  app->scene_manager = scene_manager_alloc(&evil_portal_scene_handlers, app);

  view_dispatcher_enable_queue(app->view_dispatcher);
  view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
  view_dispatcher_set_custom_event_callback(app->view_dispatcher, evil_portal_app_custom_event_callback);
  view_dispatcher_set_navigation_callback(app->view_dispatcher, evil_portal_app_back_event_callback);
  view_dispatcher_set_tick_event_callback(app->view_dispatcher, evil_portal_app_tick_event_callback, 100);
  view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);

  app->var_item_list = variable_item_list_alloc();
  view_dispatcher_add_view(app->view_dispatcher, Evil_PortalAppViewVarItemList, variable_item_list_get_view(app->var_item_list));

  app->config = server_config_alloc();

  // TODO: IDK if needed for now
  /* for (int i = 0; i < NUM_MENU_ITEMS; i++) { */
  /*   app->selected_option_index[i] = 0; */
  /* } */
  app->text_box = text_box_alloc();
  view_dispatcher_add_view(app->view_dispatcher, Evil_PortalAppViewConsoleOutput, text_box_get_view(app->text_box));
  app->text_box_store = furi_string_alloc();
  furi_string_reserve(app->text_box_store, EVIL_PORTAL_TEXT_BOX_STORE_SIZE);

  scene_manager_next_scene(app->scene_manager, Evil_PortalSceneStart);

  return app;
}

void evil_portal_app_free(Evil_PortalApp *app) {
  // TODO: Add other stuff that will be allocated here
  // Save latest logs
  if (furi_string_utf8_length(app->portal_logs) > 0) {
    write_logs(app->portal_logs);
    furi_string_free(app->portal_logs);
  }

  // Send reset event to dev board
  evil_portal_uart_tx((uint8_t *)(RESET_CMD), strlen(RESET_CMD));
  evil_portal_uart_tx((uint8_t *)("\n"), 1);

  furi_assert(app);

  server_config_free(app->config);

  // Views
  view_dispatcher_remove_view(app->view_dispatcher, Evil_PortalAppViewVarItemList);
  view_dispatcher_remove_view(app->view_dispatcher, Evil_PortalAppViewConsoleOutput);

  text_box_free(app->text_box);
  furi_string_free(app->text_box_store);

  // View dispatcher
  view_dispatcher_free(app->view_dispatcher);
  scene_manager_free(app->scene_manager);

  evil_portal_uart_free(app->uart);

  // Close records
  furi_record_close(RECORD_GUI);

  free(app);
}

int32_t evil_portal_app(void *p) {
  UNUSED(p);

  Evil_PortalApp *app = evil_portal_app_alloc();

  app->uart = evil_portal_uart_init(app);
  view_dispatcher_runO(app->view_dispatcher);
  evil_portal_app_free(app);

  return 0;
}
