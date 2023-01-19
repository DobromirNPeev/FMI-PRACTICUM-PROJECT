#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void SwapDoubles(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}
void SwapString(string& a, string& b)
{
	string temp = a;
	a = b;
	b = temp;
}
double gettingAverage(vector<double> input) {
	double sum = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		sum += input[i];
	}
	return sum / input.size();
}
bool isItANumber(char mask) {
	return mask >= '0' && mask <= '9';
}
bool checkIfALineHasAWord(string line, string search) {
	int offset;
	if ((offset = line.find(search, 0)) != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CheckWord(string filename, string search)
{
	int offset;
	string line;
	ifstream Myfile;
	Myfile.open(filename);

	if (Myfile.is_open())
	{
		while (!Myfile.eof())
		{
			getline(Myfile, line);
			if ((offset = line.find(search, 0)) != string::npos)
			{
				Myfile.close();
				return true;
			}
		}
		Myfile.close();
	}
	else
		cout << "Unable to open this file." << endl;

	return false;
}
void eraseFileLine(string filename, string facultyNumber) {
	fstream read_file;
	read_file.open(filename);
	if (read_file.fail())
	{
		cout << "Error opening file." << endl;
	}
	vector<string> lines;
	string line;
	while (getline(read_file, line))
		lines.push_back(line);
	read_file.close();
	ofstream write_file;
	write_file.open(filename);
	if (write_file.fail())
	{
		cout << "Error opening file." << endl;
		return;
	}
	for (int i = 0; i < lines.size(); i++)
		if (!checkIfALineHasAWord(lines[i], facultyNumber))
			write_file << lines[i] << endl;
	write_file.close();
}
void PuttingFileLinesIntoAVector(string filename, vector<string>& lines) {
	fstream read_file;
	read_file.open(filename);
	if (read_file.fail())
	{
		cout << "Error opening file." << endl;
		return;
	}
	string currLine;
	while (getline(read_file, currLine)) {
		if (currLine == "") {
			break;
		}
		lines.push_back(currLine);
	}
	read_file.close();
}
void IteratingThroughElementsAndErasing(vector<double>& grades) {
	for (size_t j = 0; j < grades.size() - 1; j++)
	{
		if (grades[j] == grades[j + 1]) {
			grades.erase(grades.begin() + j);
		}
	}
}
void ErasingRepeatingGrades(vector<double>& grades) {
	for (size_t i = 0; i < grades.size() - 1; i++)
	{
		IteratingThroughElementsAndErasing(grades);
	}
}
void sortingAscendingDoubles(vector <double>& grades) {
	for (size_t i = 0; i < grades.size() - 1; i++)
	{
		for (size_t j = 0; j < grades.size() - 1; j++)
		{
			if (grades[j] > grades[j + 1])
			{
				SwapDoubles(grades[j], grades[j + 1]);
			}
		}
	}
}
void sortingDescendingDoubles(vector <double>& grades) {
	for (size_t i = 0; i < grades.size() - 1; i++)
	{
		for (size_t j = 0; j < grades.size() - 1; j++)
		{
			if (grades[j] < grades[j + 1])
			{
				SwapDoubles(grades[j], grades[j + 1]);
			}
		}
	}
}
void sortingAscending(vector <string>& facNumbers) {
	for (size_t i = 0; i < facNumbers.size() - 1; i++)
	{
		for (size_t j = 0; j < facNumbers.size() - 1; j++)
		{
			if (facNumbers[j] > facNumbers[j + 1])
			{
				SwapString(facNumbers[j], facNumbers[j + 1]);
			}
		}
	}
}
void sortingDescending(vector<string>& facNumbers) {
	for (size_t i = 0; i < facNumbers.size() - 1; i++)
	{
		for (size_t j = 0; j < facNumbers.size() - 1; j++)
		{
			if (facNumbers[j] < facNumbers[j + 1])
			{
				SwapString(facNumbers[j], facNumbers[j + 1]);
			}
		}
	}
}
void GettinFacultyNumber(string line,int begin,int end,string& currentFacNumbers) {
	for (size_t i = 0; i < line.size(); i++)
	{
		if (isItANumber(line[i])) {
			begin = i;
			break;
		}
	}
	end = begin + 9;
	for (size_t i = begin; i <= end; i++)
	{
		currentFacNumbers += line[i];
	}
}
void GettingCurrentGrades(string line, vector<double>& currentGrades) {
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == ':') {
			string currentGrade;
			for (size_t j = i + 1; j < i + 5; j++)
			{
				currentGrade += line[j];
			}
			currentGrades.push_back(stod(currentGrade));
		}
	}
}
void RearrangeFacultyNumbers(vector<string> facNumbers,int begin,int end,vector<string> lines,ofstream& write_file,int i) {
	for (size_t j = 0; j < facNumbers.size(); j++)
	{
		string currentFacNumbers;
		string currNum = lines[j];
		GettinFacultyNumber(currNum, begin, end, currentFacNumbers);
		if (currentFacNumbers == facNumbers[i]) {
			write_file << lines[j] << endl;
			return;
		}
	}
}
void RearrangeAverageGrades(vector<string> lines, vector<double> grades, ofstream& write_file, int i) {
	for (size_t j = 0; j < lines.size(); j++)
	{
		string currLine = lines[j];
		vector<double> currentGrades;
		GettingCurrentGrades(currLine, currentGrades);
		if (gettingAverage(currentGrades) == grades[i]) {
			write_file << lines[j] << endl;
		}
	}
}
void SortFaculty(string filename,string typeOfSort) {
	int begin=0,end=0;
	string line,mask;
	ifstream Myfile;
	vector<string> facNumbers,lines;
	PuttingFileLinesIntoAVector(filename, lines);
	Myfile.open(filename);
	if (Myfile.is_open())
	{
		while (!Myfile.eof())
		{
			string currentFacNumbers;
			getline(Myfile, line);
			if (line == "") {
				break;
			}
			GettinFacultyNumber(line, begin, end, currentFacNumbers);
			facNumbers.push_back(currentFacNumbers);
		}
		Myfile.close();
	}
	if (typeOfSort == "Ascending") {
		sortingAscending(facNumbers);
	}
	else if (typeOfSort == "Descending") {
		sortingDescending(facNumbers);
	}
	ofstream write_file;
	write_file.open(filename);
	if (write_file.fail())
	{
		cout << "Error opening file." << endl;
		return;
	}
	for (int i = 0; i < facNumbers.size(); i++) {
		RearrangeFacultyNumbers(facNumbers, begin, end, lines, write_file, i);
	}
	write_file.close();
}
void SortGrade(string filename,string typeOfSort) {
	int begin = 0, end = 0;
	string line, mask;
	ifstream Myfile;
	vector<double> grades;
	vector<string> lines;
	PuttingFileLinesIntoAVector(filename, lines);
	Myfile.open(filename);
	if (Myfile.is_open())
	{
		while (!Myfile.eof())
		{
			string currentFacNumbers;
			getline(Myfile, line);
			if (line == "") {
				break;
			}
			vector<double> currentGrades;
			GettingCurrentGrades(line, currentGrades);
			grades.push_back(gettingAverage(currentGrades));
		}
		Myfile.close();
	}
	if (typeOfSort == "Ascending") {
		sortingAscendingDoubles(grades);
	}
	else if (typeOfSort == "Descending") {
		sortingDescendingDoubles(grades);
	}
	ErasingRepeatingGrades(grades);
	ofstream write_file;
	write_file.open(filename);
	if (write_file.fail())
	{
		cout << "Error opening file." << endl;
		return;
	}
	for (int i = 0; i < grades.size(); i++) {
		RearrangeAverageGrades(lines, grades, write_file, i);
	}
	write_file.close();
}
bool NameValidator(string name) {
	int intervalsCounter = 0;
	for (size_t i = 0; i < name.size(); i++)
	{
		if (name[i] == ' ') {
			intervalsCounter++;
		}
		else if (isItANumber(name[i])) {
			return false;
		}
	}
	if (intervalsCounter == 2) {
		return true;
	}
	return false;
}
bool FacultyNumberValidator(string facultyNumber) {
	if (facultyNumber[1] != 'M' || facultyNumber[2] != 'I' || facultyNumber.size()!=10) {
		return false;
	}
	for (size_t i = 0; i < facultyNumber.size(); i++)
	{
		if (i == 1 || i == 2) {
			continue;
		}
		if (!isItANumber(facultyNumber[i])) {
			return false;
		}
	}
	return true;
}
bool SubjectsValidator(string SubjectsAndGrades) {
	vector<string> subjects;
	vector<double> grades;
	for (size_t i = 0; i < SubjectsAndGrades.size(); i++)
	{
		if (i > SubjectsAndGrades.size()) {
			break;
		}
		if (SubjectsAndGrades[i] == ':') {
			string currentGrade;
			for (size_t j = i + 1; j < i + 5; j++)
			{
				if (isItANumber(SubjectsAndGrades[j]) || SubjectsAndGrades[j]=='.') {
					currentGrade += SubjectsAndGrades[j];
					}
					else {
						return false;
					}
			}
			grades.push_back(stod(currentGrade));
			i+=5;
		}
		else {
			string subject;
			while (SubjectsAndGrades[i] != ':') {
				subject += SubjectsAndGrades[i];
				i++;
				if (i > SubjectsAndGrades.size())
					break;
			}
			i--;
			subjects.push_back(subject);
		}
	}
	if (subjects.size() < 1 || subjects.size() > 10) {
		return false;
	}
	if (subjects.size() != grades.size()) {
		return false;
	}
	for (size_t i = 0; i < grades.size(); i++)
	{
		if (grades[i] < 2.0 || grades[i]>6.0) {
			return false;
		}
	}
	return true;
}
bool GroupValidator(string group) {
	if (group.size() != 7) {
		return false;
	}
	int groupNumber = group[6]-'0';
	if (groupNumber<1 || groupNumber>8) {
		return false;
	}
	return true;
}
bool GroupsValidator(vector<string> groups) {
	for (size_t i = 0; i < groups.size(); i++)
	{
		if (!GroupValidator(groups[i])) {
			return false;
		}
	}
	return true;
}
void ConvertingInputToVector(string groups,vector<string>& groupsAsAVector) {
	string current;
	for (size_t i = 0; i < groups.size(); i++)
	{
		if (groups[i] == ',') {
			groupsAsAVector.push_back(current);
			current = "";
		}
		else {
			current += groups[i];
		}
	}
	groupsAsAVector.push_back(current);
}
void RearrangeMoreThanOneGroupByFacultyNumber(vector<string> facNumbers,vector<string> lines,vector<string>& sorted,int i) {
	for (size_t j = 0; j < facNumbers.size(); j++)
	{
		int begin = 0, end = 0;
		string currentFacNumbers;
		string currNum = lines[j];
		GettinFacultyNumber(currNum, begin, end, currentFacNumbers);
		if (currentFacNumbers == facNumbers[i]) {
			sorted.push_back(lines[j]);
			break;
		}
	}
}
void RearrangeMoreThanOneGroupByAverageGrade(vector<string> lines, vector<double> grades, vector<string>& sorted, int i) {
	for (size_t j = 0; j < lines.size(); j++)
	{
		string currentFacNumbers;
		string currLine = lines[j];
		vector<double> currentGrades;
		GettingCurrentGrades(currLine, currentGrades);
		if (gettingAverage(currentGrades) == grades[i]) {
			sorted.push_back(lines[j]);
		}
	}
}
void SortingMoreThanOneGroupByFacultyNumber(vector<string> groups,string typeOfSort) {
	vector<string> lines,facNumbers,sorted;
	for (size_t i = 0; i < groups.size(); i++)
	{
		PuttingFileLinesIntoAVector(groups[i] + ".txt",lines);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		int begin=0, end = 0;
		string currLine = lines[i];
		string currentFacNumbers;
		GettinFacultyNumber(currLine, begin, end, currentFacNumbers);
		facNumbers.push_back(currentFacNumbers);
	}
	if (typeOfSort == "Ascending") {
		sortingAscending(facNumbers);
	}
	else if (typeOfSort == "Descending") {
		sortingDescending(facNumbers);
	}
	for (int i = 0; i < facNumbers.size(); i++) {
		RearrangeMoreThanOneGroupByFacultyNumber(facNumbers, lines, sorted, i);
	}
	for (size_t i = 0; i < sorted.size(); i++)
	{
		cout << sorted[i] << endl;
	}
}
void SortingMoreThanOneGroupByGrade(vector<string> groups,string typeOfSort) {
	vector<string> lines, sorted;
	vector<double> grades;
	for (size_t i = 0; i < groups.size(); i++)
	{
		PuttingFileLinesIntoAVector(groups[i] + ".txt",lines);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		vector<double> currentGrades;
		string currLine = lines[i];
		GettingCurrentGrades(currLine, currentGrades);
		grades.push_back(gettingAverage(currentGrades));
	}
	if (typeOfSort == "Ascending") {
		sortingAscendingDoubles(grades);
	}
	else if (typeOfSort == "Descending") {
		sortingDescendingDoubles(grades);
	}
	ErasingRepeatingGrades(grades);
	for (int i = 0; i < grades.size(); i++) {
		RearrangeMoreThanOneGroupByAverageGrade(lines, grades, sorted, i);
	}
	for (size_t i = 0; i < sorted.size(); i++)
	{
		cout << sorted[i] << endl;
	}
}
void printFile(string group) {
	ifstream file(group + ".txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
}

int main()
{
	cout << "Hello, welcome to students' information"<<endl;
	cout << "What would you want to do?"<<endl;
	while(true) {
		cout << endl;
		cout << "/////////////////////////////////////" << endl;
		cout << endl;
		cout << "You are given the following commands:" << endl;
		cout << "* Add student"<<endl;
		cout << "* Delete student"<<endl;
		cout << "* Sort (One group by average grade or by faculty number)" << endl;
		cout << "* Display (more than one group sorted by average grade or by faculty number)" << endl;
		cout << "* Exit" << endl;
		cout << "Command:" << endl;;
		string command;
		getline(cin, command);
		if (command == "Add student") {
			string name, facultyNumber, subjects, group;
			cout << "Which group ? (Example: Group 2)"<<endl;
			getline(cin, group);
			if (!GroupValidator(group)) {
				cout << "Invalid group" << endl;
				continue;
			}
			cout << "What is his name ? (Example: Dobromir Nedkov Peev)"<< endl;
			getline(cin, name);
			if (!NameValidator(name)) {
				cout << "Invalid name" << endl;;
				continue;
			}
			cout << "What is his/her faculty Number ? (Example: 0MI0000000)"<<endl;
			getline(cin, facultyNumber);
			if(!FacultyNumberValidator(facultyNumber) || CheckWord(group + ".txt", facultyNumber)) {
				cout << "Invalid Faculty Number" << endl;;
				continue;
			}
			cout << "What subjects does he/she study and what are their grades ? (Maths:6.00,PE:3.00)" << endl;;
			getline(cin,subjects);
			if (!SubjectsValidator(subjects)) {
				cout << "Invalid subject input" << endl;
				continue;
			}
			ofstream file(group + ".txt", ios::app);
			if (file.is_open()) {
				file << name << " " << facultyNumber << " " << subjects << endl;;
				file.close();
			}
		}
		else if (command == "Delete student") {
			string facultyNumber,group;
			cout << "From which group ? (Example: Group 2)" << endl;
			getline(cin, group);
			if (!GroupValidator(group)) {
				cout << "Invalid group" << endl;
				continue;
			}
			cout << "What is his/her faculty number ? (Example: 0MI0000000)" << endl;
			getline(cin, facultyNumber);
			if (!FacultyNumberValidator(facultyNumber)) {
				cout << "Invalid Faculty Number" << endl;;
				continue;
			}
			if (CheckWord(group + ".txt", facultyNumber)) {
				eraseFileLine(group + ".txt", facultyNumber);
			}
			else {
				cout << "No such student"<<endl;
			}
		}
		else if (command == "Sort") {
			string typeOfSort,group;
			string AscendingOrDescending;
			cout << "Which group would you want to sort ? (Example: Group 2)" << endl;
			getline(cin, group);
			if (!GroupValidator(group)) {
				cout << "Invalid group" << endl;
				continue;
			}
			cout << "What type of sorting would you like ? (By Average Grade or By Faculty Number)" << endl;
			getline(cin,typeOfSort);
			if (typeOfSort == "By Average Grade") {
				cout << "Ascending or descending order ?" << endl;
				getline(cin, AscendingOrDescending);
				cout << endl;
				if (AscendingOrDescending == "Ascending" || AscendingOrDescending == "Descending") {
					SortGrade(group + ".txt",AscendingOrDescending);
					printFile(group);
				}
				else {
					cout << "Invalid desired ordering"<<endl;
				}
			}
			else if (typeOfSort == "By Faculty Number") {
				cout << "Ascending or descending order ?" << endl;
				getline(cin, AscendingOrDescending);
				cout << endl;
				if (AscendingOrDescending == "Ascending" || AscendingOrDescending == "Descending") {
					SortFaculty(group + ".txt",AscendingOrDescending);
					printFile(group);
				}
				else {
					cout << "Invalid desired ordering" << endl;
				}
			}
			else {
				cout << "No such type of sorting" << endl;
			}
		}
		else if (command == "Display") {
			string groups,typeOfSort;
			vector<string> groupsAsAVector;
			cout << "Which groups ? (Example: Group 2,Group 6)" << endl;
			getline(cin, groups);
			ConvertingInputToVector(groups, groupsAsAVector);
			if (!GroupsValidator(groupsAsAVector)) {
				cout << "Incorrect input" << endl;
				continue;
			}
			cout << "What type of sorting would you like ? (By Average Grade or By Faculty Number)" << endl;
			getline(cin, typeOfSort);
			if (typeOfSort == "By Average Grade") {
				string ascendingOrDescending;
				cout << "Ascending or descending ?" << endl;
				getline(cin, ascendingOrDescending);
				cout << endl;
				if (ascendingOrDescending == "Ascending" || ascendingOrDescending == "Descending") {
					SortingMoreThanOneGroupByGrade(groupsAsAVector,ascendingOrDescending);
				}
				else {
					cout << "Invalid desired ordering" << endl;
				}
			}
			else if (typeOfSort == "By Faculty Number") {
				string ascendingOrDescending;
				cout << "Ascending or descending ?" << endl;;
				getline(cin, ascendingOrDescending);
				cout << endl;
				if (ascendingOrDescending == "Ascending" || ascendingOrDescending == "Descending") {
					SortingMoreThanOneGroupByFacultyNumber(groupsAsAVector,ascendingOrDescending);
				}
				else {
					cout << "Invalid desired ordering" << endl;
				}
			}
			else {
				cout << "No such type of sorting" << endl;
			}
		}
		else if (command=="Exit") {
			break;
		}
		else {
			cout << "No such command. Please try again" << endl;
		}
	}
}