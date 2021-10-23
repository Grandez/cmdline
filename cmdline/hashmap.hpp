#pragma once

#include <memory>
#include <any>
#include <type_traits>

#include "hashing.h"

namespace cmdline {
	template<class T>

	class HashMap {
	public:
		HashMap() = default;
		~HashMap();
		template<class P>
		bool insert(T key, std::unique_ptr<P> value) {
			unsigned long hashKey = hash(makeChar(&key));
			P p = *value;

			hitem* nitem = new hitem();
			nitem->key = key;
			nitem->hash = hashKey;
			nitem->next = nullptr;
			nitem->value = malloc(sizeof(p));
			memcpy(nitem->value, &p, sizeof(p));
			
			unsigned long ptr = hashKey % primes[size];
			if (htable[ptr] == nullptr) {
				htable[ptr] = nitem;
				slots++;
				return false;
			}
			hitem* prev = htable[ptr];
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
		void * find(T key);
	private:
		int size = 1;
		int slots = 0; // slots used
		typedef struct _hitem {
			T key;
			unsigned long hash;
			void* value;
			struct _hitem* next;
		} hitem;
		hitem** htable = (hitem**) calloc(primes[size] + 1, sizeof(hitem*));;
		// Espacio para las tablas Hash
		int primes[12] = { 31, 67, 97, 131, 173, 227, 277, 313, 373, 431, 503 };

		// Primos de 1 a 1000
		/*
		int *primes2 = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
						101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
						211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
						307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
						401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
						503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
						601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
						701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
						809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907,
						911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };
*/
		const char* makeChar(T *key) {
			if (instanceof<std::string>(key)) return ((std::string*)key)->c_str();
			return (const char *) key;
			//if (instanceof<char*>(key)) return key;
			// Debe ser numero
			//return std::to_string(key);
		}
		template<typename Base, typename P>
		inline bool instanceof(const P*) {
			return std::is_base_of<Base, P>::value;
		}
	};
	
}

