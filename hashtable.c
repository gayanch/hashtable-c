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
	Hashtable *ht = malloc(sizeof *ht);
	ht->size = size;
	ht->table = malloc(size * sizeof *ht->table);
	
	//associated function pointers
	ht->ht_put = &ht_put;
	ht->ht_get = &ht_get;
	ht->ht_delete = &ht_delete;
	ht->ht_contains_key = &ht_contains_key;
	ht->ht_dispose = &ht_dispose;
	
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
	
	if (!ht_contains_key(ht, key)) return -1;
	
	int location = _ht_hash(ht->size, key);
	Bucket *b = (&ht->table[location])->next;
	while (b != NULL) {
		if (b->key == key) {
			return b->value;
		}
		b = b->next;
	}
	
	return -1;
}

int ht_contains_key(Hashtable *ht, int key) {
	if (ht == NULL)	return 0;
	
	int location = _ht_hash(ht->size, key);
	if ((&ht->table[location]) == NULL)	return 0;
	
	Bucket *b = (&ht->table[location])->next;
	while (b != NULL) {
		if (b->key == key) {
			return 1;
		}
		b = b->next;
	}
	
	return 0;
}

int ht_delete(Hashtable *ht, int key) {
	if (ht == NULL)	return -1;								//null hashtable provided, can not proceed
	
	if (!ht_contains_key(ht, key))	return -1;		//key not found, nothing to delete
	
	int location = _ht_hash(ht->size, key);
	Bucket *b = (&ht->table[location])->next;
	while (b != NULL) {
		//check buckets with provided key
		if (b->key == key) {
			int value = b->value;
			//key found, check if it is in the middle of chain
			if (b->next != NULL) {
				Bucket *tmp = b;
				b = b->next;
				free(tmp);
				return value;
			} else {
				//last bucket, free up memory
				free(b);
				return value;
			}
		}
		b = b->next;
	}
	return -1;
}

void ht_dispose(Hashtable *ht) {
	free(ht->table);
	free(ht);
}
