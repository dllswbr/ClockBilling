#include<iostream>
//#include<ctime>
//#include<time.h>
#include<Windows.h>
#include<conio.h>

using namespace std;
class _24HourTime;

// Definition of enum which tracks AM or PM in 12 hour clock
enum AMPM {
    AM, PM
}ampm;

// Abstract class used to track time
class Time {

public:

    int hour{};
    int minute{};
    int second{};

    virtual void addOneHour() = 0;
    virtual void addOneMinute() = 0;
    virtual void addOneSecond() = 0;
};

// _12HourTime class which inherits the Time class
class _12HourTime : public Time {

    // Method to manage the 12 hour time
public:
    _12HourTime(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
        ampm = AM;
    }

    // Method to add one hour to the clock
    void addOneHour() override {
        if (hour == 12) {
            hour = 1;
            ampm = ampm == AM ? PM : AM;
        }
        else {
            hour += 1;
        }
    }

    // Method to add one minute to the clock
    void addOneMinute() override {
        if (minute == 59) {
            // adds 1 to the hour if minute passes 59
            minute = 0;
            addOneHour();
        }
        else {
            minute += 1;
        }
    }

    // Method to add one second to the clock
    void addOneSecond() {
        if (second == 59) {
            second = 0;
            //adds 1 to the minute when second passes 59
            addOneMinute();
        }
        else {
            second += 1;
        }
    }

    // Declare friend to give proper access
    friend void displayTime(const _12HourTime&, const _24HourTime&);
};

// _24HourTime class which inherits the Time class
class _24HourTime : public Time {

    // Method to manage 24 hour time
public:

    _24HourTime(int h, int m, int s) {
        hour = h;
        minute = m;
        second = s;
    }

    // Method to add one hour to the clock the same as for our 12 hour clock

    void addOneHour() {
        if (hour == 23) {
            hour = 0;
        }
        else {
            hour += 1;
        }
    }

    // Method to add one minute to the clock

    void addOneMinute() {
        if (minute == 59) {
            minute = 0;
            addOneHour();
        }
        else {
            minute += 1;
        }
    }

    // Method to add one second to the clock

    void addOneSecond() {
        if (second == 59) {
            second = 0;
            addOneMinute();
        }
        else {
            second += 1;
        }
    }

    // Declaring friend to give proper access
    friend void displayTime(const _12HourTime&, const _24HourTime&);
};

// Displaytime will be able to display time with appropriate formatting
void displayTime(const _12HourTime& time12, const _24HourTime& time24) {

    cout << "*************************** ***************************\n";
    cout << "*     12-Hour Clock       * *      24-Hour Clock      *\n";
    cout << "*     "; if (time12.hour < 10) cout << "0"; cout << time12.hour << ":";
    if (time12.minute < 10) cout << "0"; cout << time12.minute << ":";
    if (time12.second < 10) cout << "0"; cout << time12.second;
    if (ampm == AM) cout << " A M"; else cout << " P M";
    cout << "        * *         ";
    if (time24.hour < 10) cout << "0"; cout << time24.hour << ":";
    if (time24.minute < 10) cout << "0"; cout << time24.minute << ":";
    if (time24.second < 10) cout << "0"; cout << time24.second;
    cout << "        *\n";
    cout << "*************************** ***************************\n";

}

// Create the interface for our decision making process

void displayMenu() {

    system("CLS");
    cout << "***************************" << endl;
    cout << "* 1 - Add One Hour        *" << endl;
    cout << "* 2 - Add One Minute      *" << endl;
    cout << "* 3 - Add One Second      *" << endl;
    cout << "* 4 - Exit Program        *" << endl;
    cout << "***************************" << endl;
}

// Declare main method

int main() {

    //Create clocks
    _12HourTime time_12_Clock(11, 59, 59);
    _24HourTime time_24_Clock(23, 59, 59);

    displayTime(time_12_Clock, time_24_Clock);

    int userInput = 0;
    //_kbhit() is needed so that our loop will run until the keyboard is pressed.
    while(!_kbhit()) {
        time_12_Clock.addOneSecond();
        time_24_Clock.addOneSecond();
        displayTime(time_12_Clock, time_24_Clock);
        //Sleep provides the means to pause the program for 1 sec.
        Sleep(1000);
        //recycles the interface to show the ticking of the seconds.
        system("CLS");
        // breaks the while loop whenever the keyboard is hit.
        if (_kbhit()) {
            displayMenu();
            int choice;
            cin >> choice;
            // Add interface functionality

            switch (choice) {
                case 1:
                    time_12_Clock.addOneHour();
                    time_24_Clock.addOneHour();
                    displayTime(time_12_Clock, time_24_Clock);
                    break;

                case 2:
                    time_12_Clock.addOneMinute();
                    time_24_Clock.addOneMinute();
                    displayTime(time_12_Clock, time_24_Clock);
                    break;

                case 3:
                    time_12_Clock.addOneSecond();
                    time_24_Clock.addOneSecond();
                    displayTime(time_12_Clock, time_24_Clock);
                    break;

                case 4:
                    cout << "Now exiting program." << endl;
                    exit(1);
                    break;

                default:
                    // Put an error check in place
                    cout << "Error: Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }
}

