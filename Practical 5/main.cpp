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
	std::string word = "";
	std::pair<std::string, int> pair;
	while (*ptr) {
		if (*ptr == '\\') {
			pair.first = word;
			pair.second = 1;
			vector.push_back(pair);
			word = "";
		}
		else {
			word.append(1, *ptr);
		}
		ptr++;
	}
}

void reduce(std::vector<std::pair<std::string, int>>) {
	std::vector<std::pair<std::string, int>>::iterator i;
	std::vector<std::pair<std::string, int>>::iterator j;
	//Sorting
	for (i = vector.begin(); i != vector.end(); i++) {
		for (j = i + 1; j != vector.end(); j++) {
			if (i->first != "SKIP" && j->second != 101) {
				i->first.append("\\" + j->first);
				i->second++;
			}
			else {
				result.push_back(std::make_pair(i->first,i->second));
				i = j;
			}
		}
	}

	i = result.begin();
	while (i != result.end()) {
		if (i->second == 101) {
			i = result.erase(i);
		}
		else {
			++i;
		}
	}
}

void longestPath(std::vector<std::pair<std::string, int>>) {
	std::vector<std::pair<std::string, int>>::iterator i;
	std::vector<std::pair<std::string, int>>::iterator j;
	std::string pathContent = "";
	int pathLength = 0;
	for (i = result.begin(); i != result.end(); i++) {
		for (j = i + 1; j != result.end(); j++) {
			if (j->second > i->second) {
				pathContent = j->first;
				pathLength = j->second;
			}
		}
	}
	std::cout << pathContent << "\t" << pathLength << std::endl;
}

int main() {
	std::vector<std::pair<std::string, int>>::iterator i;
	std::string data[] = { "F:\\Books\\Studies\\3rd\\Distributed Systems\\Prac\\",
						"F:\\Books\\Studies\\3rd\\Distributed Systems\\Prac\\Prac 4\\",
						"C:\\SDL Dev\\SDL2_ttf-devel-2.0.15-VC\\SDL2_ttf-2.0.15\\include\\" };

	for (int i = 0; i < 3; i++) {
		map(data[i].c_str());
		vector.push_back(std::make_pair("SKIP", 101));
	}
	std::cout << "Mapped Paths: \n";
	for (i = vector.begin(); i != vector.end(); i++) {
		std::string p1 = i->first;
		int p2 = i->second;
		std::cout << p1 << " " << p2 << "\n";
	}
	std::cout << std::endl;

	std::cout << "Reduced Paths: \n";
	reduce(vector);
	for (i = result.begin(); i != result.end(); i++) {
		std::string p1 = i->first;
		int p2 = i->second;
		std::cout << p1 << " " << p2 << "\n";
	}

	std::cout << std::endl;
	std::cout << "The longest path is: \n";
	longestPath(result);
	
	system("pause");
	return 0;
}