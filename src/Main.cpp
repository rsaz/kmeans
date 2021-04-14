#include <iostream>
#include "Cluster.h"

using std::string;
using std::cout;
using std::endl;

void RunKMeans(string fileName, int k)
{
    Cluster* kmeans = new Cluster{fileName};
    kmeans->RunCluster(k);

    delete kmeans;
}


int main(int argc, char **argv)
{
    //Need 2 arguments (except filename) to run, else exit
    if(argc != 3){
        cout<<"Error: command-line argument count mismatch.";
        return 1;
    }

    //Fetching data from flags
    unsigned int K = atoi(argv[2]);
    string file = argv[1];

    RunKMeans(file, K);
    
    
    std::cin.get();
}
