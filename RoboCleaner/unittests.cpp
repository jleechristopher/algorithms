#include "unittests.h"
#include "robot.h"
#include <cctype> // isdigit(), stoi()

Test_Registrar<RoboCleanerUnitTests> RoboCleanerUnitTests::registrar;

int getTimesCleaned(const std::stringstream& output)
{
	int start = -1;
	int end;
	std::string target = "cleaned: ";
	std::string outString = output.str();

	// get index of "c" in "cleaned"
	for (int ii = 0; ii < outString.length(); ++ii)
	{
		if (outString[ii] == target[0])
		{
			for (int jj = 0; jj < target.length(); ++jj)
			{
				if (outString[ii + jj] == target[jj])
				{
					// continue
				}
				else
				{
					break;
				}
				if (jj == target.length() - 1)
				{
					start = ii + target.length();
					end = start;
				}
			}
		}
	}

	// extract start/end
	if (start >= 0)
	{
		while (std::isdigit(outString[end]))
		{
			++end;
		}
		return std::stoi(outString.substr(start, end-start));
	}
	return -1;
}

bool RoboCleanerUnitTests::square()
{
	std::stringstream input;
	std::stringstream output;
	input << " ||||| " << std::endl;
	input << " |R..| " << std::endl;
	input << " |...| " << std::endl;
	input << " |...| " << std::endl;
	input << " ||||| " << std::endl;
	int tilesToClean = 9;

	FloorMap master(input);
	RoboCleaner robo(master);
	robo.cleanFloor(output);
	std::cout << output.str();
	int xCleaned = getTimesCleaned(output);
	VERIFY_EQ(tilesToClean, xCleaned);

	return true; 
}

bool RoboCleanerUnitTests::hallway()
{
	std::stringstream input;
	std::stringstream output;
	input << "||||||" << std::endl;
	input << "|.R..|" << std::endl;
	input << "||||||" << std::endl;
	int tilesToClean = 4;

	FloorMap master(input);
	RoboCleaner robo(master);
	robo.cleanFloor(output);
	std::cout << output.str();
	int xCleaned = getTimesCleaned(output);
	VERIFY_EQ(tilesToClean, xCleaned);

	return true; 
}

bool RoboCleanerUnitTests::diamond()
{
	std::stringstream input;
	std::stringstream output;
	input << "   |   " << std::endl;
	input << "  |R|  " << std::endl;
	input << " |...| " << std::endl;
	input << "|.....|" << std::endl;
	input << " |...| " << std::endl;
	input << "  |.|  " << std::endl;
	input << "   |   " << std::endl;
	int tilesToClean = 13;

	FloorMap master(input);
	RoboCleaner robo(master);
	robo.cleanFloor(output);
	std::cout << output.str();
	int xCleaned = getTimesCleaned(output);
	VERIFY_EQ(tilesToClean, xCleaned);
	
	return true; 
}
