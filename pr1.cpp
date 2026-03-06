#include <iostream>
using namespace std;

class Vehicle
{
protected:
    int vehicleID;
    char manufacturer[50];
    char model[50];
    int year;
    static int totalVehicles;

public:
    Vehicle()
    {
        vehicleID = 0;
        manufacturer[0] = '\0';
        model[0] = '\0';
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, char manu[], char mod[], int yr)
    {
        vehicleID = id;
        int i = 0;
        while (manu[i] != '\0')
        {
            manufacturer[i] = manu[i];
            i++;
        }
        manufacturer[i] = '\0';

        i = 0;
        while (mod[i] != '\0')
        {
            model[i] = mod[i];
            i++;
        }
        model[i] = '\0';

        year = yr;
        totalVehicles++;
    }

    virtual ~Vehicle()
    {
        totalVehicles--;
    }

    int getId() { return vehicleID; }

    virtual void display()
    {
        cout << "ID: " << vehicleID
             << ", Manufacturer: " << manufacturer
             << ", Model: " << model
             << ", Year: " << year;
    }

    static int getTotalVehicles()
    {
        return totalVehicles;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle
{
protected:
    char fuelType[20];

public:
    Car(int id, char manu[], char mod[], int yr, char fuel[]) : Vehicle(id, manu, mod, yr)
    {
        int i = 0;
        while (fuel[i] != '\0')
        {
            fuelType[i] = fuel[i];
            i++;
        }
        fuelType[i] = '\0';
    }

    void display() override
    {
        Vehicle::display();
        cout << ", Fuel Type: " << fuelType;
    }
};

class ElectricCar : public Car
{
protected:
    int batteryCapacity;

public:
    ElectricCar(int id, char manu[], char mod[], int yr, char fuel[], int battery)
        : Car(id, manu, mod, yr, fuel)
    {
        batteryCapacity = battery;
    }

    void display() override
    {
        Car::display();
        cout << ", Battery: " << batteryCapacity << " kWh";
    }
};

class Aircraft
{
protected:
    int flightRange;

public:
    Aircraft(int range = 0) { flightRange = range; }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar(int id, char manu[], char mod[], int yr, char fuel[], int range)
        : Car(id, manu, mod, yr, fuel), Aircraft(range) {}

    void display() override
    {
        Car::display();
        cout << ", Flight Range: " << flightRange << " km";
    }
};

class SportsCar : public ElectricCar
{
    int topSpeed;

public:
    SportsCar(int id, char manu[], char mod[], int yr, char fuel[], int battery, int speed)
        : ElectricCar(id, manu, mod, yr, fuel, battery)
    {
        topSpeed = speed;
    }

    void display() override
    {
        ElectricCar::display();
        cout << ", Top Speed: " << topSpeed << " km/h";
    }
};

class Sedan : public Car
{
public:
    Sedan(int id, char manu[], char mod[], int yr, char fuel[]) : Car(id, manu, mod, yr, fuel) {}

    void display() override
    {
        cout << "[Sedan] ";
        Car::display();
    }
};

class SUV : public Car
{
public:
    SUV(int id, char manu[], char mod[], int yr, char fuel[]) : Car(id, manu, mod, yr, fuel) {}

    void display() override
    {
        cout << "[SUV] ";
        Car::display();
    }
};

class VehicleRegistry
{
    Vehicle *vehicles[100];
    int count;

public:
    VehicleRegistry() { count = 0; }

    void addVehicle(Vehicle *v)
    {
        if (count < 100)
        {
            vehicles[count++] = v;
        }
        else
        {
            cout << "Registry full!\n";
        }
    }

    void displayAll()
    {
        if (count == 0)
        {
            cout << "No vehicles found.\n";
            return;
        }
        for (int i = 0; i < count; i++)
        {
            vehicles[i]->display();
            cout << endl;
        }
    }

    void searchById(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (vehicles[i]->getId() == id)
            {
                cout << "Vehicle Found: ";
                vehicles[i]->display();
                cout << endl;
                return;
            }
        }
        cout << "Vehicle with ID " << id << " not found.\n";
    }
};

int main()
{
    VehicleRegistry registry;
    int choice;

    do
    {
        cout << "\n====== Vehicle Registry Menu ======\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int type;
            cout << "Select Vehicle Type:\n";
            cout << "1. Car\n2. Electric Car\n3. Flying Car\n4. Sports Car\n5. Sedan\n6. SUV\n";
            cout << "Choice: ";
            cin >> type;

            int id, yr, battery, speed, range;
            char manu[50], mod[50], fuel[20];

            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Manufacturer: ";
            cin >> manu;
            cout << "Enter Model: ";
            cin >> mod;
            cout << "Enter Year: ";
            cin >> yr;

            switch (type)
            {
            case 1:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new Car(id, manu, mod, yr, fuel));
                break;

            case 2:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity: ";
                cin >> battery;
                registry.addVehicle(new ElectricCar(id, manu, mod, yr, fuel, battery));
                break;

            case 3:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Flight Range: ";
                cin >> range;
                registry.addVehicle(new FlyingCar(id, manu, mod, yr, fuel, range));
                break;

            case 4:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                cout << "Enter Battery Capacity: ";
                cin >> battery;
                cout << "Enter Top Speed: ";
                cin >> speed;
                registry.addVehicle(new SportsCar(id, manu, mod, yr, fuel, battery, speed));
                break;

            case 5:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new Sedan(id, manu, mod, yr, fuel));
                break;

            case 6:
                cout << "Enter Fuel Type: ";
                cin >> fuel;
                registry.addVehicle(new SUV(id, manu, mod, yr, fuel));
                break;

            default:
                cout << "Invalid choice!\n";
            }
        }
        else if (choice == 2)
        {
            registry.displayAll();
        }
        else if (choice == 3)
        {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            registry.searchById(id);
        }
        else if (choice == 4)
        {
            cout << "Exiting...\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
