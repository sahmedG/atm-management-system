#include "login.h"

void *notificationThread(void *args) {
  const char *username = (const char *)args;
  while (!terminateThread) {
    ReceiveNotifications(username);
    usleep(1000000); // Sleep for 1 second
  }
  return NULL;
}
