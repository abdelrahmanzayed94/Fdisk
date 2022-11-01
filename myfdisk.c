#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#define SECTOR_SIZE	512

typedef struct 
{
	uint8_t status;
	uint8_t chsOfFirstSector[3];
	uint8_t pType;
	uint8_t chsOfLastSector[3];
	uint32_t lba;
	uint32_t sectorsCount;	
} PartitionEntry_s;

void print_buffer(char* buf, int len)
{
	for(int i = 0; i < len; i++)
	{
		if(i % 16 == 0 && i != 0)
			printf("\n");
		printf("%02X ", buf[i] & 0xFF);
	}
	
	printf("\n");
}

int main(int argc, char** argv)
{
	int index = 0;
	char buf[SECTOR_SIZE];
	bool extendedFlag = false;
	uint32_t extendedLba = 0;
	uint32_t extendedLbaIterator = 0;
	uint32_t extendedSectorsCount = 0;
	PartitionEntry_s* partitionEntryPtr;

	if(argc < 2)
	{
		printf("too few arguments!\n");
		goto function_exit;
	}
	
	int fd = open(argv[1], O_RDONLY);
	
	if(fd == -1)
	{
		if(errno == EACCES)
			printf("permission denied!\n");
		else if(errno == ENOENT)	
			printf("no such file or directory!\n");
		else
			printf("error number %d occured in opening the file!\n", errno);
		
		goto function_exit;
	}
	
	read(fd, buf, SECTOR_SIZE);
	
	//print_buffer(&buf[446], 66);
	
	partitionEntryPtr = (PartitionEntry_s*) &buf[446];
	
	for(index = 1; index < 5; index++)
	{
		//check if there is available partition, if not continue
		if(partitionEntryPtr->lba == 0)
			continue;
		
		printf("Device: %s%d\n", argv[1], index);
		printf("Boot: %s\n", partitionEntryPtr->status == 0x80? "*" : " ");
		printf("Start: %d\n", partitionEntryPtr->lba);
		printf("End: %d\n", partitionEntryPtr->lba + partitionEntryPtr->sectorsCount - 1);
		printf("Sectors: %d\n", partitionEntryPtr->sectorsCount);
		printf("Size: %ld Bytes\n", (uint64_t)partitionEntryPtr->sectorsCount * SECTOR_SIZE);
		printf("Id: %x\n", partitionEntryPtr->pType);
		printf("Type: %s\n", partitionEntryPtr->pType == 0x83? "Linux" : partitionEntryPtr->pType == 0x05? "Extended" : "Other");
		printf("**********************\n");
		
		//check if there is available extended parition type
		if(partitionEntryPtr->pType == 0x05)
		{
			extendedFlag = true;
			extendedLba = partitionEntryPtr->lba;
			extendedSectorsCount = partitionEntryPtr->sectorsCount;
		}
		
		partitionEntryPtr++;
	}
	
	if(extendedFlag)
	{
		extendedLbaIterator = extendedLba;
		while(true)
		{
			//printf("extendedLbaIterator = %d\n", extendedLbaIterator);
			lseek(fd, extendedLbaIterator * SECTOR_SIZE, SEEK_SET);
			read(fd, buf, SECTOR_SIZE);		
			//print_buffer(&buf[446], 66);
			partitionEntryPtr = (PartitionEntry_s*) &buf[446];
		
			printf("Device: %s%d\n", argv[1], index);
			printf("Boot: %s\n", partitionEntryPtr->status == 0x80? "*" : " ");
			printf("Start: %d\n", partitionEntryPtr->lba + extendedLbaIterator);
			printf("End: %d\n", partitionEntryPtr->lba + extendedLbaIterator + partitionEntryPtr->sectorsCount - 1);
			printf("Sectors: %d\n", partitionEntryPtr->sectorsCount);
			printf("Size: %ld Bytes\n", (uint64_t)partitionEntryPtr->sectorsCount * SECTOR_SIZE);
			printf("Id: %x\n", partitionEntryPtr->pType);
			printf("Type: %s\n", partitionEntryPtr->pType == 0x83? "Linux" : partitionEntryPtr->pType == 0x05? "Extended" : "Other");
			printf("**********************\n");
			
			index++;
			partitionEntryPtr++;
			if(partitionEntryPtr->lba == 0)
				break;
				
			extendedLbaIterator = extendedLba + partitionEntryPtr->lba;
		}
	}

function_exit:
	return 0;
}

