#pragma once
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace MagicSTL {
    class string {
    public:
        typedef char* iterator;

    private:
        char* m_pData;
        size_t m_nSize;        // 长度
        size_t m_nTotalSize;   // 容器大小

    public:
        string(const char* str = "");
        string(string& s);
        ~string();

        void swap(string&);
        string& operator=(string);
        char& operator[](size_t index);
        string& operator+(string& s);
        char* c_str();
        size_t size();
        size_t capacity();
        void reserve(size_t);
        size_t find(char* str, size_t index);
    };

    /***********************************/

    string::string(const char* str = "") : m_nSize(strlen(str)), m_nTotalSize(m_nSize) {
        m_pData = new char(m_nTotalSize);
        strcpy(m_pData, str);
    }

    string::string(string& s) {
        string temp(s.m_pData);   // 调用上面的构造函数
        swap(temp);                    // 深度拷贝
    }

    string::~string() {
        if (m_pData) {
            delete [] m_pData;
            m_pData = nullptr;
            m_nSize = m_nTotalSize = 0;
        }
    }

    void string::swap(string& s) {
        std::swap(m_pData, s.m_pData);
        std::swap(m_nSize, s.m_nSize);
        std::swap(m_nTotalSize, s.m_nTotalSize);
    }

    string& string::operator=(string s) {
        swap(s);
        return *this;
    }

    char& string::operator[](size_t index) {
        return m_pData[index];
    }

    string& string::operator+(string &s) {
        strcat(m_pData, s.c_str());
        return *this;
    }

    char* string::c_str() {
        return m_pData;
    }

    size_t string::size() {
        return m_nSize;
    }

    size_t string::capacity() {
        return m_nTotalSize;
    }

    void string::reserve(size_t n) {      // 重新分配大小
        if (n > m_nTotalSize) {
            char* temp = new char(n +  1);
            strcpy(temp, m_pData);
            delete [] m_pData;
            m_pData = temp;
            m_nTotalSize = n;
        }
    }

    size_t string::find(char* str, size_t index) {
        char* p = strstr(m_pData + index, str);
        if (p == nullptr) return -1;
        else return p - str;
    }

}