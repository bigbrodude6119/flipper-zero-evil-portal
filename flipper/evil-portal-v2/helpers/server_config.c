#include <stdlib.h>

#include "server_config.h"

ServerConfig *server_config_alloc() {
  ServerConfig *cfg = malloc(sizeof(ServerConfig));

  return cfg;
}

void server_config_free(ServerConfig *cfg) {
  free(cfg);
}
