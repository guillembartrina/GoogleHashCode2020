
#include "inout.hpp"

#include <vector>
#include <algorithm>

using namespace std;

struct lib_score
{
    inline bool operator() (const int l1, const int l2)
    {
        if(books[l1] == books[l2]) return l1 < l2;
        return (books[l1] > books[l2]);
    }
};

float evaluate(const library& l)
{
    float avg = l.average;
    float ld = l.books_per_day;
    float ts = l.signup_time;
    float nl = l.num_books;
    float fo1 = nl/ts;
    float fo2 = avg*ld;

    return fo1*fo2*0.75;
}

int findmax(const vector<bool>& visited)
{
    float curmax = 0.f;
    int posmax = 0;
    for(int i = 1; i < libraries.size(); i++)
    {
        if(not visited[i])
        {
            float cur = evaluate(libraries[i]);
            if(cur > curmax)
            {
                posmax = i;
                curmax = cur;
            }
        }
    }
    return posmax;
}

void calculate()
{
    sol.num_lib = 0;

    int currTime = 0;

    read_from_file();

    vector<bool> scanned(books.size(), false);
    vector<bool> visited(libraries.size(), false);

    while(currTime <= days-1) //??
    {
        //std::cerr << "Currtime " << currTime << " over " << days << std::endl;
        int max = findmax(visited);
        if(max == 0 and visited[0]) break;
        library& cl = libraries[max];
        visited[max] = true;

        int avaldays = days - (currTime + cl.signup_time);
        if(avaldays <= 0) continue;
        int avalbooks = avaldays*cl.books_per_day;
        if(avalbooks < 0) avalbooks = INT_MAX;

        sol.num_lib++;

        sol_library sl;
        sl.id_lib = cl.library_id;

        if(avalbooks < cl.num_books)
        {
            sl.num_books = avalbooks;

            vector<int> temporal(cl.id.size());
            auto it2 = cl.id.begin();
            int i = 0;
            while(it2 != cl.id.end())
            {
                temporal[i] = *it2;
                i++;
                it2++;
            }


            sort(temporal.begin(), temporal.end(), lib_score());


            int temp = avalbooks;
            auto it = temporal.begin();
            while(it != temporal.end() and temp > 0)
            {
                if(not scanned[*it])
                {
                    sl.id.push_back(*it);
                    temp--;

                    scanned[*it] = true;

                    for(int i = 0; i < libraries.size(); i++)
                    {
                        if(not visited[i])
                        {
                            if(libraries[i].id.find(*it) != libraries[i].id.end())
                            {
                                libraries[i].average -= books[*it]/libraries[i].num_books;
                                libraries[i].num_books--;
                            }
                        }
                    }
                }
                it++;
            }


        }
        else //pot scannejar totts els llibre
        {
            sl.num_books = cl.num_books;
            
            auto it = cl.id.begin();
            while(it != cl.id.end())
            {
                if(not scanned[*it])
                {
                    sl.id.push_back(*it);
                    scanned[*it] = true;

                    for(int i = 0; i < libraries.size(); i++)
                    {
                        if(not visited[i])
                        {
                            if(libraries[i].id.find(*it) != libraries[i].id.end())
                            {
                                libraries[i].average -= books[*it]/libraries[i].num_books;

                                libraries[i].num_books--;
                            }
                        }
                    }
                }
                it++;
            }
        }

        currTime += cl.signup_time;

        sol.libraries.push_back(sl);
    }
	write_to_file();
}

int main()
{
    calculate();
    return 0;
}