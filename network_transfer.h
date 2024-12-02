#ifndef NETWORK_TRANSFER_H
#define NETWORK_TRANSFER_H

void push_to_server(const char *server_ip, int port);
void fetch_from_server(const char *server_ip, int port);
void set_origin(const char *url);

#endif
