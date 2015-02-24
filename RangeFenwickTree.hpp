/**
 * Fenwick Tree supporting a range-update operation in log time. Let A[1..n] be the
 * underlying array we are updating, and let S(i) = A[1] + ... + A[i].
 * Suppose we want to update A, adding a constant x to each element
 * between indices l and r (l <= r). To update the cumulative sum
 * S(i) (l <= i <= r) we assign
 * 
 * S(i) = S(i) + (i - l + 1) * x
 * 		= S(i) + x * i - x * (l - 1)
 * 
 * If 1 <= i < l then S(i) remains the same, and if r < i <= n we'll
 * have to add (r - l + 1) * x.
 * 
 * Note that letting f(i) = x * i - x * (l - 1) we can think of this process
 * as adding linear functions on i. Suppose we have two arrays
 * mul[1..n] and add[1..n] such that S(i) = mul[i] * i + add[i]. Initially
 * mul[i] = add[i] = 0 for all i. Then, each time we update S(i)
 * we'll have
 * 
 * S(i) = {mul[i] * i + add[i]} + {x * i - x * (l - 1)}
 * 		= (mul[i] + x) * i + (add[i] - x * (l - 1))
 *
 * Therefore, after assigning
 * 
 * mul[i] += x
 * add[i] -= x * (l - 1)
 * 
 * S(i) will be updated. For 1 <= i < l we don't need to 
 * modify mul and add, and finally for r < i <= n we just need to assign
 * add[i] += (r - l + 1) * x.
 * 
 * The key observation is that we can represent mul and add as Fenwick
 * Trees to support, efficiently, all the previous operations, by making the 
 * following sequence of updates:
 * 
 * mul.update(l, x)
 * add.update(l, -x * (l - 1))
 * mul.update(r, -x)
 * add.update(r, x * r)
 * 
 * Under this representation, S(i) = mul.query(i) * i + add.query(i). 
 * 
 * Reference: http://petr-mitrichev.blogspot.com.ar/2013/05/fenwick-tree-range-updates.html
 * 
 * Author: Guido Tagliavini Ponce
 */

#ifndef __RANGE_FENWICK_TREE_HPP__
#define __RANGE_FENWICK_TREE_HPP__

#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include "FenwickTree.hpp"

using namespace std;

template<typename T>
class RangeFenwickTree{
	public:
		RangeFenwickTree(int n);
		
		T query(int idx);
		
		void update(int idx, T val);
		
		void update(int from, int to, T val);
		
		T readSingle(int idx);
		
		template<typename U>
		friend ostream &operator<<(ostream &out, RangeFenwickTree<U> &rft);
		
	private:
		FenwickTree<T> mul;
		FenwickTree<T> add;
		int n;
};

template<typename T>
RangeFenwickTree<T>::RangeFenwickTree(int n) : mul(n), add(n){
	assert(n > 0);
	this->n = n;
}

template<typename T>
void RangeFenwickTree<T>::update(int idx, T val){
	assert(idx >= 1 && idx <= n);
	
	update(idx, idx, val);
}

template<typename T>
void RangeFenwickTree<T>::update(int from, int to, T val){
	assert(from >= 1 && from <= to && to <= n);
	
	mul.update(from, val);
	add.update(from, -(from - 1) * val);
	mul.update(to, -val);
	add.update(to, to * val);
}

template<typename T>
T RangeFenwickTree<T>::query(int idx){
	assert(idx >= 1 && idx <= n);
	
	return mul.query(idx) * idx + add.query(idx);
}

template<typename T>
T RangeFenwickTree<T>::readSingle(int idx){
	assert(idx >= 1 && idx <= n);
	
	if(idx == 1){
		return query(1);
	}
	
	return query(idx) - query(idx - 1);
}

template<typename T>
ostream &operator<<(ostream &out, RangeFenwickTree<T> &rft){
	out << "Mul array:\t\t";
	for(int i = 1; i <= rft.n; i++){
		out << rft.mul.query(i) << " ";
	}
	out << endl;
	out << "Add array:\t\t";
	for(int i = 1; i <= rft.n; i++){
		out << rft.add.query(i) << " ";
	}
	out << endl;
	out << "Cumulative sums:\t";
	for(int i = 1; i <= rft.n; i++){
		out << rft.query(i) << " ";
	}
	out << endl;
	out << "Values:\t\t\t";
	for(int i = 1; i <= rft.n; i++){
		out << rft.readSingle(i) << " ";
	}
	out << endl;

	return out;
}

#endif
