#include <iostream>
#include <thread>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;
clock_t T_Begin;
clock_t T_End;
double T_Record[11];
int i = 0;
volatile bool Post = false;
volatile bool Restart = false;
volatile bool Exit = false;
volatile bool Clear = false;
void Time_Count() {
	while (true){
		T_Begin = clock();
		i = 0;
		if (Exit) {
			i = 0;
			system("cls");
			cout << "Will end after 3 seconds!";
			Sleep(3000);
			break;
		}
		while (true) {
			system("cls");
			T_End = clock();
			double Temp_T = ((double)T_End - (double)T_Begin) / 1000;
			cout << "Press \"C\" or \"c\" to clear the records !" << endl;
			cout << "Press \"P\" or \"p\" to post the time !" << endl;
			cout << "Press \"R\" or \"r\" to restart !" << endl;
			cout << "Press \"ESC\" to exit !" << endl;
			cout << "-----------------------------------------" << endl;
			cout << "\n" << "Current Time is " << Temp_T << "\n" << endl;
			cout << "-----------------------------------------" << endl;
			if (Post) {
				if (i<10){
					i++;
					T_Record[i] = Temp_T;
					Post = false;
				}
			}
			for (int j = 1; j <= i; j++) {
				cout << "Time " <<j<<" is "<< T_Record[j]<< endl;
			}
			if (i<10){
				cout << "-----------------------------------------" << endl;
				cout << "Still have "<<10-i<<" grids remained !";
			}
			else{
				cout << "-----------------------------------------" << endl;
				cout << "No grid left !";
			}
			if (Clear) {
				Clear = false;
				i = 0;
			}
			if (Restart||Exit) {
				i = 0;
				Restart = false;
				break;
			}
			Sleep(10);
		}
	}
}
void Get_Key() {
	while (true)
	{
		if (_kbhit()) {
			char K = _getch();
			if (K == 67 || K == 99) {
				Clear = true;
			}
			if (K == 80 ||K== 112) {
				Post = true;
			}
			if (K == 82 ||K== 114) {
				Restart = true;
			}
			if (K == 27) {
				Exit = true;
			}
		}
		if (Exit) {
			break;
		}
	}
}
int main() {
	thread TimeCount(Time_Count);
	thread Control(Get_Key);
	TimeCount.join();
	Control.join();
	return 0;
}