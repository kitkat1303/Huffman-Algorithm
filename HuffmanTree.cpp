/*
 * @file HuffmanTree.cpp
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
#include "HuffmanTree.h"

/**
 * constructor
 * this function initializes a HuffmanTree and the sets the
 * root_ to new Node
 * Preconditions: none
 * Postconditios: root_ is set to new Node
 */
HuffmanTree::HuffmanTree()
{
	root_ = nullptr;
}

/**
 * Overloaded constructor
 * this function takes in a char, newData and
 * count and initializes a HuffmanTree setting the roots data
 * to newData, weight to count, and minChar to newData
 * Preconditions: char newData must be set and count must be set as well
 * Postconditios: new HuffmanTree is initialized with newData for data,
 * count for weight, and newData with minChar
 */
HuffmanTree::HuffmanTree(char newData, int count)
{
	root_ = new Node();
	root_->data = newData;
	root_->weight = count;
	root_->minChar = newData;
}

/**
 * copy constructor
 * this function initializes a new HuffmanTree with the treeToBeCopied
 * values via the copyHelper function
 * Preconditions: none
 * Postconditios: a new HuffmanTree is initialized with the same values
 * as the rhs tree
 * @param treeToBeCopied: HuffmanTree to be copied
 */
HuffmanTree::HuffmanTree(const HuffmanTree &treeToBeCopied)
{
	root_ = nullptr;
	// copy tree
	copyHelper(treeToBeCopied.root_, root_);
}


HuffmanTree::HuffmanTree(HuffmanTree& tree1, HuffmanTree& tree2) {
	root_ = new Node();
	//add weights of new tree and set root to total
	root_->weight = tree1.root_->weight + tree2.root_->weight;
	//determine minChar
	root_->minChar = determineMinChar(tree1.root_->data, tree2.root_->data);
	//if first tree weight is greater, then add to right child of new root
	if (tree1.root_->weight > tree2.root_->weight) {
		root_->leftChild = tree2.root_;
		root_->rightChild = tree1.root_;
	}
	else{
		root_->leftChild = tree1.root_;
		root_->rightChild = tree2.root_;
	}
	tree1.root_ = nullptr;
	tree2.root_ = nullptr;

}



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
 
HuffmanTree::HuffmanTree(HuffmanTree &tree1, HuffmanTree &tree2)
{
	root_ = new Node();
	// add weights of new tree and set root to total
	root_->weight = tree1.root_->weight + tree2.root_->weight;
	// determine minChar
	root_->minChar = determineMinChar(tree1.root_->data, tree2.root_->data);
	// if first tree weight is greater, then add to right child of new root
	if (tree1.root_->weight > tree2.root_->weight)
	{
		copyHelper(tree1.root_, root_->rightChild);
		copyHelper(tree2.root_, root_->leftChild);
	}
	// if second tree weight is greater, then add to left child of new root
	else if (tree1.root_->weight < tree2.root_->weight)
	{
		copyHelper(tree1.root_, root_->leftChild);
		copyHelper(tree2.root_, root_->rightChild);
	}
	// if they are equal, order does not matter
	else
	{
		copyHelper(tree1.root_, root_->leftChild);
		copyHelper(tree2.root_, root_->rightChild);
	}
	// empty trees
	tree1.makeEmpty();
	tree2.makeEmpty();
}
*/

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
char HuffmanTree::determineMinChar(char c1, char c2) const
{
	if (c1 < c2)
	{
		return c1;
	}
	else
	{
		return c2;
	}
}

/**
 * operator=
 * this function clears the current tree if it is not the same as the rhs
 * tree and then assigns the rhs tree to the current tree via copyHelper()
 * Preconditions: none
 * Postconditios: a new search tree is initialized with the same values
 * as the rhs tree
 * @param rhs: right hand side search tree
 */
const HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs)
{
	// if the trees are not the same then delete current tree and replace
	if (this != &rhs)
	{
		// delete tree
		makeEmpty();
		// copy tree
		copyHelper(rhs.root_, root_);
	}
	return *this;
}

/**
 * copyHelper
 * this is a recursive function that copies the tree from copyRoot to
 * the current HuffmanTree
 * Preconditions: none
 * Postconditios: HuffmanTree assgined with values from the tree to be copied
 * @param copyRoot: pointer to root of the HuffmanTree to be copied
 * @param thisRoot: pointer to root of other HuffmanTree
 */
