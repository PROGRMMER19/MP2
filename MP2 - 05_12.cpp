#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <conio.h>

using namespace std;

struct Video {
	int id;
	string title;
	bool isAvailable;

	Video() : id(0), title(""), isAvailable(false) {}
};
//set max number of videos can handle
const int MAX_VIDEOS = 100;
string userType;

//function prototyping
void intValidation(int& num);
void dblValidation(double& dbl);
void strValidation(string& str);
void userValidation(string& input);

void regAccount();
void loginAccount(int& loginSuccess);
void exitProgram(bool& termination);

void preMenu();
void mainMenu();

void addVideo(Video* videos, int& currentCount);
void updateVideo(Video* videos, int count);
void displayVideos(const Video* videos, int count);
void deleteVideo(Video* videos, int& count);
void saveVideos(const Video* videos, int count);
void loadVideos(Video* videos, int& count);

int main() {
	Video* videos = new Video[MAX_VIDEOS];
	int currentCount = 0, choice;
	bool termination = false;

	preMenu();
	loadVideos(videos, currentCount); // load the videos from the file 

	while (!termination) {
		//display our menu
		mainMenu();
		cout << "Enter your choice: ";
		cin >> choice;

		system("cls");

		switch (choice) {
		case 1:
			addVideo(videos, currentCount);
			break;
		case 2:
			updateVideo(videos, currentCount);
			break;
		case 3:
			displayVideos(videos, currentCount);
			break;
		case 4:
			deleteVideo(videos, currentCount);
			break;
		case 5:
			saveVideos(videos, currentCount);
			break;
		case 6:
			//exit
			exitProgram(termination);
			break;
		default:
			cout << "Invalid choice " << endl;
		}

	}
	delete[] videos; //free up memory 
	return 0;
}

