#pragma once
class Graf
{
public:
	Graf();

	~Graf();

	void init(const std::vector<std::pair<int, int>> & v);

	void robercik();		// Krypton

	void flores();			// Polon

private:
	std::vector<std::pair<int, int>> _edgeList;




};

