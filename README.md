# Sorting-Algorithm-Analyzer-with-Statement-Counting
 A C++ project that implements various sorting algorithms, tracks execution time, and performs statement-based complexity analysis.
 This repository provides a comprehensive implementation of the following sorting algorithms in C++:

Insertion Sort
Bubble Sort
Selection Sort
Quick Sort
Merge Sort
Count Sort
Bucket Sort
Radix Sort
Key Features:

Accurate Statement Counting: Each algorithm includes careful instrumentation to count the number of key operations performed during sorting.
Timing Measurements: The code utilizes high-resolution timers to measure execution time of each algorithm.
Formatted Output: The program processes input from a text file (comma-separated integers), and generates a well-structured output file presenting:
Sorted input array
Best and worst performing algorithms based on execution time
A table comparing execution time and statement counts for each algorithm.
How to Use

Compile the code:  (Example using g++)

Bash
g++ -std=c++17 main.cpp -o sorting_analyzer 
Use code with caution.
Create an input file (input.txt):

23,45,12,67,1,56,89,16,56,23,154,25,1,25,23,256
10,5,8,1,3,18
# ... more test arrays
Run the executable:

Bash
./sorting_analyzer input.txt output.txt
Use code with caution.
Project Goals:

Provide a tool for learning about sorting algorithm behavior.
Facilitate analysis of algorithm performance based on input characteristics.
Demonstrate the relationship between theoretical complexity and practical execution.
