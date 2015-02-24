/**
 * Fenwick Tree (or Binary Indexed Tree).
 * Allows operations with prefix sums of an array A[1..n], namely:
 * 	1. Reading the cumulative sum for an index. In other words, given
 * 		1 <= i <= n, return A[1] + ... + A[i].
 * 	2. Updating position A[i], and consequently all the cumulative
 * 		sums.
 * 	3. Reading A[i].
 * 	4. Finding an index where a cumulative frequency lies. That is,
 * 		given s, find 1 <= i <= n such that A[1] + ... + A[i] = s.
 * 	5. Scaling the entire array A by a constant factor.
 * 
 * Operations 1, 2, 3 and 4 are done in O(log n), and 5 in O(n).
 * The structure uses only an internal array of n + 1 elements, so it is
 * fast but also compact.
 * Note that there is no need to explicitly store array A: we
 * can use this data structure to talk about A's cumulative sums
 * without really storing A.
 * 
 * Reference: Peter Fenwick, A New Data Structure for Cumulative
 * 	Frequency Tables, Software - Practice And Experience Vol. 4(3),
 * 	327-336, March 1994.
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __FENWICK_TREE_HPP__
#define __FENWICK_TREE_HPP__

#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

/**
 * T must have a default constructor that initializes the object
 * as the neutral element. It must implement the operator + such
 * that (T, +) is a group. Also, it must implement the operator
 * - in the natural way. Finally, it must implement a copy
 * constructor.
 */

template<typename T>
class FenwickTree{
	public:
		FenwickTree(int n);
		
		/**
		 * Reads the cumulative sum for index idx.
		 */
		T query(int idx);
		
		/**
		 * Updates position at index idx, and therefore all cumulative
		 * sums with indexes greater than or equal idx.
		 */
		void update(int idx, T val);
		
		/**
		 * Read value (not cumulative sum) at index idx.
		 */
		T readSingle(int idx);
		
		/**
		 * Scale the array by a factor c.
		 */
		void scale(int c);
		
		/**
		 * Returns the greatest index i such that A[1] + ... + A[i] <= cumu.
		 * Assumes all values A[j] are nonnegative (equivalently, the cumulative 
		 * sums are non-decreasing).
		 * 
		 * Precondition: A[1] <= cumu 
		 */
		int getIndex(T cumu);
		
		template<typename U>
		friend ostream &operator<<(ostream &out, FenwickTree<U> &ft);
		
	private:
		int msb(int x);
	
		vector<T> tree;
		int n;
};

template<typename T>
FenwickTree<T>::FenwickTree(int n) : tree(n + 1){
	assert(n > 0);
	this->n = n;
}

template<typename T>
void FenwickTree<T>::update(int idx, T val){
	assert(idx >= 1 && idx <= n);
	
	while(idx <= n){
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

template<typename T>
T FenwickTree<T>::query(int idx){
	assert(idx >= 1 && idx <= n);
	
	T sum = T();
	
	while(idx >= 1){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	
	return sum;
}

template<typename T>
T FenwickTree<T>::readSingle(int idx){
	assert(idx >= 1 && idx <= n);
	
	int join = idx - (idx & -idx);
	T res(tree[idx]);
	idx--;
	
	while(idx > join){
		res -= tree[idx];
		idx -= (idx & -idx);
	}
	
	return res;
}

template<typename T>
void FenwickTree<T>::scale(int c){
	for(int i = 1; i <= n; i++){
		tree[i] *= 1 / c;
	}
}

template<typename T>
int FenwickTree<T>::msb(int x){
	assert(x > 0);
	int res = 1;
	
	while(x > 1){
		res = res << 1;
		x = x >> 1;
	}
	
	return res;
}

template<typename T>
int FenwickTree<T>::getIndex(T cumu){
	assert(cumu >= tree[1]);
	
	int mask = msb(n);
	int base = 0;

	while(mask > 0){
		int mid = base + mask;
		if(mid <= n && tree[mid] <= cumu){
			cumu -= tree[mid];
			base = mid;
		}
		mask = mask >> 1;
	}
	
	return base;
}

template<typename T>
ostream &operator<<(ostream &out, FenwickTree<T> &ft){
	out << "Internal array:\t\t";
	for(int i = 1; i <= ft.n; i++){
		out << ft.tree[i] << " ";
	}
	out << endl;
	out << "Cumulative sums:\t";
	for(int i = 1; i <= ft.n; i++){
		out << ft.query(i) << " ";
	}
	out << endl;
	out << "Values:\t\t\t";
	for(int i = 1; i <= ft.n; i++){
		out << ft.readSingle(i) << " ";
	}
	out << endl;

	return out;
}

#endif
