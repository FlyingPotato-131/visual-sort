#include<bits/stdc++.h>
using namespace std;
const int RUN = 32;

template <typename T>
void insertionSort(T*first, int left, int right, bool(*compare)(const T, const T))
{
	for (int i = left + 1; i <= right; i++)
	{
		T temp = first[i];
		int j = i - 1;
		while (j >= left && !compare(first[j], temp))
		{
			first[j+1] = first[j];
			j--;
		}
		first[j+1] = temp;
	}
}

template <typename T>
void merge(T*first, int l, int m, int r, bool(*compare)(const T, const T))
{
	
	int len1 = m - l + 1, len2 = r - m;
	T left[len1], right[len2];
	for (int i = 0; i < len1; i++)
		left[i] = first[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = first[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < len1 && j < len2)
	{
		if (compare(left[i], right[j]))
		{
			first[k] = left[i];
			i++;
		}
		else
		{
			first[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < len1)
	{
		first[k] = left[i];
		k++;
		i++;
	}

	while (j < len2)
	{
		first[k] = right[j];
		k++;
		j++;
	}
}

template <typename T>
void timSort(T*first, T*last, bool(*compare)(const T, const T))
{
	
	for (int i = 0; i < last - first; i+=RUN)
		insertionSort(first, i, min((i + RUN - 1), int(last - first - 1)), compare);

	for (int size = RUN; size < last - first; size = 2 * size)
	{
		for (int left = 0; left < last - first; left += 2 * size)
		{
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (int(last - first) - 1));
			if(mid < right)
				merge(first, left, mid, right, compare);
		}
	}
}

template <typename T>
void printArray(T arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

/*int main()
{
	int arr[] = {-2, 7, 15, -14, 0, 15, 0, 7, -7,
					-4, -13, 5, 8, -14, 12};
	int n = sizeof(arr)/sizeof(arr[0]);
	printf("Given Array is\n");
	printArray(arr, n);

	timSort(arr, n);

	printf("After Sorting Array is\n");
	printArray(arr, n);
	return 0;
}*/