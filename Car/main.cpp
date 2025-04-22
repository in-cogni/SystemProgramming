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

//#define TANK_CHECK
//#define ENGINE_CHECK
//class Engine
//{
//	double consumption_100, comsumption_sec;
//	bool run;
//public:
//	Engine(double consumpiton) :consumption_100(consumpiton), comsumption_sec(consumpiton / 1000000 * 30)
//		//пояснение к comsumption_sec(consumpiton / 1000000 * 30): 
//		//сначала нашла скарость из условия домашки (Если расход 10л/100км, то расход за одну секунду будет 0.0003 л/c)
//		//по форуле: расх(л/с) = ( расх(л/100км) / 1000000 ) * скорость(м/с) => скорость = 30 м/с
//		//и далее можем посчитать любой расход в л/с, зная расход в л/100км
//	{
//		cout << "Engine is ready\n";
//	}
//	~Engine()
//	{
//		cout << "Engine is over\n";
//	}
//	void start()
//	{
//		run = true;
//		cout << "Engine is running\n";
//	}
//	void stop()
//	{
//		run = false;
//		cout << "Engine is stopped\n";
//	}
//	bool running() const
//	{
//		return run;
//	}
//	void info()const
//	{
//		cout << "\nEngine info:\n";
//		cout << "Consumption per 100 km:\t" << consumption_100 << " liters / 100 km\n";//расход л/100 км
//		cout << "Consumption per 1 sec:\t" << comsumption_sec << " liters / 1 sec\n";//расход л/с
//		cout << "Condition: "<< (running()?"running":"stopped") <<"\n";//состояние (запущен/остановлен)
//	}
//};
//
//class Car
//{
//	Tank tank;
//	Engine engine;
//public:
//	Car(int tank_capacity, double engine_consumption):tank(tank_capacity), engine(engine_consumption)
//	{
//		cout << "Car is ready\n";
//	}
//	~Car()
//	{
//		cout << "Car is over\n";
//	}
//	void fill(double amount)
//	{
//		tank.fill(amount);
//	}
//	void start_engine()
//	{
//		if (tank.get_fuel_level() > 0) engine.start();
//		else cout << "No fuel\n";
//	}
//	void stop_engine()
//	{
//		engine.stop();
//	}
//	void info() const
//	{
//		cout << "\n----Car info----\n";
//		tank.info();
//		engine.info();
//		cout << "\n-------------------\n\n";
//	}
//};

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