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
	과목이름을 초기화하고
	grades[student][test]도 같이 초기화를 해주는 생성자이다.
	*/

} // end two-argument GradeBook constructor

	// function to set the course name

/*



CourseName의 get함수 set함수를 만들어라.



*/

// display a welcome message to the GradeBook user
void GradeBook::displayMessage()
{
	
	/* 
	
	CourseName + 에 오신것을 환영합니다! 를 출력 해준다.
		
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
	
	grade[][]에서 가장 작은 성적을 리턴해준다.
	
	*/
} // end function getMinimum

// find maximum grade	
int GradeBook::getMaximum()
{
	int highestNum = 0;

	return highestNum;
	/*

	grade[][]에서 가장 큰 성적을 리턴해준다.

	*/
} // end function getMaximum     

// determine average grade for particular set of grades
double GradeBook::getAverage(const int setOfGrades[], const int grades)
{
	/*

	한 학생의 성적을 출력해주는 값을 리턴하시오. 소수점 둘째 자리 까지.
	setOfGrades[] 변수에는 한 명의 grade값 세개가 한번에 들어갈 배열 이다.
	
	*/
} // end function getAverage

// output bar chart displaying grade distribution
void GradeBook::outputBarChart()
{
	cout << "\nOverall grade distribution:" << endl;

	/*
	성적의 범위의 갯수에 따라서 barChart형식으로 출력될 수 있게 코딩한다. 

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

	출력화면처럼 setw, setprecision, fixed 를 이용하여 출력하시오.
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