#include <iostream>
#include <cmath>
#include <vector>
#include <string>

double distance(double x,double y,double i,double j)
{
    double dlat = ((i-x)*M_PI)/180;
    double dlon = ((j-y)*M_PI)/180;
    x = (x)*M_PI/180;
    i = (i)*M_PI/180;
    double a = pow(sin(dlat/2),2) + cos(x) * cos(i) * pow(sin(dlon/2),2);
    double c = 2 * atan2(sqrt(a),sqrt(1-a));
    double d = 3959.9 * c;
    return d;
}

double coo(std::string x)
{
    bool check = false;
    char b = '/';
    int stop = 0;
    std::string number;
    for(int a = x.length()-1;a>=0;a--)
    {
        if(x[a] == b)
        {
            stop = a;
            break;
        }
    }
    if(x[stop+1] == 'S' || x[stop+1] == 'E')
    {
        check = true;
    }
    int a = 0;
    while(a < stop)
    {
        number+=x[a];
        a++;
    }
    double num = std::stod(number);
    if(check)
    {
        num = -num;
    }
    return num;
}
int main()
{
    std::vector<std::vector<std::string>> ss;
    std::string olat,olon,location;
    std::cin>>olat>>olon;
    std::getline(std::cin,location);
    location.erase(0,1);
    int count = 0;
    std::cin>>count;
    while(count > 0)
    {
        std::vector<std::string> s;
        std::string lat,lon,area;
        std::cin>>lat>>lon;
        std::getline(std::cin,area);
        area.erase(0,1);
        s.push_back(lat);
        s.push_back(lon);
        s.push_back(area);
        ss.push_back(s);
        count--;
    }
    double max = distance(coo(olat),coo(olon),coo(ss[0][0]),coo(ss[0][1]));
    double min = distance(coo(olat),coo(olon),coo(ss[0][0]),coo(ss[0][1]));
    int maximum = 0;
    int minimum = 0;
    for(int a =0;a<ss.size();a++)
    {
        if(distance(coo(olat),coo(olon),coo(ss[a][0]),coo(ss[a][1]))>max)
        {
            max = distance(coo(olat),coo(olon),coo(ss[a][0]),coo(ss[a][1]));
            maximum = a;
        }
        if(distance(coo(olat),coo(olon),coo(ss[a][0]),coo(ss[a][1]))<min)
        {
            min = distance(coo(olat),coo(olon),coo(ss[a][0]),coo(ss[a][1]));
            minimum = a;
        }
    }
    std::cout<<"Start Location: "<<olat<<" "<<olon<<" ("<<location<<")"<<std::endl;
    std::cout<<"Closest Location: "<<ss[minimum][0]<<" "<<ss[minimum][1]<<" ("<<ss[minimum][2]<<") ("<<min<<" miles)"<<std::endl;
    std::cout<<"Farthest Location: "<<ss[maximum][0]<<" "<<ss[maximum][1]<<" ("<<ss[maximum][2]<<") ("<<max<<" miles)"<<std::endl;

    return 0;
}

