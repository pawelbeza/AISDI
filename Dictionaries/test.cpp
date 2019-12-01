#include <cassert>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <unordered_set>

#include "AVLTreeDictionary.h"
#include "splayTreeDictionary.h"
#include "benchmark.h"

/*!
     * Inserts all words from input to AVL dictionary and STL map and check 
     * if values for given keys are the same
*/

template<typename Dictionary>
void insertTest(std::vector<std::string> &words, const std::string nameOFfOutput) {
    Dictionary dict;

    std::ofstream output(nameOFfOutput);
    const int toAdd = 1000;
    int chunkSize = 0;

    Benchmark<std::chrono::nanoseconds> b(false);
    for (int i = 0; i < words.size(); i++) {
        if (i == chunkSize) {
            std::cout << i << std::endl;
            output << chunkSize << ", " << b.elapsed()/double(chunkSize) << std::endl;
            chunkSize += toAdd;
        }
        std::string akt = words[i];
        dict.insert({akt, rand() % 1000});
    }
    output.close();
}

template<typename Dictionary>
void queryTest(std::vector<std::string> &words, const std::string nameOFfOutput) {
    const int toAdd = 5000;
    int chunkSize = 0;
    Dictionary dict;
    std::ofstream output(nameOFfOutput);
    for (int i = 0; i < words.size(); i++) {
        if (i == chunkSize) {
            std::cout << i << std::endl;
            Benchmark<std::chrono::nanoseconds> b(false);	
            for (int j = 0; j < i; j++)
                dict.find(words[j]);
            output << chunkSize << ", " << b.elapsed()/double(i) << std::endl;
            chunkSize += toAdd;
        }
        std::string akt = words[i];
        dict[akt] = dict[akt] + 1;
    }
    output.close();
}


void unit_test(std::vector<std::string> &words) {

    SplayTreeMap<std::string,int> splayDict;
    AVLTreeMap<std::string, int> avlDict;
    std::map<std::string, int> map;

    for (auto str : words) {
        avlDict[str]++;
        splayDict[str]++;
        map[str]++;
        assert(splayDict[str] == map[str]);
        assert(avlDict[str] == map[str]);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
			std::cout << "Wrong number of arguments" << std::endl;
			return 0;
	}

	std::ifstream inputFile(argv[1]);
	std::vector<std::string> words;
	std::string word;
	while (inputFile >> word)	words.push_back(word);

    unit_test(words);

    srand (time(NULL));
    insertTest<SplayTreeMap<std::string, int>>(words, "insertTime1.txt");
    insertTest<AVLTreeMap<std::string, int>>(words, "insertTime2.txt");
    insertTest<std::map<std::string, int>>(words, "insertTime3.txt");

    queryTest<SplayTreeMap<std::string, int>>(words, "queryTime1.txt");
    queryTest<AVLTreeMap<std::string, int>>(words, "queryTime2.txt");
    queryTest<std::map<std::string, int>>(words, "queryTime3.txt");
    return 0;
}