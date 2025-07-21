#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Person {
public:
    string name;
    int age;
    string gender;
    string bloodType;

    bool inputdata() {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        if (age < 18 || age > 50) {
            cout << "Sorry, you are not eligible to donate organs." << endl;
            return false;
        }
        cout << "Enter Gender: ";
        getline(cin, gender);
        cout << "Choose Your Blood Type (A, A+, A-, B+, B-, AB+, AB-, O+, O-): ";
        while (true) {
            getline(cin, bloodType);
            if (bloodType == "A" or bloodType == "A+" or bloodType == "A-" or
                bloodType == "B+" or bloodType == "B-" or bloodType == "AB+" or
                bloodType == "AB-" or bloodType == "O+" or bloodType == "O-") {
                break;
            }
            cout << "Invalid Blood Type. Try again: ";
        }
        return true;
    }

    void displaydata() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Blood Type: " << bloodType << endl;
    }
};

class Donor : public Person {
public:
    string organType;

    bool inputdata() {
        if (!Person::inputdata()) 
        return false;
        cout << "Enter Organ Type (Heart, Kidney, Liver, Pancreas, Lungs, Xyz): ";
        while (true) {
            getline(cin, organType);
            for (char &c : organType) c = toupper(c);
            if (organType == "HEART" or organType == "KIDNEY" or organType == "LIVER" or
                organType == "PANCREAS" or organType == "LUNGS" or organType== "XYZ") 
                break;
            cout << "Invalid organ type. Try again: ";
        }
        return true;
    }

    void SaveDonorData() {
        ofstream myfile("Donor.txt", ios::app);
        if (myfile.is_open()) {
            myfile << name << endl;
            myfile << age << endl;
            myfile << gender << endl;
            myfile<< bloodType << endl;
            myfile << organType << endl;
            myfile << "=======================================\n";
            myfile.close();
        }
    }
};

class Recipient: public Person{
public:
    string requiredorgan;

    bool inputRecipientdata() {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Gender: ";
        getline(cin, gender);
        cout << "Enter Required Organ: ";
        getline(cin, requiredorgan);
        cout << "Choose Your Blood Type (A, A+, A-, B+, B-, AB+, AB-, O+, O-): ";
        while (true) {
            getline(cin, bloodType);
            if (bloodType == "A" or bloodType == "A+" or bloodType == "A-" or
                bloodType == "B+" or bloodType == "B-" or bloodType == "AB+" or
                bloodType == "AB-" or bloodType == "O+" or bloodType == "O-") {
                break;
            }
            cout << "Invalid Blood Type. Try again: ";
        }
        return true;
    }
    void displayRecipientdata(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Blood Type: " << bloodType << endl;
        cout<<"Required Organ: "<<requiredorgan<<endl;
    }

    void SaveRecipientData() {
        ofstream myfile("Recipient.txt", ios::app);
        if (myfile.is_open()) {
            myfile << name << endl;
            myfile << age << endl;
            myfile << gender << endl;
            myfile<< bloodType << endl;
            myfile << requiredorgan << endl;
            myfile << "=======================================\n";
            myfile.close();
        }
    }
};

class Inventory {
private:
    int heartcount = 0;
    int kidneycount = 0;
    int livercount = 0;
    int pancreascount = 0;
    int lungscount = 0;
    

    string normalize(string str) {
        for (char &c : str) c = tolower(c);
        return str;
    }

public:
    void addorgan(string organ) {
        organ = normalize(organ);
        if (organ == "heart") heartcount++;
        else if (organ == "kidney") kidneycount++;
        else if (organ == "pancreas") pancreascount++;
        else if (organ == "liver") livercount++;
        else if (organ == "lungs") lungscount++;
        else cout << "Organ type not recognized" << endl;
    }

    bool removeorgan(string organ) {
        organ = normalize(organ);
        if (organ == "heart" && heartcount > 0) {
            heartcount--;
            return true;
        } else if (organ == "liver" && livercount > 0) {
            livercount--;
            return true;
        } else if (organ == "pancreas" && pancreascount > 0) {
            pancreascount--;
            return true;
        } else if (organ == "lungs" && lungscount > 0) {
            lungscount--;
            return true;
        } else if (organ == "kidney" && kidneycount > 0) {
            kidneycount--;
            return true;
        }
         else {
            cout << "No " << organ << " available to remove." << endl;
            return false;
        }
    }

    void displayinventory() {
        cout << "\n--- Current Organ Inventory ---\n";
        cout << "Heart     : " << heartcount << endl;
        cout << "Kidney    : " << kidneycount << endl;
        cout << "Liver     : " << livercount << endl;
        cout << "Pancreas  : " << pancreascount << endl;
        cout << "Lungs     : " << lungscount << endl;
    }

    void SaveInventoryData() {
        ofstream myfile("Inventory.txt");
        if (myfile.is_open()) {
            myfile <<heartcount << endl;
            myfile <<kidneycount << endl;
            myfile << livercount << endl;
            myfile << pancreascount << endl;
            myfile <<lungscount << endl;
            myfile << "=======================================\n";
            myfile.close();
        } else {
            cout << "Error opening Inventory.txt for writing." << endl;
        }
    }

