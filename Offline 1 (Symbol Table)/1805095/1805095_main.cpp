#include "1805095_Symbol_Table.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int total_number_Of_Bucket;
    cin >> total_number_Of_Bucket;
    Symbol_Table *symbol_table = new Symbol_Table(total_number_Of_Bucket);

    char command;
    string symbol_name, symbol_type;
    string print_command;
    while (cin >> command)
    {
        switch(command)
        {
        case 'I':
            cin>> symbol_name >> symbol_type;
            cout<< "I " << symbol_name << " " << symbol_type << endl;
            symbol_table->Insert_from_symboltable(new Symbol_Info(symbol_name,symbol_type));
            // cout<<endl;
            break;
        case 'L':
            cin>> symbol_name;
            cout<< "L " << symbol_name << endl;
            symbol_table->lookup_from_symboltable(symbol_name);
            // cout<<endl;
            break;
        case 'D':
            cin>> symbol_name;
            cout<< "D " << symbol_name << endl;
            symbol_table->Remove_from_symboltable(symbol_name);
            // cout<<endl;
            break;
        case 'P':
            cin>> print_command;
            cout<< "P " << print_command << endl;
            if(print_command=="A")
            {
                symbol_table->print_all_scope_table();
            }
            else if(print_command=="C")
            {
                symbol_table->print_current_scope_table();
            }
            // cout<<endl;
            break;
        case 'S':
            cout<< "S" << endl;
            symbol_table->Enter_Scope(total_number_Of_Bucket);
            // cout<<endl;
            break;
        case 'E':
            cout<< "E" << endl;
            symbol_table->Exit_Scope();
            // cout<<endl;
            break;
        default:
            break;
        }
    }

    cout<< "Exiting program" << endl;
    delete symbol_table;
    return 0;
}
