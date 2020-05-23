#include<string>
using namespace std;

class GradeBook
{
public:
	const static int students = 10;
	const static int tests = 3;

	GradeBook(string, const int[][tests]);
	void setCourseName(string); // function to set the course name
	string getCourseName(); // function to retrieve the course name
	void displayMessage(); // display a welcome message
	void processGrades(); // perform various operations on the grade data
	int getMinimum(); // find the minimum grade in the grade book
	int getMaximum(); // find the maximum grade in the grade book
	double getAverage(const int[], const int); // find average of grades
	void outputBarChart(); // output bar chart of grade distribution
	void outputGrades(); // output the contents of the grades array
private:
	string courseName; // course name for this grade book
	int grades[students][tests]; // two-dimensional array of grades

};

