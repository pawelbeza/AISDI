#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

#include "quick_sort.cpp"
#include "merge_sort.cpp"
#include "bubble_sort.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2){
		cout<<"File name parameter missing!\n";
		exit(EXIT_FAILURE);
	}
	ifstream inputFile(argv[1]);
	if(!inputFile.is_open()){
		cout<<"Could not open a file!\n";
		exit(EXIT_FAILURE);
	}
	vector <string> words1;
	string word;
	while(inputFile >> word){
		words1.push_back(word);
	}
	if(!inputFile.eof()){
		cout<<"Error while reading from file!\n";
		exit(EXIT_FAILURE);
	}
	inputFile.close();

    const int chunk = 10000;
    ofstream chart("chart.txt");
	for (int chunkSize = 0; chunkSize < words1.size(); chunkSize += chunk) {
		cout << "Number of sorted elements: " << chunkSize  << endl;
		chart << chunkSize << " ";

		vector<string> words[] {words1, words1, words1, words1};
		
		cout << "Execution time of merge sort: ";
		auto t11 = std::chrono::high_resolution_clock::now();	
		mergeSort(words[0].begin(), words[0].begin() + chunkSize);
		auto t12 = std::chrono::high_resolution_clock::now();

		auto dt1 = std::chrono::duration_cast<std::chrono::microseconds>(t12 - t11);
		cout << dt1.count() << endl;
		chart << dt1.count() << " ";

		cout << "Execution time of bubble sort: ";
		auto t21 = std::chrono::high_resolution_clock::now();	
		bubbleSort(words[1].begin(), words[1].begin() + chunkSize);
		auto t22 = std::chrono::high_resolution_clock::now();

		auto dt2 = std::chrono::duration_cast<std::chrono::microseconds>(t22 - t21);
		cout << dt2.count() << endl;
		chart << dt2.count() << " ";

        cout << "Execution time of quick sort: ";
		auto t31 = std::chrono::high_resolution_clock::now();	
		quickSort(words[2].begin(), words[2].begin() + chunkSize);
		auto t32 = std::chrono::high_resolution_clock::now();

		auto dt3 = std::chrono::duration_cast<std::chrono::microseconds>(t32 - t31);
		cout << dt3.count() << endl;
		chart << dt3.count() << " ";

		cout << "Execution time of STL sort:: ";
		auto t41 = std::chrono::high_resolution_clock::now();	
		sort(words[3].begin(), words[3].begin() + chunkSize);
		auto t42 = std::chrono::high_resolution_clock::now();

		auto dt4 = std::chrono::duration_cast<std::chrono::microseconds>(t42 - t41);
		cout << dt4.count() << endl << endl;
		chart << dt4.count() << std::endl;
	}

    quickSort(words1.begin(), words1.end());
	ofstream outputFile("output.txt");
	for(string word: words1){
		outputFile<<word<<endl;
	}
	outputFile.close();
}