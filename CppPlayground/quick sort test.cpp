// 어떤 구현법이 가장 성능이 좋을까 연구

#include <iostream>
#include <numeric>

int arrSize = 0;
bool errorCaused = false;

void swap(int* arr, int left, int right, bool lastSwap = false) {
	static int SwapCounter = 0;

	if (lastSwap) std::cout << "SWL@\t";
	else std::cout << "SW@\t";
	std::cout <<  arr[left] << "(" << left << ") " << arr[right] << "(" << right << ")\tS" << ++SwapCounter << std::endl;

	int temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}

int Partition(int* arr, int left, int right)
{
	static int ICounter = 0;
	static int PartitionCounter = 0;


	// 16 22 38
	// 1~100 테스트 0 99 4950
	// 왼쪽 피벗 초기값양옆 p-1 / p+1
	/*int low = left;
	int high = right + 1;
	int pivot = arr[left];
	
	while (true) {
		while (arr[--high] >= pivot && low < high) {++ICounter;}
		while (arr[++low] < pivot && low < high) {++ICounter;}
		if (low >= high) break;
	
		swap(arr, low, high);
	}
	
	if (left != high)
		swap(arr, left, high);

	std::cout << "PD@\tLR: " << low << "," << high << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
	if (low - right > 1 || left - high > 1)
	{
		std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
		errorCaused = true;
	}
	return high;*/

	// 20 27 139
	// 1~100 테스트 0 99 5148
	// 왼쪽 피벗인데 중간처럼하는 방식 geeksforgeeks p / p+1
	/*int pivot = arr[left];
	int i = left - 1, j = right + 1;
	
	while (true) {
		// Find leftmost element greater than
		// or equal to pivot
		do {
			i++; ICounter++;
		} while (arr[i] < pivot);
	
		// Find rightmost element smaller than
		// or equal to pivot
		do {
			j--; ICounter++;
		} while (arr[j] > pivot);
	
		// If two pointers met.
		if (i >= j)
		{
			std::cout << "PD@\tLR: " << i << "," << j << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
			if (i - right > 1 || left - j > 1)
			{
				std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
				errorCaused = true;
			}
			return j;
		}
			
	
		swap(arr, i, j);
	}*/

	// 57 22 115
	// 1~100 테스트 4950 99 9900
	// 로무토 p-1 / p+1
	/*int low = left;
	int high = right;
	int pivot = arr[high];
	int i = (low - 1);
	
	for (int j = low; j <= high - 1; j++)
	{
		ICounter++;
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element
			ICounter++;
	
			swap(arr, i, j);
		}
	}
	
	if (i+1 != high)
		swap(arr, i + 1, high, true);
	
	std::cout << "PD@\tLR: " << low << "," << high << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
	if (low - right > 1 || left - high > 1)
	{
		std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
		errorCaused = true;
	}
	
	return (i + 1);*/


	// 33 27 110
	// 1~100 테스트 99 99 771
	// 중간 피벗 p-1 / p
	/*int center = (left + right) / 2;
	int low = left;
	int high = right;
	int pivot = arr[center];
	
	while (low <= high) {
		while (low <= high && arr[low] < pivot) {low++; ICounter++;}
		while (low <= high && arr[high] > pivot) {high--; ICounter++;}
	
		if (low <= high) {
			swap(arr, low, high);
			low++; high--; ICounter++; ICounter++;
		}
	}
	
	std::cout << "PD@\tLR: " << low << "," << high << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
	if (low - right > 1 || left - high > 1)
	{
		std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
		errorCaused = true;
	}
	return low;*/


	// 16 22 56
	// 1~100 테스트 0 99 4950
	// 왼쪽 피벗 초기값자체 p-1 / p+1
	/*int low = left + 1;
	int high = right;
	int pivot = arr[left];
	while (low <= high) {
		while (low <= high && arr[high] >= pivot)
		{
			--high; ++ICounter;
		}
		while (low <= high && arr[low] < pivot)
		{
			++low; ++ICounter;
		}

		if (low > high) break;

		swap(arr, low, high);
		--high; ++ICounter;
		++low; ++ICounter;
	}

	if (left != high)
		swap(arr, left, high, true);

	std::cout << "PD@\tLR: " << low << "," << high << "\t\tP" << ++PartitionCounter << "\tI" << ICounter << std::endl;
	if (low - right > 1 || left - high > 1)
	{
		std::cout << "@@@@@ Wrong Index Warning @@@@@" << std::endl;
		errorCaused = true;
	}
	return high;*/



}

void QuickSortMedian(int* arr, int Left, int Right)
{
	if (Left < Right)
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


		int	pivot = Partition(arr, Left, Right);


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
	// {
	// 	int test[] = { 1, 2, 3, 4, 5 };
	// 	int result[] = { 1, 2, 3, 4, 5 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 5,4,3,2,1 };
	// 	int result[] = { 1, 2, 3, 4, 5 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 5, 4 };
	// 	int result[] = { 4, 5 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 4, 5 };
	// 	int result[] = { 4, 5 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 7, 7 };
	// 	int result[] = { 7, 7 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 5, 3, 1, 6, 7, 2, 4, 8, 9 };
	// 	int result[] = { 1, 2, 3, 4, 5, 6, 7 ,8, 9 };
	// 	Test(test, result, std::size(test));
	// }
	//
	// {
	// 	int test[] = { 5, 3, 9, 8, 6, 5, 4, 1, 5 };
	// 	int result[] = { 1, 3, 4, 5, 5, 5, 6, 8, 9 };
	// 	Test(test, result, std::size(test));
	// }

	{
		int test[100];
		std::iota(std::begin(test), std::end(test), 0);
		int result[100];
		std::copy(std::begin(test), std::end(test), std::begin(result));
		Test(test, result, std::size(test));
	}

	if (errorCaused) std::cout << "ERROR" << std::endl;
	else std::cout << "ALL GOOD" << std::endl;


	return 0;
}




