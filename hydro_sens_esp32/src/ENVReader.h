#ifndef ENV_READER_H
#define ENV_READER_H

#include <map>
#include <string>
#include <FS.h>           // Thư viện cơ bản cho File System
#include <SPIFFS.h>       // Thư viện cụ thể cho SPIFFS
#include <Arduino.h>

class ENVReader {
private:
    std::map<std::string, std::string> env_variables;
    bool loaded = false;

    // Hàm tiện ích để phân tích cú pháp một dòng
    void parseLine(const std::string& line);

    // Hàm tiện ích để xóa khoảng trắng thừa ở hai đầu chuỗi
    std::string trim(const std::string& str);

public:
    ENVReader(const std::string& filename = "../.env");

    // Phương thức để lấy giá trị theo key
    std::string get(const std::string& key) const;
    
    // Phương thức kiểm tra xem các biến đã được tải thành công chưa
    bool isLoaded() const { return loaded; }
};

#endif // ENV_READER_H
