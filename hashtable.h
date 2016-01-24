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

struct bucket {
	int key;
	int value;
	struct bucket *next;
};

typedef struct bucket Bucket;

struct hashtable {
	int size;
	Bucket *table;
	
	//pointers for associated hashtable functions, will be assigned by ht_new function
	struct hashtable* (*new)(int size);
	void (*put)(struct hashtable *ht, int key, int value);
	int (*get)(struct hashtable *ht, int key);
	int (*delete)(struct hashtable *ht, int key);
	int (*contains_key)(struct hashtable *ht, int key);
	void (*clear)(struct hashtable *);
	void (*dispose)(struct hashtable *ht);
};

typedef struct hashtable Hashtable;

//create and return a new hashtable, with given size
Hashtable* ht_new(int size);

//adds key, value pair to hashtable
void ht_put(Hashtable *ht, int key, int value);

//before invoking this method,
//always make sure key exists in hashtable by using 'ht_contains_key' method
//returns value of key if exists, -1 otherwise (do not rely on -1 to decide whether key exists, 
//use 'ht_contains_key' instead)
int ht_get(Hashtable *ht, int key);

//returns the value of deleting key, returns -1 otherwise
int ht_delete(Hashtable *ht, int key);

//returns 1 if key exists in hashtable, -1 otherwise
int ht_contains_key(Hashtable *ht, int key);

//clears all the data in hashtable
void ht_clear(Hashtable *ht);

//free up memory allocated for hashtable
void ht_dispose(Hashtable *ht);

//internal function, should not call by client code
//returns hash value of given key
int _ht_hash(int size, int key);

#endif
