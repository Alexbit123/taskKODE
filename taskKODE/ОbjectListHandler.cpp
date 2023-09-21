#include "�bjectListHandler.h"

void �bjectListHandler::ParseQuery(std::string_view query) {
	Object object;
	int count = 0;
	while (count < QUERY_LENGTH) {
		auto it = query.find_first_of(" ");
		auto it_end = 0 + it;
		switch (count) {
		case 0: { object.name = query.substr(0, it_end); break; }
		case 1: { object.coord.x = std::stod(static_cast<std::string>(query.substr(0, it_end))); break; }
		case 2: { object.coord.y = std::stod(static_cast<std::string>(query.substr(0, it_end))); break; }
		case 3: { object.type_object = query.substr(0, it_end); break; }
		case 4: { object.time = std::stod(static_cast<std::string>(query.substr(0, std::string::npos))); break; }
		default:
			break;
		}
		query = query.substr(it_end + 1, std::string::npos);
		++count;
	}

	v.push_back(object);
}

void �bjectListHandler::SortByDistance() {
	for (auto& v : group_v) {
		std::sort(v.begin(), v.end(), [](Object& obj1, Object& obj2) {
			return Distance(obj1.coord) < Distance(obj2.coord);
			});
	}
}

void �bjectListHandler::SortByName() {
	for (auto& v : group_v) {
		std::sort(v.begin(), v.end(), [](Object& obj1, Object& obj2) {
			return obj1.name < obj2.name;
			});
	}
}

void �bjectListHandler::SortByTime() {
	for (auto& v : group_v) {
		std::sort(v.begin(), v.end(), [](Object& obj1, Object& obj2) {
			return obj1.type_object < obj2.type_object;
			});
	}
}

void �bjectListHandler::Read(std::ifstream& in) {
	while (!in.eof()) {
		std::string str;
		std::getline(in >> std::ws, str);
		ParseQuery(str);
	}
}

void �bjectListHandler::Save(std::ofstream& out) {
	for (auto& v : group_v) {
		for (auto& object : v) {
			out << object.name << " " << object.coord.x << " " << object.coord.y << " "
				<< object.type_object << " " << object.time << std::endl;
		}
		if (!v.empty()) {
			out << std::endl;
		}
	}
}

void �bjectListHandler::AddObject() {
	std::string str;
	std::cout << "������� ������ � ������� ����������_����������X_����������Y_����������_�������������, ��� _ ��� ������" << std::endl;
	std::getline(std::cin >> std::ws, str);
	ParseQuery(str);
}

void �bjectListHandler::GroupByDistance() {
	group_v.clear();
	group_v.reserve(4);
	group_v.resize(4);
	for (auto& object : v) {
		double dist = Distance(object.coord);
		if (dist < group_distance[0]) {
			group_v[0].push_back(object);					//�� 100
		}
		else if (dist < group_distance[1]) {
			group_v[1].push_back(object);					//�� 1000
		}
		else if (dist < group_distance[2]) {
			group_v[2].push_back(object);					//�� 10000
		}
		else {
			group_v[3].push_back(object);					//������� ������
		}
	}

	SortByDistance();
}

void �bjectListHandler::GroupByName() {
	group_v.clear();
	group_v.reserve(34);
	group_v.resize(34);
	for (auto& object : v) {
		auto result = std::find(group_name.begin(), group_name.end(), object.name[0]);
		if (result != group_name.end()) {
			group_v[result - group_name.begin()].push_back(object);				//������ ����� �� group_name
		}
		else {
			group_v[33].push_back(object);										//������ � ������ #
		}
	}

	SortByName();
}

void �bjectListHandler::GroupByCreationTime(std::tm& now) {
	group_v.clear();
	group_v.reserve(4);
	group_v.resize(4);
	for (auto& object : v) {
		auto time_object = GetDay(object.time);
		if (now.tm_year + 1900 == time_object.tm_year + 1900) {
			if (now.tm_mon + 1 == time_object.tm_mon + 1) {
				if (now.tm_mday == time_object.tm_mday) {
					group_v[0].push_back(object);					//�������
				}
				else {
					if (now.tm_mday == time_object.tm_mday - 1) {
						group_v[1].push_back(object);				//�����
					}
					else {
						group_v[2].push_back(object);				//� ���� ������
					}
				}
			}
			else {
				group_v[3].push_back(object);						//� ���� ����
			}
		}
		else {
			group_v[4].push_back(object);							//�����
		}
	}

	SortByTime();
	
}

void �bjectListHandler::GroupByType(int N) {
	group_v.clear();
	std::unordered_map<std::string, std::vector<Object>> result;
	size_t i = 0;

	for (auto& object : v) {
		result[object.type_object].push_back(object);
	}

	group_v.reserve(result.size());
	group_v.resize(result.size());

	for (auto& [key, value] : result) {
		if (result[key].size() > N) {
			group_v[i + 1] = std::move(value);
			++i;
		}
		else {
			for (auto& object : value) {
				group_v[0].push_back(std::move(object));						//[0] - ��� ������
			}
		}
	}

	SortByName();
}

double Distance(Coordinate& coord) {
	return std::fabs(coord.y - coord.x);
}

std::tm GetDay(double sec) {
	std::time_t t = sec;
	std::tm now;
	localtime_s(&now, &t);
	return now;
}
