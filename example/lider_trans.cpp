#include<iostream>

#include<cmath>
using namespace std;
struct polar
{
double distance;
double angle;
};
struct rect
{
double x;
double y;
};
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);
void coordinateTrans();
int main()
{
rect rplace;
polar pplace;
cout << " Enter the x and y values: ";
while (cin >> rplace.x>>rplace.y)
{
pplace = rect_to_polar(rplace);
show_polar(pplace);
coordinateTrans();
cout << "Next two number (q to quit):";


}
cout << "Done!\n";
return 0;
}
polar rect_to_polar(rect xypos)
{
polar answer;
answer.distance =
sqrt(xypos.x*xypos.x + xypos.y*xypos.y);
answer.angle =
atan(xypos.y / xypos.x);
return answer;
}

void coordinateTrans()
{

    double theta = 60/57.29577951; // 激光雷达逆时针转，角度取反
    //double laser_x = dist * cos(angle);
    //double laser_y = dist * sin(angle);
    double laser_x = 1;
    double laser_y = sqrt(3);
    //double laser_z = pos.z;
    
    double world_x = cos(theta) * laser_x - sin(theta) * laser_y;
    double world_y = sin(theta) * laser_x + cos(theta) * laser_y;

    cout << "坐标转换: x = " << world_x<<endl;
    cout << "坐标转换: y = " << world_y<<endl;

}

void show_polar(polar dapos)
{
const double Rad_to_deg = 57.29577951;
cout << "distance =" << dapos.distance<<endl;
cout << "angle =" << dapos.angle*Rad_to_deg;
cout << " degrees\n";

cout << "转换后: x = " << dapos.distance*cos(dapos.angle)<<endl;
cout << "转换后: y = " << dapos.distance*sin(dapos.angle)<<endl;
}
