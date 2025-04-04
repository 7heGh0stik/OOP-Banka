#include <iostream>
#include <vector>
using namespace std;

class Client {
private:
    int code;
    string name;
public:
    Client(int c, string n) : code(c), name(n) {}
    int GetCode() { return code; }
    string GetName() { return name; }
};

class Account {
private:
    int number;
    double balance;
    double interestRate;
    Client* owner;
    Client* partner;
public:
    Account(int n, Client* o, double ir)
        : number(n), balance(0), interestRate(ir), owner(o), partner(nullptr) {}

    Account(int n, Client* o, Client* p, double ir)
        : number(n), balance(0), interestRate(ir), owner(o), partner(p) {}

    int GetNumber() { return number; }
    double GetBalance() { return balance; }
    double GetInterestRate() { return interestRate; }
    Client* GetOwner() { return owner; }
    Client* GetPartner() { return partner; }

    bool CanWithdraw(double a) {
        return a <= balance;
    }

    bool Withdraw(double a) {
        if (CanWithdraw(a)) {
            balance -= a;
            return true;
        }
        return false;
    }

    void Deposit(double a) {
        balance += a;
    }

    void AddInterest() {
        balance += balance * interestRate;
    }

    void SetInterest(double ir) {
        interestRate = ir;
    }
};

class Bank {
private:
    vector<Client*> clients;
    vector<Account*> accounts;
    double defaultInterest;
public:
    Bank(double defaultInt) : defaultInterest(defaultInt) {}

    ~Bank() {
        for (auto c : clients) delete c;
        for (auto a : accounts) delete a;
    }

    Client* CreateClient(int c, string n) {
        Client* client = new Client(c, n);
        clients.push_back(client);
        return client;
    }

    Account* CreateAccount(int n, Client* o, double ir = -1) {
        double usedInterest = (ir < 0) ? defaultInterest : ir;
        Account* acc = new Account(n, o, usedInterest);
        accounts.push_back(acc);
        return acc;
    }

    Account* CreateAccount(int n, Client* o, Client* p, double ir = -1) {
        double usedInterest = (ir < 0) ? defaultInterest : ir;
        Account* acc = new Account(n, o, p, usedInterest);
        accounts.push_back(acc);
        return acc;
    }

    void AddInterest() {
        for (auto acc : accounts) {
            acc->AddInterest();
        }
    }

    void ModifyDefaultInterest(double newInterest) {
        for (auto acc : accounts) {
            if (acc->GetInterestRate() == defaultInterest) {
                acc->SetInterest(newInterest);
            }
        }
        defaultInterest = newInterest;
    }

    void PrintAccounts() {
        for (auto acc : accounts) {
            cout << "Účet #" << acc->GetNumber()
                 << ", stav: " << acc->GetBalance()
                 << ", úrok: " << acc->GetInterestRate() << endl;
        }
    }
};

int main() {
    Bank banka(0.01); //úrok 1 %

    Client* c1 = banka.CreateClient(1, "Novák");
    Client* c2 = banka.CreateClient(2, "Svoboda");

    Account* a1 = banka.CreateAccount(100, c1);
    Account* a2 = banka.CreateAccount(101, c2, 0.03);

    a1->Deposit(1000);
    a2->Deposit(2000);

    cout << "Před úrokem:\n";
    banka.PrintAccounts();

    banka.AddInterest();

    cout << "\nPo připsání úroku:\n";
    banka.PrintAccounts();

    banka.ModifyDefaultInterest(0.05);

    cout << "\nPo změně výchozího úroku a aktualizaci účtů:\n";
    banka.PrintAccounts();

    cout << "ENTER to exit...";
    cin.get();
    return 0;
}