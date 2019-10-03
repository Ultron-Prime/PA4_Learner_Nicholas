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

const int MAX_CHAR_ARRAY_SIZE =	256;
const int NUM_OF_SENSORS = 3;
const int NUM_OF_CARS = 5;

// proj4.h
// Required functions that deal with char arrays
size_t myStringLength(const char * str);
int myStringCompare(const char * str1, const char * str2);
char * myStringCopy(char * destination, const char * source);
char * myStringCat(char * destination, const char * source);

// Added error function
void Error();


// Sensor.h
class Sensor
{
	private:
		char m_type[MAX_CHAR_ARRAY_SIZE];
		float m_extracost;
		static int gps_cnt;
		static int camera_cnt;
		static int lidar_cnt;
		static int radar_cnt;
	public:
		Sensor();
		Sensor(char * type);
		Sensor(const Sensor&);
		char * GetType();
		void SetType(char * type);
		float GetSetSensorCost();
		float GetSensorCost();
		int GetGPSCount();
		int GetCameraCount();
		int GetLidarCount();
		int GetRadarCount();
		void ResetGPSCount();
		void ResetCameraCount();
		void ResetLidarCount();
		void ResetRadarCount();
		void ResetAll();
		friend bool operator==(const Sensor& lhs, const Sensor& rhs);
};

// Sensor.cpp
int CheckType(char * type);

Sensor::Sensor()
{
	char type[MAX_CHAR_ARRAY_SIZE] = "TYPE";
	char * typeptr = type;
	char * m_typeptr = m_type;
	while (*typeptr != '\0')
	{
		*m_typeptr++ = *typeptr++;
	}*m_typeptr = '\0';
	m_extracost = GetSetSensorCost();
}

Sensor::Sensor(char * type)
{
	myStringCopy(m_type, type);
	m_extracost = GetSetSensorCost();
}

Sensor::Sensor(const Sensor& rhs)
{
	myStringCopy(m_type, rhs.m_type);
	m_extracost = GetSetSensorCost();
}

// static int member variable declarations
int Sensor::gps_cnt = 0;
int Sensor::camera_cnt = 0;
int Sensor::lidar_cnt = 0;
int Sensor::radar_cnt = 0;

float Sensor::GetSetSensorCost()
{
	int type = CheckType(m_type);
	
	switch (type)
	{
	case 1:
		gps_cnt++;
		m_extracost = 5.0;
		return 5.0;
	case 2:
		camera_cnt++;
		m_extracost = 10.0;
		return 10.0;
	case 3:
		lidar_cnt++;
		m_extracost = 15.0;
		return 15.0;
	case 4:
		radar_cnt++;
		m_extracost = 20.0;
		return 20.0;
	default:
		m_extracost = 0.0;
		return 0.0;
	}
}

float Sensor::GetSensorCost()
{
	return m_extracost;
}

char * Sensor::GetType() { return m_type; }

void Sensor::SetType(char * type)
{
	myStringCopy(m_type, type);
	GetSetSensorCost();
}

int Sensor::GetGPSCount() { return gps_cnt; }

int Sensor::GetCameraCount() { return camera_cnt; }

int Sensor::GetLidarCount() { return lidar_cnt; }

int Sensor::GetRadarCount() { return radar_cnt; }


void Sensor::ResetGPSCount() { gps_cnt = 0; }

void Sensor::ResetCameraCount() { camera_cnt = 0; }

void Sensor::ResetLidarCount() { lidar_cnt = 0; }

void Sensor::ResetRadarCount() { radar_cnt = 0; }

void Sensor::ResetAll()
{
	ResetGPSCount();
	ResetCameraCount();
	ResetLidarCount();
	ResetRadarCount();
}

bool operator==(const Sensor& lhs, const Sensor& rhs)
{
	return !myStringCompare(lhs.m_type, rhs.m_type);
}


/* -----------------------------------------------------------------------------
FUNCTION:          CheckType()
DESCRIPTION:       Checks the sensor type, and returns a switch statement value
RETURNS:           int
NOTES:             
------------------------------------------------------------------------------- */

int CheckType(char * type)
{
	if (*type == 'g')
	{
		return 1;
	}else if (*type == 'c')
	{
		return 2;
	}else if (*type == 'l')
	{
		return 3;
	}else if (*type == 'r')
	{
		return 4;
	}else return 0;
}

