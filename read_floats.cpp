/*Assumption: our file contains 
float data plus one row of 
column names at the top.*/

#include <string> 
#include <fstream> 
#include <vector> 
#include <utility> //for std::pair
#include <stdexcept> //for std::runtime_error
#include <sstream> //fir std::stringstream
#include <iostream> 

std::vector<std::pair<std::string, std::vector<float>>> read_csv(std::string filename)
{
    //Store result
    std::vector<std::pair<std::string, std::vector<float>>> result; 

    //input file stream
    std::ifstream myFile(filename); 

    if(!myFile.is_open()) throw std::runtime_error("Could not open the requested file");

    std::string line, colname; 
    float value; 


    //Check whether state of stream is good
    if(myFile.good())
    {

        std::getline(myFile, line);

        std::stringstream ss(line);

        while(std::getline(ss, colname, ',')) 
        {
            result.push_back({colname,std::vector<float> {}}); 
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
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<float>>> dataset )
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

void create_floats_dataset(){
    /*Writing floats*/
    std::vector<float> vector1(100,1.1);
    std::vector<float> vector2(100,2.1);
    std::vector<float> vector3(100,3.1);

    std::vector<std::pair<std::string, std::vector<float>>> values = {{"One", vector1}, {"Two", vector2}, {"Three", vector3}};

    write_csv("floats2.csv",values); 
}

void print_dataset(std::vector<std::pair<std::string, std::vector<float>>> dataset){
    
    int col_nums = dataset.size();
    int row_nums = dataset.at(0).second.size();

    for(int i = 0; i < col_nums; ++i){
        std::string column_name = dataset.at(i).first;
        std::vector<float> elements = dataset.at(i).second;
        
        std::cout << "Column: " << column_name << "\t\t";
        
        for(int j = 0; j < row_nums - 1; ++j){
            std::cout << elements.at(j) << " | ";
        }
        std::cout << elements.at(row_nums -1) << ".";

        std::cout << "\n";
    }
    
}

int main() 
{
    std::vector<std::pair<std::string, std::vector<float>>> dataset; 
    
    dataset = read_csv("iris.csv");

    print_dataset(dataset);

    return 0;

}



