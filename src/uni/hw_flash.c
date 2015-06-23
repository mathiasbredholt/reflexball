#include "game_data.h"

#if defined(_Z8F6403)
#include <ez8.h>


void hw_flash_save(PlayerData *playerData) {
	asm (" LDE r0, (\playerData->coins)");
	// OCDCTL |= 0xA0; // Enable On-Chip Debugger and disable read protection

	// DBG = 0x0C; // Data write mode
	// DBG = 0x00; // Data memory address 15:8
	// DBG = 0x00; // Data memory address 7:0
	// DBG = 0x00; // Size in bytes 15:8
	// DBG = 0x02; // Size in bytes 7:0
	// DBG = playerData->coin;

	// OCDCTL &= 0x5F; // Disable On-Chip Debugger and enable read protection
}

void hw_flash_load(PlayerData *playerData) {
	asm (" LDE (\playerData->coins), r0");
	// OCDCTL |= 0x80; // Enable On-Chip Debugger

	// DBG = 0x0D; // Data read mode
	// DBG = 0x00; // Data memory address 15:8
	// DBG = 0x00; // Data memory address 7:0
	// DBG = 0x00; // Size in bytes 15:8
	// DBG = 0x02; // Size in bytes 7:0
	// playerData->coin = DBG;

	// OCDCTL &= 0x7F; // Disable On-Chip Debugger
}

#endif

#if defined(__APPLE__) || defined(__WIN32__)
void hw_flash_save(PlayerData *playerData) {}

void hw_flash_load(PlayerData *playerData) {}
#endif