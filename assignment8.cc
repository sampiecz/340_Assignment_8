/***********************************************************
 CSCI 340 - Assignment 8 - Spring 2018
 
 Progammer: Sam Piecz
 Z-ID: Z1732715
 Section: 1
 TA: 
 Date Due: April 18, 2018 
 Purpose: 
 ************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "assignment8.h"

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

using namespace std;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}


/***************************************************************
  
 Name: Constructs hash table 

 Use: Constructs hash table 

 Parameters: 

 Returns: None. 

 ***************************************************************/
HT::HT()
{
    hTable = new vector<Entry>(11);
    table_size = 11;
    item_count = 0;
}

HT::HT( int size )
{
    hTable = new vector<Entry>(size);
    table_size = size;
    item_count = 0;
}


/***************************************************************
  
 Name: Desctructor 

 Use: Deletes hashtable object 

 Parameters: None 

 Returns: None. 

 ***************************************************************/
HT::~HT()
{
    delete hTable;
}


/***************************************************************
  
 Name: search 

 Use: Searches hash table for a value 

 Parameters: const string& key 

 Returns: None. 

 ***************************************************************/
int HT::search( const string& key )
{

    int hashKey =  hashing(key);
    // if the search is successful return the position
    for(; hashKey < table_size; hashKey++ )
    {
        Entry& accessEntryInTable = (*hTable)[hashKey];

        if( accessEntryInTable.key == "+++" || accessEntryInTable.key == Entry().key )
        {
            return -1;
        }
        
        if( accessEntryInTable.key == key )
        {
            return hashKey;
        }

    }

    return -1;

}


/***************************************************************
  
 Name: insert 

 Use: inserts a value into the hash table 

 Parameters: A constant reference to an entry object 

 Returns: None. 

 ***************************************************************/
bool HT::insert( const Entry& e )
{
	int hashKey = hashing(e.key);
	
	for(; hashKey < table_size; hashKey++)
	{
        Entry& accessEntryInTable = (*hTable)[hashKey]; 
		if(accessEntryInTable.key == Entry().key || accessEntryInTable.key == "+++")
		{
			item_count++;
            accessEntryInTable = e;
			return true;
		}
		if(accessEntryInTable.key == e.key)
		{
			cerr << "This key is already in the table." << endl; 
			return false;
		}
	}
	cerr << "Overflow error. This index is taken.";
	return false;
}


/***************************************************************
  
 Name: remove 

 Use: Removes a value from the hash table 

 Parameters: const string& s 

 Returns: None. 

 ***************************************************************/
bool HT::remove( const string& s )
{
    int hashKey = hashing(s);

    for(; hashKey < table_size; hashKey++)
    {
        Entry& accessEntryInTable = (*hTable)[hashKey];
        
        if(accessEntryInTable.key == "+++" || accessEntryInTable.key == Entry().key)
        {
            return false;
        }
        if(accessEntryInTable.key == s)
        {
            accessEntryInTable.key == "+++";
            item_count--;
            return true;
        }

    }

    return -1;
}


/***************************************************************
  
 Name: print method 

 Use: Prints index, key, and description. 

 Parameters: none 

 Returns: None. 

 ***************************************************************/
void HT::print()
{
    cout << "----Hash Table-----" << endl;

	for(int index = 0; index < table_size; index++)
	{
        Entry& accessEntryInIndex = (*hTable)[index];
        if(accessEntryInIndex.key == Entry().key || accessEntryInIndex.key == "+++")
        {
            continue;
        }

		cout << index << ": " << accessEntryInIndex.key << " " << accessEntryInIndex.description << endl;
	}


    cout << "-------------------" << endl;
}

/***************************************************************
  
 Name: get_entry 

 Use: Gets an entry. 

 Parameters: const string& line 

 Returns: None. 

 ***************************************************************/
Entry* get_entry ( const string& line )
{
    Entry* e = new Entry;
    e->key = line.substr(2,3);
    e->description = line.substr(6);
    return e;
}


/***************************************************************
  
 Name: get_key

 Use: Returns key 

 Parameters: A line containing all information needed to split key. 

 Returns: None. 

 ***************************************************************/
string get_key ( const string& line)
{
    return line.substr(2,3);
}


int main(int argc, char** argv ) {
    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }

    HT ht;
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;    
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) { 
            Entry* e = get_entry( line );
            ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);
            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 ) 
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;
 
    }

    infile.close();
    return 0;
}
