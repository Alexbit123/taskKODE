#pragma once

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <ctime>

#include "DataType.h"

constexpr int QUERY_LENGTH = 5;

constexpr std::array<int, 3> group_distance {100, 1000, 10000};
constexpr std::array<int, 33> group_name {'�', '�', '�', '�', '�', '�', '�', '�', '�', '�',
'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�',
'�', '�', '�', '�', '�'};

class �bjectListHandler {
private:
	std::vector<Object> v;
	std::vector<std::vector<Object>> group_v;

	void ParseQuery(std::string_view query);

	void SortByDistance();

	void SortByName();

	void SortByTime();

public:
	void Read(std::ifstream& in);

	void Save(std::ofstream& out);

	void AddObject();

	void GroupByDistance();

	void GroupByName();

	void GroupByCreationTime(std::tm& now);

	void GroupByType(int N);
};

double Distance(Coordinate& coord);

std::tm GetDay(double sec);
