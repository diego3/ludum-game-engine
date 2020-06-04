#pragma once

#include <istream>
#include <string>
#include <fstream>
#include <stdio.h>

class FileUtil {

public:
	static std::string ReadFile(std::string filePath) {
		std::string content;
		std::string line;
		std::ifstream file(filePath);
		if (file.is_open()) {
			while (getline(file, line)) {
				content.append(line + "\n");
			}
		}
		file.close();
		return content;
	}
};