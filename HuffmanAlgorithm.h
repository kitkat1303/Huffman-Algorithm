/*
 * @file HuffmanAlgorithm.h
 * @author Katarina McGaughy
 * HuffmanAlgorithm class: The HuffmanAlgorithm class takes in an array of 
 * integers that represent the ferquency/weight for each character in the 
 * alphabet. It creates a HuffmanTree for each character and then merges 
 * the trees to create a final HuffmanTree that stores the Huffman code 
 * for each letter. 
 * The purpose of this class is to create a HuffmanTree and store the codes
 * for each letter in a CodeBook
 * Features:
 * -store HuffmanTree in priority queue
 * -merge HuffmanTree's to a final HuffmanTree
 * -use CodeBook to determine the code for various strings 
 * -output stream (code for each letter in string)
 *
 * Assumptions:
 * -output will be in alphabetical order
 * -HuffmanTree class generates the tree and codes
 *
 * @version 0.1
 * @date 2022-1-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string>
#include <iostream>
#include "HuffmanTree.h"
#include "PriorityQueue.h"
using namespace std;
#pragma once
const int NUM_LETTERS = 26;

class HuffmanAlgorithm
{
private:
	// stores codes for each character
	string CodeBook[NUM_LETTERS];

public:
	/**
	 * desctructor
	 * default constructor for HuffmanAlgorithm
	 * Preconditions: none
	 * Postconditios: deletes HuffmanAlgorithm
	 */
	~HuffmanAlgorithm(){};

	/**
	 * Overloaded constructor
	 * this functions takes in an array of integers that contains
	 * the frequency of characters and initializes an array of
	 * HuffmanTree's for each character in the alphabet with their
	 * following frequencies. A PriorityQueue is then initialized with the
	 * HuffmanTree's. The HuffmanTree's are then merged until a final
	 * HuffmanTree left. The final HuffmanTree is then used to fill the
	 * CodeBook string array with codes for each character.
	 * PreConditions: an integer array with length of 26 must be initialized
	 * PostConditions: the CodeBook is filled with Huffman codes based on the 
	 * integer array passed in
	 * @param counts: integer array of frequencies for each lowercase number
	 */
	HuffmanAlgorithm(int (&counts)[NUM_LETTERS]);

	/**
	 * getWord
	 * this funtion takes in a string and then returns the
	 * code for that string based on the CodeBook
	 * Preconditions: CodeBook must be filled
	 * PostConditions: returns the code for the string entered
	 * @return: the code for the string entered based on Huffman
	 * coding
	 */
	string getWord(string in);

	/**
	 * Overloaded output operator for HuffmanAlgorithm
	 * this function prints the character and its code on
	 * each line
	 * Preconditions: HuffmanAlgorithm object must be initialized
	 * Postconditions: the HuffmanAlgorithm is sent to the output stream
	 * @param tree: HuffmanAlgorithm object
	 * @param os: output stream
	 * @return: output stream
	 */
	friend ostream &operator<<(ostream &os, const HuffmanAlgorithm &algo);
};
