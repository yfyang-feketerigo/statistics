#include"input.h"
#include"statistics.h"
#include<boost/filesystem.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<json/json.h>
#include<boost/timer/progress_display.hpp>
#include<boost/timer/timer.hpp>
int main()
{
	try
	{
		boost::timer::auto_cpu_timer timer;
		void mkdir(std::string path);
		void throw_wrong_path(std::string path);

		Json::Value root;
		std::clog << "Reading stat_settings.json..." << endl;

		ifstream f_settings;
		f_settings.open("stat_settings.json", std::ios_base::binary);
		f_settings >> root;
		if (!f_settings.is_open())
		{
			std::cerr << "file \"stat_settings.json\" open failed" << endl;
			throw "file \"stat_settings.json\" open failed";
		}
		size_t rows = root["rows"].asLargestUInt();
		size_t stat_col = root["stat_col"].asLargestUInt();
		size_t headline = root["headline"].asLargestUInt();

		size_t distribution_size = root["distribution_size"].asLargestUInt();
		double distribution_min = root["distribution_min"].asDouble();
		double distribution_max = root["distribution_max"].asDouble();
		bool distribution_cut_flag = root["distribution_cut_flag"].asBool();

		std::string ifname_path = root["ifname_path"].asString();
		std::string ifname_prefix = root["ifname_prefix"].asString();
		std::string ifname_postfix = root["ifname_postfix"].asString();
		std::string ofname_path = root["ofname_path"].asString();
		std::string ofname_prefix = root["ofname_prefix"].asString();
		std::string ofname_postfix = root["ofname_postfix"].asString();
		std::string psfname_path = root["per_step_fname_path"].asString();
		std::string psfname = root["per_step_fname"].asString();
		size_t start_moment = root["start_moment"].asLargestUInt();
		size_t moment_number = root["moment_number"].asLargestUInt();
		size_t delta_step = root["delta_step"].asLargestUInt();
		size_t stop_step = moment_number * delta_step;
		size_t start_step = start_moment * delta_step;
		throw_wrong_path(ifname_path);
		mkdir(ofname_path);
		mkdir(psfname_path);

		std::clog << "Reading settings finished!" << std::endl;
		size_t per_step_size = (stop_step - start_step) / delta_step + 1;
		vector<double> max_per_step(per_step_size);
		vector<double> min_per_step(per_step_size);
		vector<double> mean_per_step(per_step_size);
		vector<double> variance_per_step(per_step_size);

		size_t i_ps = 0;
		std::clog << "Computing statistics..." << std::endl;
		boost::timer::progress_display pd(per_step_size);
		for (size_t istep = start_step; istep <= stop_step; istep += delta_step)
		{
			std::string ifname = ifname_path + ifname_prefix + std::to_string(istep) + ifname_postfix;
			Input indata(ifname, headline);
			indata.open_file();
			vector<double> vec_stat(rows, 0.);
			indata.skiphead();
			for (size_t i = 0; i < rows; i++)
			{
				indata.read_line_data();
				if (stat_col > indata.get_data().size())
				{
					cerr << "INVALID stat row number: " << stat_col;
					throw ("INVALID stat row number: " + std::to_string(stat_col));
				}
				vec_stat[i] = indata.get_data()[stat_col - 1];
			}
			Statistics stat(vec_stat, true, false);
			max_per_step[i_ps] = stat.get_maxim();
			min_per_step[i_ps] = stat.get_minimum();
			mean_per_step[i_ps] = stat.get_mean();
			variance_per_step[i_ps] = stat.get_variance();
			i_ps++;
			if (distribution_cut_flag == true)
			{
				stat.compute_distribution(distribution_size, distribution_min, distribution_max);
			}
			else
			{
				stat.compute_distribution(distribution_size);
			}
			std::string ofname = ofname_path + ofname_prefix + std::to_string(istep) + ofname_postfix;
			stat.get_distribution().to_csv(ofname);
			++pd;
		}

		std::ofstream ps_of;
		ps_of.open(psfname_path + psfname);
		if (!ps_of.is_open())
		{
			cerr << "open file: " << psfname_path + psfname << " failed." << std::endl;
			throw ("open file: " + psfname_path + psfname + " failed.");
		}
		ps_of << "# " << "step " << "min " << "max " << "mean " << "var " << std::endl;
		for (size_t i = 0; i < per_step_size; i++)
		{
			ps_of << i << " ";
			ps_of << start_step + i * delta_step << " ";
			ps_of << min_per_step[i] << " ";
			ps_of << max_per_step[i] << " ";
			ps_of << mean_per_step[i] << " ";
			ps_of << variance_per_step[i] << " ";
			ps_of << std::endl;
		}
		return 0;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const string e)
	{
		std::cerr << e << std::endl;
	};
}



void mkdir(std::string path)
{
	boost::filesystem::path bpath(path);
	if (!boost::filesystem::exists(path))
	{
		boost::filesystem::create_directories(bpath);
	}
}

void throw_wrong_path(std::string path)
{
	boost::filesystem::path boost_path_check(path);
	if (!(boost::filesystem::exists(boost_path_check) && boost::filesystem::is_directory(boost_path_check)))
	{
		//cerr << "data file path: " << boost_path_check << " not exits" << endl;
		throw path + " not exist!";
		//return false;
		//throw ("data file path: " + boost_path_check.string() + " not exits");
	}
	return;
}