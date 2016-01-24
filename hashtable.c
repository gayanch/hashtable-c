/**
 * Author:	Gayan C. Karunarathna
 * Github:	github.com/gayanch
 * Email:	agchamara93@gmail.com
 * License:	GNU LGPL v3
 */

#include <stdlib.h>
#include <stdio.h>

#include "hashtable.h"

Hashtable* ht_new(int size) {
	if (size <=0 ) {
		printf("Invalid size.\n");
		return NULL;
	}
	
	Hashtable *ht = malloc(sizeof *ht);
	ht->size = size;
	ht->table = malloc(size * sizeof *ht->table);
	
	//associated function pointers
	ht->put = &ht_put;
	ht->get = &ht_get;
	ht->delete = &ht_delete;
	ht->contains_key = &ht_contains_key;
	ht->clear = &ht_clear;
	ht->dispose = &ht_dispose;
	
	return ht;
}

//To-Do: implement a better hashing algorithm
int _ht_hash(int size, int key) {
	return key % size;
}

void ht_put(Hashtable *ht, int key, int value) {
	if (ht == NULL) {
		printf("Error: null hashtable");
		return;
	}
	
	int location = _ht_hash(ht->size, key);
	//new code
	//now ht->table contains only references to heads of chains,
	//ht->table's keys, values are ignored
 	Bucket *b = (&ht->table[location])->next;
	Bucket *new = malloc(sizeof *new);
	new->key = key;
	new->value = value;
	
	(&ht->table[location])->next = new;
	new->next = b;
}

int ht_get(Hashtable *ht, int key) {
	if (ht == NULL) {
		printf("Error: null hashtable");
		return -1;
	}
	
	//redundant, marked for removal
	//if (!ht_contains_key(ht, key)) return -1;
	
	int location = _ht_hash(ht->size, key);
	
	//first bucket of the chain
	Bucket *b = (&ht->table[location])->next;
	
	//search linearly until a bucket with provided key found
	while (b != NULL) {
		if (b->key == key) {
			return b->value;
		}
		b = b->next;
	}
	
	//key not found
	return -1;
}

int ht_contains_key(Hashtable *ht, int key) {
	if (ht == NULL)	return 0;
	
	int location = _ht_hash(ht->size, key);
	
	//getting first bucket of chain
	Bucket *b = (&ht->table[location])->next;
	
	//first bucket is null
	if (b == NULL)	return 0;
	
	//search linearly for a matching bucket
	while (b != NULL) {
		if (b->key == key) {
			return 1;
		}
		b = b->next;
	}
	
	//no bucket with provided key found
	return 0;
}

int ht_delete(Hashtable *ht, int key) {
	//null hashtable provided, can not proceed
	if (ht == NULL)	return -1;
	
	//key not found, nothing to delete
	//redundant, if key found, marked for removal
	//if (!ht_contains_key(ht, key))	return -1;
	
	int location = _ht_hash(ht->size, key);
	Bucket *b = (&ht->table[location])->next;
	while (b != NULL) {
		//check buckets with provided key
		if (b->key == key) {
			int value = b->value;
			//key found, check if it is in the middle of chain
			if (b->next != NULL) {
				//remove bucket and, reconnect links in chain
				Bucket *tmp = b;
				b = b->next;
				free(tmp);
				tmp = NULL;
				return value;
			} else {
				//last bucket, free up memory
				free(b);
				b = NULL;
				return value;
			}
		}
		b = b->next;
	}
	
	//provided key is not found, nothing to delete
	return -1;
}

void ht_clear(Hashtable *ht) {
	if (ht == NULL) return;
	
	//freeying memeory and mallocing new hashtable does not seem to work,
	//Thinking........... :)
/*	int size = ht->size;*/
/*	ht_dispose(ht);*/
/*	ht = ht_new(size);*/
	
	//work around
	//freeying & malloc'ing again does not seem to work
	//freeying individual buckets in table
	int size = ht->size;
	int i;
	for (i = 0; i < size; i++) {
		Bucket *b = (&ht->table[i])->next;
		
		//access buckets in list and free them
		while (b != NULL) {
			Bucket *next = b->next;
			free(b);
			b = next;
		}
	}
}

void ht_dispose(Hashtable *ht) {
	//free up all buckets in chains
	ht_clear(ht);

	free(ht->table);
	free(ht);
	ht->table = NULL;
	ht = NULL;
	
	//Note:
	//Should we free individual buckets in chain??
}
