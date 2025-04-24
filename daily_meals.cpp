#include "daily_meals.h"

using namespace std;

    Meal *head_ptr;
    Meal *tail_ptr;
    int num_meals;

    // Returns Meal pointer to target given name and calories 
    Meal* DailyMeals::search_meal(string target , int cal_of_target){
        Meal *cursor = head_ptr;
        while(cursor != NULL){
            if(cursor->get_name() == target && cursor->get_calories()== cal_of_target)
                return cursor;
            cursor = cursor->next;
        }
        cout << "Meal not Found" << endl;
        return NULL;
    }

    // Add meal to a daily list (adds at the end)
    void DailyMeals::add_meal() {
        // Do NOT need to check for duplicates since peopple can ahve the same meal multiple
        // times in a day
        string m_name;
        int m_cal, m_prot;

        cout << "\nEnter Meal Name, Calories, Protein: " ;
        cin >> m_name >> m_cal >> m_prot;
       

        Meal *newMeal = new Meal(m_name, m_cal, m_prot);
        if(head_ptr == NULL){
            head_ptr = newMeal;
            tail_ptr = head_ptr;
            newMeal->next = NULL;

            num_meals++;

            return;
        }
        
        // Generate case adding to the end
        tail_ptr->next = newMeal;
        tail_ptr = newMeal;
        newMeal->next = NULL;
        num_meals++;

        cout << m_name << " has been added!" << endl;
        
    }

    // Remove meal from day
    bool DailyMeals::remove_meal(){
        string delete_meal;
        int cals;
        cout << "Name of Meal: ";
        cin >> delete_meal;
        cout << "Calories of meal: ";
        cin >> cals;

        Meal* temp = search_meal(delete_meal, cals);

        // Meal not found
        if(temp == NULL)
            return false;

        // Case: Deleting head_ptr
        if(temp == head_ptr){
            delete temp;

            head_ptr = NULL;
            tail_ptr = NULL;
            num_meals = 0;

            return true;
        }

        // Prev is pointer before target
        Meal* prev = head_ptr;
        while(prev->next != temp){
            prev = prev->next;
        }

        // Case deleting end
        if(temp == tail_ptr)
            tail_ptr = prev;

        // Adjust pointers
        prev->next = temp->next;
        delete temp;
        
        // Successfully removed
        return true;
    }

    // Prints the meals logged in the week + calories and protein information
    void DailyMeals::display_daily_meals() {
        Meal *current = head_ptr;

        while (current != NULL) {
            cout << "--> " << current->get_name() << " (" << current->get_protein() << "g protein, "<< current->get_calories() << " calories)" << endl;
            current = current->next;
        }
    }

    // Go through the list and return the total grams of protein for the day
    int DailyMeals::total_daily_protein(){
        if(day_empty())
            return 0;
        // To be returned
        int total_protein = 0;

        Meal *cursor = head_ptr;
        while(cursor != NULL)
        {
            total_protein += cursor->get_protein();
            cursor = cursor ->next;
        }

        return total_protein;
    }
    
    // Go through the list and return the total calories for the day
    int DailyMeals::total_daily_calories(){
        if(day_empty())
            return 0;
        // To be returned
        int total_calories = 0;

        Meal *cursor = head_ptr;
        while(cursor != NULL)
        {
            total_calories += cursor->get_calories();
            cursor = cursor ->next;
        }

        return total_calories;
    }

    // Checks current stats for each day relative to goals 
    void DailyMeals::check_goals(int climit, int pgoal){
        // Checking relative to calorie limit ______________________
        int c_difference, p_difference;
        if(!day_empty()){
            c_difference = climit - total_daily_calories(); //error line
            if(c_difference == 0){
                cout << "Hit Calorie Limit" << endl;
            }
            else if(c_difference < 0){
                cout<< "Exceeded  Calorie Limit" << endl;
            }
            else{
                cout << c_difference << " Calroies Available" << endl;
            }

            // Checking relative to protein goal ________________________
            p_difference = pgoal - total_daily_protein();
            if(p_difference <= 0){
                cout << "Hit Protein Goal" << endl;
            }
            else{
                cout << p_difference << "g Below Protein Goal" << endl;
            }
        }
    }

    // Adjust protien and calories for a meal
    bool DailyMeals::change_meal_stats() {
            int c_cals, n_cals, n_prot;
            string current_name;
            cout << "(name) (calories): ";
            cin >> current_name >> c_cals;

            Meal* temp = search_meal(current_name, c_cals);

            // Meal not found so nothing to edit
            if (temp == NULL) {
                return false;
            }

            cout << "NEW Protein: ";
            cin >> n_prot;
            cout << " NEW Calories: ";
            cin >> n_cals;

            temp->change_protein(n_prot);
            temp->change_calories(n_cals);

            return true;
    }

    // Changes all instances of meal wiht certain name to new name
    bool DailyMeals::change_meal_name() {
        cout << "Name of meal you want to change ";
        string current_name;
        cin >> current_name;

        Meal* cursor = head_ptr;
        cout << "NEW Name: " << endl;
 
        string new_name;
        cin >> new_name;

        int count = 0;
        while (cursor != NULL){
            if (cursor->get_name() == current_name) {
                cursor->change_name(new_name);
                count++;
            }
            cursor = cursor->next;


        }
        if (count >= 1) { return true; }
        return false;


    }
