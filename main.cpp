
 #include <iostream>
#include <vector>
#include <string>
#include<cstdlib>
#include <memory>
#include<map>


class Leguma
{
    std::string Nume;
    int Cantitate;

public:
    Leguma(const std::string& nume, int cantitate): Nume(nume), Cantitate(cantitate) {}
    Leguma(const Leguma& copiere) : Nume(copiere.Nume), Cantitate(copiere.Cantitate) {}

    std::string get_Nume()const
    {
        return Nume;
    }
    int get_Cantitate() const
    {
        return Cantitate;
    }

    Leguma& operator=(const Leguma& copiere)
    {
        if (this==&copiere)
        {
            return *this;
        }
        Nume = copiere.Nume;
        Cantitate = copiere.Cantitate;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Leguma& leg);

};

class Topping
{
    std::vector<Leguma> Legume;
    std::string Sos;
    std::string Cascaval;
    std::string ExtraCascaval;
    std::string ExtraSos;

public:
    Topping(const std::vector<Leguma>& legume,const std::string& sos,const std::string& cascaval,const std::string& extracascaval,const std::string& extrasos)
        : Legume(legume), Sos(sos), Cascaval(cascaval), ExtraCascaval(extracascaval), ExtraSos(extrasos) {}
    std::vector<Leguma> get_Legume()const
    {
        return Legume;
    }
    //std::string get_Sos(){ return Sos; }
    //std::string get_Cascaval(){ return Cascaval; }
    std::string get_ExtraCascaval()const
    {
        return ExtraCascaval;
    }
    std::string get_ExtraSos()const
    {
        return ExtraSos;
    }

    void addLegume(const Leguma& leg)
    {
        Legume.push_back(leg);
    }

    void addExtraToppings(const Leguma& extraTopping)
    {
        addLegume(extraTopping);
    }

    friend std::ostream& operator<<(std::ostream& out, const Topping &top);

    Topping(const Topping& copiere) : Legume(copiere.Legume), Sos(copiere.Sos), Cascaval(copiere.Cascaval), ExtraCascaval(copiere.ExtraCascaval), ExtraSos(copiere.ExtraSos) {}

    Topping& operator=(const Topping& copiere)
    {
        if(this==&copiere)
            return *this;
        Legume=copiere.Legume;
        Sos=copiere.Sos;
        Cascaval=copiere.Cascaval;
        ExtraCascaval=copiere.ExtraCascaval;
        ExtraSos=copiere.ExtraSos;
        return *this;
    }
    ~Topping()
    {
        std::cout<<"Destructor Topping."<<"\n";
    }
};

class Pizza
{
    Topping Toppings;
    double Diametru;
    int Felii;

public:
    Pizza(const Topping& toppings, double diametru, int felii): Toppings(toppings), Diametru(diametru), Felii(felii) {}
    Topping get_Toppings()const
    {
        return Toppings;
    }
    double get_Diametru()const
    {
        return Diametru;
    }
    int get_Felii()const
    {
        return Felii;
    }

    double calculatePrice()
    {
        double basePrice = 10.0;
        double sizePrice = 0.5;
        double toppingvPrice = 0.0;
        double sosPrice, cascavalPrice;
        if (Toppings.get_ExtraCascaval() == "DA") cascavalPrice=5.0;
        else cascavalPrice=2.0;
        if (Toppings.get_ExtraSos() == "DA") sosPrice=4.0;
        else sosPrice=2.0;
        for (const Leguma& leguma : Toppings.get_Legume())
        {
            double unitPrice = 2.0;
            toppingvPrice = toppingvPrice + unitPrice * leguma.get_Cantitate();
        }

        double totalPrice = basePrice + (Diametru * sizePrice) + toppingvPrice+ sosPrice + cascavalPrice;
        return totalPrice;
    }

    double calculateBakingTime()
    {
        double baseBakingTime = 20.0;
        double sizeFactor = 0.5;
        double diameter = get_Diametru();
        double sizeTime = diameter * sizeFactor;
        double totalBakingTime = baseBakingTime + sizeTime;

        return totalBakingTime;
    }

