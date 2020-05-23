#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::fixed;

#include <iomanip> // parameterized stream manipulators
using std::setprecision; // sets numeric output precision
using std::setw; // sets field width

// include definition of class GradeBook from GradeBook.h
#include "GradeBook.h"

// two-argument constructor initializes courseName and grades array
GradeBook::GradeBook(string name, const int gradesArray[][tests])
{
	courseName = name;
	for (int i = 0; i < students; ++i) {
		grades[students][tests] = gradesArray[i][tests];
	}
	/*
	�����̸��� �ʱ�ȭ�ϰ�
	grades[student][test]�� ���� �ʱ�ȭ�� ���ִ� �������̴�.
	*/

} // end two-argument GradeBook constructor

	// function to set the course name

/*



CourseName�� get�Լ� set�Լ��� ������.



*/

// display a welcome message to the GradeBook user
void GradeBook::displayMessage()
{
	
	/* 
	
	CourseName + �� ���Ű��� ȯ���մϴ�! �� ��� ���ش�.
		
	*/

} // end function displayMessage

// perform various operations on the data
void GradeBook::processGrades()
{
	// output grades array
	outputGrades();

	// call functions getMinimum and getMaximum
	cout << "\nLowest grade in the grade book is " << getMinimum()
		<< "\nHighest grade in the grade book is " << getMaximum() << endl;

	// output grade distribution chart of all grades on all tests
	outputBarChart();
} // end function processGrades

// find minimum grade
int GradeBook::getMinimum()
{
	int lowestNumber = 100;

	
	return lowestNumber;
	/*
	
	grade[][]���� ���� ���� ������ �������ش�.
	
	*/
} // end function getMinimum

// find maximum grade	
int GradeBook::getMaximum()
{
	int highestNum = 0;

	return highestNum;
	/*

	grade[][]���� ���� ū ������ �������ش�.

	*/
} // end function getMaximum     

// determine average grade for particular set of grades
double GradeBook::getAverage(const int setOfGrades[], const int grades)
{
	/*

	�� �л��� ������ ������ִ� ���� �����Ͻÿ�. �Ҽ��� ��° �ڸ� ����.
	setOfGrades[] �������� �� ���� grade�� ������ �ѹ��� �� �迭 �̴�.
	
	*/
} // end function getAverage

// output bar chart displaying grade distribution
void GradeBook::outputBarChart()
{
	cout << "\nOverall grade distribution:" << endl;

	/*
	������ ������ ������ ���� barChart�������� ��µ� �� �ְ� �ڵ��Ѵ�. 

  0-9: 
10-19: 
20-29: 
30-39: 
40-49: 
50-59: 
60-69: ***
70-79: ******
80-89: ***********
90-99: *******
  100: ***

	*/
} // end function outputBarChart

// output the contents of the grades array
void GradeBook::outputGrades()
{

	/*

	���ȭ��ó�� setw, setprecision, fixed �� �̿��Ͽ� ����Ͻÿ�.
	The grades are:

            Test 1  Test 2  Test 3  Average
Student  1      87      96      70    84.33
Student  2      68      87      90    81.67
Student  3      94     100      90    94.67
Student  4     100      81      82    87.67
Student  5      83      65      85    77.67
Student  6      78      87      65    76.67
Student  7      85      75      83    81.00
Student  8      91      94     100    95.00
Student  9      76      72      84    77.33
Student 10      87      93      73    84.33

	*/
} // end function outputGrades