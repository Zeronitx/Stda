#include <iostream>
#include <iomanip>
using namespace std;
 
int main() {
    double vol[4]  = {1.0, 1.5, 2.0, 1.0};
    double kcal[4] = {1500, 5000, 5000, 4000};
 
    double bestKcal = -1;
    double bestMeat = 0, bestFlour = 0, bestMilk = 0, bestSugar = 0;
 
    for (double sugar = 0; sugar <= 2.0; sugar += 0.1) {
        for (double milk = 8*sugar; milk <= 35.0; milk += 0.1) {
            for (double flour = milk; flour <= 35.0; flour += 0.1) {
                for (double meat = 2*flour; meat <= 35.0; meat += 0.1) {
                    double mass = meat + flour + milk + sugar;
                    double volume = meat*vol[0] + flour*vol[1] + milk*vol[2] + sugar*vol[3];
 
                    if (mass > 35.0 || volume > 45.0) break;
 
                    double totalKcal = meat*kcal[0] + flour*kcal[1] + milk*kcal[2] + sugar*kcal[3];
 
                    if (totalKcal > bestKcal) {
                        bestKcal  = totalKcal;
                        bestMeat  = meat;
                        bestFlour = flour;
                        bestMilk  = milk;
                        bestSugar = sugar;
                    }
                }
            }
        }
    }
 
    cout << fixed << setprecision(1);
    cout << "Meat:  " << bestMeat  << " kg" << endl;
    cout << "Flour:   " << bestFlour << " kg" << endl;
    cout << "Milk: " << bestMilk  << " kg" << endl;
    cout << "Sugar:  " << bestSugar << " kg" << endl;
    cout << "Сaloric content: " << fixed << setprecision(0) << bestKcal << " Kcal" << endl;
 
    return 0;
}
 

