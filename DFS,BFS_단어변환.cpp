//https://programmers.co.kr/learn/courses/30/parts/12421
//DFS,BFS를 공부하기 위해 선택한 문제. 
//프로그래머스 코딩테스트 연습 > 깊이/너비 우선 탐색(DFS/BFS) > 단어 변환
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 두 string이 한 글자 차이인지 결정하는 함수. isSimular가 true이면 그래프에 간선을 긋는다.
bool isSimular(string a, string b) {
    int cnt = 0;    //서로 몇 글자가 다른지
    if (a.size() != b.size()) return false;
    else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) cnt++;
        }
    }
    if (cnt == 1) return true;
    else return false;
}

void makeGraph(vector<string> input) {
    int size = input.size();
    int** a=0;
    
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            if (isSimular(input[i], input[j])) {    //한 글자 차이라면 간선 추가
                a[i][j] = 1;
            }
            else a[i][j] = 0;
        }
    }

    cout << "makeGraph : " << endl;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;

    return answer;
}

int main() {
    string a = "aef";
    string b = "abd";
    cout << isSimular(a, b) << endl;

    vector<string> s = { "ab","ac","cd" };
    makeGraph(s);

    return 0;
}