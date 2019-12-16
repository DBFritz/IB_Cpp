#include <iostream>
#include <vector>

using namespace std;
template <class key_t, class value_t>
class acumulator_t{
    vector<key_t> key;
    vector<value_t> value;

public:
    acumulator_t(){}
    acumulator_t(vector<key_t> _key, vector<value_t> _value): key(_key), value(_value){}

    bool add(key_t new_key, value_t new_value)
    {
        for(long unsigned int i=0; i<key.size(); i++) {
            if (new_key == key[i]) {
                value[i] += new_value;
                return true;
            }
        }
        key.push_back(new_key);
        value.push_back(new_value);
        return false;
    }

    friend ostream &operator <<(ostream& output, const acumulator_t<key_t, value_t>& acumulator)
    {
        for(long unsigned int i=0; i<acumulator.key.size(); i++) {
            output << '(' << acumulator.key[i] << ',' << acumulator.value[i] << ')' << endl ;
        }
        return output;
    }
};

int main(){
    acumulator_t<string, int> acumulator;
    acumulator.add("pepe",2);
    acumulator.add("de la italia",8);
    acumulator.add("pepe",2);
    cout << acumulator;
    cin.get();
    return 0;
}