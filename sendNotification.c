#include "login.h"

void SendNotification(const char *targetUsername, const char *message) {
  char pipeName[256];
  snprintf(pipeName, sizeof(pipeName), PIPE_NAME_TEMPLATE, targetUsername);

  int hPipe = open(pipeName, O_WRONLY); // Open for writing

  if (hPipe != -1) {
    ssize_t bytesWritten = write(hPipe, message, strlen(message));
    if (bytesWritten == -1) {
      // Handle write error
      perror("Error writing to pipe");
    }
    close(hPipe);
  } else {
    // Handle pipe open error
    perror("Error opening pipe");
  }
}