// Car.h
class Car
{
	private:
		char m_make[MAX_CHAR_ARRAY_SIZE];
		char m_model[MAX_CHAR_ARRAY_SIZE];
		int m_year;
		Sensor m_sensors[NUM_OF_SENSORS];
		float m_baseprice;
		float m_finalprice;
		bool m_available;
		char m_owner[MAX_CHAR_ARRAY_SIZE];
	public:
		Car();
		Car(char * make, char * model, int year, Sensor * sensors,
			float baseprice, bool available, char * owner);
		Car(Car &);
		char * GetMake();
		char * GetModel();
		int GetYear();
		Sensor * GetSensors();
		float GetBasePrice();
		float GetFinalPrice();
		bool GetAvailable();
		char * GetOwner();
		void SetMake(char * make);
		void SetModel(char * model);
		void SetYear(int year);
		void SetBasePrice(float baseprice);
		void SetAvailable(bool available);
		void SetOwner(char * owner);
		void UpdatePrice();
		void PrintData();
		float EstimateCost(int days);
		const Car & operator+(Sensor & sensor);
		const Car & operator+(char * owner);
		friend istream & operator>>(istream & input, Car & car);
};


// Car.cpp
Car::Car()
{
	char none[MAX_CHAR_ARRAY_SIZE] = "NONE";
	char * noneptr = none;
	char * m_makeptr = m_make;
	char * m_modelptr = m_model;
	char * m_ownerptr = m_owner;
	while (*noneptr != '\0')
	{
		*m_makeptr++ = *m_modelptr++ = *m_ownerptr++ = *noneptr++;
	}*m_makeptr = *m_modelptr = *m_ownerptr = '\0';
	m_year = 0;
	m_baseprice = 0.0;
	m_finalprice = 0.0;
	m_available = false;
	
	Sensor * sensorptr = m_sensors;
	
	for (int i = 0; i < NUM_OF_SENSORS; i++, sensorptr++)
	{
		*sensorptr = Sensor(noneptr);
	}
}

Car::Car(char * make, char * model, int year, Sensor * sensors,
			float baseprice, bool available=0, char * owner=(char*)"NONE")
{
	myStringCopy(m_make, make);
	myStringCopy(m_model, model);
	m_year = year;
	m_baseprice = baseprice;
	m_available = available;
	myStringCopy(m_owner, owner);
	
	Sensor * m_sensorptr = m_sensors;
	
	for (int i = 0; i < NUM_OF_SENSORS; i++)
	{
		*m_sensorptr++ = Sensor(*sensors++);
	}

	UpdatePrice();
}

Car::Car(Car& car)
{
	myStringCopy(m_make, car.GetMake());
	myStringCopy(m_model, car.GetModel());
	m_year = car.GetYear();
	m_baseprice = car.GetBasePrice();
	m_available = car.GetAvailable();
	myStringCopy(m_owner, car.GetOwner());
	
	Sensor * sensorsource = car.GetSensors();
	Sensor * sensordest = m_sensors;
	
	for (int i = 0; i < NUM_OF_SENSORS; i++)
	{
		*sensordest++ = Sensor(*sensorsource++);
	}
	
	UpdatePrice();
}

char * Car::GetMake() { return m_make; }
char * Car::GetModel() { return m_model; }
int Car::GetYear() { return m_year; }
Sensor * Car::GetSensors() { return m_sensors; }
float Car::GetBasePrice() { return m_baseprice; }
float Car::GetFinalPrice() { return m_finalprice; }
bool Car::GetAvailable() { return m_available; }
char * Car::GetOwner() { return m_owner; }

void Car::SetMake(char * make) { myStringCopy(m_make, make); }
void Car::SetModel(char * model) { myStringCopy(m_model, model); }
void Car::SetYear(int year) { m_year = year; }
void Car::SetBasePrice(float baseprice) { m_baseprice = baseprice; }
void Car::SetAvailable(bool available) { m_available = available; }
void Car::SetOwner(char * owner) { myStringCopy(m_owner, owner); }

void Car::UpdatePrice()
{
	float tempprice = m_baseprice;
	Sensor * m_sensorsptr = m_sensors;
	
	for (int i = 0; i < NUM_OF_SENSORS; i++, m_sensorsptr++)
	{
		tempprice += m_sensorsptr->GetSensorCost();
	}
	
	m_finalprice = tempprice;
}


/* -----------------------------------------------------------------------------
FUNCTION:          operater<<()
DESCRIPTION:       Outputs data; Used for Car::PrintData()
RETURNS:           ostream &
NOTES:             
------------------------------------------------------------------------------- */

ostream & operator<<(ostream & output, Car & car)
{
	output << car.GetYear() << ' '
		<< car.GetMake() << ' '
		<< car.GetModel() << ", base price: $"
		<< car.GetBasePrice() << ", final price: $"
		<< car.GetFinalPrice() << ", available: " << boolalpha
		<< car.GetAvailable() << ", owner: "
		<< car.GetOwner();
	
	return output;
}

void Car::PrintData()
{
	cout << *this << endl;
}

