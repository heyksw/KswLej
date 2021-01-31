/*
단, 코스요리 메뉴는 최소 2가지 이상의 단품메뉴로 구성하려고 합니다. 
또한, 최소 2명 이상의 손님으로부터 주문된 단품메뉴 조합에 대해서만 코스요리 메뉴 후보에 포함하기로 했습니다.

각 손님들이 주문한 단품메뉴들이 문자열 형식으로 담긴 배열 orders,
스카피가 추가하고 싶어하는 코스요리를 구성하는 단품메뉴들의 갯수가 담긴 배열 course가 매개변수로 주어질 때,
스카피가 새로 추가하게 될 코스요리의 메뉴 구성을 문자열 형태로 배열에 담아 return 하도록 solution 함수를 완성해 주세요.

(풀이)
1번 손님의 2개 조합 {a,b} {a,c}
2번 손님의 2개 조합 {c,d}

... 모든 손님의 2개 조합에서 2개 이상 겹치는게 있는지 판단.

있다면 결과 answer vector에 삽입.

3개 조합에 대해서도 실행. 몇 개에 대해서 실행해 봐야하는지는 course에 주어짐.

 + 고려해야할것
 ACF ACDE ACDEH 가 있다면
 answer vector에 AC (o) ACE(x) ACDE(o)인 상황을 연출해야 한다.
 -> ACE가 출현한 index에 ACDE도 항상 있다면 ACE를 삭제.

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// orders의 index를 지정하기 위해 구조체 도입. arrange함수에서 필요.
struct key {
    int idx;
    string str;
};

// answer에 담기위한 string을 담는 구조체
struct ans {
    string str; //ex AC
    string idx; //ex "35"
    int cnt;    //total에서 몇번 등장하는지
};

// 내림차순을 위한 함수
bool desc(char a, char b) {
    return a > b;
}

// n번 string에서 r개를 뽑아 조합. next_permutation 메서드 활용 (include algorithm)
vector<string> combination(string input, int r) {  
    vector<char> idx;
    vector<string> result;
    for (int i = 0; i < input.size(); i++) {
        idx.push_back(input[i]);
    }

    // 0과1을 저장 할 벡터 생성
    vector<char> ind;
    // 1추가
    for (int i = 0; i < r; i++) {
        ind.push_back('1');
    }
    // 0추가
    for (int i = 0; i < idx.size() - r; i++) {
        ind.push_back('0');
    }
    sort(ind.begin(), ind.end());   //정렬
    //순열
    do {
        // 출력
        string s = "";
        for (int i = 0; i < ind.size(); i++) {
            if (ind[i] == '1') {
               // cout << idx[i]<<" ";
                s += idx[i];
            }
        }

        result.push_back(s);
       // cout << endl;

    } while (next_permutation(ind.begin(), ind.end()));

    sort(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++) {
       // cout<< result[i] << " ";
    }

    return result;
}

// input의 중복 원소를 제거해주는 함수.standard를 뽑기위함. (include algorithm) unique, erase 사용
vector<string> deduplication(vector<string> s)
{
    vector<string> output;
    //정렬
    sort(s.begin(), s.end());
    //중복 제거
    s.erase(unique(s.begin(), s.end()), s.end());
    for (int i = 0; i < s.size(); i++) {
        output.push_back(s[i]);
    }

    return output;
}

//XW랑 WX를 같게 보기위한 함수 -> char형 배열에 담아놓고 구성 원소가 같은지 판단한다.
bool isSame(string a, string b) {
    vector<char> vecA;
    vector<char> vecB;
    for (int i = 0; i < a.size(); i++) {
        vecA.push_back(a[i]);
    }
    for (int i = 0; i < b.size(); i++) {
        vecB.push_back(b[i]);
    }

    int size = 0;
    //cout << "a: " << a << ", b: " << b << endl;
    for (int i = 0; i < vecA.size(); i++) {
        for (int j = 0; j < vecB.size(); j++) {
           // cout << "vecA[" << i << "]=" << vecA[i] << ", vecB[" << j << "]=" << vecB[j] << endl;
            if (vecA[i] == vecB[j]) {
                
                size++;
            }
        }
    }

    if (size == vecA.size() && vecA.size() == vecB.size()) return true;
    else return false;
}

// temp에 가진 알파벳들을 input이 2개 이상 포함하는지 여부를 판단하는 함수.
bool isInclude(string temp, string input) { 
    vector<char> tempElem;  //ACDE
    vector<char> inputElem; //AD
    //cout << "log1" << endl;
    for (int i = 0; i < temp.size(); i++) { //temp string을 char형으로 나눠 담음.
        tempElem.push_back(temp[i]);
    }
    for (int i = 0; i < input.size(); i++) { //input string을 char형으로 나눠 담음.
        inputElem.push_back(input[i]);
    }
    //cout << "log2" << endl;
    
    int cnt = 0;
    for (int i = 0; i < tempElem.size(); i++) {
        
        for (int j = 0; j < inputElem.size(); j++) {
           // cout << "tempElem[i] : "<<tempElem[i] << ", inputElem[j] : "<< inputElem[j] << endl;
            if (tempElem[i] == inputElem[j])
            {
              //  cout << "일치 ! " << endl;
                cnt++;
            }
                
        }
    }

    if (cnt >= 2) return true;
    else return false;
}


// answer에서 ACE가 출현한 orders의 index의 combination에 ACDE도 항상 있다면 ACE를 삭제.
// find 함수 썼었는데 그렇게 하면 안됨. ABCD에서 ABC는 걸러낼 수 있지만 ACD는 걸러낼수 없음.
// include 함수를 새로 도입. isInclude 함수는 string이 아닌 char형으로 해당 알파벳 원소를 가지고 있는지 확인
// 그 중에서 가장 긴거는 냅둬야 함
// 먼저 answer에서 받았을 때 WX와 XW가 있다면 XW를 삭제해야 함
vector<ans> arrange(vector<ans>input2) {
    
    vector<int> trash;  //WX와 XW가 있다면 XW를 지워야한다. XW의 index를 가지는 벡터.

    string trashStr;
    for (int i = 0; i < input2.size(); i++) {
        
        for (int j = 0; j < input2.size(); j++) {
            if (isSame(input2[i].str, input2[j].str) && i != j && input2[i].str!=trashStr) {
                trashStr = input2[j].str;
                trash.push_back(j);
                //cout<<"trash : "<<j<<"번째, "<<
            }
        }

    }

    vector<ans> input;

    for (int i = 0; i < input2.size(); i++) {   //trash에 없는 index만 intput 벡터에 push_back 한다.
        bool isTrash = false;
        for (int j = 0; j < trash.size(); j++) {
            if (i == trash[j]) isTrash = true;
        }
        if (!isTrash) input.push_back(input2[i]);
    }

    cout << endl << "After delete trash answer : ";
    for (int i = 0; i < input.size(); i++) {
        cout << input[i].str << " ";
    }
    cout << endl;

    vector<int> eraseV;  //삭제할 index 벡터
    for (int i = 0; i < input.size(); i++) {
        string temp = input[i].str;     
      
        int del = 0;    //삭제한 횟수
        for (int j = 0; j < input.size(); j++) {
            
            //중요 cout @@@@@
            //cout << "arrange 중입니다: "<<i << ", " << j << " : " << temp <<", "<<input[j].str<<", "<<input[i].idx << ", " << input[j].idx<< endl;
            // temp를 포함 한 경우
            if (
                //input[j].str.find(temp) != string::npos //isInclude(temp,input[j].str)로 대체할 것임 @@
                isInclude(temp, input[j].str)
                && i != j && input[i].idx == input[j].idx)
            {
               // cout << i <<": 조건 만족 : " << input[i].str<< ", " <<input[i].idx << endl;
                
                if (temp.size() > input[j].str.size())
                {
                   // cout << "삭제는 하지 않았습니다." << endl;
                }
                else{
                   // cout<<"! 삭제합니다 ! str,idx : " << input[i].str << ", " << input[i].idx << endl;
                   /*
                    input.erase(input.begin() + i);
                    del++;
                    temp = input[i].str; // initiating
                    j = j - 1;  //지웠으므로 다시 한 칸 앞으로감
                    */
                    eraseV.push_back(i);
                }
            }
            
        }
        //i = i - del;

    }

    vector<ans> result;
    for (int i = 0; i < input.size(); i++) {    //eraseV에 없는 i만 저장
        bool has = false;
        for (int j = 0; j < eraseV.size(); j++) {           
            if (i == eraseV[j]) has = true;
        }
        if (!has) result.push_back(input[i]);
    }

    //cout << "result : ";
    for (int i = 0; i < result.size(); i++) {
       // cout << result[i].str << " " ;
    }
    //cout << endl;

    return result;
}

