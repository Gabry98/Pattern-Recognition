#include "GetElements.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

double** GetElements::get_elements_from_file(int& rows, int& cols, string file){

    std::string text;
    std::ifstream myfile(file);

    if(myfile.is_open()){

        while(myfile.peek() != EOF)
        {
           std::string temp;
           temp = myfile.get();
           text = text.append(temp);
        }
        myfile.close();
    }
    else cout << "Unable to open file" << endl;

    std::regex re("[,]");
    text = regex_replace(text,re," ");

    std::regex re2("[a-zA-Z] ");
    text = regex_replace(text,re2,"");

    std::regex re3(" [a-zA-Z]");
    text = regex_replace(text,re3,"");

    rows = std::count(text.begin(),text.end(),'\n');
    cols = (std::count(text.begin(),text.end(),' ')/rows)+1;
    double** elements = new double*[rows];

    int i=0,r = 0, c = 0;
    bool wait = false;

    for(size_t j=0; j<text.length(); j++)
    {
        if(text[j]==' ' || text[j]=='\n')
        {
            if(!wait)
            {
                elements[r] = new double[cols];
                wait = true;
            }
            elements[r][c] = stod(text.substr(i,j-i));
            c++;
            i = j+1;
        }

        if(c==cols && r<rows-1){
            c=0;
            r++;
            wait = false;
        }
    }

    return elements;
}

double** GetElements::get_random_query(int& queryrows, int& querycols, int rows, int cols, int regions)
{

    cout << "Insert the number of the regions you want to use for recognition: ";
    cin >> regions;

    if(regions<2 || regions>cols) throw std::runtime_error("Error: the value of the Regions is incorrect!");

    cout << endl << endl;

    queryrows = rows;
    double** query = new double*[rows];
    querycols = cols-regions+1;

    for(int i=0; i<queryrows; i++)
    {
        query[i] = new double[querycols];

        for(int j=0; j<querycols; j++)
        {
            query[i][j] = rand() % 13 + 1;
        }
    }

    return query;
}
