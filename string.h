#ifndef STRING_H__
#define STRING_H__

#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <sstream>

namespace magicstl {

class string {
private:
	char*  data_;      // 值
	size_t size_;      // 大小
	size_t capacity_;  // 容量

	unsigned short getlen(const char* str) const {
		unsigned short len = 0;
		for (; str[len++]; );
		return len;
	}

public:
	string();                    // 空构造函数

	string(const char*);         // 通用构造函数

	string(const string&);       // 拷贝构造函数

	string(const char*, size_t);

	~string();                   // 析构函数

	void swap(string&);          // 深拷贝

	char* begin() const;               // 迭代器

	char* end() const;

	const char* data() const;

	size_t size() const;

	size_t capacity() const;

	void recapacity(size_t newcapacity_);   // 调整字符串大小

	void clear();                           // 清空字符串

	void push_back(char ch);                // 追加字符

	void pop_back();                        // 删除最后一个字符

	void push_front(char ch);               // 追加到前面

	void pop_front();                       // 删除第一个字符

	void erase(size_t pos, size_t len);     // 删除字串

	void erase(size_t pos);                 // 删除字符

	bool empty() const;

	string substr(size_t pos, size_t len);  // 截取字串

	size_t find(const char*);               // 查找字串

	size_t find(string&);                   // 查找字串

	size_t count(const char*, size_t pos, size_t n);  // 统计字串出现的次数

	size_t count(string&, size_t pos, size_t n);      // 统计字串出线的次数

	// template <typename T> auto to_string(const T& value) -> string;

//	template <typename T> auto insert(size_t pos, const T&) -> string&;

	const char& operator[](const size_t index) const;         // 下标运算符

	// const auto operator[](const char* key) const;  // 字典查找
	/* string str = "hello world";
	str["hello"] " world"  // 字典查找 */

	string& operator=(const string& str);  // 赋值运算符

	string& operator=(const long long& value); 

	string& operator<<(const string& str);  // 左移运算符

	string& operator+(const string& str);
};

/* ******************************************************************************************* */
/* **************************** Implementation of class member functions ********************* */
/* ******************************************************************************************* */

/*  全局输入输出函数 */
std::ostream& operator<<(std::ostream& os, const string& str) {
	os << str.data();
	return os;
}

std::istream& operator>>(std::istream& is, string& str) {
	char _sRead[0x1FF] {};   // 缓冲区
	is >> _sRead;;
	str = _sRead;
	return is;
}
/*  结束全局输入输出函数 */


string::string() : size_(0), capacity_(1) {
	data_ = new char[capacity_];
	data_[size_] = '\0';
}

string::string(const char* str) : size_(strlen(str)), capacity_(getlen(str)) {
	data_ = new char[capacity_];
	strcpy_s(data_, capacity_, str);
}

string::string(const string& str) {
	string temp(str.data_);       // 调用 通用构造函数
	swap(temp);                   // 深拷贝
}

string::string(const char* str, size_t len) : size_(len), capacity_(len) {
	data_ = new char[capacity_];
	strcpy(data_, str);
}

string::~string() {
	if (data_) {
		delete[] data_;
		data_ = nullptr;
		size_ = capacity_ = 0;
	}
}

void string::swap(string& str) {
	std::swap(data_, str.data_);
	std::swap(size_, str.size_);
	std::swap(capacity_, str.capacity_);
}

char* string::begin() const {
	return data_;
}

char* string::end() const {
	return data_ + size_;
}

const char* string::data() const {
	return data_;
}

size_t string::size() const {
	return size_;
}

size_t string::capacity() const {
	return capacity_;
}

void string::recapacity(size_t newcapacity_) {
	if (newcapacity_ > capacity_) {
		char* newdata_ = new char[newcapacity_];  // 扩容
		strcpy_s(newdata_, capacity_, data_);     // 拷贝旧数据
		delete[] data_;                           // 删除旧数据
		data_ = newdata_;                         // 指向新数据
		capacity_ = newcapacity_;                 // 更新容量
	}
	size_ = strlen(data_);                         // 更新长度
}

void string::clear() {
	delete[] data_;
	data_ = nullptr;
	size_ = 0;
}

void string::push_back(char ch) {
	if (size_ + sizeof(ch) == capacity_) recapacity(capacity_ * 2);   // 扩容
	data_[size_++] = ch;
	data_[size_] = '\0';
}

void string::pop_back() {
	data_[--size_] = '\0';
}

void string::push_front(char ch) {
	if (size_ == capacity_) recapacity(capacity_ * 2);   // 扩容
//	insert(0, ch);
}

void string::pop_front() {
	memmove_s(data_, size_--, data_ + 1, size_);
	data_[size_--] = '\0';  // 注意和 pop_back() 中 size_ 变量的区别，i++ 和 ++i 的区别
}

void string::erase(size_t pos, size_t len) {
	if (len == 0) return;
	if (pos < 0 || pos > capacity_) throw std::logic_error(std::string("Input pos error."));
	memmove_s(data_ + pos, size_ - pos - len, data_ + pos + len, size_ - pos - len);
   	size_ -= len;
	data_[size_] = '\0';
}

void string::erase(size_t pos) {
	erase(pos, 1);      // 删除一个字符
}

bool string::empty() const {
	return size_ == 0;
}

string string::substr(size_t pos, size_t len) {
	if (pos > size_) pos = size_;
	if (pos + len > size_) len = size_ - pos;
	return string(data_ + pos, len);
}

size_t string::find(const char* str) {
	return strstr(data_, str) - data_;
}

size_t string::find(string& str) {
	return find(str.data_);
}

size_t string::count(const char* str, size_t pos, size_t n) {
	const char* p = data_ + pos;
	size_t count = 0;
	while ((p == strstr(p, str)) != NULL) {
		++count;
		p += n;
	}
	return count;
}

size_t string::count(string& str, size_t pos, size_t n) {
	return count(str.data_, pos, n);
}

/*
template <typename T> auto string::to_string(const T& value) -> string {
	std::ostringstream os;
	os << value;
	return os.str();
}


template <typename T> auto string::insert(size_t pos, const T& value) -> string& {
	if (pos < 0 || pos > capacity_) throw std::logic_error("Input pos error.");
	auto len = sizeof(to_string(value));
	if (size_ + len >= capacity_) recapacity(capacity_ * 2 + len); // 扩容
	for (int i = size_ - 1; i > pos; --i) {
		data_[i + len] = data_[i];
	}
	string temp(to_string(value));
	for (auto it = begin(); it != end(); ++it) {
		data_[pos++] = it;
	}
	size_ += len;
	data_[size_] = '\0';
	return *this;
}
*/

const char& string::operator[](const size_t index) const{
	if (index > size_) throw std::logic_error(std::string("The access array is out of the index"));
	return data_[index];
}

string& string::operator=(const string &str) {
	if (this == &str) return *this;
	string temp(str.data_);
	swap(temp);
	return *this;
}

string& string::operator=(const long long& value) {
	string temp(std::to_string(value));
	swap(temp);
	return *this;
}

string& string::operator<<(const string& str) {   // 注意 字符串结尾 \0 也算一个字符 
	unsigned short slen = getlen(str.data_);
	slen = size_ + slen - 1;
	if (size_ + slen >= capacity_) recapacity(capacity_ * 2 + slen); // 扩容
	memcpy(data_ + size_ -1, str.data_, slen - size_ + 1);
	size_ = slen;
	return *this;
}

string& string::operator+(const string& str) {
	/*
	string temp(*this);
	temp << str;
	return temp; */
	return *this << str;
}


} // namespace magicstl
#endif // !STRING_H__