#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum userSelection { CHECK, SELL, PRINT, QUIT};

void printReport();
double getTotalValue();
int getTotalItems();
void sortVecs();
void readFileIntoVecs();
bool isItemInStore(string);
string sellItem(string);
userSelection getSelectionFromUser();
string getItemFromUser(userSelection);
void showMenu();

vector<int> itemIds;
vector<string> itemNames;
vector<int> pOrdereds;
vector<int> pInStores;
vector<int> pSolds;
vector<double> manufPrices;
vector<double> sellingPrices;

//main() by Steve Myers
int main()
{

	readFileIntoVecs();
	sortVecs();

	while (true)
	{
		bool wantsToQuit = false;
		string userInput;
		showMenu();
		userSelection selection = getSelectionFromUser();
		switch (selection)
		{
		case CHECK:
			userInput = getItemFromUser(selection);
			cout << "Item is "  << (isItemInStore(userInput) ? "" : "not ") 
				<< "available in the store." << endl;
			break;
		case SELL:
			userInput = getItemFromUser(selection);
			sellItem(userInput);
			cout << "1 unit " << userInput << " has been sold." << endl;;
			break;
		case PRINT:
			printReport();
			break;
		case QUIT:
		default:
			wantsToQuit = true;
			break;
		}
		if (wantsToQuit) break;
	}
	system("pause");
	return 0;
}

//getItemFromUser() and sortVecs() by Steve Myers

string getItemFromUser(userSelection selection)
{
	return " ";
}
void sortVecs()
{
}


//readFileIntoVecs() by ...
void readFileIntoVecs()
{
}



//printReport(), getTotalValue() and getTotalItems() by...
void printReport()
{
}
double getTotalValue()
{
	return 0;
}
int getTotalItems()
{
	return 0;
}



//isItemIntStore() and sellItem() by ....
bool isItemInStore(string userInput)
{
	return false;
}
string sellItem(string userInput)
{
	return "";
}



//showMenu() and getSelectionFromUser by ....
void showMenu()
{

}
userSelection getSelectionFromUser()
{
	return QUIT;
}