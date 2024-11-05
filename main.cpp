#include <iostream>
#include <string>
using namespace std;

void getUbuntuReleases() {
    cout << "1 - Return a list of all currently supported Ubuntu releases" << endl;
}

void getCurrentLTS() {
    cout << "2 - Return the current Ubuntu LTS version" << endl;
}

void getSha256() {
    cout << "3 - Return the sha256 of the disk1.img item of a given Ubuntu release" << endl;
    // ask user input for version, check if valid version
}

void getChoice() {
    cout << "0 - Quit" << endl;
    cout << "1 - Return a list of all currently supported Ubuntu releases" << endl;
    cout << "2 - Return the current Ubuntu LTS version" << endl;
    cout << "3 - Return the sha256 of the disk1.img item of a given Ubuntu release" << endl;
    cout << endl;
    cout << "Enter \"1\", \"2\", or \"3\" for corresponding choice, or \"0\" to quit." << endl;
    int choice = -1;
    while (choice != 0) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter an integer." << endl;
            choice = -1;
        } else {
            switch(choice) {
                case 1:
                    getUbuntuReleases();
                    break;
                case 2:
                    getCurrentLTS();
                    break;
                case 3:
                    getSha256();
                    break;
                case 0:
                    break;
                default:
                    cout << "Please enter a valid integer." << endl;
            }
        }
    }

}

int main() {
    getChoice();
    return 0;
}