    virtual double calculeazaCalorii() const   //caloriile le-am pus orientativ, nu sunt adevarate
    {
        double calorii = 40.0; //incepe de la 40 pentru ca deja am adaugat pentru cascaval si sos
        for (const Leguma& leguma : Toppings.get_Legume())
        {
            calorii += 10.0 * leguma.get_Cantitate();
        }
        calorii += 0.1 * get_Diametru();
        if(Toppings.get_ExtraCascaval()=="DA") calorii+=20.0;
        if(Toppings.get_ExtraSos()=="DA") calorii+=20.0;
        return calorii;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pizza& pzz);

};


class Pizza_Nevegetariana : public Pizza
{
    std::string Salam;

public:
    Pizza_Nevegetariana(const std::string& salam, const Topping& toppings, double diametru, int felii)
        : Pizza(toppings, diametru, felii), Salam(salam) {}
    //std::string get_Salam() const { return Salam; }
    double calculatePrice()
    {
        return Pizza::calculatePrice() + 10.0;
    }

    double calculeazaCalorii() const override
    {
        return Pizza::calculeazaCalorii() + 200;
    }
    friend std::ostream& operator<<(std::ostream& out, const Pizza_Nevegetariana& pzznv);

};

class Pizza_Facuta
{
    std::string Sos;
    std::string Cascaval;
public:
    Pizza_Facuta(const std::string& sos="Sos de rosii", const std::string& cascaval="Mozzarella") : Sos(sos), Cascaval(cascaval) {}
    virtual void afiseazaPizza() const = 0;
    virtual ~Pizza_Facuta() {}
};

class Margherita : public Pizza_Facuta
{
    std::string Leguma;
public:
    Margherita(const std::string& leguma="Busuioc", const std::string& sos="Sos de rosii", const std::string& cascaval="Mozzarella") : Pizza_Facuta(sos, cascaval), Leguma(leguma) {}
    // std::string get_Leguma() {return Leguma;}
    void afiseazaPizza() const override
    {
        std::cout << "Pizza Margherita\n";
        std::cout << "Ingrediente: Mozzarela, Sos de rosii, Busuioc\n";
        std::cout << "Pret: 25.0\n";
    }

};

class QuattroStagioni : public Pizza_Facuta
{
    std::string Leguma1;
    std::string Leguma2;
    std::string Leguma3;
    std::string Leguma4;

public:
    QuattroStagioni(const  std::string& leguma1="Ciuperci",const  std::string& leguma2="Sunca",const  std::string& leguma3 ="Masline",const std::string& leguma4="Ardei",const  std::string& sos="Sos de rosii", const std::string& cascaval="Mozzarella"): Pizza_Facuta(sos, cascaval), Leguma1(leguma1), Leguma2(leguma2), Leguma3(leguma3), Leguma4(leguma4) {}

    //std::string get_Leguma1(){return Leguma1;}
    //std::string get_Leguma2(){return Leguma2;}
    //std::string get_Leguma3(){return Leguma3;}
    //std::string get_Leguma4(){return Leguma4;}
    void afiseazaPizza() const override
    {
        std::cout << "Pizza Quattro Stagioni \n";
        std::cout << "Ingrediente: Mozzarela, Sos de rosii, Ciuperci, Sunca, Masline, Ardei\n";
        std::cout << "Pret: 30.0\n";
    }
};

class Hawaii: public Pizza_Facuta
{
    std::string Salam;
    std::string Leguma;

public:

    Hawaii(const std::string& salam="Sunca", const std::string& leguma="Ananas",const std::string& sos="Sos de rosii", const std::string& cascaval="Mozzarella" ) : Pizza_Facuta(sos, cascaval), Salam(salam), Leguma(leguma) {}
    //std::string get_Salam() {return Salam;}
    //std::string get_Leguma(){return Leguma;}
    void afiseazaPizza() const override
    {
        std::cout << "Pizza Hawaii \n";
        std::cout << "Ingrediente: Mozzarela, Sos de rosii, Sunca, Ananas\n";
        std::cout << "Pret: 27.5\n";
    }

};

