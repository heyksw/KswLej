//https://programmers.co.kr/learn/courses/30/parts/12421
//DFS,BFS�� �����ϱ� ���� ������ ����. 
//���α׷��ӽ� �ڵ��׽�Ʈ ���� > ����/�ʺ� �켱 Ž��(DFS/BFS) > �ܾ� ��ȯ
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// �� string�� �� ���� �������� �����ϴ� �Լ�. isSimular�� true�̸� �׷����� ������ �ߴ´�.
bool isSimular(string a, string b) {
    int cnt = 0;    //���� �� ���ڰ� �ٸ���
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
            if (isSimular(input[i], input[j])) {    //�� ���� ���̶�� ���� �߰�
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