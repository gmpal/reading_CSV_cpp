#include <string>
#include <fstream>
#include <vector>
#include <utility> 

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset )
{
    
    std::ofstream myFile(filename);

    for (int j = 0; j < dataset.size(); ++j) 
    {
        myFile << dataset.at(j).first; 
        if( j != dataset.size() - 1) myFile << ","; 
    }
    myFile << "\n"


}