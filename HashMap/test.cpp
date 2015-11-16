#include <cstdlib>
#include <iostream>
#include <string>
#include "HashMap_v1p.h"
#include "HashMap_v2p.h"
using namespace std;

void checkSet(bool b){
	if(b){
		printf("%s\n","Set operation was successful.");
		//cout << value << endl;
	}else{
		printf("%s\n","Set operation was NOT successful.");
		//cout << value << endl;
	}
}
void checkGet(bool b){
	if(b){
		printf("%s\n","Set operation was successful.");
		//cout << value << endl;
	}else{
		printf("%s\n","Set operation was NOT successful.");
		//cout << value << endl;
	}
}

int main(int argc, char** argv){
	// Usage: ./test (defaults to running HashMap_v1.h)
	int flag = 1;
	if(argc == 2){
		flag = atoi(argv[1]);
	}
	if(argc > 2 || flag > 2){
		cout << "Usage: " << argv[0] << " (1-2)" << endl;
		return 1;
	}


	// Setting up testing parameters
	// Array of test keys
	string strArray[] = {"hello", "hola", "ni hao", 
		"bonjour", "konnichiwa", "annyeonghaseyo", 
		"ciao", "kamusta", "hallo", "zdravstvuyte", 
		"ola", "dia duit", "sain uu", "ahoj", "namaste"};
	string strArray2[] = {"annyeonghaseyo", 
		"ciao", "kamusta", "zdravstvuyte", 
		"dia duit", "sain uu", "ahoj", "namaste"};
	string strArray3[] = {"hello", "hola", "ni hao", 
		"bonjour", "konnichiwa", "hallo",  
		"ola", "sain uu", "ahoj", "namaste"};

	// Array of int values
	int sizeArray = 15;
	int* intArray = new int [sizeArray];
	for(int i = 0; i < sizeArray; i++){
		intArray[i] = i*2;
	}



	// Testing module for HashMap_v1p.h
	if(flag == 1){
		// Testing hash_map when empty
		//HashMap<string, int> hash_map_test0(0);
		//HashMap<string, int> hash_map_test1(1);
		HashMap<string, int> hash_map(10);

		// Testing set, get, and load operations
		cout << "Testing set, get, and load operations" << endl;
		for(int i = 0; i < sizeArray; i++){
			bool b = hash_map.set(strArray[i], &intArray[i]);
			checkSet(b);
			if(b)
				cout << *(hash_map.get(strArray[i])) << endl;
			cout << "Load factor: " << hash_map.load() << endl;
		}
		cout << endl;
		
		// Testing printHashMap operation
		cout << "Testing printHashMap operation" << endl;
		hash_map.printHashMap();
		cout << endl;

		// Testing get operation
		cout << "Testing get operation" << endl;
		for(int i = 0; i < sizeArray; i++){
			string keyStr = strArray[i];
			int* valPtr = hash_map.get(keyStr);
			if(valPtr != NULL){
				cout << keyStr << " -> " << *valPtr << endl;
			}else{
				cout << "Key " << keyStr << " is invalid." << endl;
			}
		}
		cout << endl;

		// Test set->update operation
		cout << "Testing set->update operation" << endl;
		for(int i = 0; i < 10; i++){
			string keyStr = strArray3[i];
			hash_map.set(keyStr, &intArray[14-i]);
			cout << keyStr << " -> " << *hash_map.get(keyStr) << endl;
			cout << "Load factor: " << hash_map.load() << endl;			
			cout << endl;
		}
		cout << "HashMap:" << endl;
		hash_map.printHashMap();
		cout << endl;

		// Testing remove/delete, load, and printHashMap operations
		cout << "Testing remove/delete, load, and printHashMap operations" << endl;
		for(int i = 0; i < sizeArray; i++){
			string keyStr = strArray[i];
			int* valPtr = hash_map.remove(keyStr);
			if(valPtr != NULL){
				cout << keyStr << " -> " << *valPtr << endl;
			}else{
				cout << "Key " << keyStr << " is invalid." << endl;
			}
			cout << "Load factor: " << hash_map.load() << endl;
			cout << endl;

			cout << "HashMap:" << endl;
			hash_map.printHashMap();
			cout << endl;
		}

		// Add the 'unsuccessful keys'
		cout << "Adding the 'unsuccessful' keys" << endl;
		for(int i = 0; i < 8; i++){
			bool b = hash_map.set(strArray2[i], &intArray[i]);
			checkSet(b);
			if(b)
				cout << *(hash_map.get(strArray2[i])) << endl;
			cout << "Load factor: " << hash_map.load() << endl;
			cout << endl;
		}
		cout << "HashMap:" << endl;
		hash_map.printHashMap();
		cout << endl;
	}


	// Testing module for HashMap_v2p.h
	if(flag == 2){
		// Testing hash_map when empty
		//HashMap<string, int> hash_map_test0(0);
		//HashMap<string, int> hash_map_test1(1);
		HashMap2<string, int> hash_map(10);

		// Testing set, get, and load operations
		cout << "Testing set, get, and load operations" << endl;
		for(int i = 0; i < sizeArray; i++){
			bool b = hash_map.set(strArray[i], &intArray[i]);
			checkSet(b);
			if(b)
				cout << *(hash_map.get(strArray[i])) << endl;
			cout << "Load factor: " << hash_map.load() << endl;
		}
		cout << endl;
		
		// Testing printHashMap operation
		cout << "Testing printHashMap operation" << endl;
		hash_map.printHashMap();
		cout << endl;

		// Testing get operation
		cout << "Testing get operation" << endl;
		for(int i = 0; i < sizeArray; i++){
			string keyStr = strArray[i];
			int* valPtr = hash_map.get(keyStr);
			if(valPtr != NULL){
				cout << keyStr << " -> " << *valPtr << endl;
			}else{
				cout << "Key " << keyStr << " is invalid." << endl;
			}
		}
		cout << endl;

		// Test set->update operation
		cout << "Testing set->update operation" << endl;
		for(int i = 0; i < sizeArray; i++){
			string keyStr = strArray3[i];
			hash_map.set(keyStr, &intArray[14-i]);
			cout << keyStr << " -> " << *hash_map.get(keyStr) << endl;
			cout << "Load factor: " << hash_map.load() << endl;			
			cout << endl;
		}
		cout << "HashMap:" << endl;
		hash_map.printHashMap();
		cout << endl;

		// Testing remove/delete, load, and printHashMap operations
		cout << "Testing remove/delete, load, and printHashMap operations" << endl;
		for(int i = 0; i < sizeArray; i++){
			string keyStr = strArray[i];
			int* valPtr = hash_map.remove(keyStr);
			if(valPtr != NULL){
				cout << keyStr << " -> " << *valPtr << endl;
			}else{
				cout << "Key " << keyStr << " is invalid." << endl;
			}
			cout << "Load factor: " << hash_map.load() << endl;
			cout << endl;

			cout << "HashMap:" << endl;
			hash_map.printHashMap();
			cout << endl;
		}

		// Add the 'unsuccessful keys'
		cout << "Adding the 'unsuccessful' keys" << endl;
		for(int i = 0; i < 8; i++){
			bool b = hash_map.set(strArray2[i], &intArray[i]);
			checkSet(b);
			if(b)
				cout << *(hash_map.get(strArray2[i])) << endl;
			cout << "Load factor: " << hash_map.load() << endl;
			cout << endl;
		}
		cout << "HashMap:" << endl;
		hash_map.printHashMap();
		cout << endl;
	}

	return 0;
}
