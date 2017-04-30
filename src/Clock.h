#ifndef __CLOCK_H__
#define __CLOCK_H__

class Clock
{
public:
	Clock();
	
	// Call Update once per frame;
	void Update();
	float dT();

private:
	double m_CurrentTime;
	double m_LastTime;

};

#endif