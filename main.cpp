#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"

#define UPDATE_FILE     "/sd/update.bin"

#define PIN_SD_MOSI                   P0_9
#define PIN_SD_MISO                   P0_8
#define PIN_SD_SCLK                   P0_7
#define PIN_SD_SSEL                   P0_6
#define PIN_SD_VDD_CONTROL_BAR        P0_5

SDBlockDevice * pSd = NULL;
FATFileSystem * pFs = NULL;

DigitalOut sdVddControlBar(PIN_SD_VDD_CONTROL_BAR, 1);


int main()
{
	sdVddControlBar = 0;
	wait_ms (50);
    pSd = new SDBlockDevice(PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_SCLK, PIN_SD_SSEL);
	pFs = new FATFileSystem("sd");
	
    pSd->init();
    pFs->mount(pSd);

    for(unsigned bc = 0; bc <= 500; bc++)
    {
    		FILE *file = fopen("/sd/sdtest.txt", "a");
    		if (file != NULL) {
        		fprintf(file, "%d \n", bc);
        		fclose(file);
        		printf("Write successful \r\n");
    		} else {
        		printf("Could not open file for write \r\n");
    		}
    }

    pFs->unmount();
    pSd->deinit();

	while(true){}
}





//#include "mbed.h"
//#include "SDBlockDevice.h"
//#include "FATFileSystem.h"
//
//#define UPDATE_FILE     "/sd/update.bin"
//
//#define PIN_SD_MOSI                   P0_9
//#define PIN_SD_MISO                   P0_8
//#define PIN_SD_SCLK                   P0_7
//#define PIN_SD_SSEL                   P0_6
//#define PIN_SD_VDD_CONTROL_BAR        P0_5
//
//SDBlockDevice * pSd = NULL;
//FATFileSystem * pFs = NULL;
//
//DigitalOut sdVddControlBar(PIN_SD_VDD_CONTROL_BAR, 1);
//
//int main()
//{
//	sdVddControlBar = 0;
//	wait_ms (50);
//    pSd = new SDBlockDevice(PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_SCLK, PIN_SD_SSEL);
//	pFs = new FATFileSystem("sd");
//
//    pSd->init();
//    pFs->mount(pSd);
//
//    //----------------------------------- Perform a write test ---------------------------------------------
//    printf("\nWriting to SD card...");
//    FILE *file = fopen("/sd/sdtest.txt", "w");
//    if (file != NULL) {
//        printf("1 \r\n");
//
//        fprintf(file, "Hello fun SD Card World!");
//        printf("2 \r\n");
//
//        fclose(file);
//        printf("Write successful \r\n");
//    } else {
//        printf("Could not open file for write \r\n");
//    }
//
//    //----------------------------------- Perform a read test ---------------------------------------------
//    printf("Reading from SD card... \r\n");
//    file = fopen("/sd/sdtest.txt", "r");
//    if (file != NULL)
//    {
//    		char c = fgetc(file);
//        	if (c == 'H'){
//        		printf("success! \r\n");
//        	}else{
//        		printf("incorrect char (%c)! \r\n", c);
//        	}
//        	fclose(file);
//	} else {
//			printf("failed! \r\n");
//	}
//
//    pFs->unmount();
//    pSd->deinit();
//
//	while(true){}
//}
