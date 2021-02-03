#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<string> permutation(string oper) {
    cout << "log permu" << endl;
    vector<char> a;
    vector<string> result;

    for (int i = 0; i < oper.size(); i++) {
        a.push_back(oper[i]);
    }

    sort(a.begin(), a.end());

    cout << "log permu2" << endl;

    do {
        string temp = "";
        for (int i = 0; i < a.size(); i++) {
            temp += a[i];
            //cout << a[i]<<" ";
        }
        result.push_back(temp);
       // printf("\n");
    } while (next_permutation(a.begin(), a.end()));

    return result;
}

//priority_queue�� ����ϱ� ���� ����ü
struct oper {
    char op;
    int idx;
};

//Expression�� �����ڰ� � ����ִ��� ����, ������ �켱������ string vector�� return
vector<string> getPriorSet(string expression) {
    cout << "log1" << endl;
    vector<string> operPriorSet;

    string oper="";
    bool hasPlus = false;
    bool hasMinus = false;
    bool hasMultiple = false;
        
    cout << "size : " << expression.size() << endl;

    // � �����ڵ��� ����ִ��� Ȯ��
    for (int i = 0; i<expression.size(); i++) {
        if (expression[i] == '+' && !hasPlus) {
            hasPlus = true;
            oper += expression[i];
        }
        else if (expression[i] == '-' && !hasMinus) {
            hasMinus = true;
            oper += expression[i];
        }
        else if (expression[i] == '*' && !hasMultiple) {
            hasMultiple = true;
            oper += expression[i];
        }
    }
    
    cout << "oper : " << oper << endl;

    operPriorSet = permutation(oper);

    cout << "operPriorSet : ";
    for (int i = 0; i < operPriorSet.size(); i++) {
        cout << operPriorSet[i] << " ";
    }
    cout << endl;
    return operPriorSet;
}

bool isOper(char c) {
    if (c == '+' || c == '-' || c == '*') return true;
    else return false;
}




long long solution(string expression) {
    long long answer = 0;

    vector<string> caseSet;

    //���ü� �ִ� �켱 ���� ���յ�, ex {+-*},{+*-}, .... n!���� ����.
    vector<string> stringOperPriorSet;
    
    //���Ŀ��� �����ڵ鸸 �̾Ƴ���, ���� �� �ִ� �켱���� ���յ��� ���� ����
    stringOperPriorSet = getPriorSet(expression);

    //������ �켱������ ���� ����� �̱�. ����� n!���� ����
    for(int i=0;i<stringOperPriorSet.size();i++){

        //i ��° ���ҿ��� int �� �켱������ �ű� (idx)
        vector<oper> operOperPriorSet;

        //i��° operPriorSet
        for (int j = 0; j < stringOperPriorSet[i].size(); j++) {
            char c = stringOperPriorSet[i][j];
            oper o = { c,j };
            operOperPriorSet.push_back(o);
            //oper(+,0) oper(-,1) .. �̷������� ���
        }

        //���� �װɷ� ť�� �켱���� ť Ȱ��

        //�켱������ ���ϴ� �Լ�(��������)
        struct cmp {
            bool operator()(char c1, char c2)//oper�� idx�� Ȱ���� ��� ��
            {
            }
        };

        queue<int> q;   //���ڸ� ���� ť
        priority_queue<char,vector<char>,cmp> pq;    //�����ڸ� ���� �켱���� ť    

        //������ ���鼭 ���ڸ� ť��, �����ڸ� �켱���� ť�� ��´�.
        for (int i = 0; i < expression.size(); i++) {
            if (isOper(expression[i])) {//�����ڶ��
                pq.push(expression[i]);
            }
            else {//���ڶ��
                int num = expression[i] - '0';
                q.push(num);
            }
        }

        //(��������)����, ���ڿ� �����ڸ� ť���� ������� ������, ����� ���Ѵ�.


    }


    return answer;
}

int main() {
    string s = "100-200*300-500+20";
    vector<string> v = getPriorSet(s);

    return 0;
}