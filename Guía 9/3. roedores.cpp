#include <iostream>
#include <string>

class Roedor_t{
protected:
    std::string name;
public:
    Roedor_t(const std::string& _name = "Unnamed"): name(_name) {}
    virtual void eat(const std::string& food = ""){std::cout << "Roedor_t::eat()" << std::endl;}
    virtual std::string getname(){return name;}
};

class Raton_t : public Roedor_t{
public:
    Raton_t(const std::string& _name = "Unnamed"): Roedor_t(_name) {}
    void eat(const std::string& food = "Cheese"){
        std::cout << name << " eat " << food << std::endl;
    }
};

class Jerbo_t :  public Roedor_t{
public:
    Jerbo_t(const std::string& _name = "Unnamed"): Roedor_t(_name) {}
    void eat(const std::string& food = "Bananas"){
        std::cout << name << " eat " << food << std::endl;
    }
};

class Hamster_t: public Roedor_t{
public:
    Hamster_t(const std::string& _name = "Unnamed"): Roedor_t(_name) {}
    void eat(const std::string& food = "Hamster's food"){
        std::cout << name << " eat " << food << std::endl;
    }
};

int main()
{
    using namespace std;
    cout << "Hola Mundo" << endl;

    Roedor_t *roedores[2];
    roedores[0] = new Hamster_t;
    roedores[1] = new Raton_t;

    dynamic_cast<Hamster_t *>(roedores[0])->eat();

    cin.get();
    return 0;
}
