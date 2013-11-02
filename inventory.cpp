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
bool readFileIntoVecs();
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
	if (! readFileIntoVecs()) 
	{
		system("pause");
		return 1;
	}

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

//getItemFromUser() readFileIntoVects() and sortVecs() by Steve Myers

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
void sortVecs()
{
    int min;
 
    for (int i = 0; i < itemIds.size(); i++)
    {
        min = i;

        for (int j = i + 1; j < itemIds.size(); j++)
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
	for (int i = 0; i < itemIds.size(); i++)
	{
		cout << itemIds[i] << endl << itemNames[i] << endl << pOrdereds[i] 
		<< endl << pSolds[i] << endl << manufPrices[i] << endl << sellingPrices[i] << endl;
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
	return TEST;
}