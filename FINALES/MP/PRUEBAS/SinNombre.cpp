#include <iostream>

using namespace std;

void mostrar(const double& dato){
	cout << "Dato: " << dato << endl;
}


int main(){
	int a = 3.0;
	mostrar(a);
	
	mostrar( a+2);
}
