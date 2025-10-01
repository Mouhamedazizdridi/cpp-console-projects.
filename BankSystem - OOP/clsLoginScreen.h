#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    

    static  bool _Login()
    {
        bool LoginFaild = false;
        int Trials = 3;

        string Username, Password;
        do
        {

            
            if (Trials == 0) {
                cout << "You are Locked after 3 faild trials";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();
            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
                Trials -= 1;
                cout << "You have " << Trials << " Trial(s) to login .\n\n";
            }
            

        } while (LoginFaild);
        CurrentUser.RegisterLogIn();

        clsMainScreen::ShowMainMenue();
        return true;

    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

