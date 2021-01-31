/*
��, �ڽ��丮 �޴��� �ּ� 2���� �̻��� ��ǰ�޴��� �����Ϸ��� �մϴ�. 
����, �ּ� 2�� �̻��� �մ����κ��� �ֹ��� ��ǰ�޴� ���տ� ���ؼ��� �ڽ��丮 �޴� �ĺ��� �����ϱ�� �߽��ϴ�.

�� �մԵ��� �ֹ��� ��ǰ�޴����� ���ڿ� �������� ��� �迭 orders,
��ī�ǰ� �߰��ϰ� �;��ϴ� �ڽ��丮�� �����ϴ� ��ǰ�޴����� ������ ��� �迭 course�� �Ű������� �־��� ��,
��ī�ǰ� ���� �߰��ϰ� �� �ڽ��丮�� �޴� ������ ���ڿ� ���·� �迭�� ��� return �ϵ��� solution �Լ��� �ϼ��� �ּ���.

(Ǯ��)
1�� �մ��� 2�� ���� {a,b} {a,c}
2�� �մ��� 2�� ���� {c,d}

... ��� �մ��� 2�� ���տ��� 2�� �̻� ��ġ�°� �ִ��� �Ǵ�.

�ִٸ� ��� answer vector�� ����.

3�� ���տ� ���ؼ��� ����. �� ���� ���ؼ� ������ �����ϴ����� course�� �־���.

 + ����ؾ��Ұ�
 ACF ACDE ACDEH �� �ִٸ�
 answer vector�� AC (o) ACE(x) ACDE(o)�� ��Ȳ�� �����ؾ� �Ѵ�.
 -> ACE�� ������ index�� ACDE�� �׻� �ִٸ� ACE�� ����.

*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// orders�� index�� �����ϱ� ���� ����ü ����. arrange�Լ����� �ʿ�.
struct key {
    int idx;
    string str;
};

// answer�� ������� string�� ��� ����ü
struct ans {
    string str; //ex AC
    string idx; //ex "35"
    int cnt;    //total���� ��� �����ϴ���
};

// ���������� ���� �Լ�
bool desc(char a, char b) {
    return a > b;
}

// n�� string���� r���� �̾� ����. next_permutation �޼��� Ȱ�� (include algorithm)
vector<string> combination(string input, int r) {  
    vector<char> idx;
    vector<string> result;
    for (int i = 0; i < input.size(); i++) {
        idx.push_back(input[i]);
    }

    // 0��1�� ���� �� ���� ����
    vector<char> ind;
    // 1�߰�
    for (int i = 0; i < r; i++) {
        ind.push_back('1');
    }
    // 0�߰�
    for (int i = 0; i < idx.size() - r; i++) {
        ind.push_back('0');
    }
    sort(ind.begin(), ind.end());   //����
    //����
    do {
        // ���
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

// input�� �ߺ� ���Ҹ� �������ִ� �Լ�.standard�� �̱�����. (include algorithm) unique, erase ���
vector<string> deduplication(vector<string> s)
{
    vector<string> output;
    //����
    sort(s.begin(), s.end());
    //�ߺ� ����
    s.erase(unique(s.begin(), s.end()), s.end());
    for (int i = 0; i < s.size(); i++) {
        output.push_back(s[i]);
    }

    return output;
}

//XW�� WX�� ���� �������� �Լ� -> char�� �迭�� ��Ƴ��� ���� ���Ұ� ������ �Ǵ��Ѵ�.
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

// temp�� ���� ���ĺ����� input�� 2�� �̻� �����ϴ��� ���θ� �Ǵ��ϴ� �Լ�.
bool isInclude(string temp, string input) { 
    vector<char> tempElem;  //ACDE
    vector<char> inputElem; //AD
    //cout << "log1" << endl;
    for (int i = 0; i < temp.size(); i++) { //temp string�� char������ ���� ����.
        tempElem.push_back(temp[i]);
    }
    for (int i = 0; i < input.size(); i++) { //input string�� char������ ���� ����.
        inputElem.push_back(input[i]);
    }
    //cout << "log2" << endl;
    
    int cnt = 0;
    for (int i = 0; i < tempElem.size(); i++) {
        
        for (int j = 0; j < inputElem.size(); j++) {
           // cout << "tempElem[i] : "<<tempElem[i] << ", inputElem[j] : "<< inputElem[j] << endl;
            if (tempElem[i] == inputElem[j])
            {
              //  cout << "��ġ ! " << endl;
                cnt++;
            }
                
        }
    }

    if (cnt >= 2) return true;
    else return false;
}


// answer���� ACE�� ������ orders�� index�� combination�� ACDE�� �׻� �ִٸ� ACE�� ����.
// find �Լ� ����µ� �׷��� �ϸ� �ȵ�. ABCD���� ABC�� �ɷ��� �� ������ ACD�� �ɷ����� ����.
// include �Լ��� ���� ����. isInclude �Լ��� string�� �ƴ� char������ �ش� ���ĺ� ���Ҹ� ������ �ִ��� Ȯ��
// �� �߿��� ���� ��Ŵ� ���־� ��
// ���� answer���� �޾��� �� WX�� XW�� �ִٸ� XW�� �����ؾ� ��
vector<ans> arrange(vector<ans>input2) {
    
    vector<int> trash;  //WX�� XW�� �ִٸ� XW�� �������Ѵ�. XW�� index�� ������ ����.

    string trashStr;
    for (int i = 0; i < input2.size(); i++) {
        
        for (int j = 0; j < input2.size(); j++) {
            if (isSame(input2[i].str, input2[j].str) && i != j && input2[i].str!=trashStr) {
                trashStr = input2[j].str;
                trash.push_back(j);
                //cout<<"trash : "<<j<<"��°, "<<
            }
        }

    }

    vector<ans> input;

    for (int i = 0; i < input2.size(); i++) {   //trash�� ���� index�� intput ���Ϳ� push_back �Ѵ�.
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

    vector<int> eraseV;  //������ index ����
    for (int i = 0; i < input.size(); i++) {
        string temp = input[i].str;     
      
        int del = 0;    //������ Ƚ��
        for (int j = 0; j < input.size(); j++) {
            
            //�߿� cout @@@@@
            //cout << "arrange ���Դϴ�: "<<i << ", " << j << " : " << temp <<", "<<input[j].str<<", "<<input[i].idx << ", " << input[j].idx<< endl;
            // temp�� ���� �� ���
            if (
                //input[j].str.find(temp) != string::npos //isInclude(temp,input[j].str)�� ��ü�� ���� @@
                isInclude(temp, input[j].str)
                && i != j && input[i].idx == input[j].idx)
            {
               // cout << i <<": ���� ���� : " << input[i].str<< ", " <<input[i].idx << endl;
                
                if (temp.size() > input[j].str.size())
                {
                   // cout << "������ ���� �ʾҽ��ϴ�." << endl;
                }
                else{
                   // cout<<"! �����մϴ� ! str,idx : " << input[i].str << ", " << input[i].idx << endl;
                   /*
                    input.erase(input.begin() + i);
                    del++;
                    temp = input[i].str; // initiating
                    j = j - 1;  //�������Ƿ� �ٽ� �� ĭ �����ΰ�
                    */
                    eraseV.push_back(i);
                }
            }
            
        }
        //i = i - del;

    }

    vector<ans> result;
    for (int i = 0; i < input.size(); i++) {    //eraseV�� ���� i�� ����
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
    vector<string> answer;  //���� ����
    vector<ans> answer2;  //���䳻�� ���� ����

    vector<key> total;   //���հ�� ���� ��� ����
    vector<string> standard;    //total���� �ߺ��� ������ ����. total���� �ߺ��� ����� ���� ����.

    for (int c = 0; c < course.size(); c++)
    {

        //cout << course[c] << "ũ���� ���յ�" << endl;

       // cout << course[c] << "���� �̾��� ��" << endl;
        for (int i = 0; i < orders.size(); i++) {
           // cout << i << "��° ���� : ";
            if (orders[i].size() >= course[c]) { // ex : 3���� �������µ� ���ڿ� ũ�Ⱑ 2�̸� ���� �� ����.
                for (int j = 0; j < combination(orders[i], course[c]).size(); j++) {                  
                   // cout << combination(orders[i], course[c])[j] << " ";    //course[c]���� ����
                    key k = { i, combination(orders[i], course[c])[j] };
                    total.push_back(k);  //total�� ����      
                }
            }
           // cout << endl;
        }                   
    }

    vector<string> temp;
    for (int i = 0; i < total.size(); i++) {
        temp.push_back(total[i].str);
    }

    //total Ȯ��
    cout << "Total : ";
    for (int i = 0; i < total.size(); i++) {
        cout << total[i].str << " ";
    }
    cout << endl;


    //standard Ȯ��
    standard = deduplication(temp);
    cout << "standard : ";
    for (int i = 0; i < standard.size(); i++) {
        cout << standard[i] << " ";
    }
    cout << endl;

    // standard�� ������ ���ڿ����� ���� total���� ��� �����ϴ���, 2���̻� �����Ѵٸ� answer�� �߰�.
    // ���� �߸� �о���. 2���̻� �����Ѵٰ� �ִ°� �ƴϰ� ���� ���� case�� answer�� �߰� �ؾ� ��
    // testcase2 ���� AB�� �� result�� �ȵ������� ���� ��. �׷��� ���ؼ� HashMap ����
    unordered_map<int,int> check; //<���ڿ� ������, �� �� �����ϴ���>
    for (int i = 0; i < course.size(); i++) {
        check.insert(unordered_map<int,int>::value_type(course[i],0));
    }

    for (int i = 0; i < standard.size(); i++) {
        int cnt = 0; //total���� ��� �����ϴ���
        string idx = "";    
        string temp = standard[i];
        for (int j = 0; j < total.size(); j++) {
            if (//temp == total[j].str
                isSame(temp,total[j].str)
                ) {
                cnt++;  //standard�� ������ ���ڿ����� ���� total���� ��� �����ϴ���
                //cout << endl;
                //cout << "cnt : " << cnt << endl;
                idx += to_string(total[j].idx);
            }
        }          
        
        if(check[temp.size()]==0){   // ���� ����ִٸ� ���� cnt ����
            check[temp.size()]=cnt;
        }
        else {
            if (check[temp.size()] < cnt) { //���� cnt�� ���� ���� cnt���� ũ�ٸ� ��ü.
                //���� ���� �ֹ��� ������ �־�� �ϱ� ����
                //check.insert(make_pair(temp.size(), cnt));
                check[temp.size()]=cnt;
            }
        }
        //cout << "check[temp.size()] : " << check[temp.size()] << endl;
        ans a = { temp,idx,cnt };
        if (cnt >=2 ) answer2.push_back(a);  //2�� �Ѿ�� answer�� push

        //cout << "answer push : " << idx << endl;
    }

    //cout << endl << "���⺸�ÿ� @@@@@@@@@@@@@@@@@" << endl;
    // �������, check[2]=3�ε� AB�� 2�� ������ ��� AB�� answer2���� ����
    for (int i = 0; i < answer2.size(); i++) {
        //cout << answer2[i].str << ", " << check[answer2[i].str.size()] << ", " << answer2[i].cnt << endl;
        if (check[answer2[i].str.size()] > answer2[i].cnt)
        {
            answer2.erase(answer2.begin() + i);
           // cout << endl << answer2[i].str << "�� ���� �߽��ϴ�." << endl;
        }
    }

    //answer Ȯ��
    cout << endl;
    cout << "answer : " << endl;;
    for (int i = 0; i < answer2.size(); i++) {
        cout << answer2[i].str << " ";
    }
    cout << endl;

    //arrange ��
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