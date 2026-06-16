#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

class ParkingBlock {

private:
	string** slots;
	int* slotsPerRow;
	int totalRows;
	float x_coordinate, y_coordinate;

public:

	//Default Constructor
	ParkingBlock()
	{
		slots = nullptr;
		slotsPerRow = nullptr;
		totalRows = 0;
		x_coordinate = 0;
		y_coordinate = 0;
	}

	//Parameterized Constructor
	ParkingBlock(int numRows)
	{
		slots = new string * [numRows];
		slotsPerRow = new int[numRows];
		for (int i = 0;i < numRows;i++)
		{
			slots[i] = nullptr;
			slotsPerRow[i] = 0;
		}
		totalRows = numRows;
		x_coordinate = 0;
		y_coordinate = 0;
	}

	//Destructor
	~ParkingBlock()
	{
		for (int i = 0;i < totalRows;i++)
		{
			delete[]slots[i];
		}
		delete[]slots;
		delete[]slotsPerRow;
	}

	//Copy Constructor
	ParkingBlock(const ParkingBlock& other)
	{
		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;
		slots = new string * [totalRows];
		slotsPerRow = new int[totalRows];
		for (int i = 0;i < totalRows;i++)
		{
			slotsPerRow[i] = other.slotsPerRow[i];
			slots[i] = new string[other.slotsPerRow[i]];
		}
		for (int i = 0;i < totalRows;i++)
		{
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				slots[i][j] = other.slots[i][j];
			}
		}
	}

	//Move Constructor
	ParkingBlock(ParkingBlock&& other)
	{
		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;
		slots = other.slots;
		slotsPerRow = other.slotsPerRow;
		other.slots = nullptr;
		other.slotsPerRow = nullptr;
		other.totalRows = 0;
	}

	// Copy Assignment
	ParkingBlock& operator = (const ParkingBlock& other)
	{
		if (this == &other)
			return *this;

		for (int i = 0; i < totalRows; i++)
			delete[] slots[i];
		delete[] slots;
		delete[] slotsPerRow;

		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;

		slots = new string * [totalRows];
		slotsPerRow = new int[totalRows];

		for (int i = 0; i < totalRows; i++)
		{
			slotsPerRow[i] = other.slotsPerRow[i];
			if (other.slots[i] != nullptr)
			{
				slots[i] = new string[slotsPerRow[i]];
				for (int j = 0; j < slotsPerRow[i]; j++)
					slots[i][j] = other.slots[i][j];
			}
			else
				slots[i] = nullptr;
		}
		return *this;
	}

	//Move Assignment
	ParkingBlock& operator = (ParkingBlock&& other)
	{
		if (this == &other)
			return *this;

		for (int i = 0; i < totalRows; i++)
			delete[] slots[i];
		delete[] slots;
		delete[] slotsPerRow;

		slots = other.slots;
		slotsPerRow = other.slotsPerRow;
		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;

		other.slots = nullptr;
		other.slotsPerRow = nullptr;
		other.totalRows = 0;

		return *this;
	}

	//Setter functions
	void setCoordinates(float x, float y)
	{
		x_coordinate = x;
		y_coordinate = y;
	}

	float getX()
	{
		return x_coordinate;
	}

	float getY()
	{
		return y_coordinate;
	}

	int getRows()
	{
		return totalRows;
	}

	int getSlotsPerRow(int row)
	{
		return slotsPerRow[row];
	}

	string getSlotValue(int row, int col)
	{
		return slots[row][col];
	}

	void addRows(int n)
	{
		string** tempSlots = new string * [totalRows + n];
		int* tempSlotsPerRow = new int[totalRows + n];
		for (int i = 0;i < totalRows;i++)
		{
			tempSlots[i] = slots[i];
			tempSlotsPerRow[i] = slotsPerRow[i];
		}
		for (int i = totalRows;i < totalRows + n;i++)
		{
			tempSlots[i] = nullptr;
			tempSlotsPerRow[i] = 0;
		}

		delete[]slots;
		delete[]slotsPerRow;
		slots = tempSlots;
		slotsPerRow = tempSlotsPerRow;
		totalRows = totalRows + n;
	}


	void addSlots(int row, int n)
	{
		if (row < 0 || row >= totalRows)
			return;
		if (slots[row] != nullptr)
			delete[] slots[row];
		slots[row] = new string[n];
		slotsPerRow[row] = n;
		for (int i = 0;i < n;i++)
		{
			slots[row][i] = "EMPTY";
		}
	}

	void parkCar(int row, int slot, string vehicleNumber)
	{
		if (row < 0 || row >= totalRows)
		{
			cout << "Invalid Row Number!" << endl;
			return;
		}

		if (slot < 0 || slot >= slotsPerRow[row])
		{
			cout << "Invalid Slot Number!" << endl;
			return;
		}

		if (slots[row][slot] == "EMPTY")
		{
			slots[row][slot] = vehicleNumber;
			cout << "Car Parked Successfully!" << endl;
		}

		else
		{
			cout << "The slot is not Empty!" << endl;
		}

	}

	void removeCar(int row, int slot)
	{
		if (row < 0 || row >= totalRows)
		{
			cout << "Invalid Row Number!" << endl;
			return;
		}

		if (slot < 0 || slot >= slotsPerRow[row])
		{
			cout << "Invalid Slot Number!" << endl;
			return;
		}

		if (slots[row][slot] == "EMPTY")
			cout << "Slot is already EMPTY! " << endl;
		else
		{
			slots[row][slot] = "EMPTY";
			cout << "Car Removed Successfully!" << endl;
		}

	}

	void displayBlock()
	{
		cout << "Coordinates (" << x_coordinate << "," << y_coordinate << ")" << endl;
		for (int i = 0;i < totalRows;i++)
		{
			cout << "     Row " << i << endl;
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				if (j == 0)
					cout << "       ";
				cout << "  Slot " << j << " [" << slots[i][j] << "]  ";
			}
			cout << endl;
		}
	}

	void resizeSlots(int row, int newSize)
	{
		if (row < 0 || row >= totalRows)
		{
			cout << "Invalid Row Number!" << endl;
			return;
		}
		if (newSize > 0)
		{
			if (newSize > slotsPerRow[row])
			{
				string* temp = new string[newSize];
				for (int i = 0;i < slotsPerRow[row];i++)
					temp[i] = slots[row][i];
				for (int i = slotsPerRow[row];i < newSize;i++)
					temp[i] = "EMPTY";
				delete[]slots[row];
				slots[row] = temp;
				slotsPerRow[row] = newSize;
				cout << "Slots resized Successfully!" << endl;
			}

			if (newSize < slotsPerRow[row])
			{
				bool flag = true;
				for (int i = newSize;i < slotsPerRow[row];i++)
				{
					if (slots[row][i] != "EMPTY")
						flag = false;
				}
				if (flag)
				{
					string* temp = new string[newSize];
					for (int i = 0;i < newSize;i++)
					{
						temp[i] = slots[row][i];
					}
					delete[]slots[row];
					slots[row] = temp;
					slotsPerRow[row] = newSize;
					cout << "Slots resized Successfully!" << endl;

				}
				else
				{
					cout << "Operation Aborted! The following occupied slots will be lost :" << endl;
					for (int i = newSize;i < slotsPerRow[row];i++)
						cout << "  Slot " << i << " [" << slots[row][i] << "]  ";
					cout << endl;
					cout << "No changes made!" << endl;
				}

			}
		}
		else
			cout << "New Size should be Positive!" << endl;
	}

	int* searchVehicle(string vehicleNumber)
	{
		int* index = new int[2];
		for (int i = 0;i < totalRows;i++)
		{
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				if (slots[i][j] == vehicleNumber)
				{
					index[0] = i;
					index[1] = j;
					return index;

				}
			}
		}
		return nullptr;
	}

	void emptyRow(int row)
	{
		// No copying or moving happens here.
		// We are just changing the values inside the same object.
		// We are working on the same objects memory.
		// if someone passed a ParkingBlock by value to a function,
		// and that function called emptyRow(), then the Copy Constructor
		// would have been called at the time of passing, not here.
		if (row < 0 || row >= totalRows)
		{
			cout << "Invalid Row Number!" << endl;
			return;
		}
		for (int i = 0;i < slotsPerRow[row];i++)
			slots[row][i] = "EMPTY";
		cout << "Row " << row << " cleared successfully!" << endl;
	}

	void emptyBlock()
	{
		// No copying or moving happens here either.
		// We are just calling emptyRow() on the same object, no new object is created.
		// But if this function were ever called on a temporary object,
		// the Move Constructor would have been called to create that temporary.

		for (int i = 0;i < totalRows;i++)
			emptyRow(i);
	}

	void transferVehicles(ParkingBlock& source)
	{

		//Copy Constructor is most efficient here. 
		//We have freed the old memory and deep copied data from source to destination.
		for (int i = 0;i < totalRows;i++)
			delete[]slots[i];
		delete[]slots;
		delete[]slotsPerRow;

		totalRows = source.totalRows;
		slots = new string * [totalRows];
		slotsPerRow = new int[totalRows];

		for (int i = 0;i < totalRows;i++)
		{

			slotsPerRow[i] = source.slotsPerRow[i];
		}

		for (int i = 0;i < totalRows;i++)
		{
			slots[i] = new string[slotsPerRow[i]];
			for (int j = 0;j < slotsPerRow[i];j++)
				slots[i][j] = source.slots[i][j];
		}
		cout << "Vehicles transferred successfully!" << endl;
	}

	void mergeVehicles(ParkingBlock& source)
	{
		if (source.totalRows > totalRows)
		{
			int oldTotal = totalRows;
			int extraRows = source.totalRows - totalRows;
			addRows(extraRows);
			for (int i = oldTotal; i < source.totalRows; i++)
				if (source.slotsPerRow[i] > 0)
					addSlots(i, source.slotsPerRow[i]);
		}
		for (int i = 0; i < source.totalRows; i++)
		{
			for (int j = 0; j < source.slotsPerRow[i]; j++)
			{
				if (source.slots[i][j] == "EMPTY")
					continue;

				string vehicle = source.slots[i][j];

				bool placed = false;
				for (int k = 0; k < slotsPerRow[i]; k++)
				{
					if (slots[i][k] == "EMPTY")
					{
						slots[i][k] = vehicle;
						placed = true;
						break;
					}
				}
				if (!placed)
				{
					resizeSlots(i, slotsPerRow[i] + 1);
					slots[i][slotsPerRow[i] - 1] = vehicle;
				}
			}
		}
		cout << "Vehicles merged successfully! ." << endl;
	}

};

