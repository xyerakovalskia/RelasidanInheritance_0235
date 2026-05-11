#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class User {
protected:
    static int globalId;
    int id;
    string nama, email;

public:
    User(string n, string e) : nama(n), email(e) { id = ++globalId; }
    static int generateId() { return ++globalId; }
    int getId() const { return id; }
    virtual void display() const = 0;
    virtual ~User() {}
};

int User::globalId = 0;

class Admin : public User {
    static vector<User*> members;
public:
    Admin(string n, string e) : User(n, e) {}
    
    void showAllMember() const {
        cout << "\n=== ALL MEMBERS ===\nID  Nama             Email\n";
        for (auto m : members) m->display();
    }
    
    void toggleActivationMember(int id) {
        for (auto& m : members) {
            if (m->getId() == id) {
                static_cast<Member*>(m)->toggleStatus();
                cout << "Toggled member " << id << endl;
                return;
            }
        }
        cout << "Member " << id << " not found\n";
    }
    
    static void addMember(User* m) { members.push_back(m); }
    
    void display() const override {
        cout << id << "  " << nama << "  [ADMIN]\n";
    }
};

vector<User*> Admin::members;

class Member : public User {
    bool status = true;
public:
    Member(string n, string e) : User(n, e) {}
    void toggleStatus() { status = !status; }
    string getStatus() const { return status ? "ACTIVE" : "INACTIVE"; }
    
    void showProfile() const {
        cout << "\nID: " << id << "\nNama: " << nama 
             << "\nEmail: " << email << "\nStatus: " << getStatus() << endl;
    }
    
    void display() const override {
        cout << id << "  " << nama << "  " << email << " [" << getStatus() << "]\n";
    }
};

int main() {
    Admin* admin = new Admin("Budi", "budi@co.com");
    Member* m1 = new Member("Ani", "ani@em.com");
    Member* m2 = new Member("Bambang", "bam@em.com");
    
    Admin::addMember(m1); Admin::addMember(m2);
    
    admin->showAllMember();
    admin->toggleActivationMember(2);
    admin->showAllMember();
    
    m1->showProfile();
    delete admin; delete m1; delete m2;
}