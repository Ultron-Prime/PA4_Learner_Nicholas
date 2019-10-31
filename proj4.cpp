/* -----------------------------------------------------------------------------

FILE:           proj4.cpp
DESCRIPTION:    Project 4 for Fall 2019 CS 202-1001 at UNR; Assists users
					in renting a car with various sensors
COMPILER:       MinGW C++ compiler
NOTES:          

MODIFICATION HISTORY:
Author				Date			Version
---------------		----------		--------------
Version 1			YYYY-MM-DD		x.x Description
Nick Learner		2019-09-29		1.0	Created program
Nick Learner		2019-09-30		1.1	Added myString funcs
Nick Learner		2019-09-30		1.2	Moved files in because of IDE problems
Nick Learner		2019-10-01		1.3	Finished declaring/implementing classes
Nick Learner		2019-10-01		1.4	Added UserMenu() and related funcs
----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>

using namespace std;

#include "proj4.h"
#include "Sensor.h"
#include "Car.h"
#include "Agency.h"


// Function prototypes
void UserMenu();
void DisplayUserMenu();
void FirstMenuOption(char *, int &, fstream &);
void SecondMenuOption(Agency &);
void ThirdMenuOption(Agency *);
void FourthMenuOption(Agency *);
Car * ShowMostExpensiveCar(Agency *);

int main()
{
	UserMenu();
	
	return 0;
}


/* -----------------------------------------------------------------------------
FUNCTION:          UserMenu()
DESCRIPTION:       Displays a menu the user picks an option from
RETURNS:           void
NOTES:             Based on Nick Learner's UserMenu() function in proj3.cpp
------------------------------------------------------------------------------- */

