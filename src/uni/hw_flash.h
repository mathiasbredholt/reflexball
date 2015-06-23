unsigned int UnlockFlash(void);

void LockFlash(void);

unsigned int EraseFlash(unsigned int pagenum);

void WriteByteToFlash(int location, unsigned int value);

void WriteByteToFlash1(int location, unsigned int value);

unsigned int ReadByteFromFlash(int location);