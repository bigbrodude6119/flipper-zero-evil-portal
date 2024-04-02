#pragma once

typedef struct s_ServerConfig {
  char ap_name[128];
} ServerConfig;

ServerConfig *server_config_alloc();
void server_config_free(ServerConfig *);
