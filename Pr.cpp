#include "Pr.h"
#include "GetElements.h"

Pr::Pr(){
    GetElements g;

    cout << "Loading Dataset..." << endl;
    elements = g.get_elements_from_file(rows,cols,"example_dataset.data");
    cout << "Dataset Loaded." << endl << endl;


    cout << "Loading Query..." << endl;
    query = g.get_elements_from_file(queryrows,querycols,"example_query.data");
    cout << "Query Loaded." << endl << endl;

    if(querycols>=cols || queryrows!=rows) throw std::runtime_error("Error: Query parameters are incorrect!");

    if(regions == -1) regions = cols-querycols+1;
    if(regions<2 || regions>cols) throw std::runtime_error("Error: the value of the Regions is incorrect!");
}

void Pr::calculate_sad()
{
    initialize_sad();

    for(int k=0; k<regions; k++)
    {
        sad[k] = sum(k);
    }
}

void Pr::initialize_sad(){

    sad = new double[regions];

    for(int i = 0; i<regions; i++)
    {
        sad[i] = 0;
    }
}

double Pr::sum(int k)
{
    double sum = 0;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<querycols ; j++)
        {
            sum += abs(elements[i][j+k]-query[i][j]);
        }
    }

    return sum;
}

int Pr::find_min_sad()
{
    double min_value = sad[0];
    int index = 0;

    for(int i=1; i<regions; i++)
    {
        if(sad[i]<min_value)
        {
            min_value = sad[i];
            index = i;
        }
    }

    return index;
}
