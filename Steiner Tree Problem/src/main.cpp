#include "../include/GA.hpp"
#include "../include/RandomSlack.hpp"

using namespace std;

int main()
{
    string path;
    printf("Please enter the file name(e.g. b01): ");
    cin>>path;
    int choice;
    printf("Which algorithm do u want to use?\n 1.GA\t2.RandomSlack\nTips: -1 to exit\n");
    cin>>choice;

    if(choice == 1) {
        GA g;
        g.exec(path);
    } else if (choice == 2) {
        RandomSlack r;
        r.exec(path);
    } else {
        printf("Error: Invalid input! The program will be killed in 5s.\n");
        sleep(5);
    }
    
    return 0;
}