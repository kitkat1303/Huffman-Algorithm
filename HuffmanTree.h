/*
 * @file HuffmanTree.h
 * @author Katarina McGaughy
 * HuffmanTree class: The HuffmanTree class constructs a Huffman tree of 
 * letters in the alphabet based on the frequency/weight associated with 
 * each letter. 
 * The purpose of this class is to create a HuffmanTree of letters.
 * 
 * Features:
 * -create HuffmanTree
 * -constructor that merges two HuffmanTree's to create another
 * -generateCodeBook generates Huffman code for each character 
 *
 * Assumptions:
 * -all characters created will be lowercase letters 
 * -generates the tree and codes
 *
 * @version 0.1
 * @date 2022-1-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>
#include <string>
using namespace std;

class HuffmanTree
{

	/**
	 * Overloaded output operator for HuffmanTree class
	 * Preconditions: HuffmanTree object must be initialized
	 * Postconditions: the HuffmanTree is sent to the output stream
	 * in inorder
	 * @param tree: HuffmanTree object
	 * @param os: output stream
	 * @return: output stream
	 */
	friend ostream &operator<<(ostream &os, const HuffmanTree &tree);

private:
	/**
	 * Node struct contains a char (data), a pointer to
	 * right child node (rightChild,) and left child node (leftChild),
	 * a count for the frequency of the char (weight),
	 * and a char (minChar) storing the minimum char in tree
	 */
	struct Node
	{

		// char object that stores a lowercase letter
		char data = '\n';

		// pointer to right child
		Node *rightChild = nullptr;

		// pointer to left child
		Node *leftChild = nullptr;

		// weight based on frequency of character
		int weight = -1;

		// minimum char in tree
		char minChar = '\n';
	};

	// pointer to root of HuffmanTree
	Node *root_ = nullptr;

	/**
	 * copyHelper
	 * this is a recursive function that copies the tree from copyRoot to
	 * the current HuffmanTree
	 * Preconditions: none
	 * Postconditios: HuffmanTree assgined with values from the tree to be copied
	 * @param copyRoot: pointer to root of the HuffmanTree to be copied
	 * @param thisRoot: pointer to root of other HuffmanTree
	 */
	void copyHelper(Node *copyRoot, Node *&thisRoot);

	/**
	 * makeEmpty
	 * this function calls makeEmptyHelper and deletes all nodes in
	 * HuffmanTree
	 * Preconditions: none
	 * Postconditios: empty HuffmanTree
	 * @param root: pointer to root of HuffmanTree
	 */
	void makeEmpty();

	/**
	 * makeEmptyHelper
	 * this recursive function deletes all nodes in
	 * HuffmanTree
	 * Preconditions: none
	 * Postconditios: empty HuffmanTree
	 * @param root: pointer to root of HuffmanTree
	 * @param data: pointer to a Comparable object
	 */
	void makeEmptyHelper(Node *&root);

	/**
	 * inorderPrint
	 * this function takes in root of HuffmanTree and recursively prints the
	 * data and count in inorder
	 * Preconditions: none
	 * Postconditions: the HuffmanTree is printed in inorder
	 * @param root: pointer to root of HuffmanTree
	 */
	void inorderPrint(Node *root) const;

	/**
	 * comparingHelper
	 * this is a recursive function that compares two search trees
	 * and returns true if they are the same and false if they are not
	 * Preconditions: none
	 * Postconditios: returns true if they are the same and false if they are not
	 * @param otherRoot: pointer to root of this HuffmanTree
	 * @param thisRoot: pointer to root of other HuffmanTree
	 * @return: returns true if they are the same and false if they are not
	 */
	bool comparingHelper(Node *otherRoot, Node *thisRoot) const;

	/**
	 * generateCodeBookHelper
	 * this functions takes in a string array called codeBook,
	 * a character letter, a root Node, a position in terms of
	 * where to store character code in codeBook, and a string called code.
	 * It recursively traverses the tree until the character is found
	 * and while traversing, adds a 0 if the character is to the left
	 * and a 1 if the character is to the right to the string code
	 * @PreCondition: string codeBook array must be initialized and
	 * passed in, character must be assigned a char, position must
	 * be the same position of place of character in the alphabet
	 * @PostConditons: codeBook array that has codes stored for each letter
	 * in the alphabet
	 * @param codeBook: string array
	 */
	void generateCodeBookHelper(Node *root, char c, string codeBook[],
										 int pos, string code) const;

	/**
	 * determinMinChar
	 * this functions takes in two characters and returns
	 * the character that is less than the other based on
	 * ordering of ASCII values
	 * PreConditions: both chars should be lowercase letters
	 * PostConditions: returns the lesser char
	 * @param c1: lowercase letter
	 * @param c2: lowercase letter
	 * @return: lesser of the two chars
	 */
	char determineMinChar(char c1, char c2) const;

