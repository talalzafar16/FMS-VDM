#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <chrono>
#include <array>
#include <stdlib.h>
#include <random>
using namespace std;
using namespace std::chrono;

 time_t current_time = time(0);
    
std::array<std::tuple<int, int, std::string, std::string,time_t,time_t,int>, 4> arrayOfTuples = {
        std::make_tuple(1, 1, "ali", "7897", current_time, current_time, 0),
        std::make_tuple(2, 0, "", "", current_time, current_time, 0),
        std::make_tuple(3, 0, "", "", current_time, current_time, 0),
        std::make_tuple(4, 0, "", "", current_time, current_time, 0),
    };

class ParkFlow {
private:
    int SlotNo, SessionNo;
    int ParkflowBothType;
    string name;
    string Vn;

public:

    void CheckParkflowBothType() {
        int type;
        cout << "Enter Booth Type" << endl;
        cout << "Enter 1 for entry" << endl;
        cout << "Enter 2 for exit" << endl;
        cout << "Enter 0 to Close" << endl;
        cin >> type;
        ParkflowBothType = type;
    }

    void displaySlots() {
        for (auto& [first, second, name, number,entryTime,exitTime,fees] : arrayOfTuples) {
            std::cout << "Space " << first;
            if (second == 0) {
                cout << " Is Free" << endl;
            }
            else {
                cout << " Is Occupied By Mr." << name << " with vehical number" << number << endl;
            }
        }
    }
void printSlip() {
        for (auto& [first, second, name, number,entryTime,exitTime,fees] : arrayOfTuples) {
            if (name==this->name) {
                cout <<"Dear Mr. "<<name<<endl<< "You have Booked parking slot number "<<first<<" for your car with number "<<number << endl;
                cout <<"And Your Session Number is "<<second << endl;
                cout <<"Entry Time :- "<<entryTime << endl;
                 cout << "You Space is Reserved Go And Park" << endl;
                break;
            }
            
        }
    }
    void GetEntryData() {
        cout << "Enter Details" << endl;
        cout << "Enter Name" << endl;
        cin >> name;
        cout << "Enter VehicleNumber" << endl;
        cin >> Vn;
        displaySlots();
    }
void GetExitData() {
        cout << "Enter Details" << endl;
        cout << "Enter Session Number" << endl;
        cin >> SessionNo;
        AuthenticateSession();
    }
 int CalculateFees(time_t enterTime,time_t exitTime){
     int rate=20;
         return  std::difftime(exitTime, enterTime)*rate; 


 }   
 void PayAmount(int fees){
     int number;
     cout<<"Enter Card Number"<<endl;
     cin>>number;
     cout<<"Amount "<<fees<<"Rs has been deducted from your account "<<number<<endl;
     cout<<"Thank you for parking"<<endl;
 }
void AuthenticateSession(){
    for (auto& [first, second, name, number,entryTime,exitTime,fees] : arrayOfTuples) {
            if (second == SessionNo) {

    exitTime = time(0);
                fees=CalculateFees(entryTime,time(0));
                cout<<"your amount is Rs"<<fees<<endl;
                PayAmount(fees);
                break;
            }

        }
}
    void allotSpaces() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100);
        int ask;
        std::cout << "Select Avaliable Space" << endl;
        cin >> ask;

        for (auto& [first, second, name, number,entryTime,exitTime,fees] : arrayOfTuples) {
            if (ask == first && second != 0) {
                cout << " Is Occupied By " << name << endl;
                allotSpaces();
            }
            if (ask == first && second == 0) {
                second = dist(gen);
                name = this->name;
                number = this->Vn;
                entryTime = time(0);

    // entryTime=ctime(&currentTime);

                printSlip();
                break;
            }
        }

        
    }

    int GetParkflowBothType() {
        return ParkflowBothType;
    }

};
class ParkFlowTest {
public:
    void testCalculateFees() {
        ParkFlow pf;
        time_t enterTime = time(0);
        time_t exitTime = enterTime + 600; // 10 minutes later
        int expectedFees = 20 * std::difftime(exitTime, enterTime);
        int calculatedFees = pf.CalculateFees(enterTime, exitTime);
        if(calculatedFees == expectedFees){
            cout<<"Fee Test Case Passed"<<endl;
        }else {
            cout << "Fee Test Case  Failed" << endl;
            cout << "Expected: " << expectedFees << ", Actual: " << calculatedFees << endl;
        }
    }
    void testAllotSpaces() {
        ParkFlow pf;
        // booth type ==1 
        pf.CheckParkflowBothType();
        // Wnterentry details
        pf.GetEntryData();
        // Run the allotSpaces function
        pf.allotSpaces();

        cout << "Test AllotSpaces Passed" << endl;
    }
    void testAuthenticateSession() {
        ParkFlow pf;
        // Set up an occupied slot
        pf.CheckParkflowBothType(); // Simulate user input for booth type (1 for entry)
        pf.GetEntryData(); // Simulate user input for entry details
        // Simulate user input for booth type (2 for exit)
        pf.CheckParkflowBothType();
        
        // Run the AuthenticateSession function
        pf.AuthenticateSession();

        // Print test result
        cout << "Test AuthenticateSession Passed" << endl;
    }
    
    void runAllTests() {
        testCalculateFees();
         testAllotSpaces();
        testAuthenticateSession();
    }
};
int main() {
    // Test Cases
    ParkFlowTest TestObj;
    // TestObj.testCalculateFees();
    TestObj.runAllTests();
    
    
    // ParkFlow ClassObj;

    // while(ClassObj.GetParkflowBothType()){
    // ClassObj.CheckParkflowBothType();
        
    // if (ClassObj.GetParkflowBothType() == 1) {
    //     ClassObj.GetEntryData();
    //     ClassObj.allotSpaces();
    // }else if(ClassObj.GetParkflowBothType() == 2){
    //     ClassObj.GetExitData();
    // }else if(ClassObj.GetParkflowBothType() == 0){
    //     break;
    // }else{
    //     cout<<"Choose Correct Options"<<endl;
    // }}
    return 0;
}
