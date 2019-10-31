#include "Sensor.h"

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

