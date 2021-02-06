#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

const char SLASH = '/';
const std::string DOT_SLASH = "./";
const std::string DOT_DOT_SLASH = "../";

namespace fs = std::filesystem;
using namespace std;


/* Replaces all instances of a certain character within a string */
string ReplaceAllSlashes(string str) {

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\\') {
            str.replace(i, 1, "/");
        }
    }

    return str;

}


/* Intention of this function is to take a path(in the form of a string) and separate it into its
component commands.*/
vector<string> SplitPath(string str) {

    // path_elements holds the commands contained in the path
    vector<string> path_elements = vector<string>();

    int i = 0;

    for (int ii = 0; ii < str.length(); ii++) {
        if (str[ii] == SLASH || ii == str.length() - 1) {
            path_elements.push_back(str.substr(i, ii - i + 1));
            i = ii + 1;
        }
    }
    return path_elements;

}


/* SanitizePath takes all of the commands from path_elements and applies them to the current working
directory. It then returns the "clean" path that does not include any special commands. */
string SanitizePath(vector<string> path_elements) {

    /* In the interest of usability, all backslashes are to be replaced by forward slashes*/
    string clean_string = ReplaceAllSlashes(filesystem::current_path().string());
    clean_string.push_back(SLASH);

    // If the first character of the command is a slash, it starts the path from root.
    if (path_elements[0][0] == SLASH) {
        clean_string.erase(3, clean_string.size() - 1);
        path_elements.erase(path_elements.begin());
    }

    // This loop is designed to iterate through the various commands
    for (int i = 0; i < path_elements.size(); i++) {

        // Two dots and then a slash refers to going back to the parent directory.
        if (path_elements[i] == DOT_DOT_SLASH) {
            // This removes everything after the second-to-last slash
            clean_string.erase(clean_string.find_last_of(SLASH), clean_string.size() - 1);
            clean_string.erase(clean_string.find_last_of(SLASH) + 1, clean_string.size() - 1);
        }
        // A single dot and then a slash refers to the current directory. Do nothing.
        else if (path_elements[i] == DOT_SLASH) {

        }
        // Otherwise, add the current command to the path.
        else {
            clean_string.append(path_elements[i]);
        }
    }

    // The end result is a "sanitized" path.
    cout << clean_string << endl;
    return clean_string;

}


bool ComparePaths(string first_path, string second_path) {

    /* In the interest of usability, all backslashes are to be replaced by forward slashes */
    first_path = ReplaceAllSlashes(first_path);
    second_path = ReplaceAllSlashes(second_path);

    if (SanitizePath(SplitPath(first_path)) == SanitizePath(SplitPath(second_path))) {
        return true;
    }
    return false;

}


int main()
{

    string first_path;
    string second_path;

    cout << "Enter the first filepath: ";
    cin >> first_path;
    cout << "Enter the second filepath: ";
    cin >> second_path;

    if (ComparePaths(first_path, second_path)) {
        cout << "The filepaths are homographs";
    }
    else {
        cout << "The filepaths are not homographs";
    }

}