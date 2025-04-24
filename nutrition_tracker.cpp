
#include <iostream>
#include <string>
#include <cctype>
#include "daily_meals.h"

// Not using this currently
enum Day {
    MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
    //   1         2          3         4        5        6        7
};

using namespace std;

// *************************************************************************************
//                              MAIN FUNCTION (TOP 5 MEALS)                            *
// *************************************************************************************

// Function to update the top 5 meals array
void updateTop5Meals(Meal* topMeals[], int &topMealsCount, Meal* newMeal){
    if(topMealsCount < 5){
        topMeals[topMealsCount] = newMeal;
        topMealsCount++;
    }
    else{
        int minIndex = 0;
        for(int i =0; i < 5; ++i){
            if(topMeals[i]->get_protein() < topMeals[minIndex]->get_protein()){
                minIndex=i;
            }
        }
            if (newMeal->get_protein() > topMeals[minIndex]->get_protein()) {
                topMeals[minIndex] = newMeal;
            }
        
    }
    for (int i = 0; i < topMealsCount - 1; i++) {
        for (int j = 0; j < topMealsCount - i - 1; j++) {
            if (topMeals[j]->get_protein() < topMeals[j + 1]->get_protein()) {
                // Swap the meals
                Meal* temp = topMeals[j];
                topMeals[j] = topMeals[j + 1];
                topMeals[j + 1] = temp;
            }
        }
    }
}

// Function to find the top 5 highest protein meals in the week
void findTop5Meals(DailyMeals* weekMeals[], Meal* topMeals[], int &topMealsCount){
    topMealsCount = 0;
    for(int i =0; i < 7; ++i){
        Meal * current = weekMeals[i]-> head_ptr;
        while(current != NULL){
            updateTop5Meals(topMeals , topMealsCount , current);
            current = current-> next;
        }
    }
}

// Function to print the top 5 highest protein meals
void printTop5Meals(Meal* topMeals[], int topMealsCount){
    if(topMealsCount == 0 ){
        cout << "There are no meals logged"<< endl;
        return;
    }
    cout<<"These were your type 5 meals of the week:"<< endl;
    for(int i = 0; i < topMealsCount; i ++){
        cout << i + 1 << ". " << topMeals[i]->get_name() << " (" << topMeals[i]->get_protein() << "g protein)" << endl;
    }

} 

// *************************************************************************************
//                                    MAIN FUNCTION                                    *
// *************************************************************************************

