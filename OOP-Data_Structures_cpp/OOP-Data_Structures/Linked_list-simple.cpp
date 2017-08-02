#include "Linked_list-simple.h"

Product::Product() {}
Product::Product(string name, unsigned int expiryDate[], float price) {
	this->name = name;
	for (int i = 0; i < 3; i++)
		this->expiryDate[i] = expiryDate[i];
	this->price = price;
	
}
Product ::~Product() {}

string Product::expiryDateFormat() {
	return to_string(expiryDate[0]) + "-" + to_string(expiryDate[1]) + "-" + to_string(expiryDate[2]);
}


void Product::setPrice(float price) {
	this->price = price;
}

bool Product::setName(string name) {
	this->name = name;
	return true;
}
bool Product::setExpiryDate(unsigned int expiryDate[]) {
	for (int i = 0; i < 3; i++)
		this->expiryDate[i] = expiryDate[i];
	return true;
}
bool Product::setPrice(string price) {
	try {
		for (int i = 0; i < price.size(); i++)
			if (!isdigit(price[i]) && price[i] != '.')
				throw "Price should be a floating point number.";
		this->price = stof(price);
		return true;
	}
	catch (string error) { 
		cout << "Error! " << error << endl; 
		return false;
	}
}


string Product::getName() {
	return name;
}

unsigned int* Product::getExpiryDate() {
	return expiryDate;
}

float Product::getPrice() {
	return price;
}

Groceries::Groceries() {}
Groceries ::~Groceries() {}

void Groceries::init() {
	// initializes list
	head = new Product;
	head = NULL;
}

bool Groceries::insertFirst(string name, unsigned int expiryDate[], float price) {
	// inserts new person at the beginning of the list
	Product *newPerson = new Product(name, expiryDate, price);
	newPerson->next = head;
	head = newPerson;
	return true;
}
bool Groceries::insertLast(string name, unsigned int expiryDate[], float price) {
	// inserts new person at last place of the list
	if (head == NULL) {
		insertFirst(name, expiryDate, price);
		return true;
	}
	Product *newProduct = new Product(name, expiryDate, price);
	Product *p = head;
	while (p->next != NULL)
		p = p->next;
	newProduct->next = NULL;
	p->next = newProduct;
	return true;
}

void Groceries::deleteFirst() {
	// deletes first element
	if (head == NULL) // list is empty
		return;
	Product *p = head;
	if (head->next == NULL) { // list has only one element
		head = NULL;
		delete p;
		return;
	}
	//list has many elements
	head = head->next;
	delete p;
}
void Groceries::deleteLast() {
	// deletes last element
	if (head == NULL) // list is empty
		return;
	if (head->next == NULL)
		deleteFirst();
	Product *p = head;
	while (p->next->next != NULL)
		p = p->next;
	p->next = NULL;
}

void Groceries::deleteProduct(string name) {
	// deletes person with given id
	Product *p = head;
	if (head->getName() == name) {
		deleteFirst();
	}
	while (p->next != NULL) {
		if (p->next->getName() == name) {
			p->next = p->next->next;
		}
		p = p->next;
	}
	if (p->next == NULL && p->getName() == name) {
		deleteLast();
	}
}

void Groceries::clearList() {
	// deletes all elements from the list
	while (head != NULL) // until list is empty, delete first elements
		deleteFirst();
}

void Groceries::showProduct(Product *p) {
	// prints out one product from list
	cout << "  " << p->getName() << "\t| " << p->expiryDateFormat() << "\t| $" << p->getPrice() << "   \t|" << endl;
}

void Groceries::show() {
	// prints out current state of list
	cout << "\n  -------------------GROCERIES-------------------\n";
	cout << "  NAME\t| EXPIRY DATE\t| PRICE\t\t|" << endl;
	if (head != NULL) { // if list is not empty
		Product *p = head;
		while (p != NULL) {
			showProduct(p);
			p = p->next;
		}
	}
	cout << "  ------------------END OF LIST------------------\n";
}

void Groceries::show(string name) {
	// prints out all products with given name
	cout << "\n  -------------------GROCERIES-------------------\n";
	cout << "  NAME\t| EXPIRY DATE\t| PRICE\t\t|" << endl;
	if (head != NULL) { // if list is not empty
		Product *p = head;
		while (p != NULL) {
			if(p->getName() == name)
				showProduct(p);
			p = p->next;
		}
	}
	cout << "  ------------------END OF LIST------------------\n";
}
void Groceries::show(float price) {
	// prints out all products with given price
	cout << "\n  -------------------GROCERIES-------------------\n";
	cout << "  NAME\t| EXPIRY DATE\t| PRICE\t\t|" << endl;
	if (head != NULL) { // if list is not empty
		Product *p = head;
		while (p != NULL) {
			if (p->getPrice() == price)
				showProduct(p);
			p = p->next;
		}
	}
	cout << "  ------------------END OF LIST------------------\n";
}

void Groceries::swap(Product *p, Product *p_prev) {
	// swaps two Product objects in list by changing pointers
	if (p == head) {
		Product *temp = p;
		head = temp->next;
		temp->next = head->next;
		head->next = temp;
	}
	else {
		Product *temp = p;
		p_prev->next = temp->next;
		temp->next = temp->next->next;
		p_prev->next->next = temp;
	}
}

void Groceries::swapData(Product *p1, Product *p2) { 
	// swaps data of 2 Product objects by changing data
	/* */

	string name_temp = p1->getName();
	p1->setName(p2->getName());
	p2->setName(name_temp);

	unsigned int *arr_temp = p1->getExpiryDate();
	unsigned int p1_arr[3] = {*(arr_temp), *(arr_temp + 1), *(arr_temp + 2) };
	arr_temp = p2->getExpiryDate();
	unsigned int p2_arr[3] = { *(arr_temp), *(arr_temp + 1), *(arr_temp + 2) };
	p1->setExpiryDate(p2_arr);
	p2->setExpiryDate(p1_arr);

	float price_temp = p1->getPrice();
	p1->setPrice(p2->getPrice());
	p2->setPrice(price_temp);
	/* */
}



bool Groceries::isOrderedByName(){
	// checks if list is ordered by ID
	Product *p = head;
	while (p->next != NULL) { // goes through all elements
		if (p->getName() > p->next->getName())
			return false; 
		p = p->next;
	}
	return true;
}

void Groceries::orderByName() {
	if (head->next != NULL) { // if list consists of at least 2 elements
		while (!isOrderedByName()) { // if is not sorted
			Product *p = head;
			Product *p_prev = p;
			while (p->next != NULL) { // goes through all elements
				if (p->getName() > p->next->getName()) { // if next element has smaller id than current, swap them
					swapData(p, p->next);
				}
				p = p->next;
			}
		}
	}
}

bool Groceries::isOrderedByPrice() {
	// checks if list is ordered by ID
	Product *p = head;
	while (p->next != NULL) { // goes through all elements
		if (p->getPrice() > p->next->getPrice())
			return false;
		p = p->next;
	}
	return true;
}

void Groceries::orderByPrice() {
	if (head->next != NULL) { // if list consists of at least 2 elements
		while (!isOrderedByPrice()) { // if is not sorted
			Product *p = head;
			Product *p_prev = head;
			while (p != NULL && p->next != NULL) { // goes through all elements
				if (p->getPrice() > p->next->getPrice()) { // if next element has smaller id than current, swap them
					swap(p, p_prev);
				}
				p_prev = p;
				p = p->next;
			}
		}
	}
}

