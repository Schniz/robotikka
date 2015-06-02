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

}
}
