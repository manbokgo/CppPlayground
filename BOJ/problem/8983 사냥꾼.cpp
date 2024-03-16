// URL: https://www.acmicpc.net/problem/8983
// Algo: 이분 탐색

// Start:	240310 21 19
// Read:	0 1
// Think:	0 2
// Code:	0 16 시간초과
// Code:    0 29 생각의 전환이 필요한걸 깨달음
// Total:	0 47
// 오모시로이

// 처음의 풀이는 animal을 정렬하고, 각 헌터가 쏠 수 있는 x 좌표 상의 동물들을 이분 탐색으로 찾아 순회하였는데
// 이미 죽은 놈은 또 카운트하면 안 되니 animalDie Bool로 스킵해야하는 것에서부터 냄새가 났다. 시간초과.

// 동물의 x 좌표를 이분 탐색으로 찾으니 O(M log N)으로 시간 복잡도가 충분하다고 생각했는데 잘못된 생각이었음.
// range가 엄청 크면 모든 헌터가 죽은 동물들을 모두 다시 방문하여 시간복잡도 O(MN)이라는 점을 깨달음. M,N이 100,000이니 당연히 시간 초과.
// 풀기 전에 시간 복잡도 계산 잘 하자.

// 모든 동물은 한 차례만 방문하면 된다.
// 생각을 정반대로 바꿔서 hunter를 정렬하고, 각 동물이 '쏘임당할' 수 있는 헌터를 이분탐색으로 찾아서 해결. 이러면 시간 복잡도 O(N log M)
// 정렬까지 포함한 총 시간복잡도는 O(M log M + N log M)
// + 헌터들의 x좌표가 정렬되지 않은채로 입력되던 게 일종의 힌트였던 듯(!)

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define Y first
#define X second
#define all(x) x.begin(), x.end()
#define SortVec(x) sort(all(x))
#define CompressVec(x) x.erase(unique(all(x)), x.end())
#define ExistInVec(x, value) find(all(x), value) != x.end()

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tiii = tuple<int, int, int>;
using tlll = tuple<ll, ll, ll>;

constexpr int INF = 0x3f3f3f3f;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, range;
    cin >> m >> n >> range;

    vector<int> hunters;
    hunters.reserve(m);
    for (int i = 0; i < m; ++i)
    {
        int num;
        cin >> num;
        hunters.pb(num);
    }

    vector<pii> animals;
    animals.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        animals.pb({x, y});
    }




    SortVec(hunters);
    int answer = 0;
    for (int i = 0; i < n; ++i)
    {
        auto [x, y] = animals[i];

        int offset = range - y;
        if (offset < 0) continue;

        int minX = x - offset;
        if (minX < 0) minX = 0;
        int maxX = x + offset;

        auto it = lower_bound(all(hunters), minX);
        if (it == hunters.end()) continue;
        if (*it > maxX) continue;
        ++answer;
    }

    /*
    // 시간 초과
    SortVec(animals);

    int answer = 0;
    for (int i = 0; i < m; ++i)
    {
        int hunter = hunters[i];

        int minX = hunter - range;
        if (minX < 0) minX = 0;
        int maxX = hunter + range;

        int minIdx = lower_bound(all(animals), pii{minX, 0}) - animals.begin();
        int maxIdx = upper_bound(all(animals), pii{maxX, 0}) - animals.begin();

        for (int j = minIdx; j < maxIdx; ++j)
        {
            auto [x, y] = animals[j];
            if (abs(x-hunter) + y > range)
            {
                j = lower_bound(all(animals), pii{++minX, 0}) - animals.begin() - 1; // 실수: ++j 생각하셈
                continue;
            }
            
            if (animalDie[j]) continue;
            animalDie[j] = true;
            ++answer;
        }
    }
    */

    cout << answer;
}
