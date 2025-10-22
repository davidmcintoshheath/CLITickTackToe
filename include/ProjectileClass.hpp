#ifndef PROJECTILECLASS
#define PROJECTILECLASS

#include <vector>

class Projectile{
public:
	//Constructors and destructors
	Projectile();
	~Projectile();
	
	//get and set functions
	double getBodyMass();
	int setBodyMass(const double &inputBodyMass);
	
	double getBodyLength();
	int setBodyLength(const double &inputBodyLength);
	
	double getWallThickness();
	int setWallThickness(const double &inputWallThickness);
	
	const std::vector<double> getAreaVector();
	int setAreaVector(const std::vector<double> &inputAreaVector);
	
	
private:
	double bodyMass;
	double bodyLength;
	double wallThickness;
	std::vector<double> areaVector; //frontalArea, sideArea
};
#endif
