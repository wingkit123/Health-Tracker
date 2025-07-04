#include <iostream>
#include <string>
#include <iomanip>
// #include <vector> // REMOVED
// #include <limits> // REMOVED

using namespace std; // Added this line

// Forward declaration for friend function
class Person;
void suggestGeneralWaterIntake(const Person& p);

// ====================================================================
// Base Class: Person
// ====================================================================
class Person {
protected:
    string name;
    int age;
    float height_cm;
    float weight_kg;

public:
    // Default constructor
    Person() : name("Unknown"), age(0), height_cm(0.0f), weight_kg(0.0f) {}

    // Parameterized constructor
    Person(string n, int a, float h, float w)
        : name(n), age(a), height_cm(h), weight_kg(w) {}

    // Virtual destructor
    virtual ~Person() {
        // cout << "Person destructor for " << name << endl; // For debugging
    }

    // --- Getters ---
    string getName() const { return name; }
    float getWeight() const { return weight_kg; }
    int getAge() const { return age; }
    float getHeight() const { return height_cm; }


    // --- Core Functionality ---
    float calculateBMI() const {
        if (height_cm <= 0) return 0.0f;
        float height_m = height_cm / 100.0f;
        return weight_kg / (height_m * height_m);
    }

    void displayBasicInfo() const {
        cout << "\n--- Basic Information for " << name << " ---" << endl;
        cout << "Age: " << age << " years" << endl;
        cout << "Height: " << fixed << setprecision(2) << height_cm << " cm" << endl;
        cout << "Weight: " << fixed << setprecision(2) << weight_kg << " kg" << endl;
        float bmi = calculateBMI();
        cout << "BMI: " << fixed << setprecision(2) << bmi << " - ";
        if (bmi < 18.5) cout << "Underweight";
        else if (bmi < 24.9) cout << "Normal weight";
        else if (bmi < 29.9) cout << "Overweight";
        else cout << "Obese";
        cout << endl;
    }

    // Pure virtual function
    virtual void displayRecommendations() const = 0;

    // Virtual function for specific updates
    virtual void performSpecificUpdate() {
        cout << "No specific update actions available for this general profile." << endl;
    }
    
    // Virtual function to allow weight update
    virtual void updateWeight(float newWeight) {
        this->weight_kg = newWeight;
        cout << name << "'s weight updated to " << fixed << setprecision(2) << newWeight << " kg." << endl;
    }


    // Friend function declaration
    friend void suggestGeneralWaterIntake(const Person& p);
};

// Friend function definition
void suggestGeneralWaterIntake(const Person& p) {
    float waterIntakeLiters = p.weight_kg * 0.033f;
    cout << "\nGeneral daily water intake suggestion for " << p.name
              << ": " << fixed << setprecision(2) << waterIntakeLiters << " liters." << endl;
}

// ====================================================================
// Derived Class 1: DietaryAdvisor
// ====================================================================
class DietaryAdvisor : public Person {
private:
    int calorieGoal;
    float waterIntakeTarget_liters;

public:
    // Constructor
    DietaryAdvisor(string n, int a, float h, float w)
        : Person(n, a, h, w), calorieGoal(2000), waterIntakeTarget_liters(2.0f) {
        determineCalorieNeeds();
        setWaterIntakeTarget();
    }

    void determineCalorieNeeds() {
        float bmi = calculateBMI();
        if (bmi < 18.5) calorieGoal = 2500;
        else if (bmi < 24.9) calorieGoal = 2000;
        else calorieGoal = 1800;
    }

    void setWaterIntakeTarget() {
        waterIntakeTarget_liters = weight_kg * 0.035f;
    }

    void displayDietPlan() const {
        cout << "Recommended Daily Calorie Intake: " << calorieGoal << " kcal" << endl;
    }

    void displayHydrationInfo() const {
        cout << "Recommended Daily Water Intake: " << fixed << setprecision(2) << waterIntakeTarget_liters << " liters" << endl;
    }

    void displayRecommendations() const override {
        cout << "\n--- Dietary Recommendations for " << name << " ---" << endl;
        displayBasicInfo();
        displayDietPlan();
        displayHydrationInfo();
    }

