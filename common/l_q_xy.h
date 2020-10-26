#include "logicBase.h"
class L_Q_xy : public Literal
{
public:
	L_Q_xy(int x, int y, int nX, int nY, bool val)
		: Literal(val, x * nY + y)
		, m_x(x)
		, m_y(y)
		, m_nX(nX)
		, m_nY(nY)
	{
	}

	L_Q_xy(int code, int nX, int nY)
		: Literal(code > 0, std::abs(code)-1)
		, m_x(m_absCode/nY)
		, m_y(m_absCode%nY)
		, m_nX(nX)
		, m_nY(nY)
	{
		assert(m_x < nX);
	}



	virtual void Dump(std::ostream& outs) const override
	{
#ifdef _DEBUG
		int x = m_absCode / m_nY;
		int y = m_absCode % m_nY;
		assert(x < m_nX);
		if (m_val)
			outs << "q_" << x <<"_" << y;
		else
			outs << "q_" << x <<"_" << y << "'";
#else
		Literal::Dump(outs);
#endif
	}

private:
	const int m_x;
	const int m_y;
	const int m_nX;
	const int m_nY;
};