//============================================================================
// 
// Name        : ProjectTwo.cpp
// Author      : Brandon A. Swartz
// Version     : 1.0
// Description : Project Two in C++
// References  :
//		SNHU CS-300 zyBook
//		SNHU CS-300 Project One and correlating assignments
//		SNHU CS-300 Project Two Guidelines and Rubric
//		SNHU CS-300 Project Two Sample Input File
//		SNHU CS-300 Project Two Sample Output
//		cppreference.com - std::vector, std::ifstream, std::getline
//		Microsoft Learn - C++ pointers and references
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>

using namespace std;

// Courses are to have unique course numbers
// prerequisites vary between courses from 0 on up
struct Course {
	string courseNumber;
	string courseName;
	vector<string> prerequisites;
};

// Node structure to hold a course and pointers to left and right child nodes
struct Node {
	Course course;
	Node* left;
	Node* right;

	// Creates a new leaf node with pointers beginning as nullptr
	Node(Course aCourse) {
		course = aCourse;
		left = nullptr;
		right = nullptr;
	}
};

// Manages Course objects using a binary search tree ordered by course number
class BinarySearchTree {
private:
	// Pointer to the root node of the binary search tree, nullptr if the tree is empty
	Node* root;

	void addNode(Node* node, Course course);

	void printInOrder(Node* node);

	void validatePrerequisites(Node* node);

	void destroyTree(Node* node);

public:
	// Constructs an initially empty binary search tree
	BinarySearchTree() {
		root = nullptr;
	}


	// Insert function for binary search tree
	// If tree empty, new course becomes root
	// Otherwise, insertion delegated to the recursive insert function addNode() helper
	void insert(Course course) {
		if (root == nullptr) {
			root = new Node(course);
		}
		else {
			addNode(root, course);
		}
	}

	// Searches the BST for a match
	// Returns a pointer to the matching course if found
	// Or nullptr if not found
	Course* search(string courseNumber) {
		Node* current = root;

		while (current != nullptr) {

			if (courseNumber == current->course.courseNumber) {
				return &current->course;
			}

			else if (courseNumber < current->course.courseNumber) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		// Reaching nullptr means the course was not found
		return nullptr;
	}

	// Prints all courses in ascending alphanumeric order
	void printCourseList() {
		printInOrder(root);
	}

	// Validates prerequisite references for all courses
	void validatePrerequisites() {
		validatePrerequisites(root);
	}

	// Destructor to free memory used by the binary search tree
	~BinarySearchTree();
};

void BinarySearchTree::addNode(Node* node, Course course) {

	// Prevent duplicate course numbers from being inserted
	if (course.courseNumber == node->course.courseNumber) {
		cout << "Duplicate course number: "
			<< course.courseNumber << endl;
		return;
	}

	// Course numbers smaller than current node belong in left subtree
	if (course.courseNumber < node->course.courseNumber) {

		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			addNode(node->left, course);
		}
	}

	// Course numbers larger than current node belong in right subtree
	else {

		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			addNode(node->right, course);
		}
	}
}

void BinarySearchTree::printInOrder(Node* node) {

	if (node != nullptr) {

		// Visit the left first
		printInOrder(node->left);

		// Process the current node
		cout << node->course.courseNumber << ", "
			<< node->course.courseName << endl;

		// Visit the right last
		printInOrder(node->right);
	}
}

bool loadCourses(string filename, BinarySearchTree& courses) {

	ifstream file(filename);

	// Stop loading if the file cannot be opened
	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return false;
	}

	string line;

	// Process the input file one course record at a time
	while (getline(file, line)) {
		istringstream iss(line);
		string field;
		vector<string> fields;

		// Separate each CSV field at a comma
		while (getline(iss, field, ',')) {
			fields.push_back(field);
		}

		// A valid course requires at least a course number and name
		if (fields.size() < 2) {
			cout << "Invalid course record: " << line << endl;
			continue;
		}

		if (fields[0].empty() || fields[1].empty()) {
			cout << "Invalid course record: " << line << endl;
			continue;
		}

		Course course;
		course.courseNumber = fields[0];
		course.courseName = fields[1];

		// Remaining fields are prerequisites, if any
		for (size_t i = 2; i < fields.size(); ++i) {
			if (!fields[i].empty()) {
				course.prerequisites.push_back(fields[i]);
			}
		}

		courses.insert(course);
	}

	file.close();
	return true;
}

	// Validates that all prerequisites for each course exist in the BST
