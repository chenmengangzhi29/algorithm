#pragma once

int hexit(char c);
void strencode(char* to, int tosize, const char* from);
void decode_str(char *to, char *from);
char *get_file_type(const char *name);
void send_error(struct bufferevent* bev, int status, char *title, char *text);
int send_header(struct bufferevent *bev, int no, const char *desp, const char *type, long len);

int send_dir(struct bufferevent *bev, const char *dirname);
int response_http(struct bufferevent *bev, const char *method, char *path);
void conn_readcb(struct bufferevent *bev, void *user_data);
void conn_eventcb(struct bufferevent *bev, short events, void *user_data);
void signal_cb(evutil_socket_t sig, short events, void *user_data);
void listener_cb(struct evconnlistener *listener,
                evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data);
