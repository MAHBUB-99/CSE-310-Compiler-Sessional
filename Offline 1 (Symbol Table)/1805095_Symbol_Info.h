 #ifndef SYMBOL_INFO_H
#define SYMBOL_INFO_H

#include <iostream>
#include <string>
using namespace std;

class Symbol_Info
{
private:
    string symbol_name;
    string symbol_type;
    int hash_index;
    int hash_position;
    Symbol_Info *next_symbol_pointer;
public:
    Symbol_Info()
    {
        this->symbol_name = "";
        this->symbol_type = "";
        this->next_symbol_pointer = NULL;
    }
    Symbol_Info(string name, string type)
    {
        this->symbol_name = name;
        this->symbol_type = type;
        this->next_symbol_pointer = nullptr;
    }
    void set_Symbol_name(string name)
    {
        this->symbol_name = name;
    }
    string get_Symbol_name()
    {
        return this->symbol_name;
    }
    void set_Symbol_type(string type)
    {
        this->symbol_type = type;
    }
    string get_Symbol_type()
    {
        return this->symbol_type;
    }
    void set_hash_index(int hash_index)
    {
        this->hash_index = hash_index;
    }
    int get_hash_index()
    {
        return this->hash_index;
    }
    void set_hash_position(int hash_position)
    {
        this->hash_position = hash_position;
    }
    int get_hash_position()
    {
        return this->hash_position;
    }
    Symbol_Info* get_next_symbol_pointer()
    {
        return this->next_symbol_pointer;
    }
    void set_next_symbol_pointer(Symbol_Info *next_symbol_pointer)
    {
        this->next_symbol_pointer = next_symbol_pointer;
    }
    ~Symbol_Info()
    {
        this->symbol_name = "";
        this->symbol_type = "";
        this->next_symbol_pointer = nullptr;
    }
};

#endif // SYMBOL_INFO_H