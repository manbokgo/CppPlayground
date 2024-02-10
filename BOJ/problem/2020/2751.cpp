#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000000;
vector<int> v(MAX);
vector<int> sortedV(MAX);

void Merge(vector<int> &vec, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (k <= right)
    {
        if (j > right)
            sortedV[k++] = vec[i++];
        else if (i > mid)
            sortedV[k++] = vec[j++];
        else if (vec[i] < vec[j])
            sortedV[k++] = vec[i++];
        else
            sortedV[k++] = vec[j++];
    }

    for (int i = left; i <= right; i++)
    {
        vec[i] = sortedV[i];
    }
    
}

void MergeSort(vector<int> &vec, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(vec, left, mid);
        MergeSort(vec, mid + 1, right);
        Merge(vec, left, mid, right);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        v[i] = val;
    }

    MergeSort(v, 0, n-1);

    for (int i = 0; i < n; i++)
    {
        cout << v[i] << "\n";
    }
}