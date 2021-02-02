/*
	Author: Vishnu Rampersaud
	Date: 11/22/2019

	
	This is the Sort.h header file for Part(1) and Part(2) of the assignment.
	This file contains all sorting functions used for parts 1 and 2 of the assignment. 

	I added the median3, quicksortMiddle, and quicksortFirst functions to this file.
	I also modified the insertionSort, heapSort, mergeSort, and quickSort functions 
	along with all of their helper functions to allow a Comparator class to be used for comparisons. 
	All other code below was provided by Professor Stamos, and sourced from Data
	Structures and Algorithm Analysis in C++, 4th edition, by Mark Allen
	Weiss.
*/

#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a , Comparator less_than)
{
    for( int p = 1; p < a.size( ); ++p )
    {
        Comparable tmp = std::move( a[ p ] );

        int j;
        for( j = p; j > 0 && less_than(tmp, a[ j - 1 ]); --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable>& a, Comparator less_than, int left, int right)
{
	for (int p = left + 1; p <= right; ++p)
	{
		Comparable tmp = std::move(a[p]);
		int j;

		for (j = p; j > left && less_than(tmp, a[j - 1]); --j)
			a[j] = std::move(a[j - 1]);
		a[j] = std::move(tmp);
	}
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}


/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable>& a, Comparator less_than, int i, int n)
{
	int child;
	Comparable tmp;

	for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && less_than(a[child], a[child + 1]))
			++child;
		if (less_than(tmp, a[child]))
			a[i] = std::move(a[child]);
		else
			break;
	}
	a[i] = std::move(tmp);
}

/**
 * Standard heapsort.
 */
template <typename Comparable, typename Comparator>
void heapsort(vector<Comparable>& a, Comparator less_than)
{
	for (int i = a.size() / 2 - 1; i >= 0; --i)  /* buildHeap */
		percDown(a, less_than, i, a.size());
	for (int j = a.size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);               /* deleteMax */
		percDown(a, less_than, 0, j);
	}
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void merge(vector<Comparable>& a, Comparator less_than, vector<Comparable>& tmpArray,
	int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	// Main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (!less_than(a[rightPos], a[leftPos]))
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);

	while (leftPos <= leftEnd)    // Copy rest of first half
		tmpArray[tmpPos++] = std::move(a[leftPos++]);

	while (rightPos <= rightEnd)  // Copy rest of right half
		tmpArray[tmpPos++] = std::move(a[rightPos++]);

	// Copy tmpArray back
	for (int i = 0; i < numElements; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable>& a, Comparator less_than,
	vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, less_than, tmpArray, left, center);
		mergeSort(a, less_than, tmpArray, center + 1, right);
		merge(a, less_than, tmpArray, left, center + 1, right);
	}
}

/**
 * Mergesort algorithm (driver).
 */
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable>& a, Comparator less_than)
{
	vector<Comparable> tmpArray(a.size());

	mergeSort(a, less_than, tmpArray, 0, a.size() - 1);
}


