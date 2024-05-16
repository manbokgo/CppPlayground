// URL: https://school.programmers.co.kr/learn/courses/30/lessons/72414
// Algo: 누적 합, 문자열 다루기

// Start:	240511 21 42
// Read:	0 2
// Think:	0 17
// Code:	0 38
// Total:	0 57

// string Split 함수 구현. 그런데 vector 동적 할당 때문에 거의 7배 느림
// 문자열 포맷이 고정이니 substr로 직접 적어주는게 훨씬 빠르다

// 처음엔 슬라이딩 윈도우의 시작점을 각 시간의 시작점으로 해서 누적합 없이 돌렸는데
// 시간 초과 + 틀림으로 아사리판 남. 다시 살펴보니 각 시간 시작점이 아니라도 최대 포함일 수도 있고
// 최악의 케이스를 생각하면 30만 O(n^2)임. 어림없는 풀이였다.

// 다시 생각해보니 초 단위로 변환한 최댓값이 360'000으로 4MB가 안 되니
// 배열 충분히 만들만하고 시간 초과=DP, 고로 누적 합으로 가닥 잡음.

// LV3 92344 파괴되지 않은 건물 문제처럼 시작점+, 종료점-을 체크하고
// 첫번째 누적은 각 초의 값을 확정하고, 두번째 누적이 실제 누적합을 만든다.
// 실수: 누적합 값이 int 범위 초과하니 long long 써야함

// sum[3]이 3~4 구간의 값을 저장하니, 3~5초 구간을 구하려면 sum[4]-sum[2]를 해야하는데
// 잘못 생각해서 sum[5]-sum[2] 적어놓고는 삽질함. 후.. 누적합 수련이 필요하다

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using pii = pair<int, int>;
using ll = long long;

vector<string> Split(const string& str, const string& delimiter)
{
    vector<string> ret;

    const size_t delimLen = delimiter.length();
    size_t st = 0, en;
    while ((en = str.find(delimiter, st)) != string::npos)
    {
        ret.push_back(str.substr(st, en - st));
        st = en + delimLen;
    }
    ret.push_back(str.substr(st));

    return ret;
}

vector<string> Split(const string& str, char delimiter)
{
    vector<string> ret;

    istringstream iss(str);
    string buffer;
    while (getline(iss, buffer, delimiter))
    {
        ret.push_back(buffer);
    }

    return ret;
}

string SecToLog(int sec)
{
    int hr = sec / 3600;
    sec -= hr * 3600;

    int mn = sec / 60;
    sec -= mn * 60;

    ostringstream oss;
    oss << setw(2) << setfill('0') << hr
        << ':'
        << setw(2) << setfill('0') << mn
        << ':'
        << setw(2) << setfill('0') << sec;

    return oss.str();
}

int LogToSec(const string& str)
{
    return stoi(str.substr(0, 2)) * 3600 + stoi(str.substr(3, 5)) * 60 + stoi(str.substr(6, 8));

    vector<string> log = Split(str, ':');
    return stoi(log[0]) * 3600 + stoi(log[1]) * 60 + stoi(log[2]);
}

pii ConvertLogs(const string& str)
{
    return {LogToSec(str.substr(0, 8)), LogToSec(str.substr(9, 17))};

    vector<string> logs = Split(str, '-');
    return {LogToSec(logs[0]), LogToSec(logs[1])};
}

// 누적 합
string solution(string play_time, string adv_time, vector<string> logs)
{
    int playTime = LogToSec(play_time);
    int advTime = LogToSec(adv_time);

    vector<ll> sum(playTime + 1);
    for (const auto& log : logs)
    {
        const auto [st, en] = ConvertLogs(log);
        ++sum[st];
        --sum[en];
    }

    for (int i = 1; i <= playTime; ++i) sum[i] += sum[i - 1];
    for (int i = 1; i <= playTime; ++i) sum[i] += sum[i - 1];

    int answer = 0;
    ll mxSum = sum[0 + advTime];
    for (int i = 1; i + advTime - 1 <= playTime; ++i)
    {
        ll now = sum[i + advTime - 1] - sum[i - 1];
        if (now > mxSum)
        {
            answer = i;
            mxSum = now;
        }
    }

    return SecToLog(answer);
}


// 누적합 없는 슬라이딩 윈도우
/*
string solution(string play_time, string adv_time, vector<string> logs)
{
    int playTime = LogToSec(play_time);
    int advTime = LogToSec(adv_time);

    vector<pii> times;
    times.reserve(logs.size());
    for (const auto& log : logs)
    {
        times.push_back(ConvertLogs(log));
    }

    sort(times.begin(), times.end());

    int answer = 0;
    ll answerSum = 0;
    for (int i = 0; i < times.size(); ++i)
    {
        const auto [nowSt, nowEn] = times[i];
        const int advEn = nowSt + advTime;
        if (advEn >= playTime) break;

        ll sum = 0;
        for (int j = i; j < times.size(); ++j)
        {
            auto [st, en] = times[j];
            if (st >= advEn) break;
            if (en > advEn) en = advEn;
            sum += en - st;
        }

        if (answerSum < sum)
        {
            answer = nowSt;
            answerSum = sum;
        }
    }

    int advSt = playTime - advTime;
    ll sum = 0;
    for (auto [st, en] : times)
    {
        if (en <= advSt) continue;
        sum += en - max(st, advSt);
    }

    if (answerSum < sum)
    {
        answer = advSt;
    }

    return SecToLog(answer);
}
*/


int main()
{
    string result;

    result = solution("02:03:55", "00:14:15", {
        "01:20:15-01:45:14", "00:40:31-01:00:00", "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30"
    });
    cout << result << '\n';

    result = solution("99:59:59", "25:00:00", {
        "69:59:59-89:59:59", "01:00:00-21:00:00", "79:59:59-99:59:59", "11:00:00-31:00:00"
    });
    cout << result << '\n';

    result = solution("50:00:00", "50:00:00", {"15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45"});
    cout << result << '\n';

    return 0;
}
