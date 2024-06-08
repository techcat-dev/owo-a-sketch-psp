#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

PSP_MODULE_INFO("Controller", 0, 1, 1);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define printf pspDebugScreenPrintf

int done = 0;

int exit_callback(int arg1, int arg2, void *common)
{
    done = 1;
    return 0;
}

int callback_thread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback",
        exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void)
{
    int thid = sceKernelCreateThread("update_thread",
        callback_thread, 0x11, 0xFA0, 0, 0);

    if(thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

void SetY(int *y) {
    (*y) += 3;
}

void SetYneg(int *y) {
    (*y) += -3;
}

void SetX(int *X) {
    (*X) += 5;
}

void SetXneg(int *X) {
    (*X) += -5;
}

int y = 0;
int x = 0;



int main(void)
{
    SceCtrlData pad;

    pspDebugScreenInit();
    setup_callbacks();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    while (!done)
    {
        pspDebugScreenSetXY(0, 0);
        sceCtrlReadBufferPositive(&pad, 1);

        printf("OWO \n");
        

        if (pad.Buttons != 0)
        {
            if (pad.Buttons & PSP_CTRL_SQUARE)
            {

            }
            if (pad.Buttons & PSP_CTRL_TRIANGLE)
            {



            }
            if (pad.Buttons & PSP_CTRL_CIRCLE)
            {
                

            }
            if (pad.Buttons & PSP_CTRL_CROSS)
            {
                


            }

            if (pad.Buttons & PSP_CTRL_UP)
            {
                
                SetYneg(&y);
                pspDebugScreenSetXY(x, y);
                sleep(1);
                printf("OwO");

            }
            if (pad.Buttons & PSP_CTRL_DOWN)
            {
                SetY(&y);
                pspDebugScreenSetXY(x, y);
                sleep(1);
                printf("OwO");

            }
            if (pad.Buttons & PSP_CTRL_LEFT)
            {
                
                SetXneg(&x);
                pspDebugScreenSetXY(x, y);
                sleep(1);
                printf("OwO");

            }
            if (pad.Buttons & PSP_CTRL_RIGHT)
            {

                SetX(&x);
                pspDebugScreenSetXY(x, y);
                sleep(1);
                printf("OwO");
                


            }
              if (pad.Buttons & PSP_CTRL_START)
            {
                
               sceKernelExitGame();
                return 0;          
            }

              if (pad.Buttons & PSP_CTRL_SELECT)
            {


                x = 0;
                y = 0;
                pspDebugScreenClear();


            }
        }
    }

    sceKernelExitGame();
    return 0;
}

