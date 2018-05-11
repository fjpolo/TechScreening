#include "../include/kenkou_keyboard_monitor.h"

int  main(void){

    printInstructions();

    for(;;){
        kenkouKeyboardMonitor();
    }
}
