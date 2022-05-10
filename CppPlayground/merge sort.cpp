# include <stdio.h>
# define MAX_SIZE 8
int sorted[MAX_SIZE]; // 추가적인 공간이 필요

void Merge(int list[], int left, int mid, int right)
{
	int low = left;
	int high = mid + 1;
	int pivot = left;

	while (low <= mid && high <= right)
	{
		if (list[low] <= list[high])
			sorted[pivot++] = list[low++];
		else
			sorted[pivot++] = list[high++];
	}

	if (low > mid)
	{
		for (int i = high; i <= right; i++)
			sorted[pivot++] = list[i];
	}
	else
	{
		for (int i = low; i <= mid; i++)
			sorted[pivot++] = list[i];
	}

	for (int i = left; i <= right; i++)
	{
		list[i] = sorted[i];
	}
}

void MergeSort(int list[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		MergeSort(list, left, mid);
		MergeSort(list, mid + 1, right);
		Merge(list, left, mid, right);
	}
}

void main()
{
	int i;
	int n = MAX_SIZE;
	int list[n] = {21, 10, 12, 20, 25, 13, 15, 22};

	// 합병 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 7)
	MergeSort(list, 0, n - 1);

	// 정렬 결과 출력
	for (i = 0; i < n; i++)
	{
		printf("%d\n", list[i]);
	}
}