int main() {
    // Important variables needed for the main
    string days_of_the_week[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    DailyMeals *weekMeals[7];

    bool in_program = true;
    int input = -1;
    int day = -1;
    int protein_goal = 0;
    int calorie_limit = 0;
    string meal_name;

    // Initialize array of head_ptrs for the week
    for (int i = 0; i < 7; ++i) {
        // Each item in the array is a default Meal (head of each list)
        weekMeals[i] = new DailyMeals();
    }

    Meal *topMeals[5];
    int topMealsCount = 0;

// ******************************************     MENU + SWTICH STATEMENT     ************************************************
    while(in_program){
        // Menu output
        cout<< "\nWelcome to your weekly nutritional tracker !!\n" << "[1] Add Meal\n" << "[2] Remove Meal\n" << "[3] Change Meal Info\n" << "[4] Display Week\n" << "[5] Review Goals\n" << "[6] Check Progress\n" << "[7] Top 5 Protein Meals\n" << "[8] Exit Program " << "\n\nReference: [1 2 3 4 5 6] -> [M T W Th F S Su] (use ints)\n" << endl;
        
        // User input for menu selection
        cout << "Selection: ";
        cin >> input;

        // Checks taht input is valid to swtich satement if letters or special characters
        if(cin.fail()){
                cout << "FAILED INPUT\n" << endl;
                cin.clear();
                cin.ignore(100000, '\n');
        }


        // Switch statement that operates on user input
        switch(input) {
        //**************************************** ADD A MEAL ****************************************
        case 1:{
            cout << "\nLet's Add a Meal !!\n"<< "Which day are we adding to? : ";
            cin >> day;

            if(cin.fail()){
                cout << "FAILED INPUT" << endl;
                cin.clear();
                cin.ignore(100000, '\n');
                break;
            }
            
            if(day < 0 || day > 6){
                cout << "Invalid date !!\n" << endl;
                break;
            }

            weekMeals[day-1]->DailyMeals::add_meal();
            Meal *lastMeal = weekMeals[day -1] ->tail_ptr;
            updateTop5Meals(topMeals , topMealsCount , lastMeal);
    
            break;}
        //**************************************** REMOVE A MEAL ****************************************
        case 2:{
            cout << "Which day are we removing from? : " << endl;
            cin >> day;

            if(cin.fail()){
                cout << "FAILED INPUT" << endl;
                cin.clear();
                cin.ignore(100000, '\n');
                break;
            }

            if(day < 0 || day > 6){
                cout << "Invalid date !!\n" << endl;
                break;
            }

            // If no meals have been logged for that day yet
            if(weekMeals[day-1]->day_empty()){
                cout << "Day is empty, no meals to remove :(" << endl;
                break;
            }

            weekMeals[day-1]->DailyMeals::remove_meal();
            findTop5Meals(weekMeals, topMeals, topMealsCount);


            break;}

        //**************************************** CHANGE MEAL INFO ****************************************   
        case 3:{
            cout << "[1] Change meal name \n[2] Change protein and calories for specific meal" << endl;
            int option, day;
            cin >> option;

            cout << "Which Day does the meal belong to: ";
            cin >> day;

            if(cin.fail()){
                cout << "FAILED INPUT" << endl;
                cin.clear();
                cin.ignore(100000, '\n');
                break;
            }
 
            if(day < 0 || day > 6){
                cout << "Invalid date !!\n" << endl;
                break;
            }

            if (option == 1) {
                if(weekMeals[day-1]->change_meal_name())
                    cout << "Meal name changed!!\n";
                findTop5Meals(weekMeals, topMeals, topMealsCount);
                break;
            }
            else {
                int n_pro, n_cal;
                if(weekMeals[day-1]->change_meal_stats())
                    cout << "Meal stats changed!!\n";
                findTop5Meals(weekMeals, topMeals, topMealsCount);
                break;
            }

            

            break;}

        //**************************************** DISPLAY THE WEEK ****************************************
        case 4:{
            cout << "Printing meals: " << endl;
            // Call function to print meals

            for(int i = 0; i < 7; i++){
                cout << days_of_the_week[i] << endl;
                cout << "================\n" << endl;
                weekMeals[i]->DailyMeals::display_daily_meals();
                cout << "\n";
            }

            break;}
        //**************************************** SET GOALS ****************************************
        case 5:{
            cout << "Let's set some goals!" << endl;
            // Call function to print meals
            char user_input;
            int new_climit, new_pgoal;
            cout << "Current Goals" << endl;
            cout << "Calorie Limit: " << calorie_limit << " Daily Protein Goal: " << protein_goal << endl;  

            cout << "Yould you like to change your goals? [Y] [N] : ";
            cin >> user_input;
            // Maybe add soemthing to switch to upper case so user can input y or n

            if(user_input == 'N')
                break;
            
            if(user_input == 'Y'){
                cout << "NEW calorie Limit: ";
                cin >> calorie_limit;
                cout << "NEW protein goal: ";
                cin >> protein_goal;

                cout << "\nGOALS HAVE BEEN UPDATED !!" << endl;
                break;
            }

            break;}
        //**************************************** CHECK PROGRESS ****************************************
        case 6:{
            cout << "Check Progress !! " << endl;

            for(int i = 0; i < 7; i++){
                cout << days_of_the_week[i] << endl;
                cout << "================\n" << endl;
                weekMeals[i]->DailyMeals::check_goals(calorie_limit, protein_goal);
                cout << "\n";
            }
            break;}

        //**************************************** EXIT PROGRAM ****************************************
        case 7:{ 
            printTop5Meals(topMeals, topMealsCount);
            cout << "\n";
            break;}

        //**************************************** EXIT PROGRAM ****************************************
        case 8:{
            cout << "Exiting Program !!" << endl;
            return 1;}

        //**************************************** INVALID INPUT ****************************************
        default:{
            cout << "Invalid option. Please select a value between 1 to 8" << endl;
            break;}
    }
    
    }
}
