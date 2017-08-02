#include <iostream>
#include <string>
using namespace std;

class Location
{
private:
	double longitude;
	double latitude;
	string name;
public:
	Location *next;
	Location *prev;
	Location();
	Location(double lon, double lat, string name);
	~Location();

	bool setLongitude(double lon);
	bool setLatitude(double lat);
	bool setName(string name);
	double getLongitude();
	double getLatitude();
	string getName();



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

	bool insertLocation(double lon, double lat, string name);

	void showLocation(Location * l);

	void show();

	double distanceBetweenLocations(Location * l1, Location * l2);

	bool deleteLocation(Location * p);

	bool deleteByName(string name);



};
