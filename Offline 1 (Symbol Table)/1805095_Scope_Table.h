#ifndef SCOPE_TABLE_H 
#define SCOPE_TABLE_H

#include <iostream>
#include <string>
#include "1805095_Symbol_Info.h"
using namespace std;

class Scope_Table
{
private:
    string scope_Id;
    int total_number_of_buckets,total_number_of_child;
    Symbol_Info **chain_HashTable;
    Scope_Table *parent_scope_table;
public:
    Scope_Table(int n,Scope_Table *parent_scope)
    {
        this->total_number_of_buckets = n;
        this->total_number_of_child = 0;
        this->chain_HashTable = new Symbol_Info*[n];
        for (int i = 0; i < n; i++)
        {
            this->chain_HashTable[i] = nullptr;
        }
        this->parent_scope_table = parent_scope;
        if(parent_scope == nullptr)
        {
            this->scope_Id = "1";
        }
        else
        {
            this->scope_Id = parent_scope->scope_Id + "." + to_string(parent_scope->total_number_of_child);
            // parent_scope->total_number_of_child++;
        }
    }

    void set_scope_Id(string scope_Id)
    {
        this->scope_Id = scope_Id;
    }
    string get_scope_Id()
    {
        return this->scope_Id;
    }

    void set_total_number_of_buckets(int total_number_of_buckets)
    {
        this->total_number_of_buckets = total_number_of_buckets;
    }
    int get_total_number_of_buckets()
    {
        return this->total_number_of_buckets;
    }
    void increment_total_number_of_child()
    {
        this->total_number_of_child++;
    }
    int get_total_number_of_child()
    {
        return this->total_number_of_child;
    }

    void set_parent_scope_table(Scope_Table *parent_scope)
    {
        this->parent_scope_table = parent_scope;
    }
    Scope_Table* get_parent_scope_table()
    {
        return this->parent_scope_table;
    }



    unsigned long hash_function_sdbm(const char *str)
    {
        unsigned long hash = 0;
        int c;
        while (c=*str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return (hash % total_number_of_buckets);
    }   

    void Insert_in_scopetable(Symbol_Info *symbol)
    {
        string key=symbol->get_Symbol_name();
        int index=hash_function_sdbm(key.c_str());
        int position_in_chain=1;
        if(chain_HashTable[index]==NULL)    //no collision: insert at the beginning of the chain
        {
            chain_HashTable[index]=symbol;
            symbol->set_next_symbol_pointer(NULL);
            symbol->set_hash_index(index);
            symbol->set_hash_position(position_in_chain);
        }
        else    //collision: traverse and insert at the end of the chain
        {
            Symbol_Info *temp=chain_HashTable[index];
            while(temp->get_next_symbol_pointer()!=NULL)
            {
                temp=temp->get_next_symbol_pointer();
                position_in_chain++;
            }
            temp->set_next_symbol_pointer(symbol);
            symbol->set_next_symbol_pointer(NULL);
            symbol->set_hash_index(index);
            symbol->set_hash_position(position_in_chain+1);
        }
        cout << "        Inserted " << " at position <" << (index+1) << ", " << position_in_chain << "> of ScopeTable# " << scope_Id << endl;
        
    }

    Symbol_Info* lookup_in_scopetable(string symbol_name)
    {
        unsigned long hash_value = hash_function_sdbm(symbol_name.c_str());
        Symbol_Info *temp = chain_HashTable[hash_value];
        int position_in_chain = 0;
        while (temp != nullptr)
        {
            if(temp->get_Symbol_name() == symbol_name)
            {
                // cout <<"         '"<<symbol_name<<"'"<< "found at position <" << hash_value << ", " << position_in_chain << "> of ScopeTable# " << scope_Id << endl;
                return temp;
            }
            position_in_chain++;
            temp = temp->get_next_symbol_pointer();
        }
        // cout << "Not found" << endl;
        return nullptr;
    }

    bool Delete_in_scopetable(string symbol_name)    //delete a symbol from the current scope table
    {
        unsigned long index = hash_function_sdbm(symbol_name.c_str());
        Symbol_Info *temp = chain_HashTable[index];

        if(lookup_in_scopetable(symbol_name) == nullptr)  //if the symbol is not found in the current scope table
        {
            cout << "        Not found in the current scopeTable# "<< scope_Id << endl;
            return false;
        }
        else if(temp->get_Symbol_name() == symbol_name && temp->get_next_symbol_pointer()==nullptr)    //if the symbol is in the first position of the chain
        {
            cout << "        Deleted "<<"'"<<symbol_name<<"'" << " from position"<<"<"<<(temp->get_hash_index()+1)<<", "<< temp->get_hash_position() <<">"<<" ScopeTable#" <<scope_Id<< endl;
            delete temp;
            chain_HashTable[index] = nullptr;
            return true;
        }
        //has chain and if the symbol is in the middle or at the end of the chain
        Symbol_Info *previous = chain_HashTable[index];
        int c=0;
        while(temp->get_Symbol_name() != symbol_name && temp->get_next_symbol_pointer()!=nullptr)
        {
            previous = temp;
            temp = temp->get_next_symbol_pointer();
            c++;
        }
        //if the symbol is found in the middle of the chain
        if(temp->get_Symbol_name() == symbol_name && temp->get_next_symbol_pointer()!=nullptr)
        {
            if(c==0)
            {
                chain_HashTable[index] = temp->get_next_symbol_pointer();
                
            }
            previous->set_next_symbol_pointer(temp->get_next_symbol_pointer());
            temp->set_next_symbol_pointer(nullptr);
            delete temp;
            return true;
        }
        //if the symbol is found at the end of the chain
        else 
        {
            previous->set_next_symbol_pointer(nullptr);
            temp->set_next_symbol_pointer(nullptr);
            delete temp;
            return true;
        }
        return false;
    }

    void Print_current_scopetable()    //print the current scope table
    {
        cout << "        ScopeTable# " << this->scope_Id << endl;
        for (int i = 0; i < total_number_of_buckets; i++)
        {
            cout << "        " << (i+1) ;
            Symbol_Info *temp = chain_HashTable[i];
            while (temp != nullptr)
            {
                cout << " --> " << "(" << temp->get_Symbol_name() << "," << temp->get_Symbol_type() << ")";
                temp = temp->get_next_symbol_pointer();
            }
            cout << endl;
        }
    }

    ~Scope_Table()
    {
        this->scope_Id = "";
        this->total_number_of_child = 0;
        // this->parent_scope_table = nullptr;
        for (int i = 0; i < total_number_of_buckets; i++)
        {
            Symbol_Info *temp = chain_HashTable[i];
            while (temp)
            {
                Symbol_Info *temp_next_in_chain = temp->get_next_symbol_pointer();
                delete temp;
                temp = temp_next_in_chain;
            }
        }
        delete[] chain_HashTable;
    }
};

#endif // SCOPE_TABLE_H