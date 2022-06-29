/*
 * @file HuffmanAlgorithm.cpp
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
#include "HuffmanAlgorithm.h"

//divide this function into smaller functions

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
 * PostConditions: the CodeBook is filled with Huffman codes based on the integer
 * array passed in
 * @param counts: integer array of frequencies for each lowercase number
 */
HuffmanAlgorithm::HuffmanAlgorithm(int (&counts)[NUM_LETTERS])
{
	// initialize all huffman tree for each letter of alphabet
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	HuffmanTree *trees[NUM_LETTERS];
	for (int i = 0; i < NUM_LETTERS; i++)
	{
		char c = alphabet[i];
		trees[i] = new HuffmanTree(c, counts[i]);
	}

	// initialize priority queue with trees array
	PriorityQueue<HuffmanTree> pq =
		 PriorityQueue<HuffmanTree>(trees, NUM_LETTERS);

	// merge trees, delete two old trees, insert new merged tree
	int numTree = 0;
	while (pq.numElements != 1)
	{
		numTree++;
		// merge tree with the two min trees in pq
		HuffmanTree *firstTree = pq.deleteMin();
		HuffmanTree *secondTree = pq.deleteMin();
		HuffmanTree *mergedTree = new HuffmanTree(*firstTree, *secondTree);
		delete firstTree;
		firstTree = nullptr;
		delete secondTree;
		secondTree = nullptr;
		pq.insert(new HuffmanTree(*mergedTree));
		cout << "Tree number " << numTree << " " << *mergedTree << endl;
		mergedTree = nullptr;
	}

	PriorityQueue<HuffmanTree> pq2 = PriorityQueue<HuffmanTree>();

	cout << "testing assignment operator pq: " << endl;
	pq2 = pq;
	HuffmanTree finalTree1 = HuffmanTree(*pq2.items[1]);


	// get codes
	HuffmanTree finalTree = HuffmanTree(*pq.items[1]);
	finalTree.generateCodeBook(CodeBook);

	if (finalTree1 == finalTree){
		cout << "assignment operator works" << endl;
	}

	cout << "testing copy c for pq: " << endl;
	PriorityQueue<HuffmanTree> pq3 = PriorityQueue<HuffmanTree>(pq);

	HuffmanTree finalTree3 = HuffmanTree(*pq3.items[1]);

	if (finalTree1 == finalTree3){
		cout << "copy constructor works" << endl;
	}

	// deallocate memory of trees array
	for (int i = 0; i < NUM_LETTERS; i++)
	{
		delete trees[i];
		trees[i] = nullptr;
	}
}

/**
 * getWord
 * this funtion takes in a string and then returns the
 * code for that string based on the CodeBook
 * Preconditions: CodeBook must be filled
 * PostConditions: returns the code for the string entered
 * @return: the code for the string entered based on Huffman
 * coding
 */
string HuffmanAlgorithm::getWord(string in)
{
	string code = "";
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	int length = in.length();
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < NUM_LETTERS; j++)
		{
			if (in[i] == alphabet[j])
			{
				code = code + CodeBook[j];
			}
		}
	}
	return code;
}

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
ostream &operator<<(ostream &os, const HuffmanAlgorithm &algo)
{
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < NUM_LETTERS; i++)
	{
		cout << alphabet[i] << " " << algo.CodeBook[i] << endl;
	}
	return os;
}
