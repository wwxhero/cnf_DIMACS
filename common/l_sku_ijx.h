#include "logicBase.h"

class SudokuGrid
{
public:
	struct Cell
	{
		int row_i;
		int col_i;
	};
	SudokuGrid()
		: m_fullX({1, 2, 3, 4, 5, 6, 7, 8, 9})
	{
	}
	bool Initialize(std::istream& input)
	{
		bool initialized = true;
		for(int r = 0; r < 9 && initialized; r ++)
		{
			for (int c = 0; c < 9 && initialized; c ++)
			{
				int val_cell = 0;
				input >> val_cell;
				initialized = !input.bad();
				if (initialized
					&& 0 == val_cell)
					m_lstCells.push_back(Cell{ r, c });
			}
		}
#if 0
		auto it_cells = m_lstCells.begin();
		for (int r = 0; r < 9; r ++)
		{
			for (int c = 0; c < 9; c ++)
			{
				bool hit = (it_cells->row_i == r
							&& it_cells->col_i == c);
				const char* tag = hit ? "0 " : "x ";
				std::cout << tag;
				if (hit)
					it_cells ++;
			}
			std::cout << std::endl;
		}
		assert(it_cells == m_lstCells.end());
#endif
		return initialized;
	}
	const std::list<Cell>& emptyCells() const
	{
		return m_lstCells;
	}
	const std::list<int>& fullX() const
	{
		return m_fullX;
	}
private:
	std::list<Cell> m_lstCells;
	const std::list<int> m_fullX;
};

class L_SKU_ijx : public Literal
{
public:
	L_SKU_ijx(int i_r, int i_c, int x, bool val)
		: Literal(val, i_r * 100 + i_c * 10 + x)
		, m_r(i_r)
		, m_c(i_c)
		, m_x(x)
	{
		assert(x > -1 && x < 10);
	}

	virtual void Dump(std::ostream& outs) const override
	{
#ifdef _DEBUG
		if (m_val)
			outs << m_r << "_" << m_c << "_" << m_x;
		else
			outs << m_r << "_" << m_c << "_" << m_x << "'";
#endif
	}
public:
	const int m_r;
	const int m_c;
	const int m_x;
};
