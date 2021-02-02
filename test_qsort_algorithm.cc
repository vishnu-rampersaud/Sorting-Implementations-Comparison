/*
	Author: Vishnu Rampersaud
	Date: 11/22/2019

	This is the test_qsort_algorithm.cc file for Part(2) of the assignment.
	This code tests variations of the quicksort algorithm which include, median of three, 
	middle pivot, and first pivot. 

	
*/

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

namespace {

// Verifies the sorted order of the vector based on the comparator @less_than (less, greater)
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable>& input, Comparator less_than) {

	// Checks to see if vector size is >= 2. If it is not, then there is nothing to compare
	if (input.size() >= 2) {

		// Check all adjacent elements to see if they're in the right order
		for (unsigned int i = 0; i < input.size() - 1; i++) {
			// if the current index is (<=) or (>=) to the next index, then it is in order; move to the next value
			// using (<=) or (>=) to check depends on what the user specifies for the less_than variable
			if (!less_than(input[i + 1], input[i])) {
				continue;
			}
			// if the current index is not (<=) or (>=) to the next index, then it is not in the correct order. 
			// Using (<=) or (>=) to check depends on what the user specifies for the less_than variable
			else {
				return false;
			}
		}

	}
	
	// If the vector size is less than 2, then it can't be sorted/ Already sorted with one element 
	// If no errors were found, the vector is in sorted order; return true
	return true;
}

// Quicksort implementation using the median of three as a pivot
template <typename Comparable, typename Comparator>
void QuickSortMedian3(vector<Comparable>& a, Comparator less_than) {
	quicksort(a, less_than);
}

// Quicksort implementation using the middle value as a pivot 
template <typename Comparable, typename Comparator>
void QuickSortMiddle(vector<Comparable>& a, Comparator less_than) {
	quicksortMiddle(a, less_than, 0, a.size());
}

// Quicksort implementation using the first value as a pivot 
template <typename Comparable, typename Comparator>
void QuickSortFirst(vector<Comparable>& a, Comparator less_than) {
	quicksortFirst(a, less_than, 0, a.size());
}

// @ sort_type: The type of sorting method that's going to be used 
// @ test_vector_: Vector that needs to be sorted
// @ comparison_type: less<int>{} or greater<int>{}
// @ begin: The start time of the code
// @ end: the end time of the code 
// Function that prints out the amount of time it takes one sorting algorithm to run. 
// It also verifies the sorted order of the resulting vector 
template <typename Clock>
void printDurationAndVerify(const string& sort_type, vector<int>& test_vector_, const string& comparison_type, const Clock& begin, const Clock& end)
{
	cout << "---------------------------" << endl;
	cout << sort_type << ":\nRuntime: ";

	// Print the total nanoseconds and milliseconds taken to compute the sorting method 
	cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << ", ";
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

	// Verify the sorted order of the vector based on the comparison_type variable 
	if (comparison_type == "less") {
		cout << "Verified: " << VerifyOrder(test_vector_, less<int>{}) << endl;
	}
	else if (comparison_type == "greater") {
		cout << "Verified: " << VerifyOrder(test_vector_, greater<int>{}) << endl;
	}
}

