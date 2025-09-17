#include <iostream>
#include <string>
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
        cin.ignore();
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

    float getAvgSpeed() {
        return (float)distance_km / time_hrs;
    }
};

class Passenger : public Train {
protected:
    string name, from, to;
    int age, seatNo;
    static int seatCounter, pnrNo;

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
int Passenger::pnrNo = 25090800;

void Passenger::getPNR() {
    ++pnrNo;
    cout << "Your PNR No. is: " << pnrNo << endl;
}
class Ticket : public Passenger {
private:
    string travelClass;
    float fare;
    bool confirmed;

public:
    Ticket() : Passenger() {
        travelClass = "Sleeper";
        fare = 0.0;
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
        float baseRate= (travelClass == "AC") ? 2.0 : 1.0;
        fare = distance_km * baseRate;
    }

    void displayTicket() {
        cout << "Class: " << travelClass << " | Fare:" << fare
             << " | Status: " << (confirmed ? "Confirmed" : "Pending") << endl;
    }
};


int main() {
    int choice;
    int n;
    cout << "Enter number of passengers: ";
    cin >> n;

    Ticket t1[50];

    do {
        cout << "\n========= RAILWAY MANAGEMENT MENU =========\n";
        cout << "1. Add Train Details\n";
        cout << "2. Add Passenger(s)\n";
        cout << "3. Display Train Details\n";
        cout << "4. Display Passenger Details\n";
        cout << "5. Book Ticket\n";
        cout << "6. Display Ticket\n";
        cout << "7. Exit\n";
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
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
