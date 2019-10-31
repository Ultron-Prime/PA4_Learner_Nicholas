#include "Agency.h"

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

istream & operator>>(istream & input, Agency & agency)
{
	for (unsigned int i = 0; i < NUM_OF_CARS; i++)
	{
		input >> agency[i];
	}
	
	return input;
}

void Agency::ReadAllData(istream & inputfile)
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

void Agency::PrintAvailableCars(ostream & output)
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