void HuffmanTree::copyHelper(Node *copyRoot, Node *&thisRoot)
{ // thisRoot was &

	if (copyRoot != nullptr)
	{
		thisRoot = new Node();
		thisRoot->data = copyRoot->data;
		thisRoot->weight = copyRoot->weight;
		thisRoot->minChar = copyRoot->minChar;
		copyHelper(copyRoot->leftChild, thisRoot->leftChild);
		copyHelper(copyRoot->rightChild, thisRoot->rightChild);
	}
	else
	{
		thisRoot = nullptr;
	}
}

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
bool HuffmanTree::operator<(const HuffmanTree &rhs) const
{
	if (root_->weight < rhs.root_->weight)
	{
		return true;
	}
	// if weights are equal then compare characters
	if (root_->weight == rhs.root_->weight)
	{
		cout << "Weights are equal" << endl;
		// traverse tree and find smallest character in both
		if (root_->minChar < rhs.root_->minChar)
		{
			return true;
		}
	}
	return false;
}

/**
 * operator==
 * this function calls compareToHelper and returns true if compareToHelper
 * returns true
 * Preconditions: rhs HuffmanTree must be initialized
 * Postconditios: returns true if the trees are the same and false or else
 * @param rhs: right hand side search tree
 * @return: returns true if the trees are the same and false or else
 */
bool HuffmanTree::operator==(const HuffmanTree &rhs) const
{
	return comparingHelper(rhs.root_, root_);
}

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
bool HuffmanTree::operator!=(const HuffmanTree &rhs) const
{
	return !comparingHelper(rhs.root_, root_);
}

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
bool HuffmanTree::comparingHelper(Node *otherRoot, Node *thisRoot) const
{
	// if both roots are nullptr return true
	if (otherRoot == nullptr && thisRoot == nullptr)
	{
		return true;
	}
	// if roots are not the same then retuen false
	else if (otherRoot == nullptr && thisRoot != nullptr)
	{
		return false;
	}
	else if (otherRoot != nullptr && thisRoot == nullptr)
	{
		return false;
	}
	// if both roots are not nullptr
	else
	{
		// return true if the data and count are the same for the nodes
		if (otherRoot->data == thisRoot->data &&
			 otherRoot->weight == thisRoot->weight &&
			 comparingHelper(otherRoot->leftChild, thisRoot->leftChild) &&
			 comparingHelper(otherRoot->rightChild, thisRoot->rightChild))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/**
 * desctructor
 * this function deletes are nodes from HuffmanTree
 * Preconditions: none
 * Postconditios: HuffmanTree is deleted
 */
HuffmanTree::~HuffmanTree()
{
	makeEmpty();
}

/**
 * makeEmpty
 * this function calls makeEmptyHelper and deletes all nodes in
 * HuffmanTree
 * Preconditions: none
 * Postconditios: empty HuffmanTree
 * @param root: pointer to root of HuffmanTree
 */
void HuffmanTree::makeEmpty()
{
	if (root_ != nullptr)
	{
		makeEmptyHelper(root_);
	}
}

/**
 * makeEmptyHelper
 * this recursive function deletes all nodes in
 * HuffmanTree
 * Preconditions: none
 * Postconditios: empty HuffmanTree
 * @param root: pointer to root of HuffmanTree
 * @param data: pointer to a Comparable object
 */
void HuffmanTree::makeEmptyHelper(Node *&root)
{
	if (root != nullptr)
	{
		makeEmptyHelper(root->leftChild);
		makeEmptyHelper(root->rightChild);
		delete root;
		root = nullptr;
	}
}

/**
 * inorderPrint
 * this function takes in root of HuffmanTree and recursively prints the
 * data and count in inorder
 * Preconditions: none
 * Postconditions: the HuffmanTree is printed in inorder
 * @param root: pointer to root of HuffmanTree
 */
void HuffmanTree::inorderPrint(Node *root) const
{
	if (root != nullptr)
	{
		cout << root->data << " " << root->weight << endl;
		inorderPrint(root->leftChild);
		inorderPrint(root->rightChild);
	}
}

/**
 * Overloaded output operator for HuffmanTree class
 * Preconditions: HuffmanTree object must be initialized
 * Postconditions: the HuffmanTree is sent to the output stream
 * in inorder
 * @param tree: HuffmanTree object
 * @param os: output stream
 * @return: output stream
 */
ostream &operator<<(ostream &os, const HuffmanTree &tree)
{
	tree.inorderPrint(tree.root_);
	return os;
}

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
void HuffmanTree::generateCodeBook(string codeBook[]) const
{
	string code = "";
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 26; i++)
	{
		char c = alphabet[i];
		generateCodeBookHelper(root_, c, codeBook, i, code);
	}
}

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
void HuffmanTree::generateCodeBookHelper(Node *root, char c,
					string codeBook[], int pos, string code) const
{
	int position = 0;
	if (root == nullptr)
	{
		return;
	}

	if (root->data == c)
	{
		codeBook[pos] = code;
	}

	generateCodeBookHelper(root->leftChild, c, codeBook, pos, code + "0");
	generateCodeBookHelper(root->rightChild, c, codeBook, pos, code + "1");
}