    void performSpecificUpdate() override {
        cout << "\nUpdating Dietary Profile for " << name << ":" << endl;
        cout << "1. Recalculate Calorie and Water Goals" << endl;
        cout << "2. Log a meal (Feature not implemented)" << endl;
        cout << "Enter choice (1): ";
        int choice_val; // Renamed to avoid conflict with global 'choice' in main
        cin >> choice_val;
        if (cin.good() && choice_val == 1) {
            determineCalorieNeeds();
            setWaterIntakeTarget();
            cout << "Dietary goals have been re-evaluated." << endl;
        } else {
            cout << "Invalid choice or no action taken." << endl;
        }
        cin.clear();
        cin.ignore(1024, '\n');
    }
    
    void updateWeight(float newWeight) override {
        Person::updateWeight(newWeight);
        determineCalorieNeeds();
        setWaterIntakeTarget();
        cout << "Dietary goals re-evaluated for " << name << " due to weight change." << endl;
    }
};

// ====================================================================
// Derived Class 2: FitnessPlanner
// ====================================================================
class FitnessPlanner : public Person {
private:
    string primaryGoal;
    int stepsTakenToday;
    float distanceCoveredToday_km;

public:
    FitnessPlanner(string n, int a, float h, float w, string goal = "Maintenance")
        : Person(n, a, h, w), primaryGoal(goal), stepsTakenToday(0), distanceCoveredToday_km(0.0f) {}

    void suggestExerciseRegimen() const {
        cout << "Fitness Goal: " << primaryGoal << endl;
        float bmi = calculateBMI();
        if (primaryGoal == "Weight Loss" || bmi >= 25.0) {
            cout << "Recommended: 30-60 minutes of moderate cardio 5 days a week." << endl;
        } else if (primaryGoal == "Muscle Gain") {
            cout << "Recommended: 3-5 days of strength training." << endl;
        } else {
            cout << "Recommended: Balanced routine of 150 mins moderate aerobic activity/week." << endl;
        }
    }

    void updateActivity(int steps, float distance) {
        stepsTakenToday = steps;
        distanceCoveredToday_km = distance;
        cout << "Activity updated for " << name << ": " << steps << " steps, "
                  << fixed << setprecision(2) << distance << " km." << endl;
    }

    void displayActivityReport() const {
        cout << "Today's Activity: " << stepsTakenToday << " steps, "
                  << fixed << setprecision(2) << distanceCoveredToday_km << " km." << endl;
    }

    void displayRecommendations() const override {
        cout << "\n--- Fitness Recommendations for " << name << " ---" << endl;
        displayBasicInfo();
        suggestExerciseRegimen();
        displayActivityReport();
    }

    void performSpecificUpdate() override {
        cout << "\nUpdating Fitness Profile for " << name << ":" << endl;
        int steps;
        float distance;
        cout << "Enter steps taken today: ";
        cin >> steps;
        if (!cin.good() || steps < 0) {
            cout << "Invalid steps. Aborting update.\n";
            cin.clear();
            cin.ignore(1024, '\n');
            return;
        }
        cout << "Enter distance covered today (km): ";
        cin >> distance;
         if (!cin.good() || distance < 0) {
            cout << "Invalid distance. Aborting update.\n";
            cin.clear();
            cin.ignore(1024, '\n');
            return;
        }
        updateActivity(steps, distance);
        cin.ignore(1024, '\n');
    }
    
    void updateWeight(float newWeight) override {
        Person::updateWeight(newWeight);
        cout << "Consider reviewing fitness goals for " << name << " due to weight change." << endl;
    }
};

// ====================================================================
// Derived Class 3: SleepWellnessMonitor
// ====================================================================
class SleepWellnessMonitor : public Person {
private:
    float hoursSlept;
    int sleepQualityRating; 
    string bedtime;    
    string waketime;   

public:
    SleepWellnessMonitor(string n, int a, float h, float w)
        : Person(n, a, h, w), hoursSlept(0.0f), sleepQualityRating(0), bedtime("N/A"), waketime("N/A") {}

    void logSleep(float hours, int quality, const string& bt, const string& wt) {
        hoursSlept = hours;
        sleepQualityRating = quality;
        bedtime = bt;
        waketime = wt;
        cout << "Sleep logged for " << name << ": " << fixed << setprecision(1) << hours << " hours, Quality: " << quality
                  << "/5 (Bedtime: " << bt << ", Waketime: " << wt << ")" << endl;
    }

