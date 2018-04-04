#include <iostream>
#include <regex>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include<map>
#include <unordered_map>
#include <functional>


#include <thread>

void test()
{
  std::regex rq("S");
  printf("S works.\n");

  std::regex r2(".\n");
   printf(". works\n");
  
  std::regex r3(".+");
  printf(".+ works\n");

  std::regex r4("[0-9]");
  printf("[0-9] works");

}

void test1()
{
  std::stringstream stream;
  std::string result;
  int number = 123456;
  stream<<number;
  stream>>result;
  std::cout<<result<<std::endl;

  std::stringstream stream1;
  char ch[6];
  stream1<<123456;
  stream1>>ch;
  std::cout<<ch<<std::endl;
}


void learn_lambda_func_1()
{
  int value1 = 1;
  auto copy_value_1 = [value1]{return value1;};
  value1 = 100;
  auto stored_value_1 = copy_value_1();
}

void learn_lambda_func_2()
{
  int value_2 = 1;
  auto copy_value_2 = [value_2]{
    return value_2;
  };
  auto stored_value_2 = copy_value_2();
}

void foo(std::shared_ptr<int> i)
{
 (*i)++;
}

void testSharedPtr()
{
  auto pointer = std::make_shared<int>(10);
  foo(pointer);
  std::cout<<*pointer<<std::endl;
}


void testUnorderedMap()
{
  std::unordered_map<int, std::string> u = {
    {1, "1"},
    {5, "5"},
    {3, "3"},
    {4, "4"}
  };
  std::map<int, std::string> v = {
    {1, "1"},
    {5, "5"},
    {3, "3"},
    {4, "4"}
  };

  std::cout<<"std::unordered_map"<<std::endl;
  for(const auto& n : u)
  {
    std::cout<<"Key:["<<n.first<<"] Value:[" <<n.second<<"]"<<std::endl;
  }

  std::cout<<std::endl;
  std::cout<<"std::map"<<std::endl;
  for(const auto& x:v)
    std::cout<<"Key:["<<x.first<<"] Value:[" <<x.second<<"]"<<std::endl;

}

void testRegex()
{
  std::string fnames[] = {"foo.txt", "bar.txt","test","a0.txt", "AA.txt" };

  std::regex txt_regex("[a-z]+\\.txt");
  
  for(const auto& fname:fnames)
    std::cout<<fname<<": "<<std::regex_match(fname, txt_regex)<<std::endl;

  std::smatch base_match;
  std::cout<<"get matched info in another way:"<<std::endl;
  for(const auto& fname:fnames)
  {
    if(std::regex_match(fname, base_match, txt_regex))
    {
      if(base_match.size() == 2)
      {
	std::string base = base_match[1].str();
	std::cout<<"sub-match[0]: "<<base_match[0].str()<<std::endl;
	std::cout<<fname<<" sub-match[1]: "<<base<<std::endl;
      }
    }
  }
}

int fooFun(int para)
{
  return para;
}

void testFunc()
{
  std::function<int(int)> func = fooFun;
  std::cout<<func(10)<<std::endl;
}

void fooThread()
{
  std::cout<<"Hello, world"<<std::endl;
}

void testThread()
{
  std::thread t(fooThread);
  t.join();
}

int main()
{ 
  test();
  test1();
  learn_lambda_func_1();
  learn_lambda_func_2();

  testSharedPtr();

  testUnorderedMap();

  testRegex();

  testFunc();

  testThread();
  return 0;
}
