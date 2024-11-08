#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
using namespace std;

class ImageParser{
    public:
        virtual void getReleases() = 0;
        virtual void getCurrentLTS() = 0;
        virtual void getSha256() = 0;
        void set_json(json jf) {
            _jf = jf;
        }
        void print(vector<string> vec) {
            for (int i = 0; i < vec.size(); i++) {
                cout << vec[i] << endl;
            }
        }

    protected:
        json _jf;
};

class UbuntuImageParser : public ImageParser {
    public:
        // add consts and header comments
        void getReleases() {
            vector<string> releases;
            for (const auto& item : _jf["products"].items()) {
                if (_jf["products"][item.key()]["supported"]) {
                    releases.push_back(_jf["products"][item.key()]["version"]);
                }
            }
            releases.erase( unique( releases.begin(), releases.end() ), releases.end() );
            cout << "The currently supported Ubuntu releases are:" << endl;
            print(releases);
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
                            getReleases();
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
};

int main() {
    // get json data from website
    // https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json
    std::ifstream f("download.json");
    json jf = json::parse(f);

    // cout << jf["products"] << endl;

    UbuntuImageParser u;
    u.set_json(jf);
    u.getReleases();
    // u.getChoice();

    return 0;
}