void loadParkingLot(string filename, ParkingBlock*& blocks, int& numBlocks)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "File could not be opened!" << endl;
		return;
	}
	file >> numBlocks;
	blocks = new ParkingBlock[numBlocks];

	for (int i = 0; i < numBlocks; i++)
	{
		int numRows;
		file >> numRows;
		blocks[i].addRows(numRows);

		for (int j = 0; j < numRows; j++)
		{
			int numSlots;
			file >> numSlots;
			blocks[i].addSlots(j, numSlots);
		}
	}
	file.close();
	cout << "Parking Layout Loaded Successfully!" << endl;
}

void loadBlockCoordinates(string filename, ParkingBlock* blocks, int totalBlocks)
{
	float x, y;
	ifstream file(filename);
	if (!file.is_open())
	{

		cout << "File could not be opened!" << endl;
		return;
	}


	for (int i = 0;i < totalBlocks;i++)
	{
		file >> x;
		file >> y;
		blocks[i].setCoordinates(x, y);

	}
	cout << "Coordinates loaded successfully!" << endl;
}

void smartAllocate(string vehicleNumber, int desiredBlockIndex, ParkingBlock* blocks, int numBlocks)
{
	double minDistance = -1;
	int bestSlot = -1;
	int bestRow = -1;
	int bestBlock = -1;
	float x = blocks[desiredBlockIndex].getX();
	float y = blocks[desiredBlockIndex].getY();


	for (int i = 0;i < numBlocks;i++)
	{

		for (int j = 0;j < blocks[i].getRows();j++)
		{
			for (int k = 0;k < blocks[i].getSlotsPerRow(j);k++)
			{

				if (blocks[i].getSlotValue(j, k) == "EMPTY")
				{
					float slotX = blocks[i].getX() + (k * 8);
					float slotY = blocks[i].getY() + (j * 16);
					double distance = sqrt(pow(slotX - x, 2) + pow(slotY - y, 2));
					if (minDistance == -1 || distance < minDistance)
					{
						minDistance = distance;
						bestBlock = i;
						bestRow = j;
						bestSlot = k;
					}
				}
			}

		}
	}
	if (bestBlock != -1)
	{
		blocks[bestBlock].parkCar(bestRow, bestSlot, vehicleNumber);

		cout << "Vehicle parked at Block "
			<< bestBlock << " Row "
			<< bestRow << " Slot "
			<< bestSlot << endl;
	}
	else
	{
		cout << "No empty slot found!" << endl;
	}
}


