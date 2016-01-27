#include <stdio.h>

//define the type of value
#define VTYPE char

#include "hashtable.h"

int main() {
	Hashtable *ht = ht_new(23);
	
	ht->put(ht, 10, 'A');
	ht->put(ht, 15, 'B');
	ht->put(ht, 20, 'C');
	
	printf("Key: %d, value: %c\n", 10, ht->get(ht, 10));
	printf("Key: %d, value: %c\n", 15, ht->get(ht, 15));
	printf("Key: %d, value: %c\n", 20, ht->get(ht, 20));

	//always perform 'ht_dispose' after usage of hashtable to avoid memory leaks
	ht_dispose(ht);
}
