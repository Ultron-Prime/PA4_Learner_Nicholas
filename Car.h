#ifndef CAR_H
#define CAR_H

#include "Sensor.h"

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

#endif
