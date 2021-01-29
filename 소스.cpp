#include <iostream>
#include <string>
#include <vector>

//���� !! vec.begin()+i �� Ȱ���ؾ� �Ѵٴ� ��, string�� ���������� null�� �����ִٴ� �� 

using namespace std;

string step1(string input) {
    string result = "";

    for (int i = 0; i < input.size(); i++) {
        input[i] = tolower(input[i]);
    }

    result = input;

    cout << "step1 : " << input << endl;

    return result;
}

bool step2check(char c) {
    if (
        ('a' <= c && c <= 'z')
        || ('0' <= c && c <= '9')
        || c == '-' || c == '_' || c == '.'
        )
    {
        return true;
    }
    else return false;
}

string step2(string input) {
    string result = "";

    for (int i = 0; i < input.size(); i++) {
        if (step2check(input[i])) {
            result += input[i];
        }
    }

    cout << "step2 : " << result << endl;

    return result;
}


string step3(string input) {    //���ӵ� ��ħǥ ����
    string result = "";
    // ���� ������ ���� vector�� string ���
    vector<char> vec;
    for (int i = 0; i < input.size(); i++) {
        vec.push_back(input[i]); 
    }
    bool isPeriod = false;
    for (int i = 0; i < vec.size(); i++) {
        if (isPeriod == true)//���� ���Ұ� period �� ��
        {
            if (vec[i] == '.')//���� ���Ұ� period
            {
                isPeriod = true;
                vec.erase(vec.begin() + i);
                i = i - 1;  //vec�� �������Ƿ� �� ĭ �ڷ� ������
            }
            else {//���� ���Ұ� period �ƴ�
                isPeriod = false;
            }
        }
        else {//���� ���Ұ� period �ƴ� ��
            if (vec[i] == '.')//���� ���Ұ� period
            {
                isPeriod = true;
            }
            else {//���� ���Ұ� period �ƴ�
                isPeriod = false;
            }
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        result += vec[i];
    }
    cout << "step3 : " << result << endl;
    return result;
}

string step4(string input) { // ��ħǥ�� ó���̳� ���� ��ġ�Ѵٸ� ����
    string result = "";

    // ���� ������ ���� vector�� string ���
    vector<char> vec;
    for (int i = 0; i < input.size(); i++) {
        vec.push_back(input[i]);
    }

    if (vec.front() == '.') {
        vec.erase(vec.begin());
    }

    if (vec.back() == '.') {
        vec.pop_back();
    }

    for (int i = 0; i < vec.size(); i++) {
        result += vec[i];
    }

    cout << "step4 : " << result << endl;

    return result;
}

string step5(string input) { // �� ���ڿ��̶�� 'a' �߰�
    string result = "";

    if (input.size() == 0) {
        result += 'a';
    }
    else {
        result = input;
    }

    cout << "step5 : " << result << endl;

    return result;
}

string step6(string input) { //���̰� 16�� �̻��̸�, new_id�� ù 15���� ���ڸ� ������ ������ ���ڵ��� ��� �����մϴ�.
    //���� ���� �� ��ħǥ(.)�� new_id�� ���� ��ġ�Ѵٸ� ���� ��ġ�� ��ħǥ(.) ���ڸ� �����մϴ�.
    string result = "";

    vector<char> vec;
   
   
    if (input.size() >= 16) {
        for (int i = 0; i < 15; i++) {
            cout << i<<" : "<<input[i];
            vec.insert(vec.begin() + i, input[i]);
        }
    }
    else {
        for (int i = 0; i < input.size(); i++) {
            vec.push_back(input[i]);
        }
    }
    
    if (vec.back() == '.') {
        vec.pop_back();
    }

    for (int i = 0; i < vec.size(); i++) {
        result += vec[i];
    }

    cout << "step6 : " << result << endl;
    

    return result;
}

//���̰� 2�� ���϶��, new_id�� ������ ���ڸ� new_id�� ���̰� 3�� �� ������ �ݺ��ؼ� ���� ���Դϴ�.
string step7(string input) {
    string result = "";

    if (input.size() <= 2) {
        //���� ! string �� �������� null�� �ֱ� ������ -1�� ����� �Ѵ�.
        char back = input[input.size()-1];
        cout << "back : " << back;
        while (input.size() != 3) {
            input += back;
        }
    }

    result = input;

    cout << "step7 : " << result << endl;

    return result;
}

string solution(string new_id) {
    string answer = "";

    answer = step7(step6(step5(step4(step3(step2(step1(new_id)))))));

    return answer;
}

int main() {
    string input = "z-+.^.";

    cout << "input : " << input << endl;

    cout << "result : " << solution(input) << endl;

    return 0;
}
