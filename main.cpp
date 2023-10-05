#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_QUEUE = 5;
const int MAX_SPECIALIZATION = 20;

struct hospital_queue
{
    string names[MAX_QUEUE];
    int status[MAX_QUEUE];
    int len;
    int spec;

    hospital_queue()
    {
        len = 0;
    }
    hospital_queue(int spec_)
    {
        len = 0;
        spec = spec_;
    }
    bool add_end(string name, int st)
    {
        if (len == MAX_QUEUE)
            return false;

        names[len] = name;
        status[len] = st;
        len++;
        return true;
    }

    bool add_front(string name, int st)
    {
        if (len == MAX_QUEUE)
            return false;

        for (int i = len - 1; i >= 0; i--)
        {
            names[i + 1] = names[i];
            status[i + 1] = status[i];
        }
        names[0] = name;
        status[0] = st;
        len++;
        return true;
    }
    void remove_front()
    {
        for (int i = 0; i < len - 1; i++)
        {
            names[i] = names[i + 1];
            status[i] = status[i + 1];
        }
        len--;
    }
    void print()
    {
        for (int i = 0; i < len; i++)
        {
            cout << names[i] << " ";
            if (status[i] == 1)
                cout <<"Urgent\n";
            else if (status[i] == 0)
                cout << "Regular\n";
        }

    }


};
struct hospital_system
{
    hospital_queue queues[MAX_SPECIALIZATION];

    int menu()
    {
        int choice = -1;
        while (choice == -1)
        {
            cout <<"Enter your choice: "<<endl;
            cout <<"1) Add new patient\n2) Print all patients\n3) Get next patient\n4) Exit\n";
            cin >> choice;
            if (!(choice >= 1 && choice <= 4))
                choice = -1;
        }
        return choice;
    }
    int run()
    {
        while (true)
        {
            int choice = menu();
            if (choice == 1)
                add_patient();
            else if (choice == 2)
                print_patients();
            else if (choice == 3)
                get_next();
            else if (choice == 4)
                break;
            cout <<endl;
        }
    }
    bool add_patient()
    {
        string name;
        int status, spec;
        cout << "Enter your specialization, name, and status: \n";
        cin >> spec >> name >> status;
        hospital_queue patient = queues[spec - 1];
        bool flag;
        if (status == 0)
            flag = patient.add_end(name, status);
        else if (status == 1)
            flag = patient.add_front(name, status);
        if (!flag)
            cout << "Queue is full!";
        else
        {
            queues[spec - 1] = patient;
            cout << "Patient added successfully!\n\n";
        }

    }
    void print_patients()
    {

        for (int i = 0; i < MAX_SPECIALIZATION; i++)
        {
            hospital_queue test = queues[i];
            if (!test.len)
                continue;
            cout << "There are " << test.len << " patients in specialization " << (i + 1) << endl;
            test.print();
        }
    }
    void get_next()
    {
        int spec;
        cout <<"Enter specialization: "<<endl;
        cin >> spec;
        hospital_queue test = queues[spec - 1];
        cout<<test.names[0]<<" please go with the Dr."<<endl;
        test.remove_front();
        queues[spec - 1] = test;
    }
};

int main()
{

    hospital_system hospital = hospital_system();
    hospital.run();


	return 0;
}