public:
	/**
	 * constructor
	 * this function initializes a HuffmanTree and the sets the
	 * root_ to new Node
	 * Preconditions: none
	 * Postconditios: root_ is set to new Node
	 */
	HuffmanTree();

	/**
	 * Overloaded constructor
	 * this function takes in a char, newData and
	 * count and initializes a HuffmanTree setting the roots data
	 * to newData, weight to count, and minChar to newData
	 * Preconditions: char newData must be set and count must be set as well
	 * Postconditios: new HuffmanTree is initialized with newData for data,
	 * count for weight, and newData with minChar
	 */
	HuffmanTree(char newData, int count);

	/**
	 * copy constructor
	 * this function initializes a new HuffmanTree with the treeToBeCopied
	 * values via the copyHelper function
	 * Preconditions: none
	 * Postconditios: a new HuffmanTree is initialized with the same values
	 * as the rhs tree
	 * @param treeToBeCopied: HuffmanTree to be copied
	 */
	HuffmanTree(const HuffmanTree &tree);

	/**
	 * Overloaded constructor
	 * this constructor takes in two HuffmanTrees
	 * and combines them into one tree. The tree with the lower
	 * total weight is set to the new tree's root's left child
	 * and the tree with the higher weight is set to the root's
	 * right child node. The root is first set with a new weight
	 * that is the total of both trees weights and the minChar is determined
	 * via calling the function determineMinChar. The left and right subtrees
	 * are filled via calling the copyHelper function. Once the new tree
	 * is filled, the two old tree's data is cleared.
	 *  Preconditions: two HuffmanTree's must be initialized
	 * Postconditios: a new HuffmanTree is initialized by merging
	 * tree1 and tree2
	 * @param tree1: HuffmanTree to be cmerged
	 * @param tree2: HuffmanTree to be merged
	 */
	HuffmanTree(HuffmanTree &tree1, HuffmanTree &tree2);

	/**
	 * operator=
	 * this function clears the current tree if it is not the same as the rhs
	 * tree and then assigns the rhs tree to the current tree via copyHelper()
	 * Preconditions: none
	 * Postconditios: a new search tree is initialized with the same values
	 * as the rhs tree
	 * @param rhs: right hand side search tree
	 */
	const HuffmanTree &operator=(const HuffmanTree &rhs);

	/**
	 * desctructor
	 * this function deletes are nodes from HuffmanTree
	 * Preconditions: none
	 * Postconditios: HuffmanTree is deleted
	 */
	~HuffmanTree();

	/**
	 * operator==
	 * this function calls compareToHelper and returns true if compareToHelper
	 * returns true
	 * Preconditions: rhs HuffmanTree must be initialized
	 * Postconditios: returns true if the trees are the same and false or else
	 * @param rhs: right hand side search tree
	 * @return: returns true if the trees are the same and false or else
	 */
	bool operator==(const HuffmanTree &rhs) const;

	/**
	 * operator!=
	 * this function calls compareToHelper and returns true if compareToHelper
	 * returns false
	 * Preconditions: rhs HuffmanTree must be initialized
	 * Postconditios: returns true if they are not the same tree and
	 * false if they are
	 * @param rhs: right hand side search tree
	 * @return: returns true if they are not the same tree and
	 * false if they are
	 */
	bool operator!=(const HuffmanTree &rhs) const;

	/**
	 * Overloaded operator<
	 * this function takes in a Huffmantree and compares the weight
	 * of its root to the current root (sum weight of the tree).
	 * If the weights are the same, then the tree storing the
	 * earliest character is smaller (for example 'a' is smaller than 'b')
	 * PreConditions: there must be an addiitonal HUffmanTree initialized
	 * PostCondiitons: returns true if the current HUffmanTree's root
	 * has a weight less than rhs root. If weights are the same,
	 * return true if current tree contains the smallest character
	 * @param rhs: HuffmanTree object
	 * @return: returns true if the current HUffmanTree's root
	 * has a weight less than rhs root. If weights are the same,
	 * return true if current tree contains the smallest character
	 */
	bool operator<(const HuffmanTree &rhs) const;

	/**
	 * generateCodeBook
	 * this functions takes in a string array called codeBook
	 * and calls the generateCodeBookHelper function for each
	 * character in the alphabet, which in turn traverses the
	 * HuffmanTree and determines code for each letter and stores
	 * it in the codeBook array
	 * @PreCondition: string codeBook array must be initialized and
	 * passed in
	 * @PostConditons: codeBook array with codes for each letter
	 * in the alphabet
	 * @param codeBook: string array
	 */
	void generateCodeBook(string codeBook[]) const;
};
