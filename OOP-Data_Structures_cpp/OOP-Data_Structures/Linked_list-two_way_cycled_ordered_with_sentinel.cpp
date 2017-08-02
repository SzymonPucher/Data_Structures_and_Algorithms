#include "Linked_list-two_way_cycled_ordered_with_sentinel.h"


Location::Location(){}
Location::Location(double lon, double lat, string name){
	this->longitude = lon;
	this->latitude = lat;
	this->name = name;
}
Location::~Location(){}
// SETTES
bool Location::setLongitude(double lon) {
	this->longitude = lon;
	return true;
}
bool Location::setLatitude(double lat) {
	this->latitude = lat;
	return true;
}
bool Location::setName(string name){
	this->name = name;
	return true;
}
// GETTERS
double Location::getLongitude() {
	return longitude;
}
double Location::getLatitude() {
	return latitude;
}

string Location::getName(){
	return name;
}


Trip::Trip(){}
Trip::Trip(string name) {
	this->name = name;
}
Trip::~Trip(){}

bool Trip::setName(string name) {
	this->name = name;
	return true;
}
string Trip::getName() {
	return name;
}

void Trip::init() { 
	// initializes list
	sentinel = new Location;
	sentinel->next = sentinel->prev = sentinel;
}

bool Trip::insertLocation(double lon, double lat, string name) { 
	// inserts element in in right place in list
	Location *newLoc = new Location;
	newLoc->setLongitude(lon);
	newLoc->setLatitude(lat);
	newLoc->setName(name);
	if (sentinel->next == sentinel) { 
		// if list is empty
		newLoc->next = newLoc->prev = sentinel;
	}
	else if (sentinel->next->next == sentinel) { 
		// if list has only one element
		if (lon + lat < sentinel->next->getLatitude() + sentinel->next->getLongitude()) {
			newLoc->next = sentinel->next;
			newLoc->prev = sentinel;
		}
		else {
			newLoc->next = sentinel;
			newLoc->prev = sentinel->next;
		}
	}
	else { 
		// list has more than one element, we can pick place for new one using distance
		Location *srch = sentinel->next;
		Location *place = srch;
		double min_dist = distanceBetweenLocations(newLoc, srch);
		while (srch != sentinel) { 
			// looking for a location to which our new location has minimal distance
			if (min_dist > distanceBetweenLocations(newLoc, srch)) {
				min_dist = distanceBetweenLocations(newLoc, srch);
				place = srch; // pointer to "minimal distance location"
			}
			srch = srch->next;
		}
		if (distanceBetweenLocations(place->prev, newLoc) < distanceBetweenLocations(place->prev, place)) {
			// do we have closer to previous location from place we are in or to next location? Yes
			newLoc->next = place;
			newLoc->prev = place->prev;
		}
		else {
			// and No (up)
			newLoc->next = place->next;
			newLoc->prev = place;
		}
	}
	newLoc->next->prev = newLoc;
	newLoc->prev->next = newLoc;
	return true;
}
void Trip::showLocation(Location *l) { 
	// shows one object in the list
	cout.precision(9);
	cout << "   " << l->getLatitude() << " \t| " << l->getLongitude() << endl;
}
void Trip::show() { // shows all elements of list
	cout << "  LATITUDE \t| LONGITUDE" << endl;
	Location *srch = sentinel->next;
	while (srch != sentinel) {
		showLocation(srch);
		srch = srch->next;
		//cout << distanceBetweenLocations(srch->prev, srch);
	}
	cout << "  END  -------------\n";
}
double Trip::distanceBetweenLocations(Location *l1, Location *l2) { 
	// measures distance in straight line between locations based on geografical coordinates
	return sqrt(pow(l1->getLatitude() - l2->getLatitude(), 2) + pow(l1->getLongitude() - l2->getLongitude(), 2));
}
bool Trip::deleteLocation(Location *p) {
	p->next->prev = p->prev;
	p->prev->next = p->next;
	delete p;
}

bool Trip::deleteByName(string name) {
	Location *srch = sentinel->next;
	while (srch != sentinel) {
		if (srch->getName() == name)
			deleteLocation(srch);
		srch = srch->next;
	}
}