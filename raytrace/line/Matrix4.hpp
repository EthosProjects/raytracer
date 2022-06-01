#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <exception>


class Matrix4 {
public:
    double values[4][4] { 0.0 };
    void setToIdentity();
    bool toInverse();

    double getDeterminant();
    bool operator== (const Matrix4& rhs);
	bool Compare (const Matrix4& t_matrix, double t_tolerance);

    // Overload +, - and * operators (friends).
    Matrix4 operator+= (const Matrix4 &rhs);
    Matrix4 operator+= (const double &rhs);
    friend Matrix4 operator+ (const Matrix4 &lhs, const Matrix4 &rhs);
    friend Matrix4 operator+ (const double &lhs, const Matrix4 &rhs);
    friend Matrix4 operator+ (const Matrix4 &lhs, const double &rhs);
    
    Matrix4 operator-= (const Matrix4 &rhs);
    Matrix4 operator-= (const double &rhs);
    friend Matrix4 operator- (const Matrix4& lhs, const Matrix4& rhs);
    friend Matrix4 operator- (const double& lhs, const Matrix4& rhs);
    friend Matrix4 operator- (const Matrix4& lhs, const double& rhs);
    
    Matrix4 operator*= (const Matrix4 &rhs);
    Matrix4 operator*= (const double &rhs);
};
Matrix4 operator* (const Matrix4 &lhs, const Matrix4 &rhs);
Matrix4 operator* (const Matrix4 &lhs, const double &rhs);
Matrix4 operator* (const double &lhs, const Matrix4 &rhs);
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix4);
#if FALSE
class qbMatrix2 {
	public:
		// Define the various constructors.
    qbMatrix2();
    qbMatrix2(int nRows, int nCols);
    qbMatrix2(int nRows, int nCols, const double *inputData);
    qbMatrix2(const qbMatrix2 &inputMatrix);
    qbMatrix2(int nRows, int nCols, const std::vector<double> &inputData);

    // And the destructor.
    ~qbMatrix2();

    // Configuration methods.
    bool Resize(int numRows, int numCols);
    void SetToIdentity();

    // Element access methods.
    double GetElement(int row, int col) const;
    bool SetElement(int row, int col, double elementValue);
    int GetNumRows() const;
    int GetNumCols() const;
    
    // Manipulation methods.
    // Compute matrix inverse.
    bool Inverse();
    // Convert to row echelon form.
    qbMatrix2 RowEchelon();
    // Return the transpose.
    qbMatrix2 Transpose() const;
    
    // Compute determinant.
    double Determinant();

		// Overload == operator.
		bool operator== (const qbMatrix2& rhs);
		bool Compare (const qbMatrix2& matrix1, double tolerance);
		
		// Overload the assignment operator.
		qbMatrix2 operator= (const qbMatrix2 &rhs);