int main()
{
	ParkingBlock* blocks = nullptr;
	int numBlocks = 0;
	bool flag = 1;
	int choice;

	while (flag)
	{
		cout << "------------MENU------------" << endl;
		cout << " 0. Initialize: load from file or enter layout manually at runtime" << endl
			<< " 1. Park a vehicle" << endl
			<< " 2. Remove a vehicle" << endl
			<< " 3. Display full parking system" << endl
			<< " 4. Resize slots in a row" << endl
			<< " 5. Search for a vehicle" << endl
			<< " 6. Empty a row" << endl
			<< " 7. Empty a block" << endl
			<< " 8. Transfer vehicles between blocks" << endl
			<< " 9. Smart allocate a vehicle" << endl
			<< " 10. Load block coordinates from file" << endl
			<< " 11. Merge vehicles into a block" << endl
			<< " 12. Exit" << endl;
		cout << "----------Enter Your Choice-----------" << endl;
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number: ";
		}

		if (choice == 0)
		{
			int option;
			cout << "Option 1: Enter the layout Manually" << endl;
			cout << "Option 2: Load from file" << endl;
			cout << "Choose your option :";
			cin >> option;

			if (option == 1)
			{
				cout << "Enter Number of Blocks :";
				cin >> numBlocks;

				blocks = new ParkingBlock[numBlocks];

				for (int i = 0;i < numBlocks;i++)
				{
					int numRows;
					cout << "Enter Number of Rows for Block " << i << " :";
					cin >> numRows;
					blocks[i].addRows(numRows);
					for (int j = 0; j < numRows; j++)
					{
						int numSlots;
						cout << "  Enter Slots for Block " << i << ", Row " << j << ": ";
						cin >> numSlots;

						blocks[i].addSlots(j, numSlots);
					}
				}
			}

			if (option == 2)
			{
				string filename = "blocks.txt";
				loadParkingLot(filename, blocks, numBlocks);
			}

		}

		else if (choice == 1)
		{
			if (blocks == nullptr)
			{
				cout << "Blocks have not been initialized yet!" << endl;
				continue;
			}
			int row, slot, blockIndex;
			string vehicleNum;
			cout << "Enter the Block Number (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			cout << "Enter the row :";
			cin >> row;
			cout << "Enter the slot :";
			cin >> slot;
			cout << "Enter the Vehicle Number :";
			cin >> vehicleNum;
			blocks[blockIndex].parkCar(row, slot, vehicleNum);
		}

		else if (choice == 2)
		{
			int blockIndex, row, slot;
			cout << "Enter the Block Number (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			cout << "Enter the row :";
			cin >> row;
			cout << "Enter the slot :";
			cin >> slot;
			blocks[blockIndex].removeCar(row, slot);

		}

		else if (choice == 3)
		{
			if (blocks == nullptr)
			{
				cout << "Blocks have not been initialized yet!" << endl;
				continue;
			}
			cout << "--------- Parking Layout--------- " << endl;
			for (int i = 0;i < numBlocks;i++)
			{
				cout << "Block " << i << endl;
				blocks[i].displayBlock();
			}
		}

		else if (choice == 4)
		{
			int blockIndex;
			cout << "Enter the Block Number (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			int row, newSize;
			cout << "Enter row Number that you want to resize :";
			cin >> row;
			cout << "Enter the new Size :";
			cin >> newSize;
			blocks[blockIndex].resizeSlots(row, newSize);
		}

		else if (choice == 5)
		{
			if (blocks == nullptr)
			{
				cout << "System not initialized!" << endl;
				continue;
			}
			int* Search = nullptr;
			int block = -1;
			string vehicleNumber;
			cout << "Enter vehicle Number :";
			cin >> vehicleNumber;
			for (int i = 0;i < numBlocks;i++)
			{
				Search = blocks[i].searchVehicle(vehicleNumber);
				if (Search != nullptr)
				{
					block = i;
					break;
				}

			}
			if (Search == nullptr)
			{
				cout << "Vehicle Not Found!" << endl;

			}
			else
			{
				cout << "Vehicle found at Block " << block << " Row " << Search[0] << " Slot " << Search[1] << endl;
			}
			delete[]Search;
		}

		else if (choice == 6)
		{
			if (blocks == nullptr)
			{
				cout << "Blocks have not been initialized yet!" << endl;
				continue;
			}
			int blockIndex;
			cout << "Enter the Block Number (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			int row;
			cout << "Enter Row number that you want to Empty :";
			cin >> row;

			blocks[blockIndex].emptyRow(row);
		}

		else if (choice == 7)
		{
			if (blocks == nullptr)
			{
				cout << "Blocks have not been initialized yet!" << endl;
				continue;
			}
			int blockIndex;
			cout << "Enter the Block Number that you want to EMPTY (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			blocks[blockIndex].emptyBlock();
			cout << "Block " << blockIndex << " Emptied successfully!" << endl;
		}

		else if (choice == 8)
		{
			if (blocks == nullptr)
			{
				cout << "System not initialized!" << endl;
				continue;
			}
			int blockIndex;
			cout << "Enter the Destination Block (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}

			int source;
			cout << "Ënter the Source Block : (0 to " << numBlocks - 1 << "): ";
			cin >> source;

			if (source < 0 || source >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}

			if (source == blockIndex)
			{
				cout << "Source and Destination cannot be same!" << endl;
				continue;
			}

			blocks[blockIndex].transferVehicles(blocks[source]);

		}

		else if (choice == 9)
		{
			if (blocks == nullptr)
			{
				cout << "System not initialized!" << endl;
				continue;
			}
			string vehNum;
			int desiredBlockIndex;
			cout << "Enter desired Block (0 to " << numBlocks - 1 << "): ";
			cin >> desiredBlockIndex;
			if (desiredBlockIndex < 0 || desiredBlockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}
			cout << "Enter Vehicle Number :";
			cin >> vehNum;
			smartAllocate(vehNum, desiredBlockIndex, blocks, numBlocks);
		}

		else if (choice == 10)
		{
			if (blocks == nullptr)
			{
				cout << "System not initialized!" << endl;
				continue;
			}
			string filename = "coordinates.txt";
			loadBlockCoordinates(filename, blocks, numBlocks);
		}

		else if (choice == 11)
		{
			if (blocks == nullptr)
			{
				cout << "System not initialized!" << endl;
				continue;
			}
			int blockIndex;
			cout << "Enter the Destination Block (0 to " << numBlocks - 1 << "): ";
			cin >> blockIndex;

			if (blockIndex < 0 || blockIndex >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}

			int source;
			cout << "Ënter the Source Block : (0 to " << numBlocks - 1 << "): ";
			cin >> source;

			if (source < 0 || source >= numBlocks)
			{
				cout << "Invalid Block Number!" << endl;
				continue;
			}

			if (source == blockIndex)
			{
				cout << "Source and Destination cannot be same!" << endl;
				continue;
			}

			blocks[blockIndex].mergeVehicles(blocks[source]);
		}

		else if (choice == 12)
		{
			flag = 0;
		}

		else
		{
			cout << "Invalid choice! " << endl;
		}

	}
	delete[] blocks;
	return 0;

}