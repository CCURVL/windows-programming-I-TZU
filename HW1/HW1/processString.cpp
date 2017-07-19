#include <iostream>
#include <string>
#include <vector>

#include <gtest\gtest.h>

using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	std::string input = inputStr;
	
	for (int i = 0; i<input.size(); i++)
		if (int(input.c_str()[i]) != 32 && int(input.c_str()[i]) != 45 
			&& !(int(input.c_str()[i])>47 && int(input.c_str()[i])<58))
			return -1;

	std::istringstream ss(input);
	std::string token;

	std::vector<int> vArr;

	while (std::getline(ss, token, ' '))
	{
		int temp = atoi(token.c_str());
		vArr.push_back(temp);
	}

	std::sort(vArr.begin(), vArr.end());

	std::ostringstream tmpStr;

	if (!vArr.empty())
	{
		std::copy(vArr.begin(), vArr.end() - 1,
		std::ostream_iterator<int>(tmpStr, " "));
		tmpStr << vArr.back();
		std::string input = tmpStr.str();
		std::cout << input << std::endl;
		return 0;
	}
	
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	double d, e, f;
	if(b*b-4*a*c>0)
	{
		d = ((-b) + sqrt(b*b - 4 * a*c)) / (2 * a);
		e = ((-b) - sqrt(b*b - 4 * a*c)) / (2 * a);
		x.push_back(d);
		x.push_back(e);
		return 1;
	}
	else if(b*b-4*a*c<0)
	{
		return -1;
	} 
	else
	{
		f = (-b) / (2 * a);
		x.push_back(f);
		return 0;
	}
}

int main(int argc, char*argv[]) {
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}