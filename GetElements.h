#ifndef GETELEMENTS_H_INCLUDED
#define GETELEMENTS_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class GetElements{

    public:
        double** get_elements_from_file(int& rows, int& cols, string file);
        double** get_random_query(int& queryrows, int& querycols, int rows, int cols, int regions);


};

#endif // GETELEMENTS_H_INCLUDED
