/*
Code for assingment 5 task 2, translation of a class diagram. Created by Szymon Pucher.

Association class: Created by attaching as atributes, pointers to classes that association class connects. In this case RESERVATION (associotiation class) connects classes CLIENT and ROOM.
Composition: Created by adding to class A which is a part of class B ( Class B is a composits of class A), class B as a pointer.  Then creating destructor of class B in such way that when class B is deleted it deletes all classes A, that are a part of class B (ex. if building is destroyed all rooms in it are destroyed too).
Aggregation: Created by adding to class A which is a part of class B, class B as a pointer. Then creating destructor of class B in such way that when class B is deleted, all classes A that are a part of class B still exist.
Association: Is created by adding pointer to a class that has multiplicity is bigger or equal to 1 that is associated with a class that has multiciply equal to 1 (if multiciplity is many to many there is usually association class between them).
*/
#include <iostream>

using namespace std;

class Hotel;
class Client;
class Payment;

class Room {

	int room_number;
	char* room_standard;
	Hotel* myHotel_p; // pointer to a hotel, in which this room is

public:
	
	Room() {};

	Room(Hotel* htl, int num, char* room_std) {
		// creates room and assingns it to given hotel
		myHotel_p = htl;

		if (NULL != myHotel_p) {
			room_number = num;

			room_standard = new char(sizeof(strlen(room_std)));
			room_standard = room_std;
		}
		else cout << "Error! Hotel itself is not created yet.\n";
		cout << "|| INFO || New instance of class ROOM  (" << room_number << ", " << room_standard << ") created." << endl;
	};

	~Room() {
		cout << "|| INFO || Instance of class ROOM (" << room_number << ", " << room_standard << ") deleted." << endl;
		//myHotel_p = NULL;
		//delete (room_standard);
	}

	static void createRoom_v(Room* (&room), Hotel* hse, int num, char* rStd) {
		// Used for creating an instace of room in choosen hotel
		room = new Room(hse, num, rStd);
	}

	static void initList_v(Room *(&roomsList_p)[5]) {
		// Function creates list of rooms.
		roomsList_p[5] = new Room[5];
	}

	int getRoomNum() {
		return room_number;
	}

	void disp() {
		// Function displays room info.
		cout << "Room number: " << room_number << "\nRoom standard: " << room_standard << endl << endl;
	}

};
/* */
class Client
{
private:
	int ID;
	char* name_p;
	char* dateOfBirth_p;
	char gender;

public:

	Client(int id_num, char *sName, char* dateOfBirth, char gndr) {
		
		ID = id_num;
		gender = gndr;

		name_p = new char(sizeof(strlen(sName)));
		name_p = sName;

		dateOfBirth_p = new char(sizeof(strlen(dateOfBirth)));
		dateOfBirth_p = dateOfBirth;

		cout << "|| INFO || New instance of class CLIENT (" << ID << ", " << name_p << ", " << dateOfBirth_p << ") created." << endl;
	}

	char* getClientName()const {
		return(name_p);
	}

	~Client() {
		cout << "|| INFO || Instance of class CLIENT (" << name_p << ", " << dateOfBirth_p << ") deleted." << endl;
		//delete(name_p);
	};
};
/* */
class Reservation
{
private:

	// pointers to objects of classes this association class connect, this is my approach for creating association class in c++
	Client * client_p;
	Room * room_p;
	char * startDate;
	char * endDate;
	char * status;

	Payment* paym_p; /* pointer to instance of PAYMENT class, based on that aggregation is created,
					  one payment can be done for one reservation, but a client can make many payments for many different reservations. */

	static unsigned int index;
	static Reservation* reservationList[4];

public:

	Reservation(char* sDate, char* eDate, char* rStatus, Client* client, Room* room) :
		startDate(0), endDate(0), status(0), client_p(client), room_p(room)
	{
		
		if (index < 4)
		{
			// assigning input values to an instance of reservation class
			startDate = new char(sizeof(strlen(sDate)));
			startDate = sDate;

			endDate = new char(sizeof(strlen(eDate)));
			endDate = eDate;

			status = new char(sizeof(strlen(rStatus)));
			status = rStatus;

			//insert this reservation in reservationList
			reservationList[index++] = this;
		}
		else cout << "Cannot accomodate any more Reservations. Limit: 4.\n";

		cout << "|| INFO || New instance of class RESERVATION (" << getClientName() << ", " << startDate << ", " << endDate << ", " << getRoomNum() << ") created." << endl;
	};

