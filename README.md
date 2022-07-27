# String Similarity Project

This project calculates the similarity values of two strings.
It uses two algorithms, namely **Levenshtein Distance Algorithm** and **Dice Coefficient Algorithm** and produces two decimal values ranging between 0 to 1, 0 means not at all similar and 1 means that the two strings are same.

# Components of the project

I have added test cases using GoogleTest framework using CMAKE. 
1. CMakelists.txt contains the configurations for Cmake. 
2. similarityProject.h is header file containing all the function implemented to calculate the similarity ratios using two algorithms.
3. similarityProjectTest.cpp is our test file that contains testcases. 

The 'Original StringSimilarity template' folder contains 'OGstringSimilarityTemplate.cpp' which is a C++ program which asks the user to enter two strings and produces a pair of two decimal values. The first decimal value of the pair is calculated using Levenshtein Distance Algorithm and the second decimaml value is calculated using Dice coefficient Algorithm.

## A brief description of functions used in the header file 

- find_similarity() - This function accepts a pair of strings as input, calls the two Algorithm functions which calculate similarity ratios and returns a pair of 'double' as final answer. I didnt use this function in test file because GTEST's ASSERT and EXPECT_EQ functions dont allow checking a pair with anohter pair. I have to use GMOCK for that, which can be implemented in later iterations of this project.

- levenschtein_distance_algorithm() - accepts input of type pair<stirng, string> which is the pair of given strings. This calls another function (find_levenshtein_distance() which calculates the levenshtein distance for the given strings). Then computes the ratio using the formula -> (length of bigger string - levenshtein distance of two strings) / greater length. returns the ratio. 

- find_levenschtein_distance() - finds levenshtein distance of two strings. Algorithm is applied using Dynamic programing that uses a 2D matrix. All cells are initialised with 0's and are filled in rows-first fashion from left to right. If string1[i - 1] == string2[j - 1] then dp[i][j] = dp[i - 1][j - 1] else it takes the minimum of dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1] and adds 1 to it. Answer is collected from the lower-most right-most  cell of the matrix.

- dice_coefficient_algorithm() - accepts pair of string, initiallises two hashmaps to store bigrams, calls fill_map() function to fill these maps with bigrams of two given strings in two different maps. Then calls find_intersection() function to find common bigrams in the filled maps. Calculates the dice coefficient ratio using the formula -> (2 * number of common bibgrams) / ( total bigrams of string 1 + total bigrams of string 2) 

- fill_map() - accepts a map (passing by reference) and a string. Parses the string into bigrams and stores the bigrams as key and their frequency as value. For eg - string str = "sampleple", bigrams and freq of this are sa 1, am 1, mp 1, pl 2, le 2, ep 1, pl 1, le 1. Storing frequency in map instead of just storing bigrams in a set helps in finding true similarity of edge cases like str_1 ="aa" and str_2 = "aaaaa". If we use set for this test case, similarity ratio would be 1 which is clearly not the case.

- find_intersections() - finds common bigrams by checking if the bigrams stored in map2 are present in map1. If present, we are collecting the lesser value from both the maps of that bigram. 

## similarityProjectTest.cpp 
It stores the testcases which are to be run. The tests are currently configured for the two algorithms individually. It tests both algorithms with inputs 
1. where any or both of the  givenstrings are empty
2. where both are non - empty  
3. where strings have spaces between them. Spaces are considered as characters in this project. Bigrams having space are not discarded asinvalid bigrams. 

Currently all the test cases in the test file pass for all the given inputs. More test cases can be added in the test file as per convenince.

# Directions to build and run the similarityProjectTest.cpp 

I used cmake and googletest with vscode and Windows11. I used the gcc compile kit to build cmake. 

- Install cmake and add path to environment variables
- Clone this(stringSimilarityProject) repository in an empty folder. 
- Clone googletest repo in the same folder. To do that open terminal in the same directory and type
 
```
git clone https://github.com/google/googletest.git -b release-1.12.0.
cd googletest
mkdir build
cd build
cmake .. -DBUILD_GMOCK=OFF # we do not need GMOCK for this project
```
- You should see a folder named googletest in you cwd. Cmake would ask to choose a compiler kit to build and configure cmake files. I used gcc because it was the only active kit I had installed.

come to root directory and open terminal and type
```
mkdir build
```
- Your root directory should now have folder named 'build'. Go to build directory.

then type the following in terminal to build and run test file
```
cmake ..
make
./similarityProjectTest.cpp
```
