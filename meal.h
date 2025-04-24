#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Meal {
    private:
        string name;
        int calories;
        // For protein uinit will be grams
        int protein;

    public:
        Meal* next;

        // Default constructor for Meal
        Meal(){
            name = "unknown";
            calories = 0;
            protein = 0;
            next = NULL;
        }

        Meal(const std::string& name, int calories, int pro) : name(name), calories(calories), next(NULL), protein(pro) {
            // this is the constructor for when the user gives input
        }
        // Accessor and mutator functions
        void change_calories(int new_cal){
		    calories = new_cal;
        }
        void change_name(string new_name){
		    name = new_name;
	    }
        void change_protein(int new_protein){
		    protein = new_protein;
	    }

        int get_calories(){return calories;}

        string get_name(){return name;}
        
        int get_protein(){return protein;}
};