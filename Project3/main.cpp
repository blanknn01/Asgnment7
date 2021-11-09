#include<iostream>
#include"Text_Preprocessor.h"
#include<thread>
#include<mutex>
mutex locker;
void avg_high(fstream& file, double avg) 
{
    lock_guard<mutex> g_lock(locker);
    double n;
    if (file.is_open()) {
        while (file >> n) {
           
            if (n >= avg) {
                ofstream thread1_file("Thread1.txt", ios::app | ios::ate);
                if (thread1_file.is_open()) {
                    thread1_file << n<<endl;
                    thread1_file.close();
                }
                else {
                    cout << "File not found" << endl;
                }
            }
        }
    }
}

void avg_below(fstream& file, double avg)
{
    lock_guard<mutex> g_lock(locker);
    double n;
    if (file.is_open()) {
        while (file >> n) {
            if (n < avg) {
                ofstream thread2_file("Thread2.txt", ios::app | ios::ate);
                if (thread2_file.is_open()) {
                    thread2_file << n << endl;
                    thread2_file.close();
                }
                else {
                    cout << "File not found" << endl;
                }
            }
        }
    }
    
}
double calculate_avg(fstream& file)
{
    int amount = 0;
    double all_sum = 0;
    double n = 0;
    if (file.is_open())
    {
        while (file >> n) {
            all_sum += n;
            amount++;
        }
    } 
    return all_sum / amount;
}
int main() {


    Text_Preprocessor text("Text.txt");
    text.preprocess_text();
    Text_Preprocessor text2("Text.txt");
    string key_word;
    cout << "Looking for: ";
    cin >> key_word;
    int search_result = text2.search_word(key_word);
    if (search_result != 0) {
        cout << "Found in " << search_result;
    }
    else {
        cout <<  "Not found" << endl;
    }
    cout << endl << endl << endl;

    fstream file("task2.txt");
    double avg = calculate_avg(file);
    file.close();
    file.open("task2.txt");
    thread thread1(avg_high, ref(file), ref(avg));
    thread1.join();
    file.close();
    file.open("task2.txt");
    thread thread2(avg_below, ref(file), ref(avg));
    thread2.join();
    cout << "avarage is: "<<avg<<endl;
    cout << "Also check, Thread1.txt and Thread2.txt";




    

  

}