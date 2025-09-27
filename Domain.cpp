#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Train {
protected:
    string train_id;
    string train_name;
    string source_station;
    string destination_station;
    int distance_km;
    int time_hrs;

public:
    Train() {
        train_id = "12050";
        train_name = "Gatiman Express";
        source_station = "Delhi";
        destination_station = "Agra";
        distance_km = 195;
        time_hrs = 3;
    }

    Train(string id, string name, string source, string dest, int dist, int time) {
        train_id = id;
        train_name = name;
        source_station = source;
        destination_station = dest;
        distance_km = dist;
        time_hrs = time;
    }

    void getTrainData() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Train ID: ";
        getline(cin, train_id);
        cout << "Enter Train Name: ";
        getline(cin, train_name);
        cout << "Enter Source Station: ";
        getline(cin, source_station);
        cout << "Enter Destination Station: ";
        getline(cin, destination_station);
        cout << "Enter Distance (in km): ";
        cin >> distance_km;
        cout << "Enter Duration (in hrs): ";
        cin >> time_hrs;
    }

    void displayTrain() {
        cout << "\n========== TRAIN SUMMARY ==========\n";
        cout << "Train ID        : " << train_id << endl;
        cout << "Train Name      : " << train_name << endl;
        cout << "Route           : " << source_station << " <> " << destination_station << endl;
        cout << "Distance        : " << distance_km << " km" << endl;
        cout << "Duration        : " << time_hrs << " hrs" << endl;
    }

    friend float getAvgSpeed(const Train& t);

    Train operator+(const Train& other) {
        Train merged;
        merged.train_id = train_id + "-" + other.train_id;
        merged.train_name = train_name + " & " + other.train_name;
        merged.source_station = source_station;
        merged.destination_station = other.destination_station;
        merged.distance_km = distance_km + other.distance_km;
        merged.time_hrs = time_hrs + other.time_hrs;
        return merged;
    }
};

float getAvgSpeed(const Train& t) {
    if (t.time_hrs == 0) return 0.0f;
    return static_cast<float>(t.distance_km) / t.time_hrs;
}

class Passenger : public Train {
protected:
    string name, from, to;
    int age, seatNo;
    static int seatCounter;
    static int PNRNo;

public:
    Passenger() : Train() {
        name = "--";
        age = 0;
        from = "--";
        to = "--";
        seatNo = 0;
    }

    void addPassenger() {
        cout << "Enter passenger name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter from station: ";
        cin >> from;
        cout << "Enter to station: ";
        cin >> to;
        allotSeat();
        getPNR();
    }

    void displayPassenger() {
        cout << "Seat no: " << seatNo << " | Name: " << name << " | Age: " << age
             << " | From: " << from << " | To: " << to << endl;
    }

    void allotSeat() {
        seatNo = ++seatCounter;
    }

    static void getPNR();
};

int Passenger::seatCounter = 0;
int Passenger::PNRNo = 25090800;

void Passenger::getPNR() {
    ++PNRNo;
    cout << "Your PNR No. is: " << PNRNo << endl;
}

class Ticket : public Passenger {
private:
    string travelClass;
    float fare;
    bool confirmed;

public:
    Ticket() : Passenger() {
        travelClass = "Sleeper";
        fare = 0.0f;
        confirmed = false;
    }

    void getTicket() {
        cout << "Enter travel class: ";
        cin >> travelClass;
        calculateFare();
        confirmed = true;
        cout << "Ticket confirmed.\n";
    }

    void calculateFare() {
        float baseRate = (travelClass == "AC") ? 2.0f : 1.0f;
        fare = distance_km * baseRate;
    }

    void displayTicket() {
        cout << "Class: " << travelClass << " | Fare: " << fare
             << " | Status: " << (confirmed ? "Confirmed" : "Pending") << endl;
    }
};

int main() {
    int choice;
    int n;
    cout << "Enter number of passengers: ";
    cin >> n;

    if (n < 1 || n > 50) {
        cout << "please enter a number between 1 and 50\n";
        return 0;
    }

    Ticket t1[50];

    do {
        cout << "\n========= RAILWAY MANAGEMENT MENU =========\n";
        cout << "1. Add Train Details\n";
        cout << "2. Add Passenger(s)\n";
        cout << "3. Display Train Details\n";
        cout << "4. Display Passenger Details\n";
        cout << "5. Book Ticket\n";
        cout << "6. Display Ticket\n";
        cout << "7. Combine Trains\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                t1[0].getTrainData();
                cout << "Details entered successfully...\n";
                break;

            case 2:
                for (int i = 0; i < n; i++) {
                    cout << "\n--- Enter details for Passenger " << i + 1 << ":\n";
                    t1[i].addPassenger();
                    cout << "Details entered successfully...\n";
                }
                break;

            case 3:
                t1[0].displayTrain();
                break;

            case 4:
                cout << "\n========== PASSENGER DETAILS ==========\n";
                for (int i = 0; i < n; i++) {
                    t1[i].displayPassenger();
                }
                break;

            case 5:
                for (int i = 0; i < n; i++) {
                    cout << "\n=========== TICKET BOOKING ===========\n" << i + 1 << ":\n";
                    t1[i].getTicket();
                }
                break;

            case 6:
                cout << "\n========== TICKET DETAILS ==========\n";
                for (int i = 0; i < n; i++) {
                    t1[i].displayTicket();
                }
                break;

            case 7:
                if (n >= 2) {
                    cout << "\nJoint Train Details: \n";
                    Train combined = t1[0] + t1[1];
                    combined.displayTrain();
                    cout << "Average speed of combined train: " << getAvgSpeed(combined) << " km/hr\n";
                } else {
                    cout << "Need at least 2 passengers (and thus 2 train objects) to demonstrate combine.\n";
                }
                break;

            case 8:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
