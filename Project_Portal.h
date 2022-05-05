#pragma once

#include <time.h>
#include "Portal.h"
#include "Project_versions.pb.h"

Userportal::User_data file;
Userportal::Project_portal version;
Version_control::File_version control;

class Notepad_File
{
protected:

	int file_id = 1000;
	int version_id = 100;
	string project_name;
	char C_time[30];
	int project_id, select, P_ID;
	int action = 1, version_num = 1;

public:

	void read_file()
	{
		std::fstream input("Project_Details.bin", std::ios::in | std::ios::binary);
		if (!file.ParseFromIstream(&input))
			std::cerr << "Project_Details.bin , File not Found" << endl;
		file_id += file.projects_size();
	}

	void write_file()
	{
		std::fstream output("Project_Details.bin", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!file.SerializeToOstream(&output))
			std::cerr << "Failed to Write the Details in File";
	}

	void read_version()
	{
		std::fstream input("Versions.bin", std::ios::in | std::ios::binary);
		if (!version.ParseFromIstream(&input))
			std::cerr << "Versions.bin , File not Found" << endl;
		version_id += version.versions_size();
	}

	void write_version()
	{
		version_id++;
		File_version* v = version.add_versions();
		v->set_version_id(version_id);
		v->set_projectid(project_id);


		Version_control::Versioning* c = control.add_commit();
		c->set_actions(action);
		c->set_version_no(version_num);

		time_t result = time(NULL);
		ctime_s(C_time, sizeof C_time, &result);
		c->set_created_time(C_time);
		c->mutable_content();


		std::fstream output("Versions.bin", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!version.SerializeToOstream(&output))
			std::cerr << "Failed to Write the Details in File" << endl;
	}

	void new_file()
	{
		cout << "Enter the File Name  : ";
		cin >> project_name;
		project_id = file_id++;
		cout << "Your File ID : " << project_id << endl;

		Userportal::Project_portal* f = file.add_projects();
		f->set_project_name(project_name);
		f->set_project_id(project_id);
		f->set_userid(user_id);

		std::ofstream textfile(std::to_string(project_id) + ".txt");
		cout << "File Created Successfully" << endl << endl;

		write_version();
	}

	void old_file()
	{
		cout << "Total Existing File : " << file.projects_size() << endl << endl;

		cout << "Enter the File ID  : ";
		cin >> P_ID;

		for (int i = 0; i < file.projects_size(); ++i)
		{
			if (file.projects(i).project_id() == P_ID)
			{
				cout << "1. Add Content\n2. Update Content\n3. Remove Content\n4. Display Content\n5. Revert Version" << endl << endl;
				cout << "Select your option, To perform the action : ";
				cin >> select;
				cout << endl;

				switch (select)
				{
				case 1:
					add_content(P_ID);
					action++;
					break;

				case 2:
					update_content(P_ID);
					action++;
					break;

				case 3:
					remove_content(P_ID);
					action++;
					break;

				case 4:
					display_content(P_ID);
					break;

				case 5:
					revert_version();
					break;

				default:
					cout << "Option Not Available." << endl;
				}
				if (action == 5)
				{
					version_num++;
					action = 0;
					write_version();
				}
			}
		}
		if (file.projects_size() == 0)
		{
			cout << "No Files Found." << endl;
		}
	}

	void add_content(int P_ID)
	{
		string add_text;
		project_id = P_ID;
		std::fstream textfile;

		cout << "Enter the Content to be added into the File : " << endl;
		cin.ignore();
		getline(cin, add_text);

		textfile.open(std::to_string(project_id) + ".txt", std::ios::app | std::ios::out);
		if (textfile.is_open())
		{
			textfile << add_text;
			textfile.close();
		}
		cout << "Content Successfully Added into the File" << endl << endl;
	}

