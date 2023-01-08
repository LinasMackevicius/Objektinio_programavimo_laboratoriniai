
#pragma warning(disable : 4996)

#include <iostream>
#include<cmath>
#include<ctime>

using namespace std;

class Time 
{
public:
    time_t t = time(NULL);
    tm* tPtr = localtime(&t);


    int currentYear = (tPtr->tm_year) + 1900;
    int currentMonth = (tPtr->tm_mon) + 1;
    int currentDay = (tPtr->tm_mday);
};


class Person : public Time
{
private:
    string name;
    string surname;

    int yearOfBirth;
    int monthOfBirth;
    int dayOfBirth;

public:

    Person(string nameThis, string surnameThis, int yearOfBirthThis, int monthOfBirthThis, int dayOfBirthThis)
    {
        // Check if the name or surname is an empty string or a string containing only whitespace
        if (nameThis.empty() || surnameThis.empty() || nameThis.find_first_not_of(' ') == string::npos || surnameThis.find_first_not_of(' ') == string::npos)
        {
            throw invalid_argument("Invalid name or surname");
        }

        // Check if the birth date is invalid
        if (yearOfBirthThis < 0 || monthOfBirthThis < 1 || monthOfBirthThis > 12 || dayOfBirthThis < 1 || dayOfBirthThis > 31)
        {
            throw invalid_argument("Invalid birth date");
        }

        // Check if the birth date is after the current date
        if ((yearOfBirthThis > currentYear) || (yearOfBirthThis == currentYear && monthOfBirthThis > currentMonth) || (yearOfBirthThis == currentYear && monthOfBirthThis == currentMonth && dayOfBirthThis > currentDay))
        {
            throw invalid_argument("Birth date cannot be after the current date");
        }
        
        surname = surnameThis;
        yearOfBirth = yearOfBirthThis;
        monthOfBirth = monthOfBirthThis;
        dayOfBirth = dayOfBirthThis;
    }

    int getPersonsAge()
    {
        return currentYear - yearOfBirth;
    }
 
    int getNumberOfdaysUntilBirthday()
    {
        tm currentDate = { 0 };
        currentDate.tm_year = currentYear - 1900;
        currentDate.tm_mon = currentMonth - 1;
        currentDate.tm_mday = currentDay;

        tm nextBirthday = { 0 };
        nextBirthday.tm_year = currentYear - 1900;
        nextBirthday.tm_mon = monthOfBirth - 1;
        nextBirthday.tm_mday = dayOfBirth;

        // If the current date is after the person's birthday, set the year for the next birthday to the following year
        if (mktime(&currentDate) > mktime(&nextBirthday))
        {
            nextBirthday.tm_year += 1;
        }

        time_t currentTime = mktime(&currentDate);
        time_t nextBirthdayTime = mktime(&nextBirthday);

        int diffInSeconds = difftime(nextBirthdayTime, currentTime);
        //number of seconds in the day;
        int diffInDays = diffInSeconds / 86400;

        return diffInDays;
    }

    void printInfo()
    {
        std::cout << "Name: " << name << '\n';
        std::cout << "Surname: " << surname << '\n';
        std::cout << "Year of birth: " << yearOfBirth << '\n';
        std::cout << "Month of birth: " << monthOfBirth << '\n';
        std::cout << "Day of birth: " << dayOfBirth << '\n';
        std::cout << "Age: " << getPersonsAge() << '\n';
        std::cout << "Days until next birthday: " << getNumberOfdaysUntilBirthday() << '\n';
    }
};


int main()
{
    Person mySelf("Linas", "as asd", 2001, 12, 30);
    std::cout << mySelf.getPersonsAge() << '\n';

    mySelf.printInfo();

    std::cout <<'\n'<< '\n';
    std::cout << "---------------------------------" << '\n';
    std::cout << '\n' << '\n';

}