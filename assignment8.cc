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
#include "assignment8.h"

using std::cout;
using std::cerr;
using std::endl;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
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

/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
HT::HT()
{
    hTable = new vector<Entry>(11);
}

/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
HT::HT( int size )
{
    hTable = new vector<Entry>(size);
    table_size = size;
    item_count = 0;
}


/***************************************************************
  
 Name: Desctructor 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
HT::~HT()
{
    delete hTable;
}


/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
int HT::search( const string& key )
{

    int hashKey =  hasing(key.key);
    // if the search is successful return the position
    while( hashkey < hTable )
    {
        if( hTable[hashkey] == "---" )
        {
            return false;
        }
        
        if( hTable[hashkey] == key )
        {
            return hashKey;
        }

        hashkey++;

    }

    return -1;

}


/***************************************************************
  
 Name: 

 Use:  

 Parameters: 

 Returns: None. 

 ***************************************************************/
bool HT::insert( const Entry& e )
{
	int hashKey = hashing(e.key);
	
	for(int i = 0; i < table_size; i++)
	{
		if(hTable[hashKey].key == "---")
		{
	
			hTable[hashKey] = e;
			item_count++;
			return true;
		}
		if(hTable[hashKey].key != "---")
		{
			cerr << "This key is already in the table." << endl; 
			return false;
		}
	}
	cerr << "Overflow error. This index is taken.";
	return false;
}


/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
bool HT::remove( const string& s )
{
}


/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
void HT::print()
{
	for(int i = 0; i < table_size; i++)
	{
		// put a pointer to hTable maybe but its a data member???
		Entry entryObject = hTable[i];
		cout << "Key: " << entryObject.key << " " << "Description: " entryObject.description << endl;
	}
}

/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
Entry* get_entry ( const string& line )
{
    Entry* e new Entry;
    e-> key = line.substr(2,3);
    e->description = line.substr(5,8);
    return e;
}


/***************************************************************
  
 Name: 

 Use: 

 Parameters: 

 Returns: None. 

 ***************************************************************/
string get_key ( const string& line)
{
    return line.substr(2,3);
}
