#include <iostream>
#include <vector>
#include <string>

class Leguma{
 std::string Nume;
 int Cantitate;

 public:
    Leguma(const std::string& nume, int cantitate): Nume(nume), Cantitate(cantitate){}
    Leguma(const Leguma& other) : Nume(other.Nume), Cantitate(other.Cantitate) {}

     std::string get_Nume()const { return Nume; }
     int get_Cantitate() const { return Cantitate; }

     Leguma& operator=(const Leguma& copiere) {
          if (this==&copiere) {
        return *this;
        }
       Nume = copiere.Nume;
       Cantitate = copiere.Cantitate;
    return *this;
     }

     friend std::ostream& operator<<(std::ostream& out, const Leguma& leg);

};

class Topping{
 std::vector<Leguma> Legume;
 std::string Sos;
 std::string Cascaval;
 std::string ExtraCascaval;
 std::string ExtraSos;

 public:
     Topping(const std::vector<Leguma>& legume,const std::string& sos,const std::string& cascaval,const std::string& extracascaval,const std::string& extrasos)
    : Legume(legume), Sos(sos), Cascaval(cascaval), ExtraCascaval(extracascaval), ExtraSos(extrasos) {}
     std::vector<Leguma> get_Legume(){return Legume; }
     std::string get_Sos(){ return Sos; }
     std::string get_Cascaval(){ return Cascaval; }
     std::string get_ExtraCascaval(){ return ExtraCascaval; }
     std::string get_ExtraSos(){ return ExtraSos; }

     friend std::ostream& operator<<(std::ostream& out, const Topping &top);

     Topping(const Topping& copiere) : Legume(copiere.Legume), Sos(copiere.Sos), Cascaval(copiere.Cascaval), ExtraCascaval(copiere.ExtraCascaval), ExtraSos(copiere.ExtraSos){}

     Topping& operator=(const Topping& copiere){
     if(this==&copiere)
        return *this;
     Legume=copiere.Legume;
     Sos=copiere.Sos;
     Cascaval=copiere.Cascaval;
     ExtraCascaval=copiere.ExtraCascaval;
     ExtraSos=copiere.ExtraSos;
     return *this;
        }
      ~Topping(){
      std::cout<<"Destructor Topping."<<"\n";
      }
};

class Pizza{
Topping Toppings;
double Diametru;
int Felii;

public:
    Pizza(const Topping& toppings, double diametru, int felii): Toppings(toppings), Diametru(diametru), Felii(felii) {}
    Topping get_Toppings(){return Toppings; }
    double get_Diametru(){return Diametru; }
    int get_Felii(){return Felii; }
    double calculatePrice() {
        double basePrice = 10.0;
        double sizePrice = 0.5;
        double toppingvPrice = 0.0;
        double sosPrice, cascavalPrice;
        if (Toppings.get_ExtraCascaval() == "DA") cascavalPrice=5.0;
                              else cascavalPrice=2.0;
        if (Toppings.get_ExtraSos() == "DA") sosPrice=4.0;
                              else sosPrice=2.0;
        for (const Leguma& leguma : Toppings.get_Legume()) {
            double unitPrice = 2.0;
            toppingvPrice = toppingvPrice + unitPrice * leguma.get_Cantitate();
        }

        double totalPrice = basePrice + (Diametru * sizePrice) + toppingvPrice+ sosPrice + cascavalPrice;
        return totalPrice;
    }

    friend std::ostream& operator<<(std::ostream& out, const Pizza& pzz);

};

std::ostream& operator<<(std::ostream& out, const Leguma& leg){
out << "Leguma: {"
    << leg.Nume << " " << leg.Cantitate
    << "}\n";
return out;
}

std::ostream& operator<<(std::ostream& out, const Topping &top){
out<<"Topping: [";
   for(const Leguma& leguma : top.Legume){
    out<<leguma.get_Nume()<<", "<<leguma.get_Cantitate()<<"\n";}
    out<<top.Sos<<"\n"<<top.Cascaval<<"\n"
       <<"Extra Cascaval: "<<top.ExtraCascaval<<"\n"
       <<"Extra Sos: "<<top.ExtraSos
       <<"]\n";
return out;
}

std::ostream& operator<<(std::ostream& out, const Pizza& pzz){
out<<"    Pizza: {"<<"\n";
out<<"    "<<pzz.Toppings;
out<<"    Diametru: "<<pzz.Diametru<<"\n"
   <<"    Felii: "<<pzz.Felii
   <<"}\n";
 return out;
}

int main()

{ Leguma leguma1("Castravete", 9);
  std::cout<<"Nume: "<<leguma1.get_Nume() <<std::endl;
  std::cout<<"Cantitate: "<<leguma1.get_Cantitate() <<std::endl;
  Leguma leguma2("Rosie", 3);
  Leguma leguma3("Ceapa", 2);
  std::vector<Leguma> legume;
  legume.push_back(leguma1);
  legume.push_back(leguma2);
  legume.push_back(leguma3);
  Topping topping1(legume, "Sos de rosii", "Feta", "NU", "NU");
  std::cout<<"Sos: "<<topping1.get_Sos() <<std::endl;
  std::cout<<"Cascaval: "<<topping1.get_Cascaval() <<std::endl;
  std::cout<<"ExtraCascaval: "<<topping1.get_ExtraCascaval() <<std::endl;
  std::cout<<"ExtraSos: "<<topping1.get_ExtraSos() <<std::endl;
  Pizza pizza1(topping1, 20, 8);
  std::cout<<"Diametru: "<<pizza1.get_Diametru() <<std::endl;
  std::cout<<"Felii: "<<pizza1.get_Felii() <<std::endl;
  double price=pizza1.calculatePrice();
  std::cout<<"Pret: "<< price <<std::endl;

  std::cout<<pizza1;

    return 0;
}
