#ifndef GYRO_SAMPLE_H
#define GYRO_SAMPLE_H

#include "sample.h"

class GyroSample : public Sample
{
public:
	GyroSample(float r, float p, float y);
	GyroSample(const std::string& line);
	~GyroSample() {}
	inline float roll() const { return roll_; }
	inline float pitch() const { return pitch_; }
	inline float yaw() const { return yaw_; }
	
	virtual void save(std::ofstream& out);

private:
	float roll_;
	float pitch_;
	float yaw_;
};

#endif
