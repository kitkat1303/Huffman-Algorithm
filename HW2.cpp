//------------------------------------------------------------------------
// HW2.CPP
// Driver code for testing Huffman class for creating Huffman codes
// Author:  Clark Olson
//------------------------------------------------------------------------
// This code tests all of the basic functionality of the Huffman class
// for CSS 502 HW 2.  It is not meant to exhaustively test the class.
//
// Assumptions:
//  - none
//------------------------------------------------------------------------
#include <iostream>
#include "HuffmanAlgorithm.h" 
using namespace std;
//------------------------------------------------------------------------
// main
// Preconditions: none
// Postconditions: tests methods of the Huffman class using randomly
// generated character counts



int main() {

	// Create random counts
  int counts[NUM_LETTERS];
  for (int i = 0; i < NUM_LETTERS; i++) {
    //counts[i] = rand() % 1000;
    counts[i] = (i + 1) * (i + 1);
  }

  // Construct Huffman codes and display table
  HuffmanAlgorithm code(counts);
  cout << code << endl;

  // Simple test of encoding words
  cout << "test:  " << code.getWord("test") << endl;
  cout << "least: " << code.getWord("least") << endl;
  cout << endl;



  return 0;
}

	/*
	// Create random counts
	int counts[NUM_LETTERS];
	for (int i = 0; i < NUM_LETTERS; i++) {
		counts[i] = rand() % 1000;
	}
	// Construct Huffman codes and display table
	HuffmanAlgorithm code(counts);
	cout << code << endl;
	// Simple test of encoding words
	cout << "test:  " << code.getWord("test") << endl;
	cout << "least: " << code.getWord("least") << endl;
	cout << endl;
	return 0;
}

*/