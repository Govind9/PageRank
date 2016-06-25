#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

double d=0.15;

class Page
{
public:
	int id;
	double pr;
	int N;
	vector <int> inlinks;
	void printMe()
	{
		cout<<"I am page number: "<<id<<" and I have a pagerank of: "<<pr<<endl;
	}
};

vector <Page> pages; 

void print()
{
	double sum = 0;
	for(int i=0;i<pages.size(); i++)
	{
		sum += pages[i].pr;
		pages[i].printMe();
		continue;
		cout<<pages[i].id<<"\t"<<pages[i].N<<"\t";
		for(int j=0; j<pages[i].inlinks.size();j++)
		{
			cout<<pages[i].inlinks[j]<<",";
		}
		cout<<endl;
	}
	cout<<"Sum: "<<sum<<endl;
}

void compute()
{
	bool flag = true;
	int iter=1;
	double temp[pages.size()];
	while(flag)
	{
		flag = false;
		cout<<"Iterations: "<<iter<<endl;
		for(int i = 0; i<pages.size(); i++)
		{
			temp[i] = 0;
			for(int j = 0; j<pages[i].inlinks.size(); j++)
			{
				 temp[i]+=pages[pages[i].inlinks[j]].pr/pages[pages[i].inlinks[j]].N;
			}
			temp[i]=d/pages.size()+(1-d)*temp[i];
			if(abs(pages[i].pr-temp[i])>0.1)
			{
				flag = true;
			}
		}
		for(int i = 0; i < pages.size(); i++)
		{
			pages[i].pr = temp[i];
		}
		iter++;
		print();
	}
}

void initialize(const char *filename)
{
	ifstream file(filename);
	int i;
	char ch=' ';
	while(!file.eof())
	{
		Page page;
		page.N = 0;
		file>>page.id; //get the id
		file.get(ch); //get past the space
		while(ch!='\n' && ch!='\r') //while the line does not end
		{
			int l;
			file>>l; //get the number
			page.inlinks.push_back(l); //save the number
			file.get(ch); //get past the comma
		}
		pages.push_back(page);
	}
	pages.pop_back(); //removing one extra bogus entry
	file.close();
	file.open(filename);
	ch = ' ';
	while(!file.eof())
	{
		file.get(ch);
		file.get(ch); //get past the space
		while(ch!='\n' && ch!='\r') //while the line does not end
		{
			int l;
			file>>l; //get the number
			pages[l].N++;
			file.get(ch); //get past the comma
		}
	}
	file.close();
	for(int i = 0; i < pages.size(); i++)
	{
		pages[i].pr = 1.0/double(pages.size()); //Starting point for all the PRs
	}
}

int main()
{
	initialize("webgraph.txt");
	print();
	compute();
	return 0;
}
