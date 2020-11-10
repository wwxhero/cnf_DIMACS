#include "logicBase.h"
class L_Latin_rcx : public Literal
{
public:
	L_Latin_rcx(int n, int r, int c, int x, bool val)
		: Literal(val, x + c * n + r * n * n + 1)
		, d(0)
		, m_r(r)
		, m_c(c)
		, m_x(x)
	{
	}

	L_Latin_rcx(int code, int n)
		: Literal(code > 0, std::abs(code))
		, d(m_absCode-1)
		, m_r(d/(n * n))
		, m_c((d - m_r * n * n)/n)
		, m_x(d%n)
	{
	}

	virtual void Dump(std::ostream& outs) const override
	{
#ifdef _DEBUG
		if (m_val)
			outs << "l_" << m_r << "_" << m_c << "_" << m_x;
		else
			outs << "l_" << m_r << "_" << m_c << "_" << m_x << "'";
#else
		Literal::Dump(outs);
#endif
	}

private:
	const int m_r;
	const int m_c;
	const int m_x;
	const int d;
};