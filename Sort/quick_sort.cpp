#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

template<typename IteratorType>
void quickSort(IteratorType first, IteratorType last)
{
	if (distance(first, last) <= 1)	return;

	auto i = first, j = last - 1;
	auto pivot = *(first + distance(first, last) / 2);
	while(distance(i, j) >= 0) {
		while (*i < pivot)
			i++;
		while (*j > pivot)
			j--;
		if (distance(i, j) >= 0) {
			iter_swap(i, j);
			i++;
			j--;
		}
	}
	// cout << j - i << endl << endl;
	quickSort(first, next(j));
	quickSort(i, last);
}