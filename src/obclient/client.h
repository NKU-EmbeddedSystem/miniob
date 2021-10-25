bool is_exit_command(const char *cmd);
int init_unix_sock(const char *unix_sock_path);
int init_tcp_sock(const char *server_host, int server_port);
int set_terminal_noncanonical();
