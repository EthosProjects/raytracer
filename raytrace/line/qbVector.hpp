#pragma once
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

class qbVector {
	public:
		// Define the various constructors.
		// Default.
		qbVector();
		
		// With a single integer specifying the number of dimensions.
		qbVector(int numDims);
		
		// With input data (std::vector).
		qbVector(std::vector<double> inputData);
		
		// And the destructor.
		~qbVector();	
		
		// Functions to return parameters of the vector.
		int GetNumDims() const;
		
		// Functions to handle elements of the vector.
		double GetElement(int index) const;
		void SetElement(int index, double value);
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		double norm();
		
		// Return a normalized copy of the vector.
		qbVector Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		qbVector operator+ (const qbVector &rhs) const;		
		qbVector operator- (const qbVector &rhs) const;
		qbVector operator* (const double &rhs) const;
		
		// Friend functions.
		friend qbVector operator* (const double &lhs, const qbVector &rhs);
		
		// Static functions.
		static double dot(const qbVector &a, const qbVector &b);
		static qbVector cross(const qbVector &a, const qbVector &b);
		
	private:
		std::vector<double> m_vectorData;
		int m_nDims;
		
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
qbVector::qbVector()
{
	m_nDims = 0;
	m_vectorData = std::vector<double>();
}

qbVector::qbVector(int numDims)
{
	m_nDims = numDims;
	m_vectorData = std::vector<double>(numDims, static_cast<double>(0.0));
}

qbVector::qbVector(std::vector<double> inputData)
{
	m_nDims = inputData.size();
	m_vectorData = inputData;
}

qbVector::~qbVector()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO RETURN PARAMETERS
/* *************************************************************************************************/
int qbVector::GetNumDims() const
{
	return m_nDims;
}

/* **************************************************************************************************
FUNCTIONS TO HANDLE ELEMENTS OF THE VECTOR
/* *************************************************************************************************/
double qbVector::GetElement(int index) const
{
	return m_vectorData[index];
}

void qbVector::SetElement(int index, double value)
{
	m_vectorData[index] = value;
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector,known as the 'norm'.
double qbVector::norm()
{
	double cumulativeSum = static_cast<double>(0.0);
	for (int i=0; i<m_nDims; ++i)
		cumulativeSum += (m_vectorData.at(i) * m_vectorData.at(i));
		
	return sqrt(cumulativeSum);
}

// Return a normalized copy of the vector.
qbVector qbVector::Normalized()
{
	// Compute the vector norm.
	double vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	qbVector result(m_vectorData);
	return result * (static_cast<double>(1.0) / vecNorm);
}

// Normalize the vector in place.
void qbVector::Normalize()
{
	// Compute the vector norm.
	double vecNorm = this->norm();
	
	// Compute the elements of the normalized version of the vector.
	for (int i=0; i<m_nDims; ++i)
	{
		double temp = m_vectorData.at(i) * (static_cast<double>(1.0) / vecNorm);
		m_vectorData.at(i) = temp;
	}
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
qbVector qbVector::operator+ (const qbVector &rhs) const
{
	// Check that the number of dimensions match.
	if (m_nDims != rhs.m_nDims)
		throw std::invalid_argument("Vector dimensions do not match.");
	
	std::vector<double> resultData;
	for (int i=0; i<m_nDims; ++i)
		resultData.push_back(m_vectorData.at(i) + rhs.m_vectorData.at(i));
		
	qbVector result(resultData);
	return result;
}

qbVector qbVector::operator- (const qbVector &rhs) const
{
	// Check that the number of dimensions match.
	if (m_nDims != rhs.m_nDims)
		throw std::invalid_argument("Vector dimensions do not match.");
	
	std::vector<double> resultData;
	for (int i=0; i<m_nDims; ++i)
		resultData.push_back(m_vectorData.at(i) - rhs.m_vectorData.at(i));
		
	qbVector result(resultData);
	return result;
}

qbVector qbVector::operator* (const double &rhs) const
{
	// Perform scalar multiplication.
	std::vector<double> resultData;
	for (int i=0; i<m_nDims; ++i)
		resultData.push_back(m_vectorData.at(i) * rhs);
		
	qbVector result(resultData);
	return result;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
qbVector operator* (const double &lhs, const qbVector &rhs)
{
	// Perform scalar multiplication.
	std::vector<double> resultData;
	for (int i=0; i<rhs.m_nDims; ++i)
		resultData.push_back(lhs * rhs.m_vectorData.at(i));
		
	qbVector result(resultData);
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
double qbVector::dot(const qbVector &a, const qbVector &b)
{
	// Check that the number of dimensions match.
	if (a.m_nDims != b.m_nDims)
		throw std::invalid_argument("Vector dimensions must match for the dot-product to be computed.");
	
	// Compute the dot product.
	double cumulativeSum = static_cast<double>(0.0);
	for (int i=0; i<a.m_nDims; ++i)
		cumulativeSum += a.m_vectorData.at(i) * b.m_vectorData.at(i);
	
	return cumulativeSum;
}

qbVector qbVector::cross(const qbVector &a, const qbVector &b)
{
	// Check that the number of dimensions match.
	if (a.m_nDims != b.m_nDims)
		throw std::invalid_argument("Vector dimensions must match for the cross-product to be computed.");
	
	// Check that the number of dimensions is 3.
	/* Although the cross-product is also defined for 7 dimensions, we are
		not going to consider that case at this time. */
	if (a.m_nDims != 3)
		throw std::invalid_argument("The cross-product can only be computed for three-dimensional vectors.");
	
	// Compute the cross product.
	std::vector<double> resultData;
	resultData.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
	resultData.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
	resultData.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) - (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

	qbVector result(resultData);
	return result;
}