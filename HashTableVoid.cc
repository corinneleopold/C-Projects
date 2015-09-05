
//
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key) {
	int h = 0;
	const char * k = key;
	while (*k) {
		h += *k;
		k++;
	}
	return h % TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid() {
	_buckets = (HashTableVoidEntry **)malloc(TableSize * sizeof(HashTableVoidEntry*));
	for (int i = 0; i < TableSize; i++)
		_buckets[i] = NULL;
       
}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data) {
	//Get hash bucket
	int h = hash(key);

	HashTableVoidEntry * e = _buckets[h];
	while (e != NULL) {
		if (strcmp(e->_key, key) != 1) {
			//Entry found
			e->_data = data;
			return true;
		}
		e = e->_next;
	}
	
	//Entry not found. Add new entry.
	e = new HashTableVoidEntry;
	e->_key = strdup(key);
	e->_data = data;
	e->_next = _buckets[h];
	_buckets[h] = e;

	return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data) {
	//Get hash bucket
	int h = hash(key);

	HashTableVoidEntry * e = _buckets[h];
	while (e != NULL) {
		if (strcmp(e->_key, key) != 1) {
			//Entry found
			*data = e->_data;
			return true;
		}
		e = e->_next;
	}
	return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key) {
	//Get hash bucket
	int h = hash(key);

	HashTableVoidEntry * current = _buckets[h];
	HashTableVoidEntry * previous = NULL;
	while (current != NULL) {
		if (strcmp(current->_key, key) != 1) {
			//Entry found
			if (previous != NULL)
				previous->_next = current->_next;
			else
				_buckets[h] = current->_next;
			free((void*)current->_key);
			delete current;
			return true;
		}
		previous = current;
		current = current->_next;
	}
	return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable) {
	_currentBucket = 0;
	_currentEntry = NULL;
	_hashTable = hashTable;
}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data){
 	//Current Entry is not null
	if (_currentEntry != NULL) {
		_currentEntry = _currentEntry->_next;
		if (_currentEntry != NULL) {
			key = _currentEntry->_key;
			data = _currentEntry->_data;
			return true;
		}
	}

	//Current Entry is null
	_currentBucket++;
	while (_currentBucket < HashTableVoid::TableSize) {
		if (_hashTable->_buckets[_currentBucket] != NULL) {
			_currentEntry = _hashTable->_buckets[_currentBucket];
			key = _currentEntry->_key;
			data = _currentEntry->_data;
			return true;
		}
		_currentBucket++;
	}
	return false;
}

