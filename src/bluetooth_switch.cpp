#include "bluetooth_switch.h"

int bluetooth_SW(void){
	int prev;
	openSerial();

	setGPIO();

//	cout<<"here"<<endl;

	int state;

	prev=readState();

	while(1){
		state=readState();
		if ((state!=prev)&&(state==1)){
			mysock=startBeacon();
			write(ardu,&ON_RED_LIGHT,1);
			prev=state;

		}
		else if((state!=prev)&(state==0)){
			pauseBeacon(mysock);
			write(ardu,&OFF_RED_LIGHT,1);
			prev=state;
		}
	}


	return 0;
}

int readState(void){
	return (*(gpioGPX + (0x0c24 >> 2))>>2)&1;
}

int openSerial(void){
	ardu=open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	return 0;
}

int setGPIO(void){
	initGPIO();



	*(gpioGPX + (0x0c20 >> 2)) &= 0x0;  //init config

	*(gpioGPX + (0x0c20 >> 2)) |= (1<<(4*5));	// 13pin OUTPUT
	*(gpioGPX + (0x0c20 >> 2)) &= ~(1<<(4*2));	// 15pin INPUT
	*(gpioGPX + (0x0c20 >> 2)) |= (1<<(4*6));	// 17pin OUTPUT

	*(gpioGPX + (0x0c24 >> 2)) |= (1<<5);		//13pin HIGH
	*(gpioGPX + (0x0c24 >> 2)) &= ~(1<<6);		//17pin LOW

	return 0;
}

int initGPIO(void){
	int fd = openFileDiscriptor();
	if(fd == -1){
		return -1;
	}

	gpioGPX = mapMemory(fd,GPIO_GPX_CONFIG_BASE_ADDR);

	return 0;
}

int openFileDiscriptor(void){
	int fd;

	if((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0){
		printf("Unable to open /dev/mem\n");
		return -1;
	}

	return fd;
}

unsigned int* mapMemory(int fd, int addrBase){
//	int addrBase = 0;
//
//	switch(peripherel){
//	case PERIPHEREL_GPX:
//		addrBase = GPIO_GPX_CONFIG_BASE_ADDR;
//		break;
//	case PERIPHEREL_GPA:
//		addrBase = GPIO_GPA_CONFIG_BASE_ADDR;
//		break;
//	case PERIPHEREL_GPB:
//		addrBase = GPIO_GPB_CONFIG_BASE_ADDR;
//		break;
//	default:
//		return NULL;
//	}

	unsigned int* gpio = (unsigned int*)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, addrBase);

	if(gpio < 0){
		printf("Mmap failed.\n");
		return NULL;
	}

	return gpio;
}

int readGPIO(void){
	int read_state;


	initGPIO();

//	printf("GPX1CON register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c20 >> 2)));
//	printf("GPX1DAT register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c24 >> 2)));
//	cout<<endl;
	*(gpioGPX + (0x0c20 >> 2)) &= 0x0;
//	printf("GPX1CON register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c20 >> 2)));
	*(gpioGPX + (0x0c20 >> 2)) |= (1<<(4*5));
	*(gpioGPX + (0x0c20 >> 2)) &= ~(1<<(4*2));
	*(gpioGPX + (0x0c20 >> 2)) |= (1<<(4*6));
//	cout<<endl;

//	printf("GPX1CON register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c20 >> 2)));

	*(gpioGPX + (0x0c24 >> 2)) |= (1<<5);
	*(gpioGPX + (0x0c24 >> 2)) &= ~(1<<6);

//	printf("GPX1DAT register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c24 >> 2)));

	while(1){
		printf("GPX1DAT register : 0x%08x\n",*(unsigned int *)(gpioGPX + (0x0c24 >> 2)));

		read_state=(*(gpioGPX + (0x0c24 >> 2))>>2)&1;

		printf("read_state : %d\n",read_state);

		sleep(1);
	}

	return 0;
}
