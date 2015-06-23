#include "hw_flash.h"

#if defined(_Z8F6403)
#include <ez8.h>

#define PAGE_SIZE 512

char far Flash_Page[PAGE_SIZE];				// Far is used so this variable is placed in Edata
char near RamByte;

void hw_flash_init() {
	init_flash();
}

/****************************************************************/
/* This function unlocks Flash for Flash Programming 			*/
/****************************************************************/
unsigned int UnlockFlash(void)
{
	if ( (FSTAT & 0x3F) == 0x00 )			// Flash Controller Locked state
	{
		FCTL = 0x73;						// First unlock command

		if ( (FSTAT & 0x3F) == 0x01 )		// First unlock Command recieved
		{
			FCTL = 0x8C;					// Second unlock command

			if ( (FSTAT & 0x3F) == 0x02 )	// Unlocked programming state
				return 0x00;
			else
				return 0xFF;
		}
		else
			return 0xFF;

	}
	else
		return 0xFF;

}

/****************************************************************/
/* Locks the Flash controller 									*/
/****************************************************************/
void LockFlash(void)
{
	while ( (FSTAT & 0x3F) != 0x00 )
	{
		FCTL = 0xFF;						// write some value other than 0x73, 0x8c, 0x95, and 0x63
		// to Flash control Register
	}


}


/****************************************************************/
/* This function Erases the page "pagenum" in Flash */
/****************************************************************/
unsigned int EraseFlash(unsigned int pagenum)
{
	unsigned int status;

	status = UnlockFlash();

	if (status == 0x00)
	{	// check if Flash is unlocked
		FPS = pagenum;						// Set the page to be erased
		FCTL = 0x95;						// Page erase
	}

// No need to unlock as Flash controller locks immediatetly after page erase
}

/****************************************************************/
void WriteByteToFlash(int location, unsigned int value)
{
	unsigned int pagenum;
	int i, TempLoc;
	char Interrupts;

	pagenum = (location >> 9);
	TempLoc = (location & 0xFE00);

	for (i = 0; i < PAGE_SIZE; i++)
		Flash_Page[i] = ReadByteFromFlash(TempLoc + i);

	Flash_Page[location - TempLoc] = value;

	Interrupts = IRQCTL;
	IRQCTL = 0x00;

	EraseFlash(pagenum);

//	Flash_Page[location - TempLoc] = value;

	for (i = 0; i < PAGE_SIZE; i++)
		WriteByteToFlash1(TempLoc + i, Flash_Page[i]);

	LockFlash();

	IRQCTL = Interrupts;
//	EI();
}

/****************************************************************/
void WriteByteToFlash1(int location, unsigned int value)
{
	UnlockFlash();

	RamByte = (location >> 8);
	asm("LD R8, _RamByte");

	RamByte = (location & 0x00FF);
	asm("LD R9, _RamByte");

	RamByte = value;
	asm("LD R10, _RamByte");

	asm("LDC @RR8, R10");						// Load Byte into Flash location

}

unsigned int ReadByteFromFlash(int location)
{
	unsigned int value;

	RamByte = (location >> 8);
	asm("LD R8, _RamByte");

	RamByte = (location & 0x00FF);
	asm("LD R9, _RamByte");

	asm("LDC R10, @RR8");
	asm("LD _RamByte, R10");
	value = RamByte;

	return (value & 0xFF);
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_flash_save(PlayerData *playerData) {}

void hw_flash_load(PlayerData *playerData) {}
#endif