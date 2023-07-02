#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <exception>
#include <iterator>

using namespace std;

string html = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\" /> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\" /> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /> <title>Sales Management System</title> </head> <link rel=\"stylesheet\" href=\"project.css\" /> <body> <img src=\"banner.jpeg\" alt=\"Banner\" class=\"banner\" />";
string table = "<div> <table class=\"topics\"> <tr> <th>S.NO</th> <th>Product ID </th> <th>Product</th> <th>Quantity</th> <th>Price</th> <th>Category</th> <th>Total</th> </tr> <tr>";

class ProductInterface
{
protected:
    string id, name, quantity, price, category;
    int total;

public:
    virtual void setName(string x) = 0;
    virtual void setCategory(string x) = 0;
    virtual void setQuantity(string x) = 0;
    virtual void setPrice(string x) = 0;
    virtual void setId(string x) = 0;
    virtual string getName() = 0;
    virtual string getCategory() = 0;
    virtual string getQuantity() = 0;
    virtual string getPrice() = 0;
    virtual string getId() = 0;
    virtual int getTotal() = 0;
};

class Product : public ProductInterface
{
public:
    string getId() { return id; }
    string getName() { return name; }
    string getQuantity() { return quantity; }
    string getPrice() { return price; }
    string getCategory() { return category; }
    int getTotal()
    {
        total = stoi(quantity) * stoi(price);
        return total;
    }
    void setName(string x) { name = x; }
    void setQuantity(string x) { quantity = x; }
    void setPrice(string x) { price = x; }
    void setCategory(string x) { category = x; }
    void setId(string x) { id = x; }
    Product() {}
    Product(string id, string name, string quantity, string price, string category)
    {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->category = category;
    }
};

unordered_map<string, Product> um;
unordered_map<string, Product> bill;
unordered_map<string, Product> sales;
unordered_map<string, Product>::iterator it;

string dataHtml(unordered_map<string, Product>::iterator it, int count)
{
    return "<tr class=\" data \"> <td>" + to_string(count) + "</td> <td>" + it->second.getId() + "</td> <td>" + it->second.getName() + "</td> <td>" + it->second.getQuantity() + "</td> <td>" + it->second.getPrice() + "</td> <td>" + it->second.getCategory() + "</td><td>" + to_string(it->second.getTotal()) + "</td> </tr>";
}

class HtmlGenerator
{
private:
    int count;
    string search;

public:
    HtmlGenerator() {}
    HtmlGenerator(int option, string x)
    {
        search = x;
        ofstream out;
        out.open("index.html");
        string data = "";
        string headers = "";
        string billAmount = "";
        switch (option)
        {
        case 1:
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                count++;
                data += dataHtml(it, count);
            }
            headers = "<div class=\"heading\">ALL ITEMS</div>";
            break;
        case 3:
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getCategory() == search)
                {
                    count++;
                    data += dataHtml(it, count);
                }
            }
            headers = "<div class=\"heading\">Category: " + x + "(" + to_string(count) + ")</div>";
            break;
        case 4:
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getTotal() >= stoi(search))
                {
                    count++;
                    data += dataHtml(it, count);
                }
            }
            headers = "<div class=\"heading\">Items above price Rs. " + x + "(" + to_string(count) + ")</div>";
            break;
        case 5:
            count = 0;
            for (it = bill.begin(); it != bill.end(); it++)
            {
                count++;
                data += dataHtml(it, count);
            }
            headers = "<div class=\"heading\">BILL</div>";
            billAmount = "</tr> </table> <table class=\"topics\"> <tr class=\"data final\"> <td class=\"bill\">TOTAL AMOUNT:</td> <td class=\"bill\"> " + search + "</td> </tr> </table> </div> </body> </html>";
            break;
        case 6:
            count = 0;
            for (it = sales.begin(); it != sales.end(); it++)
            {
                count++;
                data += dataHtml(it, count);
            }
            headers = "<div class=\"heading\">Sales</div>";
            billAmount = "</tr> </table> <table class=\"topics\"> <tr class=\"data final\"> <td class=\"bill\">TOTAL AMOUNT:</td> <td class=\"bill\"> " + search + "</td> </tr> </table> </div> </body> </html>";
            break;
        default:
            break;
        }
        data = html + headers + table + data + billAmount;
        out << data;
        ShellExecute(NULL, "open", "index.html", NULL, NULL, SW_SHOWNORMAL);
        out.close();
    }
    HtmlGenerator(int option, int subOption, string x)
    {
        search = x;
        ofstream out;
        out.open("index.html");
        string data = "";
        string headers = "";
        switch (subOption)
        {
        case 1:
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getId() == search)
                {
                    count++;
                    data += dataHtml(it, count);
                }
            }
            break;
        case 2:
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getName() == search)
                {
                    count++;
                    data += dataHtml(it, count);
                }
            }
            break;
        case 0:
            return;
        }
        data = html + headers + table + data;
        out << data;
        ShellExecute(NULL, "open", "index.html", NULL, NULL, SW_SHOWNORMAL);
        out.close();
    }
};

