#include <stdio.h>

//define KT(key type)
#define KT int

//define VT(value type)
#define VT double

#include "hashtable.h"

int main() {

	Hashtable *ht = ht_new(23);
	ht->put(ht, 10, 20.5);
	
	printf("%f\n", ht->get(ht, 10));
	
	ht->dispose(ht);
}
