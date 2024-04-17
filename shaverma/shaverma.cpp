#include <iostream>
#include <string>
using namespace std;

// размеры 
enum class Size { S = 20, M = 30, L = 40, XXL = 50 };

class Food abstract // базовый абстрактный напиток
{
protected:
    Size size;
    double price;
    string description;

public:
    Size getSize() const
    {
        return size;
    }

    double getPrice() const
    {
        return price;
    }

    string getDescription() const
    {
        return description;
    }

    void print() const
    {
        cout << description << " = " << price << " UAH\n";
    }
};

// shaverma classic - конкретный базовый food без добавок
class ShavermaClassic : public Food
{
public:
    ShavermaClassic(Size size)
    {
        this->size = size;
        description = "very delicious classic shaverma";

        if (size == Size::M) price = 150; // 330г
        else if (size == Size::L) price = 200; // 400г
        else throw "invalid shaverma size";
    }
};

// shaverma cheese - конкретный базовый food без добавок
class ShavermaCheese : public Food
{
public:
    ShavermaCheese()
    {
        // size = ...
        description = "very delicious cheese shaverma";
        price = 150;
    }
};

// hotdog - конкретный базовый food без добавок
class HotDog : public Food
{
public:
    HotDog()
    {
        // size = ...
        description = "delicious snack";
        price = 30;
    }
};

////////////////////////////////////////////////////////////////

// базовая абстрактная добавка (надо было назвать Additive?)
class Condiment abstract : public Food // добавка помечена как наследник food - это важно для реализации паттерна!
{
protected:
    Food* food; // указатель на оригинальный food
};

// sauce
class SauceCondiment : public Condiment
{
public:
    SauceCondiment(Food* food)
    {
        this->food = food; // добавка
        description = this->food->getDescription() + " + Sauce (5 UAH)";
        price = this->food->getPrice() + 5;
    }

    SauceCondiment()
    {
        this->food = this;
        description = "large pack of sauce to go";
        price = 10;
    }
};

class CheeseCondiment : public Condiment
{
public:
    CheeseCondiment(Food* food)
    {
        this->food = food;
        description = this->food->getDescription() + " + Cheese (15 UAH)";
        price = this->food->getPrice() + 15;
    }
};

class MeatCondiment : public Condiment
{
public:
    MeatCondiment(Food* food)
    {
        this->food = food;
        description = this->food->getDescription() + " + Meat (40 UAH)";
        price = this->food->getPrice() + 40;
    }
};

int main()
{
    Food* hotDog = new HotDog();
    Food* shavermaClassic = new ShavermaClassic(Size::L);
    Food* shavermaCheese = new ShavermaCheese();

    hotDog->print();
    shavermaClassic->print();
    shavermaCheese->print();

    cout << "================================================\n";

    Food* upgradedShavermaPlus = new MeatCondiment(new SauceCondiment(new HotDog()));
    upgradedShavermaPlus->print();

    Food* doubleCheeseShaverma = new CheeseCondiment(upgradedShavermaPlus);
    doubleCheeseShaverma->print();

    Food* extraMeatShaverma = new MeatCondiment(new MeatCondiment(new MeatCondiment(new ShavermaClassic(Size::L))));
    extraMeatShaverma->print();

    Food* sauceToGo = new SauceCondiment(new SauceCondiment(new SauceCondiment()));
    sauceToGo->print();
}