/**
 * Quicksort Median of three pivot implementation
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable& median3(vector<Comparable>& a, Comparator less_than, int left, int right)
{
	int center = (left + right) / 2;

	if (less_than(a[center], a[left]))
		std::swap(a[left], a[center]);
	if (less_than(a[right], a[left]))
		std::swap(a[left], a[right]);
	if (less_than(a[right], a[center]))
		std::swap(a[center], a[right]);

	// Place pivot at position right - 1
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}


/* Quicksort Middle pivot implementation 
 * Uses Middle element partitioning
 * a is an array of Comparable items.
 * less_than is a comparator that compares array items based on user input
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksortMiddle(vector<Comparable>& a, Comparator less_than, int left, int right)
{
	if (left < right)
	{
		// Find middle element in array and assign it to the pivot
		int center = left + (right - left) / 2; 
		const Comparable pivot = a[center];

		// Place the pivot in the last position to anchor it
		std::swap(a[center], a[right - 1]); 

		int i = left-1, j = right-1;

		// Sort the array so that all items on the left are smaller than the pivot
		// and all items on the right are larger than pivot (this is reversed if using greater<int>{} class) 
		for (; ; ) {
			while (less_than(a[++i], pivot) && i < right) {};
			while (less_than(pivot, a[--j]) && j > left) {};
			if (i < j) {

				// Place elements on correct side of the pivot
				std::swap(a[i], a[j]);
			}
			else {
				break;
			}
		}

		// Replace pivot in correct position
		std::swap(a[i], a[right - 1]); 

		// Recursive calls to sub-arrays 
		if (j > left) {
			quicksortMiddle(a, less_than, left, i);		// Sort smaller elements
		}
		if (i < right) {
			quicksortMiddle(a, less_than, i + 1, right);	// Sort larger elements
		}

	}
}


/* Quicksort using First element as pivot implementation
 * Uses first element partitioning
 * a is an array of Comparable items.
 * less_than is a comparator that compares array items based on user input
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksortFirst(vector<Comparable>& a, Comparator less_than, int left, int right)
{
	if (left < right)
	{
		// Find the first element in the array and assign it to the pivot
		const Comparable pivot = a[left];

		// Place the pivot in the last position to anchor it
		std::swap(a[left], a[right - 1]); 

		int i = left-1, j = right-1;

		// Sort the array so that all items on the left are smaller than the pivot
		// and all items on the right are larger than pivot (this is reversed if using greater<int>{} class) 
		for (; ; ) {
			while (less_than(a[++i], pivot) && i < right) {};
			while (less_than(pivot, a[--j]) && j > left) {};

			if (i < j) {
				// Place elements on correct side of pivot
				std::swap(a[i], a[j]);
			}
			else {
				break;
			}
		}


		// Replace pivot in correct position
		std::swap(a[i], a[right-1]);

		// Recursive calls to sub-arrays 
		if (j > left) {
			quicksortFirst(a, less_than, left, i);		// Sort smaller elements
		}
		if (i < right) {
			quicksortFirst(a, less_than, i + 1, right);	// Sort larger elements
		}
	}
}



/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable>& a, Comparator less_than, int left, int right)
{
	if (left + 10 <= right)
	{
		const Comparable& pivot = median3(a, less_than, left, right);

		// Begin partitioning
		int i = left, j = right - 1;

		// Sort the array so that all items on the left are smaller than the pivot
		// and all items on the right are larger than pivot (this is reversed if using greater<int>{} class) 
		for (; ; )
		{
			while (less_than(a[++i], pivot)) {}
			while (less_than(pivot, a[--j])) {}
			if (i < j) {
				// Place elements on correct side of pivot
				std::swap(a[i], a[j]);
			}
			else {
				break;
			}
		}

		// Place pivot in correct position
		std::swap(a[i], a[right - 1]);  // Restore pivot

		quicksort(a, less_than, left, i - 1);     // Sort small elements
		quicksort(a, less_than, i + 1, right);	  // Sort large elements
	}

	// Do an insertion sort on the subarray if there are 10 items or less
	else {
		insertionSort(a, less_than, left, right);
	}
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable>& a, Comparator less_than)
{
	quicksort(a, less_than, 0, a.size() - 1);
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

            // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, left, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, right, k );
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
        
        auto chosenItem = items[ items.size( ) / 2 ];
        
        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }
        
        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!
        
        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );

/*
        items.clear( );
        items.insert( end( items ), begin( smaller ), end( smaller ) );
        items.insert( end( items ), begin( same ), end( same ) );
        items.insert( end( items ), begin( larger ), end( larger ) );
*/
    }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator lessThan )
{
    if( begin == end )
        return;
        
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        auto tmp = std::move( *p );
        for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
            *j = std::move( *(j-1) );
        *j = std::move( tmp );
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    insertionSort( begin, end, less<decltype(*begin )>{ } );
}



#endif
