#ifndef _HW_FLASH_H_
#define _HW_FLASH_H_
void hw_flash_init();

void WriteByteToFlash(int location, unsigned int value);

unsigned int ReadByteFromFlash(int location);
#endif