    void getSleepDurationAdvice() const {
        if (age >= 18 && age <= 64) {
            cout << "Recommended sleep (18-64 years): 7-9 hours." << endl;
        } else if (age >= 65) {
            cout << "Recommended sleep (65+ years): 7-8 hours." << endl;
        } else { 
            cout << "Consult specific guidelines for children/teens." << endl;
        }
    }

    void getSleepQualityTips() const {
        cout << "Tips for better sleep quality:\n"
                  << "- Maintain a consistent sleep schedule.\n"
                  << "- Create a restful environment.\n"
                  << "- Limit blue light before bed.\n";
    }

    void displaySleepSummary() const {
        cout << "Last Logged Sleep:\n"
                  << "  Duration: " << fixed << setprecision(1) << hoursSlept << " hours\n"
                  << "  Quality : " << sleepQualityRating << "/5\n"
                  << "  Bedtime : " << bedtime << ", Waketime: " << waketime << endl;
    }

    void displayRecommendations() const override {
        cout << "\n--- Sleep Wellness Recommendations for " << name << " ---" << endl;
        displayBasicInfo();
        getSleepDurationAdvice();
        displaySleepSummary();
        if (sleepQualityRating > 0 && sleepQualityRating < 3) {
            getSleepQualityTips();
        }
    }

    void performSpecificUpdate() override {
        cout << "\nLogging Sleep for " << name << ":" << endl;
        float hours;
        int quality_val; // Renamed to avoid conflict
        string bt, wt;

        cout << "Enter hours slept: ";
        cin >> hours;
        if(!cin.good() || hours < 0 || hours > 24) {
            cout << "Invalid hours. Aborting.\n";
            cin.clear();
            cin.ignore(1024, '\n');
            return;
        }

        cout << "Enter sleep quality (1-5): ";
        cin >> quality_val;
        if(!cin.good() || quality_val < 1 || quality_val > 5) {
            cout << "Invalid quality. Aborting.\n";
            cin.clear();
            cin.ignore(1024, '\n');
            return;
        }
        cin.ignore(1024, '\n'); 

        cout << "Enter bedtime (e.g., 10:30 PM): ";
        getline(cin, bt);
        cout << "Enter waketime (e.g., 06:30 AM): ";
        getline(cin, wt);

        logSleep(hours, quality_val, bt, wt);
    }
};

// ====================================================================
// Utility function for getting validated integer input
// ====================================================================
int getValidatedInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good() && value >= minVal && value <= maxVal) {
            cin.ignore(1024, '\n'); 
            return value;
        }
        cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(1024, '\n');
    }
}

float getValidatedFloat(const string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.good() && value >= minVal && value <= maxVal) {
            cin.ignore(1024, '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(1024, '\n');
    }
}


