#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s;
    vector<int> v1(26, 0);
	
    cin >> s;
    for (auto c : s) {
        ++v1[c-97];
    }
	for (auto result : v1) {
        cout << result << ' ';
	}
}