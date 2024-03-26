#include <bits/stdc++.h>
using namespace std;

int main() {
    string a = "110010101001";
    int b = stoi(a, nullptr, 2);
    string c = bitset<32>(b).to_string();

    cout << c;
}
