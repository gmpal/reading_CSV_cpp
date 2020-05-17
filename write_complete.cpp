#include <string>
#include <fstream>
#include <vector>
#include <utility> 
/*
(string,vector), (string,vector), (string,vector), ...
*/
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset )
{
    int col_nums = dataset.size();
    int row_nums = dataset.at(0).second.size();
    
    //FileStream
    std::ofstream myFile(filename);

    //Managing column names: j moves column-wise 
    for (int j = 0; j < col_nums; ++j) 
    {
        myFile << dataset.at(j).first; 
        //preventing comma at the end of the line
        if( j != col_nums - 1) myFile << ","; 
    }
    myFile << "\n"; 


    //Managing elements: moving row-wise 
    for(int i = 0; i < row_nums; ++i )
    {
        //Adding numbers row by row (filling the file line-wise)
        for (int j = 0; j < col_nums; ++j) 
        {
            myFile << dataset.at(j).second.at(i);
            if( j != col_nums - 1) myFile << ","; 
        }

        myFile << "\n";
    }

    myFile.close(); 

}

int main() {
    std::vector<int> vector1(100,10);
    std::vector<int> vector2(100,20);
    std::vector<int> vector3(100,30);

    std::vector<std::pair<std::string, std::vector<int>>> values = {{"One", vector1}, {"Two", vector2}, {"Three", vector3}};

    write_csv("multiple.columns.csv",values); 

    return 0;  
}