#include <iostream>
#include <string>
#include <vector>

using namespace std;


string toLowerCase(string str) {
    string tmp = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
        tmp.push_back(str[i]);
    }
    return tmp;
}

string removeUnallowed(string str) {
    string tmp = "";
    for(int i = 0; i < str.length(); i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= '0' && str[i] <= '9') ||
            str[i] == '-' ||
            str[i] == '_' ||
            str[i] == '.')
            tmp.push_back(str[i]);
    }
    return tmp;
}

string removeContinuousPeriod(string str) {
    string tmp = "";
    bool isPeriod = false;
    for(int i = 0; i < str.length(); i++) {
        if(!isPeriod){
            if(str[i] == '.')
                isPeriod = true;
            tmp.push_back(str[i]);
        }
        else if(str[i] != '.') {
            isPeriod = false;
            tmp.push_back(str[i]);
        }
    }
    return tmp;
}

string removeFirstLastPeriod(string str) {
    if(str.length() == 0)   return str;
    if(str[0] == '.') {
        str = str.substr(1, str.length() - 1);
    }
    if(str[str.length() - 1] == '.') {
        str = str.substr(0, str.length() - 1);
    }
    return str;
}

string fillWithA(string str) {
    if(str.length() == 0) return "a";
    return str;
}

string cutTheString(string str) {
    if(str.length() > 15) {
        if(str[14] == '.')  str = str.substr(0, 14);
        else str = str.substr(0, 15);
    }
    return str;
}

string supplementString(string str) {
    while(str.length() < 3) {
        str.push_back(str[str.length() - 1]);
    }
    return str;
}


string solution(string new_id) {
    string answer = "";
    new_id = toLowerCase(new_id);
    new_id = removeUnallowed(new_id);
    new_id = removeContinuousPeriod(new_id);
    new_id = removeFirstLastPeriod(new_id);
    new_id = fillWithA(new_id);
    new_id = cutTheString(new_id);
    new_id = supplementString(new_id);
    answer = new_id;

    return answer;
}

int main() {
    string new_id;
    cin >> new_id;
    new_id = solution(new_id);
    cout << new_id << endl;

    return 0;
}
