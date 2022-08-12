#include "json/json.h"

#include <iostream>
#include <string>

int main() {
    Json::Value root;
    Json::Reader reader;
    const std::string json_data = R"({"name" : "Tony", "salary" : 100, "msg" : "您好", "files" : [ "1.ts", "2.txt" ]})";
    if (!reader.parse(json_data, root)) {
        std::cerr << "json parse failed\n";
        return 0;
    }

    std::string name = root["name"].asString();
    int salary = root["salary"].asInt();
    std::string msg = root["msg"].asString();
    std::cout << "name: " << name << " salary: " << salary;
    std::cout << " msg: " << msg << std::endl;
    std::cout << "enter files: \n";
    Json::Value files = root["files"];// read array here

    for (const auto &file : files) {
        std::cout << file.asString() << " ";
    }
    std::cout << std::endl;
}