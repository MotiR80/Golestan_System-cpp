#include <iostream>
#include <string>
#include <vector>
using namespace std;

class courseInfo
{
private:
    string name,
            id,
            days,
            time,
            prerequisite,
            requisite;
    int units ;
    double  startTime,
            endTime;
public:
    void set_name(string Name){ name = Name; }
    void set_id(string Id){ id = Id; }
    void set_days(string Days){ days = Days; }
    void set_time(string Time){ time = Time; }
    void set_prerequisite(string Prerequisite){ prerequisite = Prerequisite; }
    void set_requisite(string Requisite){ requisite = Requisite; }
    void set_units(int Units){ units = Units; }
    void set_startTime(double sTime){ startTime = sTime; }
    void set_endTime(double eTime){ endTime = eTime; }
    string get_name(){ return name; }
    string get_id(){return id; }
    string get_days(){return days; }
    string get_time(){ return time; }
    string get_prerequisite(){return prerequisite; }
    string get_requisite(){ return requisite; }
    int get_units(){return units; }
    double get_startTime(){ return startTime; }
    double get_endTime(){ return endTime; }


};

class studentInfo
{
private:
    string id;
    vector<string> course;
    vector<bool> grade;
    vector<int> selectedLesson;
    int units = 0;
    bool checkGetLesson = false;
public:
    void set_id(string Id){ id= Id; }
    void set_course(string Course){ course.push_back(Course); }
    void set_grade(bool Grade){ grade.push_back(Grade); }
    void set_units(int Units){ units = Units; }
    void set_selectedLesson(int Select){ selectedLesson.push_back(Select); }
    void set_checkGetLesson(bool check){ checkGetLesson = check; }
    string get_id(){ return id; }
    vector<string> get_course(){ return course; }
    vector<bool> get_grade(){ return grade; }
    vector<int> get_selectedLesson(){ return selectedLesson; }
    int get_units(){ return units; }
    bool get_checkGetLesson(){ return checkGetLesson; }
};

courseInfo addCourse(string info, bool& check)
{
    courseInfo temp;
    bool a = true;
    int spaceFinder,wordCounter = 0;
    while (a)
    {
        spaceFinder = info.find(" ");
        if (spaceFinder == -1)
            spaceFinder = info.length();
        if(wordCounter == 0)
        {
            if (spaceFinder == info.length()){
                check = true;
                break;
            }
            while (info[spaceFinder - 1] == '\\')
                spaceFinder = info.find(" ", spaceFinder + 1);
            temp.set_name(info.substr(0, spaceFinder));
            while (temp.get_name().find('\\') != -1)
                temp.set_name(temp.get_name().erase(temp.get_name().find('\\'),1));
            info = info.substr(spaceFinder + 1);
        }
        if(wordCounter == 1)
        {
            if (spaceFinder == info.length()){
                check = true;
                break;
            }
            temp.set_id(info.substr(0,spaceFinder));
            info = info.substr(spaceFinder + 1);
        }
        if (wordCounter == 2)
        {
            if (spaceFinder == info.length()){
                check = true;
                break;
            }
            temp.set_units(int(info[0]) - 48);
            info = info.substr(spaceFinder + 1);
        }
        if (wordCounter == 3)
        {
            if (spaceFinder == info.length()){
                check = true;
                break;
            }
            temp.set_days(info.substr(0,spaceFinder));
            info = info.substr(spaceFinder + 1);
        }
        if (wordCounter == 4)
        {
            temp.set_time(info.substr(0, spaceFinder));
            if (spaceFinder == info.length())
               a = false;
            else
                info = info.substr(spaceFinder + 1);

        }
        if (wordCounter == 5)
        {
            if (info.find("pre:") != -1)
            {
                while (info[spaceFinder - 1] == '\\') {
                    if (info.find(" ", spaceFinder + 1) != -1)
                        spaceFinder = info.find(" ", spaceFinder + 1);
                    else
                        spaceFinder = info.length();
                }
                temp.set_prerequisite(info.substr(0, spaceFinder));
                while (temp.get_prerequisite().find('\\') != -1)
                    temp.set_prerequisite(temp.get_prerequisite().erase(temp.get_prerequisite().find('\\'),1));
                temp.set_prerequisite(temp.get_prerequisite().erase(0,4));
                if (spaceFinder == info.length())
                    a = false;
                else {
                    info = info.substr(spaceFinder + 1);
                }
            }
        }
        if (wordCounter == 6)
        {
            temp.set_requisite(info.substr(0));
            while (temp.get_requisite().find('\\') != -1)
                temp.set_requisite(temp.get_requisite().erase(temp.get_requisite().find('\\'),1));
            temp.set_requisite(temp.get_requisite().erase(0,3));
            a = false;
        }

        wordCounter++;
    }
    if (temp.get_time() != "") {
        double startEndTime[2];
        string tempTime = temp.get_time();
        for (int i = 0; i < 2; ++i) {
            if (tempTime.find(':') == 1) {
                startEndTime[i] = double(tempTime[0]) - 48;
                startEndTime[i] += ((double(tempTime[2]) - 48) * 10 + (double(tempTime[3]) - 48)) / 60;
                if (i == 0)
                    tempTime = tempTime.substr(5);
            } else {
                startEndTime[i] = (double(tempTime[0]) - 48) * 10 + (double(tempTime[1]) - 48);
                startEndTime[i] += ((double(tempTime[3]) - 48) * 10 + (double(tempTime[4]) - 48)) / 60;
                if (i == 0)
                    tempTime = tempTime.substr(6);
            }
        }
        temp.set_startTime(startEndTime[0]);
        temp.set_endTime(startEndTime[1]);
    }
    if (temp.get_id().length() != 9) //test 12;
        check = true;

    return temp;

}

