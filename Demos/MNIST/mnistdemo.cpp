/*Author: Austin Graham*/
#include<iostream>
#include<fstream>
#include"../../Models/Neural Network/NeuralNetwork.h"
using namespace std;

int TOTAL_ELEMENTS;
int ROWS;
int COLUMNS;

int reverseInt(int num)
{
	int left_most = (0x000000FF & num) << 24;
	int middle_left = (0x0000FF00 & num) << 8;
	int middle_right = (0x00FF0000 & num) >> 8;
	int right_most = (0xFF000000 & num) >> 24;
	return left_most + middle_left + middle_right + right_most; 
}

int* readLabelFile(const char* fileName)
{
	ifstream file(fileName, ios::in | ios::binary);
	int* labels = NULL;
	int magic_number = 0;
	int size = 0;
	if(file.is_open())
	{
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = reverseInt(magic_number);
		cout<<"Magic Number: "<<magic_number<<endl;
		file.read((char*)&size, sizeof(size));
		size = reverseInt(size);
		cout<<"Size of file in elements: "<<size<<endl;
		cout<<"Getting elements..."<<endl;
		labels = new int[size];
		for(int i = 0; i < size; i++)
		{
			file.read((char*)&labels[i], 1);
		}
	}
	file.close();
	return labels;
}

int** readImageFiles(const char* fileName)
{
	ifstream file(fileName, ios::in | ios::binary);
	int** images = NULL;
	int magic_number = 0;
	int size = 0;
	if(file.is_open())
	{
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = reverseInt(magic_number);
		cout<<"Magic Number: "<<magic_number<<endl;
		file.read((char*)&size, sizeof(size));
		size = reverseInt(size);
		TOTAL_ELEMENTS = size;
		cout<<"Size of file in elements: "<<size<<endl;
		images = new int*[size];
		int rows = 0;
		int columns = 0;
		file.read((char*)&rows, sizeof(rows));
		file.read((char*)&columns, sizeof(columns));
		rows = reverseInt(rows);
		columns = reverseInt(columns);
		ROWS = rows;
		COLUMNS = columns;
		cout<<"Rows in each image: "<<rows<<endl;
		cout<<"Columns in each image: "<<columns<<endl;
		cout<<"Getting elements..."<<endl;
		for(int i = 0; i < size; i++)
		{
			images[i] = new int[rows*columns];
			for(int j = 0; j < rows*columns; j++)
			{
				file.read((char*)&images[i][j], 1);
			}
		}
	}
	file.close();
	return images;
}

double** transformLabelstoExpectedOutput(int* labels)
{
	double** newLabels = new double*[TOTAL_ELEMENTS];
	for(int i = 0; i < TOTAL_ELEMENTS; i++)
	{
		newLabels[i] = new double[4];
		int iter = labels[i];
		for(int j = 0; j < 4; j++)
		{
			newLabels[i][j] = (iter % 2 == 0) ? 0 : 1;
			iter /= 2;
		}
	}
	return newLabels;
}

double** normalizeImages(int** images)
{
	double** newImages = new double*[TOTAL_ELEMENTS];
	for(int i = 0; i < TOTAL_ELEMENTS; i++)
	{
		newImages[i] = new double[ROWS*COLUMNS];
		for(int j = 0; j < ROWS*COLUMNS; j++)
		{
			newImages[i][j] = (double)images[i][j] / 255.0;
		}
	}
	return newImages;
}

int main()
{
	cout<<"Reading label file..."<<endl;
	int* labels = readLabelFile("Data/train-labels.idx1-ubyte");
	cout<<"Retrieved labels."<<endl;
	cout<<"Reading image files..."<<endl;
	int** images = readImageFiles("Data/train-images.idx3-ubyte");
	cout<<"Read images."<<endl;
	cout<<"Transforming labels to expected output..."<<endl;
	double** asBinary = transformLabelstoExpectedOutput(labels);
	cout<<"Normalizing images..."<<endl;
	double** normalizedImages = normalizeImages(images);
	
	cout<<"Building Network..."<<endl;
	int layers [] = {ROWS*COLUMNS, ROWS*COLUMNS+10, 4};
	NeuralNetwork* nn = new NeuralNetwork(layers, 3, 199);
	cout<<"Network ID: "<<nn->getID()<<endl;
	
	cout<<"Training..."<<endl;
	for(int i = 0; i < TOTAL_ELEMENTS; i++)
	{
		cout<<i<<endl;
		double* output = nn->feedForward(normalizedImages[i]);
		nn->backPropogate(asBinary[i], normalizedImages[i]);
	}
	cout<<"Trained"<<endl;


	cout<<"Cleaning up..."<<endl;
	for(int i = 0; i < TOTAL_ELEMENTS; i++)
	{
		delete [] images[i];
		delete [] asBinary[i];
		delete [] normalizedImages[i];
	}
	delete [] labels;
	delete [] images;
	delete [] asBinary;
	delete [] normalizedImages;
	cout<<"Done."<<endl;
	return 0;
}
