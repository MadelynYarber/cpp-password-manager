#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm> //check
//#include <cstring>

using namespace std;

namespace cop4530 {
template <typename K, typename V>
class HashTable {
public:

HashTable(size_t size = 101); //Constructor
~HashTable(); //Destructor

bool contains(const K &k) const;
bool match(const std::pair<K, V> &kv) const;
bool insert(const std::pair<K, V> &kv);
bool insert(std::pair<K, V> &&kv);
bool remove(const K &k);
void clear();
bool load(const char *filename);
void dump() const;
size_t size() const;
bool write_to_file(const char *filename) const;
int getSize() const; // check
int get_prime_below(int n);

private:
void makeEmpty();
void rehash();
size_t myhash(const K &k) const;
unsigned long prime_below(unsigned long sz);
void setPrimes(std::vector<unsigned long>& primes);
// max_prime is used by the helpful functions provided to you.
static const unsigned int max_prime = 1301081;

// used if the initial capacity of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 101;

std::vector<std::list<std::pair<K, V>>> table;
//size_t num_elements;
//size_t table_size;
int table_size;

};
#include "hashtable.hpp"
}//namespace cop4530

#endif
