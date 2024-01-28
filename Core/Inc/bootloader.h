/*
 * Bootloader Basic
 *
 * Author : Chau Thanh Dat
 * 31.12.2023
 */
#include"main.h"

#define APP1_ADDRESS_START  (0x08005000)	//Origin + Bootloader size (20kB)
#define APP2_ADDRESS_START  (0x0800A800)	//Origin + Bootloader size (20kB) + App1 Bank (22kB)
#define BANK_SIZE 			(0X5800)		//22kB
#define PAGE_USER			(0X400)			//1kB

#define ERASE_FLASH_MEMORY 	"#$ERASE_MEM"
#define FLASHING_START 		"#$FLASH_START"
#define FLASHING_FINISH 	"#$FLASH_FINISH"
#define FLASHING_ABORT 		"#$FLASH_ABORT"

typedef void (application_t) (void);

typedef struct
{
    uint32_t		stack_addr;     // Stack Pointer
    application_t*	func_p;        // Program Counter
} JumpStruct;

typedef enum
{
	App1 = 0,
	App2 = 1,
} AppSelection;

void DeInit();
void bootloaderInit();
void JumpToApplicationApp(uint32_t address);
uint32_t readData(uint32_t address);
void errorBlink();
