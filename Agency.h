#ifndef AGENCY_H
#define AGENCY_H

#include "Car.h"

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
		void ReadAllData(istream & inputfile);
		void PrintAllData(ostream & output);
		void PrintAvailableCars(ostream & output);
		friend istream & operator>>(istream & input, Agency & agency);
};

#endif
