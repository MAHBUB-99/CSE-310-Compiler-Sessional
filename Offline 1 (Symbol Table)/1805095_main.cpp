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
    int command_counter=0;
    while (cin >> command)
    {
        command_counter+=1;
        switch(command)
        {
        case 'I':
            cin>> symbol_name >> symbol_type;
            cout<< "Cmd " <<command_counter << ": I " << symbol_name << " " << symbol_type << endl;
            symbol_table->Insert_from_symboltable(new Symbol_Info(symbol_name,symbol_type));
            // cout<<endl;
            break;
        case 'L':
            cin>> symbol_name;
            cout<< "Cmd " <<command_counter << ": L " << symbol_name << endl;
            symbol_table->lookup_from_symboltable(symbol_name);
            // cout<<endl;
            break;
        case 'D':
            cin>> symbol_name;
            cout<< "Cmd " <<command_counter << ": D " << symbol_name << endl;
            symbol_table->Remove_from_symboltable(symbol_name);
            // cout<<endl;
            break;
        case 'P':
            cin>> print_command;
            cout<< "Cmd " <<command_counter << ": P " << print_command << endl;
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
            cout<< "Cmd " <<command_counter << ": S" << endl;
            symbol_table->Enter_Scope(total_number_Of_Bucket);
            // cout<<endl;
            break;
        case 'E':
            cout<< "Cmd " <<command_counter << ": E" << endl;
            symbol_table->Exit_Scope(0);
            // cout<<endl;
            break;
        case 'Q':
            cout<< "Cmd " <<command_counter << ": Q" << endl;
            while(symbol_table->is_empty()==false)
            {
                symbol_table->Exit_Scope(1);
            }
            break;
        default:
            break;
        }
    }

    // cout<< "Exiting program" << endl;
    delete symbol_table;
    return 0;
}