	Reservation(char* sDate, char* eDate, char* rStatus, Client* client, Room* room, Payment* paym) :
		startDate(0), endDate(0), status(0), client_p(client), room_p(room), paym_p(paym)
	{
		/*
		Proper (in my opinion) constructor for class diagram this code is based on. Creates instance of RESERVATION which is an association class and to which PAYMENT objects aggregate.
		*/
		if (index < 4)
		{
			// assigning input values to an instance of reservation class
			startDate = new char(sizeof(strlen(sDate)));
			startDate = sDate;

			endDate = new char(sizeof(strlen(eDate)));
			endDate = eDate;

			status = new char(sizeof(strlen(rStatus)));
			status = rStatus;

			//insert this reservation in reservationList
			reservationList[index++] = this;
		}
		else cout << "Cannot accomodate any more Reservations. Limit: 4.\n";

		cout << "|| INFO || New instance of class RESERVATION(" << getClientName() << ", " << startDate << ", " << endDate << ", " << getRoomNum() << ") created." << endl;
	};

	

	~Reservation() {
		cout << "|| INFO || Instance of class RESERVATION (" << getClientName() << ", " << startDate << ", " << endDate << ", " << getRoomNum() << ") deleted." << endl;
		/* * /
		I've encoutered minor problems with visual studio and destructors. That's why I commented deleting those pointers.
		delete (startDate);
		delete (endDate);
		delete (status);
		/* */
		paym_p = NULL;
		index--;
	};

	static char* findClient(char *rStart, int roomNum) {
		for (int i = 0; i <index; i++)
		{
			if ((reservationList[i]->getReservStartDate() == rStart) &&
				(reservationList[i]->getRoomNum() == roomNum))
			{
				// roomName (room name) and rStart (reservation start date) serve as a key in this class, pairs of them have to be unique
				return(reservationList[i]->getClientName());
			}
		}
	}

	static void disp() {
		cout << "List of all reservations (for checking findClient method):\n";
		for (int i = 0; i < index; i++) {
			cout << "\n----";
			cout << "\nReservation start date: " << reservationList[i]->startDate;
			cout << "\nName: " << reservationList[i]->getClientName();
		}
		cout << "\n\n-----------\n\n";
	}
	// getters
	char* getClientName()const { return(client_p->getClientName()); };
	int getRoomNum() const { return(room_p->getRoomNum()); };
	char* getReservStartDate()const { return(startDate); };
	char* getReservEndDate()const { return(endDate); };
	char* getReservStatus()const { return(status); };
};

/* */
class Hotel {
	/*
	Class which contains all ROOMS, done by a list of pointers to instances of ROOM class, which is deleted when HOTEL object containing those rooms is deleted and created the hotel is created.
	*/
private:
	char* Hotel_name;
	char* address;
	int amountOfStars;
	

public:
	Room* roomsList[5];
	Hotel() {};
	Hotel(char *hName, char* addr, int stars) {

		// assigning given name of hotel to instance of a class
		Hotel_name = new char(sizeof(strlen(hName)));;
		Hotel_name = hName;

		address = new char(sizeof(strlen(addr)));;
		address = addr;

		amountOfStars = stars;
		cout << "|| INFO || New instance of class HOTEL (" << Hotel_name << ") created." << endl;
		// initializing list of room in hotel
		Room::initList_v(roomsList);

		// creating example rooms in hotel
		Room* myRoom;
		Room::createRoom_v(myRoom, this, 110, "Premium");
		roomsList[0] = myRoom;

		Room::createRoom_v(myRoom, this, 232, "Standard");
		roomsList[1] = myRoom;

		Room::createRoom_v(myRoom, this, 321, "VIP");
		roomsList[2] = myRoom;

		Room::createRoom_v(myRoom, this, 113, "Standard");
		roomsList[3] = myRoom;

		Room::createRoom_v(myRoom, this, 287, "Studio");
		roomsList[4] = myRoom;
	}

	~Hotel()
	{
		cout << "|| INFO || Instance of class HOTEL (" << Hotel_name << ") deleted." << endl;
		// Deleting all the rooms, list of rooms and name of hotel; classic destructor :)
		for (unsigned int i = 0; i<5; ++i)
			if (roomsList[i] != NULL)
				delete (roomsList[i]);

		//delete[] roomsList_p; 
		//delete (Hotel_name);
		//delete (address);
	}

