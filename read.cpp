/*Assumption: our file contains 
integer data plus one row of 
column names at the top.*/

#include <string> 
#include <fstream> 
#include <vector> 
#include <utility> //for std::pair
#include <stdexcept> //for std::runtime_error
#include <sstream> //fir std::stringstream

std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename)
{
    //Store result
    std::vector<std::pair<std::string, std::vector<int>>> result; 

    //input file stream
    std::ifstream myFile(filename); 

    if(!myFile.is_open()) throw std::runtime_error("Could not open the requested file");

    std::string line, colname; 
    int value; 


    //Check whether state of stream is good
    if(myFile.good())
    {

        std::getline(myFile, line);

        std::stringstream ss(line);

        while(std::getline(ss, colname, ',')) 
        {
            result.push_back({colname,std::vector<int> {}}); 
        }
    }

    while(std::getline(myFile, line))
    {
        std::stringstream ss(line);

        int colIdx = 0; 

        while (ss >> value) 
        {
            result.at(colIdx).second.push_back(value);
            
            //Peek next character: if comma, ignore.
            if(ss.peek() == ',') ss.ignore();
            
            colIdx++;

        }
    }

    myFile.close();

    return result;

}

/*Previous write function*/
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

int main()
{
    std::vector<std::pair<std::string, std::vector<int>>> file1;
    std::vector<std::pair<std::string, std::vector<int>>> file2; 

    file1 = read_csv("single_column.csv");
    file2 = read_csv("multiple_columns.csv"); 

    write_csv("single_column_check.csv", file1);
    write_csv("multiple_column_check.csv", file2);
}