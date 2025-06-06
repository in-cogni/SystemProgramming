﻿#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <thread>

using std::cin;
using std::cout;
using std::endl;
using namespace std::chrono_literals;

#define Enter 13
#define Escape    27

#define MIN_TANK_CAPACITY 20
#define MAX_TANK_CAPACITY 120


class Tank
{
	double fuel_level;
public:
	const int CAPACITY;
	double get_fuel_level()const
	{
		return fuel_level;
	}
	Tank(int capacity):CAPACITY
	(
		capacity<MIN_TANK_CAPACITY?MIN_TANK_CAPACITY:
		capacity>MAX_TANK_CAPACITY?MAX_TANK_CAPACITY:
		capacity
	),
		fuel_level(0)
	{
		cout << "Tank:";
			if (capacity < MIN_TANK_CAPACITY)cout << "Min capacity was applied" << endl;
			if (capacity > MAX_TANK_CAPACITY)cout << "Max capacity was applied" << endl;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}
	double fill(double amount)
	{
		if (amount < 0)return fuel_level;
		fuel_level += amount;
		if (fuel_level >= CAPACITY)
		{
			fuel_level = CAPACITY;
			cout << "Full Tank" << endl;
		}
		return fuel_level;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	void info()const
	{
		cout << "Capacity:\t" << CAPACITY << " liters.\n";
		cout << "Fuel level:\t" << fuel_level << " liters.\n";
	}
};
#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 25
class Engine
{
	const double CONSUMPTION;//расход на 100 км
	const double DEFAULT_CONSUMPTION_PER_SECOND;
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	Engine(double consumption):
		CONSUMPTION
	    (
			consumption < MIN_ENGINE_CONSUMPTION? MIN_ENGINE_CONSUMPTION:
			consumption >MAX_ENGINE_CONSUMPTION?MAX_ENGINE_CONSUMPTION:
			consumption
		),
		DEFAULT_CONSUMPTION_PER_SECOND(CONSUMPTION*3e-5),
		consumption_per_second(DEFAULT_CONSUMPTION_PER_SECOND)
	{
		is_started = false;
		cout << "Engine is ready\n";
	}
	~Engine()
	{
		cout << "Engine is over\n";
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info()const
	{
		cout << "Consumpiton: " << CONSUMPTION << " liters/100km\n";
		cout << "Default Consumpiton: " << DEFAULT_CONSUMPTION_PER_SECOND << " liters/s\n";
		cout << "Consumption: " << consumption_per_second << " liters/s\n";
	}
};

#define MAX_SPEED_LOWER_LIMIT 130
#define MAX_SPEED_HIGHER_LIMIT 408

class Car
{
	Engine engine;
	Tank tank;
	int speed;
	int accelaretion;
	const int MAX_SPEED;
	bool driver_inside;
	struct
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
	}threads_container;//Эта структура не имеет имени и реализует только 1 экземпляр.

public:
	Car(double consumption, int capacity, int max_speed = 250, int accelaretion = 10) :
		MAX_SPEED
		(
			max_speed<MAX_SPEED_LOWER_LIMIT ? MAX_SPEED_LOWER_LIMIT :
			max_speed>MAX_SPEED_HIGHER_LIMIT ? MAX_SPEED_HIGHER_LIMIT :
			max_speed
		),
		engine(consumption),
		tank(capacity),
		speed(0),
		accelaretion(accelaretion)
	{
		driver_inside = false;
		cout << "Your car is ready to go, press 'Enter' to get in ;-)\n";
	}
	~Car()
	{
		cout << "The car is over\n";
	}
	void get_in()
	{
		driver_inside = true;
		threads_container.panel_thread = std::thread(&Car::panel, this);
		//panel();
	}
	void get_out()
	{
		driver_inside = false;
		if (threads_container.panel_thread.joinable())
			threads_container.panel_thread.join();
		system("CLS");
		cout << "You are out of the Car\n";
	}
	void start()
	{
		if (tank.get_fuel_level())
		{
			engine.start();
			threads_container.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop()
	{
		engine.stop();
		if (threads_container.engine_idle_thread.joinable())
			threads_container.engine_idle_thread.join();
	}
	void accelerate()
	{
		if (driver_inside && engine.started())
		{
			speed += accelaretion;
			if (!threads_container.free_wheeling_thread.joinable())
				threads_container.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			std::this_thread::sleep_for(1s);
		}
	}
	void slow_down()
	{
		if (driver_inside && engine.started())
		{
			speed -= accelaretion;
			if (speed < 0) speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void control()
	{
		char key = 0;
		do
		{
			key = 0;
			if(_kbhit())key = _getch();
			switch (key)
			{
			case Enter:
				driver_inside ? get_out() : get_in();
				break;
			case 'F': case 'f':
				double fuel;
				cout << "Введите объем топлива: "; cin >> fuel;
				tank.fill(fuel);
				break;
			case 'I': case 'i'://Ignition
				if (driver_inside)!engine.started() ? start() : stop();
					break;
			case'W':case'w':
				accelerate();
				break;
			case'S':case's':
				slow_down();
				break;
			case Escape:
				stop();
				get_out();
			}
			if (tank.get_fuel_level() <= 0)stop();
			if (speed <= 0 && threads_container.free_wheeling_thread.joinable())
				threads_container.free_wheeling_thread.join();
		} while (key != Escape);
		//Concurent execution(одновременное выполнение)
	}
	void free_wheeling()
	{
		while (--speed > 0)
		{
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Fuel level: " << tank.get_fuel_level() << " liters\n";
			if (tank.get_fuel_level() < 5)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Engine is " << (engine.started() ? "started" : "stopped") << endl;
			cout << "Speed: " << speed << " km/h\n";
			/*fuel_consumption();*/
			Sleep(1000);
		}
	}

	void info()const
	{
		engine.info();
		tank.info();
		cout << "Speed:    " << speed << " km/h\n";
		cout << "MaxSpeed: " << MAX_SPEED << " km/h\n";
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef TANK_CHECK
	Tank tank(80);
	double fuel;
	do
	{
		cout << "На сколько заправляемся?"; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK

	Car bmw(10, 80, 270);
	//bmw.info();
	
	bmw.control();

	//Car car(80, 10);//80 - вмсетимость бака, 10 - расход л/100км
	//double fuel;
	//short choice;
	//do
	//{
	//	car.info();
	//	cout << "Выберите:\n";
	//	cout << "1 - заправиться\n";
	//	cout << "2 - запустить двигатель\n";
	//	cout << "3 - остановить двигатель\n";
	//	cout << "0 - выход\n";
	//	cin >> choice;
	//	if (choice == 1)
	//	{
	//		cout << "На сколько заправляемся?\n"; cin >> fuel;//
	//		car.fill(fuel);
	//	}
	//	else if (choice == 2)
	//	{
	//		car.start_engine();
	//	}
	//	else if (choice == 3)
	//	{
	//		car.stop_engine();
	//	}
	//	else if (choice == 0)
	//		return;
	//	else cout << "введено некорректое значение. повторите попытку\n";
	//} while (true);
	//
}