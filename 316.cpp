#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<cmath>
using namespace std;

/*The Definition of Constant*/
#define POPSIZE 500 //population size //
#define MAXIMIZATION 1 //maximization flag
#define MINIMIZATION 2 //minimization flag
/*�������в���*/
#define Cmax 100//certain maximal value
#define Cmin 0 //certain minimun value
#define LENGTH1 9//the chromosome length of 1st variable�ַ�������Ϊ9
#define LENGTH2 9//the chromosome length of 2nd variable�ַ�������Ϊ9
#define CHROMLENGTH LENGTH1 + LENGTH2 //�����ַ������ϳ�һ�����干20λ�����ɻ�����
int FunctionMode = MAXIMIZATION;//optimization type���Ż��ͣ�
int PopSize = 80;//population size��ʼ��Ⱥ���СΪ80
int MaxGeneration = 200;//��������
double Pc = 0.6;//probability of mutation���ý������
double Pm = 0.01;//probability of mutation���ñ������
/*The Definition of Data Structure*/
struct individual//�������ݽṹ
{
	char chrom[CHROMLENGTH + 1];//һ������Ⱦɫ��
	double value;//object value of this individual ����ĺ���ֵ
	double fitness;//fitness value of this individual �������Ӧ��ֵ
};
/*ȫ�ֱ���*/
int generation;//number of generation
int best_index;//index of best individual����ø����±꣩
int worst_index;//index of worst individua
struct individual bestindividual;//best individual of current generation��struct��һ�ֽṹ�壬���԰��������ͬ���͵ı�����
struct individual worstindividual;//worst individual of current generation
struct individual currentbest;//best individual by now��������õģ�
struct individual population[POPSIZE];//population
/*Declaration of Prototype���溯����ԭ��*/
void GenerateInitialPopulation();
void GenerateNextPopulation();
void EvaluatePopulation();
long DecodeChromosome(char*, int, int);
void CalculateObjectValue();
void CalculateFitnessValue();
void FindBestAndWorstIndividual();
void PerformEvolution();
void SelectionOperator();
void CrossoverOperator();
void MutationOperator();
void OutputTextReport();
int main()
{
	generation = 0;//��ʼ��P(0)
	GenerateInitialPopulation();//������ʼȺ�壬���ó�ʼȺ��
	EvaluatePopulation();//��ʼȺ����Ӧ�ȼ���
	while (generation < MaxGeneration) {
		generation++;
		GenerateNextPopulation();
		EvaluatePopulation();
		PerformEvolution();
		OutputTextReport();
	}
system ("pause");	
return 0;
}
/*Function:Generate the first population.������������
Variable:None.*/
void GenerateInitialPopulation()
{
	int i, j;
	int flag = 1;
	srand((unsigned)time(NULL));
	for (i = 0; i < PopSize; i++)
	{
		for (j = 0; j < CHROMLENGTH; j++)
		{
			population[i].chrom[j] = (rand() % 10 < 5) ? '0' : '1';//���������10ȡģ����
		}
		population[i].chrom[CHROMLENGTH] = '\0';//�ַ���������־����ֹ����
	}
}
/*Function:Initialize the first generation
Variable:None*/
void GenerateNextPopulation()
{
	SelectionOperator();
	CrossoverOperator();
	MutationOperator();
}
/*Function:Evaluate population according to certain formula
Variable:None*/
void EvaluatePopulation()
{
	CalculateObjectValue();//calculate object value
	CalculateFitnessValue();//calculate fitness value
	FindBestAndWorstIndividual();//find the best and worst individual
}
/*Function:��������Ⱦɫ�����Ϊʮ��������.
Variable:None.
Note:The returned value may be plus,or minus.For different coding method,this
value may be changed into "unsigned int".*/
long DecodeChromosome(char* string, int point, int length)
{
	int i;
	long decimal = 0L;
	char* pointer;
	for (i = 0, pointer = string + point; i < length; i++, pointer++)
	{
		decimal += (*pointer - '0') << (length - 1 - i);
	}
	return (decimal);
}
/*Function:To calcluate object value.����Ⱥ����ÿ�������Ŀ�꺯��ֵ
Variable:None.
note:For different problem, user must change these code.
This example is dealing with Rosenbrock function.
Rosenbrock function is defined as:
f(x1,x2)=100*(x1^2-x2)^2+(1-x1)^2
Its maximal value is:
f(-2.048,-2.048)=3905.926227*/
void CalculateObjectValue()
{
	int i;
	long temp1, temp2;
	double x1, x2;
	//Rosenbrock function
	for (i = 0; i < PopSize; i++)
	{
		temp1 = DecodeChromosome(population[i].chrom, 0, LENGTH1);//�����ƶ�Ӧ��ʮ���Ƶ�ֵ
		temp2 = DecodeChromosome(population[i].chrom, LENGTH1, LENGTH2);
		x1 = 4.096 * temp1 / 1023.0 - 2.048;
		x2 = 4.096 * temp2 / 1023.0 - 2.048;
		population[i].value = sin(x1 * x1) + (1 + x2) * (1 + x2) + exp(x1);
	}
}
/*Function:To calculate fitness value.
Variable:None.ǰ���Ѿ�����ø���Ŀ�꺯��ֵ��Ŀ�꺯��f(x)����Ӧ�Ⱥ���F(x)��ת����ϵ*/
void CalculateFitnessValue()
{
	int i;
	double temp;
	for (i = 0; i < PopSize; i++)
	{
		if (FunctionMode == MAXIMIZATION)//maximization��Ŀ�꺯�������ֵ��ǰ�涨��Cmin=0
		{
			if ((population[i].value + Cmin) > 0.0)
			{
				temp = Cmin + population[i].value;
			}
			else
			{
				temp = 0.0;
			}
		}
		else if (FunctionMode == MINIMIZATION)//minimization��Ŀ�꺯����Сֵ,Cmax=100
		{
			if (population[i].value < Cmax)
			{
				temp = Cmax - population[i].value;
			}
			else
			{
				temp = 0.0;
			}
		}
		population[i].fitness = temp;
	}
}
/*Function:To Find out the best individual so far current generation.
Variable:None.*/
void FindBestAndWorstIndividual()
{
	int i;
	double sum = 0.0;
	//find out the best and worst individual of this generation
	bestindividual = population[0];
	worstindividual = population[0];
	for (i = 1; i < PopSize; i++)
	{
		if (population[i].fitness > bestindividual.fitness)
		{
			bestindividual = population[i];
			best_index = i;
		}
		else if (population[i].fitness < worstindividual.fitness)
		{
			worstindividual = population[i];
			worst_index = i;
		}
		sum += population[i].fitness;//sum = sum+population[i].fitness
	}
	//find out the best individual so far
	if (generation == 0)
	{
		//initialize the best individual
		currentbest = bestindividual;
	}
	else
	{
		if (bestindividual.fitness > currentbest.fitness)
		{
			currentbest = bestindividual;
		}
	}
}
/*Function:To perform evolution operation based on elitise
model.Elitist model is to replace the worst
individual of this generation by the current
best one.��Ӣģʽ����õ�ȡ�����ĸ���
Variable:None.*/
void PerformEvolution()
{
	if (bestindividual.fitness > currentbest.fitness)
	{
		currentbest = population[best_index];
	}
	else
	{
		population[worst_index] = currentbest;
	}
}
/*Function:To reproduce a chromosome by
proportional selection.
Variable:None.*/
void SelectionOperator()
{
	int i, index;
	double p, sum = 0.0;
	double cfitness[POPSIZE];//cumulative fitness value
	struct individual newpopulation[POPSIZE];
	//calculate relative fitness���������Ӧ��
	for (i = 0; i < PopSize; i++)
	{
		sum += population[i].fitness;
	}
	for (i = 0; i < PopSize; i++)
	{
		cfitness[i] = population[i].fitness / sum;
	}
	//calculate cumulative fitness�ۼ���Ӧ��
	for (i = 1; i < PopSize; i++)
	{
		cfitness[i] = cfitness[i - 1] + cfitness[i];
	}
	//selection operation
	for (i = 0; i < PopSize; i++)
	{
		p = rand() % 1000 / 1000.0;//�������һ�����������1000�õ�0-999�������ٳ���1000�õ�[0,0.999]�ĸ�����
		index = 0;
		while (p > cfitness[index])
		{
			index++;
		}
		newpopulation[i] = population[index];
	}
	for (i = 0; i < PopSize; i++)
	{
		population[i] = newpopulation[i];
	}
}
/*Function:Crossover two chromosome by means
 of one point crossover.
 Variable:None.*/