// @ sort_type: The type of sorting method that's going to be used 
// @ test_vector_: Vector that needs to be sorted
// @ comparison_type: less<int>{} or greater<int>{}
// Function that tests how long a specified sorting algorthm takes to run while sorting it based on the user preference
// Calls the function printDurationAndVerify() to output the data computed and to verify of the vector is in the correct sorted order
void SortAndTestTiming(const string& sort_type, vector<int>& test_vector_, const string& comparison_type)
{
	// Assign alternative name (Time) to chrono::high_resolution_clock type for convenience
	typedef chrono::high_resolution_clock Time; 

	// Check to see which type of sorting method is used
	if (sort_type == "Median of three") {
		// Checks to see which type of sorted order the vector needs to be sorted in (less, greater) 
		if (comparison_type == "less") {
			// start of piece of code to time
			const auto begin = Time::now(); 
			QuickSortMedian3(test_vector_, less<int>{});
			// End of piece of code to time
			const auto end = Time::now(); 
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end); 
		}

		else if (comparison_type == "greater") {
			// Start of piece of code to time
			const auto begin = Time::now();
			QuickSortMedian3(test_vector_, greater<int>{});
			// End of piece of code to time
			const auto end = Time::now();
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end);
		}

		else {
			cout << "Invalid Comparison type. Please use 'less' or 'greater'"; 
			return;
		}
	}

	else if (sort_type == "Middle") {
		// Checks to see which type of sorted order the vector needs to be sorted in (less, greater) 
		if (comparison_type == "less") {
			// start of piece of code to time
			const auto begin = Time::now();
			QuickSortMiddle(test_vector_, less<int>{}); 
			// End of piece of code to time
			const auto end = Time::now();
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end);
		}

		else if (comparison_type == "greater") {
			// start of piece of code to time
			const auto begin = Time::now();
			QuickSortMiddle(test_vector_, greater<int>{});
			// End of piece of code to time
			const auto end = Time::now();
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end);
		}

		else {
			cout << "Invalid Comparison type. Please use 'less' or 'greater'";
			return;
		}
	}

	else if (sort_type == "First") {
		// Checks to see which type of sorted order the vector needs to be sorted in (less, greater) 
		if (comparison_type == "less") {
			// start of piece of code to time
			const auto begin = Time::now();
			QuickSortFirst(test_vector_, less<int>{}); 
			// End of piece of code to time
			const auto end = Time::now();
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end);
		}

		else if (comparison_type == "greater") {
			// start of piece of code to time
			const auto begin = Time::now();
			QuickSortFirst(test_vector_, greater<int>{});
			// End of piece of code to time
			const auto end = Time::now();
			// Calls function to verify the order, calculate and print the time duration for the sorting algorithm
			printDurationAndVerify(sort_type, test_vector_, comparison_type, begin, end);
		}

		else {
			cout << "Invalid Comparison type. Please use 'less' or 'greater'";
			return;
		}
	}

	else {
		cout << "Invalid Sort Type. Please retry using quick_median, quick_middle, or quick_first" << endl;
		return;
	}
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
	vector<int> a;
	for (size_t i = 0; i < size_of_vector; ++i)
		a.push_back(rand());
	return a;
}

// Generates and returns sorted vector of size @size_of_vector.
vector<int> GenerateSortedVector(size_t size_of_vector) {
	vector<int> a;
	for (size_t i = 1; i <= size_of_vector; ++i)
		a.push_back(i);
	return a;
}


}  // namespace

// Function to print out vector values. Only used to test
template <typename Comparable>
void print_vector(const vector<Comparable>& a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (i == 0)
			cout << "{" << a[i] << ", ";
		else if (i < a.size() - 1)
			cout << a[i] << ", ";
		else
			cout << a[i] << "}";
	}
	cout << endl;
}

// Main function
int main(int argc, char** argv) {

	// Check to make sure all arguments were inputted
	if (argc != 4) {
		cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
		return 0;
	}

	// Get input type, random or sorted 
	const string input_type = string(argv[1]);
	// Initialize input_size
	const int input_size = stoi(string(argv[2]));
	// Get comparison type, less than or greater than 
	const string comparison_type = string(argv[3]);

	// Check to see if valid entry was entered
	if (input_type != "random" && input_type != "sorted_small_to_large") {
		cout << "Invalid input type" << endl;
		return 0;
	}

	// Check to see if valid entry was entered
	if (input_size <= 0) {
		cout << "Invalid size" << endl;
		return 0;
	}

	// Check to see if valid entry was entered
	if (comparison_type != "less" && comparison_type != "greater") {
		cout << "Invalid comparison type" << endl;
		return 0;
	}
  
	// Display the specifications to the user
	cout << "Testing quicksort: " << input_type << " " << input_size << " numbers " 
		<< comparison_type << endl;

	// Generate and fill vector based on user input
	vector<int> input_vector;

	if (input_type == "random") {
		input_vector = GenerateRandomVector(input_size);
	}
	else {
		input_vector = GenerateSortedVector(input_size);
	}
  
	// Create copies of the generated vector to pass through each sorting algorithm 
	vector<int> quicksort_median_vector_ = input_vector;
	vector<int> quicksort_middle_vector_ = input_vector;
	vector<int> quicksort_first_vector_ = input_vector;
	string quick_median = "Median of three", quick_middle = "Middle", quick_first = "First";

	// Use all three quicksort sorting methods (median of three, middle, first) 
	// and sort the generated vector based on user input. 
	// Time all these sorting methods and display the amount of time taken to complete each method
	// along with if it is sorted properly or not (Verification status). 
	SortAndTestTiming(quick_median, quicksort_median_vector_, comparison_type);
	SortAndTestTiming(quick_middle, quicksort_middle_vector_, comparison_type);
	SortAndTestTiming(quick_first, quicksort_first_vector_, comparison_type);


	return 0;
}
