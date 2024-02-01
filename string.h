#ifndef STRING_H__
#define STRING_H__

#include <string.h>
#include <algorithm>

namespace magicstl {

class string {
private:
    char*  data_;
    size_t size_;
    size_t capacity_;

    unsigned short getlen(const char* str) {
        unsigned short len = 0;
        for (; str[len++]; );
        return len;
    }

public:
    string(const char* str = "");    // 通用构造函数
    string(const string&);           // 拷贝构造函数
    string& operator=(string&);
    char& operator[](size_t index);
    ~string();

    void swap(string&);
};

string::string(const char* str = "") : size_(getlen(str)), capacity_(size_) {
    data_ = new char[capacity_];
    memcpy(data_, str, size_);          // 将 char* 字符串交给 string 类托管，向上一层封装
}

string::string(const string& str) {
    string temp(str.data_);      // 调用通用构造函数
    swap(temp);                  // 深拷贝
}

string::~string() {
    if (data_) {
        delete [] data_;
        data_ = nullptr;
        size_ = capacity_ = 0;
    }
}

void string::swap(string& str) {
    std::swap(data_, str.data_);
    std::swap(size_, str.size_);
    std::swap(capacity_, str.capacity_);
}

string& string::operator=(string& str) {
    swap(str);
    return *this;
}

char& string::operator[](size_t index) {
    return data_[index];
}

}

#endif // !STRING_H__