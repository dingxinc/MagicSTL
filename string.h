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

    unsigned short getlen(const char* str) const {
        unsigned short len = 0;
        for (; str[len++]; );
        return len;
    }

public:
    string(const char* str);    // 通用构造函数

    string(const char* str, size_t len);

    string(const string&);           // 拷贝构造函数

    string& operator=(string&);      // 赋值运算符

    ~string();

    char& operator[](size_t index);  // 下标运算符

    void swap(string&);              // 深拷贝

    size_t find(const char* str);  // 查找子串

    size_t count(const char* str, size_t pos, size_t n);  // 统计子串出现次数

    size_t size() const;  // 获取字符串长度

    size_t capacity() const;  // 获取字符串容量

    const char* data() const;  // 获取字符串指针

    void resize(size_t new_size);  // 调整字符串长度

    void clear();  // 清空字符串

    void push_back(char ch);  // 追加字符

    void pop_back();  // 删除最后一个字符

    void assign(const char* str);  // 赋值字符串

    void insert(size_t pos, const char* str);  // 插入字符串

    void insert(size_t pos, const char* str, size_t len);  // 插入字符串

    void insert(size_t pos, char ch);  // 插入字符

    void erase(size_t pos, size_t len);  // 删除子串

    void erase(size_t pos);  // 删除字符

    string substr(size_t pos, size_t len) const;  // 截取子串

    bool empty() const;  // 判断是否为空字符串

    bool operator==(const string&) const;  // 判断是否相等

    bool operator!=(const string&) const;  // 判断是否不等

    bool operator<(const string&) const;  // 判断是否小于

    bool operator<=(const string&) const;  // 判断是否小于等于

    bool operator>(const string&) const;  // 判断是否大于

    bool operator>=(const string&) const;  // 判断是否大于等于

    string& operator<<(const string& str);  // 左移运算符

    string& operator>>(string& str);  // 右移运算符

    string& operator+=(const string& str);  // 加等于运算符

    string& operator-=(const string& str);  // 减等于运算符
};

/* ******************************************************************************************* */
/* **************************** Implementation of class member functions ********************* */
/* ******************************************************************************************* */

string::string(const char* str) : size_(getlen(str)), capacity_(size_) {
    data_ = new char[capacity_];
    memcpy(data_, str, size_);          // 将 char* 字符串交给 string 类托管，向上一层封装
}


string::string(const char* str, size_t len) : size_(len), capacity_(len) {
    data_ = new char[capacity_];
    memcpy(data_, str, size_);
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


size_t string::find(const char* str) {
    return strstr(data_, str) - data_;
}


size_t string::count(const char* str, size_t pos, size_t n) {
    const char* p = data_ + pos;
    size_t count = 0;
    while ((p = strstr(p, str)) != nullptr) {
        ++count;
        p += n;
    }
    return count;
}


size_t string::size() const {
    return size_;
}

size_t string::capacity() const {
    return capacity_;
}


const char* string::data() const {
    return data_;
}


void string::resize(size_t new_size) {
    if (new_size > capacity_) {
        char* new_data = new char[new_size];       // 扩容
        memcpy(new_data, data_, size_);// 拷贝旧数据
        delete [] data_;                           // 删除旧数据
        data_ = new_data;                          // 指向新数据
        capacity_ = new_size;                       // 更新容量
    }
    size_ = new_size;    // 更新长度
}


void string::clear() {
    size_ = 0;
}


void string::push_back(char ch) {
    if (size_ == capacity_) {
        resize(capacity_ * 2);  // 扩容
    }
    data_[size_++] = ch;
}


void string::pop_back() {
    --size_;
}


void string::assign(const char* str) {
    string temp(str);
    swap(temp);
}


void string::insert(size_t pos, const char* str) {
    insert(pos, str, getlen(str));
}


void string::insert(size_t pos, const char* str, size_t len) {
    if (len == 0) {
        return;
    }
    if (size_ + len > capacity_) {
        resize(size_ + len);
    }
    memmove(data_ + pos + len, data_ + pos, size_ - pos);
    memcpy(data_ + pos, str, len);
    size_ += len;
}


void string::insert(size_t pos, char ch) {
    insert(pos, &ch, 1);
}


void string::erase(size_t pos, size_t len) {
    if (len == 0) {
        return;
    }
    memmove(data_ + pos, data_ + pos + len, size_ - pos - len);
    size_ -= len;
}


void string::erase(size_t pos) {
    erase(pos, 1);
}


string string::substr(size_t pos, size_t len) const {
    if (pos > size_) {
        pos = size_;
    }
    if (pos + len > size_) {
        len = size_ - pos;
    }
    return string(data_ + pos, len);
}


bool string::empty() const {
    return size_ == 0;
}


bool string::operator==(const string& str) const {
    return size_ == str.size_ && memcmp(data_, str.data_, size_) == 0;
}


bool string::operator!=(const string& str) const {
    return !(*this == str);
}


bool string::operator<(const string& str) const {
    return std::lexicographical_compare(data_, data_ + size_, str.data_, str.data_ + str.size_);
}


bool string::operator<=(const string& str) const {
    return *this < str || *this == str;
}


bool string::operator>(const string& str) const {
    return !(*this <= str);
}


bool string::operator>=(const string& str) const {
    return !(*this < str);
}


string& string::operator<<(const string& str) {
    // insert(size_, str.data_, str.size_);
    // return *this;    // 左移运算符返回左侧对象 
    unsigned short len = getlen(str.data_);
    if (size_ + len > capacity_) {
        resize(size_ + len);
    }
    memcpy(data_ + size_, str.data_, len);
    size_ += len;
    return *this;
}


string& string::operator>>(string& str) {
    // str = substr(0, size_);
    // resize(0);
    // return str;    // 右移运算符返回右侧对象
    str = *this;
    resize(0);
    return str;
}

string& string::operator+=(const string& str) {
    // insert(size_, str.data_, str.size_);
    // return *this;    // 加等于运算符返回左侧对象
    unsigned short len = getlen(str.data_);
    if (size_ + len > capacity_) {   // 扩容
        resize(size_ + len);
    }
    memcpy(data_ + size_, str.data_, len);   // 拷贝新数据
    size_ += len;
    return *this;   
}


string& string::operator-=(const string& str) {
    size_t pos = find(str.data_);
    if (pos != string::npos) {
        erase(pos, str.size_);
    }
    return *this;
}     

}

#endif // !STRING_H__