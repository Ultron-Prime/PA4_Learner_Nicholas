/* -----------------------------------------------------------------------------

FILE:           proj4.cpp
DESCRIPTION:    Project 4 for Fall 2019 CS 202-1001 at UNR; Assists users
					in renting a car with various 
COMPILER:       MinGW C++ compiler
NOTES:          

MODIFICATION HISTORY:
Author				Date			Version
---------------		----------		--------------
Version 1			YYYY-MM-DD		x.x Description
Nick Learner		2019-09-29		1.0	Created program
Nick Learner		2019-09-30		1.1	Added myString funcs
Nick Learner		2019-09-30		1.2	Moved files in because of IDE problems
----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>

using namespace std;

const int MAX_CHAR_ARRAY_SIZE =	256;
const int NUM_OF_SENSORS = 3;
const int NUM_OF_CARS = 5;

void Error();

// proj4.h
// Required functions that deal with char arrays
size_t myStringLength(const char * str);
int myStringCompare(const char * str1, const char * str2);
char * myStringCopy(char * destination, const char * source);
char * myStringCat(char * destination, const char * source);


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
		return 5.0;
	case 2:
		camera_cnt++;
		return 10.0;
	case 3:
		lidar_cnt++;
		return 15.0;
	case 4:
		radar_cnt++;
		return 20.0;
	default:
		return 0.0;
	}
}

float Sensor::GetSensorCost()
{
	return m_extracost;
}

char * Sensor::GetType() { return m_type; }

void Sensor::SetType(char * type) { myStringCopy(m_type, type); }

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
	if (*type = 'g')
	{
		return 1;
	}else if (*type = 'c')
	{
		return 2;
	}else if (*type = 'l')
	{
		return 3;
	}else if (*type = 'r')
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
		fstream & operator>>(fstream & input);
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
	output << car.GetMake() << ' ' 
		<< car.GetModel() << ' '
		<< car.GetYear() << ", base price: "
		<< car.GetBasePrice() << ", final price: "
		<< car.GetFinalPrice() << ' '
		<< car.GetAvailable() << ' ' << boolalpha
		<< car.GetAvailable() << ' '
		<< car.GetOwner() << endl;
	
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

fstream & Car::operator>>(fstream & input)
{
	// Input for first four variables
	input >> this->m_year >> this->m_make >> this->m_model >> this->m_baseprice;
	
	// Input for sensor(s)
	Sensor * sensorptr = this->m_sensors;
	
	char c;
	char tempsensorname[MAX_CHAR_ARRAY_SIZE];
	char * tempsensornameptr = tempsensorname;// Only useful for 
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
		
		if (c == '}')
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
	}
	
	// Input availability
	input >> this->m_available;
	
	// Input owner, if car is not available
	if (this->m_available)
	{
		input >> this->m_owner;
	}
	
	this->UpdatePrice();
	
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
		const int GetZipcode();
		const Car & operator[](unsigned int index);
		Agency & ReadAllData();
		void PrintAllData(fstream & output);
		void PrintAvailableCars(fstream & output);
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

const int Agency::GetZipcode() { return m_zipcode; }

const Car & operator[](unsigned int index) { return m_inventory[index]; }

fstream & operator>>(fstream & input, Agency & agency, int & zipcode)
{
	char tempname[MAX_CHAR_ARRAY_SIZE];
	
	input >> agency.m_name >> zipcode;
	
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		input >> agency[i];
	}
	
	return input;
}

Agency & Agency::ReadAllData()
{
	fstream inputfile;
	char filename[MAX_CHAR_ARRAY_SIZE];
	int zipcode;
	
	cout << "Input filename: ";
	cin >> filename;
	
	inputfile.open(filename);
	
	if (inputfile)
	{
		inputfile >> *this >> zipcode;// Uses an overloaded operator
		
		Agency agency(this->m_name, zipcode, this->m_inventory);
		return agency;
	}else Error();
}


/*
#include "proj4.h"
#include "Sensor.h"
#include "Car.h"
#include "Agency.h"
*/
int main()
{
	cout << "Nothing to see here..." << endl;
	
	return 0;
}


/* -----------------------------------------------------------------------------
FUNCTION:          myStringLength()
DESCRIPTION:       Finds and returns the length of a given string
RETURNS:           pointer to a char
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
