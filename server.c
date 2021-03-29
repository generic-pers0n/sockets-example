#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), client_sfd, result;
  struct sockaddr_in address, client;
  ssize_t received_result;
  socklen_t client_size  = sizeof(struct sockaddr_in),
            address_size = sizeof(struct sockaddr_in);

  printf("Running server...\n");

  if (socket_fd < 0)
  {
    perror("socket: could not create socket");
    return -1;
  }

  // Setup our address
  address.sin_family = AF_INET;
  address.sin_port   = htons(50000);
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  /*result = inet_aton("127.0.0.1", &address.sin_addr);
  if (result == 0)
  {
    perror("inet_aton error");
    close(socket_fd);
    return -1;
  }*/

  // Bind the address
  result = bind(socket_fd, (struct sockaddr*) &address, address_size);
  if (result < 0)
  {
    perror("bind: cannot bind socket");
    close(socket_fd);
    return -1;
  }

  // Listen for any connections
  result = listen(socket_fd, 1); // Only one connection shall do
  if (result < 0)
  {
    perror("cannot listen on socket");
    close(socket_fd);
    return -1;
  }

  // Accept any incoming connections
  client_sfd = accept(socket_fd, (struct sockaddr*) &client, &client_size);
  if (client_sfd < 0)
  {
    perror("cannot accept incoming connections");
    close(socket_fd);
    return -1;
  }

  printf("Accepted connection from client\n");

  /** At this point, we already have a client connected to the server. From now
   * on, we should be able to send and receive messages to and from the client.
   * For our purposes, we'll only be receiving one message, display it, and send
   * a message of our own to the connected client.
   **/

  char msg[] = "gperson";
  char received_msg[5];

  // Receive a message
  received_result = recv(client_sfd, received_msg, sizeof(received_msg), 0);
  if (received_result < sizeof(received_msg))
  {
    printf("WARNING: Received message was shorter than expected.\n");
    printf("Received message was \'%s\'\n", received_msg);
    printf("Attempting to send message to client anyways...\n");
  }

  printf("Received message from client: %s\n", received_msg);

  received_result = send(client_sfd, msg, sizeof(msg), 0);
  if (received_result < sizeof(msg))
  {
    printf("WARNING: Sent message was shorter than expected\n");
  }

  printf("Connection finished. Cleaning up...\n");
  close(client_sfd);
  close(socket_fd);
  return 0;
}

