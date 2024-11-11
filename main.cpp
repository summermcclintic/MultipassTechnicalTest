#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <vector>
#include <sstream>

using json = nlohmann::json;
using namespace std;

// ImageParser interface
class ImageParser{
    public:
        virtual void getReleases() = 0;
        virtual void getCurrentLTS() = 0;
        virtual void getSha256() = 0;

        // set class json variable
        void set_json(const json jf) {
            _jf = jf;
        }

        // checks to see if a string is in an array of strings
        bool is_in(const vector<string> versions, const string v) const {
            for (int i = 0; i < versions.size(); i++) {
                if (versions[i] == v) {
                    return true;
                }
            }
            return false;
        }

        // prints out options user can select from
        void print_options() const {
            cout << endl;
            cout << "0 - Quit" << endl;
            cout << "1 - Return a list of all currently supported Ubuntu releases" << endl;
            cout << "2 - Return the current Ubuntu LTS version" << endl;
            cout << "3 - Return the sha256 of the disk1.img item of a given Ubuntu release" << endl;
            cout << endl;
            cout << "Enter \"1\", \"2\", or \"3\" for corresponding choice, or \"0\" to quit." << endl;
        }

        // prints a vector with commas and a space seperating each element
        void print(const vector<string> vec) const {
            for (int i = 0; i < vec.size()-1; i++) {
                cout << vec[i] << ", ";
            }
            cout << vec[vec.size()-1] << endl;
        }

    protected:
        json _jf;
};

class UbuntuImageParser : public ImageParser {
    public:
        // method to print out a kist of all currently supported Ubuntu releases
        void getReleases() {
            vector<string> releases;
            for (const auto& item : _jf["products"].items()) {
                if (_jf["products"][item.key()]["supported"]) {
                    releases.push_back(_jf["products"][item.key()]["version"]);
                }
            }
            releases.erase(unique(releases.begin(), releases.end()), releases.end());
            cout << "The currently supported Ubuntu releases are:" << endl;
            print(releases);
        }

        // method to print out the current Ubuntu LTS version
        void getCurrentLTS() {
            string version = "";
            vector<string> aliases;
            for (const auto& item : _jf["products"].items()) {
                string as = _jf["products"][item.key()]["aliases"];
                stringstream ss(as);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    aliases.push_back(substr);
                }
                for (int i = 0; i < aliases.size(); i++) {
                    if (aliases[i] == "lts") {
                        version = _jf["products"][item.key()]["version"];
                    }
                }
                aliases.clear();
            }
            cout << "The current Ubuntu LTS version is " << version << "." << endl;
        }

        // method to print out the sha256 of the disk1.img item of a given Ubuntu release
        void getSha256() {
            vector<string> versions;
            for (const auto& item : _jf["products"].items()) {
                if (_jf["products"][item.key()]["arch"] == "amd64") {
                    versions.push_back(_jf["products"][item.key()]["version"]);
                }
            }
            cout << "Please input which Ubuntu release to find the sha256 of the disk1.img item of. Ubuntu versions are:" << endl;
            print(versions);
            string version = "";
            cin >> version;
            while (!is_in(versions, version)) {
                cout << "Please enter a version that exists." << endl;
                cin >> version;
            }

            vector<string> options;
            vector<string> archs;
            for (const auto& item : _jf["products"].items()) {
                if (_jf["products"][item.key()]["version"] == version) {
                    options.push_back(item.key());
                    archs.push_back(_jf["products"][item.key()]["arch"]);
                }
            }
            int index = 0;
            for (int i = 0; i < archs.size(); i++) {
                if (archs[i] == "amd64") {
                    index = i;
                }
            }

            vector<string> dates;
            for (const auto& item : _jf["products"][options[index]]["versions"].items()) {
                dates.push_back(item.key());
            }

            string date = dates[0];
            if (dates.size() > 1) {
                cout << "Which date would you like to see the sha256 of the disk1.img of?" << endl;
                print(dates);
                cin >> date;
                while (!is_in(dates, date)) {
                    cout << "Please enter a date that exists." << endl;
                    cin >> date;
                }
            }

            cout << endl;
            if (_jf["products"][options[index]]["versions"][date]["items"]["disk1.img"]["sha256"].is_null()) {
                cout << "The sha56 of the disk1.img for Ubuntu version " << version << ", architecture amd64, and date " << date << " does not exist." << endl;
            } else {
                cout << "Here is the sha56 of the disk1.img for Ubuntu version " << version << ", architecture amd64, and date " << date << ":" << endl;
                cout << _jf["products"][options[index]]["versions"][date]["items"]["disk1.img"]["sha256"] << endl;
            }
        }

        // method to ask the user which choice they want, keep asking until the user terminates by entering "0"
        void getChoice() {
            print_options();
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
                            cout << endl;
                            getReleases();
                            print_options();
                            break;
                        case 2:
                            cout << endl;
                            getCurrentLTS();
                            print_options();
                            break;
                        case 3:
                            cout << endl;
                            getSha256();
                            print_options();
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

// Function to handle data received from libcurl and write to string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// Function to fetch JSON data from a URL using libcurl
string fetch_json(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

int main() {
    // get json data from website
    string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    string json_data = fetch_json(url);
    json jf = json::parse(json_data);

    // set up parser of json data
    UbuntuImageParser u;
    u.set_json(jf);
    u.getChoice();

    return 0;
}