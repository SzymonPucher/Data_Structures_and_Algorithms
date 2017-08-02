#include "main.h"
#include "math.h"
void test_linked_list_simple() {
	Groceries g;
	g.init();
	unsigned int arr1[3] = { 31,1,2017 };
	unsigned int arr2[3] = { 21,2,2015 };
	unsigned int arr3[3] = { 11,3,2016 };
	unsigned int arr4[3] = { 31,4,2015 };
	unsigned int arr5[3] = { 21,5,2016 };
	unsigned int arr6[3] = { 11,6,2015 };
	unsigned int arr7[3] = { 31,7,2016 };
	unsigned int arr8[3] = { 21,8,2015 };
	unsigned int arr9[3] = { 11,9,2017 };
	
	g.insertLast("Aaa", arr1, 363.99);
	g.insertFirst("Bbb", arr3, 413.43);
	g.insertFirst("Ccc", arr2, 6.77);
	g.insertLast("Sss", arr3, 33.99);
	g.insertFirst("Dss", arr4, 133.43);
	g.insertLast("Bbb", arr5, 413.43);
	g.insertFirst("Das", arr6, 333.99);
	g.insertFirst("Wds", arr7, 123.43);
	g.insertFirst("Des", arr8, 613.77);
	g.insertLast("Wer", arr9, 3763.99);
	g.insertFirst("Ads", arr3, 813.43);
	g.insertLast("Ers", arr6, 66.77);
	g.show();
	g.orderByName();
	g.show();
	g.orderByPrice();
	g.show();
	g.deleteFirst();
	g.deleteLast();
	g.deleteFirst();
	g.show();
}



void test_linked_list_complex() {
	Trip t;
	t.init();
	t.insertLocation(51.112676, 12.555555, "a");
	t.insertLocation(53.112676, 32.555555, "a");
	t.insertLocation(23.112676, 43.555555, "c");
	t.insertLocation(12.112676, 125.555555, "c");
	t.insertLocation(45.112676, 87.555555, "b");
	t.insertLocation(57.112676, 31.555555, "d");
	t.insertLocation(123.112676, 93.555555, "b");
	t.insertLocation(43.112676, 45.555555, "b");
	t.show();
	t.deleteByName("d");
	t.show();
	t.deleteByName("a");
	t.show();
	t.deleteByName("c");
	t.show();
	t.deleteByName("b");
	t.show();
}

bool CubeRoot(int x) {
	if (cbrt(x) == int(cbrt(x))) return true;
	return false;
}

int solution(int a, int b) {
	int res = 0;
	for (int i = a; i < b; i++) {
		if (CubeRoot(i)) res++;
	}
	return res;
}

int main() {
	
	//test_linked_list_simple();
	//test_linked_list_complex();
	cout << solution(8,1000000);
	system("pause");
	return 0;
}