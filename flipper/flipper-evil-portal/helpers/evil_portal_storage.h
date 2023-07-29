#include <furi.h>
#include <storage/storage.h>

#define PORTAL_FILE_DIRECTORY_PATH EXT_PATH("apps_data/evil_portal")
#define EVIL_PORTAL_INDEX_SAVE_PATH PORTAL_FILE_DIRECTORY_PATH "/index.html"
#define EVIL_PORTAL_AP_SAVE_PATH PORTAL_FILE_DIRECTORY_PATH "/ap.config.txt"
#define EVIL_PORTAL_LOG_SAVE_PATH PORTAL_FILE_DIRECTORY_PATH "/logs"

void write_logs(Storage *storage, FuriString* portal_logs);