studentInfo addStudent(string info)
{
    studentInfo temp;
    string tempCourse;
    int spaceFinder;
    bool a = true;

    spaceFinder = info.find(" ");
    temp.set_id(info.substr(0, spaceFinder));
    info = info.substr(spaceFinder + 1);

    while (a)
    {
        spaceFinder = info.find(" ");
        while (info[spaceFinder - 1] == '\\')
            spaceFinder = info.find(" ", spaceFinder + 1);
        tempCourse =info.substr(0, spaceFinder);
        while (tempCourse.find('\\') != -1)
            tempCourse = tempCourse.erase(tempCourse.find('\\'),1);
        temp.set_course(tempCourse);

        info = info.substr(spaceFinder + 1);
        spaceFinder = info.find(" ");

        if (info.length() > 1)
        {
            if (info[1] == '.' || info[1] == ' ')
                temp.set_grade(false);
            else
                temp.set_grade(true);
        }
        else
            temp.set_grade(false);


        if (spaceFinder == -1)
            a = false;
        else
            info = info.substr(spaceFinder + 1);

    }
    return temp;
}

int login( bool& inOrOut, vector<studentInfo> students )
{
    int number;
    string id;
    cout << "Enter student_id:";
    cin >> id;
    cout << endl;
    for (int i = 0; i < students.size(); i++) {
        if (id == students[i].get_id()) {
            number = i;
            inOrOut = true;
            return number;
        }
    }
    cout << "Invalid student_id, try again." << endl;
    return -1;
}

void requisiteLessons(vector<int>& tempNumber,vector<studentInfo>& students, vector<courseInfo>& courses, int& units, bool& checker);

bool checkTimes(vector<int>& tempNumber, vector<courseInfo>& courses, vector<studentInfo>& students ,int studentNumber);

