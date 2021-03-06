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
#include <algorithm>

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

void print_dataset(std::vector<std::pair<std::string, std::vector<float>>> dataset, int num_instances = -1){
    
    int col_nums = dataset.size();
    int row_nums;
    if (num_instances == -1){
        row_nums = dataset.at(0).second.size();
    } else {
        row_nums = num_instances;
    }
    for(int i = 0; i < col_nums; ++i){
        std::string column_name = dataset.at(i).first;
        if (i != col_nums-1) {
            std::cout << "x_" << i << ": " << column_name << "\n" ;
        } else {
            std::cout << "y" << ": " << column_name << "\n" ;
        }
    }

    for(int i = 0; i < col_nums; ++i){
        if (i != col_nums-1) {
            std::cout << "x_" << i << "\t | \t" ;
        } else {
            std::cout << "y" << "\t |" ;
        }
       
    }
    std::cout << "\n";
    for(int i =  0; i < col_nums; ++i){
        if (i==0) {
            std::cout << "-----| ";
        } else {
            std::cout << "----- | ";
        }
    } 
    std::cout << "\n";

    
    for(int j = 0; j< row_nums; ++j){
        for(int i = 0; i < col_nums; ++i){
            float element = dataset.at(i).second.at(j);
            std::cout << element << "\t | \t" ;
        }  
        std::cout << "\n";
    }

}

/*Returns a copy of the sorted vector*/
std::vector<float> sort_single_vector(std::vector<float> vector){
    std::vector<float> sorted(vector);
    std::sort(sorted.begin(), sorted.end());
    return sorted; 
}

/*Sorts vector 2 following the sorting of vector1*/
std::pair<std::vector<float>, std::vector<float>> sort_unison(std::vector<float> vector1, std::vector<float> vector2)
{


    std::pair<std::vector<float>, std::vector<float>> result; 

    int size = vector1.size();

    //Initialize index vector
    std::vector<int> index(size, 0);
    std::vector<float> v1_sorted(size, 0);
    std::vector<float> v2_sorted(size, 0);

    //Fill up index vector
    for (int i = 0 ; i != size ; i++) {
        index[i] = i;
    }

    //Sort index based on the corresponding values of vector1
    sort(index.begin(), index.end(),
    [&](const int& a, const int& b) {
        return (vector1[a] < vector1[b]);
    });

    //sort the two vectors based on the commond sorting index
    for (int i = 0 ; i != size ; i++) {
    v1_sorted[i] = vector1[index[i]];
    v2_sorted[i] = vector2[index[i]];
    }
    
    //pass them as a pair
    result = {v1_sorted, v2_sorted};

    return result; 
    
}

void print_vector(std::vector<float> vector){
    
    int size = vector.size();
    
    for (int i = 0 ; i < size-1 ; i++){
        std::cout << vector.at(i) << ',';
        //if (i > 1 && (i+1)%10 == 0) std::cout << "\n";
    }
    std::cout << vector.at(size-1) << '.' << "\n";
}

std::vector<float> get_column(std::vector<std::pair<std::string, std::vector<float>>> dataset, std::string column_name){
    int row_nums = dataset.at(0).second.size();
    int col_nums = dataset.size();
    
    std::vector<float> result(row_nums,0);
    std::string column;

    for (int i = 0; i < col_nums; ++i){
        column = dataset.at(i).first;
        if (column == column_name) {
            result = dataset.at(i).second;
        }
    }

    
    return result;
}





int main() 
{

    
    std::vector<std::pair<std::string, std::vector<float>>> dataset; 
    
    dataset = read_csv("iris.csv");

    //print_dataset(dataset,10); 

    std::vector<float> y = get_column(dataset, "class");
    std::vector<float> x_0 = get_column(dataset, "sepal_length");
    print_vector(x_0);
    print_vector(y);

    std::pair<std::vector<float>, std::vector<float>> sorted_pair =  sort_unison(x_0,y);
    //print_vector(sorted_pair.first);
    //print_vector(sorted_pair.second);

    std::vector<std::pair<std::string, std::vector<float>>> representation = {{"first",sorted_pair.first},{"second",sorted_pair.second}};
    
    print_dataset(representation);
    

    /*
    std::pair<std::vector<float>, std::vector<float>> sorted_couple; 

    sorted_couple = sort_unison(arr,arr2);

    std::vector<float> sorted_x = sorted_couple.first;
    std::vector<float> sorted_y = sorted_couple.second;

    print_vector(sorted_x);
    print_vector(sorted_y);
*/
    return 0;

}



