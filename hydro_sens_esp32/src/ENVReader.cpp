// #include <ENVReader.h>

// std::string ENVReader::trim(const std::string& str) {
//     // Tìm vị trí ký tự không phải khoảng trắng đầu tiên
//     size_t first = str.find_first_not_of(" \t\n\r");
//     if (std::string::npos == first) {
//         return str;
//     }

//     size_t last = str.find_last_not_of(" \t\n\r");
//     return str.substr(first, (last - first + 1));
// }

// void ENVReader::parseLine(const std::string& line) {
//     std::string trimmed_line = trim(line);

//     // Bỏ qua dòng trống hoặc dòng comment
//     if (trimmed_line.empty() || trimmed_line[0] == '#') {
//         return;
//     }

//     // Tìm vị trí dấu "="
//     size_t delimiterPos = trimmed_line.find('=');
//     if (delimiterPos != std::string::npos) {
//         // Lấy KEY
//         std::string key = trimmed_line.substr(0, delimiterPos);
//         key = trim(key);

//         // Lấy VALUE
//         std::string value = trimmed_line.substr(delimiterPos + 1);
//         value = trim(value);

//         // Lưu vào map
//         if (!key.empty()) {
//             env_variables[key] = value;
//         }
//     }
// }

// ENVReader::ENVReader(const std::string& filename) {
//     // Khởi tạo SPIFFS
//     if (!SPIFFS.begin(true)) {
//         Serial.println("FATAL: SPIFFS Mount Failed!");
//         loaded = false;
//         return;
//     }
//     Serial.println("SPIFFS Mounted successfully.");

//     // Mở file
//     File file = SPIFFS.open(filename.c_str(), FILE_READ);
//     if (!file) {
//         Serial.print("FATAL: Failed to open file for reading: ");
//         Serial.println(filename.c_str());
//         SPIFFS.end();
//         loaded = false;
//         return;
//     }
    
//     // Đọc từng dòng và phân tích cú pháp
//     while (file.available()) {
//         std::string line = file.readStringUntil('\n').c_str(); 
//         parseLine(line);
//     }

//     // Đóng file và kết thúc
//     file.close();
//     SPIFFS.end(); 
//     loaded = true;
//     Serial.println("Environment variables loaded successfully.");
// }

// std::string ENVReader::get(const std::string& key) const {
//     if (env_variables.count(key)) {
//         return env_variables.at(key);
//     }
//     // Trả về chuỗi rỗng nếu không tìm thấy key
//     return "";
// }

#include <ENVReader.h>

String ENVReader::trim(const String& str) {
    String s = str;

    // Trim left
    int start = 0;
    while (start < s.length() && isspace(s[start])) start++;

    // Trim right
    int end = s.length() - 1;
    while (end >= 0 && isspace(s[end])) end--;

    if (start > end) return "";
    return s.substring(start, end + 1);
}

void ENVReader::parseLine(const String& line) {
    String trimmed_line = trim(line);

    // Bỏ qua dòng trống hoặc comment
    if (trimmed_line.length() == 0 || trimmed_line[0] == '#') {
        return;
    }

    int delimiterPos = trimmed_line.indexOf('=');
    if (delimiterPos != -1) {
        // Lấy key
        String key = trim(trimmed_line.substring(0, delimiterPos));

        // Lấy value
        String value = trim(trimmed_line.substring(delimiterPos + 1));

        if (key.length() > 0) {
            env_variables[key] = value;   // map<String,String>
        }
    }
}

ENVReader::ENVReader(const String& filename) {
    if (!SPIFFS.begin(true)) {
        Serial.println("Lỗi: SPIFFS mount thất bại!");
        loaded = false;
        return;
    }
    Serial.println("SPIFFS mount thành công.");

    File file = SPIFFS.open(filename, FILE_READ);
    if (!file) {
        Serial.print("Lỗi: Không thể mở file: ");
        Serial.println(filename);
        SPIFFS.end();
        loaded = false;
        return;
    }

    // Đọc từng dòng
    while (file.available()) {
        String line = file.readStringUntil('\n');
        parseLine(line);
    }

    file.close();
    SPIFFS.end();
    loaded = true;
    Serial.println("Các biến môi trường đã được tải thành công.");
}

String ENVReader::get(const String& key) const {
    if (env_variables.count(key)) {
        return env_variables.at(key);
    }
    return "";
}
