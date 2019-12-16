#include <iostream>

class Base_t{
protected:
    int id;
public:
    Base_t(int _id): id(_id) {}
    Base_t(const Base_t &old_obj){
        id = old_obj.id;
    }
    int getID(){return id;}
    Base_t * clone(){
        return new Base_t(*this);
    }
};

class Derived2_t: public Base_t{
public:
    Derived2_t(int _id): Base_t(id) {}
    Derived2_t(const Derived2_t &old_obj){
        id = old_obj.id;
    }
    Derived2_t * clone(){
        return new Derived2_t(*this);
    }
};

class Derived2_t: public Base_t{
public:
    Derived2_t(int _id): Base_t(id) {}
    Derived2_t(const Derived2_t &old_obj){
        id = old_obj.id;
    }
    Derived2_t * clone(){
        return new Derived2_t(*this);
    }
};

int main(){
    using namespace std;

    // Compruebo que se copia y no son equivalente.
    Base_t base(3);
    Base_t *copy = base.clone();
    cout << base.getID() << '\t' << copy->getID() << endl;
    delete copy;
    cout << base.getID() << '\t' << copy->getID() << endl;

    

    cin.get();
    return 0;
}