	void disp() {
		// Displays information about all the rooms in hotel.

		cout << "\nName of the Hotel: " << Hotel_name << " at " << address << " with " << amountOfStars << " stars.\n";

		if (roomsList != NULL) {
			cout << "\nROOMS INFO: \n";
			for (unsigned int i = 0; i < 5; i++)
				if (NULL != roomsList[i])
					roomsList[i]->disp();

		}
	}
};

/* */
class Payment {
private:
	float amount;
	char* dateOfPayment;
	Client* cli_p; // every payment is associated with one client

public:
	Payment(char *date, float amt, Client* client_name) {
		
		
		dateOfPayment = new char(sizeof(strlen(date)));
		dateOfPayment = date;
		amount = amt;
		cli_p = client_name;
		cout << "|| INFO || New instance of class PAYMENT (" << amount << ", " << dateOfPayment << ") created." << endl;
	}

	~Payment() {
		cout << "|| INFO || Instance of class PAYMENT(" << amount << ", " << dateOfPayment << ") deleted." << endl;
		//delete (dateOfPayment);
		cli_p = NULL;
	}

	void disp() {
		cout << "Date of payment: " << dateOfPayment << endl;
		cout << "Amount of money paid: " << amount << endl << endl;
	};
};
/* */
unsigned int Reservation::index = 0;
Reservation* Reservation::reservationList[4] = { 0,0,0,0 };

int main()
{
	cout << "-------------------------------- Example of Hotel - Room composition ----------------------------------\n\n";
	{
		cout << "HOTEL itself creates the ROOMS and deletes them as well, before it gets deleted...\n";
		Hotel htl("Prime Hotel", "21 street, NY", 4);

		cout << "\n\HOTEL INFO:";
		htl.disp();
		cout << "\n!! Here HOTEL is deleted, and because of that all rooms in hotel are deleted too.\n";
	}
	cout << "\n\n----------------------------------------- END OF Composition example -------------------------------------------\n\n\n\n";
	/* */
	{
		int i;

		cout << "----------------- Example of Association Class RESERVATION - connecting classes: ROOM and Client ------------------\n\n";

		cout << "We've got 4 CLIENTS:\n";
		Client *clients[4] = { new Client(1, "Melanie", "24.05.1976", 'F'), new Client(2, "Sefanie", "02.01.1965", 'F'), new Client(3, "John", "30.03.1973", 'M'), new Client(4, "Mark", "11.08.1982", 'M') };

		cout << "\nWe've got 5 ROOMS (here we will only assign reservations to first 2):\n";

		Hotel htl("Prime Hotel", "21 street, NY", 4);

		cout << "\nHere class RESERVATION associates CLIENT and ROOM.\n";
		Reservation reserv1("06.06.2017", "08.06.2017", "unpaid", clients[0], htl.roomsList[1]);
		Reservation reserv2("22.06.2017", "09.07.2017", "paid", clients[3], htl.roomsList[0]);
		Reservation reserv3("28.07.2017", "21.08.2017", "unpaid", clients[2], htl.roomsList[0]);
		Reservation reserv4("18.06.2017", "29.06.2017", "cancelled", clients[1], htl.roomsList[1]);

		cout << "\nFinding a CLIENT using RESERVATION and ROOM: \n";
		cout << "CLIENT who RESERVED ROOM number: 110 from 22.06.2017 is: " << Reservation::findClient("22.06.2017", 110) << endl << endl;

		Reservation::disp();

		cout << "Deletion of objects.\n\n";
	}
	/* */
	cout << "\n\n-------------------------------------- END OF Association class example --------------------------------------\n\n\n\n";
	cout << "----------- Example of Reservation - Payment aggregation + association between CLIENT and PAYMENT ------------\n\n";

	{
		Client client(1, "Melanie", "24.05.1976", 'F');
		Hotel htl("Prime Hotel", "21 street, NY", 4);
		Payment pmnt("11.12.2016", 1390.99, &client);
		cout << "A PAYMENT $1390.90 was done for RESERVATION for a ROOM from 11.12.2016, by Melanie with ID = 1. \n";
		{
			Reservation reserv1("06.06.2017", "08.06.2017", "unpaid", &client, htl.roomsList[1], &pmnt);
			cout << "At this point RESERVATION gets deleted...\n";
		} // here RESERVATION object will be deleted, whereas PAYMENT object is still there

		cout << "\nBut PAYMENT is still there: \n"; 
		pmnt.disp();
		cout << "\n";

	} // here PAYMENT is deleted
	cout << "\n\n----------------------------------------- END OF Aggregation example -------------------------------------------\n";


	system("pause");
	exit(0);
	return(0);
}