class Ingredient
{
public:
    std::string Nume;
    int CantitateDisponibila;

    Ingredient(const std::string& nume, int cantitate)
        : Nume(nume), CantitateDisponibila(cantitate) {}

    void afiseazaStoc() const
    {
        std::cout << "Stoc pentru " << Nume << ": " << CantitateDisponibila << " bucati\n";
    }

    void actualizeazaStoc(int cantitate)
    {
        CantitateDisponibila += cantitate;
    }
};

class InventarPizza
{
    std::map<std::string, Ingredient> Inventar;

public:
    const std::map<std::string, Ingredient>& getInventar() const
    {
        return Inventar;
    }
    std::map<std::string, Ingredient>::iterator cautaIngredient(const std::string& nume)
    {
        return Inventar.find(nume);
    }
    void adaugaIngredient(const std::string& nume, int cantitate)
    {
        Inventar.emplace(nume, Ingredient(nume, cantitate));
    }

    bool areSuficienteIngrediente(const std::vector<Leguma>& ingrediente) const
    {
        for (const Leguma& leguma : ingrediente)
        {
            auto it = Inventar.find(leguma.get_Nume());
            if (it == Inventar.end() || it->second.CantitateDisponibila < leguma.get_Cantitate())
            {
                return false;
            }
        }
        return true;
    }

    void afiseazaStocul() const
    {
        std::cout << "Stoc Ingrediente:\n";
        for (const auto& entry : Inventar)
        {
            entry.second.afiseazaStoc();
        }
    }

    void actualizeazaStocul(const std::vector<Leguma>& ingrediente)
    {
        for (const Leguma& leguma : ingrediente)
        {
            auto it = Inventar.find(leguma.get_Nume());

            if (it != Inventar.end())
            {
                it->second.actualizeazaStoc(-leguma.get_Cantitate());
            }
        }
    }

};

