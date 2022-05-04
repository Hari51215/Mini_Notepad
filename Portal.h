#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Login_setup.pb.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

Userportal::User_file person;
int user_id;

class Login
{
    protected:
        string user_name, email, location, password;
        int individual_id = 10000, age = 0;

    public:
        string encryption(string str)
        {
            for (int i = 0; i < str.size(); ++i)
            {
                char c = ((str[i] - 'a' + 2) % 26) + 'a';
                str[i] = c;
            }
            return str;
        }

        void read_file()
        {
            std::fstream input("login_Details.bin", std::ios::in | std::ios::binary);
            if (!person.ParseFromIstream(&input))
                std::cerr << "Login_details.bin , File not Found" << endl;
            individual_id += person.candidate_size();
        }

        void write_file()
        {
            std::fstream output("login_Details.bin", std::ios::out | std::ios::trunc | std::ios::binary);
            if (!person.SerializeToOstream(&output))
                std::cerr << "Failed to Write the Details in File";
        }

        bool user_sign_in()
        {
            string mail,De_mail,passkey,De_passkey;
            cout << "Enter the Email ID : ";
            cin >> mail;
            for (int i = 0; i < person.candidate_size(); ++i)
            {
                if (person.candidate(i).email() == encryption(mail))
                {
                    cout << "Enter the Password : ";
                    cin >> passkey;

                    if (person.candidate(i).password() == encryption(passkey))
                    {
                        cout << endl<< "Logged In Successfully !" << endl;
                        return 1;
                    }
                    else
                        cout << "Incorrect / Wrong Password !" << endl;
                }
            }
            if (person.candidate_size() == 0)
            {
                cout << "No Details Found in the File." << endl;
            }
            return 0;
        }

        void user_sign_up()
        {
            string user_email, user_password;
            cout << "Enter the Email ID : ";
            cin >> email;
            cout << "Enter the Password : ";
            cin >> password;
            cout << "Enter the User Name : ";
            cin >> user_name;
            cout << "Enter the Location : ";
            cin >> location;
            cout << "Enter the Age : ";
            cin >> age;

            user_email = encryption(email);
            user_password = encryption(password);
            user_id = individual_id++;

            Userportal::User_data* user = person.add_candidate();
            user->set_email(user_email);
            user->set_password(user_password);
            user->set_user_name(user_name);
            user->set_user_id(user_id);
            user->set_location(location);
            user->set_age(age);
            cout << endl;
        }

        void display()
        {
            for (int i = 0; i < person.candidate_size(); ++i)
            {
                Userportal::User_data user = person.candidate(i);
                cout << "Email : " << user.email() << endl;
                cout << "Password : " << user.password() << endl;
                cout << "Name : " << user.user_name() << endl;
                cout << "ID : " << user.user_id() << endl;
                cout << "Location : " << user.location() << endl;
                cout << "Age : " << user.age() << endl;
                cout << endl;
            }
        }
};