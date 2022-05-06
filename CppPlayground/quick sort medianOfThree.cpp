// 일반 테스트 32 7 11
// 1~100 테스트 62 31 350
// 기존 1~100 테스트 0 99 4950 / 99 99 771

#include <iostream>
#include <numeric>

int arrSize = 0;
bool errorCaused = false;

void swap(int* arr, int left, int right, bool lastSwap = false) {
	static int SwapCounter = 0;

	if (lastSwap) std::cout << "SWL@\t";
	else std::cout << "SW@\t";
	std::cout << arr[left] << "(" << left << ") " << arr[right] << "(" << right << ")\tS" << ++SwapCounter << std::endl;

	int temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}

void threeSort(int arr[], int left, int mid, int right)
{
	std::cout << "THREE " << left << " " << mid << " " << right << std::endl;
	if (arr[left] > arr[mid]) swap(arr, left, mid);
	if (arr[mid] > arr[right]) swap(arr, mid, right);
	if (arr[left] > arr[mid]) swap(arr, left, mid);
	std::cout << "THREE END " << left << " " << mid << " " << right << std::endl;
}


int PartitionMedian(int* arr, int left, int mid, int right)
{
	static int ICounter = 0;
	static int PartitionCounter = 0;

	int pivot = arr[mid];
	swap(arr, mid, right - 1);

	int low = left;
	int high = right - 1;

	while (true) {
		while (arr[++low] <= pivot && low < high) { ++ICounter; }
		while (arr[--high] > pivot && low < high) { ++ICounter; }
		if (low >= high) break;

		swap(arr, low, high);
	}

	if (low != right - 1)
		swap(arr, low, right - 1, true);

	std::cout << "PD@\tLR: " << low << "," << high << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
	if (low - right > 1 || left - high > 1)
	{
		std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
		errorCaused = true;
	}
	return low;
}

void QuickSortMedian(int* arr, int Left, int Right)
{
	int mid = (Left + Right) / 2;
	threeSort(arr, Left, mid, Right);

	if (Right - Left + 1 > 3)
	{

		std::cout << "Before: ";
		for (int i = 0; i < arrSize; ++i)
		{
			if (i == Left) std::cout << "[";
			else std::cout << " ";

			std::cout << arr[i];

			if (i == Right) std::cout << "]";
			else std::cout << " ";
		}
		std::cout << std::endl;


		int	pivot = PartitionMedian(arr, Left, mid, Right);


		// std::cout << "New Pivot: " << arr[pivot] << "(" << pivot << ")" << std::endl;
		std::cout << "After: ";
		for (int i = 0; i < arrSize; ++i)
		{
			if (i == pivot + 1 && pivot + 1 <= Right) std::cout << "[";
			else if (i == Left && pivot - 1 >= Left) std::cout << "[";
			else std::cout << " ";

			if (i == pivot) std::cout << "*";
			std::cout << arr[i];
			if (i == pivot) std::cout << "*";

			if (i == pivot - 1 && pivot - 1 >= Left) std::cout << "]";
			else if (i == Right && pivot + 1 <= Right) std::cout << "]";
			else std::cout << " ";
		}
		std::cout << std::endl << std::endl;


		QuickSortMedian(arr, Left, pivot - 1);
		QuickSortMedian(arr, pivot + 1, Right);
	}
}

void QuickSortMedian(int* arr, int size) {
	arrSize = size;
	std::cout << "---------------------------" << std::endl;;
	QuickSortMedian(arr, 0, size - 1);
	std::cout << "---------------------------" << std::endl;
}


bool Test(int* arr1, int* arr2, int size)
{
	static const auto arraysAreEqual = "Arrays are equal.";
	static const auto arraysAreNotEqual = "@@@ Arrays are NOT equal. @@@";

	std::cout << "Input: ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr1[i] << " ";
	}
	std::cout << std::endl;


	QuickSortMedian(arr1, size);


	std::cout << "Sorted: ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr1[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Expected: ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << arr2[i] << " ";
	}
	std::cout << std::endl;


	for (int i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			std::cout << arraysAreNotEqual << std::endl << std::endl << std::endl;
			errorCaused = true;
			return false;
		}
	}

	std::cout << arraysAreEqual << std::endl << std::endl << std::endl;
	return true;
}

int main() {
	{
		int test[] = { 1, 2, 3, 4, 5 };
		int result[] = { 1, 2, 3, 4, 5 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 5,4,3,2,1 };
		int result[] = { 1, 2, 3, 4, 5 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 5, 4 };
		int result[] = { 4, 5 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 4, 5 };
		int result[] = { 4, 5 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 7, 7 };
		int result[] = { 7, 7 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 5, 3, 1, 6, 7, 2, 4, 8, 9 };
		int result[] = { 1, 2, 3, 4, 5, 6, 7 ,8, 9 };
		Test(test, result, std::size(test));
	}
	
	{
		int test[] = { 5, 3, 9, 8, 6, 5, 4, 1, 5 };
		int result[] = { 1, 3, 4, 5, 5, 5, 6, 8, 9 };
		Test(test, result, std::size(test));
	}

	// {
	// 	int test[100];
	// 	std::iota(std::begin(test), std::end(test), 0);
	// 	int result[100];
	// 	std::copy(std::begin(test), std::end(test), std::begin(result));
	// 	Test(test, result, std::size(test));
	// }


	if (errorCaused) std::cout << "ERROR" << std::endl;
	else std::cout << "ALL GOOD" << std::endl;


	return 0;
}