float Car::EstimateCost(int days)
{
	return (m_finalprice * days);
}

const Car & Car::operator+(Sensor & sensor)
{
	Sensor * sensorptr = this->GetSensors();
	
	for (int i = 0; i < NUM_OF_SENSORS; i++, sensorptr++)
	{
		if (!myStringCompare(sensorptr->GetType(), "NONE"))
		{
			sensorptr->SetType(sensor.GetType());
			UpdatePrice();
			break;
		}else;
	}
	
	return *this;
}

const Car & Car::operator+(char * owner)
{
	SetOwner(owner);
	SetAvailable(false);
	return *this;
}

fstream & operator>>(fstream & input, Car & car)
{
	int year;
	char make[MAX_CHAR_ARRAY_SIZE], model[MAX_CHAR_ARRAY_SIZE];
	float baseprice;
	
	// Input for first four variables
	input >> year >> make >> model >> baseprice;
	
	car.SetYear(year);
	car.SetMake(make);
	car.SetModel(model);
	car.SetBasePrice(baseprice);
	
	char astring[MAX_CHAR_ARRAY_SIZE];
	char * astringptr;
	Sensor * sensorptr = car.GetSensors();
	int restofstrlen;
	
	do
	{
		input >> astring;
		astringptr = astring;
		
		if (*astringptr == '{')
		{
			astringptr++;
		}else;
		if (*astringptr == 'g')
		{
			sensorptr->SetType((char *)"gps");
			sensorptr++;
			restofstrlen = 3;
		}else if (*astringptr == 'c')
		{
			sensorptr->SetType((char *)"camera");
			sensorptr++;
			restofstrlen = 6;
		}else if (*astringptr == 'l')
		{
			sensorptr->SetType((char *)"lidar");
			sensorptr++;
			restofstrlen = 5;
		}else if (*astringptr == 'r')
		{
			sensorptr->SetType((char *)"radar");
			sensorptr++;
			restofstrlen = 5;
		}else if (*astringptr == '}')
		{
			restofstrlen = 0;
		}else;
	}
	while (*(astringptr + restofstrlen) != '}');
	
	/*
	
	// Input for sensor(s)
	Sensor * sensorptr = car.GetSensors();
	
	char c;
	
	// Only useful for consuming characters from the file
	char tempsensorname[MAX_CHAR_ARRAY_SIZE];
	char * tempsensornameptr = tempsensorname;
	
	// Probably unnecessary, but it gets the job done
	char gps[MAX_CHAR_ARRAY_SIZE] = "gps";
	char * gpsptr = gps;
	char camera[MAX_CHAR_ARRAY_SIZE] = "camera";
	char * cameraptr = camera;
	char lidar[MAX_CHAR_ARRAY_SIZE] = "lidar";
	char * lidarptr = lidar;
	char radar[MAX_CHAR_ARRAY_SIZE] = "radar";
	char * radarptr = radar;
	
	input.get(c);// ' '
	input.get(c);// '{'
	
	for (int i = 0; i < NUM_OF_SENSORS; i++, sensorptr++)
	{
		input.get(c);
		
		if (c == '}' || c == ' ')
		{
			break;// Should break out of for()
		}else if (c == 'g' || c == 'G')
		{
			*tempsensornameptr++ = 'g';
			input.get(*tempsensornameptr++);// 'p'
			input.get(*tempsensornameptr++);// 's'
			input.get(*tempsensornameptr++);// ' ' or '}'
			*tempsensornameptr = '\0';
			sensorptr->SetType(gpsptr);
		}else if (c == 'c' || c == 'C')
		{
			*tempsensornameptr++ = 'c';
			input.get(*tempsensornameptr++);// 'a'
			input.get(*tempsensornameptr++);// 'm'
			input.get(*tempsensornameptr++);// 'e'
			input.get(*tempsensornameptr++);// 'r'
			input.get(*tempsensornameptr++);// 'a'
			input.get(*tempsensornameptr++);// ' ' or '}'
			*tempsensornameptr = '\0';
			sensorptr->SetType(cameraptr);
		}else if (c == 'l' || c == 'L')
		{
			*tempsensornameptr++ = 'l';
			input.get(*tempsensornameptr++);// 'i'
			input.get(*tempsensornameptr++);// 'd'
			input.get(*tempsensornameptr++);// 'a'
			input.get(*tempsensornameptr++);// 'r'
			input.get(*tempsensornameptr++);// ' ' or '}'
			*tempsensornameptr = '\0';
			sensorptr->SetType(lidarptr);
		}else if (c == 'r' || c == 'R')
		{
			*tempsensornameptr++ = 'r';
			input.get(*tempsensornameptr++);// 'a'
			input.get(*tempsensornameptr++);// 'd'
			input.get(*tempsensornameptr++);// 'a'
			input.get(*tempsensornameptr++);// 'r'
			input.get(*tempsensornameptr++);// ' ' or '}'
			*tempsensornameptr = '\0';// Not super useful
			sensorptr->SetType(radarptr);
		}else;
		
		car = car + *sensorptr;
	}
	
	*/
	
	bool available;
	char noowner[MAX_CHAR_ARRAY_SIZE] = "NO OWNER";
	char * noownerptr = noowner;
	char owner[MAX_CHAR_ARRAY_SIZE];
	
	// Input availability
	input >> available;
	
	car.SetAvailable(available);
	
	// Input owner, if car is not available
	if (!available)
	{
		input >> owner;
		car.SetOwner(owner);
	}else
		car.SetOwner(noownerptr);
	
	car.UpdatePrice();
	
	return input;
}


