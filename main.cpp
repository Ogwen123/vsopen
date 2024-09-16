#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <bits/stdc++.h>
using namespace std;

string get_name(string& line) {
    vector<char> buffer = {};

    for (char& c : line) {
        if (c == ',') {
            string str(buffer.begin(), buffer.end()); // converts a vector of chars into a string
            return str;
        } else {
            buffer.push_back(c);
        }
    }
    string str(buffer.begin(), buffer.end());
    return str;
}

vector<string> get_paths(string line) {
    vector<string> paths = {};

    vector<char> buffer = {};
    bool passed_name = false;
    for (char& c : line) {
        if (c == ',') {
            if (!passed_name) {
                passed_name = true;
                buffer = {};
                continue;
            }
            string str(buffer.begin(), buffer.end()); // converts a vector of chars into a string
            paths.push_back(str);
            buffer = {};
        } else {
            buffer.push_back(c);
        }
    }

    return paths;
}

const int MAX_NAME_LENGTH = 20;

int main(int argc, char *argv[]) {
    fstream config_file(R"(C:\Users\Owen\OneDrive\Desktop\vsopen.txt)");
    if (!config_file.is_open()) {
        cout << "Cannot open file!" << endl;
        exit(1);
    }
    if (argc == 2) {
        string line;

        while (getline(config_file, line)){
            cout << line << endl;
            cout << get_name(line) << endl;
            if (get_name(line) != argv[1]) continue;
            vector<string> paths = get_paths(line);
            for (const string& path : paths) {
                const char *command = ("code -g " + path).c_str();
                cout << "running: " << command << endl;
                system(command);
            }
        }

    } else if (argc == 1) {
        cout << "Incorrect number of arguments." << endl;
        exit(2);

    } else {
        if (strcmp(argv[1], "--new") == 0) {
            cout << "here" << endl;
            if (argc < 4) {
                cout << "This flag needs at least 2 args, the name of the profile and at least 1 file path." << endl;
                config_file.close();
                exit(2);
            }

            string name = argv[2];

            if (name.length() > MAX_NAME_LENGTH) {
                cout << "Name is too long. The max length is " << MAX_NAME_LENGTH << "." << endl;
                exit(1);
            }

            if (name.find(',') < name.length()) {
                cout << "You name cannot have commas in it." << endl;
                exit(1);
            }

            string profile = argv[2];
            for (int i = 3; i < argc; i++) {
                profile += ",";
                profile += argv[i];
            }
            config_file << profile << endl;
        } else {
            cout << "Incorrect flag." << endl;
            config_file.close();
            exit(2);
        }
    }
    config_file.close();
}
