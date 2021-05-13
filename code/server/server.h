#ifndef SERVER_H
#define SERVER_H


#include <sys/socket.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>



typedef struct
{
    char userId[256];
    char password[256];
    struct sockaddr_in ip_address;
    unsigned char permissions : 3; // 0 0 0 -> 1 1 1
} user_info;

typedef struct
{
    user_info users[NO_MAX_USERS];
    int no_users;

} shm_t;


// #define SERVER_UDP_PORT 9001
// #define SERVER_TCP_PORT 9001
#define SERVER_IP "10.0.2.15"// "129.136.212.251"
#define BUF_SIZE 1024
#define NO_MAX_USERS 10
#define CONFIG_FILE "data/users.dat"



void write_info_to_file();
void get_info_from_file();
void get_shared_memory();
void receive_admin();
int remove_from_list(char * name);
int process_command(int admin_fd_socket, char instruction[]);
void print_user_info(int fd, user_info* user);
void wrong_command(int fd, char *error_msg);
void error_msg(char *msg);



pid_t admin_pid;
int sock_udp;
shm_t *shmem;
int client_port, config_port;

#endif