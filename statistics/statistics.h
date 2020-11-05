/*

class Statistics :ͳ���࣬����ͳ��һά���ݣ��ɼ��㣺
	���ֵ��Сֵ����ֵ����λ�����ֲ�

	struct Distribution���ֲ��ṹ������ֲ��������͡�
*/
#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>	
struct Distribution
{
	double min = 0; //�����е���Сֵ
	double max = 0; //�����е����ֵ
	std::vector<double> distribution; //�ֲ�
	void normalization() //��һ��
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
	void to_csv(std::string fname, std::string seq = " "); //������ļ�
};

class Statistics
{
private:
	std::vector<double> data; //raw data
	double mean = 0; //��ֵ
	double median = 0; //��λ��
	double maxim = 0; //���ֵ
	double minimum = 0; //��Сֵ
	double variance = 0; //����
	Distribution distribution; //�ֲ�
	size_t out_range_counter = 0;

public:
	Statistics(std::vector<double> _data, bool flag_variance = true, bool flag_median = true); //���캯��
	Distribution compute_distribution(size_t size); //����ֲ�
	Distribution compute_distribution(size_t size, double min, double max);//����ֲ���ָ�������Сֵ

	inline double get_mean() { return mean; } //����ƽ��ֵ
	inline double get_median() { return median; } //������λ��
	inline double get_maxim() { return maxim; } //�������ֵ
	inline double get_minimum() { return minimum; } //������Сֵ
	inline double get_variance() { return variance; } //���ط���
	inline std::vector<double> get_data() { return data; } //����ԭʼ����
	inline Distribution get_distribution() { return distribution; } //���طֲ�
	inline void sort() //��С��������
	{
		std::sort(data.begin(), data.end());
	}
};