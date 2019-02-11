#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Magic
{
private:
    unsigned** tab;
    int row;
    int col;
    int degree;
public:
    Magic(int);
    ~Magic();
    void print();
    void alg();
    int reflect(int);
};

Magic::Magic(int n)
{
    degree = n;
    tab = new unsigned* [degree];
    for(row=0; row < degree; row++)
        tab[row] = new unsigned [degree];
    for(row=0; row < degree; row++)
        for(col=0; col < degree; col++)
            tab[row][col] = 0;
}

Magic::~Magic()
{
    for(row=0; row < degree; row++)
        delete [] tab[row];
    delete []tab;
}

void Magic::print()
{
    int degree2;
    int len=0;
    degree2 = (degree * degree);
    while(degree2 > 0)
    {
        degree2 /= 10;
        len++;
    }
    for(row=0; row < degree; row++)
    {
        for(col=0; col < degree; col++)
            printf("%0*d ", len, tab[row][col]);
        putchar('\n');
    }
    putchar('\n');
    return;
}

int Magic::reflect(int k)
{
    if(k<0)
        return(k + degree);
    if(k > (degree - 1))
        return(k - degree);
    return(k);
}

void Magic::alg()
{
    int i,j;
    int n = degree;
    int s; //счетчик
    int p; //значение переменной
    int M = ((degree - 1) / 2); // N = 2M+1 из условия
    row = (degree - 1); //ряд квадрата
    col = (degree - 1); //столбец квадрата
    
    for(s=0; s < n; s++)
        tab[row-s][col-s] = M*5;   //заполняем главную диагональ первого квадрата
    
    for (p=degree-1; p>0; p--) //заполняем остальные диагонали первого квадрата
    {
        for(s=0; s < n; s++)
        {
            i = row-s+1;
            j = col-s;
            reflect(i);
            reflect(j);
            if (p == M)
                p--;
            tab[i][j]=p*5;
            
        }
    row++;
    }
    for(s=0; s < n; s++)
        tab[row-s][s] += M+1; // складываем значения главной диагонали второго квадрата с соответствующими клетками первого квадрата
    
    for (p=1; p<degree; p++) // складываем значения остальных диагоналей второго квадрата с соответствующими клетками первого квадрата
    {
        for(s=0; s < n; s++)
        {
            i = row-s+1;
            j = s;
            reflect(i);
            reflect(j);
            if (p == M)
                p--;
            tab[i][j]+=p;
            
        }
        row++;
    }
}


int main(int argc, char* argv[])
{
    int n;
    std::cin >> n;
    if(argc != 2)
        return(puts("Usage: magic degree"));
    n = atoi(argv[1]);
    if((n % 2) == 0)
    {
        puts("Usage: magic 5 (or 7, 11, 17, ...)");
        return(n);
    }
    Magic mag(n);
    mag.alg();
    mag.print();
    return(n);
}
