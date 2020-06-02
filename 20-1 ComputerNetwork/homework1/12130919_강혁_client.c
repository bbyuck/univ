#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define NAME_SIZE 30

void error_handling(char* message);
void read_routine(int sock, char* buf);
void write_routine(int sock, char* buf, char* userName);

int main(int argc, char *argv[]) {
  int sock;
  pid_t pid;

  char buf[BUF_SIZE];
  char user_name[NAME_SIZE];

  struct sockaddr_in serv_adr;

  if(argc != 4) {
    printf("Usage : %s <IP> <port> <user name>\n", argv[0]);
    exit(1);
  }

  sprintf(user_name, "[%s]", argv[3]);

  sock = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))== -1) {
    error_handling("connect() error!");
  }

  pid = fork();
  if(pid == 0) {
    write_routine(sock, buf, user_name);
  }else {
    read_routine(sock, buf);
  }

  close(sock);

  return 0;
}

void read_routine(int sock, char * buf) {
  while(1) {
    int str_len = read(sock, buf, BUF_SIZE);
    if (str_len == 0) return;

    buf[str_len] = 0;
    fputs(buf, stdout);
  }
}

void write_routine(int sock, char* buf, char* userName) {
  char message[BUF_SIZE];
  while (1)
  {
    fgets(buf, BUF_SIZE, stdin);

    if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
      shutdown(sock, SHUT_WR);
      return;
    }
    sprintf(message, "%s %s", userName, buf);
    write(sock, message, strlen(message));
  }
}

void error_handling(char* message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}