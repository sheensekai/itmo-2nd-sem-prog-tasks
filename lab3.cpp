#include "lab3.h"
#include <iostream>

CIntStack::CIntStack(size_t size) :
    max_size(size),
    head(0),
    stack(new int[max_size])
    {}
CIntStack::CIntStack(CIntStack const & right) :
    max_size(right.max_size),
    head(right.head),
    stack(new int[max_size]) {
    for (int i = 0; i < head; i++)
        stack[i] = right.stack[i];
}

CIntStack::~CIntStack(){
    delete[] stack;
}

int CIntStack::push(int const & num) {
    if (head < max_size)
        stack[head++] = num;
    return (int)head;
}
int CIntStack::pop() {
    if (head > 0)
        return stack[--head];
    else return stack[0];
}
int CIntStack::pop(int const & num) {
    for (int i = 0; i < num; i ++)
        pop();
    if (head > 0)
        return stack[head];
    else return stack[0];
}
int CIntStack::popall() {
    head = 0;
    return stack[head];
}
int & CIntStack::back() {
    if (head > 0)
        return stack[head - 1];
    else return stack[0];
}
bool CIntStack::isempty() const {
    return !head;
}
int CIntStack::depth() const {
    return (int)head;
}
int CIntStack::size() const {
    return (int)max_size;
}

void CIntStack::output() {
    std::cout << "Stack :" << std::endl;
    for (int i = 0; i < head; i++)
        std::cout << stack[i] << " ";
    std::cout << std::endl;
}

CTXTFile::CTXTFile() :
    file(nullptr),
    file_name(""),
    open_mode(""),
    buffer_size(0),
    buffer(nullptr) {
}
CTXTFile::CTXTFile(std::string const & arg_name, std::string const & arg_mode) :
    file(nullptr),
    file_name(arg_name),
    open_mode(arg_mode),
    buffer_size(0),
    buffer(nullptr) {
    open(file_name, open_mode);
}
CTXTFile::~CTXTFile() {
    close();
    delete[] buffer;
}

int CTXTFile::open(std::string const & arg_name, std::string const & arg_mode) {
    if (file_name != arg_name)
        file_name = arg_name;
    if (open_mode != arg_mode)
        open_mode = arg_mode;
    file = fopen(file_name.c_str(), open_mode.c_str());

    if (file != nullptr) {

        if (buffer == nullptr) {
            buffer_size = 256;
            buffer = new char[buffer_size];
        }
        buffer[0] = '\0';

        return 0;
    } else return EOF;

}
void CTXTFile::close() {
    fclose(file);
}
int CTXTFile::reopen(std::string const & arg_mode) {
    close();
    return open(file_name, arg_mode);
}

bool CTXTFile::isopened() const {
    return file != nullptr;
}
bool CTXTFile::eof() const {
    return feof(file) != 0;
}
std::string CTXTFile::name() const {
    return file_name;
}
std::string CTXTFile::lastline() const {
    return (std::string)buffer;
}

std::string CTXTFile::readline() {
    int pos;
    char ch;
    for (pos = 0; pos < buffer_size && (ch = (char)fgetc(file)) != EOF && ch != '\n'; pos++)
        buffer[pos] = ch;
    buffer[pos] = '\0';

    return (std::string)buffer;
}
std::string CTXTFile::readword() {
    int pos = 0;
    char ch;
    while((ch = (char)fgetc(file)) == ' ' || ch == '\n');
    if (ch != EOF)
        buffer[pos++] = ch;
    for (; pos < buffer_size && (ch = (char)fgetc(file)) != EOF && ch != '\n' && ch != ' '; pos++)
        buffer[pos] = ch;
    buffer[pos] = '\0';

    return (std::string)buffer;
}

