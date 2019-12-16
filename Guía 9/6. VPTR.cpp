#include <iostream>

class Padre_t{
public:
    int id = 0;
    Padre_t(int _id): id(_id) {}
    virtual void foo(){
        std::cout << "Padre_t::foo()" << std::endl;
    }

    virtual void goo(){
        std::cout << "Padre_t::goo()" << std::endl;
    }
};

class Hijo_t: public Padre_t{

};


template <class class_t>
void print_vtable(class_t *myClass)
{
    intptr_t * p = (intptr_t *) myClass;
    std::cout << sizeof(class_t) << std::endl;
    for(size_t i=0;i<sizeof(class_t)/sizeof(intptr_t);i++,p++){
        std::cout << i << ' ' << std::hex << (void*)*p << std::endl;
        printf("%d\t%016x\n",i,*p);
    }
    p =  (intptr_t *) myClass;
    p = (intptr_t *)*p;
    for(size_t i=0;i<2;i++,p++){
        printf("%d\t%016x\n",i,*p);
    }
}

int main()
{
    using namespace std;

    Padre_t darth_vader(3);

    print_vtable(&darth_vader);

    cin.get();
    return 0;
}