void enroll(vector<studentInfo>& students,vector<courseInfo>& courses, int studentNumber)
{
    vector<int> tempNumber;
    bool check = true;
    int units = students[studentNumber].get_units();
    string course_id , tempId;
    while (course_id.find(';') == -1){
        getline(cin, course_id);
        tempId = course_id;
        if (course_id[4] == ' ' && course_id[8] == ' ' && (course_id[11] == ',' || course_id[11] == ';')){
            tempId.pop_back();
            tempId.erase(8,1);
            tempId.erase(4,1);
            for (int i = 0; i < courses.size(); i++) {
                if (tempId == courses[i].get_id()) {
                    if (courses[i].get_prerequisite() != "") {
                        for (int j = 0; j < students[studentNumber].get_course().size(); ++j) {
                            if (students[studentNumber].get_course()[j] == courses[i].get_prerequisite()) {
                                if (students[studentNumber].get_grade()[j]) {
                                    tempNumber.push_back(i);
                                    units += courses[i].get_units();
                                    break;
                                }
                                else {
                                    cout << "Course " << courses[i].get_name() << " prerequisites are not met." << endl;
                                    check = false;
                                    break;
                                }
                            }
                            if (j == students[studentNumber].get_course().size() - 1 && students[studentNumber].get_course()[j] != courses[i].get_prerequisite()) {
                                cout << "Course " << courses[i].get_name() << " prerequisites are not met." << endl;
                                check = false;
                            }
                        }
                    }
                    else {
                        tempNumber.push_back(i);
                        units += courses[i].get_units();
                    }
                    break;
                }
            }
        }
        else {
            cout << "Invalid argument(s)" << endl;
            check = false;
        }
    }
    requisiteLessons(tempNumber, students, courses, units, check);
    if (units < 12) {
        if (check)
            cout << "Minimum units required is not met." << endl;
    }
    else
    {
        if (check) {
            if (units < 20) {
                if (checkTimes(tempNumber, courses, students, studentNumber)) {
                    students[studentNumber].set_units(units);
                    for (int i = 0; i < tempNumber.size(); ++i) {
                        students[studentNumber].set_selectedLesson(tempNumber[i]);
                    }
                    students[studentNumber].set_checkGetLesson(true);
                }
            }
        }
    }
}

