#include "evil_portal_scene.h"

// Generate scene on_enter handler array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_enter,
void (*const evil_portal_scene_on_enter_handlers[])(void *) = {
  #include "evil_portal_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_event handler array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_event,
bool (*const evil_portal_scene_on_event_handlers[])(void *, SceneManagerEvent) = {
  #include "evil_portal_scene_config.h"
};
#undef ADD_SCENE

// Generate scene on_exit handler array
#define ADD_SCENE(prefix, name, id) prefix##_scene_##name##_on_exit,
void (*const evil_portal_scene_on_exit_handlers[])(void *) = {
  #include "evil_portal_scene_config.h"
};
#undef ADD_SCENE

// Init scene handler configuration structure
conost SceneManagerHandlers evil_portal_scene_handlers = {
  .on_enter_handlers = evil_portal_scene_on_enter_handlers,
  .on_event_handlers = evil_portal_scene_on_event_handlers,
  .on_exit_handlers = evil_portal_scene_on_exit_handlers,
  .scene_nim = Evil_PortalSceneNum,
};