// Agency.h
class Agency
{
	private:
		char m_name[MAX_CHAR_ARRAY_SIZE];
		const int m_zipcode;
		Car m_inventory[NUM_OF_CARS];
	public:
		Agency();
		Agency(char * name, int zipcode, Car * car);
		void SetName(char * name);
		char * GetName();
		int GetZipcode();
		Car * GetFirstCar();
		Car & operator[](unsigned int index);
		void ReadAllData(fstream & inputfile);
		void PrintAllData(ostream & output);
		void PrintAvailableCars(fstream & output);
		friend fstream & operator>>(fstream & input, Agency & agency);
};


// Agency.cpp
Agency::Agency() : m_zipcode(00000)
{
	char none[MAX_CHAR_ARRAY_SIZE] = "NONE";
	char * noneptr = none;
	SetName(noneptr);
	
	Car * carptr = m_inventory;
	
	for (int i = 0; i < NUM_OF_CARS; i++, carptr++)
	{
		carptr->SetMake(noneptr);
		carptr->SetModel(noneptr);
		carptr->SetYear(0);
		carptr->SetOwner(noneptr);
		carptr->SetBasePrice(0.0);
		carptr->SetAvailable(false);
		
		Sensor * sensorptr = carptr->GetSensors();
	
		for (int i = 0; i < NUM_OF_SENSORS; i++, sensorptr++)
		{
			*sensorptr = Sensor(noneptr);
		}
	}
}

Agency::Agency(char * name, int zipcode, Car * car) : m_zipcode(zipcode)
{
	SetName(name);
	
	Car * carptr = m_inventory;
	
	for (int i = 0; i < NUM_OF_CARS; i++, car++, carptr++)
	{
		carptr->SetMake(car->GetMake());
		carptr->SetModel(car->GetModel());
		carptr->SetYear(car->GetYear());
		carptr->SetOwner(car->GetOwner());
		carptr->SetBasePrice(car->GetBasePrice());
		carptr->SetAvailable(car->GetAvailable());
		
		Sensor * sensorptr = carptr->GetSensors();
		Sensor * copiedsensorptr = car->GetSensors();
		
		for (int i = 0; i < NUM_OF_SENSORS; i++, sensorptr++, copiedsensorptr++)
		{
			*sensorptr = *copiedsensorptr;
		}
	}
}

void Agency::SetName(char * name) { myStringCopy(m_name, name); }

char * Agency::GetName() { return m_name; }

int Agency::GetZipcode() { return m_zipcode; }

Car * Agency::GetFirstCar() { return m_inventory; }

Car & Agency::operator[](unsigned int index) { return m_inventory[index]; }

fstream & operator>>(fstream & input, Agency & agency)
{
	for (unsigned int i = 0; i < NUM_OF_CARS; i++)
	{
		input >> agency[i];
	}
	
	return input;
}

void Agency::ReadAllData(fstream & inputfile)
{
	inputfile >> *this;// Uses an overloaded operator
}

void Agency::PrintAllData(ostream & output)
{
	output << this->m_name << ' '
		<< this->m_zipcode << endl;
	
	Car * carptr = this->m_inventory;
	
	for (int i = 0; i < NUM_OF_CARS; i++, carptr++)
	{
		carptr->PrintData();
	}
	
	cout << endl;
}

void Agency::PrintAvailableCars(fstream & output)
{
	output << this->m_name << ' '
		<< this->m_zipcode << endl;
	
	Car * carptr = this->m_inventory;
	
	for (int i = 0; i < NUM_OF_CARS; i++, carptr++)
	{
		if (carptr->GetAvailable())
		{
			carptr->PrintData();
		}
	}
}


/*
#include "proj4.h"
#include "Sensor.h"
#include "Car.h"
#include "Agency.h"
*/

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
