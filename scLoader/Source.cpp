#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// We make it independent of other WinBase APIs
extern "C" bool __stdcall VirtualProtect(void* ad, unsigned long sz, unsigned long prot,unsigned long* old);
extern "C" int  free(char* c);

int main(int argc, char** argv)
{
	if (argc != 2)
		return -1;

	FILE* file = fopen(argv[1], "rb");
	if (file == 0)
		return -2;

	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data = new char[size-1];

	int i = 0; char c;
	while ((c = getc(file)) != EOF)
	{
		data[i] = c;
		i++;
	}

	VirtualProtect((void*)data, size, 0x40, NULL);

	__asm call data        // LOL: We are Calling DATA :P

	delete [] data;

	return 0;
}