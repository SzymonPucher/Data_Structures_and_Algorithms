#include <iostream>
#include <string>
using namespace std;

class Location
{
private:
	double longitude;
	double latitude;
	
public:
	Location *next;
	Location *prev;
	Location();
	Location(double lon, double lat);
	~Location();

	bool setLongitude(double lon);
	bool setLatitude(double lat);
	double getLongitude();
	double getLatitude();



};


class Trip
{
private:
	string name;
	Location *sentinel;

public:
	Trip();
	Trip(string name);
	~Trip();

	bool setName(string name);
	string getName();

	void init();

	bool insertLocation(double lon, double lat);

	void showLocation(Location * l);

	void show();

	double distanceBetweenLocations(Location * l1, Location * l2);



};
