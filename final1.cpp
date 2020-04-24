#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <list>
#include "unordered_map.hpp"
using namespace std;
int main()
{
	Hashtable<int> phoneBook;
	phoneBook.insert("Shaji",903);
	phoneBook.insert("Ludei",90903);
	phoneBook.insert("Kiri",9093);
	phoneBook.insert("CHei",9031);
	phoneBook.insert("Abbai",9023);
	phoneBook.insert("Ummi",9033);
	phoneBook.insert("Ammi",90);
	phoneBook.insert("Anchi",03);
	Hashtable<int>::iterator it1 = phoneBook.begin();
	it1.print();
	//copy constructor
	Hashtable<int> nameMap(phoneBook);
	Hashtable<int>::iterator it2 = nameMap.begin();
	cout << endl;
	it2.print();
	//copy assignement operator
	//move constructor
	Hashtable<int> nameMap1 = move(phoneBook);
	Hashtable<int>::iterator it3 = nameMap1.begin();
	cout << endl;
	it3.print();
	//iterating through hash map
	for(Hashtable<int>::iterator it = nameMap1.begin();it != nameMap1.end();++it)
		cout << (*it).first << " " << (*it).second << endl;
	//normal iteration 
	for(auto it = nameMap1.begin();it!=nameMap1.end();++it)
		cout << (*it).first << " " << (*it).second << endl;
	//Find function
	Hashtable<int>::iterator it = nameMap1.search("Shaji");
	cout << endl;
	if(it != nameMap1.end())
		cout << (*it).first << " " << (*it).second << endl;
	else
		cout << "Not present" << endl;
	//operator overloading []
	nameMap1["Shaji"] += 3;
	cout << nameMap1["Shaji"] << endl;
	nameMap1["Sangam"] = 10;
	cout << nameMap1["Sangam"] << endl;
  	return 0;
}
