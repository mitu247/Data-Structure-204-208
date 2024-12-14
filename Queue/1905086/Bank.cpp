#include "Arr.cpp"
#include "LL.cpp"
#include <iostream>
using namespace std;

class Customer
{
public:
    int enterTime;
    int serviceTime;
    int leaveTime;
    Customer() {}
    Customer(int enterTime, int serviceTime)
    {
        this->enterTime = enterTime;
        this->serviceTime = serviceTime;
        leaveTime = enterTime + serviceTime;
    }
};

int main()
{
    int n, elapsedTime = 0;
    cin >> n;

    Arr<Customer> queue1;
    Arr<Customer> queue2;

    int booth1 = 0, booth2 = 0, totalServices = 0;

    while (totalServices != n) {
        int entryTime, serviceTime;
        cin >> entryTime >> serviceTime;
        totalServices++;
        Customer customer(entryTime, serviceTime);

        if (queue1.length() == 0 && queue2.length() == 0) {
            if (booth1 <= entryTime) {
                queue1.enqueue(customer);
            }
            else if (booth2 <= entryTime) {
                queue2.enqueue(customer);
            }
            else {
                queue1.enqueue(customer);
            }
        }
        else if (queue1.length() <= queue2.length()) queue1.enqueue(customer);
        else queue2.enqueue(customer);

        while ((booth1 <= entryTime && queue1.length()) || (booth2 <= entryTime && queue2.length())) {
            if (booth1 <= entryTime && queue1.length()) {
                Customer customer = queue1.dequeue();
                booth1 = booth1 < customer.enterTime? customer.leaveTime:booth1+customer.serviceTime;
            }

            if (booth2 <= entryTime && queue2.length()) {
                Customer customer = queue2.dequeue();
                booth2 = booth2 < customer.enterTime? customer.leaveTime:booth2+customer.serviceTime;
            }

            while((queue1.length() - queue2.length() >= 2) && queue1.length()) {
                Customer rogue = queue1.leaveQueue();
                queue2.enqueue(rogue);
            }
            while((queue2.length() - queue1.length() >= 2) && queue2.length()) {
                Customer rogue = queue2.leaveQueue();
                queue1.enqueue(rogue);
            }
        }
    }
    if (booth1 >= booth2) elapsedTime = booth2;
    else elapsedTime = booth1;

    while (queue1.length() || queue2.length()) {
        if (booth1 <= elapsedTime && queue1.length()) {
                Customer customer = queue1.dequeue();
                booth1 = booth1 < customer.enterTime? customer.leaveTime:booth1+customer.serviceTime;
            }
            if (booth2 <= elapsedTime && queue2.length()) {
                Customer customer = queue2.dequeue();
                booth2 = booth2 < customer.enterTime? customer.leaveTime:booth2+customer.serviceTime;
            }
            while((queue1.length() - queue2.length() >= 2) && queue1.length()) {
                Customer rogue = queue1.leaveQueue();
                queue2.enqueue(rogue);
            }
            while((queue2.length() - queue1.length() >= 2) && queue2.length()) {
                Customer rogue = queue2.leaveQueue();
                queue1.enqueue(rogue);
            }
            elapsedTime++;
    }
    cout << "Booth-1 finishes service at, t = " << booth1 << endl;
    cout << "Booth-2 finishes service at, t = " << booth2 << endl;

    return 0;
}
