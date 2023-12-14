#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "1805095_Scope_Table.h"
using namespace std;
class Symbol_Table
{
private:
    Scope_Table *current_scope_table;
    int table_size;
public:
    Symbol_Table(int n)
    {
        this->table_size = n;
        this->current_scope_table = new Scope_Table(table_size,nullptr);
        cout << "        ScopeTable#" << " 1" << " created" << endl;
    }
    void Enter_Scope(int n)
    {
        //create a new scope table and make it the current scope. Make the previous current scope as the parent of the new scope table.
        // cout<<" testttttttttttttttt: "<<current_scope_table->get_total_number_of_child()<<endl;
        current_scope_table->increment_total_number_of_child();
        int child_number = current_scope_table->get_total_number_of_child();
        Scope_Table *new_scope_table = new Scope_Table(n,this->current_scope_table);
        
        new_scope_table->set_parent_scope_table(this->current_scope_table);

        string child_number_string = to_string(child_number);
        string parent_scope_id = this->current_scope_table->get_scope_Id();
        string new_scope_id = parent_scope_id + "." + child_number_string;
        new_scope_table->set_scope_Id(new_scope_id);
        this->current_scope_table = new_scope_table;

        cout << "        ScopeTable# " << new_scope_id << " created" << endl;
    }
    void Exit_Scope(int flag)
    {
        Scope_Table *parent_scope_table = this->current_scope_table->get_parent_scope_table();
        if(parent_scope_table!=nullptr)
        {
            cout << "        ScopeTable# " << this->current_scope_table->get_scope_Id() << " deleted" << endl;
            delete this->current_scope_table;
            this->current_scope_table = parent_scope_table;
        }
        else if (flag==1)
        {
            cout << "        ScopeTable# " << this->current_scope_table->get_scope_Id() << " deleted" << endl;
            delete this->current_scope_table;
            this->current_scope_table = nullptr;
        }
        else
        {
            cout << "        ScopeTable# " << this->current_scope_table->get_scope_Id() << " cannot be deleted" << endl;
        }
    }
    bool Insert_from_symboltable(Symbol_Info *symbol_info)
    {
        if(this->current_scope_table==nullptr)
        {
            current_scope_table = new Scope_Table(table_size,nullptr);
        }
        if(current_scope_table->lookup_in_scopetable(symbol_info->get_Symbol_name())!=nullptr)
        {
            cout << "        <" << symbol_info->get_Symbol_name() << "," << symbol_info->get_Symbol_type() << "> already exists in current ScopeTable# " << current_scope_table->get_scope_Id() << endl;
            delete symbol_info;
            return false;
        }
        current_scope_table->Insert_in_scopetable(symbol_info);
        return true;
    }
    bool Remove_from_symboltable(string symbol_name)
    {
        Symbol_Info *current_Symbol = current_scope_table->lookup_in_scopetable(symbol_name);
        if(current_scope_table->Delete_in_scopetable(symbol_name))
        {
            // cout<< "Found in ScopeTable# " << current_scope_table->get_scope_Id() << " at position "<< current_Symbol->get_hash_position() << endl;
            // cout<< "Deleted entry at " << current_Symbol->get_hash_position() << " from current ScopeTable" << endl;
            return true;
        }
        else
        {
            // cout << symbol_name<< "Not found" << endl;
            return false;
        }
    }
    bool lookup_from_symboltable(string symbol_name)
    {
        Scope_Table *temp = this->current_scope_table;
        while (temp != nullptr)
        {
            Symbol_Info *current_Symbol = temp->lookup_in_scopetable(symbol_name);
            if(current_Symbol!=nullptr)
            {
                cout<< "found " << "at position "<< current_Symbol->get_hash_position() << "of ScopeTable# " << temp->get_scope_Id()<< endl;
                return true;
            }
            temp = temp->get_parent_scope_table();
        }
        cout <<"         '"<< symbol_name<<"'"<< " Not found in any of the ScopeTables" << endl;
        return false;
    }
    void print_current_scope_table()
    {
        if(this->current_scope_table!=nullptr)
            this->current_scope_table->Print_current_scopetable();
    }
    void print_all_scope_table()
    {
        Scope_Table *temp = this->current_scope_table;
        while (temp != nullptr)
        {
            temp->Print_current_scopetable();
            temp = temp->get_parent_scope_table();
        }
    }

    bool is_empty()
    {
        if(this->current_scope_table==nullptr)
        {
            // cout << "NO CURRENT SCOPE" << endl;
            return true;
        }
        return false;
    }

    ~Symbol_Table()
    {
        // if(current_scope_table->get_parent_scope_table()!=nullptr)
        //     delete current_scope_table->get_parent_scope_table();
        // delete current_scope_table;
    }
};

#endif  //SYMBOL_TABLE_H