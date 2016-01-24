# hashtable-c
Simple hashtable implementation in C

#Usage
* Create new hashtable with size of 23
  ##### `Hashtable *ht = ht_new(23);`

* Put a <key, value> pair, ex: <10, 50>
  #####`ht_put(ht, 10, 50);` 
or 
  ##### `ht->put(ht, 10, 50);`

* Get a value by key, ex: for key = 10
  ##### `int value = ht_get(ht, 10);` 
or 
  ##### `int value = ht->get(ht, 10);`

* Check for existence of a Key
  ##### `int is_present = ht_contains_key(ht, 10);`
or
  ##### `int is_present = ht->contains_key(ht, 10);`

* Delete a key 10
  ##### `int value = ht_delete(ht, 10);` 
or 
  ##### `int value = ht->delete(ht, 10);`

* Finally dispose hashtable
  ##### `ht_dispose(ht);` 
or 
  ##### `ht->dispose(ht);`
  
  * Unstable functions
  Following methods are still in unstable state and does not guaranteed to work.
  
  ** Clear hashtable
  	Clears the entire hashtable (all keys will be deleted)
  	#####`ht_clear(ht);`
  	or
  	#####`ht->clear(ht);`
