
#include <fstream> 

int main() {
	// Create output filestream object
	std::ofstream myFile("foo.csv");

	myFile << "Foo\n";
	myFile << "1\n";
	myFile << "2\n";
	myFile << "3\n";

	myFile.close();

	return 0;
}
