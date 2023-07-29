#include "evil_portal_storage.h"

Storage *evil_portal_open_storage() {
  return furi_record_open(RECORD_STORAGE);
}

void evil_portal_close_storage() { furi_record_close(RECORD_STORAGE); }

char *sequential_file_resolve_path(Storage *storage, const char *dir,
                                   const char *prefix, const char *extension) {
  if (storage == NULL || dir == NULL || prefix == NULL || extension == NULL) {
    return NULL;
  }

  char file_path[256];
  int file_index = 0;

  do {
    if (snprintf(file_path, sizeof(file_path), "%s/%s_%d.%s", dir, prefix,
                 file_index, extension) < 0) {
      return NULL;
    }
    file_index++;
  } while (storage_file_exists(storage, file_path));

  return strdup(file_path);
}

void write_logs(FuriString *portal_logs) {
  Storage *storage = evil_portal_open_storage();

  if (!storage_file_exists(storage, EVIL_PORTAL_LOG_SAVE_PATH)) {
    storage_simply_mkdir(storage, EVIL_PORTAL_LOG_SAVE_PATH);
  }

  char *seq_file_path = sequential_file_resolve_path(
      storage, EVIL_PORTAL_LOG_SAVE_PATH, "log", "txt");

  File *file = storage_file_alloc(storage);

  if (storage_file_open(file, seq_file_path, FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
    storage_file_write(file, furi_string_get_cstr(portal_logs), furi_string_utf8_length(portal_logs));
  }
  storage_file_close(file);
  storage_file_free(file);
  evil_portal_close_storage();
}