void BinarySearchTree::validatePrerequisites(Node* node) {

	if (node != nullptr) {

		// Traverse the left first
		validatePrerequisites(node->left);

		// Check every prerequisite belonging to the current course
		for (const string& prerequisite : node->course.prerequisites) {

			if (search(prerequisite) == nullptr) {
				cout << "Warning: Prerequisite " 
					<< prerequisite
					<< " for " 
					<< node->course.courseNumber
					<< " was not found."
					<< endl;
			}
		}

		// Traverse the right last
		validatePrerequisites(node->right);
	}
}

// Recursively deletes all nodes in the BST
BinarySearchTree::~BinarySearchTree() {
	destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* node) {
	if (node != nullptr) {
		// Delete the left subtree first
		destroyTree(node->left);
		// Delete the right subtree next
		destroyTree(node->right);
		// Delete the current node last
		delete node;
	}
}

// Converts a course number to uppercase for case-insensitive searching
string toUpperCase(string value) {
	for (char& character : value) {
		character = toupper(static_cast<unsigned char>(character));
	}
	return value;
}

// Searches for and displays a course along with its prerequisites information
void printCourseInformation(BinarySearchTree& courses, string courseNumber) {

	courseNumber = toUpperCase(courseNumber);

	Course* foundCourse = courses.search(courseNumber);

	if (foundCourse == nullptr) {
		cout << "Course " << courseNumber << " was not found." << endl;
		return;
	}
	else {
		cout << foundCourse->courseNumber << ", "
			<< foundCourse->courseName << endl;
	}
	if (foundCourse->prerequisites.empty()) {
		cout << "Prerequisites: None" << endl;
		return;
	}
	else {
		cout << "Prerequisites: " << endl;

		for (const string& prerequisiteNumber : foundCourse->prerequisites) {
					
			Course* prerequisite = courses.search(prerequisiteNumber);

			if (prerequisite != nullptr) {
				cout << prerequisite->courseNumber << ", "
					<< prerequisite->courseName << endl;
			}
			else {
				cout << prerequisiteNumber
					<< ", course information unavailable" 
					<< endl;
			}
		}		
	}
}
int main() {

	BinarySearchTree courses;
	bool dataLoaded = false;
	int choice = 0;

	cout << "Welcome to the course planner." << endl;

	while (choice != 9) {

		cout << endl;
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit." << endl;
		cout << endl;
		cout << "What would you like to do? ";

		// Validate user input for menu selection
		if (!(cin >> choice)) {

			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cout << "Invalid input. Please enter a menu number." << endl;
			continue;
		}

		if (choice == 1) {

			string filename;

			cout << "Enter the course data file name: ";
			// Read complete file name or path, including spaces, and discard leading whitespace
			// filename alone is resolved relative to program's working directory
			// Use of full path is allowed, but not required unless file is outside the working directory
			getline(cin >> ws, filename);

			if (loadCourses(filename, courses)) {
				courses.validatePrerequisites();
				dataLoaded = true;

				cout << "Course data loaded successfully." << endl;
			}
		}

		else if (choice == 2) {

			if (!dataLoaded) {
				cout << "Course data must be loaded first." << endl;
			}

			else {
				cout << endl;
				cout << "Here is a sample schedule:" << endl;
				cout << endl;

				courses.printCourseList();
			}
		}

		else if (choice == 3) {

			if (!dataLoaded) {
				cout << "Course data must be loaded first." << endl;
			}

			else {
				string courseNumber;

				cout << "What course do you want to know about? ";
				cin >> courseNumber;

				printCourseInformation(courses, courseNumber);
			}
		}

		else if (choice == 9) {
			cout << "Thank you for using the course planner!" << endl;
		}

		else {
			cout << choice << " is not a valid option." << endl;
		}
	}

	return 0;
}