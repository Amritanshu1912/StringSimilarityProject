#ifndef SIMILARITYPROJECT_H
#define SIMILARITYPROJECT_H
  
#include <bits/stdc++.h>
using namespace std;

// function Declarations
pair<double, double> find_similarity(pair<string, string>);

// funtions associated with Lavenshtein Distance Algorithm
double levenschtein_distance_algorithm(pair<string, string>);
int find_levenschtein_distance(pair<string, string>);
int findMin(int, int, int);
void freeMemory(int **, int, int);

// funtions associated with Dice Coefficient Algorithm
double dice_coefficient_algorithm(pair<string, string>);
void fill_map(map<string, int> &, string &);
int find_intersections(map<string, int> &, map<string, int> &);

// function definitons

pair<double, double> find_similarity(const pair<string, string> my_string_pair)
{
    pair<double, double> answer_pair(levenschtein_distance_algorithm(my_string_pair), dice_coefficient_algorithm(my_string_pair));
    return answer_pair;
}

double levenschtein_distance_algorithm(const pair<string, string> my_string_pair)
{
    string string1 = my_string_pair.first;
    string string2 = my_string_pair.second;
    // base cases
    // if both strings are empty, distance becomes 0, ratio becomes 0/0, we should return 0 in such case
    // if any string is empty, it means they are not all similar, therefore ratio becomes zero
    if (string1.length() == 0 || string2.length() == 0)
        return 0;

    // Check to catch identical strings:
    if (string1 == string2)
        return 1;

    int distance = find_levenschtein_distance(my_string_pair);
    int greater_length = string1.length() > string2.length() ? string1.length() : string2.length();
    double levenshtein_ratio = (double)(greater_length - distance) / (double)(greater_length);

    levenshtein_ratio = std::round(levenshtein_ratio * 100.0) / 100.0;
    return levenshtein_ratio;
}

int find_levenschtein_distance(const pair<string, string> my_string_pair)
{
    string string1 = my_string_pair.first;
    string string2 = my_string_pair.second;

    // Declaring a 2D array on the heap dynamically:
    int length_1 = string1.length();
    int length_2 = string2.length();
    int **dp = new int *[length_1 + 1];
    for (int i = 0; i < length_1 + 1; i++)
        dp[i] = new int[length_2 + 1];

    // Initialising first column:
    for (int i = 0; i < length_1 + 1; i++)
        dp[i][0] = i;

    // Initialising first row:
    for (int j = 0; j < length_2 + 1; j++)
        dp[0][j] = j;

    // Applying the algorithm:
    int insertion, deletion, replacement;
    for (int i = 1; i < length_1 + 1; i++)
    {
        for (int j = 1; j < length_2 + 1; j++)
        {
            if (string1[i - 1] == string2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                // Choosing the best option:
                insertion = dp[i][j - 1];
                deletion = dp[i - 1][j];
                replacement = dp[i - 1][j - 1];
                dp[i][j] = 1 + findMin(insertion, deletion, replacement);
            }
        }
    }

    int answer = dp[length_1][length_2];

    freeMemory(dp, length_1 + 1, length_2 + 1);

    return answer;
}

int findMin(int x, int y, int z)
{
    if (x <= y && x <= z)
        return x;
    else if (y <= x && y <= z)
        return y;
    else
        return z;
}

void freeMemory(int **arr, int a, int b)
{
    for (int i = 0; i < a; i++)
        delete[] arr[i];

    delete[] arr;
}

double dice_coefficient_algorithm(const pair<string, string> my_string_pair)
{
    string string1 = my_string_pair.first;
    string string2 = my_string_pair.second;

    // base cases
    // if any string is empty, it means zero common bigrams, therefore dice coeff becomes zero
    if (string1.length() == 0 || string2.length() == 0)
        return 0;

    // Check to catch identical strings:
    if (string1 == string2)
        return 1;

    // avoid exception for single character searches
    if (string1.length() < 2 || string2.length() < 2)
        return 0;

    map<string, int> string1_bigrams, string2_bigrams;
    // calling fill_map function which parses the string(for eg - string1) and stores all the bigrams in map(for eg - strings1_bigrams)
    fill_map(string1_bigrams, string1);
    fill_map(string2_bigrams, string2);
    // find_intersection finds the number of common bigrams in both maps
    int intersection = find_intersections(string1_bigrams, string2_bigrams);

    // calculating dice coefficient
    // formula is twice of common bigrams divided by sum of the total number of bigrams of two strings
    int total = string1.length() - 1 + string2.length() - 1;
    double dice_coefficient = (double)(intersection * 2) / (double)total;

    dice_coefficient = std::round(dice_coefficient * 100.0) / 100.0;

    return dice_coefficient;
}

void fill_map(map<string, int> &string_bigrams, string &str)
{
    // extract character-bigrams from string1 and insert in map_1 i.e. string1_bigrams
    for (int i = 0; i < (str.length() - 1); i++)
    {
        string temp = str.substr(i, 2);
        // if this bigram is already present, increase the frequency by 1
        if (string_bigrams.find(temp) != string_bigrams.end())
            string_bigrams[temp]++;

        // if not present insert this bigram as new with freq as '1'
        else
            string_bigrams.insert({temp, 1});
    }
}

int find_intersections(map<string, int> &string1_bigrams, map<string, int> &string2_bigrams)
{
    int intersection = 0;
    // declaring iterator 'itr' to traverse map
    std::map<string, int>::iterator itr = string2_bigrams.begin();

    while (itr != string2_bigrams.end())
    {
        int lower_value = 0;
        // if the bigram is present in both maps, then compare frequencies of this bigram in both maps and grab the lower frequency.
        if (string1_bigrams.find(itr->first) != string1_bigrams.end())
            lower_value = string1_bigrams.find(itr->first)->second < itr->second ? string1_bigrams.find(itr->first)->second : itr->second;

        // collecting lower frequencies of all common bigrams in 'intersection' variable
        intersection += lower_value;
        itr++;
    }
    return intersection;
}

#endif