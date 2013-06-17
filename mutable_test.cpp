#include <iostream>
#include <map>
#include <string>
#include <sstream>


using namespace std;
//#include <memory>

class myData
{
private:
	int m_K, m_D, m_F;
	
	//mutable variable to set or unset flag for caching of old or new calculation respectively
	mutable bool m_cacheFlag; 

	//mutable variable to keep track of stored results
	mutable int resultsCount; 

	//mutable map variable to store results of the expensive calculation
	typedef map<int,int> myCachedResult;
	mutable myCachedResult myExpensiveResult;
	
	// Any expensive calculation 
	int add() const 
	{
		return m_K + m_D + m_F;
	}
	
public:
	
	//Initializtion constructor
	myData():m_K(0), m_D(0), m_F(0), m_cacheFlag(false),resultsCount(0) {} 
	
	//Function to store expensive calculation results
	//mutable map storage variable myExpensiveResult
	int expensiveCalc() const
	{
		
		if (m_cacheFlag == false)
		{
			m_cacheFlag = true;
			resultsCount++;
			//Store expensive calculation only once depending on m_cacheFlag setting		
			myExpensiveResult[resultsCount] = add(); 
		}
		
		return myExpensiveResult[resultsCount];		
	}

	//Function to change internal data for the expensive calculation
	void changeData(int K, int D, int F)
	{
		m_cacheFlag = false;
		m_K = K;
		m_D = D;
		m_F = F;
	}
	
	//Function to find the stored results in the mutable map variable myExpensiveResult container
	int findExpensiveCalc(const int calcNumber)
	{
		myCachedResult::iterator it = myExpensiveResult.find(calcNumber);

		return (*it).second;
	}


};


int main()
{
	myData calc1;

	calc1.changeData(10,12,10);
	
	cout << "1st calculation results :" << calc1.expensiveCalc() << endl;

	
	calc1.changeData(11,12,10);
	
	cout << "2nd calculation results :" << calc1.expensiveCalc() << endl;
	
	//Show cached results
	cout << "Stored 1st calculation results :" << calc1.findExpensiveCalc(1) << endl;
	cout << "Stored 2nd calculation results :" << calc1.findExpensiveCalc(2)<< endl;
}