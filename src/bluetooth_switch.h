#ifndef BLUETOOTH_SWITCH_H_
#define BLUETOOTH_SWITCH_H_

#include "bluetooth.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

#define GPIO_GPX_CONFIG_BASE_ADDR 0x13400000

using namespace std;

static volatile uint32_t* gpioGPX;

static int ardu;

static int mysock;

static char ON_RED_LIGHT='1';
static char OFF_RED_LIGHT='0';

int bluetooth_SW(void);

int openSerial(void);
int setGPIO(void);
int readState(void);

int readGPIO(void);

int initGPIO(void);
int openFileDiscriptor(void);
unsigned int* mapMemory(int fd, int addrBase);

#endif
