#include <iostream>
#include <cstdlib>
#include <utility>
#include <any>

#include "hashing.h"
#include "hashmap.hpp"
#include <memory>
#include <any>

namespace cmdline {
	/*
	template <class T>  
	HashMap<T>::HashMap() {
		void* key;
		T** htable = calloc(primes[size] + 1, sizeof(hitem *));
	}
	*/
/*
	template <class T>
	bool HashMap<T>::insert(T key, void * value) {
 		std::cout << "size of pointer " << sizeof(value) << std::endl;
		unsigned long k = hash(key);
		hitem *nitem = new hitem();
		nitem->key = key;
		nitem->next = nullptr;
		nitem->value = malloc(sizeof(value));
		memcpy(nitem->value, &value, sizeof(value));

		if (htable[k] == nullptr) {
			htable[k] = nitem;
			slots++;
			return false;
		}
		hitem* prev = htable[k];
		while (prev->key != nitem->key) {
			if (prev->next == nullptr) prev = prev->next;
		}
		if (prev->key == nitem->key) {
			free(prev->value);
			prev->value = nitem->value;
			return true;
		}
		prev->next = nitem;
		return false;
	}
*/
	template <class T>
	void * HashMap<T>::find(T key) {
		unsigned long k = hash(key);
		hitem* prev = htable[k];
		if (prev == nullptr) return nullptr;
		while (prev->key != key) {
			prev = prev->next;
			if (prev == nullptr) return nullptr;
		}
		return prev->value;
	}

	template <class T>  HashMap<T>::~HashMap() {
		for (int i = 0; i < primes[size]; i++) {
			if (htable[i] == nullptr) continue;
			hitem* prev = htable[i];
			hitem* curr = prev;
			while (curr) {
				free(curr->value);
				curr = prev->next;
				free(prev);
				prev = curr;
			}
		}
	}
}
