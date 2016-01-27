/**
 * Author:	Gayan C. Karunarathna
 * Github:	github.com/gayanch
 * Email:	agchamara93@gmail.com
 * License:	GNU LGPL v3
 */
 
 /**
  * This is a simple hashtable implementation in C language. Wrote this for one of my personal work,
  * since C does not has hashtable in standard library. 
  * hash function used in here is not so good one, just uses size % key arithmatic to calculate the hash,
  * better hashing algorithm would be useful.
  **/
  
#ifndef HASHTABLE_H
#define HASHTABLE_H

//VTYPE is the type of value, default type is int,
//Supports: int, double, float, char
#ifndef VTYPE 
	#define VTYPE int
#endif

//for now keys are limited to type int

struct bucket {
	int key;
	VTYPE value;
	struct bucket *next;
};

typedef struct bucket Bucket;

struct hashtable {
	//capacity of hashtable
	int cap;
	
	//number of items in hashtable
	int size;
	
	Bucket *table;
	
	//pointers for associated hashtable functions, will be assigned by ht_new function
	void (*put)(struct hashtable *ht, int key, VTYPE value);
	VTYPE (*get)(const struct hashtable *ht, int key);
	VTYPE (*delete)(struct hashtable *ht, int key);
	int (*contains_key)(const struct hashtable *ht, int key);
	double (*load_factor)(const struct hashtable *ht);
	void (*clear)(struct hashtable *);
	void (*dispose)(struct hashtable *ht);
};

typedef struct hashtable Hashtable;

//create and return a new hashtable, with given size
Hashtable* ht_new(int size);

//adds key, value pair to hashtable
void ht_put(Hashtable *ht, int key, VTYPE value);

//before invoking this method,
//always make sure key exists in hashtable by using 'ht_contains_key' method
//returns value of key if exists, -1 otherwise (do not rely on -1 to decide whether key exists, 
//use 'ht_contains_key' instead)
VTYPE ht_get(const Hashtable *ht, int key);

//returns the value of deleting key, returns -1 otherwise
VTYPE ht_delete(Hashtable *ht, int key);

//returns 1 if key exists in hashtable, -1 otherwise
int ht_contains_key(const Hashtable *ht, int key);

//clears all the data in hashtable
void ht_clear(Hashtable *ht);

//returns the current load factor of hashtable
double ht_load_factor(const Hashtable *ht);

//free up memory allocated for hashtable
void ht_dispose(Hashtable *ht);

//internal function, should not call by client code
//returns hash value of given key
int _ht_hash(int size, int key);

#endif
