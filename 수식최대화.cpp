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

//priority_queue를 사용하기 위한 구조체
struct oper {
    char op;
    int idx;
};

//Expression에 연산자가 몇개 들어있는지 세고, 연산자 우선순위를 string vector로 return
vector<string> getPriorSet(string expression) {
    cout << "log1" << endl;
    vector<string> operPriorSet;

    string oper="";
    bool hasPlus = false;
    bool hasMinus = false;
    bool hasMultiple = false;
        
    cout << "size : " << expression.size() << endl;

    // 어떤 연산자들이 들어있는지 확인
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

    //나올수 있는 우선 순위 조합들, ex {+-*},{+*-}, .... n!개가 나옴.
    vector<string> stringOperPriorSet;
    
    //수식에서 연산자들만 뽑아내서, 나올 수 있는 우선순위 조합들을 담은 벡터
    stringOperPriorSet = getPriorSet(expression);

    //연산자 우선순위에 따른 결과들 뽑기. 결과는 n!개가 나옴
    for(int i=0;i<stringOperPriorSet.size();i++){

        //i 번째 원소에서 int 형 우선순위를 매김 (idx)
        vector<oper> operOperPriorSet;

        //i번째 operPriorSet
        for (int j = 0; j < stringOperPriorSet[i].size(); j++) {
            char c = stringOperPriorSet[i][j];
            oper o = { c,j };
            operOperPriorSet.push_back(o);
            //oper(+,0) oper(-,1) .. 이런식으로 담김
        }

        //이제 그걸로 큐와 우선순위 큐 활용

        //우선순위를 정하는 함수(아직안함)
        struct cmp {
            bool operator()(char c1, char c2)//oper의 idx를 활용한 대소 비교
            {
            }
        };

        queue<int> q;   //숫자를 담을 큐
        priority_queue<char,vector<char>,cmp> pq;    //연산자를 담을 우선순위 큐    

        //수식을 보면서 숫자면 큐에, 연산자면 우선순위 큐에 담는다.
        for (int i = 0; i < expression.size(); i++) {
            if (isOper(expression[i])) {//연산자라면
                pq.push(expression[i]);
            }
            else {//숫자라면
                int num = expression[i] - '0';
                q.push(num);
            }
        }

        //(아직안함)그후, 숫자와 연산자를 큐에서 순서대로 꺼내고, 결과를 구한다.


    }


    return answer;
}

int main() {
    string s = "100-200*300-500+20";
    vector<string> v = getPriorSet(s);

    return 0;
}