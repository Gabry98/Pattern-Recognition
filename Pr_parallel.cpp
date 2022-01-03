#include "Pr_parallel.h"
#include "GetElements.h"
#include <omp.h>

Pr_parallel::Pr_parallel(){
    GetElements g;

    cout << "Loading Dataset..." << endl;
    elements = g.get_elements_from_file(rows,cols,"blogData_train.csv");
    cout << "Dataset Loaded." << endl << endl;


    cout << "Loading Query..." << endl;
    query = g.get_random_query(queryrows,querycols,rows,cols,regions);
    cout << "Query Loaded." << endl << endl;

    if(querycols>=cols || queryrows!=rows) throw std::runtime_error("Error: Query parameters are incorrect!");

    if(regions == -1) regions = cols-querycols+1;
    if(regions<2 || regions>cols) throw std::runtime_error("Error: the value of the Regions is incorrect!");
}

void Pr_parallel::calculate_sad()
{
    initialize_sad();

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for(int k=0; k<regions; k++)
    {
        sad[k] = sum(k);
    }
}

void Pr_parallel::initialize_sad(){

    sad = new double[regions];

    #pragma omp parallel for num_threads(omp_get_max_threads())
    for(int i = 0; i<regions; i++)
    {
        sad[i] = 0;
    }
}

double Pr_parallel::sum(int k)
{
    double sum = 0;

    for(int i=0; i<rows; i++)
    {
        #pragma omp simd reduction(+:sum)
        for(int j=0; j<querycols ; j++)
        {
            sum += abs(elements[i][j+k]-query[i][j]);
        }
    }

    return sum;
}

int Pr_parallel::find_min_sad()
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
