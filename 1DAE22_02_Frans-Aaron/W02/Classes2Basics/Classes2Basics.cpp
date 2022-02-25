// Frans Aaron 1DAE22
#include "pch.h"
#include "Time.h"
#include "Square.h"
#include "Container.h"
#include <iostream>

#pragma region Funcs
void TestSquares();
void CompareTimes(const Time* t1, const Time* t2);
void PrintInstanceCntr(const std::string& message);
void TestContainer();
void PrintContainer(const Container* pContainer);
#pragma endregion



int main()
{
    //TestSquares();

    //PrintInstanceCntr("Nr of Time Objects->");
    //Time* t1{ new Time(30000) };
    //Time* t2{ new Time(30001) };
    //CompareTimes(t1, t2);
    //PrintInstanceCntr("Nr of Time Objects->");
    //delete t1;
    //t1 = nullptr;
    //delete t2;
    //t2 = nullptr;
    //PrintInstanceCntr("Nr of Time Objects->");

	TestContainer();

}

void TestSquares()
{
    Square* sq1{ new Square(20) };

    sq1->Print();

    std::cout << '\n';

    Square* sq2{ new Square(20, 10, 5) };

    sq2->Print();

    delete sq1;
    sq1 = nullptr;
    delete sq2;
    sq2 = nullptr;

    std::cout << '\n';
}

void CompareTimes(const Time* t1, const Time* t2)
{
    t1->Print();

    std::cout << '\n';

    t2->Print();
    std::cout << '\n';

    t1->GetSeconds() == t2->GetSeconds() ? 
        std::cout << "Equal" :
        std::cout << "Not Equal";

    std::cout << '\n';
}

void PrintInstanceCntr(const std::string& message)
{
    std::cout << message << Time::GetNrInstances();

    std::cout << '\n';
}

void TestContainer()
{
	std::cout << "\n-- Container tests --\n";
	// Define a Container object
	const int cap{ 5 };
	std::cout << "Create container with capacity of " << cap << " elements\n";
	Container* pContainer{ new Container{cap} };
	PrintContainer(pContainer);

	// Add some values to the container
	int actNr{ 0 };
	std::cout << "\nPush back of " << (cap - 1) << " elements\n";
	for (int idx{ 1 }; idx < cap; ++idx)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);

	std::cout << "\nChange the value of the elements (using Set)\n";
	for (int idx{ 0 }; idx < actNr; ++idx)
	{
		pContainer->Set(idx, rand() % 21);
	}
	PrintContainer(pContainer);

	std::cout << "\nPush back another " << (cap - 1) << " elements\n";
	for (int i{ 1 }; i < cap; ++i)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);
	delete pContainer;
}

void PrintContainer(const Container* pContainer)
{
	std::cout << "-- Print container --\n";
	std::cout << "   Capacity: " << pContainer->Capacity() << std::endl;
	std::cout << "   Size: " << pContainer->Size() << std::endl;
	std::cout << "   Get the elements (using Get and Size)\n   ";
	for (int idx{ 0 }; idx < pContainer->Size(); ++idx)
	{
		std::cout << pContainer->Get(idx) << " ";
	}
	std::cout << std::endl;
}


