#ifndef SENSOR_H
#define SENSOR_H

#include "proj4.h"

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

#endif
