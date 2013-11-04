#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

enum userSelection { CHECK_BY_ID=1, CHECK_BY_NAME, SELL_BY_ID, SELL_BY_NAME, PRINT, QUIT };

void testVecs();
void printReport(double, int);
double getTotalValue();
int getTotalItems();
void sortVecs();
void readFileIntoVecs();
bool isItemInStoreByName(string, int&);
bool isItemInStoreById(int, int&);
void sellItem(int);
userSelection getSelectionFromUser();
int getItemIdFromUser(userSelection);
string getItemNameFromUser(userSelection);
void showMenu();
void fileInput(int);
int noOfRows();
string toUpper(string);
void clearInput();

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
                string userName;
                int userId;
                showMenu();
                userSelection selection = getSelectionFromUser();
                int position = -1;
                switch (selection)
                {
                case CHECK_BY_NAME:
                        clearInput();
                        userName = getItemNameFromUser(selection);
                        cout << " ";
                        cout << "Item is " << (isItemInStoreByName(userName, position) ? "" : "not ")
                                << "available in the store." << endl;
                        break;
                case CHECK_BY_ID:
                        clearInput();
                        userId = getItemIdFromUser(selection);
                        cout << " ";
                        cout << "Item is " << (isItemInStoreById(userId, position) ? "" : "not ")
                                << "available in the store." << endl;
                        break;
                case SELL_BY_NAME:
                        clearInput();
                        userName = getItemNameFromUser(selection);

                        if (isItemInStoreByName(userName, position))
                        {
                                sellItem(position);
                                cout << " ";
                                cout << "1 unit " << userName << " has been sold." << endl;
                        }
                        else
                        {
                                cout << " ";
                                cout << "Couldn't sell item - " << userName << " not found in store" << endl;
                        }
                        break;
                case SELL_BY_ID:
                        clearInput();
                        userId = getItemIdFromUser(selection);

                        if (isItemInStoreById(userId, position))
                        {
                                sellItem(position);
                                cout << " ";
                                cout << "1 unit " << userId << " has been sold." << endl;
                        }
                        else
                        {
                                cout << " ";
                                cout << "Couldn't sell item - " << userId << " not found in store" << endl;
                        }
                        break;
                case PRINT:
                        printReport(getTotalValue(), getTotalItems());
                        break;
                case QUIT:
                default:
                        wantsToQuit = true;
                        break;
                }
                if (wantsToQuit) break;
                system("pause");
        }

        return 0;
}

//getItemNameFromUser() getItemIdFromUser() readFileIntoVecs() and sortVecs() by Steve Myers

string getItemNameFromUser(userSelection selection)
{
        cout << " ";
        switch (selection)
        {
        case CHECK_BY_NAME:
                cout << "Enter name of item to check inventory: ";
                break;
        case SELL_BY_NAME:
                cout << "Enter name of item to sell: ";
                break;
        }

        string input;
        getline(cin, input);
        return input;
}
int getItemIdFromUser(userSelection selection)
{
        int input;
        while (true)
        {
                cout << " ";
                switch (selection)
                {
                case CHECK_BY_ID:
                        cout << "Enter ID of item to check inventory: ";
                        break;
                case SELL_BY_ID:
                        cout << "Enter ID of item to sell: ";
                        break;
                }
                cin >> input;
                
                if (cin) break;
                else clearInput();
        }

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

// toUppder() copied from stackoverflow by user GigaWatt
// http://stackoverflow.com/questions/9507895/converting-stdstring-to-upper-case-major-performance-difference

string toUpper(string str)
{
        for (int pos = 0, sz = str.length(); pos < sz; ++pos)
        {
                if (str[pos] >= 'a' && str[pos] <= 'z') { str[pos] += ('A' - 'a'); }
        }
        return str;
}

//isItemIntStoreByName() isItemIntStoreById() and sellItem() by Steve Myers
bool isItemInStoreByName(string userName, int& position)
{
        for (unsigned i = 0; i < itemNames.size(); i++)
        {
                if (toUpper(itemNames[i]) == toUpper(userName))
                {
                        position = i;
                        return pInStores[i] > 0;
                }
        }
        return false;

}
bool isItemInStoreById(int input, int& position)
{
        for (unsigned i = 0; i < itemIds.size(); i++)
        {
                if (itemIds[i] == input)
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
void printReport(double getTotalValue, int getTotalItems)
{
        system("CLS");
        cout << left << setw(8) << itemIds.at(0)
        << setw(20) << itemNames.at(0) << setw(12) << pOrdereds.at(0) << setw(12)<< pInStores.at(0) << setw(12)  << pSolds.at(0)
        << setw(12) <<manufPrices.at(0)<< setw(12) << sellingPrices.at(0)<<endl
        <<setw(10) <<getTotalValue << setw(10) << getTotalItems;
}
//gets total selling price of all the items in store
//getTotalValue() by Jaime Woodbury
double getTotalValue()
{
	//initialize variable - SM
    double totalValue = 0;
    for(int a=0; a<itemIds.size(); a++)
	//edit to multiply by pInStores[a] - SM
    totalValue += sellingPrices[a] * pInStores[a];
        
    return totalValue;
}

//gets total items in store
//getTotalItems by Jaime Woodbury
int getTotalItems()
{
	//initialize variable - SM
    int totalItems = 0;
    for(int a=0; a<itemIds.size(); a++)
    totalItems=totalItems+pInStores[a];
    
    return totalItems;
}


//showMenu() by Jaime Woodbury
void showMenu()
{
        system("CLS");
        cout<<endl<<endl<<endl<<endl
                <<" MAIN MENU"<<endl
                <<" **********************************************"<<endl
                <<" * *"<<endl
                <<" * 1 - Check Inventory by ID. *"<<endl
                <<" * *"<<endl
                <<" * 2 - Check Inventory by Name. *"<<endl
                <<" * *"<<endl
                <<" * 3 - Sell an Item By ID. *"<<endl
                <<" * *"<<endl
                <<" * 4 - Sell an Item By Name. *"<<endl
                <<" * *"<<endl
                <<" * 5 - Print Report *"<<endl
                <<" * *"<<endl
                <<" * 6 - Quit Program. *"<<endl
                <<" * *"<<endl
                <<" **********************************************"<<endl
                <<endl;
}

//getSelectionFromUser() by Steve Myers
userSelection getSelectionFromUser()
{
        //nice static type system here.

        int s = false;
        while (!s)
        {
                cout <<" Enter the Number of Your Selection: ";
                cin >> s;
                if (s == CHECK_BY_ID || s == CHECK_BY_NAME || s == SELL_BY_ID
                        || s == SELL_BY_NAME || s == PRINT || s == QUIT)
                {
                        return static_cast<userSelection> (s);
                }
                s = false;
                clearInput();
        }
}
//clearInput() by Steve Myers
void clearInput()
{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
