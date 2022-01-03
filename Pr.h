#ifndef PR_H_INCLUDED
#define PR_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <math.h>

using namespace std;

class Pr{

    private:
        double** elements;
        double** query;
        double* sad;
        int rows, cols, querycols, queryrows;
        int regions = -1;
        void initialize_sad();
        double sum(int k);

    public:
        Pr();
        void calculate_sad();
        int find_min_sad();

};


#endif // PR_H_INCLUDED
