#include "statistics.h"

Statistics::Statistics(std::vector<double> _data, bool flag_variance, bool flag_median)
{
	if (_data.empty())
	{
		std::cerr << "EMPTY data!" << std::endl;
		return;
	}
	data = _data;

	auto minmax = std::minmax_element(data.begin(), data.end());
	minimum = *(minmax.first);
	maxim = *(minmax.second);

	mean = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		mean += data[i];
	}
	mean /= data.size();

	if (flag_variance)
	{
		variance = 0;
		for (size_t i = 0; i < data.size(); i++)
		{
			variance = std::pow(data[i] - mean, 2);
		}
		variance /= data.size();
	}


	if (flag_median)
	{
		std::sort(_data.begin(), _data.end());
		if (_data.size() % 2 == 0)
		{
			double size = _data.size();
			median = (_data[size / 2 - 1] + _data[size / 2]) / 2;
		}
		else
		{
			median = _data[_data.size() / 2];
		}
	}
	return;
}

Distribution Statistics::compute_distribution(size_t size)
{
	Distribution _dstbt;
	_dstbt.max = maxim;
	_dstbt.min = minimum;
	double delta = (maxim - minimum) / (size - 1);
	//size_t size = (maxim - minimum) / delta + 1;
	_dstbt.distribution.resize(size, 0);
	for (size_t i = 0; i < data.size(); i++)
	{
		size_t index = floor((data[i] - minimum) / delta); //��������Сֵ������0���ٽ��зֲ�����
		_dstbt.distribution[index]++;
	}
	distribution = _dstbt;
	return _dstbt;
}

Distribution Statistics::compute_distribution(size_t size, double min, double max)
{
	Distribution _dstbt;
	_dstbt.max = max;
	_dstbt.min = min;
	double delta = (max - min) / size;
	out_range_counter = 0;
	_dstbt.distribution.resize(size, 0);
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] < max && data[i] >= min)
		{
			size_t index = floor((data[i] - minimum) / delta); //��������Сֵ������0���ٽ��зֲ�����
			_dstbt.distribution[index]++;
		}
		else
		{
			out_range_counter++;
		}
	}
	distribution = _dstbt;
	return _dstbt;
}



void Distribution::to_csv(std::string fname, std::string seq)
{
	std::ofstream ofile;
	ofile.open(fname);
	if (!ofile.is_open())
	{
		//std::cerr << "File " << fname << " open failed!" << std::endl;
		throw ("File " + fname + " open failed");
	}
	ofile << "mid" << seq << "left" << seq << "right" << seq << "distribution" << std::endl;
	for (size_t i = 0; i < distribution.size(); i++)
	{
		double delta = (max - min) / (distribution.size() - 1);
		double left = i * delta + min;
		double right = ((double)i + 1) * delta + min;
		double mid = (left + right) / 2;
		ofile << mid << seq << left << seq << right << seq << distribution[i];
		ofile << std::endl;
	}
	return;
}
