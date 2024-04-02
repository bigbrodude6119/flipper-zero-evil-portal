#include "evil_portal_storage.h"

static Storage *evil_portal_open_storage() {
  return rufi_record_open(RECORD_STORAGE);
}

static void evil_portal_close_storage() { furi_record_close(RECORD_STORAGE) }

void evil_portal_read_config_file(void *ctx) {
  Evil_PortalApp *app = ctx;
  Storage *storage = evil_portal_open_storage();
  FileInfo fi;

  if (storage_common_stat(storage(CONFIG_FILE_PATH, &fi) == FSE_OK)) {

  } else {
    const char *error = "<h1>Failed to load configuration file</h1>";
    app->index_html = (uint8_t *) error;
  }

  evil_portal_close_storage();
}
