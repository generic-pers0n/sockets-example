#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  int socket_fd, result;
  struct sockaddr_in server_address;
  socklen_t sa_size = sizeof(server_address); // size of server_address

  if (argc < 2)
  {
    printf("Usage: %s [address]\n", argv[0]);
    return 0;
  }

  printf("Connecting to server...\n");

  // Create a new socket
  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket < 0)
  {
    perror("ERROR: cannot create socket");
    return -1;
  }

  // Bind the socket to the server address
  printf("Connecting to server @ \'%s\'...\n", argv[1]);

  memset(&server_address, 0, sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_port   = htons(50000);
  result = inet_pton(AF_INET, argv[1], &server_address.sin_addr);
  if (result <= 0)
  {
    perror("inet_pton error");
    close(socket_fd);
    return -1;
  }
  /*result = inet_aton(argv[1], &server_address.sin_addr);
  if (result < 1)
  {
    perror("inet_aton error");
    close(socket_fd);
    return -1;
  }*/

  result = connect(socket_fd, (struct sockaddr*) &server_address, sa_size);
  if (result < 0)
  {
    perror("connect(): cannot connect to server");
    close(socket_fd);
    return -1;
  }

  /** From this point on, we'll be able to receive message from the server. For
   * our specific purposes, we'll be sending a simple message to the server and
   * the server will be able to display it on the screen. Then, after that, the
   * server will send a message of its own, and the client will be able to
   * display that message.
   **/

  printf("Successfully connected to the server @ \'%s\'\n", argv[1]);

  // Send a message
  char msg[] = "thicc";
  char received_msg[7];

  ssize_t msg_result = send(socket_fd, msg, sizeof(msg), 0);
  if (msg_result < sizeof(msg))
  {
    perror("send");
    printf("WARNING: message was short. Expected 4 bytes instead of %ld\n", msg_result);
    printf("Attempting to receive message from server anyways...\n");
  }

  sleep(1);

  // Receive a message
  msg_result = recv(socket_fd, received_msg, sizeof(received_msg), 0);
  if (msg_result < sizeof(received_msg))
  {
    perror("recv");
    printf("WARNING: received message was short. Expected to receive 7 bytes instead of %ld\n", msg_result);
    printf("Received message \'%s\'\n", received_msg);
  }

  printf("Receivged message from server: %s\n", received_msg);

  printf("Connection finished. Closing...\n");
  close(socket_fd);
  printf("Goodbye!\n");
  return 0;
}

