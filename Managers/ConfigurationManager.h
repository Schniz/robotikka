#include <string>
#include <iostream>

using namespace std;
#include "../Models/Location.h"
#include "../Models/Size.h"

namespace Managers {
class ConfigurationManager {
public:
	ConfigurationManager(string filePath);
	virtual ~ConfigurationManager();

	string getPngMapPath();
	Location getStartLocation();
	Location getEndLocation();
	float getPixelPerCm();
	float getPngGridResolution();
	Size getRobotSize();

	friend ostream& operator<<(ostream& os, ConfigurationManager* config);
private:
	string m_PngMapPath;
	Location m_StartLocation;
	Location m_EndLocation;
	float m_PpCM;
	float m_PngGridResolution;
	Size m_RobotSize;
};

}
