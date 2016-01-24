#include <stdio.h>

#include "hashtable.h"

int main() {
	Hashtable *ht = ht_new(23);
	
	ht->put(ht, 5, 65);	//first methos of invoking functions
	ht_put(ht, 10, 50);		//other method of invoking functions
	ht_put(ht, 33, 150);
	ht_put(ht, 56, 250);
	
	//not working
	ht_clear(ht);
	
	printf("Key: %d, Value: %d\n", 5, ht_get(ht, 5));
	printf("Key: %d, Value: %d\n", 10, ht_get(ht, 10));
	printf("Key: %d, Value: %d\n", 33, ht_get(ht, 33));
	printf("Key: %d, Value: %d\n", 56, ht->get(ht, 56));
	
	//always make sure key exists in hashtable by 'ht_contains_key' method
	printf("Key: %d, Value: %d\n", 15, ht->get(ht, 15));
	
	printf("Key contains %d: %d\n", 56, ht_contains_key(ht, 56));
	
	printf("Deleting key: %d, Value: %d\n", 56, ht_delete(ht, 56));
	
	printf("Key contains %d: %d\n", 56, ht_contains_key(ht, 56));

	//always perform 'ht_dispose' after usage of hashtable to avoid memory leaks
	ht_dispose(ht);
}
