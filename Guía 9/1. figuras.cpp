#include <iostream>

class Figure_t{
public:
    virtual void draw(){
        std::cout << "Figure_t::Draw" << std::endl;
    }
};

class Square_t : public Figure_t{
public:
    void draw(){
        std::cout << "Square_t::Draw" << std::endl;
    }
};

class Triangle_t: public Figure_t{
public:
    void draw(){
        std::cout << "Triangle_t::Draw" << std::endl;
    }
};

int main()
{
    using namespace std;
    cout << "Hola mundo!" << endl;

    Figure_t * figure_array = new Figure_t[10];
    for(int i=0;i<10;i++)
        figure_array[i].draw();

    cin.get();
    return 0;
}