#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

const string folder = "SimulatedDrive";

void listFiles() {
    cout << "\n--- Files and Folders ---\n";
    bool found = false;

    for (const auto& entry : fs::directory_iterator(folder)) {
        cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ")
             << entry.path().filename().string() << '\n';
        found = true;
    }

    if (!found) cout << "No files found.\n";
}

void createFile() {
    string name;
    cout << "Enter file name: ";
    getline(cin, name);

    if (name.empty() || name.find_first_of("/\\:") != string::npos ||
        name == "." || name == "..") {
        cout << "Invalid file name.\n";
        return;
    }

    fs::path path = fs::path(folder) / name;

    if (fs::exists(path)) {
        cout << "File already exists.\n";
        return;
    }

    ofstream file(path);
    if (file) cout << "File created successfully.\n";
    else cout << "Could not create file.\n";
}

void readFile() {
    string name, line;
    cout << "Enter file name: ";
    getline(cin, name);

    if (name.empty() || name.find_first_of("/\\:") != string::npos) {
        cout << "Invalid file name.\n";
        return;
    }

    ifstream file(fs::path(folder) / name);
    if (!file) {
        cout << "File not found or cannot be opened.\n";
        return;
    }

    cout << "\n--- File Content ---\n";
    while (getline(file, line)) cout << line << '\n';
}

void appendFile() {
    string name, content;
    cout << "Enter file name: ";
    getline(cin, name);

    if (name.empty() || name.find_first_of("/\\:") != string::npos) {
        cout << "Invalid file name.\n";
        return;
    }

    fs::path path = fs::path(folder) / name;
    if (!fs::is_regular_file(path)) {
        cout << "File does not exist.\n";
        return;
    }

    cout << "Enter text to append: ";
    getline(cin, content);

    ofstream file(path, ios::app);
    if (file) {
        file << content << '\n';
        cout << "Content added successfully.\n";
    } else cout << "Could not write to file.\n";
}

void searchFile() {
    string name;
    cout << "Enter file name to search: ";
    getline(cin, name);

    if (name.empty() || name.find_first_of("/\\:") != string::npos) {
        cout << "Invalid file name.\n";
        return;
    }

    fs::path path = fs::path(folder) / name;
    if (fs::exists(path))
        cout << "Found: " << path.string() << '\n';
    else
        cout << "File not found.\n";
}

void deleteFile() {
    string name;
    cout << "Enter file name to delete: ";
    getline(cin, name);

    if (name.empty() || name.find_first_of("/\\:") != string::npos) {
        cout << "Invalid file name.\n";
        return;
    }

    fs::path path = fs::path(folder) / name;

    if (fs::is_regular_file(path) && fs::remove(path))
        cout << "File deleted successfully.\n";
    else
        cout << "File not found or could not be deleted.\n";
}

int main() {
    try {
        fs::create_directories(folder);

        int choice;
        do {
            cout << "\n===== FILE EXPLORER SIMULATOR =====\n";
            cout << "1. List Files\n";
            cout << "2. Create File\n";
            cout << "3. Read File\n";
            cout << "4. Append to File\n";
            cout << "5. Search File\n";
            cout << "6. Delete File\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            string input;
            getline(cin, input);

            try {
                size_t pos;
                choice = stoi(input, &pos);
                if (pos != input.size()) choice = -1;
            } catch (...) {
                choice = -1;
            }

            switch (choice) {
                case 1: listFiles(); break;
                case 2: createFile(); break;
                case 3: readFile(); break;
                case 4: appendFile(); break;
                case 5: searchFile(); break;
                case 6: deleteFile(); break;
                case 0: cout << "Exiting program...\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 0);
    } catch (const fs::filesystem_error& e) {
        cout << "Filesystem error: " << e.what() << '\n';
    }

    return 0;
}
