#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum userSelection { CHECK, SELL, PRINT, TEST, QUIT };

void testVecs();
void printReport();
double getTotalValue();
int getTotalItems();
void sortVecs();
void readFileIntoVecs();
bool isItemInStore(string, int&);
void sellItem(int);
userSelection getSelectionFromUser();
string getItemFromUser(userSelection);
void showMenu();
void fileInput(int);
int noOfRows();

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
		int position = -1;
		switch (selection)
		{
		case CHECK:
			userInput = getItemFromUser(selection);
			cout << "Item is "  << (isItemInStore(userInput, position) ? "" : "not ") 
				<< "available in the store." << endl;
			break;
		case SELL:
			userInput = getItemFromUser(selection);
			
			if (isItemInStore(userInput, position))
			{
				sellItem(position);
				cout << "1 unit " << userInput << " has been sold." << endl;
			}
			else
			{
				cout << "Couldn't sell item - " << userInput << " not found in store" << endl;
			}
			break;
		case PRINT:
			printReport();
			break;
		case TEST:
			testVecs();
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

//getItemFromUser() readFileIntoVecs() and sortVecs() by Steve Myers

string getItemFromUser(userSelection selection)
{
	switch (selection)
	{
	case CHECK:
		cout << "Enter name of item to check inventory: ";
		break;
	case SELL:
		cout <<  "Enter name of item to sell: ";
		break;
	}

	string input;
	getline(cin, input); 
	return input;
}
void readFileIntoVecs()
{
	fileInput(noOfRows());
}

void sortVecs()
{
	int min;

	for (unsigned i = 0; i < itemIds.size(); i++)
	{
		min = i;

		for (unsigned j = i + 1; j < itemIds.size(); j++)
			if (itemNames[j] < itemNames[min])
				min = j;

		swap(itemNames[i], itemNames[min]);
		swap(itemIds[i], itemIds[min]);
		swap(pOrdereds[i], pOrdereds[min]);
		swap(pInStores[i], pInStores[min]);
		swap(pSolds[i], pSolds[min]);
		swap(manufPrices[i], manufPrices[min]);
		swap(sellingPrices[i], sellingPrices[min]);
	}
}
void testVecs()
{
	for (unsigned i = 0; i < itemIds.size(); i++)
	{
		cout << itemIds[i] << endl << itemNames[i] << endl << pOrdereds[i] 
		<< endl << pSolds[i] << endl << manufPrices[i] << endl << sellingPrices[i] << endl;
	}
}

//isItemIntStore() and sellItem() by Steve Myers
bool isItemInStore(string userInput, int& position)
{
	for (unsigned i = 0; i < itemNames.size(); i++)
	{
		if (itemNames[i] == userInput)
		{
			position = i;
			return pInStores[i] > 0;
		}
	}
	return false;

}
void sellItem(int position)
{
	++pSolds[position];
	--pInStores[position];
}


//counts lines in textfile: Jaime Woodbury
int noOfRows()                                         
{
	int numberOfRows = 0;
	string line;
	ifstream myfile("initial.txt");

	while (getline(myfile, line))
		numberOfRows++;

	return numberOfRows;
}


//inputs file data into vectors: Jaime Woodbury
void fileInput(int noOfRows)
{
	ifstream inf("initial.txt");
	string word;
	int item, order; 
	double manPrice, sellPrice;
	char ch;

	for (unsigned i=0; i<noOfRows/3; i++)

	{      
		inf>>item;
		itemIds.push_back(item);

		inf.get(ch); 

		getline(inf, word);
		itemNames.push_back(word);

		inf>>order;
		pOrdereds.push_back(order);

		inf>>manPrice;
		manufPrices.push_back(manPrice);

		inf>>sellPrice;
		sellingPrices.push_back(sellPrice);
	}

	for (unsigned i=0; i<itemIds.size(); i++)
	{
		//intilizes vector pSolds to 0
		int sold = 0;
		pSolds.push_back(sold);

		//adds data to pInStores vector
		int inStore;
		inStore = pOrdereds.at(i)-pSolds.at(i);
		pInStores.push_back(inStore);

	}
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


//showMenu() and getSelectionFromUser by ....
void showMenu()
{

}
userSelection getSelectionFromUser()
{
	return TEST;
}

/*
bool readFileIntoVecs()
{
ifstream inFile;

//place intial.txt in the project folder
inFile.open("initial.txt");

if (!inFile)
{
cout << "Invalid input.";
inFile.close();
return false;
}

while (inFile)
{
int itemId;
string itemName;
int pOrdered;
double manufPrice, sellingPrice;

inFile >> itemId;
inFile.ignore(numeric_limits<streamsize>::max(), '\n');
getline(inFile, itemName);
inFile >> pOrdered >> manufPrice >> sellingPrice;
inFile.ignore(numeric_limits<streamsize>::max(), '\n');

itemIds.push_back(itemId);
itemNames.push_back(itemName);
pOrdereds.push_back(pOrdered);
pInStores.push_back(pOrdered);
pSolds.push_back(0);
manufPrices.push_back(manufPrice);
sellingPrices.push_back(sellingPrice);

}

inFile.close();
return true;
}
*/