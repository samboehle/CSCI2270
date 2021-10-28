#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

struct studentData
{
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length)
{
    studentData student;

    student.studentName = studentName;
    student.homework = homework;
    student.recitation = recitation;
    student.quiz = quiz;
    student.exam = exam;
    student.average = (homework + recitation + quiz + exam) / 4.0;

    students[length] = student;
}

char calcLetter(double avg)
{
    if(avg >= 90)
    {
        return 'A';
    }
    if(avg < 90 && avg >= 80)
    {
        return 'B';
    }
    if(avg < 80 && avg >= 70)
    {
        return 'C';
    }
    if(avg < 70 && avg >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

void printList(const studentData students[], int length)
{
    for(int i=0; i < length; i++)
    {
        cout << students[i].studentName << " earned " << students[i].average << " which is an " << calcLetter(students[i].average) << endl;
    }

}

int split(string main, char splitter, string array[], int size)
{
    main += splitter;
    char current;
    int place = 0;


    for(int i = 0; i < main.length(); i++)
    {
        
        if(main[i] != splitter)
        {
            array[place] += main[i];
        }
        else if(main[i] == splitter)
        {
            place++;
        }
    }
    

    return place;

}

int main(int argc, char *argv[])
{
    int n = 100;
    studentData students[n];
    
    ifstream myfile;
    myfile.open(argv[1]);
    if(myfile.fail())
    {
        cout << "Failed to open the file." << endl;
    }

    string line;
    string current[5];
    int size = 0;
    while(getline(myfile, line))
    {
        split(line, ',', current, 5);
        addStudentData(students, current[0], stoi(current[1]), stoi(current[2]), stoi(current[3]), stoi(current[4]), size);
        size++;
        fill_n(current, 5, "");
    }

    printList(students, size);

    int lower = int(*argv[3]);
    int upper = int(*argv[4]);

    
    ofstream output(argv[2]);
    int grade;
    for(int i = 0; i < size; i++)
    {
        grade = int(calcLetter(students[i].average));
        if(grade <= lower && grade >= upper)
        {
            output << students[i].studentName << ", " << students[i].average << ", " << calcLetter(students[i].average) << endl;
        }
    }

    output.close();
    return 0;

}