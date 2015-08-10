#include "motorControl.h"

int testMotor(void){
	char HIGH='1',LOW='0';

	fd1=open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

	while(1){
		write(fd1,&HIGH,1);

		sleep(2);

		write(fd1,&LOW,1);

		sleep(2);
	}
	return 0;
}