    // Overload +, - and * operators (friends).
    friend qbMatrix2 operator+ (const qbMatrix2& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator+ (const double& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator+ (const qbMatrix2& lhs, const double& rhs);
    
    friend qbMatrix2 operator- (const qbMatrix2& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator- (const double& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator- (const qbMatrix2& lhs, const double& rhs);
    
    friend qbMatrix2 operator* (const qbMatrix2& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator* (const double& lhs, const qbMatrix2& rhs);
    friend qbMatrix2 operator* (const qbMatrix2& lhs, const double& rhs);
    
    // qbMatrix2 * qbVector.
    friend qbVector operator* (const qbMatrix2& lhs, const qbVector& rhs);

		bool Separate(qbMatrix2 &matrix1, qbMatrix2 &matrix2, int colNum);
		bool Join(const qbMatrix2& matrix2);
		qbMatrix2 FindSubMatrix(int rowNum, int colNum);
		
		// Function to return the rank of the matrix.
		int Rank();		
		
		bool IsSquare();
		bool IsRowEchelon();	
		bool IsNonZero();	
		bool IsSymmetric();
		void PrintMatrix();
		void PrintMatrix(int precision);

	private:
		int Sub2Ind(int row, int col) const;
		bool CloseEnough(double f1, double f2);
		void SwapRow(int i, int j);
		void MultAdd(int i, int j, double multFactor);
		void MultRow(int i, double multFactor);
		int FindRowWithMaxElement(int colNumber, int startingRow);	

	private:
		double *m_matrixData;
    int m_nRows, m_nCols, m_nElements;
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
qbMatrix2::qbMatrix2()
{
	m_nRows = 1;
  m_nCols = 1;
  m_nElements = 1;
  m_matrixData = nullptr;
}

// Construct empty matrix (all elements 0)
qbMatrix2::qbMatrix2(int nRows, int nCols)
{
  m_nRows = nRows;
  m_nCols = nCols;
  m_nElements = m_nRows * m_nCols;
  m_matrixData = new double[m_nElements];
  for (int i=0; i<m_nElements; i++)
	  m_matrixData[i] = 0.0;
}

// Construct from const linear array.
qbMatrix2::qbMatrix2(int nRows, int nCols, const double *inputData)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_nElements = m_nRows * m_nCols;
	m_matrixData = new double[m_nElements];
	for (int i=0; i<m_nElements; i++)
	  m_matrixData[i] = inputData[i];
}

// The copy constructor.
qbMatrix2::qbMatrix2(const qbMatrix2 &inputMatrix)
{
	m_nRows = inputMatrix.m_nRows;
	m_nCols = inputMatrix.m_nCols;
	m_nElements = inputMatrix.m_nElements;
	
	m_matrixData = new double[m_nElements];
	for (int i=0; i<m_nElements; i++)
		m_matrixData[i] = inputMatrix.m_matrixData[i];
}

// Construct from std::vector.
qbMatrix2::qbMatrix2(int nRows, int nCols, const std::vector<double> &inputData)
{
	m_nRows = nRows;
	m_nCols = nCols;
	m_nElements = m_nRows * m_nCols;
	m_matrixData = new double[m_nElements];
	for (int i=0; i<m_nElements; ++i)
		m_matrixData[i] = inputData.at(i);
}

qbMatrix2::~qbMatrix2()
{
	// Destructor.
	if (m_matrixData)
		delete[] m_matrixData;
	
	m_matrixData = nullptr;
}

/* **************************************************************************************************
CONFIGURATION FUNCTIONS
/* *************************************************************************************************/
bool qbMatrix2::Resize(int numRows, int numCols)
{
	m_nRows = numRows;
	m_nCols = numCols;
	m_nElements = (m_nRows * m_nCols);
	delete[] m_matrixData;
	m_matrixData = new double[m_nElements];
	if (m_matrixData != nullptr)
	{
		for (int i=0; i<m_nElements; i++)
			m_matrixData[i] = 0.0;

		return true;
	}
	else
	{
		return false;
	}
}

// Function to convert the existing matrix into an identity matrix.
void qbMatrix2::SetToIdentity()
{
	if (!IsSquare())
		throw std::invalid_argument("Cannot form an identity matrix that is not square.");
		
	for (int row=0; row<m_nRows; ++row)
	{
		for (int col=0; col<m_nCols; ++col)
		{
			if (col == row)
				m_matrixData[Sub2Ind(row,col)] = 1.0;
			else
				m_matrixData[Sub2Ind(row,col)] = 0.0;
		}
	}
}

/* **************************************************************************************************
ELEMENT FUNCTIONS
/* *************************************************************************************************/
double qbMatrix2::GetElement(int row, int col) const
{
	int linearIndex = Sub2Ind(row, col);
	if (linearIndex >= 0)
		return m_matrixData[linearIndex];
	else
		return 0.0;

}

bool qbMatrix2::SetElement(int row, int col, double elementValue)
{
	int linearIndex = Sub2Ind(row, col);
	if (linearIndex >= 0)
	{
		m_matrixData[linearIndex] = elementValue;
		return true;
	} 
	else 
	{
		return false;
	}
}

int qbMatrix2::GetNumRows() const
{
	return m_nRows;
}

int qbMatrix2::GetNumCols() const
{
	return m_nCols;
}

bool qbMatrix2::Compare(const qbMatrix2& matrix1, double tolerance)
{
	// First, check that the matrices have the same dimensions.
	int numRows1 = matrix1.m_nRows;
	int numCols1 = matrix1.m_nCols;
	if ((numRows1 != m_nRows) || (numCols1 != m_nCols))
		return false;
		
	// Loop over all the elements and compute the sum-of-squared-differences.
	double cumulativeSum = 0.0;
	for (int i=0; i<m_nElements; ++i)
	{
		double element1 = matrix1.m_matrixData[i];
		double element2 = m_matrixData[i];
		cumulativeSum += ((element1 - element2) * (element1 - element2));
	}
	double finalValue = sqrt(cumulativeSum / ((numRows1 * numCols1)-1));
	if (finalValue < tolerance)
		return true;
	else
		return false;
}

/* **************************************************************************************************
OVERLOADED OPERATOR FUNCTIONS
/* *************************************************************************************************/

/* **************************************************************************************************
THE + OPERATOR
/* *************************************************************************************************/
// matrix + matrx.
qbMatrix2 operator+ (const qbMatrix2& lhs, const qbMatrix2& rhs)
{
	int numRows = lhs.m_nRows;
	int numCols = lhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; i++)
		tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// scaler + matrix
qbMatrix2 operator+ (const double& lhs, const qbMatrix2& rhs)
{
	int numRows = rhs.m_nRows;
	int numCols = rhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs + rhs.m_matrixData[i];
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix + scaler
qbMatrix2 operator+ (const qbMatrix2& lhs, const double& rhs)
{
	int numRows = lhs.m_nRows;
	int numCols = lhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs.m_matrixData[i] + rhs;
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

/* **************************************************************************************************
THE - OPERATOR
/* *************************************************************************************************/
// matrix - matrix
qbMatrix2 operator- (const qbMatrix2& lhs, const qbMatrix2& rhs)
{
	int numRows = lhs.m_nRows;
	int numCols = lhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; i++)
		tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;    
}

// scaler - matrix
qbMatrix2 operator- (const double& lhs, const qbMatrix2& rhs)
{
	int numRows = rhs.m_nRows;
	int numCols = rhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs - rhs.m_matrixData[i];
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix - scaler
qbMatrix2 operator- (const qbMatrix2& lhs, const double& rhs)
{
	int numRows = lhs.m_nRows;
	int numCols = lhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs.m_matrixData[i] - rhs;
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

/* **************************************************************************************************
THE * OPERATOR
/* *************************************************************************************************/
// matrix * vector
qbVector operator* (const qbMatrix2& lhs, const qbVector& rhs)
{
	// Verify the dimensions of the inputs.
	if (lhs.m_nCols != rhs.GetNumDims())
		throw std::invalid_argument("Number of columns in matrix must equal number of rows in vector.");
	
	// Setup the vector for the output.
	qbVector result(lhs.m_nRows);
	
	// Loop over rows and columns and perform the multiplication operation element-by-element.
	for (int row=0; row<lhs.m_nRows; ++row)
	{
		double cumulativeSum = 0.0;
		for (int col=0; col<lhs.m_nCols; ++col)
		{
			cumulativeSum += (lhs.GetElement(row,col) * rhs.GetElement(col));
		}
		result.SetElement(row, cumulativeSum);
	}
	
	return result;
}

// scaler * matrix
qbMatrix2 operator* (const double& lhs, const qbMatrix2& rhs)
{
	int numRows = rhs.m_nRows;
	int numCols = rhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs * rhs.m_matrixData[i];
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix * scaler
qbMatrix2 operator* (const qbMatrix2& lhs, const double& rhs)
{
	int numRows = lhs.m_nRows;
	int numCols = lhs.m_nCols;
	int numElements = numRows * numCols;
	double *tempResult = new double[numElements];
	for (int i=0; i<numElements; ++i)
		tempResult[i] = lhs.m_matrixData[i] * rhs;
		
	qbMatrix2 result(numRows, numCols, tempResult);
	delete[] tempResult;
	return result;
}

// matrix * matrix
qbMatrix2 operator* (const qbMatrix2& lhs, const qbMatrix2& rhs)
{
	int r_numRows = rhs.m_nRows;
	int r_numCols = rhs.m_nCols;
	int l_numRows = lhs.m_nRows;
	int l_numCols = lhs.m_nCols;

	if (l_numCols == r_numRows)
	{
		// This is the standard matrix multiplication condition.
		// The output will be the same size as the RHS.
		double *tempResult = new double[lhs.m_nRows * rhs.m_nCols];

		// Loop through each row of the LHS.
		for (int lhsRow=0; lhsRow<l_numRows; lhsRow++)
		{
			// Loop through each column on the RHS.
			for (int rhsCol=0; rhsCol<r_numCols; rhsCol++)
			{
				double elementResult = 0.0;
				// Loop through each element of this LHS row.
				for (int lhsCol=0; lhsCol<l_numCols; lhsCol++)
				{
					// Compute the LHS linear index.
					int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;

					// Compute the RHS linear index (based on LHS col).
					// rhs row number equal to lhs column number.
					int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;

					// Perform the calculation on these elements.
					elementResult += (lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex]);
				}

				// Store the result.
				int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
				tempResult[resultLinearIndex] = elementResult;
			}		
		}
		qbMatrix2 result(l_numRows, r_numCols, tempResult);
		delete[] tempResult;
		return result;
	}
	else
	{
		qbMatrix2 result(1, 1);
		return result;
	}
}

/* **************************************************************************************************
THE == OPERATOR
/* *************************************************************************************************/
bool qbMatrix2::operator== (const qbMatrix2& rhs)
{
	// Check if the matricies are the same size, if not return false.
	if ((this->m_nRows != rhs.m_nRows) && (this->m_nCols != rhs.m_nCols))
		return false;
		
	// Check if the elements are equal.
	bool flag = true;
	for (int i=0; i<this->m_nElements; ++i)
	{
		//if (this->m_matrixData[i] != rhs.m_matrixData[i])
		if (!CloseEnough(this->m_matrixData[i], rhs.m_matrixData[i]))
			flag = false;
	}
	return flag;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
qbMatrix2 qbMatrix2::operator= (const qbMatrix2 &rhs)
{
	// Make sure we're not assigning to ourself.
	if (this != &rhs)
	{
		m_nRows = rhs.m_nRows;
		m_nCols = rhs.m_nCols;
		m_nElements = rhs.m_nElements;
		
		if (m_matrixData)
			delete[] m_matrixData;
		
		m_matrixData = new double[m_nElements];
		for (int i=0; i<m_nElements; i++)
			m_matrixData[i] = rhs.m_matrixData[i];	
			
		return *this;
	}
    return *this;
}

/* **************************************************************************************************
SEPARATE THE MATRIX INTO TWO PARTS, AROUND THE COLUMN NUMBER PROVIDED
(Note that the output is returned into the two qbMatrix2 pointers in the input argument list)
/* *************************************************************************************************/
bool qbMatrix2::Separate(qbMatrix2 &matrix1, qbMatrix2 &matrix2, int colNum)
{
	// Compute the sizes of the new matrices.
	int numRows = m_nRows;
	int numCols1 = colNum;
	int numCols2 = m_nCols - colNum;
	
	// Resize the two matrices to the proper dimensions.
	matrix1.Resize(numRows, numCols1);
	matrix2.Resize(numRows, numCols1);
	
	// Loop over the original matrix and store data into the appropriate elements of the two
	// output matrices.
	for (int row=0; row<m_nRows; ++row)
	{
		for (int col=0; col<m_nCols; ++col)
		{
			if (col < colNum)
			{
				matrix1.SetElement(row, col, this->GetElement(row, col));
			}
			else
			{
				matrix2.SetElement(row, col-colNum, this->GetElement(row, col));
			}
		}
	}
	return true;
}

/* **************************************************************************************************
JOIN TwO MATRICES TOGETHER
/* *************************************************************************************************/
bool qbMatrix2::Join (const qbMatrix2& matrix2)
{
	// Extract the information that we need from both matrices
	int numRows1 = m_nRows;
	int numRows2 = matrix2.m_nRows;
	int numCols1 = m_nCols;
	int numCols2 = matrix2.m_nCols;
	
	// If the matrices have different numbers of rows, then this operation makes no sense.
	if (numRows1 != numRows2)
		throw std::invalid_argument("Attempt to join matrices with different numbers of rows is invalid.");
	
	// Allocate memory for the result.
	// Note that only the number of columns increases.
	double* newMatrixData = new double[numRows1*(numCols1+numCols2)];
	
	// Copy the two matrices into the new one.
	int linearIndex, resultLinearIndex;
	for (int i=0; i<numRows1; ++i)
	{
		for (int j=0; j<(numCols1+numCols2); ++j)
		{
			resultLinearIndex = (i * (numCols1+numCols2)) + j;
			
			// If j is in the left hand matrix, we get data from there...
			if (j < numCols1)
			{
				linearIndex = (i * numCols1) + j;
				newMatrixData[resultLinearIndex] = m_matrixData[linearIndex];
			}
			// Otherwise, j must be in the right hand matrix, so we get data from there...
			else
			{
				linearIndex = (i * numCols2) + (j - numCols1);
				newMatrixData[resultLinearIndex] = matrix2.m_matrixData[linearIndex];
			}
		}
	}
	
	// Update the stored data.
	m_nCols = numCols1+numCols2;
	m_nElements = m_nRows * m_nCols;
	delete[] m_matrixData;
	m_matrixData = new double[m_nElements];
	for (int i=0; i<m_nElements; ++i)
		m_matrixData[i] = newMatrixData[i];
	
	delete[] newMatrixData;
	return true;
}

/* **************************************************************************************************
COMPUTE MATRIX DETERMINANT
/* *************************************************************************************************/
double qbMatrix2::Determinant()
{
	// Check if the matrix is square.
	if (!IsSquare())
		throw std::invalid_argument("Cannot compute the determinant of a matrix that is not square.");
		
	// If the matrix is 2x2, we can just compute the determinant directly.
	double determinant;
	if (m_nRows == 2)
	{
		determinant = (m_matrixData[0] * m_matrixData[3]) - (m_matrixData[1] * m_matrixData[2]);
	}
	else
	{
		/* Otherwise we extract the sub-matrices and then recursively call this function
			until we get to 2x2 matrices. */
			
		// We will find the sub-matrices for row 0.
		// So, loop over each column.
		double cumulativeSum = 0.0;
		double sign = 1.0;
		for (int j=0; j<m_nCols; ++j)
		{
			// And find the sub-matrix for each element.
			qbMatrix2 subMatrix = this->FindSubMatrix(0, j);
			
			/* Cumulatively multiply the determinant of the sub-matrix by the
				current element of this matrix and the sign variable (note the
				recursive calling of the Determinant() method). */
			cumulativeSum += this->GetElement(0, j) * subMatrix.Determinant() * sign;
			sign = -sign;
		}
		determinant = cumulativeSum;
	}	
		
	return determinant;
}

/* **************************************************************************************************
COMPUTE MATRIX INVERSE (USING GAUSS-JORDAN ELIMINATION)
/* *************************************************************************************************/
bool qbMatrix2::Inverse()
{
	// Check if the matrix is square (we cannot compute the inverse if it isn't).
	if (!IsSquare())
		throw std::invalid_argument("Cannot compute the inverse of a matrix that is not square.");
	
	// If we get to here, the matrix is square so we can continue.
	
	// Form an identity matrix with the same dimensions as the matrix we wish to invert.
	qbMatrix2 identityMatrix(m_nRows, m_nCols);
	identityMatrix.SetToIdentity();
	
	// Join the identity matrix to the existing matrix.	
	int originalNumCols = m_nCols;
	Join(identityMatrix);

	// Begin the main part of the process.
	int cRow, cCol;
	int maxCount = 100;
	int count = 0;
	bool completeFlag = false;
	while ((!completeFlag) && (count < maxCount))
	{
		for (int diagIndex=0; diagIndex<m_nRows; ++diagIndex)
		{		
			// Loop over the diagonal of the matrix and ensure all diagonal elements are equal to one.
			cRow = diagIndex;
			cCol = diagIndex;

			// Find the index of the maximum element in the current column.
			int maxIndex = FindRowWithMaxElement(cCol, cRow);
		
			// If this isn't the current row, then swap.
			if (maxIndex != cRow)
			{
				//std::cout << "Swap rows " << cRow << " and " << maxIndex << std::endl;
				SwapRow(cRow, maxIndex);
			}
			// Make sure the value at (cRow,cCol) is equal to one.
			if (m_matrixData[Sub2Ind(cRow,cCol)] != 1.0)
			{
				double multFactor = 1.0 / m_matrixData[Sub2Ind(cRow,cCol)];
				MultRow(cRow, multFactor);
				//std::cout << "Multiply row " << cRow << " by " << multFactor << std::endl;
			}
		
			// Consider the column.
			for (int rowIndex=cRow+1; rowIndex<m_nRows; ++rowIndex)
			{
				// If the element is already zero, move on.
				if (!CloseEnough(m_matrixData[Sub2Ind(rowIndex, cCol)], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					int rowOneIndex = cCol;
				
					// Get the value stored at the current element.
					double currentElementValue = m_matrixData[Sub2Ind(rowIndex, cCol)];
					
					// Get the value stored at (rowOneIndex, cCol)
					double rowOneValue = m_matrixData[Sub2Ind(rowOneIndex, cCol)];
					
					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{
						// Compute the correction factor.
						// (required to reduce the element at (rowIndex, cCol) to zero).
						double correctionFactor = -(currentElementValue / rowOneValue);
	
						MultAdd(rowIndex, rowOneIndex, correctionFactor);
						
						//std::cout << "Multiply row " << rowOneIndex << " by " << correctionFactor <<
						//	" and add to row " << rowIndex << std::endl;
					}
				}
			}
		
			// Consider the row.			
			for (int colIndex=cCol+1; colIndex<originalNumCols; ++colIndex)
			{			
				// If the element is already zero, move on.
				if (!CloseEnough(m_matrixData[Sub2Ind(cRow, colIndex)], 0.0))
				{
					// Obtain the element to work with from the matrix diagonal.
					// As we aim to set all the diagonal elements to one, this should
					// always be valid for a matrix that can be inverted.
					int rowOneIndex = colIndex;
				
					// Get the value stored at the current element.
					double currentElementValue = m_matrixData[Sub2Ind(cRow, colIndex)];
					
					// Get the value stored at (rowOneIndex, colIndex)
					double rowOneValue = m_matrixData[Sub2Ind(rowOneIndex, colIndex)];
					
					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{					
						
						// Compute the correction factor.
						// (required to reduce the element at (cRow, colIndex) to zero).
						double correctionFactor = -(currentElementValue / rowOneValue);				
					
						// To make this equal to zero, we need to add -currentElementValue multiplied by
						// the row at rowOneIndex.
						MultAdd(cRow, rowOneIndex, correctionFactor);
						
						//std::cout << "Multiply row " << rowOneIndex << " by " << correctionFactor <<
						//	" and add to row " << cRow << std::endl;
					}
				}
			}
		}
		
		// Separate the result into the left and right halves.
		qbMatrix2 leftHalf;
		qbMatrix2 rightHalf;
		this->Separate(leftHalf, rightHalf, originalNumCols);
		
		// When the process is complete, the left half should be the identity matrix.
		if (leftHalf == identityMatrix)
		{
			// Set completedFlag to true to indicate that the process has completed.
			completeFlag = true;
			
			// Rebuild the matrix with just the right half, which now contains the result.			
			m_nCols = originalNumCols;
			m_nElements = m_nRows * m_nCols;
			delete[] m_matrixData;
			m_matrixData = new double[m_nElements];
			for (int i=0; i<m_nElements; ++i)
				m_matrixData[i] = rightHalf.m_matrixData[i];
		}
		
		// Increment the counter.
		count++;
	}
	
	// Return whether the process succeeded or not.
	return completeFlag;
}

/* **************************************************************************************************
COMPUTE AND RETURN THE TRANSPOSE
/* *************************************************************************************************/
qbMatrix2 qbMatrix2::Transpose() const
{
	// Form the output matrix.
	// Note that we reverse the order of rows and columns, as this will be the transpose.
	qbMatrix2 resultMatrix(m_nCols, m_nRows);
	
	// Now loop through the elements and copy in the appropriate order.
	for (int i=0; i<m_nRows; ++i)
	{
		for (int j=0; j<m_nCols; ++j)
		{
			resultMatrix.SetElement(j, i, this->GetElement(i, j));
		}
	}
	
	return resultMatrix;
}

/* **************************************************************************************************
CONVERT TO ROW ECHELON FORM (USING GAUSSIAN ELIMINATION)
/* *************************************************************************************************/
qbMatrix2 qbMatrix2::RowEchelon()
{
	/* The current matrix must have at least as many columns as rows, but note that we don't
		actually require it to be square since we assume that the user may have combined a
		square matrix with a vector. They would do this, for example, if they were trying to 
		solve a system of linear equations. */
	if (m_nCols < m_nRows)
		throw std::invalid_argument("The matrix must have at least as many columns as rows.");
	
	/* Make a copy of the matrix data before we start. We do this because the procedure below
		will make changes to the stored matrix data (it operates 'in place') and we don't want
		this behaviour. Therefore we take a copy at the beginning and then we will replace the
		modified matrix data with this copied data at the end, thus preserving the original. */
	double *tempMatrixData;
	tempMatrixData = new double[m_nRows * m_nCols];
	for (int i=0; i<(m_nRows*m_nCols); ++i)
		tempMatrixData[i] = m_matrixData[i]; 
	
	// Begin the main part of the process.
	int cRow, cCol;
	int maxCount = 100;
	int count = 0;
	bool completeFlag = false;
	while ((!completeFlag) && (count < maxCount))
	{
		for (int diagIndex=0; diagIndex<m_nRows; ++diagIndex)
		{	
			// Loop over the diagonal of the matrix and ensure all diagonal elements are equal to one.
			cRow = diagIndex;
			cCol = diagIndex;
			
			// Find the index of the maximum element in the current column.
			int maxIndex = FindRowWithMaxElement(cCol, cRow);
			
			// Now consider the column.
			// Our aim is to set all elements BELOW the diagonal to zero.
			for (int rowIndex=cRow+1; rowIndex<m_nRows; ++rowIndex)
			{
				// If the element is already zero, move on.
				if (!CloseEnough(m_matrixData[Sub2Ind(rowIndex, cCol)], 0.0))
				{
					int rowOneIndex = cCol;
				
					// Get the value stored at the current element.
					double currentElementValue = m_matrixData[Sub2Ind(rowIndex, cCol)];
					
					// Get the value stored at (rowOneIndex, cCol)
					double rowOneValue = m_matrixData[Sub2Ind(rowOneIndex, cCol)];
					
					// If this is equal to zero, then just move on.
					if (!CloseEnough(rowOneValue, 0.0))
					{
						// Compute the correction factor.
						// (required to reduce the element at (rowIndex, cCol) to zero).
						double correctionFactor = -(currentElementValue / rowOneValue);
						MultAdd(rowIndex, rowOneIndex, correctionFactor);
					}
				}
			}							
		}
		
		/* Test whether we have achieved the desired result of converting the
			matrix into row-echelon form. */
		completeFlag = this->IsRowEchelon();
		
		// Increment the counter.
		count++;
	}
	
	// Form the output matrix.
	qbMatrix2 outputMatrix(m_nRows, m_nCols, m_matrixData);
	
	// Restore the original matrix data from the copy.
	for (int i=0; i<(m_nRows * m_nCols); ++i)
		m_matrixData[i] = tempMatrixData[i];
	
	// Delete the copy.
	delete[] tempMatrixData;
	
	return outputMatrix;
}

/* **************************************************************************************************
COMPUTE THE RANK OF THE PROVIDED MATRIX
/* *************************************************************************************************/
int qbMatrix2::Rank()
{
	// Convert the matrix to row-echelon form.
	qbMatrix2 matrixCopy = this->RowEchelon();
	
	/* If this didn't work, then we compute the rank by finding
		the largest non-zero sub-matrix with a non-zero determinant.
		
		Note that this method is slower for large matrices and therefore
		it is better to use the RowEchelon method if possible. */
	int numNonZeroRows = 0;
	if (!matrixCopy.IsRowEchelon())
	{
		// Setup a std::vector to store the sub-matrices as we go.
		std::vector<qbMatrix2> subMatrixVector;
		
		// Store the current matrix into the array first.
		subMatrixVector.push_back(*this);
		
		/* Loop through the subMatrixVector until either we have tested every
			sub-matrix or the completeFlag is set. */
		bool completeFlag = false;
		int subMatrixCount = 0;
		while ((subMatrixCount < subMatrixVector.size()) && (!completeFlag))
		{	
			// Extract the currentMatrix to work with.
			qbMatrix2 currentMatrix = subMatrixVector[subMatrixCount];
			subMatrixCount++;
			
			// Test if this matrix is non-zero.
			if (currentMatrix.IsNonZero())
			{
				// If the determinant is non-zero, then we have our result.
				double currentMatrixDet = currentMatrix.Determinant();
				if (!CloseEnough(currentMatrixDet, 0.0))
				{
					completeFlag = true;
					numNonZeroRows = currentMatrix.GetNumRows();
				}
				else
				{
					// Extract and store each sub-matrix (if larger than 2x2).
					if ((currentMatrix.GetNumRows() > 2) && (currentMatrix.GetNumCols() > 2))
					{
						for (int i=0; i<currentMatrix.GetNumRows(); ++i)
						{
							for (int j=0; j<currentMatrix.GetNumCols(); ++j)
							{
								// Extract this sub-matrix and store.
								subMatrixVector.push_back(currentMatrix.FindSubMatrix(i,j));
							}
						}
					}
				}
			}
		}
	}
	else
	{
		/* Converting to row echelon form did work, so we can simply
			count the number of non-zero rows to get the rank. */
	
		/* If we get to here, then we can assume that the matrix is now
			in row-echelon form and we can compute the rank quite easily
			as simply the number of non-zero rows. */
			
		int nRows = matrixCopy.GetNumRows();
		int nCols = matrixCopy.GetNumCols();
			
		// Loop over each row and test whether it has at least one non-zero element.
		for (int i=0; i<nRows; ++i)
		{
			// Loop over the columns of this row.
			int colSum = 0;
			for (int j=0; j<nCols; ++j)
			{
				if (!CloseEnough(matrixCopy.GetElement(i,j), 0.0))
					colSum++;
			}
			// If colSum is greater than zero, then increment numNonZeroRows.
			if (colSum > 0)
				numNonZeroRows++;
		}
	
	}
	// The rank of the matrix is simply the number of non-zero rows.
	return numNonZeroRows;
	
}

/* **************************************************************************************************
PRIVATE FUNCTIONS
/* *************************************************************************************************/
// Function to return the linear index corresponding to the supplied row and column values.
int qbMatrix2::Sub2Ind(int row, int col) const
{
	if ((row < m_nRows) && (row >= 0) && (col < m_nCols) && (col >= 0))
		return (row * m_nCols) + col;
	else
		return -1;
}

// Function to test whether the matrix is square.
bool qbMatrix2::IsSquare()
{
	if (m_nCols == m_nRows)
		return true;
	else
		return false;
}

// Function to test whether the matrix is non-zero.
bool qbMatrix2::IsNonZero()
{
	// Loop over every element.
	int numNonZero = 0;
	for (int i=0; i<m_nElements; ++i)
	{
		// If this element is close enough to zero, then
		// increment our numNonZero counter.
		if (!CloseEnough(m_matrixData[i], 0.0))
			numNonZero++;
	}
	
	/* If the numNonZero counter is still equal to zero, then
		the matrix must be all zeros, hence we return false. 
		Otherwise we return true. */
	return (numNonZero != 0);
}

// Function to test whether the matrix is in row-echelon form.
bool qbMatrix2::IsRowEchelon()
{
	/* We do this by testing that the sum of all the elements in the
		lower triangular matrix is zero. */
	// Loop over each row, except the first one (which doesn't need to have any zero elements).
	double cumulativeSum = 0.0;
	for (int i=1; i<m_nRows; ++i)
	{
		/* Loop over the columns that correspond to the lower triangular
			matrix according to the current row. */
		for (int j=0; j<i; ++j)
		{
			// Add this element to the cumulative sum.
			cumulativeSum += m_matrixData[Sub2Ind(i, j)];
		}
	}
	
	/* If the matrix is in row-echelon form, then cumulative sum should
		still equal zero, otherwise the matrix cannot be in row-echelon form. */
	return CloseEnough(cumulativeSum, 0.0);
}

// Function to test whether the matrix is symmetric.
bool qbMatrix2::IsSymmetric()
{
	/* First test that the matrix is square, if it is
		not, then it cannot by symmetric. */
	if (!this->IsSquare())
		return false;
		
	// Now test for symmetry about the diagonal.
	double currentRowElement = 0.0;
	double currentColElement = 0.0;
	bool returnFlag = true;
	int diagIndex = 0;
	while ((diagIndex < m_nCols) && returnFlag)
	{
		int rowIndex = diagIndex + 1;
		while ((rowIndex < m_nRows) && returnFlag)
		{
			currentRowElement = this->GetElement(rowIndex, diagIndex);
			currentColElement = this->GetElement(diagIndex, rowIndex);
			
			// Compare the row and column elements.
			if (!CloseEnough(currentRowElement, currentColElement))
				returnFlag = false;
			
			// Increment row index.
			rowIndex++;
		}
		
		// Increment diagIndex.
		diagIndex++;
		
	}
	
	// Return the result.
	return returnFlag;
	
}

// Function to swap rows i and j (in place).
void qbMatrix2::SwapRow(int i, int j)
{
	// Store a tempory copy of row i.
	double *tempRow = new double[m_nCols];
	for (int k=0; k<m_nCols; ++k)
		tempRow[k] = m_matrixData[Sub2Ind(i,k)];
		
	// Replace row i with row j.
	for (int k=0; k<m_nCols; ++k)
		m_matrixData[Sub2Ind(i,k)] = m_matrixData[Sub2Ind(j,k)];
		
	// Replace row k with the tempory copy of the original row i.
	for (int k=0; k<m_nCols; ++k)
		m_matrixData[Sub2Ind(j,k)] = tempRow[k];
	
	// Tidy up after ourselves.
	delete[] tempRow;
}

// Function to add a multiple of row j to row i (in place).
void qbMatrix2::MultAdd(int i, int j, double multFactor)
{
	for (int k=0; k<m_nCols; ++k)
		m_matrixData[Sub2Ind(i,k)] += (m_matrixData[Sub2Ind(j,k)] * multFactor);
}

// Function to the find the row with the maximum element at the column given.
// Returns the row index.
int qbMatrix2::FindRowWithMaxElement(int colNumber, int startingRow)
{
	double tempValue = m_matrixData[Sub2Ind(startingRow, colNumber)];
	int rowIndex = startingRow;
	for (int k=startingRow+1; k<m_nRows; ++k)
	{
		if (fabs(m_matrixData[Sub2Ind(k, colNumber)]) > fabs(tempValue))
		{
			rowIndex = k;
			tempValue = m_matrixData[Sub2Ind(k, colNumber)];
		}
	}
	return rowIndex;
}

// Function to multiply a row by the given value.
void qbMatrix2::MultRow(int i, double multFactor)
{
	for (int k=0; k<m_nCols; ++k)
		m_matrixData[Sub2Ind(i,k)] *= multFactor;
}

// A simple function to print a matrix to stdout.
void qbMatrix2::PrintMatrix()
{
	int nRows = this->GetNumRows();
	int nCols = this->GetNumCols();
	for (int row = 0; row<nRows; ++row)
  {
	  for (int col = 0; col<nCols; ++col)
    {
	    std::cout << std::fixed << std::setprecision(3) << this->GetElement(row, col) << "  ";
    }
	std::cout << std::endl;
	}    
}

// A simple function to print a matrix to stdout, with specified precision.
void qbMatrix2::PrintMatrix(int precision)
{
	int nRows = this->GetNumRows();
	int nCols = this->GetNumCols();
	for (int row = 0; row<nRows; ++row)
  {
	  for (int col = 0; col<nCols; ++col)
    {
	    std::cout << std::fixed << std::setprecision(precision) << this->GetElement(row, col) << "  ";
    }
	std::cout << std::endl;
	}    
}

bool qbMatrix2::CloseEnough(double f1, double f2)
{
    return fabs(f1-f2) < 1e-9;
}

// Function to find the sub-matrix for the given element.
qbMatrix2 qbMatrix2::FindSubMatrix(int rowNum, int colNum)
{
	// Create a new matrix to store the sub-matrix.
	// Note that this is one row and one column smaller than the original.
	qbMatrix2 subMatrix(m_nRows-1, m_nCols-1);
	
	// Loop over the elements of the existing matrix and copy to sub-matrix as appropriate.
	int count = 0;
	for (int i=0; i<m_nRows; ++i)
	{
		for (int j=0; j<m_nCols; ++j)
		{
			// If i or j correspond to rowNum or colNum, then ignore this element.
			if ((i != rowNum) && (j != colNum))
			{
				subMatrix.m_matrixData[count] = this->GetElement(i,j);
				count++;
			}
		}
	}
	
	return subMatrix;
}
#endif