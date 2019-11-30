#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

template<typename IteratorType>
void bubbleSort(IteratorType first, IteratorType last) {
	last--;
	for (;first != last; last--) {
		for (auto tmp = first; tmp != last; tmp++) {
			auto nastepny = next(tmp);
			if (*tmp > *nastepny)
				iter_swap(tmp, nastepny);
		}
	}
}

template<typename IteratorType>
void quickSort(IteratorType first, IteratorType last)
{
	if (distance(first, last) <= 1)	return;

	auto i = first, j = last - 1;
	auto pivot = *(first + distance(first, last) / 2);
	while(distance(i, j) > 0) {
		while (*i < pivot)
			i++;
		while (*j > pivot)
			j--;
		if (distance(i, j) > 0)
			iter_swap(i, j);
		if(distance(i, j) > 0 && *i == *j)
			j--;
	}

	quickSort(first, j);
	quickSort(next(i), last);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
			cout << "Wrong number of arguments" << endl;
			return 0;
	}
	ifstream inputFile(argv[1]);
	vector<string> words1;
	string word;

	while (inputFile >> word)	words1.push_back(word);
	
	for (int chunkSize = 1000; chunkSize <= 10000; chunkSize += 1000) {
		cout << "Number of sorted elements: " << chunkSize  << endl;

		vector<string> words[] {words1, words1, words1};
		
		cout << "Execution time of quick sort: ";
		auto t11 = std::chrono::high_resolution_clock::now();	
		quickSort(words[0].begin(), words[0].begin() + chunkSize);
		auto t12 = std::chrono::high_resolution_clock::now();

		auto dt1 = std::chrono::duration_cast<std::chrono::microseconds>(t12 - t11);
		cout << dt1.count() << endl;

		cout << "Execution time of bubble sort: ";
		auto t21 = std::chrono::high_resolution_clock::now();	
		bubbleSort(words[1].begin(), words[1].begin() + chunkSize);
		auto t22 = std::chrono::high_resolution_clock::now();

		auto dt2 = std::chrono::duration_cast<std::chrono::microseconds>(t22 - t21);
		cout << dt2.count() << endl;

		cout << "Execution time of STL sort:: ";
		auto t31 = std::chrono::high_resolution_clock::now();	
		sort(words[2].begin(), words[2].begin() + chunkSize);
		auto t32 = std::chrono::high_resolution_clock::now();

		auto dt3 = std::chrono::duration_cast<std::chrono::microseconds>(t32 - t31);
		cout << dt3.count() << endl << endl;
	}

	quickSort(words1.begin(), words1.end());
	ofstream output("output.txt");
	for (auto s : words1)	output << s << endl;
	output.close();
}
