#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <utility>

std::vector<std::pair<std::string, int>> vector;
std::vector<std::pair<std::string, int>> result;

void map(const char *ptr) {
	//Mapping to seperate
	int num = 0;
	std::string word="";
	std::pair<std::string, int> pair;
	while (*ptr) {
		if (*ptr == ' ') {
			pair.first = word;
			pair.second = 1;
			vector.push_back(pair);
			word = "";
		}
		else{
			word.append(1,*ptr);
		}
		ptr++;
	}
}

void reduce(std::vector<std::pair<std::string, int>>) {
	std::vector<std::pair<std::string, int>>::iterator i;
	std::vector<std::pair<std::string, int>>::iterator j;
	//Sorting
	for(i = vector.begin(); i != vector.end(); i++) {
		result.push_back(std::make_pair(i->first,i->second));
		for (j = i + 1; j != vector.end(); j++) {
			if (i->first == j->first && j->second==1) {
				result.push_back(std::make_pair(j->first, j->second));
				j->first = "";
				j->second = 0;
			}
		}
		i->first = "";
		i->second = 0;
	}
	i = result.begin();
	while (i != result.end()) {
		if (i->second == 0) {
			i = result.erase(i);
		}
		else {
			++i;
		}
	}
	//Printing out the Sorted Map
	std::cout << "Sorted map: \n";
	for (i = result.begin(); i != result.end(); i++) {
		std::string p1 = i->first;
		int p2 = i->second;
		std::cout << p1 << " " << p2 << "\n";
	}

	//Reduce
	for (i = result.begin(); i != result.end(); i++) {
		for (j = i + 1; j != result.end(); j++) {
			if (i->first == j->first) {
				i->second++;
				result.erase(j--);
			}
		}
	}
}

int main() {
	//Data needs to have a " " at the end or it will miss the last word.
	char data[] = "TEST REE TEST FREE BEE KNEES FREEZE TEST REE REE BEE WEE KNEES ";
	if (*data == NULL) {
		std::cout << "EMPTY CHARS!";
		return 0;
	}
	else {
		map(data);
	}
	std::cout << "Mapping result: \n";
	std::vector<std::pair<std::string, int>>::iterator i;
	for (i = vector.begin(); i != vector.end(); i++){
		std::string p1 = i->first;
		int p2 = i->second;
		std::cout << p1 << " " << p2 << "\n";
	}
	std::cout << "\n";
	/*if (vector.begin() != vector.begin() + 1) {
		it
	}*/
	reduce(vector);
	std::cout << "\nReduced map: \n";
	for (i = result.begin(); i != result.end(); i++) {
		std::string p1 = i->first;
		int p2 = i->second;
		std::cout << p1 << " " << p2 << "\n";
	}

	system("pause");
	return 0;
}