#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
	std::fstream output;
	output.open("largedata.dat", ios::out | ios::binary);

	for (int i = 0; i < 2000000; i++)
	{
		int value = rand();
		output.write(reinterpret_cast<char*>(&value), sizeof(value));
	}

	output.close();
	std::cout << "file created" << std::endl;

	std::fstream input;
	input.open("largedata.dat", ios::in | ios::binary);
	int value;

	std::cout << "the first 10 numbers in the file are " << std::endl;
	for (int i = 0; i < 10; i++)
	{
		input.read(reinterpret_cast<char*>(&value), sizeof(value));
		std::cout << value << " ";
	}

	input.close();

	return 0;
}

int initializeSegments(int segmentSize, string sourceFile, string f1)
{
	int* list new int[segmentSize];

	std::fstream input;
	input.open(sourceFile.c_str(), ios::in | ios::binary);
	std::fstream output;
	output.open(f1.c_str(), ios::out | ios::binary);

	int numberOfSegments = 0;
	while (!input.eof())
	{
		int i = 0;
		for ( ; !input.eof() && i< segmentSize; i++)
		{
			input.read(reinterpret_cast<char*>(&list[i], sizeof(list[i])));
		}

		if (input.eof()) i--;
		if (i <= 0) break;
		else numberOfSegments++;

		quickSort(list, i);
		for (int j = 0; j < i; j++)
		{
			output.write(reinterpret_cast<char*>(&list[j], sizeof(list[j])));
		}
	}
	
	input.close();
	output.close();
	delete [] list;
	return numberOfSegments;
}

template <typename T>
void Bubble(T *arr, int size) {
    int temp;
    int counter = 1;
     
    while(counter){
        counter = 0;
        for(int i = 0; i < size-1; i++) {
            if(arr[i] > arr[i+1]) {
                counter = 1;
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp; 
            }
        }
    }
}

template <typename T>
void bubble(T *arr,int count)
{
	T t;

	for(int i = 1; i < count; i++) {
		for(int j = count-1; j >= i; j--) {
			if(arr[j-1] > arr[j]) {
				t = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = t;
			}
		}
	}
}