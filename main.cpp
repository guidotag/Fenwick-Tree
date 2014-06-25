#include "FenwickTree.hpp"
#include "RangeFenwickTree.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void ft_update_test(){
	FenwickTree<int> ft(10);

	ft.update(0, 2);
	ft.update(3, 5);
	ft.update(1, 1);
	ft.update(9, 1);
	
	cout << ft;
	
	assert(ft.query(0) == 2);
	assert(ft.query(6) == 8);
	assert(ft.query(2) == 3);
	assert(ft.query(9) == 9);
}

void ft_readSingle_test(){
	FenwickTree<int> ft(10);
	
	ft.update(0, 2);
	ft.update(3, 5);
	ft.update(1, 1);
	ft.update(9, 1);
	
	assert(ft.readSingle(1) == 1);
	assert(ft.readSingle(3) == 5);
	assert(ft.readSingle(2) == 0);
	assert(ft.readSingle(0) == 2);
	assert(ft.readSingle(9) == 1);
	assert(ft.readSingle(6) == 0);
}

void ft_getIndex_test(){
	FenwickTree<int> ft(10);
	
	ft.update(0, 2);
	ft.update(3, 5);
	ft.update(1, 1);
	ft.update(9, 1);
	
	assert(ft.getIndex(2) == 0);
	assert(ft.getIndex(3) == 2);
	assert(ft.getIndex(7) == 2);
	assert(ft.getIndex(8) == 8);
	assert(ft.getIndex(9) == 9);
	assert(ft.getIndex(15) == 9);
}

void rft_query_test(){
	RangeFenwickTree<int> rft(10);
	
	rft.update(1, 4, 1);
	rft.update(3, 7, 2);
	rft.update(8, 8, 3);
	
	assert(rft.query(0) == 0);
	assert(rft.query(1) == 1);
	assert(rft.query(2) == 2);
	assert(rft.query(3) == 5);
	assert(rft.query(4) == 8);
	assert(rft.query(5) == 10);
	assert(rft.query(6) == 12);
	assert(rft.query(7) == 14);
	assert(rft.query(8) == 17);
	assert(rft.query(9) == 17);
	
	cout << rft;
}

void rft_readSingle_test(){
	RangeFenwickTree<int> rft(10);
	
	rft.update(1, 4, 1);
	rft.update(3, 7, 2);
	rft.update(8, 8, 3);
	
	assert(rft.readSingle(0) == 0);
	assert(rft.readSingle(1) == 1);
	assert(rft.readSingle(2) == 1);
	assert(rft.readSingle(3) == 3);
	assert(rft.readSingle(4) == 3);
	assert(rft.readSingle(5) == 2);
	assert(rft.readSingle(6) == 2);
	assert(rft.readSingle(7) == 2);
	assert(rft.readSingle(8) == 3);
	assert(rft.readSingle(9) == 0);
}

int main(){
	//~ ft_update_test();
	//~ ft_readSingle_test();
	//~ ft_getIndex_test();
	rft_readSingle_test();
	rft_query_test();
	
	return 0;
}
