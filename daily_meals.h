#include "meal.h"

using namespace std;

class DailyMeals {

    public:
        Meal *head_ptr;
        Meal *tail_ptr;
        int num_meals;

        DailyMeals() : head_ptr(NULL), num_meals(0) {
            // List constructor for DailyMeals !!
        }

        // Returns true if list is empty, false if not
        bool day_empty(){
            return (num_meals == 0);
        }

        // Add meal to a daily list (adds at the end)
        void add_meal();

        // Remove meal from day
        bool remove_meal();

        // Prints the meals logged in the week + calories and protein information
        void display_daily_meals();
        
        // Returns Meal pointer to target
        Meal* search_meal(string target, int cals);

        // Go through the list and return the total grams of protein for the day
        int total_daily_protein();
        
        // Go through the list and return the total calories for the day
        int total_daily_calories();

        //
        void check_goals(int pgoal, int climit);

        // 
        bool change_meal_stats();

        // 
        bool change_meal_name();
  
};
