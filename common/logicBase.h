#include <iostream>
#include <sstream>
#include <list>
#include <assert.h>

class Literal
{
public:
	Literal(bool val, int absCode)
		: m_val(val)
		, m_absCode(absCode)
	{
		assert(m_val > -1);
	}
	virtual void Dump(std::ostream& outs) const
	{
		if (m_val)
			outs << m_absCode + 1;
		else
			outs << -(m_absCode + 1);
	}

public:
	const int m_absCode;
	const bool m_val;
};


class Clause
{
public:
	Clause()
	{
	}
	~Clause()
	{
		for (auto it_lit = m_lits.begin()
			; it_lit != m_lits.end()
			; it_lit ++)
			delete *it_lit;
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
		(*it_lit)->Dump(outs);
		it_lit ++;
		for (
			; it_lit != m_lits.end()
			; it_lit ++)
		{
			outs << " "; (*it_lit)->Dump(outs);
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
	bool isCnf() const
	{
		return !m_lits.empty();
	}
	void Add(const Literal* lit)
	{
		m_lits.push_back(lit);
	}
	const std::list<const Literal*>& cnfLiterals() const
	{
		return m_lits;
	}
private:
	std::list<const Literal*> m_lits;
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

template<typename Functor>
bool ParseIter(std::istream& iss, Functor litFac, Clause& cls)
{
	int code_l = 0;
	while (iss >> code_l)
	{
		if (0 != code_l)
		{
			Literal* lit = litFac(code_l);
			cls.Add(lit);
		}
	}
	return cls.isCnf();
}

