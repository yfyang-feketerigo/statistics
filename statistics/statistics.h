/*
class Statistics :统计类，用于统计一维数据，可计算：
	最大值最小值，均值，中位数，分布
	该类在调用构造函数时自动计算最大值、最小值、中位数
	计算分布需要调用方法compute_distribution
struct Distribution：分布结构，储存分布数据类型。
*/
#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
struct Distribution
{
	double min = 0; //分布下限
	double max = 0; //分布上限
	std::vector<double> distribution; //分布
	void normalization() //归一化
	{
		double sum = 0;
		for (size_t i = 0; i < distribution.size(); i++)
		{
			sum += distribution[i];
		}
		for (size_t i = 0; i < distribution.size(); i++)
		{
			distribution[i] /= sum;
		}
		return;
	}
	void to_csv(std::string fname, std::string seq = " "); //输出到文件，seq指明分割符
};

class Statistics
{
private:
	std::vector<double> data; //raw data
	double mean = 0; //均值
	double median = 0; //中位数
	double maxim = 0; //最大值
	double minimum = 0; //最小值
	double variance = 0; //方差
	Distribution distribution; //分布
	size_t out_range_counter = 0;//在使用指定范围的统计分布时，计量超过范围的数据数量

public:
	Statistics(std::vector<double> _data, bool flag_variance = true, bool flag_median = true); //构造函数
	Distribution compute_distribution(size_t size); //计算分布
	Distribution compute_distribution(size_t size, double min, double max);//计算分布，指定最大最小值

	inline double get_mean() { return mean; } //返回平均值
	inline double get_median() { return median; } //返回中位数
	inline double get_maxim() { return maxim; } //返回最大值
	inline double get_minimum() { return minimum; } //返回最小值
	inline double get_variance() { return variance; } //返回方差
	inline double get_out_range_counter() { return out_range_counter; }//返回超范围数据数
	inline std::vector<double> get_data() { return data; } //返回原始数据
	inline Distribution get_distribution() { return distribution; } //返回分布
	inline void sort() //从小到大排序
	{
		std::sort(data.begin(), data.end());
	}
};
