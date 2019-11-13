#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setprecision;
using std::fixed;
#include <fstream>
using std::ifstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include <algorithm> 
using std::stable_sort;
using std::min;
using std::max;
#include <map>
using std::map;
#include <utility>
using std::pair;

bool sort_by_sec(const pair<string,int> &a, // sorts a pair by the second value
              const pair<string,int> &b)   
{ 
    return (a.second < b.second); 
} 

int main() {
    ifstream input("common_passwords.txt");
    vector<string> passwords;               // vector for all passwords
    vector<string> similar_passwords;       // vector for all common passwords
    string x;                               // temperary storage for passwords from file
    string given;                           // given password to check

    while (input >> x) {                    // loop to store all passwords
        passwords.push_back(x);
    }
    cout << "Give me a password:" << endl;
    cin >> given;
    cout << "You provided a password of " << given << endl;
    int size_given = static_cast<int>(given.size());
    int num_sim = 0;          
    int num_dif = 0;
    map<string,int> word_to_num;
    for (auto word : passwords) {           // loop to compare passwords
        for (int i = 0; i < min(static_cast<int>(word.size()), size_given); i++) {
            if (word[i] == given[i]) {
                num_sim++;
            }
        }
        num_dif = static_cast<int>(max(given.size(),word.size()) - num_sim);
        word_to_num[word] = num_dif;
        num_sim = 0;
    }
    vector<pair<string,int>> word_to_num_vec;
    for (auto e : word_to_num) {
        word_to_num_vec.push_back(e);
    }
    stable_sort(word_to_num_vec.begin(),word_to_num_vec.end(),sort_by_sec); // sorting the vector of passwords and similar int
    int j = 0;
    if (word_to_num_vec[0].second != word_to_num_vec[1].second) {           // outputting results 
        cout << "The most similar passwords to " << given << " are:" << endl;
        cout << word_to_num_vec[0].first << ", "<< endl;
        cout << "All of which are " << word_to_num_vec[0].second << " character(s) different." << endl;
    } else {
        cout << "The most similar passwords to " << given << " are:" << endl;
        while (word_to_num_vec[j].second == word_to_num_vec[j+1].second) {
            cout << word_to_num_vec[j].first << ", ";
            j++;
        }
        cout << word_to_num_vec[j].first << ", " << endl;
        cout << "All of which are " << word_to_num_vec[j].second << " character(s) different." << endl;
    }
}