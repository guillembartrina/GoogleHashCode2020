#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

#define INPUT_FILE "d_tough_choices.txt"
#define OUTPUT_FILE "sol4.txt"

//define data and solution
struct library
{
    int library_id;
    unordered_set<int> id;
    int num_books;
    int signup_time;
    int books_per_day;
    float average;
};

vector <int> books; //books score
vector <library> libraries;
int days;
int num_libraries;
int num_books;

struct sol_library
{
    int id_lib;
    int num_books;
    vector <int> id;
};

struct solution
{
    int num_lib;
    vector <sol_library> libraries;
};

solution sol;

void read_from_file()
{
    ifstream inFile(INPUT_FILE);
    inFile >> num_books >> num_libraries >> days;
    books = vector <int>(num_books);
    libraries = vector <library>(num_libraries);
    for(int i = 0; i < num_books; ++i) inFile >> books[i];
    for(int i = 0; i < num_libraries; ++i)
    {
        int sz;
        inFile >> sz;
        libraries[i].library_id = i;
        inFile >> libraries[i].signup_time;
        inFile >> libraries[i].books_per_day;
        float avg = 0.f;
        for(int j = 0; j < sz; ++j)
        {
            int tmp;
            inFile >> tmp;
            avg += (float)books[tmp];
            libraries[i].id.insert(tmp);
        }
        libraries[i].num_books = libraries[i].id.size();
        libraries[i].average = avg/libraries[i].num_books;
    }
}

void write_to_file() 
{
    ofstream outFile(OUTPUT_FILE);
    outFile << sol.num_lib << endl;
    for(int i = 0; i < sol.num_lib; ++i)
    {
        outFile << sol.libraries[i].id_lib << " " << sol.libraries[i].num_books << endl;
        bool first = true;
        for(int j = 0; j < sol.libraries[i].num_books; ++j) 
        {
            if(not first) outFile << " ";
            outFile << sol.libraries[i].id[j];
            first = false;
        }
        outFile << endl;
    }
    cout << "Output file overwritten with solution" << endl;
}
