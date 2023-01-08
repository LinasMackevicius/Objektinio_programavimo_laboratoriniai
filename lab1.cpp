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
        name = nameThis;
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
    Person mySelf("Linas", "Mackevicius", 2001, 12, 30);
    std::cout << mySelf.getPersonsAge() << '\n';

    mySelf.printInfo();

    std::cout <<'\n'<< '\n';
    std::cout << "---------------------------------" << '\n';
    std::cout << '\n' << '\n';

}