#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
 	int size;
	list<WordEntry> *hashTable;
	
 public:
	HashTable(int);
	~HashTable();
	bool contains(const string &);
	double getAverage(const string &);
	void put(const string &, int);
 
 private:
	int computeHash(const string &);

	//copy constructor-- included here for rule of 3
    HashTable(const HashTable&);

	//copy assignment-- included here for rule of 3
    HashTable& operator=(const HashTable&);

};

#endif