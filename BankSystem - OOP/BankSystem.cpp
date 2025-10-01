#include <iostream>
#include<iomanip>
#include"clsLoginScreen.h"



int main()

{

    
    while (true) {
        
        if (!clsLoginScreen::ShowLoginScreen()) {
            break;
        }
    }
    system("pause>0");
    return 0;
}