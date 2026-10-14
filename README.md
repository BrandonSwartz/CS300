# CS300: Data Structures and Algorithms

## Portfolio Artifacts

### Project One: Data Structure Analysis
Project One evaluated the use of vectors, hash tables, and binary search trees for storing and retrieving course information. The analysis compares the runtime and memory considerations of each structure and considers their suitability for the requirements of the advising application.

### Project Two: Advising Assistance Program
Project Two implements the course-advising application in C++ using a binary search tree. The program loads course information from a file, stores the courses in the tree, prints the complete course list in alphanumeric order using an inorder traversal, and allows users to search for individual courses and their prerequisistes.

## Reflection

### What problem was I solving in the projects for this course?
The primary problem was to design and implement an application that could organize course information for academic advisers. The program needed to load course data, display all courses in alphanumeric order, and retrieve individual courses along with their prerequisites. Project One required me to approach the problem first from a design and analysis perspective by comparing possible data structures. Project Two then required me to prove that design through a working C++ implementation.

### How did you approach the problem? Consider why data structures are important to understand.
I approached the problem by first evaluating vectors, hash tables, and binary search trees rather than immediately beginning the implementation. I compared how each structure handled loading, searching, ordering, and memory usage. One of the more important lessons for me was learning not to think of a data structure as simply being fast or slow. Its efficiency depends on which operation is being performed and on conditions such as hash collisions or whether a binary search tree remains reasonably balanced. I ultimately selected a binary search tree because it provided a strong balance between course lookup and naturally ordered output through inorder traversal.

### How did you overcome any roadblocks you encountered while going through the activities or project?
Several roadblocks required me to slow down and examine how the program was structured and what it was doing rather than simply correcting syntax. These included understanding pointer relationships within the binary search tree, improving the precision of my pseudocode, analyzing worst-case runtime, separating public class interfaces from private helper functions, and handling file input correctly. I found that translating more complicated pointer expressions into plain-language statements helped me follow the program logic without relying on memorization. Testing also became an important part of the process. I tested invalid menu selections, missing files, malformed course records, duplicate courses, courses with varying numbers of prerequisites, lowercase search input, and attempts to access course information before data had been loaded.

### How has your work on this project expanded your approach to designing software and developing programs?
This course and its projects reinforced the importance of planning before implementation. Instead of starting with a preferred data structure and attempting to force the problem into it, I learned to begin with the program requirements and evaluate which structure best supports them. Project One provided the design and analysis before Project Two required implementation, which made the relationship between algorithm design and working code much clearer.

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
My approach has become more deliberate about organization, naming, comments, validation, and separation of responsibilities. I used public functions to provide a clear interface to the binary search tree while keeping internal helper functions private. Input validation, reuasable functions, descriptive naming, and cleanup of dynamically allocated memory were also incorporated to improve maintainability. These practices make the program easier to review, debug, modify, and use as a future reference.
