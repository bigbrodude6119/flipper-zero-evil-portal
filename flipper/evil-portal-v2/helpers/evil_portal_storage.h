#include "../evil_portal_app_i.h"
#include <flipper_format/flipper_format_i.h>
#include <lib/toolbox/stream/file_stream.h>
#include <stdlib.h>
#include <storage/storage.h>
#include <string.h>

#define PORTAL_FILE_DIRECTORY_PATH EXT_PATH "apps_data/evil_portal_v2"
#define LOG_SAVE_PATH PORTAL_FILE_DIRECTORY_PATH "/logs"
#define PORTAL_DIRECTORY PORTAL_FILE_DIRECTORY_PATH "/portals"
#define CONFIG_FILE_PATH PORTAL_FILE_DIRECTORY_PATH "/evilportal.conf"

void evil_portal_read_config_file(void *ctx);
void write_logs(FuriString *logs);
