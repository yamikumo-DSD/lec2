//triangle_area.cpp

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

int main(void)
{
	static constexpr auto ELEMENT_NUM = 5;
	double length[ELEMENT_NUM] = { 0.0 }, higher[ELEMENT_NUM] = {0.0};

	ifstream fin("foo.txt");

	if (!fin)
	{
		cout << "入力ファイルを開けません\n";
		return 1;
	}

	int i = 0;
	while (!fin.eof() && i < ELEMENT_NUM)
	{
		string line;
		getline(fin, line);
		sscanf(line.c_str(), "%lf,%lf", length + i, higher + i);
		++i;
	}

	for (int j = 0; j != ELEMENT_NUM; ++j)
	{
		cout << "Base length=" << length[j] << ", Height=" << higher[j] << " -> " << length[j] * higher[j] * 0.5 << endl;
	}
}
