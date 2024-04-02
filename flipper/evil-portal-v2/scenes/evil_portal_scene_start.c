#include "../evil_portal_app_i.h"

typedef enum { NO_ARGS = 0, INPUT_ARGS, TOGGLE_ARGS } InputArgs;

typedef enum {
  FOCUS_CONSOLE_END = 0,
  FOCUS_CONSOLE_START,
  FOCUS_CONSOLE_TOGGLE
} FocusConsole;

#define SHOW_STOPSCAN_TIP true
#define NO_TIP false

#define MAX_OPTIONS 9

bool evil_portal_scene_start_on_event(void *ctx, SceneManagerEvent event) {
  UNUSED(ctx);
  Evil_PortalApp *app = ctx;
  bool consumed = false;

  if (event.type == SceneManagerEventTypeCustom) {
    if (event.event == Evil_PortalEventStartPortal) {
      scene_manager_set_scene_start(app->scene_manager, Evil_PortalSceneStart, app->selected_menu_index);
      scene_manager_next_scene(app->scene_manager, Evil_PortalAppViewStartPortal);
    } else if (event.event == Evil_PortalAppViewStartPortal) {

    } else if (event.event == Evil_PortalEventStartConsole) {

    }
  }
  consumed = true;
}

void evil_portal_scene_start_on_exit(void *ctx) {
  Evil_PortalApp *app = ctx;
  variable_item_list_reset(app->var_item_list);
}