class MainMenu
{

private:
    int count;
    string search;

public:
    void showAllItems()
    {
        count = 0;
        for (it = um.begin(); it != um.end(); it++)
        {
            count++;
            cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
        }
        HtmlGenerator(1, "x");
    }
    void searchItemsBy()
    {
        count = 0;
        cout << "-------Search By--------" << endl;
        cout << "1.ID\n2.Product Name\n-------Press 0 to go back--------\n";
        unsigned int response;
        try
        {
            cin >> response;
            if (response > 2)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (response)
        {
        case 1:
            cout << "Enter the id of product: ";
            cin >> search;
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getId() == search)
                {
                    count++;
                    cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
                }
            }
            break;
        case 2:
            cout << "Enter the name of product: ";
            cin >> search;
            count = 0;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getName() == search)
                {
                    count++;
                    cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
                }
            }
            break;
        case 0:
            return;
        }
        HtmlGenerator(2, response, search);
    }
    void sortItemsByCategory()
    {
        count = 0;
        cout << "-------Categories--------" << endl;
        cout << "1.Grocery\n2.Clothing\n3.Electronics\n-------Press 0 to go back--------\n";
        unsigned int categoryOption;
        try
        {
            cin >> categoryOption;
            if (categoryOption > 3)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (categoryOption)
        {
        case 1:
            search = "Grocery";
            break;
        case 2:
            search = "Clothing";
            break;
        case 3:
            search = "Electronics";
            break;
        case 0:
            return;
        }
        for (it = um.begin(); it != um.end(); it++)
        {
            if (it->second.getId() == search)
            {
                count++;
                cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
            }
        }
        HtmlGenerator(3, search);
    }
    void sortByPrice()
    {
        cout << "Enter price: ";
        unsigned int price;
        try
        {
            cin >> price;
            if (!cin)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        for (it = um.begin(); it != um.end(); it++)
        {
            if (it->second.getTotal() >= price)
            {
                count++;
                cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
            }
        }
        HtmlGenerator(4, to_string(price));
    }
};

class Account
{
protected:
    int count;
    int totalAmount;

public:
    void generateBill()
    {
        count = 0;
        totalAmount = 0;
        for (it = bill.begin(); it != bill.end(); it++)
        {
            count++;
            cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
            totalAmount += it->second.getTotal();
        }
        HtmlGenerator(5, to_string(totalAmount));
    }

    void sellings()
    {
        count = 0;
        totalAmount = 0;
        for (it = sales.begin(); it != sales.end(); it++)
        {
            count++;
            cout << count << ". " << it->second.getId() << "    " << it->second.getName() << "  " << it->second.getQuantity() << "   " << it->second.getPrice() << " " << it->second.getCategory() << "  " << it->second.getTotal() << endl;
            totalAmount += it->second.getTotal();
        }
        HtmlGenerator(6, to_string(totalAmount));
    }
};

class EditMenu : public Account
{
private:
    int addition, newQuantity, newPrice;
    string id, name, category;
    Product *p;

public:
    void addItem()
    {
        cout << "-------Choose an Option--------" << endl;
        cout << "1.Add an existing item\n2.Add new item\n-------Press 0 to go back--------\n";
        unsigned int response;
        try
        {
            cin >> response;
            if (response > 2)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (response)
        {
        case 1:
            cout << "-------Add ITEMS TO--------" << endl;
            cout << "1.Enter Product ID\n2.Enter Product Name\n-------Press 0 to go back--------\n";
            unsigned int option;
            try
            {
                cin >> option;
                if (option > 2)
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "Some Error occured\n";
                return;
            }
            switch (option)
            {
            case 1:
                cout << "Enter id of the item: ";
                cin >> id;
                bill[id] = um[id];
                newQuantity = stoi(um[id].getQuantity());
                cout << "\nEnter number of items to be added: ";
                cin >> addition;
                bill[id].setQuantity(to_string(addition));
                newQuantity += addition;
                um[id].setQuantity(to_string(newQuantity));
                break;
            case 2:
                cout << "Enter Product name: ";
                cin >> name;
                for (it = um.begin(); it != um.end(); it++)
                {
                    if (it->second.getName() == name)
                    {
                        id = it->second.getId();
                    }
                }
                newQuantity = stoi(um[id].getQuantity());
                cout << "\nEnter number of items to be added: ";
                cin >> addition;
                bill[id] = um[id];
                bill[id].setQuantity(to_string(addition));
                newQuantity += addition;
                um[id].setQuantity(to_string(newQuantity));
                break;
            case 0:
                return;
            }
            break;
        case 2:
            cout << "Enter new unique id: ";
            cin >> id;
            try
            {
                if (um.find(id) != um.end())
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "Enter Unique id" << endl;
                break;
            }
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter quantity: ";
            cin >> newQuantity;
            cout << "Enter price of the product: ";
            cin >> newPrice;
            cout << "Enter category of product: ";
            cin >> category;
            p = new Product(id, name, to_string(newQuantity), to_string(newPrice), category);
            um[id] = *p;
            bill[id] = um[id];
            break;
        case 0:
            return;
        }
        cout << "\nProduct Added!" << endl;
    }
    void sellItem()
    {
        cout << "-------Sell ITEMS--------" << endl;
        cout << "1.Enter Product ID\n2.Enter Product Name\n-------Press 0 to go back--------\n";
        unsigned int option;
        try
        {
            cin >> option;
            if (option > 2)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (option)
        {
        case 1:
            cout << "Enter id of the item: ";
            cin >> id;
            try
            {
                if (um.find(id) == um.end())
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "Enter correct id" << endl;
                return;
            }
            break;
        case 2:
            cout << "Enter Product name: ";
            cin >> name;
            for (it = um.begin(); it != um.end(); it++)
            {
                if (it->second.getName() == name)
                {
                    id = it->second.getId();
                }
            }
            try
            {
                if (um.find(id) == um.end())
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "Enter correct name" << endl;
                return;
            }
            break;
        case 0:
            return;
        }
        cout << "--------Options--------" << endl;
        cout << "1.Sell entire stock\n2.Enter Quantity\n-------Press 0 to go back--------\n";
        try
        {
            cin >> option;
            if (option > 2)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (option)
        {
        case 1:
            sales[id] = um[id];
            um.erase(id);
            break;
        case 2:
            cout << "Enter Quantity: ";
            cin >> newQuantity;
            try
            {
                if (newQuantity >= stoi(um[id].getQuantity()))
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "You are entering way more!" << endl;
                return;
            }
            sales[id] = um[id];
            sales[id].setQuantity(to_string(newQuantity));
            newQuantity = stoi(um[id].getQuantity()) - newQuantity;
            um[id].setQuantity(to_string(newQuantity));
            break;
        case 0:
            return;
        }
        cout << "\nProduct Sold!" << endl;
    }
    void modifyItem()
    {
        cout << "Enter ID of product: ";
        cin >> id;
        cout << "-------Modify ITEMS--------" << endl;
        cout << "1.Change Product Name\n2.Change Product Category\n3.Change Product price\n4.Change Product quantity\n5.Remove Product-------Press 0 to go back--------\n";
        unsigned int option;
        try
        {
            cin >> option;
            if (option > 5)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Some Error occured\n";
            return;
        }
        switch (option)
        {
        case 1:
            cout << "Enter new product name: ";
            cin >> name;
            um[id].setName(name);
            break;
        case 2:
            cout << "-------Choose new category--------" << endl;
            cout << "1.Grocery\n2.Clothing\n3.Electronics\n-------Press 0 to go back--------\n";
            unsigned int categoryOption;
            try
            {
                cin >> categoryOption;
                if (categoryOption > 3)
                {
                    throw exception();
                }
            }
            catch (...)
            {
                cout << "Some Error occured\n";
                return;
            }
            switch (categoryOption)
            {
            case 1:
                category = "Grocery";
                break;
            case 2:
                category = "Clothing";
                break;
            case 3:
                category = "Electronics";
                break;
            case 0:
                return;
            }
            um[id].setCategory(category);
            break;
        case 3:
            cout << "Enter new price: ";
            cin >> newPrice;
            um[id].setPrice(to_string(newPrice));
            break;
        case 4:
            cout << "Enter new quantity: ";
            cin >> newQuantity;
            um[id].setQuantity(to_string(newQuantity));
            break;
        case 5:
            um.erase(id);
            cout << "Product removed!" << endl;
            break;
        case 0:
            return;
        }
    }
};

void saveData()
{
    ofstream out("items.txt");
    for (it = um.begin(); it != um.end(); it++)
    {
        out << it->second.getId() << endl;
        out << it->second.getName() << endl;
        out << it->second.getQuantity() << endl;
        out << it->second.getPrice() << endl;
        out << it->second.getCategory() << endl;
    }
    out.close();
}

class Menu : public MainMenu, public EditMenu
{
public:
    Menu()
    {
        ifstream in("Items.txt");
        try
        {
            if (in.eof() == 1)
            {
                throw exception();
            }
        }
        catch (...)
        {
            cout << "Could not reach database" << endl;
        }
        while (!in.eof())
        {
            string a1, a2, a3, a4, a5;
            getline(in, a1);
            if (in.eof())
            {
                break;
            }
            getline(in, a2);
            getline(in, a3);
            getline(in, a4);
            getline(in, a5);
            Product p(a1, a2, a3, a4, a5);
            um[p.getId()] = p;
        }
    }

    void options()
    {
        unsigned int response;
        while (response != 0)
        {
            cout << "-------Menu-------" << endl;
            cout << "1.All Products\n2.Search Item\n3.Sort by Category\n4.Sort by Price\n5.Add Products\n6.Sell Products\n7.Modify Product\n8.Generate Bill\n9.Sales\n-------Press 0 to exit--------\n";
            cout << "Enter your response: ";
            try
            {
                cin >> response;
                if (response > 9)
                {
                    throw string("Invalid");
                }
            }
            catch (string e)
            {
                cout << e << endl;
                // return;
            }
            catch (...)
            {
                cout << "Some error occured" << endl;
                break;
            }
            switch (response)
            {
            case 1:
                showAllItems();
                break;
            case 2:
                searchItemsBy();
                break;
            case 3:
                sortItemsByCategory();
                break;
            case 4:
                sortByPrice();
                break;
            case 5:
                addItem();
                break;
            case 6:
                sellItem();
                break;
            case 7:
                modifyItem();
                break;
            case 8:
                generateBill();
                break;
            case 9:
                sellings();
                break;
            case 0:
                // abort();
                break;
            default:
                break;
            }
            saveData();
        }
    }
};

int main()
{
    Menu a;
    a.options();
}
