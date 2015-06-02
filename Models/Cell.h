#include <iostream>
#include <vector>

using namespace std;

class Cell
{
public:
	double Cell_Cost;

	// Consts
	static const double OCCUPIED;
	static const double FREE;
	static const double WALL;
	static const unsigned NUM_NEIGHBORS;

	// Ctors
	Cell(unsigned x, unsigned y, double cell_cost = 1.0);
	Cell(const Cell& cell);
	Cell(const Cell* cell);

	// Dtor
	~Cell();

	// Metohods
	void init(vector<Cell*> neighbors);

	inline vector<Cell*> getNeighbors() {
		return m_Neighbors;
	};

	inline unsigned getX() {
		return m_X;
	};

	inline unsigned getY() {
		return m_Y;
	};

	inline bool getIsInit() {
		return m_IsInit;
	};

	bool isFree();

protected:
	bool m_IsInit;
	vector<Cell*> m_Neighbors;
	unsigned m_X;
	unsigned m_Y;
};