// solution
vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;  //정답 벡터
    vector<ans> answer2;  //정답내기 위한 벡터

    vector<key> total;   //조합결과 나온 모든 벡터
    vector<string> standard;    //total에서 중복을 제외한 벡터. total에서 중복이 몇개인지 세기 위함.

    for (int c = 0; c < course.size(); c++)
    {

        //cout << course[c] << "크기의 집합들" << endl;

       // cout << course[c] << "개를 뽑았을 때" << endl;
        for (int i = 0; i < orders.size(); i++) {
           // cout << i << "번째 조합 : ";
            if (orders[i].size() >= course[c]) { // ex : 3개를 뽑으려는데 문자열 크기가 2이면 뽑을 수 없음.
                for (int j = 0; j < combination(orders[i], course[c]).size(); j++) {                  
                   // cout << combination(orders[i], course[c])[j] << " ";    //course[c]개를 뽑음
                    key k = { i, combination(orders[i], course[c])[j] };
                    total.push_back(k);  //total에 대입      
                }
            }
           // cout << endl;
        }                   
    }

    vector<string> temp;
    for (int i = 0; i < total.size(); i++) {
        temp.push_back(total[i].str);
    }

    //total 확인
    cout << "Total : ";
    for (int i = 0; i < total.size(); i++) {
        cout << total[i].str << " ";
    }
    cout << endl;


    //standard 확인
    standard = deduplication(temp);
    cout << "standard : ";
    for (int i = 0; i < standard.size(); i++) {
        cout << standard[i] << " ";
    }
    cout << endl;

    // standard에 지정된 문자열들이 각각 total에서 몇번 출현하는지, 2번이상 출현한다면 answer에 추가.
    // 문제 잘못 읽었음. 2번이상 출현한다고 넣는게 아니고 가장 많은 case를 answer에 추가 해야 함
    // testcase2 에서 AB가 왜 result에 안들어가는지에 대한 답. 그러기 위해서 HashMap 도입
    unordered_map<int,int> check; //<문자열 사이즈, 몇 번 출현하는지>
    for (int i = 0; i < course.size(); i++) {
        check.insert(unordered_map<int,int>::value_type(course[i],0));
    }

    for (int i = 0; i < standard.size(); i++) {
        int cnt = 0; //total에서 몇번 출현하는지
        string idx = "";    
        string temp = standard[i];
        for (int j = 0; j < total.size(); j++) {
            if (//temp == total[j].str
                isSame(temp,total[j].str)
                ) {
                cnt++;  //standard에 지정된 문자열들이 각각 total에서 몇번 출현하는지
                //cout << endl;
                //cout << "cnt : " << cnt << endl;
                idx += to_string(total[j].idx);
            }
        }          
        
        if(check[temp.size()]==0){   // 맵이 비어있다면 현재 cnt 삽입
            check[temp.size()]=cnt;
        }
        else {
            if (check[temp.size()] < cnt) { //현재 cnt가 기존 맵의 cnt보다 크다면 교체.
                //가장 많이 주문된 조합을 넣어야 하기 때문
                //check.insert(make_pair(temp.size(), cnt));
                check[temp.size()]=cnt;
            }
        }
        //cout << "check[temp.size()] : " << check[temp.size()] << endl;
        ans a = { temp,idx,cnt };
        if (cnt >=2 ) answer2.push_back(a);  //2를 넘어가면 answer에 push

        //cout << "answer push : " << idx << endl;
    }

    //cout << endl << "여기보시오 @@@@@@@@@@@@@@@@@" << endl;
    // 예를들어, check[2]=3인데 AB는 2번 출현한 경우 AB를 answer2에서 삭제
    for (int i = 0; i < answer2.size(); i++) {
        //cout << answer2[i].str << ", " << check[answer2[i].str.size()] << ", " << answer2[i].cnt << endl;
        if (check[answer2[i].str.size()] > answer2[i].cnt)
        {
            answer2.erase(answer2.begin() + i);
           // cout << endl << answer2[i].str << "를 삭제 했습니다." << endl;
        }
    }

    //answer 확인
    cout << endl;
    cout << "answer : " << endl;;
    for (int i = 0; i < answer2.size(); i++) {
        cout << answer2[i].str << " ";
    }
    cout << endl;

    //arrange 후
    answer2 = arrange(answer2);
    cout << "After arrange : ";
    for (int i = 0; i < answer2.size(); i++) {
        cout << answer2[i].str << " ";
    }
    cout << endl;

    for (int i = 0; i < answer2.size(); i++) {
        answer.push_back(answer2[i].str);
    }

    return answer;
}

int main() {
    vector<string> orders = { "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" };
    vector<int> course = { 2,3,4 };

    solution(orders, course);
    

    return 0;
}