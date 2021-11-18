//
// Created by Light-Laptop on 2021/10/25.
//

#include <iostream>
#include <netdb.h>
#include <cstring>
#include <string>
#include <vector>

#include "common/defs.h"

#define PORT_DEFAULT 6789
#define MAX_MEM_BUFFER_SIZE 8192

using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::string;
using std::vector;

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

void test_script(const vector<string> &sql_script_names)
{
  std::cout << "Begin to connect server. " << endl << endl;

  int sockfd = connect();

  for (const auto &sql_script_name : sql_script_names) {
    printf("Start test: %s\n", sql_script_name.c_str());

    string base_dir = "../../test/";
    string out_base_dir = "../../build/";
    string sql_script_path = base_dir + sql_script_name;
    string both_sql_and_result_path = out_base_dir + sql_script_name + ".result";

    ifstream fin(sql_script_path);
    if (!fin.is_open()) {
      printf("Fail to open script: %s\n", sql_script_path.c_str());
      exit(-1);
    }

    ofstream bout(both_sql_and_result_path);
    if (!bout.is_open()) {
      printf("Fail to create file: %s\n", both_sql_and_result_path.c_str());
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
      if (strlen(send_buf) > 2 && send_buf[0] == '-' && send_buf[1] == '-') {
        continue;
      }
      if (send_buf[strlen(send_buf) - 1] != ';') {
        send_buf[strlen(send_buf) - 1] = '\0';
      } else {
        send_buf[strlen(send_buf)] = '\0';
      }
      if (send(sockfd, send_buf, strlen(send_buf) + 1, 0) == -1) {
        perror("send error \n");
        exit(1);
      }
      cout << "  [SQL] " << send_buf << endl;
      usleep(500000);
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
      bout << send_buf << endl
           << recv_buf << endl;
    }
    printf("Successfully finish test: %s.\n\n", sql_script_name.c_str());
  }
  close(sockfd);
  chdir("../../");
  char cwd_buff[80];
  getcwd(cwd_buff, sizeof(cwd_buff));
  printf("Results are saved at %s/build\n\n", cwd_buff);
}

int main() {
  test_script({
//    "aggregation_empty_test.sql",
//    "aggregation_fail_test.sql",
//    "aggregation_test.sql",
//    "aggregation_test2.sql",
//    "aggregation_test3.sql",
//    "aggregation_test4.sql",
//    "basic_test.sql",
//    "date_test.sql",
//    "group_by_test.sql",
//    "group_by_test2.sql",
//    "group_by_test3.sql",
//    "identifier_test.sql",
//    "nullable.sql",
//    "order.sql",
//    "outer_join_empty_test.sql",
//    "outer_join_test.sql",
    "subquery_syntax_test.sql",
//    "subquery_test.sql",
//    "unique.sql",
//    "where_test.sql",
  });
}
