#include <bits/stdc++.h>
using namespace std;

void BubbleSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
		for (int j = 0; j < vec.size() - i - 1; ++j)
			if (vec[j] > vec[j+1]) swap(vec[j], vec[j+1]);
}

void SelectionSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		int min = i;
		for (int j = i+1; j < vec.size(); ++j)
			if (vec[j] < vec[min]) min = j;
		
		swap(vec[i], vec[min]);
	}
}

void InsertionSort(vector<int>& vec)
{
	for (int i = 1; i < vec.size(); ++i)
	{
		int j, current = vec[i];
		for (j = i-1; j >= 0 && current < vec[j]; --j)
			vec[j + 1] = vec[j];
		vec[j + 1] = current;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int n;
	cin >> n;
	vector<int> lst(n);

	for (int i = 0; i < n; ++i) cin >> lst[i];
	// BubbleSort(lst);
	// SelectionSort(lst);
	InsertionSort(lst);
	for (auto val : lst) cout << val << '\n';
}