#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

class RealEstateDeal 
{
public:
    virtual ~RealEstateDeal() {}
    virtual void edit() = 0;
    virtual void display() const = 0;
    virtual void saveToFile(std::ofstream& out) const = 0;
    virtual std::unique_ptr<RealEstateDeal> clone() const = 0; // Полиморфное копирование
};

class PurchaseDeal : public RealEstateDeal 
{
private:
    std::string buyer;
    double price;
public:
    PurchaseDeal(std::string b = "Unknown", double p = 0.0) : buyer(b), price(p) {}
    void edit() override 
    {
        std::cout << "Enter buyer name: ";
        std::cin >> buyer;
        std::cout << "Enter price: ";
        std::cin >> price;
    }
    void display() const override 
    {
        std::cout << "Purchase Deal - Buyer: " << buyer << ", Price: " << price << std::endl;
    }
    void saveToFile(std::ofstream& out) const override 
    {
        out << "PurchaseDeal, Buyer: " << buyer << ", Price: " << price << "\n";
    }
    std::unique_ptr<RealEstateDeal> clone() const override 
    {
        return std::make_unique<PurchaseDeal>(*this);
    }
};

class SaleDeal : public RealEstateDeal
{
private:
    std::string seller;
    double price;
public:
    SaleDeal(std::string s = "Unknown", double p = 0.0) : seller(s), price(p) {}
    void edit() override 
    {
        std::cout << "Enter seller name: ";
        std::cin >> seller;
        std::cout << "Enter price: ";
        std::cin >> price;
    }
    void display() const override
    {
        std::cout << "Sale Deal - Seller: " << seller << ", Price: " << price << std::endl;
    }
    void saveToFile(std::ofstream& out) const override
    {
        out << "SaleDeal, Seller: " << seller << ", Price: " << price << "\n";
    }
    std::unique_ptr<RealEstateDeal> clone() const override
    {
        return std::make_unique<SaleDeal>(*this);
    }
};

class RentalDeal : public RealEstateDeal 
{
private:
    std::string renter;
    double monthlyRate;
public:
    RentalDeal(std::string r = "Unknown", double m = 0.0) : renter(r), monthlyRate(m) {}
    void edit() override 
    {
        std::cout << "Enter renter name: ";
        std::cin >> renter;
        std::cout << "Enter monthly rate: ";
        std::cin >> monthlyRate;
    }
    void display() const override 
    {
        std::cout << "Rental Deal - Renter: " << renter << ", Monthly Rate: " << monthlyRate << std::endl;
    }
    void saveToFile(std::ofstream& out) const override
    {
        out << "RentalDeal, Renter: " << renter << ", Monthly Rate: " << monthlyRate << "\n";
    }
    std::unique_ptr<RealEstateDeal> clone() const override 
    {
        return std::make_unique<RentalDeal>(*this);
    }
};

class MortgageDeal : public RealEstateDeal
{
private:
    std::string lender;
    double interestRate;
public:
    MortgageDeal(std::string l = "Unknown", double i = 0.0) : lender(l), interestRate(i) {}
    void edit() override 
    {
        std::cout << "Enter lender name: ";
        std::cin >> lender;
        std::cout << "Enter interest rate: ";
        std::cin >> interestRate;
    }
    void display() const override 
    {
        std::cout << "Mortgage Deal - Lender: " << lender << ", Interest Rate: " << interestRate << "%" << std::endl;
    }
    void saveToFile(std::ofstream& out) const override
    {
        out << "MortgageDeal, Lender: " << lender << ", Interest Rate: " << interestRate << "\n";
    }
    std::unique_ptr<RealEstateDeal> clone() const override 
    {
        return std::make_unique<MortgageDeal>(*this);
    }
};

class LeaseDeal : public RealEstateDeal
{
private:
    std::string lessee;
    int leaseTerm;
public:
    LeaseDeal(std::string l = "Unknown", int t = 0) : lessee(l), leaseTerm(t) {}
    void edit() override
    {
        std::cout << "Enter lessee name: ";
        std::cin >> lessee;
        std::cout << "Enter lease term (months): ";
        std::cin >> leaseTerm;
    }
    void display() const override
    {
        std::cout << "Lease Deal - Lessee: " << lessee << ", Lease Term: " << leaseTerm << " months" << std::endl;
    }
    void saveToFile(std::ofstream& out) const override 
    {
        out << "LeaseDeal, Lessee: " << lessee << ", Lease Term: " << leaseTerm << "\n";
    }
    std::unique_ptr<RealEstateDeal> clone() const override
    {
        return std::make_unique<LeaseDeal>(*this);
    }
};

// Фабрика для создания объектов с аргументами
class ArgumentDealFactory 
{
public:
    static std::unique_ptr<RealEstateDeal> createPurchaseDeal(std::string buyer, double price) 
    {
        return std::make_unique<PurchaseDeal>(buyer, price);
    }

    static std::unique_ptr<RealEstateDeal> createSaleDeal(std::string seller, double price)
    {
        return std::make_unique<SaleDeal>(seller, price);
    }

    static std::unique_ptr<RealEstateDeal> createRentalDeal(std::string renter, double monthlyRate) 
    {
        return std::make_unique<RentalDeal>(renter, monthlyRate);
    }

    static std::unique_ptr<RealEstateDeal> createMortgageDeal(std::string lender, double interestRate)
    {
        return std::make_unique<MortgageDeal>(lender, interestRate);
    }

    static std::unique_ptr<RealEstateDeal> createLeaseDeal(std::string lessee, int leaseTerm)
    {
        return std::make_unique<LeaseDeal>(lessee, leaseTerm);
    }
};


class DealManager // класс для управления сделками самый главный
{
private:
    std::vector<std::unique_ptr<RealEstateDeal>> deals;// уникальный указатель тут есть , тип объект удаляется когда не нужен 
public:
    void addDeal(std::unique_ptr<RealEstateDeal> deal) 
    {
        deals.push_back(std::move(deal));
    }

    void deleteDeal(size_t index) 
    {
        if (index < deals.size()) 
        {
            deals.erase(deals.begin() + index);
        }
    }

    void editDeal(size_t index)
    {
        if (index < deals.size())
        {
            deals[index]->edit();
        }
    }

    void displayAllDeals() const
    {
        for (const auto& deal : deals)// передается по ссылке
        {
            deal->display();
        }
    }

    void saveAllDealsToFile(const std::string& filename) const 
    {
        std::ofstream out(filename);
        for (const auto& deal : deals) 
        {
            deal->saveToFile(out);
        }
    }
};

int main() {
    DealManager manager;

    manager.addDeal(ArgumentDealFactory::createPurchaseDeal("Alice", 250000));
    manager.addDeal(ArgumentDealFactory::createSaleDeal("Bob", 300000));
    manager.addDeal(ArgumentDealFactory::createRentalDeal("Charlie", 1500));
    manager.addDeal(ArgumentDealFactory::createMortgageDeal("Diana", 3.5));
    manager.addDeal(ArgumentDealFactory::createLeaseDeal("Edward", 24));
    manager.displayAllDeals();
    manager.saveAllDealsToFile("deals.txt");
    manager.editDeal(0);  // Редактирование первой сделки
    manager.displayAllDeals();
    manager.deleteDeal(1); 
    manager.displayAllDeals();

    return 0;
}