// Function for number validation
void intValidation(int& num) {
	while (true) {
		if (cin >> num) {
			break;
		}else {
			cout << "Input must be a number, try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

// Function for decimal input only
void dblValidation(double& dbl) {
	while (true) {
		if (cin >> dbl) {
			break;
		}else {
			cout << "Input must have a decimal point, try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

// Function to validate string input
void strValidation(string& input) {
	bool validation = false;

	while (true) {
		getline(cin, input);
		for (char c : input) {
			if (!(isalpha(c) || isspace(c))) {
				break;
			}else {
				validation = true;
			}
		}
		if (!validation) {
			cout << "Input must be a string, try again: ";
		}else {
			break;
		}
	}
}

// Function to validate user input (yes/no)
void userValidation(string& input) {
	strValidation(input);
	while (true) {
		if (!(input == "yes" || tolower(input == "YES") || tolower(input == "Yes") || input == "no" || tolower(input == "NO") || tolower(input == "No"))) {
			cout << "Invalid, type only either \"yes\" or \"no\": ";
		}else {
			break;
		}
	}
}

void regAccount() {
	bool usernameSuccess = false, passwordSuccess = false, ageSuccess = false, utypeSuccess = false;
	string regUsername, regPassword, regUtype, regMember;
	int passwordLength = 8, acceptedAge = 20, regAge;
	ofstream usersFile;

	cout << "Enter a username (should have letters): ";
	while (true) {
		cin >> regUsername;
		for (char u : regUsername) {
			if (!isalpha(u)) {
				break;
			}else {
				usernameSuccess = true;
			}
		}
		if (!usernameSuccess) {
			cout << "Username should have letters, please try again: ";
		}else {
			break;
		}
	}

	cout << "Enter a password (must have letters, numbers, symbols, and be at least 8 characters long): ";
	while (true) {
		cin >> regPassword;
		for (char p : regPassword) {
			if (!(isalnum(p) || ispunct(p)) || regPassword.length() < passwordLength) {
				break;
			}else {
				passwordSuccess = true;
			}
		}
		if (!passwordSuccess) {
			cout << "Password is weak, please try again: ";
		}else {
			break;
		}
	}

	cout << "Enter your age (must be 20 years old or above): ";
	while (true) {
		intValidation(regAge);
		if (regAge < acceptedAge) {
			cout << "Age is not accepted, please try again: ";
		}else {
			ageSuccess = true;
			break;
		}
	}

	cout << "Do you work for HJT Video Rental System? (yes/no): ";
	cin.ignore();
	userValidation(regUtype);
	regUtype == "yes" || "YES" || "Yes" ? userType = "Admin" : userType = "User";
	utypeSuccess = true;

	cout << "Do you want to apply for a membership? (yes/no): ";
	userValidation(regMember);

	system("cls");

	if (usernameSuccess && passwordSuccess && ageSuccess && utypeSuccess) {
		cout << "You have successfully registered to the system" << endl;
		usersFile.open("HJT_users.txt", ios::app);
		usersFile << regUsername << "\t\t";
		usersFile << regPassword << "\t\t";
		usersFile << regAge << "\t\t";
		usersFile << regUtype;
		if (regMember == "yes" || tolower(regMember == "YES") || tolower(regMember == "Yes")) {
			usersFile << "\t\tw/Membership";
		}
		usersFile << endl;
		usersFile.close();
	}
}

void loginAccount(int& loginSuccess) {
	string username, password, uname, pass, line;
	const string utype1 = "Admin", utype2 = "User";
	int ast;
	ifstream usersData("HJT_users.txt");

	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	ast = _getch();

	while (ast != 13) { //13 is the ASCII code for enter key
		if (ast == 8) { //8 is the ASCII code for backspace
			if (!password.empty()) {
				password.pop_back();
				cout << "\b \b";
			}
		}else {
			password.push_back(ast);
			cout << '*';
		}
		ast = _getch();
	}

	if (usersData.is_open()) {
		while (usersData >> uname >> pass && getline(usersData, line)) {
			if (uname == username && pass == password) {
				if (line.find(utype1) != string::npos) {
					userType = utype1;
				}else if (line.find(utype2) != string::npos) {
					userType = utype2;
				}
				loginSuccess = 1;
			}
		}
	}else {
		cout << "Error in database" << endl;
		return;
	}

	usersData.close();
	system("cls");

	loginSuccess == 1 ? cout << "You have successfully logged-in to the system" << endl : cout << "Username or Password is incorrect" << endl;
}

void exitProgram(bool& termination) {
	string exit;

	cout << "Are you sure do you want to terminate the program? (yes/no): ";
	cin.ignore();
	userValidation(exit);

	system("cls");

	if (exit == "yes" || tolower(exit == "YES") || tolower(exit == "Yes")) {
		termination = true;
		cout << "Program has been successfully terminated." << endl;
	}
}

void preMenu() {
	bool earlyTermination = false;
	int loginSuccess = 0, accessOption;

	do{
		cout << "\nHJT Video Rental System\n";
		cout << "OPTIONS" << endl;
		cout << "1. Login" << endl;
		cout << "2. Register" << endl;
		cout << "3. Exit" << endl;

		cout << "Enter your option (1-3): ";
		while (true) {
			intValidation(accessOption);
			if (accessOption < 1 || accessOption > 3) {
				cout << "Option should be from 1-3 only, please try again: ";
			}else {
				break;
			}
		}

		system("cls");

		switch (accessOption) {
		case 1:
			loginAccount(loginSuccess);
			break;
		case 2:
			regAccount();
			break;
		case 3:
			exitProgram(earlyTermination);
			if (earlyTermination) {
				exit(0);
			}
			break;
		}
	} while (loginSuccess != 1);
}

void mainMenu() {
	cout << "\nOPTIONS:\n";
	cout << "1.  Add video \n";
	cout << "2.  Update Video \n";
	cout << "3.  Display all the video\n";
	cout << "4.  Delete Video\n";
	cout << "5.  Save the video\n";
	cout << "6.  Exit\n";
}

void addVideo(Video* videos, int& currentCount) {
	//check if we have reach the max number of videos
	//max_count = 100 - max count
	if (currentCount >= MAX_VIDEOS) {
		cout << "MAX video limit reached..." << endl;
		return;
	}
	//input the data
	//int id; string title; bool isAvailable;
	cout << "Enter Video ID: ";
	intValidation(videos[currentCount].id);
	cout << "Enter Video Title: ";
	cin.ignore(); //clear the input buffer
	strValidation(videos[currentCount].title);
	videos[currentCount].isAvailable = true; //always true new
	currentCount++;
	cout << "Video Added successfully " << endl;
}

void updateVideo(Video* videos, int count){
	int id, index = -1;
	cout << "Enter video ID to update: ";
	cin >> id;
	for (int i = 0; i < count; i++) {
		if (videos[i].id == id) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		cout << "Enter new title ";
		cin.ignore();
		getline(cin, videos[index].title);
		cout << "Update available (1 for available 0 for not): ";
		cin >> videos[index].isAvailable;
		cout << "Video Updated " << endl;
	}else {
		cout << "video not found" << endl;
	}

}
void displayVideos(const Video* videos, int count){
	cout << "Display all videos " << endl;
	for (int i = 0; i < count; i++) {
		//int id; string title; bool isAvailable;
		cout << "ID: " << videos[i].id << endl;
		cout << "Title: " << videos[i].title << endl;
		cout << "Available: " << (videos[i].isAvailable ? "YES" : "NO") << endl;
	}
}

void deleteVideo(Video* videos, int& count){
	int id, index = -1;
	cout << "Enter video ID to delete: ";
	cin >> id;
	for (int i = 0; i < count; i++) {
		if (videos[i].id == id) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		for (int j = index; j < count - 1; j++) {
			videos[j] = videos[j + 1];
		}
		count--;
		cout << "Video successfully deleted " << endl;
	}
	else {
		cout << "video not found" << endl;
	}

}

void saveVideos(const Video* videos, int count){
	ofstream outFile("videos.txt");
	if (!outFile) {
		cout << "Error opening the file for writing " << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		outFile << videos[i].id << "\n" << videos[i].title << "\n" << videos[i].isAvailable << endl;
	}
	outFile.close();
	cout << "Video record save successfully. " << endl;
}

void loadVideos(Video* videos, int& count){
	ifstream inFile("videos.txt");
	if (!inFile) {
		cout << "No existing data found. starting fresh... " << endl;
		return;
	}
	Video temp;
	while (inFile >> temp.id) {
		inFile.ignore(); // ignore the newline after the ID
		getline(inFile, temp.title);
		inFile >> temp.isAvailable;
		inFile.ignore(); //newline is ignore 
		if (count < MAX_VIDEOS) {
			videos[count++] = temp;
		}
	}
	inFile.close();
	cout << "Videos loaded successfully.. " << endl;

}
