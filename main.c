//PS2ChangeLEDColor by silverhacker >:D

#include <stdio.h>
#include <kernel.h>
#include <debug.h>
#include <tamtypes.h>
#include <libcdvd.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <unistd.h>

/*
    This program can change the color of the LED in the power button of PlayStation 2

    So far I've only tested the program on my PS2 Slim SCPH-90010, so I don't know if it works on other models
    or if it works on PS2 Fat (most likely it doesn't work)

    WARNING!!!!

    I am NOT responsible for any damage your console may suffer from using this program!

    Use at your own risk!
*/

/*
    Many thanks to Matías Israelson (aka el_isra) for telling me where to get 
    SCMD commands for the MechaCon, thanks to him I got the SCMD to change the LED color :D
*/

#define LED_OFF 0x00
#define LED_RED 0x01
#define LED_GREEN 0x02
#define LED_ORANGE 0x03

int ChangeLEDColor(u32 color_param, u32 *stat)
{
    unsigned char subcommand, out_buffer[16];

    int result = 0;
    subcommand = color_param;

    result = sceCdApplySCmd(0x25, &subcommand, sizeof(subcommand), out_buffer);

    if(result != 0)
    {
        *stat = out_buffer[0];
    }

    return result;
}

void LoadModules()
{   
    int ret;

    ret = SifLoadModule("rom0:SIO2MAN", 0, NULL);

    if(ret < 0){
        printf("Error loading SIO2MAN :( :(\n");
        SleepThread();
    }

	ret = SifLoadModule("rom0:CDVDMAN", 0, NULL);

    if(ret < 0){
        printf("Error loading CDVDMAN :(\n");
        SleepThread();
    }

	ret = SifLoadModule("rom0:CDVDFSV", 0, NULL);
    if(ret < 0){
        printf("Error loading CDVDFSV :(\n");
        SleepThread();
    }
}

int main()
{   
    u32 stat;

    //Reset IOP
    SifInitRpc(0);
	SifIopReset("", 0);
	while(!SifIopSync()){}

	SifInitRpc(0);
	SifLoadFileInit();

    LoadModules();
    
    sceCdInit(SCECdINoD);

    while(1)
    {
        ChangeLEDColor(LED_OFF, &stat); //Off
        sleep(1);
        ChangeLEDColor(LED_RED, &stat); //Red
        sleep(1);
        ChangeLEDColor(LED_GREEN, &stat); //Green
        sleep(1);
        ChangeLEDColor(LED_ORANGE, &stat); //Orange
        sleep(1);
    }

    return 0;

}