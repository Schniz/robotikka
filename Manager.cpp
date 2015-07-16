
#include "Manager.h"
#include "Managers/ConfigurationManager.h"
#include "Models/Map.h"

Manager::Manager(Robot* robot, Plan* pln) {
	_robot = robot;
	_curr = pln->getStartPoint();
	_plan = pln;
}
void Manager::run()
{
		_robot->Read();

//		if(!_curr->startCond())
//			return;

		while (_curr->stopCond())
		{
			_curr = _curr->selectNext();

			if (_curr == NULL)
				return;
		}

		_curr->action();

		while(_curr != NULL)
		{
			while(!_curr->stopCond())
			{
				_curr->action();
				_robot->Read();
			}
			_curr = _curr->selectNext();
			_robot->Read();
		}
}

void Manager::InitApp()
{
	// init configuration manager
	//ConfigurationManager::LoadFromFile("Reasurce\parameters.txt");

	// load map
	Map *m = new Map(strtok(&ConfigurationManager::GetInstance()->getPngMapPath()[0], " "));


}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
