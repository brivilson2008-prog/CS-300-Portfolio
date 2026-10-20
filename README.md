# CS-300-Portfolio
CS 300: Data Structures and Algorithms Portfolio
What is in this repository
ProjectTwo.cpp: A C++ program for ABCU's advisors. It loads course data from a CSV file, prints all courses in alphanumeric order, and prints one course with its prerequisites.
CS_300_Project_One_Pseudocode_and_Runtime_Analysis.docx: My pseudocode and runtime analysis comparing a vector, a hash table, and a binary search tree.
Reflection
What was the problem I was solving in the projects for this course?

The advisors in the Computer Science department at ABCU needed a program to help them when they talk with students. The program had to do two main things: print a list of all the courses in alphanumeric order, and print the title and prerequisites for any one course. In Project One, I planned the solution with pseudocode and compared three data structures. In Project Two, I wrote the program in C++.

How did I approach the problem? Why are data structures important to understand?

I planned before I coded. In Project One, I wrote pseudocode for loading the file, creating course objects, and printing course information with a vector, a hash table, and a binary search tree. Then I checked how fast each one would be using Big O. This showed me why data structures matter. The choice changes how fast the program runs and how much work it takes to do a task. For example, a binary search tree keeps courses in order, so printing a sorted list is easy. A hash table is very fast for finding one course, but it has no order, so it must be sorted first. A vector is simple, but finding one item means checking items one by one.

In Project Two, I built the program in small steps. I wrote one function to load the file, one to find a course, one to print the sorted list, one to print a single course, and one for the menu. I stored the courses in a vector of Course objects and sorted them by course number before printing.

How did I overcome roadblocks?

I ran into a few problems in Project Two:

The program could not open the CSV file. Eclipse was running the program from a different folder than the one that held the file. I fixed this by finding the file's real location and typing the full path.
The filename was cut off at the first space. My code reads the filename with cin >>, which stops at a space, so the leftover words turned into bad menu choices. I renamed the file so it had no spaces.
One prerequisite showed "title unavailable." MATH201 loaded fine, but it failed when it was listed as a prerequisite. I noticed it only happened to the last item on a line. The file had Windows-style line endings, which left a hidden carriage return on the end of each line. I fixed it by removing that character right after reading each line.

These problems taught me to test every menu option and to check bad input, like a course that does not exist or choosing an option before loading the data.

How has this work expanded my approach to designing software and developing programs?

I now plan first instead of jumping straight into code. Writing pseudocode helped me think through the steps and catch mistakes early. I also learned to compare options before choosing one, since every data structure has tradeoffs. And I think more about what can go wrong, like missing files, bad menu choices, and data that is not in the format I expected.

How has this work changed the way I write programs that are maintainable, readable, and adaptable?

I now keep each function to one job and give it a clear name, like findCourse and printCourseList. I use a struct to keep a course's data together, and I add comments to explain the purpose of each section. I reuse findCourse in more than one place instead of copying the same code. This also makes the program easier to change. If I switched to a different data structure, I would only need to change the load, find, and print functions, and the menu could stay the same.
