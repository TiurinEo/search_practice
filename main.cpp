#include <iostream>
#include <vector>
#include "plant.h"
#include <discpp.h>
using namespace std;
void
min_max(double& minim,double& maxim, vector<double> vect){
     maxim=vect[0];
     minim=vect[0];
int     razmer=vect.size();
    for (int i=0;i<razmer;i++){
        if(vect[i]<minim) minim=vect[i];
            else if (vect[i]>maxim) maxim=vect[i];
    }
}

vector<double>
input_gi(int i){

    double gi_min,gi_max,d_gi;

    cout<<"g"<<i<<"_min=";cin>>gi_min;
    cout<<"g"<<i<<"_max=";cin>>gi_max;
    cout<<"step d_g"<<i<<"=";cin>>d_gi;

    int razmer=((gi_max-gi_min)/d_gi)+1;

    vector<double> gi(razmer);

    gi[0]=gi_min;
    gi[razmer]=gi_max;

    for (int j=1;j<razmer;j++){
        gi[j]=gi[j-1]+d_gi;
    }
    return gi;

}

vector<double>
input_m(double k){
    vector<double> result(k);
    for (int i=0;i<k;i++){
        cout<<"M"<<i<<"=";cin>>result[i];
    }
    return result;
}
vector<double>
input_a(double k){
 vector<double> result(k);
    for (int i=0;i<k;i++){
        cout<<"a"<<i<<"=";cin>>result[i];
    }
    return result;
}
vector<double>
input_b(double k){
 vector<double> result(k);
    for (int i=0;i<k;i++){
        cout<<"b"<<i<<"=";cin>>result[i];
    }
    return result;
}
vector<double>
input_g(double k){
 vector<double> result(k);
    for (int i=0;i<k;i++){
        cout<<"g"<<i<<"=";cin>>result[i];
    }
    return result;
}
void
input(double& N, double& k,vector<double>& in_channel,vector<double>& a,vector<double>& b, vector<double>& g ){
    cout<<"N=";cin>>N;
    cout<<"k=";cin>>k;
    in_channel=input_m(k);
    a=input_a(k);
    b=input_b(k);
    g=input_g(k);
}
vector<double>
find_tep1(vector<vector<double>> x,vector<double> a){
    double N=x[0].size();
    vector<double> result(N);
    for (int i=0;i<x.size();i++){
            double summ=0;
        for (int j=0;j<N;j++){
            summ+=x[i][j];
        }
    result[i]=(a[i]*summ)/N;
    }
    return result;
}
vector<double>
find_tep2(vector<vector<double>> x,vector<double> b,vector<double> g){
    double N=x[0].size();
    vector <double> result(N);
    for (int i=0;i<x.size();i++){
        double summ=0;
        for (int j=0;j<N;j++){
            summ=summ+((x[i][j]-g[i])*(x[i][j]-g[i]));
        }
        result[i]=(b[i]*summ)/N;
    }
    return result;
}
vector<double>
find_tep2_from_number_channel(vector<vector<double>> x,vector<double> b,vector<double> g,int number_channel){
    int N=x[number_channel].size();
    int k=g.size();
    vector <double> result(k);

    for (int i=0;i<k;i++ ){
    double summ=0;
    for (int j=0;j<N;j++){
        summ=summ+((x[number_channel][j]-g[i])*(x[number_channel][j]-g[i]));
    }
    result[i]=(b[number_channel]*summ)/N;
    }
    return result;
}

vector<double> in_channel,b,g;
vector<double> a;
double N,k;

double gi_min,gi_max,d_gi;
int main()
{

  input(N,k,in_channel,a,b,g);
    Plant plant;
    plant_init(plant);
    vector<vector<double>> x(k,vector <double> (N));

    for (size_t j=0;j<N;j++){
        for (size_t i=0;i<k;i++){
            x[i][j]=plant_measure(in_channel[i],plant);

        }

    }
vector<double> tep1(k),tep2(k);
tep1=find_tep1(x,a);
tep2=find_tep2(x,b,g);





    vector<double> g_number_channel;
    cout<<endl;
    int number_channel, number_channel_withoutplusone;
    for (int p=0;p<k;p++){
    cout<<"i=";cin>>number_channel_withoutplusone;
    number_channel=number_channel_withoutplusone-1;
    g_number_channel=input_gi(number_channel);
    vector<double> tep2_number_channel(g_number_channel.size());
    tep2_number_channel=find_tep2_from_number_channel(x,b,g_number_channel,number_channel);
    cout<<endl;
    cout<<'\t'<<"g"<<number_channel<<'\t'<<"tep2_"<<number_channel;
    cout<<endl;
    for (int i=0;i<g_number_channel.size();i++){
        cout<<'\t'<<g_number_channel[i]<<'\t'<<tep2_number_channel[i]<<endl;
    }
    int razmer_g=g_number_channel.size();
    int razmer_tep2=tep2_number_channel.size();
    double max_tep2, min_tep2, max_g,min_g;

    min_max(min_tep2,max_tep2,tep2_number_channel);
    min_max(min_g,max_g,g_number_channel);



    // ������ ��� ��������� �������.
    Dislin g;

    // ������ ������, "cons" �������� ����� �� �����.
    g.metafl("cons");

    // �������� ����� �������� ���� (�� ��������� ��������).
    g.scrmod("revers");

    // �������������� ����������, ������ ���� ������ ������ ������� ���������.
    g.disini();

    // ������ ������� ����.
    g.name("G_i", "x");
    g.name("Tep2_i", "y");

    // ���������� ���� ����� ������� �� ��� �������: ���, ������ ����� �����.


    // ���������� ������������� ����� (����� �������) �� ����.
    g.ticks(10, "x");
    g.ticks(10, "y");

    // ������ ��������� �������.
    g.titlin("Plant parameter plot", 1);

    // ���������� ���� ��� ����� ��������, �������� � ������ �� 0 �� 1 (RGB).
    // �����: ��� ���������� ����� � ������ � 1, �. �. ���� ������-�����.
    const int background_color = g.intrgb(0.95, 0.95, 0.95);

    // ���������� ���� ������������ ���� ��� ������� ����.
    g.axsbgd(background_color);

    // ������ ������������ �����.
    g.graf(
        // ������� �������� �� ��� ������� (X).
        min_g, max_g,
        // ���������� �������� �� ��� ������� � ��������� �� ���.
        min_g, (max_g-min_g)/10,
        // ������� �������� �� ��� ������� (Y).
        min_tep2, max_tep2,
        // ���������� �������� �� ��� ������� � ��������� �� ���.
        min_tep2, (max_tep2-min_tep2)/10);

    // ������ ������-����� ���� ��� ���������� ������.
    g.setrgb(0.7, 0.7, 0.7);
    // ������ ����� � ��������� ������ �� ����.
    g.grid(1, 1);

    // ������ ���� ��� ���������� ������ �� ����� �����������.
    // �����: �������� ����, ����������� � ����� (������ ��� ������ ����).
    g.color("fore");
    // ������ ���������.
    g.title();

    g.color("red");
    g.curve(&g_number_channel[0], &tep2_number_channel[0], g_number_channel.size());
    g.disfin();
    }
}
/// M1=8.1

