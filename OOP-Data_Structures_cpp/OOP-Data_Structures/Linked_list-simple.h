
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
	string name;
	unsigned int expiryDate[3];
	float price;
public:
	Product *next;
	Product();
	Product(string name, unsigned int expiryDate[], float price);
	~Product();
	string expiryDateFormat();

	void setPrice(float price);

	bool setName(string name);
	bool setExpiryDate(unsigned int expiryDate[]);
	bool setPrice(string price);

	string getName();
	unsigned int* getExpiryDate();
	float getPrice();
};

class Groceries {
private:
	Product *head;
public:
	Groceries ();
	~Groceries ();

	void init();
	bool insertFirst(string name, unsigned int expiryDate[], float pricee);
	bool insertLast(string name, unsigned int expiryDate[], float price);

	void deleteFirst();
	void deleteLast();
	void deleteProduct(string name);
	void clearList();

	void showProduct(Product * p);
	void show();
	void show(string name);
	void show(float price);

	void swapData(Product * p1, Product * p2);

	void swap(Product * p, Product * p_prev);

	bool isOrderedByName();
	void orderByName();

	bool isOrderedByPrice();
	void orderByPrice();
};

