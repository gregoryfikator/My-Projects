#include <iostream>
#include "Prefix.h"
#include "Suffix.h"
#include "Weapon.h"

using namespace std;

int main()
{
	srand(time(NULL));

	cout << "Decorator pattern test" << endl;
	cout << "Dynamic adding prefixes and sufixes for items." << endl;
	cout << "Like in RPG game as Diablo" << endl << endl << endl;

	cout << "1. Pointer to the abstract class of the item." << endl;
	cout << "Creating new Item and decorating it with new random prefix and suffix." << endl;
	cout << "Prints name received from ItemAbstract pointer: " << endl;
	ItemAbstract * ptr = new Suffix(new Prefix(new Item("Topor")));
	string tmp = ptr->getName();
	cout << tmp << endl << endl;

	cout << "2. Than we can pass received name from decorator to initialize static object of Item class." << endl;
	cout << "Prints name from Item class field: " << endl;
	Item staticItem(tmp);
	cout << staticItem.getName();
	cout << endl << endl;

	cout << "3. Or pass received name from decorator to initialize dynamic object of Item class." << endl;
	cout << "Prints name received from Item pointer: " << endl;
	Item * dynamicItem = new Weapon(tmp);
	cout << dynamicItem->getName();
	cout << endl << endl;

	system("PAUSE");
	delete ptr;
	delete dynamicItem;
	return 0;
}
