#include "FenwickTree.hpp"
#include "RangeFenwickTree.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void ft_update_test(){
	FenwickTree<int> ft(10);

	ft.update(1, 2);
	ft.update(4, 5);
	ft.update(2, 1);
	ft.update(10, 1);
	
	cout << ft;
	
	assert(ft.query(1) == 2);
	assert(ft.query(7) == 8);
	assert(ft.query(3) == 3);
	assert(ft.query(10) == 9);
}

void ft_readSingle_test(){
	FenwickTree<int> ft(10);
	
	ft.update(1, 2);
	ft.update(4, 5);
	ft.update(2, 1);
	ft.update(10, 1);
	
	assert(ft.readSingle(2) == 1);
	assert(ft.readSingle(4) == 5);
	assert(ft.readSingle(3) == 0);
	assert(ft.readSingle(1) == 2);
	assert(ft.readSingle(10) == 1);
	assert(ft.readSingle(7) == 0);
}

void ft_getIndex_test(){
	FenwickTree<int> ft(10);
	
	ft.update(1, 2);
	ft.update(4, 5);
	ft.update(2, 1);
	ft.update(10, 1);
	
	assert(ft.getIndex(2) == 1);
	assert(ft.getIndex(3) == 3);
	assert(ft.getIndex(7) == 3);
	assert(ft.getIndex(8) == 9);
	assert(ft.getIndex(9) == 10);
	assert(ft.getIndex(15) == 10);
}

void rft_query_test(){
	RangeFenwickTree<int> rft(10);
	
	rft.update(2, 5, 1);
	rft.update(4, 8, 2);
	rft.update(9, 9, 3);
	
	assert(rft.query(1) == 0);
	assert(rft.query(2) == 1);
	assert(rft.query(3) == 2);
	assert(rft.query(4) == 5);
	assert(rft.query(5) == 8);
	assert(rft.query(6) == 10);
	assert(rft.query(7) == 12);
	assert(rft.query(8) == 14);
	assert(rft.query(9) == 17);
	assert(rft.query(10) == 17);
	
	cout << rft;
}

void rft_readSingle_test(){
	RangeFenwickTree<int> rft(10);
	
	rft.update(2, 5, 1);
	rft.update(4, 8, 2);
	rft.update(9, 9, 3);
	
	assert(rft.readSingle(1) == 0);
	assert(rft.readSingle(2) == 1);
	assert(rft.readSingle(3) == 1);
	assert(rft.readSingle(4) == 3);
	assert(rft.readSingle(5) == 3);
	assert(rft.readSingle(6) == 2);
	assert(rft.readSingle(7) == 2);
	assert(rft.readSingle(8) == 2);
	assert(rft.readSingle(9) == 3);
	assert(rft.readSingle(10) == 0);
}

int main(){
	// ft_update_test();
	// ft_readSingle_test();
	// ft_getIndex_test();
	rft_readSingle_test();
	rft_query_test();
	
	return 0;
}
