#ifndef WEB_H_
#define WEB_H_
#include <t_net.h>
int t_listen(int port,int backlog);
void doit(int c_fd);
#endif
