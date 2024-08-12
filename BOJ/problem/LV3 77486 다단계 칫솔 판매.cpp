// URL: https://school.programmers.co.kr/learn/courses/30/lessons/77486
// Algo: 구현

// Start:	240417 16 12
// Read:	0 5 enroll 동명이인은 없는 거겠지...?
// Think:	0 3
// Code:	0 15  DFS 실패.
// Code:	0 6   성공. 분리 집합에서의 Find 로직 사용. while loop로도 된다.
// Total:	0 26

// DFS는 (내 벌이+수금1+수금2)x0.9라는 식인데 1원 절삭 오차 때문에 틀림. 내 벌이x0.9 + 수금1x0.9 + 수금2x0.9 로 해야한다.
// 아니 무슨 말단이 칫솔 3개 팔자마자 3개만큼 상납하고, 7개 팔자마자 상납하고 이게 말이 됨?
// 이번 분기에 총합 10개 팔았습니다! 하고 10개만큼 상납하는거지 거 참

// 실수: *0.1이 아니라 /10으로 해야함. 1064 -= 1064 * 0.1 를 하면 958이 나올 것으로 잘못 예상했다.
// 풀어쓰면  int 변수 = 1064 - 1064 * 0.1 이고, 결국  int 변수 = 957.6 가 되어 957이 나온다. 멍청한!
// 아니면 int 십퍼 = 1064 * 0.1로 int로 만들어버린 후 빼든가

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

template <class K, class V>
using umap = unordered_map<K, V>;

vector<int> ans;
vector<int> P;
umap<string, int> M;

void Find(int num, int val)
{
    ans[num] += val - val / 10;

    if (P[num] < 0 || val < 10) return;
    return Find(P[num], val / 10);
}


vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    P.reserve(enroll.size());
    for (int i = 0; i < enroll.size(); ++i)
    {
        M[enroll[i]] = i;
        if (referral[i] != "-") P.push_back(M[referral[i]]);
        else P.push_back(-1);
    }
    
    ans.resize(enroll.size(), 0);
    for (int i = 0; i < seller.size(); ++i)
    {
        Find(M[seller[i]], 100 * amount[i]);
    }
    
    return ans;
}




// DFS
/*
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

template <class K, class V>
using umap = unordered_map<K, V>;

vector<int> ans;
vector<vector<int>> C;
umap<string, int> M;

void DFS(int num, int par)
{
    for (int child : C[num])
        DFS(child, num);
    
    if (ans[num] < 10) return;
    ans[par] += ans[num] / 10;
    ans[num] -= ans[num] / 10;
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    C.resize(enroll.size() + 1);
    for (int i = 0; i < enroll.size(); ++i)
    {
        M[enroll[i]] = i + 1;
        if (referral[i] != "-") C[M[referral[i]]].push_back(i + 1);
        else C[0].push_back(i + 1);
    }
    
    ans.resize(enroll.size() + 1, 0);
    for (int i = 0; i < seller.size(); ++i)
    {
        ans[M[seller[i]]] += 100 * amount[i];
    }
    
    DFS(0, 0);
    ans.erase(ans.begin());

    return ans;
}

*/