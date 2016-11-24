/*Author: Austin Graham*/
/*Class representing the matrix data structure*/
template <class DT>
class Matrix
{
public:
	//Constructor taking how large the matrix should be with a base value
	Matrix(int rows, int columns, DT base);
	//Copy constructor
	Matrix(Matrix* m);
	//Destructor
	~Matrix();
	//Get the number of rows in this matrix
	int getRows();
	//Get the number of columns in this matrix
	int getColumns();
	//Set a particular value in the matrix
	void set(int row, int column, DT newData);
	//Get a particular value in the matrix
	DT& get(int row, int column);
	//Exted the matrix by a number of rows and columns
	void extend(int addRows, int addColumns);
	//Get an entire row
	DT* getRow(int row);
	//Get an entire column
	DT* getColumn(int column);
private:
	//Initialize matrix
	void init(int rows, int columns);
	//Hold the data
	DT** data;
	//The number of rows
	int rows;
	//The number of columns
	int columns;
	//Base value of the matrix
	DT base;
};

/*Construct a matrix with a certain number of rows and columns, with a base value*/
template <class DT>
Matrix<DT>::Matrix(int rows, int columns, DT base)
{
	//Initialize the matrix
	this->init(rows, columns);
	this->rows = rows;
	this->columns = columns;

	//Set the base value
	this->base = base;

	//Set all values to the base
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			this->data[i][j] = base;
		}
	}
}

/*Make a deep copy of an existing matrix*/
template <class DT>
Matrix<DT>::Matrix(Matrix* m)
{
	//Initialize the new matrix
	this->init(m->getRows(), m->getColumns());
	this->rows = m->getRows();
	this->columns = m->getColumns();
	//Set the base value
	this->base = m->base;

	//Copy all data
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			this->data[i][j] = m->get(i,j);
		}
	}
}

/*Deconstruct the matrix*/
template <class DT>
Matrix<DT>::~Matrix()
{
	//Delete all data in the matrix
	for(int i = 0; i < this->rows; i++)
	{
		delete [] this->data[i];
	}
	delete [] data;
}

/*Get the number of rows in the matrix*/
template <class DT>
int Matrix<DT>::getRows()
{
	return this->rows;
}

/*Get the number of columns in the matrix*/
template <class DT>
int Matrix<DT>::getColumns()
{
	return this->columns;
}

/*Set an element to a value in the matrix*/
template <class DT>
void Matrix<DT>::set(int row, int column, DT newData)
{
	this->data[row][column] = newData;
}

/*Get a particular element in the matrix*/
template <class DT>
DT& Matrix<DT>::get(int row, int column)
{
	return this->data[row][column];
}

/*Extend the matrix size*/
template <class DT>
void Matrix<DT>::extend(int addRows, int addColumns)
{
	//Hold the current data
	DT** tempHolder = this->data;

	//Reinitialize the data
	this->init(this->rows + addRows, this->columns + addColumns);

	//Reset the number of rwos and columns
	this->rows += addRows;
	this->columns += addColumns;

	//Iterate through new holder, if place already exists
	//set to past value, otherwise set to base
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			if(i < this->rows - addRows && j < this->columns - addColumns)
			{
				this->data[i][j] = tempHolder[i][j];
			}
			else
			{
				this->data[i][j] = base;
			}
		}
	}

	//Delete the temporary spot
	for(int i = 0; i < this->rows - addRows; i++)
	{
		delete [] tempHolder[i];
	}
	delete [] tempHolder;
}

/*Get an entire row of the matrix*/
template <class DT>
DT* Matrix<DT>::getRow(int row)
{
	return this->data[row];
}

/*Get an entire column of the matrix*/
template <class DT>
DT* Matrix<DT>::getColumn(int column)
{
	DT* col = new DT[this->rows];
	for(int i = 0; i < this->rows; i++)
	{
		col[i] = this->data[i][column];
	}
	return col;
}

/*Initialize the data holder*/
template <class DT>
void Matrix<DT>::init(int rows, int columns)
{
	this->data = new DT*[rows];
	for(int i = 0; i < rows; i++)
	{
		this->data[i] = new DT[columns];
	}
}