void schedule(studentInfo student, vector<courseInfo> courses) {
    string weekdays[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    vector<courseInfo> lessons;
    bool check;
    for (int i = 0; i < student.get_selectedLesson().size(); ++i)
        lessons.push_back((courses[student.get_selectedLesson()[i]])) ;

    for (int i = 0; i < 7; ++i) {
        check = false;
        for (int j = 0; j < lessons.size(); ++j) {
            if (lessons[j].get_days().find(weekdays[i].substr(0,3)) != -1)
                check = true;
        }
        if(check) {
            cout<<weekdays[i]<<endl;
            for (int j = 0; j < lessons.size();++j) {
                if (lessons[j].get_days().find(weekdays[i].substr(0,3)) != -1) {
                    cout << "\t" << lessons[j].get_time() << endl;
                    cout << "\t\t" << lessons[j].get_name() << endl;
                }
            }
        }
    }
}

int main() {
    string code,firstWord;
    vector<courseInfo> courses;
    vector<studentInfo> students;
    int firstSpace;
    int studentNumber;
    bool inOrOut = false;
    while(getline(cin,code))
    {
        firstSpace = code.find(' ');
        firstWord = code.substr(0,firstSpace);
        if (firstWord == "addCourse")
        {
            bool check = false;
            courses.push_back( addCourse(code.substr(firstSpace + 1), check));
                if (check) {
                    courses.pop_back();
                    cout << "Invalid arguments(s)" << endl;
                }
        }
        else if (firstWord == "addStudent")
        {
            students.push_back(addStudent(code.substr(firstSpace + 1)));

        }
        else if (code == "login")
        {
            studentNumber = login(inOrOut , students);
            cin.ignore();
        }
        else if (code == "logout")
        {
            inOrOut = false;
        }
        else if (code == "enroll")
        {
            if (inOrOut){
                enroll(students, courses, studentNumber);
            }
            else cout << "Authorization failed!"<< endl;
        }
        else if (code == "78")
        {
            if (inOrOut) {
                studentInfo stu = students[studentNumber];
                schedule(stu, courses);
            }
            else cout << "Authorization failed!"<< endl;
        }
        else cout << "Invalid command" << endl;

    }

}

void requisiteLessons(vector<int>& tempNumber,vector<studentInfo>& students, vector<courseInfo>& courses, int& units, bool& checker)
{
    bool check;
    for (int i = 0; i < courses.size(); ++i) {
        check = false;
        for (int j = 0; j < courses.size(); ++j) {
            if (courses[i].get_requisite() == courses[j].get_name()){
                for (int k = 0; k < tempNumber.size(); ++k) {
                    if (courses[i].get_name() == courses[tempNumber[k]].get_name()){
                        for (int l = 0; l < tempNumber.size(); ++l) {
                            if (courses[j].get_name() == courses[tempNumber[l]].get_name()){
                                check = true;
                                break;
                            }
                            if (courses[j].get_name() != courses[tempNumber[l]].get_name() && l == tempNumber.size() - 1){
                                cout << "Course " << courses[i].get_name() << " requisites are not met." << endl;
                                tempNumber.erase(tempNumber.begin()+ k);
                                units -= courses[i].get_units();
                                check = true;
                                checker = false;
                            }
                        }
                    }
                    if (check)
                        break;
                    if (courses[i].get_name() != courses[tempNumber[k]].get_name() &&  k == tempNumber.size() - 1){
                        for (int k = 0; k < tempNumber.size(); ++k){
                            if (courses[j].get_name() == courses[tempNumber[k]].get_name()){
                                cout << "Course " << courses[j].get_name() << " requisites are not met." << endl;
                                tempNumber.erase(tempNumber.begin()+ k);
                                units -= courses[j].get_units();
                                check = true;
                                checker = false;
                            }
                        }
                    }
                }
            }
            if (check)
                break;
        }
    }
}

bool checkTimes(vector<int>& tempNumber, vector<courseInfo>& courses, vector<studentInfo>& students ,int studentNumber)
{
    if (students[studentNumber].get_checkGetLesson()) {
        vector<int> Number(students[studentNumber].get_selectedLesson());

        for (int i = 0; i < Number.size(); ++i) {
            for (int j = i + 1; j < Number.size(); ++j) {
                string firstDay_A = courses[Number[i]].get_days().substr(0,3);
                string secondDay_A;
                if (courses[Number[i]].get_days().find('/') != -1)
                    secondDay_A = courses[Number[i]].get_days().substr(4);
                else
                    secondDay_A = firstDay_A;
                string day_B = courses[Number[j]].get_days().substr(0);
                int startTime_A = courses[Number[i]].get_startTime();
                int endTime_A = courses[Number[i]].get_endTime();
                int startTime_B = courses[Number[j]].get_startTime();
                int endTime_B = courses[Number[j]].get_endTime();
                if (day_B.find(firstDay_A) != -1 || day_B.find(secondDay_A) != -1) {
                    if (startTime_A >= endTime_B)
                        continue;
                    else if (startTime_B >= endTime_A)
                        continue;
                    else
                        return false;
                }
            }
        }
        return true;
    }
    else {
        for (int i = 0; i < tempNumber.size(); ++i) {
            for (int j = i + 1; j < tempNumber.size(); ++j) {
                string firstDay_A = courses[tempNumber[i]].get_days().substr(0,3);
                string secondDay_A;
                if (courses[tempNumber[i]].get_days().find('/') != -1)
                    secondDay_A = courses[tempNumber[i]].get_days().substr(4,3);
                else
                    secondDay_A = firstDay_A;
                string day_B = courses[tempNumber[j]].get_days().substr(0);
                double startTime_A = courses[tempNumber[i]].get_startTime();
                double endTime_A = courses[tempNumber[i]].get_endTime();
                double startTime_B = courses[tempNumber[j]].get_startTime();
                double endTime_B = courses[tempNumber[j]].get_endTime();
                if (day_B.find(firstDay_A) != -1 || day_B.find(secondDay_A) != -1) {
                    if (startTime_A >= endTime_B)
                        continue;
                    else if (startTime_B >= endTime_A)
                        continue;
                    else
                        return false;
                }
            }
        }
        return true;
    }

}