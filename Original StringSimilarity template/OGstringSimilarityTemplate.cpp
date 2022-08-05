#include <bits/stdc++.h>

using namespace std;

class similarity
{
private:
    pair<string, string> given_string_pair;
    pair<double, double> answer_pair;

public:
    similarity(pair<string, string> _given_string_pair) : given_string_pair(_given_string_pair){};

    pair<string, string> get_string_pair();
    void set_answer_pair(pair<double, double> &);

    void find_similarity();
    void print_answer();
    int find_levenschtein_distance();
    double levenschtein_distance_algorithm();
    double dice_coefficient_algorithm();
};

// function Declarations
pair<string, string> read_input();
int findMin(int, int, int);
void freeMemory(int **, int, int);
void fill_map(map<string, int> &, string &);
int find_intersections(map<string, int> &, map<string, int> &);

int main()
{
    cout << "This utility finds similarity value (between 0 - 1) of two strings." << endl;
    pair<string, string> given_string_pair;
    given_string_pair = read_input();

    similarity object(given_string_pair);
    object.find_similarity();
    object.print_answer();

    return 0;
}

pair<string, string> read_input()
{
    cout << "\nEnter two strings." << endl;
    string string1, string2;
    cout << "String_1 : ";
    cin >> string1;
    cout << "String_2 : ";
    cin >> string2;

    pair<string, string> input_strings(string1, string2); // making pair of given string and returning the pair
    return input_strings;
}

pair<string, string> similarity ::get_string_pair()
{
    return given_string_pair;
}

void similarity::set_answer_pair(pair<double, double> &my_ans_pair)
{
    answer_pair = my_ans_pair;
}

void similarity::find_similarity()
{
    pair<double, double> answer_pair(levenschtein_distance_algorithm(), dice_coefficient_algorithm());
    set_answer_pair(answer_pair);
}

double similarity::levenschtein_distance_algorithm()
{
    string string1 = get_string_pair().first;
    string string2 = get_string_pair().second;
    double levenshtein_ratio;

    int distance = find_levenschtein_distance();

    int greater_length = string1.length() > string2.length() ? string1.length() : string2.length();

    levenshtein_ratio = (double)(greater_length - distance) / (double)(greater_length);

    levenshtein_ratio = std::round(levenshtein_ratio * 100.0) / 100.0;

    return levenshtein_ratio;
}

int similarity::find_levenschtein_distance()
{
    string string1 = get_string_pair().first;
    string string2 = get_string_pair().second;

    // Declaring a 2D array on the heap dynamically:
    int length_1 = string1.length();
    int length_2 = string2.length();

    if (length_1 == 0 || length_2 == 0)
    {
        return length_1 == 0 ? length_2 : length_1;
    }

    int **d = new int *[length_1 + 1];
    for (int i = 0; i < length_1 + 1; i++)
        d[i] = new int[length_2 + 1];

    // Initialising first column:
    for (int i = 0; i < length_1 + 1; i++)
        d[i][0] = i;

    // Initialising first row:
    for (int j = 0; j < length_2 + 1; j++)
        d[0][j] = j;

    // Applying the algorithm:
    int insertion, deletion, replacement;
    for (int i = 1; i < length_1 + 1; i++)
    {
        for (int j = 1; j < length_2 + 1; j++)
        {
            if (string1[i - 1] == string2[j - 1])
            {
                d[i][j] = d[i - 1][j - 1];
            }
            else
            {
                // Choosing the best option:
                insertion = d[i][j - 1];
                deletion = d[i - 1][j];
                replacement = d[i - 1][j - 1];
                d[i][j] = 1 + findMin(insertion, deletion, replacement);
            }
        }
    }

    int answer = d[length_1][length_2];

    freeMemory(d, length_1 + 1, length_2 + 1);

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

double similarity::dice_coefficient_algorithm()
{
    string string1 = get_string_pair().first;
    string string2 = get_string_pair().second;

    // base cases
    if (string1.length() == 0 || string2.length() == 0) // if any string is empty, it means zero common bigrams,
        return 0;                                       // therefore dice coeff becomes zero

    if (string1 == string2) // Check to catch identical strings:
        return 1;

    if (string1.length() < 2 || string2.length() < 2) // avoid exception for single character searches
        return 0;

    map<string, int> string1_bigrams, string2_bigrams;

    fill_map(string1_bigrams, string1);

    fill_map(string2_bigrams, string2);

    int intersection = find_intersections(string1_bigrams, string2_bigrams);

    // calculate dice coefficient.....formula is twice of common bigrams divided by sum of the number of bigrams of two strings
    int total = string1.length() - 1 + string2.length() - 1;
    double dice_coefficient = (double)(intersection * 2) / (double)total;

    dice_coefficient = std::round(dice_coefficient * 100.0) / 100.0;

    return dice_coefficient;
}

void fill_map(map<string, int> &string_bigrams, string &str)
{
    for (int i = 0; i < (str.length() - 1); i++) // extract character bigrams from string1 and insert in map_1 i.e. string1_bigrams
    {
        string temp = str.substr(i, 2);

        if (string_bigrams.find(temp) != string_bigrams.end()) // if this bigram is already present, increase the frequency by 1
            string_bigrams[temp]++;

        else // if not present insert this bigram as new with freq as '1'
            string_bigrams.insert({temp, 1});
    }
}

int find_intersections(map<string, int> &string1_bigrams, map<string, int> &string2_bigrams)
{
    // gg3  gg6
    int intersection = 0;
    std::map<string, int>::iterator itr = string2_bigrams.begin();
    while (itr != string2_bigrams.end())
    {
        int lower_value = 0;
        if (string1_bigrams.find(itr->first) != string1_bigrams.end()) // if  the bigram is present in both maps, then compare frequencies of this bigram in both maps and grab the lower frequency.
        {
            lower_value = string1_bigrams.find(itr->first)->second < itr->second ? string1_bigrams.find(itr->first)->second : itr->second;
        }
        intersection += lower_value; // collecting lower frequencies of all common bigrams in 'intersection' variable
        itr++;
    }
    return intersection;
}

void similarity::print_answer()
{
    cout << endl;
    cout << "         Algorithm Name        | Similarity Value" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Levenshtein Distance Algorithm :    " << std::fixed << std::setprecision(2) << answer_pair.first << endl;
    cout << "Dice-Coefficient Algorithm     :    " << answer_pair.second << endl;
    cout << "\n\n";
}
