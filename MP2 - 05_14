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
	double price;
	bool isAvailable;

	Video() : id(0), title(""), price(0.0), isAvailable(false) {}
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
void rentVideos(Video* videos, int count);
void saveVideos(const Video* videos, int count);
void loadVideos(Video* videos, int& count);
void searchVideos(const Video* videos, int count);

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
		intValidation(choice);

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
			searchVideos(videos, currentCount);
			break;
		case 7:
			//exit
			exitProgram(termination);
			break;
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
		if (!(input == "yes" || tolower(input == "YES") || tolower(input == "Yes") || input == "no" || tolower(input == "NO") || tolower(input == "No")) || input == "") {
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
		cout << "HJT Video Rental System\n";
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
	cout << "OPTIONS:\n";
	cout << "1.  Add video \n";
	cout << "2.  Update Video \n";
	cout << "3.  Display all the video\n";
	cout << "4.  Delete Video\n";
	cout << "5.  Save the video\n";
	cout << "6.  Search a video\n";
	cout << "7.  Exit\n";
}

void addVideo(Video* videos, int& currentCount) {
	if (userType == "User") {
		cout << "Sorry, but only admins can add videos. Press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}

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
	cout << "Enter Video Price: ";
	dblValidation(videos[currentCount].price);
	videos[currentCount].isAvailable = true; //always true new
	currentCount++;
	cout << "Video added successfully, press enter to continue...";
	cin.ignore();
	cin.get();
	system("cls");
	return;
}

void updateVideo(Video* videos, int count){
	int id, index = -1;
	string updateConfirm;

	if (userType == "User") {
		cout << "Sorry, but only admins can update videos. Press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}

	cout << "Enter video ID to update: ";
	intValidation(id);
	for (int i = 0; i < count; i++) {
		if (videos[i].id == id) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		cout << "Are you sure do you want to update the video \"" << videos[index].title << "\"? (yes/no): ";
		userValidation(updateConfirm);
		if (updateConfirm == "no" || tolower(updateConfirm == "NO") || tolower(updateConfirm == "No")) {
			return;
		}

		cout << "Enter new title ";
		cin.ignore();
		getline(cin, videos[index].title);
		cout << "Video updated successfully, press enter to continue...";
		cin.get();
		system("cls");
		return;
	}else {
		cout << "Video is not found, press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}

}
void displayVideos(const Video* videos, int count){
	if (count == 0) {
		cout << "No videos are saved as of the moment, press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}

	cout << "Display all videos " << endl;
	//cout << "ID\t\tTitle\t\tPrice\t\tAvailability" << endl;
	for (int i = 0; i < count; i++) {	
		//int id; string title; bool isAvailable;
		cout << videos[i].id << "\t\t";
		cout << videos[i].title << "\t\t";
		cout << videos[i].price << "\t\t";
		cout << (videos[i].isAvailable ? "Available" : "Rented") << endl;
	}

	cout << "Press enter to continue...";
	cin.ignore();
	cin.get();
	system("cls");
	return;
}

void deleteVideo(Video* videos, int& count){
	int id, index = -1;
	string deleteConfirm;

	if (userType == "User") {
		cout << "Sorry, but only admins can delete videos. Press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}

	cout << "Enter video ID to delete: ";
	intValidation(id);
	for (int i = 0; i < count; i++) {
		if (videos[i].id == id) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		cout << "Are you sure do you want to delete the video \"" << videos[index].title << "\"? (yes/no): ";
		userValidation(deleteConfirm);
		if (deleteConfirm == "no" || tolower(deleteConfirm == "NO") || tolower(deleteConfirm == "No")) {
			return;
		}

		for (int j = index; j < count - 1; j++) {
			videos[j] = videos[j + 1];
		}
		count--;

		cout << "Video deleted successfully, press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}else {
		cout << "Video is not found, press enter to continue...";
		cin.ignore();
		cin.get();
		system("cls");
		return;
	}
}

void rentVideos(Video* videos, int count) {
	int index = -1;
	string videoRent, rentConfirm, rentContinue;

	do {
		cout << "Enter video to rent: ";
		strValidation(videoRent);

		for (int i = 0; i < count; i++) {
			if (videos[i].title == videoRent) {
				index = i;
				break;
			}
		}

		if (index == -1) {
			cout << "Video is not found, press enter to continue...";
			cin.get();
			system("cls");
			return;
		}

		cout << "Are you sure do you want to rent the video \"" << videos[index].title << "\" which costs P" << videos[index].price << "? (yes/no): ";
		userValidation(rentConfirm);

		if (rentConfirm == "yes" || tolower(rentConfirm == "YES") || tolower(rentConfirm == "Yes")) {
			videos[index].isAvailable = false;
			cout << "The video \"" << videos[index].title << "\" (P" << videos[index].price << ") has now been rented." << endl;
		}

		cout << "Do you want to rent more videos? (yes/no): ";
		userValidation(rentContinue);

		system("cls");
	} while (rentContinue == "yes" || tolower(rentContinue == "YES") || tolower(rentContinue == "Yes"));
}

void saveVideos(const Video* videos, int count){
	string saveConfirm;
	ofstream outFile("videos.txt");

	cout << "Are you sure do you want to save the video/s? (yes/no): ";
	cin.ignore();
	userValidation(saveConfirm);
	if (saveConfirm == "no" || tolower(saveConfirm == "NO") || tolower(saveConfirm == "No")) {
		return;
	}

	if (!outFile.is_open()) {
		cout << "Error opening the file for writing " << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		outFile << videos[i].id << "\t\t" << videos[i].title << "\t\t" << videos[i].price << "\t\t" << (videos[i].isAvailable ? "Available" : "Rented") << endl;
	}
	outFile.close();
	cout << "Video record save successfully. Press enter to continue...";
	cin.get();
	system("cls");
	return;
}

void loadVideos(Video* videos, int& count){
	ifstream inFile("videos.txt");
	if (!inFile) {
		cout << "No existing data found. starting fresh... " << endl << endl;
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
	cout << "Videos loaded successfully.. " << endl << endl;
}

void searchVideos(const Video* videos, int count) {
	string videoSearch, searchConfirm;
	int searchIndex, stoiVid;
	bool videoFound = false;

	do {
		cout << "You are searching for? (Title/Price): ";
		cin.ignore();
		getline(cin, videoSearch);

		for (char n : videoSearch) {
			if (isdigit(n)) {
				stoiVid = stoi(videoSearch);
			}
		}
	
		for (int i = 0; i < count; i++) {
			if (videos[i].title == videoSearch || videos[i].price == stoiVid) {
				videoFound = true;
				searchIndex = i;
				break;
			}
		}

		if (videoFound) {
			cout << "Here are the result/s of what you are looking for: " << endl;
			cout << videos[searchIndex].id << "\t\t" << videos[searchIndex].title << "\t\t" << videos[searchIndex].price << "\t\t" << (videos[searchIndex].isAvailable ? "Available" : "Rented") << endl;
		}
		else {
			cout << "Video is not found. Press enter to continue...";
			cin.ignore();
			cin.get();
			system("cls");
			return;
		}

		cout << "Do you want to search for other videos? (yes/no): ";
		userValidation(searchConfirm);

		system("cls");
	} while (searchConfirm == "yes" || tolower(searchConfirm == "YES") || tolower(searchConfirm == "Yes"));
}
