#include "Car.h"

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

istream & operator>>(istream & input, Car & car)
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

