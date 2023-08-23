#include "login.h"
void ReceiveNotifications(const char *username) {
  char pipeName[256];
  snprintf(pipeName, sizeof(pipeName), PIPE_NAME_TEMPLATE, username);
  mkfifo(pipeName, 0666);
  int hPipe = open(pipeName, O_RDONLY); // Open for reading

  if (hPipe != -1) {
    while (1) {
      char buffer[256];
      ssize_t bytesRead = read(hPipe, buffer, sizeof(buffer) - 1);
      if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Received Notification: %s\n", buffer);
      }
    }
    close(hPipe);
  } else {
    // Handle pipe open error
    perror("Error opening pipe for reading");
  }
}
