#include "Project_Portal.h"

int main()
{
    int  option,validation,choice;
    Login L_obj;
    Notepad_File N_obj;

    L_obj.read_file();
    N_obj.read_file();

    while (1)
    {
        cout << "-----------------" << endl;
        cout << "User Login Portal" << endl;
        cout << "-----------------" << endl << endl;
        cout << "1. Sign In\n2. Sign Up\n3. Sign Out" << endl << endl;
        cout << "Select the Option : ";
        cin >> option;

        switch (option)
        {
            case 1:
                validation = L_obj.user_sign_in();
                if (validation)
                {
                    cout << "Implementing a Mini Notepad . . ." << endl << endl;
                    while (1)
                    {
                        cout << endl << "1. Create a New File\n2. View Already Created File\n3. Close" << endl << endl;
                        cout << "Select the Choice : ";
                        cin >> choice;

                        switch (choice)
                        {
                            case 1:
                                N_obj.new_file();
                                N_obj.write_file();
                                break;

                            case 2:
                                N_obj.old_file();
                                break;

                            case 3:
                                exit(0);

                            default:
                                cout << "Invalid Choice !" << endl;
                                break;
                        }
                    }
                }
                else
                {
                    cout << "Please Sign In Again or Sign Up " << endl;
                }
                break;

            case 2:
                L_obj.user_sign_up();
                break;

            case 3:
                //L_obj.display();
                cout << "Signed Out" << endl;
                exit(0);
            default:
                cout << "Invalid Option !" << endl;
                break;
        }
        L_obj.write_file();
    }
    return 0;
}