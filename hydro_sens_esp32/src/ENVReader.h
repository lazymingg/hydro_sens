#ifndef ENV_READER_H
#define ENV_READER_H

#define MAX_LENGTH_VALUE 64

#include <Arduino.h>
#include <map>
#include <FS.h>           // Thư viện cơ bản cho File System
#include <SPIFFS.h>       // Thư viện cụ thể cho SPIFFS

class ENVReader {
private:
    std::map<String, String> env_variables;
    bool loaded = false;

    // Hàm tiện ích để phân tích cú pháp một dòng
    void parseLine(const String& line);

    // Hàm tiện ích để xóa khoảng trắng thừa ở hai đầu chuỗi
    String trim(const String& str);
public:
    ENVReader(const String& filename = "../.env");

    // Phương thức để lấy giá trị theo key
    String get(const String& key) const;
    
    // Phương thức kiểm tra xem các biến đã được tải thành công chưa
    bool isLoaded() const { return loaded; }
};

#endif // ENV_READER_H