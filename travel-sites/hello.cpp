#include <iostream>
#include <string>

class Myclass
{
	public:
		Myclass(std::string _str):str(_str){};
		virtual ~Myclass(){};

		void display(void) { std::cout << str << std::endl; };

	private:
		std::string str;
};

int main(int argc, const char** argv)
{
	Myclass classtest("Hello world!");
	classtest.display();

	return 0;
}
