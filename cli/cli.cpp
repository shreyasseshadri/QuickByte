#include "cli.hpp"

int initialize_connection(char *ip_address)
{
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0)
    {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                             sizeof(serv_addr))) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    return sock;
}

char *query_server(int socket, char *query)
{

    char *buffer = (char *)malloc(1024 * sizeof(char));

    send(socket, query, strlen(query), 0);

    int n_bytes = read(socket, buffer, 1024);

    return buffer;
}

int main(int argc, char **argv)
{
    int socket = initialize_connection("127.0.0.1");
    while (1)
    {
        char *line = readline("> ");
        char *response = query_server(socket, line);

        std::cout << response << "\n";
    }
}