    void ReadInventoryData() {
        ifstream readfile("Inventory.txt");
        if (readfile.is_open()) {
            readfile >> heartcount;
            readfile >> kidneycount;
            readfile >> livercount;
            readfile >> pancreascount;
            readfile >> lungscount;
            readfile.close();
        }
    }
};

bool iscompatible(string donorBT, string recipientBT) {
    if (donorBT == "O-") 
    return true;
    if (recipientBT == "AB+") 
    return true;
    return donorBT == recipientBT;
}

int main() {
    Inventory inv;
    inv.ReadInventoryData();

    string inventorypassword = "1234";

    while (true) {
        int choice;
        cout << "\n----------Organ Donation System------------" << endl;
        cout << "1. Enter Donor details" << endl;
        cout << "2. Enter Recipient details" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. View all Donors" << endl;
        cout << "5. View all Recipients" << endl;
        cout << "6. Search Donors by Blood Type" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Donor d;
            if (d.inputdata()) {
                d.displaydata();
                d.SaveDonorData();
                inv.addorgan(d.organType);
                inv.SaveInventoryData();
            }
        } else if (choice == 2) {
            Recipient r;
            r.inputRecipientdata();
            r.displayRecipientdata();
            r.SaveRecipientData();
            bool match = false;

            ifstream donorfile("Donor.txt");
            if (donorfile.is_open()) {
                Donor d;
                string line;
                while (getline(donorfile, d.name)) {
                    donorfile >> d.age;
                    donorfile.ignore();
                    getline(donorfile, d.gender);
                    getline(donorfile, d.bloodType);
                    getline(donorfile, d.organType);
                    getline(donorfile, line); // separator

                    if (d.organType == r.requiredorgan && iscompatible(d.bloodType, r.bloodType)) {
                        if (inv.removeorgan(r.requiredorgan)) {
                            cout << "Organ Successfully provided to recipient!" << endl;
                            cout << "Matched with Donor: " << d.name << endl;
                            match = true;
                            break;
                        }
                    }
                }
                donorfile.close();
            }

            if (!match) {
                cout << "No compatible Donor found or organ not available!" << endl;
            }
        } else if (choice == 3) {
            string entrypassword;
            int attempts=0;
            while(attempts<3){
                cout<<"Enter your password to access the inventory : "<<endl;
            getline(cin, entrypassword);
             if (entrypassword == inventorypassword) {
                cout<<"Your Password is correct"<<endl;
                inv.displayinventory();
            }
        else {
                cout << "Invalid Password. Try Again." << endl;
                attempts++;
            }
        
        if(attempts==3){
            cout<<"3 Wrong attempts..."<<endl;
            cout<<"Access denied!"<<endl;
            exit(0);
        }
    }
    }
    else if (choice == 4) {
            ifstream donorfile("Donor.txt");
            if (donorfile.is_open()) {
                Donor d;
                string line;
                int count = 0;
                while (getline(donorfile, d.name)) {
                    donorfile >> d.age;
                    donorfile.ignore();
                    getline(donorfile, d.gender);
                    getline(donorfile, d.bloodType);
                    getline(donorfile, d.organType);
                    getline(donorfile, line);
                    cout << "\nDonor " << ++count << ":" << endl;
                    d.displaydata();
                    cout << "Organ: " << d.organType << endl;
                    cout << "================================" << endl;
                }
                donorfile.close();
            } else {
                cout << "No donor records available." << endl;
            }
        } else if (choice == 5) {
            ifstream recipientfile("Recipient.txt");
            if (recipientfile.is_open()) {
                Recipient r;
                string line;
                int count = 0;
                while (getline(recipientfile, r.name)) {
                    recipientfile >> r.age;
                    recipientfile.ignore();
                    getline(recipientfile, r.gender);
                    getline(recipientfile, r.bloodType);
                    getline(recipientfile, r.requiredorgan);
                    getline(recipientfile, line);
                    cout << "\nRecipient " << ++count << ":" << endl;
                    r.displayRecipientdata();
                    cout << "Required Organ: " << r.requiredorgan << endl;
                    cout << "--------------------------" << endl;
                }
                recipientfile.close();
            } else {
                cout << "No recipient records available." << endl;
            }
        } else if (choice == 6) {
            string searchBT;
            cout << "Enter Blood Type to Search Donors: ";
            getline(cin, searchBT);
            bool found = false;
            ifstream donorfile("Donor.txt");
            if (donorfile.is_open()) {
                Donor d;
                string line;
                while (getline(donorfile, d.name)) {
                    donorfile >> d.age;
                    donorfile.ignore();
                    getline(donorfile, d.gender);
                    getline(donorfile, d.bloodType);
                    getline(donorfile, d.organType);
                    getline(donorfile, line);
                    if (d.bloodType == searchBT) {
                        cout << "\nMatching Donor Found:" << endl;
                        d.displaydata();
                        cout << "Organ: " << d.organType << endl;
                        cout << "======================================" << endl;
                        found = true;
                    }
                }
                donorfile.close();
            }
            if (!found) {
                cout << "No Donors found with blood type " << searchBT << endl;
            }
        } else if (choice == 7) {
            cout << "Exiting the program...\nThank you!" << endl;
            break;
        } else {
            cout << "Invalid input! Please try again..." << endl;
        }
    }

    return 0;
}
