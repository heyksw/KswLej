// 느낀점 : 잘 쓰지도 못하는 priority queue 사용하지 말자

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

//연산자면 true 숫자면 false return
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

//우선순위 큐를 사용하기 위한 class
class Compare {
public:
    string priority = "";
    Compare(string priority) {
        this->priority = priority;
    }
    bool operator()(char c1, char c2) {
        int idx1=0;
        int idx2=0;
        // string에서 더 앞에있는 것이 우선순위 높음
        for (int i = 0; i < this->priority.size(); i++) {
            if (c1 == priority[i]) idx1 = i;
            if (c2 == priority[i]) idx2 = i;

            return idx1 > idx2;
        }
    }
};

long long solution(string expression) {
    long long answer = 0;
    queue<int> q;   //피연산자를 담을 큐
    priority_queue<char,Compare> pq;    //연산자를 담을 큐
    long long result = 0;   //결과를 담을 변수


    //수식을 큐와 우선순위 큐에 분류하기
    string stringNum = "";
    int num = 0;
    for (int i = 0; i < expression.size(); i++) {                 
        if (!isOperator(expression[i])) {   //숫자면           
            stringNum += expression[i];
        }
        else {//연산자면           
            stringstream ssInt(stringNum);
            ssInt >> num;   //여기껏 쌓인 stringNum을 int형으로 바꿔서 num에 넣기
            q.push(num);    //그리고 num을 큐에 push
            stringNum = ""; //그리고 stringNum, num 초기화
            num = 0;
            cout << "연산자 " << expression[i] << "를 우선순위 큐에 push 합니다." << endl;
            pq.push(expression[i]); //우선순위 큐에 연산자 push
        }    
    }

    cout << "큐 : ";
    while (!q.empty()) {
        int temp = q.front();
        cout << temp << " ";
        q.pop();
    }

    //우선순위 큐 안에 몇 가지의 연산자가 들어있는지 구하기
    vector<char> operSet;
    bool hasPlus = false;
    bool hasMinus = false;
    bool hasMultiple = false;
    int cnt = 0;    //연산자가 몇 가지 있는지
    cout << "우선순위 큐 : ";
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
    cout << "우선순위 큐에는 " << cnt << "가지의 연산자가 들어있습니다." << endl;
    
    
    //우선순위를 string형으로 담을 벡터. "+-*", "+*-" , ...
    vector<string> priority;

    //operSet의 조합 구하기

    //0과 1을 저장할 벡터 생성
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
        // 출력
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
    int priorityCaseNum = Factorial(cnt);    //n!개의 우선순위 케이스
    for (int i = 0; i < priorityCaseNum; i++) {
        //결과를 내고 result보다 크면 result로 갱신 시킴
        char tempOper = pq.pop();



    }



    return answer;
}

int main() {
    string ex = "100-200*300-500+20";

    int result = solution(ex);

    cout << "결과 : " << result << endl;

    return 0;
}