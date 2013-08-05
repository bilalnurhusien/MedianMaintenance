/*
 *  File: MedianMaintenance.cpp
 *
 *  Copyright 2013 © Bilal Nurhusien
 *  This program is free software.
 *
 *  Description:
 *  Implemented the median maintenance algorithm using max and min heaps.
 *
 *  Input File:
 *  The text file contains a list of the integers from 1 to 10000 in unsorted order
 *  The numbers are treated as a stream of integers arriving one by one. The input
 *  file was taken from an Algorithms and Analysis course from Stanford, taught by
 *  Tim Roughgarden.
 *
 *  Output:
 *  The median sum of numbers modulo 10000 is displayed using standard output.
 *  i.e. The output is (m1+m2+m3+...+m10000)mod10000 where m1 is the first
 *  median, m2 is the second median, etc.
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct Comp
{
  bool operator()(const unsigned int& a, const unsigned int& b) const {
    return a > b ;
  }
};

const char* inputfile = "./Test1.txt";

/*
 * Precondition: Input file is a text file located in the project directory.
 *               Each line of the file contains a number from 1-10000.
 *
 * Postcondition: Every number in the file is stored in the queue (M).
 */

int readfile(queue<unsigned int>& Q) {
	std::string line;
	std::ifstream infile;
	infile.open(inputfile);

	if(infile.fail())
	{
		cout << "Problem opening file.";
		return -1;
	}

	while (getline(infile, line)) {
		istringstream iss(line);
		unsigned int a;
		iss >> a;
		Q.push(a);
	}

	return 0;
}

/*
 * Precondition: Q is a non-empty queue
 *
 * Postcondition: Returns the medium of numbers in read so far. The size of Q
 *                decreases by 1. The size of MaxHeap or MinHeap increase by 1.
 *                i.e. a number is taken from Q and inserted into either MaxHeap
 *                or MinHeap.
 */

unsigned int MedianMaintenance (queue<unsigned int>& Q, vector<unsigned int>& MaxHeap,
								vector<unsigned int>& MinHeap) {
    unsigned int min = 0;
	unsigned int median = 0;

	// Read next number in queue
	unsigned int next = Q.front();
	Q.pop();

	if (!MinHeap.empty()) {
		min = MinHeap.front();
	}

	/*
	 * Step 1: Add the next number to one of the heaps. If the
	 * number is greater than the root of MinHeap, add it to
	 * MinHeap, otherwise add it to MaxHeap.
	 */

	if (next > min) {
		MinHeap.push_back(next);
		push_heap (MinHeap.begin(),MinHeap.end(), Comp());
	}

	else {
		MaxHeap.push_back(next);
		push_heap (MaxHeap.begin(),MaxHeap.end());
	}

	/*
	 * Step 2: Balance the heaps. The heaps will either have
	 * the same number of elements or one of them will contain
	 * 1 more item.
	 */

	if (int (MinHeap.size() - MaxHeap.size()) > 1) {
		pop_heap (MinHeap.begin(), MinHeap.end(), Comp());
		unsigned int temp = MinHeap.back();
		MinHeap.pop_back();
		MaxHeap.push_back(temp);
		push_heap (MaxHeap.begin(),MaxHeap.end());
	}

	else if (int (MaxHeap.size() - MinHeap.size()) > 1) {
		pop_heap (MaxHeap.begin(),MaxHeap.end());
		unsigned int temp = MaxHeap.back();
		MaxHeap.pop_back();
		MinHeap.push_back(temp);
		push_heap (MinHeap.begin(),MinHeap.end(), Comp());
	}

	/*
	 * Step 3: Calculate the median. If the number of elements (n)
	 * read so far is even, return the n/2th smallest element.
	 * Otherwise, return the (n+1)/2 smallest element.
	 *
	 */

	if ((MaxHeap.size() + MinHeap.size())%2 == 0)
		median = MaxHeap.front();

	else if (int(MaxHeap.size() - MinHeap.size()) == 1) {
		median = MaxHeap.front();
	}

	else {
		median = MinHeap.front();
	}

	return median;

}

int main () {
	queue<unsigned int> Q;         // Store numbers in queue
	vector<unsigned int> MaxHeap;  // Store smallest 1/2 of numbers in max heap
	vector <unsigned int> MinHeap; // Store largest 1/2 of numbers in min heap
	unsigned int sum = 0;

	// Read numbers from file into queue
	if (readfile(Q) < 0) return -1;

	// Create max and min heaps
	make_heap(MaxHeap.begin(),MaxHeap.end());
	make_heap(MinHeap.begin(),MinHeap.end(), Comp());

	// Add median to sum
	while(Q.size() != 0)
		sum += MedianMaintenance(Q, MaxHeap, MinHeap);

	// Display the (median sum of numbers) modulo 10000 using standard output.
	sum = sum % 10000;
	cout << "Median sum: " << sum << endl;
}
