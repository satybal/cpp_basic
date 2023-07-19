#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "high_scores.h"

const std::string high_scores_filename = "high_scores.txt";
const std::string temp_filename = "temp.txt";

void save_results(const std::string &user_name, const int attempts) {
	std::filesystem::copy(high_scores_filename, temp_filename, std::filesystem::copy_options::overwrite_existing);

	{  // add new record 
		std::ofstream out_file {high_scores_filename, std::ios_base::trunc};
		std::ifstream in_file {temp_filename};
		
		if (!out_file.is_open() || !in_file.is_open()) {
			std::cout << "Failed to open file: " << high_scores_filename << "!" << std::endl;
		}

		std::string current_user;
		int user_record;
		bool user_exists = false;

		while (true) {
			in_file >> current_user;
			in_file >> user_record;
			in_file.ignore();

			if (in_file.fail() && user_exists) break; // user is already exist in the table
													  // and file overwritten
			
			else if (in_file.fail()) { // adding new user in the table
				out_file << user_name << ' ' << attempts << std::endl;

				break;
			} else {  // rewriting line by line checking user record
		    	out_file << current_user << ' ';

				if (current_user == user_name) {
			     	out_file << (user_record < attempts ? user_record : attempts);
				    user_exists = true;
				}
				else out_file << user_record;

		    	out_file << std::endl;
			}
		}
	}
	show_high_scores();
}

void show_high_scores() {
	{
		std::ifstream in_file {high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		}

		int score;
		std::string usr;

		std::cout << "High scores table:" << std::endl;

		while (true) {
			in_file >> usr;
			in_file >> score;
			in_file.ignore();

			if (in_file.fail()) break;

			std::cout << usr << " " << score << std::endl;
		}
	}
}
