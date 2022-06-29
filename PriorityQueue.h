//--------------------------------------------------------------------
// PRIORITYQUEUE.H
// Declaration and definition of the template PriorityQueue class
// Author: Olson (borrowing from a previous edition of Carrano/Henry)
//--------------------------------------------------------------------
// PriorityQueue class:
// Implements a priority queue using a heap with the following methods:
// insert, deleteMin, findMin, heapify
//  The heap is stored in a vector (see the CSS 502 lecture notes)
//  Assumptions:
//  Can only store data for which operator< exists
//  (hence the Comparable type variable)
//--------------------------------------------------------------------

/*TODO:
1. comment everything including functions
2. try to transfer memory without allocating new in 
HuffmanTree constructor 
3. ensure no memory leaks 
4. see if memory can be transffered from array to pq in PQ constructor 
5. ensure destructor works....
6. when insert into items vector do you create new Comparable??

*/


#pragma once
#include <vector>
#include <iostream>
using namespace std;
template <typename Comparable>
class PriorityQueue
{
public:

	// Number of elements in the queue
	int numElements = 0;
	// vector that holds pointers to Comparable objects
	vector<Comparable *> items;

	/**
	 * constructor
	 * this function initializes the items vector and adds a
	 * dummy node to the first element in the vector for the priority queue
	 *
	 */
	PriorityQueue() : items(vector<Comparable *>()){}

	/**
	 * destructor
	 * this function deletes all elements in items vector
	 */
	~PriorityQueue()
	{
		delete items[0];
		items[0] = nullptr;
		items.clear();
	}

	/**
	 * copy constructor
	 * this function takes in a PriorityQueue and makes a copy of it
	 * Preconditions: pq must be initialized
	 * Postcondiitions: a copy of pq is made
	 *
	 * @param pq : PriorityQueue to be copied
	 */
	PriorityQueue(const PriorityQueue &pq)
	{
		// set numElements
		numElements = pq.numElements;
		// add new pointer to Comparable objects to vector
		for (int i = 0; i < numElements+1; i++)
		{
			items.push_back(new Comparable(*pq.items[i]));
		}
	}

	/**
	 * constructor
	 * this function takes an array of Comparable pointers and
	 * constructs a PriorityQueue using the (supplied) heapify method.
	 * Preconditions: an array with length count must be passed in
	 * Postconditions: a priorityqueue is initialized with the Comparable
	 * objects from the array
	 */
	PriorityQueue(Comparable *array[], int count) 
	{
		// set count to numElements
		numElements = count;

		// add dummyNode
		items.push_back(new Comparable(*array[0]));

		// copy Comparable* to items vector
		for (int i = 0; i < count; i++)
		{
			items.push_back(new Comparable(*array[i])); 
		}

		// set number of elements to count
		numElements = count;
		// heapify the priority queue
		heapify();
	}

	/**
	 * operator=
	 * this function takes in a PriorityQueue and sets the current PriorityQueue
	 * to equal it
	 * Preconditions: rhs must be initialized
	 * Postconditions: new PriorityQeue is initialized and assigned the rhs
	 * PriorityQueue
	 * @param rhs : PriorityQueue being assigned
	 * @return const PriorityQueue& : the current PriorityQueue
	 */
	const PriorityQueue &operator=(const PriorityQueue &rhs)
	{
		if (this != &rhs)
		{
			// clear vector
			items.clear();
			// assign numElements
			numElements = rhs.numElements;
			// add elements in rhs vector to current items vector
			for (int i = 0; i < numElements+1; i++)
			{
				items.push_back(new Comparable(*rhs.items[i]));
			}
		}
		return *this;
	}

	/**
	 * insert
	 * this function adds a single item to the priority queue
	 * Preconditions: the initial heap has sufficient memory allocated
	 * and satisfies the heap order property
	 * Postconditions: inserts the item into the queue, such that a new
	 * heap is created containing the union of the elements
	 * @param c : pointer to Comparable object
	 */
	void insert(Comparable *c)
	{
		if (c == NULL)
			return;
		// Add item in position 0 (dummy position) to prevent percolating up
		// from root
		if (items.size() < 1)
			items.push_back(c);
		else
			items[0] = c;
		// Ensure we have enough space
		numElements++;
		while ((int)items.size() <= numElements)
			items.push_back(nullptr);
		// Percolate up
		int position = numElements;
		while (*c < *items[position / 2])
		{
			items[position] = items[position / 2];
			position = position / 2;
		}
		items[position] = c;
	}

	/**
	 * findMin
	 * this function returns a const pointer to the minimum value in the priority
	 * queue
	 * Preconditions: items[0] exists if numElements is larger than zero
	 * Postconditions: Returns nullptr if the heap is empty, otherwise returns
	 * the item at the root of the heap (presumably the minimum priority).
	 *
	 * @return const Comparable* : the minimum Comparable object in pq
	 */
	const Comparable *findMin() const
	{
		if (numElements <= 0)
			return nullptr;
		else
			return items[1];
	}

	/**
	 * deleteMin
	 * returns a const pointer to the minimum value in the priority queue
	 *
	 * Preconditions: items[0] exists if numElements is larger than zero
	 * Postconditions: Returns nullptr if the heap is empty, otherwise returns
	 * the item at the root of the heap (presumably the minimum priority).
	 *
	 * @return Comparable* : pointer to deleted Comparable object
	 */
	Comparable *deleteMin()
	{
		if (numElements == 0)
			return nullptr;
		// Give memory back to user
		Comparable *toReturn = items[1];
		items[1] = items[numElements];
		numElements--;
		percolateDown(1);
		return toReturn;
	}

	/**
	 * size
	 * Preconditions: none
	 * Postconditions: returns the size of the queue
	 *
	 * @return int : number of elements
	 */
	int size() const
	{
		return numElements;
	}

	/**
	 * isEmpty
	 * Preconditions: none
	 * Postconditions: returns whether the queue is empty (zero elements)
	 * @return int : true if number of elements is 0
	 */
	int isEmpty() const
	{
		return numElements == 0;
	}

private:
	/**
	 * percolateDown
	 * this function is used to restore the heap order property after deleteMin
	 * Preconditions: Both subtrees of the root are heaps
	 * Postconditions: Restores the heap order property by shifting the root
	 * down until it reaches an appropriate node
	 *
	 * @param position : current position in PriorityQueue
	 */
	void percolateDown(int position)
	{
		int child = position * 2;
		if (child > numElements)
			return;
		if (child != numElements && *items[child + 1] < *items[child])
			child++;
		if (*items[child] < *items[position])
		{
			swap(items[child], items[position]);
			percolateDown(child);
		}
	}

	/**
	 * heapify
	 * this function modifies any set of data into a heap
	 *
	 * Preconditions: items has been allocated space for numElements pointers
	 * Postconditions: The items stored form a heap
	 *
	 */
	void heapify()
	{
		for (int i = numElements / 2; i > 0; i--)
			percolateDown(i);
	}
};