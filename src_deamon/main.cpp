#include <iostream>
#include <cstdlib>

#include <chrono> // for pause
#include <thread>

#include <ctime> //for time

//for file streams
#include <iostream>
#include <fstream>
using namespace std;

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

bool flagCheck(string filePath) {
	string flag;
	ifstream fileStream;
	fileStream.open (filePath);

	getline(fileStream, flag);
	if (flag == "true") {
		fileStream.close();
		return true;
	}
	else {
		fileStream.close();
		return false;
	}	
}

void psDemon() {
	string outTop, outDateTime;
	ofstream myFile;

	for (;;) {
		myFile.open ("example.txt", ios::app); //ios::app ->All output operations are performed 
		//at the end of the file, appending the content to the current content of the file.
		outDateTime = currentDateTime();
        cout << outDateTime << endl;
		
		myFile << outDateTime << endl;
		myFile.close(); //for sync output
		system("top -b -n 2 | egrep 'Cpu|Swap' | cat >> example.txt"); //TODO rewrite file stream in C++

		this_thread::sleep_for(chrono::seconds(10)); //-std=c++11

		if (flagCheck("flag.txt") == false) {
			cout << "App closed." << endl;
			return;
		}
	}
}


int main() {

	psDemon();
		
	return 0;
}
