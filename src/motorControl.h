#ifndef motorControl_H_
#define motorControl_H_

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

static int fd1;

#define RUN_TRAIN 1
#define STOP_TRAIN 0

int testMotor(void);

int setTrainState(int state);

#endif
