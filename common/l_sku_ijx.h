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
	bool Initialize(std::istream& input, char* vals = NULL)
	{
		bool initialized = true;
		bool rExists[9][10]; // rExists[id_r][n] = true: n in [1-9] exists on row id_r
		bool cExists[9][10];
		bool gExists[9][10];
		bool rcExists[9][9][10]; //rcExists[r][c][n] = true: n in [1-9] exists on cell(r, c)
		memset(rExists, true, sizeof(bool) * 90);
		memset(cExists, true, sizeof(bool) * 90);
		memset(gExists, true, sizeof(bool) * 90);
		memset(rcExists, true, sizeof(bool) * 810);
		for(int r = 0; r < 9 && initialized; r ++)
		{
			for (int c = 0; c < 9 && initialized; c ++)
			{
				int val_cell = 0;
				input >> val_cell;
				initialized = !input.bad();
				if (initialized)
				{
					int g = (r/3) * 3 + (c/3);
					if (0 == val_cell)
					{
						Cell cell = {r, c};
						m_lstCells.push_back(cell);
						m_r2cells[r].push_back(cell);
						m_c2cells[c].push_back(cell);
						m_g2cells[g].push_back(cell);
					}
					else
					{
						rExists[r][val_cell] = false; 		//remove val_cell from row 'r' domain
						cExists[c][val_cell] = false; 		//remove val_cell from column 'c' domain
						gExists[g][val_cell] = false; 		//remove val_cell from grid 'g' domain
						for (int c_sub = 0; c_sub < 9; c_sub ++)
							rcExists[r][c_sub][val_cell] = false;	//remove val_cell from cell 'r, c' domain
						for (int r_sub = 0; r_sub < 9; r_sub ++)
							rcExists[r_sub][c][val_cell] = false;	//remove val_cell from cell 'r, c' domain
					}
				}
				if (vals)
					vals[r*9 + c] = char(val_cell + '0');
			}
		}

		if (initialized)
		{
			for (int i_g = 0; i_g < 9; i_g ++)
			{
				for (int x = 1; x < 10; x ++)
				{
					if (rExists[i_g][x])
						m_r2X[i_g].push_back(x);
					if (cExists[i_g][x])
						m_c2X[i_g].push_back(x);
					if (gExists[i_g][x])
						m_g2X[i_g].push_back(x);
				}
			}

			for (int r = 0; r < 9; r ++)
			{
				for (int c = 0; c < 9; c ++)
				{
					for (int x = 1; x < 10; x ++)
					{
						if (rcExists[r][c][x])
							m_rc2X[r][c].push_back(x);
					}
				}
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
	const std::list<Cell>& emptyCells_r(int row_i) const
	{
		return m_r2cells[row_i];
	}
	const std::list<int>& xDomain_r(int row_i) const
	{
		return m_r2X[row_i];
	}
	const std::list<Cell>& emptyCells_c(int col_i) const
	{
		return m_c2cells[col_i];
	}
	const std::list<int>& xDomain_c(int row_i) const
	{
		return m_c2X[row_i];
	}
	const std::list<Cell>& emptyCells_g(int gri_i) const
	{
		return m_g2cells[gri_i];
	}
	const std::list<int>& xDomain_g(int row_i) const
	{
		return m_g2X[row_i];
	}
	const std::list<int>& fullX() const
	{
		return m_fullX;
	}
	const std::list<int>& xDomain_rc(int row_i, int col_i) const
	{
		return m_rc2X[row_i][col_i];
	}
private:
	std::list<Cell> m_lstCells;
	std::list<Cell> m_r2cells[9];
	std::list<int>	m_r2X[9];
	std::list<Cell> m_c2cells[9];
	std::list<int>	m_c2X[9];
	std::list<Cell> m_g2cells[9];
	std::list<int>	m_g2X[9];
	std::list<int>	m_rc2X[9][9];
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
		assert(x > 0 && x < 10);
	}

	L_SKU_ijx(int code)
		: Literal(code > 0, std::abs(code))
		, m_r(m_absCode/100)
		, m_c((m_absCode - 100 * m_r)/10)
		, m_x(m_absCode - 100 * m_r - 10 * m_c)
	{
		assert(-1 < m_r && m_r < 9);
		assert(-1 < m_c && m_c < 9);
		assert( 0 < m_x && m_x < 10);
	}

	virtual void Dump(std::ostream& outs) const override
	{
#ifdef _DEBUG
		if (m_val)
			outs << m_r << "_" << m_c << "_" << m_x;
		else
			outs << m_r << "_" << m_c << "_" << m_x << "'";
#else
		Literal::Dump(outs);
#endif
	}
public:
	const int m_r;
	const int m_c;
	const int m_x;
};