void CrossoverOperator()
{
	int i, j;
	int index[POPSIZE];
	int point, temp;
	double p;
	char ch;
	//make a pair of individual randomly������
	for (i = 0; i < PopSize; i++)
	{
		index[i] = i;
	}
	for (i = 0; i < PopSize; i++)
	{
		point = rand() % (PopSize - i);
		temp = index[i];
		index[i] = index[i + point];
		index[point + i] = temp;
	}
	//one point crossover operation
	for (i = 0; i < PopSize - 1; i += 2)
	{
		p = rand() % 1000 / 1000.0;
		if (p < Pc)
		{
			point = rand() % (CHROMLENGTH - 1) + 1;
			for (j = point; j < CHROMLENGTH; j++)
			{
				ch = population[index[i]].chrom[j];
				population[index[i]].chrom[j] = population[index[i + 1]].chrom[j];
				population[index[i + 1]].chrom[j] = ch;
			}
		}
	}
}
/*Function:Mutation of a chromosome.
Variable:None*/
void MutationOperator()
{
	int i, j;
	double p;
	//bit mutation
	for (i = 0; i < PopSize; i++) {
		for (j = 0; j < CHROMLENGTH; j++) {
			p = rand() % 1000 / 1000.0;
			if (p < Pm) {
				population[i].chrom[j] = (population[i].chrom[j] == '0') ? '1' : '0';
			}
		}
	}

}
/*Function:Output the results of current population.
Variable:None.*/
void OutputTextReport()
{
	int i;
	double sum;//temporary sum
	double average;//average of population object value
	//calculate average object value
	sum = 0.0;
	for (i = 0; i < PopSize; i++)
	{
		sum += population[i].value;
	}
	average = sum / PopSize;
	//print results of this population
	printf("gen=%d,avg=%f,best=%f,", generation, average, currentbest.value);
	printf("chromosome=");
	for (i = 0; i < CHROMLENGTH; i++)
	{
		printf("%c", currentbest.chrom[i]);
	}
	printf("\n");
}
