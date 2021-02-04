// ������ : �� ������ ���ϴ� priority queue ������� ����

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

//�����ڸ� true ���ڸ� false return
bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*') return true;
    else return false;
}

int Factorial(int n) {

    int result = 1;

    for (int i = 1; i <= n; ++i)
        result *= i;

    return result;
}

//�켱���� ť�� ����ϱ� ���� class
class Compare {
public:
    string priority = "";
    Compare(string priority) {
        this->priority = priority;
    }
    bool operator()(char c1, char c2) {
        int idx1=0;
        int idx2=0;
        // string���� �� �տ��ִ� ���� �켱���� ����
        for (int i = 0; i < this->priority.size(); i++) {
            if (c1 == priority[i]) idx1 = i;
            if (c2 == priority[i]) idx2 = i;

            return idx1 > idx2;
        }
    }
};

long long solution(string expression) {
    long long answer = 0;
    queue<int> q;   //�ǿ����ڸ� ���� ť
    priority_queue<char,Compare> pq;    //�����ڸ� ���� ť
    long long result = 0;   //����� ���� ����


    //������ ť�� �켱���� ť�� �з��ϱ�
    string stringNum = "";
    int num = 0;
    for (int i = 0; i < expression.size(); i++) {                 
        if (!isOperator(expression[i])) {   //���ڸ�           
            stringNum += expression[i];
        }
        else {//�����ڸ�           
            stringstream ssInt(stringNum);
            ssInt >> num;   //���ⲯ ���� stringNum�� int������ �ٲ㼭 num�� �ֱ�
            q.push(num);    //�׸��� num�� ť�� push
            stringNum = ""; //�׸��� stringNum, num �ʱ�ȭ
            num = 0;
            cout << "������ " << expression[i] << "�� �켱���� ť�� push �մϴ�." << endl;
            pq.push(expression[i]); //�켱���� ť�� ������ push
        }    
    }

    cout << "ť : ";
    while (!q.empty()) {
        int temp = q.front();
        cout << temp << " ";
        q.pop();
    }

    //�켱���� ť �ȿ� �� ������ �����ڰ� ����ִ��� ���ϱ�
    vector<char> operSet;
    bool hasPlus = false;
    bool hasMinus = false;
    bool hasMultiple = false;
    int cnt = 0;    //�����ڰ� �� ���� �ִ���
    cout << "�켱���� ť : ";
    while (!pq.empty()) {
        char temp = pq.top();
        cout << temp << " ";
        if (temp == '+' && hasPlus == false) {
            hasPlus = true;
            cnt++;
            operSet.push_back('+');
        }
        if (temp == '-' && hasMinus == false) {
            hasMinus = true;
            cnt++;
            operSet.push_back('-');
        }
        if (temp == '*' && hasMultiple == false) {
            hasMultiple = true;
            cnt++;
            operSet.push_back('*');
        }
        pq.pop();
    }
    cout << endl;
    cout << "�켱���� ť���� " << cnt << "������ �����ڰ� ����ֽ��ϴ�." << endl;
    
    
    //�켱������ string������ ���� ����. "+-*", "+*-" , ...
    vector<string> priority;

    //operSet�� ���� ���ϱ�

    //0�� 1�� ������ ���� ����
    vector<int> ind;

    for (int i = 0; i < cnt; i++) {
        ind.push_back(1);
    }

    for (int i = 0; i < operSet.size() - cnt; i++) {
        ind.push_back(0);
    }

    sort(ind.begin(), ind.end());

    do {
        string temp = "";
        // ���
        for (int i = 0; i < ind.size(); i++) {            
            if (ind[i] == 1) {
                cout<<operSet[i]<<" ";
                temp += operSet[i];
            }
        }
        priority.push_back(temp);
        cout << endl;

    } while (next_permutation(ind.begin(), ind.end()));

    long long result = 0;
    int priorityCaseNum = Factorial(cnt);    //n!���� �켱���� ���̽�
    for (int i = 0; i < priorityCaseNum; i++) {
        //����� ���� result���� ũ�� result�� ���� ��Ŵ
        char tempOper = pq.pop();



    }



    return answer;
}

int main() {
    string ex = "100-200*300-500+20";

    int result = solution(ex);

    cout << "��� : " << result << endl;

    return 0;
}