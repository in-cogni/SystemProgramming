#include <iostream>
using namespace std;

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
		//this->CAPACITY = capacity;
		//this->fuel_level = 0;
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
		cout << "\nTank info:\n";
		cout << "Capacity:\t" << CAPACITY << " liters.\n";
		cout << "Fuel level:\t" << fuel_level << " liters.\n";
	}
};

class Engine
{
	double consumption_100, comsumption_sec;
	bool run;
public:
	Engine(double consumpiton) :consumption_100(consumpiton), comsumption_sec(consumpiton / 1000000 * 30)
		//��������� � comsumption_sec(consumpiton / 1000000 * 30): 
		//������� ����� �������� �� ������� ������� (���� ������ 10�/100��, �� ������ �� ���� ������� ����� 0.0003 �/c)
		//�� ������: ����(�/�) = ( ����(�/100��) / 1000000 ) * ��������(�/�) => �������� = 30 �/�
		//� ����� ����� ��������� ����� ������ � �/�, ���� ������ � �/100��
	{
		cout << "Engine is ready\n";
	}
	~Engine()
	{
		cout << "Engine is over\n";
	}
	void start()
	{
		run = true;
		cout << "Engine is running\n";
	}
	void stop()
	{
		run = false;
		cout << "Engine is stopped\n";
	}
	bool running() const
	{
		return run;
	}
	void info()const
	{
		cout << "\nEngine info:\n";
		cout << "Consumption per 100 km:\t" << consumption_100 << " liters / 100 km\n";//������ �/100 ��
		cout << "Consumption per 1 sec:\t" << comsumption_sec << " liters / 1 sec\n";//������ �/�
		cout << "Condition: "<< (running()?"running":"stopped") <<"\n";//��������� (�������/����������)
	}
};

class Car
{
	Tank tank;
	Engine engine;
public:
	Car(int tank_capacity, double engine_consumption):tank(tank_capacity), engine(engine_consumption)
	{
		cout << "Car is ready\n";
	}
	~Car()
	{
		cout << "Car is over\n";
	}
	void fill(double amount)
	{
		tank.fill(amount);
	}
	void start_engine()
	{
		if (tank.get_fuel_level() > 0) engine.start();
		else cout << "No fuel\n";
	}
	void stop_engine()
	{
		engine.stop();
	}
	void info() const
	{
		cout << "\n----Car info----\n";
		tank.info();
		engine.info();
		cout << "\n-------------------\n\n";
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	/*Tank tank(80);
	double fuel;
	do
	{
		cout << "�� ������� ������������?"; cin >> fuel;
		tank.fill(fuel);
		tank.info();
	} while (true);*/

	Car car(80, 10);//80 - ����������� ����, 10 - ������ �/100��

	double fuel;
	short choice;

	do
	{
		car.info();

		cout << "��������:\n";
		cout << "1 - �����������\n";
		cout << "2 - ��������� ���������\n";
		cout << "3 - ���������� ���������\n";
		cout << "0 - �����\n";

		cin >> choice;

		if (choice == 1)
		{
			cout << "�� ������� ������������?\n"; cin >> fuel;
			car.fill(fuel);
		}
		else if (choice == 2)
		{
			car.start_engine();
		}
		else if (choice == 3)
		{
			car.stop_engine();
		}
		else if (choice == 0)
			return;
		else cout << "������� ����������� ��������. ��������� �������\n";
	} while (true);
	
}