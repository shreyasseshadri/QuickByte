#include <stdio.h>
#include <bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int initialize_connection(char *ip_address);

char *query_server(int socket, char *query);
int main(int argc, char **argv);