
#include <iostream>
#include <cmath>

int main(void)
{
	using namespace std;
	
	double area;
	double side;
	cout << "Enter the floor area,in square feet,of your home?" << endl;
	cin >> area;
	side = sqrt(area);
	cout << "That's the equivalent of square" << side << "feet the side."
		<< endl;
	return 0;
}