// ====================================================================
// Main Function
// ====================================================================
int main() {
    Person** users_array = nullptr; 
    int numUsers = 0;
    int currentUsersCount = 0; 

    cout << "=============================================" << endl;
    cout << "   Welcome to the Comprehensive Health Tracker " << endl;
    cout << "=============================================" << endl;

    numUsers = getValidatedInt("Enter number of users to track: ", 1, 100);
    users_array = new Person*[numUsers]; 

    for (int i = 0; i < numUsers; ++i) {
        users_array[i] = nullptr;
    }

    for (int i = 0; i < numUsers; ++i) {
        cout << "\n--- Entering details for User " << i + 1 << " ---" << endl;
        string name_val; 
        int age_val;
        float height_val, weight_val;

        cout << "Enter name: ";
        getline(cin, name_val); 
        if (name_val.empty() && i==0) { // Handle empty name on first user if previous input was from getValidatedInt
             getline(cin, name_val);
        }


        age_val = getValidatedInt("Enter age: ", 1, 120);
        height_val = getValidatedFloat("Enter height (cm): ", 50.0f, 300.0f);
        weight_val = getValidatedFloat("Enter weight (kg): ", 10.0f, 500.0f);

        cout << "\nSelect profile type for " << name_val << ":" << endl;
        cout << "1. Dietary Advisor" << endl;
        cout << "2. Fitness Planner" << endl;
        cout << "3. Sleep Wellness Monitor" << endl;
        int profileChoice = getValidatedInt("Enter choice (1-3): ", 1, 3);

        Person* newUser = nullptr;
        switch (profileChoice) {
            case 1:
                newUser = new DietaryAdvisor(name_val, age_val, height_val, weight_val);
                break;
            case 2: {
                string goal_val;
                cout << "Enter primary fitness goal (e.g., Weight Loss, Muscle Gain): ";
                getline(cin, goal_val);
                if (goal_val.empty()) getline(cin, goal_val);
                newUser = new FitnessPlanner(name_val, age_val, height_val, weight_val, goal_val);
                break;
            }
            case 3:
                newUser = new SleepWellnessMonitor(name_val, age_val, height_val, weight_val);
                break;
        }
        if (newUser) {
            users_array[i] = newUser; 
            currentUsersCount++;
            cout << name_val << "'s profile created successfully." << endl;
        }
    }
    
    int choice; // This is the main menu choice variable
    do {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Display All Users' Basic Info" << endl;
        cout << "2. Get Specific Recommendations for a User" << endl;
        cout << "3. Get General Water Intake Suggestion for a User" << endl;
        cout << "4. Perform Specific Update for a User" << endl;
        cout << "5. Update a User's Weight" << endl;
        cout << "6. Exit" << endl;
        choice = getValidatedInt("Enter your choice: ", 1, 6);

        int userIndexInput; 
        if (choice >= 2 && choice <= 5) {
            if (currentUsersCount == 0) {
                cout << "No users to operate on." << endl;
                continue;
            }
            string prompt_str = "Enter user number (1 to ";
            char buffer[10];
            // Using sprintf as a simple way for int to string conversion
            // that doesn't require C++11's std::to_string
            #if defined(_MSC_VER) // For Microsoft Visual C++
                sprintf_s(buffer, sizeof(buffer), "%d", currentUsersCount);
            #else // For GCC/Clang and other compilers
                sprintf(buffer, "%d", currentUsersCount);
            #endif
            prompt_str += buffer;
            prompt_str += "): ";
            userIndexInput = getValidatedInt(prompt_str, 1, currentUsersCount);
        }


        switch (choice) {
            case 1:
                if (currentUsersCount == 0) {
                    cout << "No users to display." << endl;
                } else {
                    cout << "\n--- All Users Basic Info ---" << endl;
                    for (int i = 0; i < currentUsersCount; ++i) {
                        if(users_array[i] != nullptr) { 
                           cout << "User " << i + 1 << ": ";
                           users_array[i]->displayBasicInfo();
                        }
                    }
                }
                break;
            case 2:
                if(userIndexInput -1 < currentUsersCount && users_array[userIndexInput -1] != nullptr)
                    users_array[userIndexInput - 1]->displayRecommendations();
                else if (currentUsersCount > 0) cout << "Invalid user selection." << endl;
                break;
            case 3:
                 if(userIndexInput -1 < currentUsersCount && users_array[userIndexInput -1] != nullptr)
                    suggestGeneralWaterIntake(*(users_array[userIndexInput - 1]));
                 else if (currentUsersCount > 0) cout << "Invalid user selection." << endl;
                break;
            case 4:
                if(userIndexInput -1 < currentUsersCount && users_array[userIndexInput -1] != nullptr)
                    users_array[userIndexInput - 1]->performSpecificUpdate();
                else if (currentUsersCount > 0) cout << "Invalid user selection." << endl;
                break;
            case 5: {
                if(userIndexInput -1 < currentUsersCount && users_array[userIndexInput -1] != nullptr) {
                    string name_of_user = users_array[userIndexInput-1]->getName();
                    string prompt_str = "Enter new weight (kg) for " + name_of_user + ": ";
                    float newWeightVal = getValidatedFloat(prompt_str, 10.0f, 500.0f);
                    users_array[userIndexInput - 1]->updateWeight(newWeightVal);
                } else if (currentUsersCount > 0) cout << "Invalid user selection." << endl;
                break;
            }
            case 6:
                cout << "Exiting Health Tracker. Stay healthy!" << endl;
                break;
        }
    } while (choice != 6);

    for (int i = 0; i < currentUsersCount; ++i) {
        if (users_array[i] != nullptr) {
            delete users_array[i]; 
            users_array[i] = nullptr; 
        }
    }
    delete[] users_array; 
    users_array = nullptr; 

    return 0;
}