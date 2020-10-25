#include <iostream>
#include <sstream>
#include <list>
#include <assert.h>

class Literal
{
public:
	Literal(int code, bool val, int nX, int nY)
		: m_nX(nX)
		, m_nY(nY)
	{
		assert(code > 0);
		m_code = (val ? code : -code);
	}
	void Dump(std::ostream& outs) const
	{
#ifdef _DEBUG
		bool posi = (m_code > 0);
		int code_m = posi ? m_code : -m_code;
		code_m --;
		int x = code_m / m_nY;
		int y = code_m % m_nY;
		assert(x < m_nX);
		if (posi)
			outs << "q_" << x <<"_" << y;
		else
			outs << "q_" << x <<"_" << y << "'";
#else
		outs << m_code;
#endif
	}
private:
	int m_code;
	const int m_nX;
	const int m_nY;
};

class Clause
{
public:
	Clause()
	{
	}
	explicit Clause(const std::string& cmmt)
	{
		m_cmmt = std::move(cmmt);
	}
	explicit Clause(Clause&& cls)
	{
		m_lits = std::move(cls.m_lits);
		m_cmmt = std::move(cls.m_cmmt);
	}
	void DumpCNF(std::ostream& outs) const
	{
		auto it_lit = m_lits.begin();
		it_lit->Dump(outs);
		it_lit ++;
		for (
			; it_lit != m_lits.end()
			; it_lit ++)
		{
			outs << " "; it_lit->Dump(outs);
		}
		outs << " 0" << std::endl;
	}
	void DumpCmt(std::ostream& outs) const
	{
		outs << "c " << m_cmmt.c_str() << std::endl;
	}
	void Dump(std::ostream& outs) const
	{
		bool is_cmmt = (m_lits.empty());
		bool is_cnf = (m_cmmt.empty());
		assert(!(is_cmmt && is_cnf));
		if (is_cmmt)
			DumpCmt(outs);
		else
			DumpCNF(outs);

	}
	void Add(const Literal& lit)
	{
		m_lits.push_back(lit);
	}
private:
	std::list<Literal> m_lits;
	std::string		m_cmmt;
};


class Formula
{
public:
	Formula(int n_props)
		: m_nProps(n_props)
	{
	}
	void Add(Clause& cls)
	{
		m_clses.push_back(std::move(cls));
	}
	void Dump(std::ostream& outs) const
	{
		outs << "p cnf " << m_nProps << " " << m_clses.size() << std::endl;
		for (auto it_cls = m_clses.begin()
			; it_cls != m_clses.end()
			; it_cls ++)
		{
			it_cls->Dump(outs);
		}
	}
private:
	int m_nProps;
	std::list<Clause> m_clses;
};

class Proposition
{
public:
	Proposition(bool val) : m_val(val)
	{
	}

	virtual Literal encode() const = 0;
protected:
	const bool m_val;
};