	void update_content(int P_ID)
	{
		string update, oldline, newline, readline;
		int option = 0;

		project_id = P_ID;
		std::fstream textfile;

		cout << "1. Overwrite a Particular Line.\n2. Overwrite the Entire Document." << endl << endl;
		cout << "Select the option : ";
		cin >> option;

		if (option == 1)
		{
			cout << "Enter the Existing Line, Needs to be Overwrite with New Line : " << endl;
			cin.ignore();
			getline(cin, oldline);

			cout << "Enter the New Line, Needs to be Overwrite with Existing Line : " << endl;
			cin.ignore();
			getline(cin, newline);

			textfile.open(std::to_string(project_id) + ".txt", std::ios::in | std::ios::out);
			if (textfile.is_open())
			{
				while (getline(textfile, readline))
				{
					textfile << readline.replace(readline.find(oldline), oldline.length(), newline);
				}
				textfile.close();
			}
		}
		else if (option == 2)
		{
			cout << "Enter the Content to Overwrite the Entire Document : " << endl;
			cin.ignore();
			getline(cin, update);

			textfile.open(std::to_string(project_id) + ".txt", std::ios::out | std::ios::trunc);
			if (textfile.is_open())
			{
				textfile << update;
				textfile.close();
			}
		}
		else
			cout << "Invalid Option !" << endl;
	}

	void remove_content(int P_ID)
	{
		string removeline, readline;
		int option = 0;

		project_id = P_ID;
		std::fstream textfile;

		cout << "1. Remove a Particular Line.\n2. Remove the Entire Document." << endl << endl;
		cout << "Select the option : ";
		cin >> option;

		if (option == 1)
		{
			textfile.open(std::to_string(project_id) + ".txt");
			cout << "Which line do you want to remove ?" << endl;
			cin.ignore();
			getline(cin, removeline);

			if (textfile.is_open())
			{
				while (getline(textfile, readline))
				{
					readline.replace(readline.find(removeline), removeline.length(), "");
				}
				textfile.close();
			}
		}
		else if (option == 2)
		{
			textfile.open(std::to_string(project_id) + ".txt", std::ios::out | std::ios::trunc);
			textfile.close();
		}
		else
			cout << "Invalid Option !" << endl;
	}

	void display_content(int P_ID)
	{
		project_id = P_ID;
		std::fstream textfile;
		textfile.open(std::to_string(project_id) + ".txt", std::ios::in);
		if (textfile.is_open())
		{
			string display_text;
			while (getline(textfile, display_text))
			{
				cout << display_text << endl;
			}
			textfile.close();
		}
	}

	void revert_version()
	{
		int V_id = 0, V_num = 0;

		std::fstream input("Versions.bin", std::ios::in | std::ios::binary);
		if (!version.ParseFromIstream(&input))
			std::cerr << "Versions.bin , File not Found" << endl;

		cout << "Enter the Version ID : ";
		cin >> V_id;

		for (int i = 0; i < version.versions_size(); ++i)
		{
			if (version.versions(i).version_id() == V_id)
			{
				cout << "Enter the Version Number, To Revert : ";
				cin >> V_num;
				if (version.versions(i).version_no() == V_num)
				{
					P_ID = version.versions(i).projectid();
					display_content(P_ID);
				}
			}
		}
	}

	void display()
	{
		for (int i = 0; i < file.projects_size(); ++i)
		{
			Userportal::Project_portal f = file.projects(i);
			cout << endl << "Project Name : " << f.project_name() << endl;
			cout << "Project ID : " << f.project_id() << endl;

			cout << endl;
		}

		cout << endl;

		for (int i = 0; i < version.versions_size(); ++i)
		{
			File_version v = version.versions(i);
			cout << "Actions : " << v.actions() << endl;
			cout << "Version ID : " << v.version_id() << endl;
			cout << "Version Number :  " << v.version_no() << endl;
			cout << "Created Time : " << v.created_time();
			cout << "Project ID : " << v.projectid() << endl;

			cout << endl;
		}
	}
};