void UserMenu()
{
	bool continuemenu;
	int choice;
	
	char agencyname[MAX_CHAR_ARRAY_SIZE];
	int agencyzipcode = -1;
	Car defaultcararray[NUM_OF_CARS];
	
	DisplayUserMenu();
	
	cin >> choice;
	
	if (choice == 5)
	{
		cout << endl;
		cout << "Thank you for using Let's Rent a Car, Version 3" << "\n\n";
	}else
	{
		while (choice != 1)
		{
			cout << "\n\n";
			cout << "Data has not yet been read. Please choose option 1." << "\n\n";
			
			DisplayUserMenu();
			
			cin >> choice;
		}
		
		fstream inputfile;
		FirstMenuOption(agencyname, agencyzipcode, inputfile);
		
		Agency agency(agencyname, agencyzipcode, defaultcararray);
		
		agency.ReadAllData(inputfile);
		
		do
		{
			continuemenu = true;
			
			DisplayUserMenu();
			
			cin >> choice;
			
			switch (choice)
			{
			case 1:
				cout << "Option 1 is no longer available. Please choose another option or"
					<< " quit the program and restart it." << "\n\n";
				break;
			case 2:
				SecondMenuOption(agency);
				break;
			case 3:
				ThirdMenuOption(&agency);
				break;
			case 4:
				FourthMenuOption(&agency);
				break;
			case 5:
				cout << endl;
				cout << "Thank you for using Let's Rent a Car, Version 3" << "\n\n";
				continuemenu = false;
				break;
			default:
				cout << endl;
				Error();
				break;
			}
		}
		while (continuemenu);
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          DisplayUserMenu()
DESCRIPTION:       Displays a menu the user picks an option from
RETURNS:           void
NOTES:             Based on Nick Learner's almost identical function in proj3.cpp
------------------------------------------------------------------------------- */

void DisplayUserMenu()
{
	// Menu prompt as per Proj4 instructions
	cout << "Let's Rent a Car, Version 3" << endl;
	cout << "1) Input the name of the rental agency and rental car datafile" << endl;
	cout << "2) Print all rental agency and rental car data to console" << endl;
	cout << "3) Show total number of sensors in the rental agency's cars" << endl;
	cout << "4) Show most expensive rental car and its price per day" << endl;
	cout << "5) Quit program" << endl;
	
	cout << "Enter your choice [ 1 2 3 4 5 ]: ";
}


/* -----------------------------------------------------------------------------
FUNCTION:          FirstMenuOption()
DESCRIPTION:       Inputs agency data from a file
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void FirstMenuOption(char * tempagencyname, int & tempagencyzipcode, fstream & inputfile)
{
	char filename[MAX_CHAR_ARRAY_SIZE];
	
	cout << endl << "Input filename: ";
	cin >> filename;
	
	inputfile.open(filename);
	
	if (inputfile)
	{
		inputfile >> tempagencyname >> tempagencyzipcode;
		
		cout << endl << "Agency info has been inputted." << endl;
	}else Error();
	
	cout << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          SecondMenuOption()
DESCRIPTION:       Prints agency data to the console
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void SecondMenuOption(Agency & agency)
{
	cout << endl;
	agency.PrintAllData(cout);
	cout << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          ThirdMenuOption()
DESCRIPTION:       Prints total number of eac sensor type
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void ThirdMenuOption(Agency * agency)
{
	unsigned int number = 0;
	
	cout << endl;
	
	Sensor * sensorptr = agency->GetFirstCar()->GetSensors();
	
	cout << "Num of GPSs:     " << sensorptr->GetGPSCount()    << endl
		 << "Nums of Cameras: " << sensorptr->GetCameraCount() << endl
		 << "Num of Lidars:   " << sensorptr->GetLidarCount()  << endl
		 << "Num of Radars:   " << sensorptr->GetRadarCount() << "\n\n";
}


/* -----------------------------------------------------------------------------
FUNCTION:          FourthMenuOption()
DESCRIPTION:       Prints the most expensive car and asks user to rent it
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void FourthMenuOption(Agency * agency)
{
	char choice, owner[MAX_CHAR_ARRAY_SIZE];
	Car * car = ShowMostExpensiveCar(agency);
	
	cout << endl << "Most expensive car:" << endl;
	car->PrintData();
	cout << endl << "Would you like to rent the car? [ Y N ]: ";
	cin >> choice;
	
	switch (choice)
	{
	case 'Y':
	case 'y':
		cout << "Please enter your name:";
		cin >> owner;
		
		car->SetOwner(owner);
		car->SetAvailable(false);
		
		cout << "You have successfully rented the " << car->GetYear()
			<< ' ' << car->GetMake() << ' ' << car->GetModel()
			<< " for " << car->GetFinalPrice() << " per day." << "\n\n";
		break;
	case 'N':
	case 'n':
		cout << "If you say so. It's a pretty great car..." << "\n\n";
		break;
	default:
		Error();
		break;
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          ShowMostExpensiveCar()
DESCRIPTION:       Self explanatory
RETURNS:           void
NOTES:             Based on function with same name in Nick Learner's proj3.cpp
------------------------------------------------------------------------------- */

Car * ShowMostExpensiveCar(Agency * agency)
{
	Car * car = agency->GetFirstCar();
	Car * mostexpensivecar = car;
	
	for (int i = 0; i < NUM_OF_CARS; i++, car++)
	{
		if ((car->GetFinalPrice() > mostexpensivecar->GetFinalPrice()) && car->GetAvailable())
		{
			mostexpensivecar = car;
		}
	}
	
	return mostexpensivecar;
}


/* -----------------------------------------------------------------------------
FUNCTION:          myStringLength()
DESCRIPTION:       Finds and returns the length of a given string
RETURNS:           size_t (like an int)
NOTES:             
------------------------------------------------------------------------------- */

size_t myStringLength(const char * str)
{
	size_t i = 0;
	
	while (*str++)
	{
		i++;
	}
	
	return i;
}


/* -----------------------------------------------------------------------------
FUNCTION:          myStringCompare()
DESCRIPTION:       Compares two char arrays 
RETURNS:           int
NOTES:             return value is less than 0 if str1 is less than str2,
					greater than 0 if str1 is greater than str2, 0 if they're ==
------------------------------------------------------------------------------- */

int myStringCompare(const char * str1, const char * str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	
	return *str1 - *str2;
}


/* -----------------------------------------------------------------------------
FUNCTION:          myStringCopy()
DESCRIPTION:       Copies a char array to a destination
RETURNS:           pointer to a char
NOTES:             
------------------------------------------------------------------------------- */

char* myStringCopy(char * destination, const char * source)
{
	while ((*destination++ = *source++));
	
	return destination;
}


/* -----------------------------------------------------------------------------
FUNCTION:          myStringCat()
DESCRIPTION:       Adds (concatenates) a char array to a destination
RETURNS:           pointer to a char
NOTES:             
------------------------------------------------------------------------------- */

char* myStringCat(char * destination, const char * source)
{
	while (*destination)// Goes until '\0', then stops there
	{
		destination++;
	}
	
	// Same basic function as myStringCopy()
	while ((*destination++ = *source++));
	
	return destination;
}


/* -----------------------------------------------------------------------------
FUNCTION:          Error()
DESCRIPTION:       Gives error message
RETURNS:           void
NOTES:             Used in proj2.cpp of PA2_Learner_Nicholas
------------------------------------------------------------------------------- */

void Error()
{
	cout << "Incorrect input! Please enter a correct input." << "\n\n";
}
