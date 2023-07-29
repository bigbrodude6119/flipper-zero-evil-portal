#include <stream/stream.h>
#include <stream/buffered_file_stream.h>
#include "../evil_portal_uart.h"

#define PORTAL_FILE_DIRECTORY_PATH EXT_PATH("apps_data/evil_portal")
#define EVIL_PORTAL_AP_SAVE_PATH PORTAL_FILE_DIRECTORY_PATH "/ap.config.txt"

static const char TAG[] = "evil_portal_command";

static bool send_file_over_uart(Storage *storage, const char* path) {
    Stream *file_stream = buffered_file_stream_alloc(storage);
    if (!buffered_file_stream_open(file_stream, path, FSAM_READ, FSOM_OPEN_EXISTING)) {
        FURI_LOG_E(TAG, "Unable to open stream: %s", path);
        // The stream should be closed also if the open fails.
        buffered_file_stream_close(file_stream);
        return false;
    }

    uint8_t read_buffer[128];
    size_t to_read_bytes = stream_size(file_stream);

    while(to_read_bytes > 0) {
        size_t byte_read = stream_read(file_stream, read_buffer, sizeof read_buffer);
        evil_portal_uart_tx(read_buffer, byte_read);

        to_read_bytes -= byte_read;
    }

    buffered_file_stream_close(file_stream);

    return true;
}

bool evil_portal_set_html(Storage *storage, const char* path) {
    furi_assert(storage, "storage is null");
    furi_assert(path, "the html file path is null");

    // Start the html set sending to the esp the command, use -1 to exclude the string terminator bytes.
    evil_portal_uart_tx((uint8_t*) "sethtml=", 8);

    bool html_sent = send_file_over_uart(storage, path);

    if (!html_sent) {
        char *error_message = "<b>Evil portal</b><br>Unable to read the html file.<br>"
                              "Is the SD Card set up correctly? <br>See instructions @ "
                              "github.com/bigbrodude6119/flipper-zero-evil-portal<br>"
                              "Under the 'Install pre-built app on the flipper' section.";
        evil_portal_uart_tx((uint8_t*) error_message, strlen(error_message));
    }

    // Send the commands terminator.
    evil_portal_uart_tx((uint8_t*) "\n", 1);

    return true;
}

bool evil_portal_set_ap_name(Storage *storage) {
    furi_assert(storage, "storage is null");

    // Start the html set sending to the esp the command, use -1 to exclude the string terminator bytes.
    evil_portal_uart_tx((uint8_t*) "setap=", 6);

    bool ap_name_sent = send_file_over_uart(storage, EVIL_PORTAL_AP_SAVE_PATH);

    if (!ap_name_sent) {
        char *default_name = "Evil Portal";
        evil_portal_uart_tx((uint8_t*) default_name, strlen(default_name));
    }

    // Send the commands terminator.
    evil_portal_uart_tx((uint8_t*) "\n", 1);
    return true;
}
