//
// Created by Light-Laptop on 2021/10/25.
//

#include <iostream>
#include <netdb.h>
#include <cstring>
#include "common/defs.h"

#define PORT_DEFAULT 6789
#define MAX_MEM_BUFFER_SIZE 8192

static char *server_host = (char *)LOCAL_HOST;

int connect() {
  int sockfd;
  struct hostent *host;
  struct sockaddr_in serv_addr;

  if ((host = gethostbyname(server_host)) == NULL) {
    perror("gethostbyname");
    exit(1);
  }

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error \n");
    exit(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons((uint16_t)PORT_DEFAULT);
  serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(serv_addr.sin_zero), 8);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
    perror("Failed to connect \n");
    exit(1);
  }

  return sockfd;
}

#include <string>
#include <fstream>

using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::string;

static string fname = "sql.txt";

void test_script(const string& sql_script_name)
{
  std::cout << "Begin to connect server. " << std::endl;

  int sockfd = connect();

  string base_dir = "../../test/";
  string out_base_dir = "../../build/";
  ifstream fin(base_dir + sql_script_name);
  ofstream fout(out_base_dir + sql_script_name + ".result");
  ofstream bout(out_base_dir + sql_script_name + ".both");

  if (!fin.is_open() || !fout.is_open()) {
    exit(-1);
  }

  char send_buf[MAX_MEM_BUFFER_SIZE] = {0};
  char recv_buf[MAX_MEM_BUFFER_SIZE] = {0};

  while (!fin.eof()) {
    memset(send_buf, 0, sizeof(send_buf));
    fin.getline(send_buf, sizeof(send_buf));
    if (strlen(send_buf) == 0) {
      break;
    }
    send_buf[strlen(send_buf) - 1] = '\0';
    if (send(sockfd, send_buf, strlen(send_buf) + 1, 0) == -1) {
      perror("send error \n");
      exit(1);
    }

    usleep(250000);
    memset(recv_buf, 0, sizeof(recv_buf));
    int len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    if (len < 0) {
      printf("connection exception\n");
      break;
    }
    if (len == 0) {
      printf("Connection has been closed\n");
      break;
    }
    fout << recv_buf;
    bout << send_buf << endl
      << recv_buf << endl;
  }

  close(sockfd);
  chdir("../../");
  char cwd_buff[80];
  getcwd(cwd_buff, sizeof(cwd_buff));
  printf("Successfully finish test.\n");
  printf("Results are saved at %s/build\n", cwd_buff);
}

int main() {
  test_script("sql.txt");
}
