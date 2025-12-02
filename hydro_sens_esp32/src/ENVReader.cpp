#include "ENVReader.h"

std::string ENVReader::trim(const std::string& str) {
    const std::string whitespace = " \t\n\r";
    size_t start = str.find_first_not_of(whitespace);
    if (std::string::npos == start) {
        return "";
    }
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

void ENVReader::parseLine(const std::string& line) {
    size_t delimiter_pos = line.find('=');
    if (delimiter_pos == std::string::npos || delimiter_pos == 0) {
        return; 
    }

    std::string key = line.substr(0, delimiter_pos);
    std::string value = line.substr(delimiter_pos + 1);

    key = trim(key);
    value = trim(value);
    
    if (!key.empty()) {
        env_variables[key] = value;
    }
}

ENVReader::ENVReader(const std::string& filename) {
    if (!SPIFFS.begin(true)) {
        Serial.println("Error: Init SPIFFS failed!");
        loaded = false;
        return;
    }

    File file = SPIFFS.open(filename.c_str(), FILE_READ);
    if (!file) {
        Serial.printf("Warning: Cannot open file ENV: %s\n", filename.c_str());
        loaded = false;
        return;
    }

    String line;
    while (file.available()) {
        line = file.readStringUntil('\n');
        
        std::string trimmed_line = trim(line.c_str());

        if (trimmed_line.empty() || trimmed_line[0] == '#') {
            continue;
        }

        parse_line(trimmed_line);
    }
    
    file.close();
    loaded = true;
    Serial.printf("Done loading ENV: %s\n", filename.c_str());
}

std::string ENVReader::get(const std::string& key) const {
    auto it = env_variables.find(key);
    if (it == env_variables.end()) {
        // Trên hệ thống nhúng (Embedded System) như ESP32, 
        // thường tránh dùng exception. Thay vào đó, trả về chuỗi rỗng 
        // hoặc dùng hàm get_with_default.
        return "";
    }
    return it->second;
}
