#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Client {
private:
    int code;
    string name;
public:
    Client(int c, string n) : code(c), name(n) {}
    int getCode() { return code; }
    string getName() { return name; }
};

class Account {
private:
    int number;
    double balance;
    double interestRate;
    Client* owner;
    Client* partner;
public:
    Account(int n, Client* c) : number(n), balance(0), interestRate(0), owner(c), partner(nullptr) {}
    Account(int n, Client* c, double ir) : number(n), balance(0), interestRate(ir), owner(c), partner(nullptr) {}
    Account(int n, Client* c, Client* p) : number(n), balance(0), interestRate(0), owner(c), partner(p) {}
    Account(int n, Client* c, Client* p, double ir) : number(n), balance(0), interestRate(ir), owner(c), partner(p) {}
    
    int getNumber() { return number; }
    double getBalance() { return balance; }
    double getInterestRate() { return interestRate; }
    Client* getOwner() { return owner; }
    Client* getPartner() { return partner; }
    
    bool canWithdraw(double a) { return balance >= a; }
    void deposit(double a) { balance += a; }
    bool withdraw(double a) {
        if (canWithdraw(a)) {
            balance -= a;
            return true;
        }
        return false;
    }
    void addInterest() { balance += balance * interestRate; }
};

class Bank {
private:
    vector<Client*> clients;
    vector<Account*> accounts;
public:
    void addClient(int c, string n) { clients.push_back(new Client(c, n)); }
    void addAccount(int n, Client* c, double ir = 0) { accounts.push_back(new Account(n, c, ir)); }
    
    Client* getClient(int c) {
        for (auto client : clients)
            if (client->getCode() == c) return client;
        return nullptr;
    }
    Account* getAccount(int n) {
        for (auto account : accounts)
            if (account->getNumber() == n) return account;
        return nullptr;
    }
    
    void addInterestToAll() {
        for (auto account : accounts)
            account->addInterest();
    }
};

int main() {
    Bank bank;
    bank.addClient(1, "Alice");
    bank.addClient(2, "Bob");
    
    Client* alice = bank.getClient(1);
    Client* bob = bank.getClient(2);
    
    bank.addAccount(101, alice, 0.02);
    bank.addAccount(102, bob, 0.03);
    
    Account* acc1 = bank.getAccount(101);
    Account* acc2 = bank.getAccount(102);
    
    acc1->deposit(1000);
    acc2->deposit(2000);
    
    cout << "Alice balance: " << acc1->getBalance() << endl;
    cout << "Bob balance: " << acc2->getBalance() << endl;
    
    acc1->addInterest();
    acc2->addInterest();
    
    cout << "Alice balance after interest: " << acc1->getBalance() << endl;
    cout << "Bob balance after interest: " << acc2->getBalance() << endl;
    
    cout << "Press ENTER to exit...";
    cin.get();
    
    return 0;
}