std::ostream& operator<<(std::ostream& out, const Leguma& leg)
{
    out << "Leguma: {"
        << leg.Nume << " " << leg.Cantitate
        << "}\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Topping &top)
{
    out<<"Topping: [";
    for(const Leguma& leguma : top.Legume)
    {
        out<<leguma.get_Nume()<<", "<<leguma.get_Cantitate()<<"\n";
    }
    out<<top.Sos<<"\n"<<top.Cascaval<<"\n"
       <<"Extra Cascaval: "<<top.ExtraCascaval<<"\n"
       <<"Extra Sos: "<<top.ExtraSos
       <<"]\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Pizza& pzz)
{
    out<<"    Pizza: {"<<"\n";
    out<<"    "<<pzz.Toppings;
    out<<"    Diametru: "<<pzz.Diametru<<"\n"
       <<"    Felii: "<<pzz.Felii
       <<"}\n";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Pizza_Nevegetariana& pzznv)
{
    out<<"    Pizza Nevegetariana: {"<<"\n";
    out<<"    "<<pzznv.get_Toppings();
    out<<"    Salam: "<<pzznv.Salam<<"\n"
       <<"    Diametru: "<<pzznv.get_Diametru()<<"\n"
       <<"    Felii: "<<pzznv.get_Felii()
       <<"}\n";
    return out;
}

void adaugaIngredientInInventar(InventarPizza& inventar)
{
    std::string nume;
    int cantitate;

    std::cout << "Introdu numele ingredientului: ";
    std::cin >> nume;

    auto it = inventar.cautaIngredient(nume);

    if (it == inventar.getInventar().end())
    {
        std::cout << "Introdu cantitatea disponibila: ";
        std::cin >> cantitate;

        inventar.adaugaIngredient(nume, cantitate);
        std::cout << "Ingredient adaugat cu succes!\n";
    }
    else
    {
        std::cout << "Ingredientul se afla deja in inventar.\n";
    }
}
void actualizeazaStocIngredient(InventarPizza& inventar)
{
    std::string nume;
    int cantitate;

    std::cout << "Introdu numele ingredientului pentru actualizare: ";
    std::cin >> nume;

    auto it = inventar.cautaIngredient(nume);

    if (it != inventar.getInventar().end())
    {
        std::cout << "Introdu noua cantitate disponibila: ";
        std::cin >> cantitate;

        it->second.actualizeazaStoc(cantitate);
        std::cout << "Stoc actualizat cu succes!\n";
    }
    else
    {
        std::cout << "Ingredientul nu a fost gasit in inventar.\n";
    }
}




int main()
{

    InventarPizza inventar;
    inventar.adaugaIngredient("Ciuperci", 20);
    inventar.adaugaIngredient("Masline", 15);
    inventar.adaugaIngredient("Ardei", 30);
    inventar.adaugaIngredient("Rosii", 25);
    inventar.adaugaIngredient("Castraveti", 18);
    inventar.adaugaIngredient("Ceapa", 22);
    inventar.adaugaIngredient("Ananas", 12);

    std::vector<Leguma> legume;
   for (const std::string lgm : {"Ciuperci", "Masline", "Ardei", "Rosii", "Castraveti", "Ceapa"}) {
    int cantitate = rand() % 10;
    legume.push_back(Leguma(lgm, cantitate));
}

    /* for (const Leguma& lgm : legume) {
         std::cout << "Nume: " << lgm.get_Nume() << std::endl;
         std::cout<<"Cantitate: " << lgm.get_Cantitate() << std::endl;
     }

    Leguma leguma1("Castravete", rand()%10);
    std::cout<<"Nume: "<<leguma1.get_Nume() <<std::endl;
    std::cout<<"Cantitate: "<<leguma1.get_Cantitate() <<std::endl;
    Leguma leguma2("Rosie", rand()%10);
    Leguma leguma3("Ceapa", rand()%10);
    std::vector<Leguma> legume;
    legume.push_back(leguma1);
    legume.push_back(leguma2);
    legume.push_back(leguma3);*/

    Topping topping1(legume, "Sos de rosii", "Feta", "NU", "NU");
    Leguma extraTopping("Ananas", 3);
    topping1.addExtraToppings(extraTopping);
    Leguma newLeguma("Mazare", 5);
    topping1.addLegume(newLeguma);
    //std::cout<<"Sos: "<<topping1.get_Sos() <<std::endl;
    //std::cout<<"Cascaval: "<<topping1.get_Cascaval() <<std::endl;
    //std::cout<<"ExtraCascaval: "<<topping1.get_ExtraCascaval() <<std::endl;
    //std::cout<<"ExtraSos: "<<topping1.get_ExtraSos() <<std::endl;
    Pizza pizza1(topping1, 20, 8);
    //std::cout<<"Diametru: "<<pizza1.get_Diametru() <<std::endl;
    //std::cout<<"Felii: "<<pizza1.get_Felii() <<std::endl;


    std::vector<Leguma> legume_pnv;
   for (const std::string lgm_pnv : {"Ciuperci", "Masline", "Ardei", "Rosii", "Castraveti", "Ceapa"}) {
    int cantitate = rand() % 10;
    legume_pnv.push_back(Leguma(lgm_pnv, cantitate));
}

    /*for (const Leguma& lgm : legume) {
        std::cout << "Nume: " << lgm.get_Nume() << std::endl;
        std::cout<<"Cantitate: " << lgm.get_Cantitate() << std::endl;
    }*/

    Topping topping2 (legume_pnv, "Sos de rosii", "Parmezan", "DA", "NU");
    //std::cout<<"Sos: "<<topping2.get_Sos() <<std::endl;
    //std::cout<<"Cascaval: "<<topping2.get_Cascaval() <<std::endl;
    //std::cout<<"ExtraCascaval: "<<topping2.get_ExtraCascaval() <<std::endl;
    //std::cout<<"ExtraSos: "<<topping2.get_ExtraSos() <<std::endl;
    Pizza_Nevegetariana pizza2("Sunca",topping2, 15, 4);
    //std::cout<<"Salam: "<<pizza2.get_Salam()<<std::endl;
    //std::cout<<"Diametru: "<<pizza2.get_Diametru() <<std::endl;
    //std::cout<<"Felii: "<<pizza2.get_Felii() <<std::endl;



    int optiune=-1;

    do
    {
        std::cout << "---------------------------\n";
        std::cout << "1. Adauga ingredient in inventar\n";
        std::cout << "2. Actualizeaza stocul pentru un ingredient\n";
        std::cout << "3. Comanda pizza facuta\n";
        std::cout << "4. Creeaza o pizza.\n";
        std::cout << "0. Iesire\n";
        std::cout << "---------------------------\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;
    

        switch (optiune)
        {
        case 1:
            adaugaIngredientInInventar(inventar);
            break;
        case 2:
            actualizeazaStocIngredient(inventar);
            break;
        case 3:
        {
            int optiunePizza;
            std::cout << "---------------------------\n";
            std::cout << "Alege tipul de pizza:\n";
            std::cout << "1. Margherita\n";
            std::cout << "2. Quattro Stagioni\n";
            std::cout << "3. Hawaii\n";
            std::cout << "0. Inapoi la meniu\n";
            std::cout << "---------------------------\n";
            std::cout << "Alege o opțiune: ";
            std::cin >> optiunePizza;

            switch (optiunePizza)
            {
            case 1:
            {
                Pizza_Facuta* optiunea1 = new Margherita();
                optiunea1->afiseazaPizza();
                delete optiunea1;
                break;
            }
            case 2:
            {
                Pizza_Facuta* optiunea2 = new QuattroStagioni();
                optiunea2->afiseazaPizza();
                delete optiunea2;
                break;
            }
            case 3:
            {
                Pizza_Facuta* optiunea3 = new Hawaii();
                optiunea3->afiseazaPizza();
                delete optiunea3;
                break;
            }

            case 0:
            {
                std::cout << "Înapoi la meniu.\n";
                break;
            }
            default:
            {
                std::cout << "Opțiune invalidă. Încearcă din nou.\n";
            }
            }
            break;
        }
        break;



        case 4:
        {
            if (inventar.areSuficienteIngrediente(legume))
            {
                std::cout << "Avem suficiente ingrediente pentru pizza!\n";
            }
            else
            {
                std::cout << "Nu avem suficiente ingrediente pentru pizza!\n";
                inventar.afiseazaStocul();
                return 1;
            }
            std::cout<<"Pizza1"<<std::endl;
            std::cout<<pizza1;
            double calorii1=pizza1.calculeazaCalorii();
            std::cout<<"Calorii: "<<calorii1<<std::endl;
            double price1=pizza1.calculatePrice();
            std::cout<<"Pret: "<< price1 <<std::endl;
            double time1=pizza1.calculateBakingTime();
            std::cout<<"Timp: "<< time1 <<std::endl;
            inventar.actualizeazaStocul(legume);
            inventar.afiseazaStocul();
            auto& inventarMap = inventar.getInventar();
            (void)inventarMap;
            std::cout<<"-------------------------------------------------------------"<<std::endl;
            if (inventar.areSuficienteIngrediente(legume_pnv))
            {
                std::cout << "Avem suficiente ingrediente pentru pizza!\n";
            }
            else
            {
                std::cout << "Nu avem suficiente ingrediente pentru pizza!\n";
                inventar.afiseazaStocul();
                return 1;
            }
            std::cout<<"Pizza2(nevegetariana)"<<std::endl;
            std::cout<<pizza2;
            double calorii2=pizza2.calculeazaCalorii();
            std::cout<<"Calorii: "<<calorii2<<std::endl;
            double price2=pizza2.calculatePrice();
            std::cout<<"Pret: "<< price2 <<std::endl;
            double time2=pizza2.calculateBakingTime();
            std::cout<<"Timp: "<< time2 <<std::endl;
            inventar.actualizeazaStocul(legume_pnv);
            inventar.afiseazaStocul();
            break;

        }
        case 0:
            std::cout << "Programul se inchide.\n";
            break;
        default:
            std::cout << "Opțiune invalida. Incearca din nou.\n";
        }

    }
    while (optiune != 0);





    return 0;
}

