#include <bits/stdc++.h>
using namespace std;

const int MAX = 5000000;
vector<int> v(MAX);

int MiddleOfThree(vector<int> &vec, int a, int b, int c)
{
    if ((vec[a] < vec[b] && vec[b] < vec[c]) || (vec[c] < vec[b] && vec[b] < vec[a]))
        return b;
    else if ((vec[b] < vec[a] && vec[a] < vec[c]) || (vec[c] < vec[a] && vec[a] < vec[b]))
        return a;
    else
        return c;
}

int partition(vector<int> &vec, int left, int right, int pivotIdx)
{
    int pivot = vec[pivotIdx];
    swap(vec[pivotIdx], vec[right]);

    int store = left;
    for (int i = left; i < right; i++)
    {
        if (vec[i] <= pivot)
        {
            swap(vec[store++], vec[i]);
        }
    }
    swap(vec[right], vec[store]);
    return store;
}

void QuickSort(vector<int> &vec, int left, int right, int k)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        int pivotIdx = MiddleOfThree(vec, left, mid, right);

        int newPivotIdx = partition(vec, left, right, pivotIdx);
        if (newPivotIdx == k)
            return;
        QuickSort(vec, left, newPivotIdx - 1, k);
        QuickSort(vec, newPivotIdx + 1, right, k);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    --k;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    QuickSort(v, 0, n - 1, k);
    // nth_element(v.begin(), v.begin() + k, v.begin() + n);
    cout << v[k] << "\n";
}