#ifndef PROGTASKSCPP_LAB3_H
#define PROGTASKSCPP_LAB3_H

#include <cstddef>
#include <cstdio>
#include <string>

// Стек целых чисел
class CIntStack {
public:
    explicit CIntStack(size_t size = 10);
    CIntStack(CIntStack const & right);
    ~CIntStack();

    int push(int const & num = 0);
    int pop();
    int pop(int const & num);
    int popall();
    int & back();

    bool isempty() const;
    int depth() const;
    int size() const;

    void output();

private:
    size_t max_size;
    size_t head;
    int * stack;
};
class CTXTFile {
public:
    CTXTFile();
    explicit CTXTFile(std::string const & name, std::string const & mode = "r+");
    ~CTXTFile();

    int open(std::string const & arg_name, std::string const & arg_mode = "r+");
    int reopen(std::string const & mode = "r+");
    void close();

    bool isopened() const;
    bool eof() const;
    std::string name() const;
    std::string lastline()const ;

    std::string readline();
    std::string readword();

private:
    FILE * file;
    std::string file_name;
    std::string open_mode;

    char * buffer;
    size_t buffer_size;
};


#endif //PROGTASKSCPP_LAB3_H
