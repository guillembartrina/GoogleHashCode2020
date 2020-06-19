#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;

#define INPUT_FILE "c_incunabula.txt"
#define OUTPUT_FILE "solc.txt"

//define data and solution
struct library
{
    vector<int> id;
    int nb;
    int myid;
    int signup_time;
    int books_per_day;
    int score = 0;
    double avg = 0;
};

vector <int> books; //books score
vector<bool> books2;
vector <library> libraries;
vector<bool> libraries2;
int days;
int num_libraries;
int num_books;
vector< vector<int> > bl;


struct myComp {

bool operator()(const library* l1, const library* l2) {
    return l1->avg <= l2->avg;
}

};

//priority_queue<library*, vector<library*>, myComp> pq;

void read_from_file()
{
    ifstream inFile(INPUT_FILE);
    inFile >> num_books >> num_libraries >> days;
    books = vector <int>(num_books);
    books2 = vector<bool>(num_books,true);
    bl = vector< vector<int> >(num_books);
    libraries2 = vector<bool>(num_books,true);
    libraries = vector <library>(num_libraries);
    for(int i = 0; i < num_books; ++i) inFile >> books[i];
    for(int i = 0; i < num_libraries; ++i)
    {
        int sz;
        inFile >> sz;
        libraries[i].id = vector <int>(sz);
        inFile >> libraries[i].signup_time;
        inFile >> libraries[i].books_per_day;
        for(int j = 0; j < sz; ++j) {
            inFile >> libraries[i].id[j];
            libraries[i].score += books[libraries[i].id[j] ];
            bl[libraries[i].id[j] ].push_back(libraries[i].myid);
        }
    }
    for (int i = 0; i < num_libraries; ++i) {
        libraries[i].myid = i;
        libraries[i].nb = (libraries[i].id).size();
        libraries[i].avg = double(libraries[i].score)/double(libraries[i].signup_time);
        //pq.push(&libraries[i]);
    }
    
}

void greedy() {
    int day = 0;
    int ns = 0;
    while (day < days) {
        priority_queue<library*, vector<library*>, myComp> pq;
        for (int i = 0; i < num_libraries; ++i) {
        if (libraries2[i]) pq.push(&libraries[i]);
    }
        int idl = pq.top()->myid;
        libraries2[idl] = false;
        cout << pq.top()->myid << " " << (pq.top()->id).size() << endl;
        for (int i = 0; i < (pq.top()->id).size(); ++i) {
            cout << (pq.top()->id)[i] << " ";
            if (books2[(pq.top()->id)[i] ]) {
                books2[(pq.top()->id)[i] ] = false;
                for (int j : bl[(pq.top()->id)[i] ]) {
                    if (j != idl) {
                        libraries[j].score -= books[(pq.top()->id)[i] ];
                        libraries[j].nb -= 1;
                        if (libraries[j].nb > 0) {
                        libraries[j].avg = double(libraries[j].score)/double(libraries[j].signup_time);
                        } else libraries[j].avg = -1;
                    }
                }
            }
        }
        cout << endl;
        day += pq.top()->signup_time;
        ++ns;
        //pq.pop();
        
    }
    cout << ns << endl;
}

void write_to_file() 
{
    ofstream outFile(OUTPUT_FILE);
    //outFile << ...
    cout << "Output file overwritten with solution" << endl;
}

int main() {
    read_from_file();
    greedy();
}

