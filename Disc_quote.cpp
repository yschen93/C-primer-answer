#include <iostream>
#include <string>

using namespace std;

class Quote
{
public:
	Quote() = default;
	Quote(const string& bn, double dp) :bookNo(bn), price(dp){}
	virtual ~Quote() = default;
	string isbn() const { return bookNo; }
	virtual double net_price(size_t n) const;
private:
	string bookNo;
protected:
	double price = 0.0;
};

class Disc_quote : public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const string& book, double dp, size_t num, double dis)
		:Quote(book, dp), quantity(num), discount(dis){}
	double net_price(size_t n) const = 0;
protected:
	size_t quantity;
	double discount;
};

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string& bn, double dp, size_t num, double dis)
		:Disc_quote(bn, dp, num, dis){}
	void dis()
	{
		cout << quantity << endl;
	}
	double net_price(size_t n) const override;
};

class Limit_quote : public Disc_quote
{
public:
	Limit_quote(const string& bn, double dp, size_t num, size_t limit, double dis)
		:Disc_quote(bn, dp, num, dis){}
	double net_price(size_t n) const override;
};

double Quote::net_price(size_t n) const
{
	return n * price;
}

double Bulk_quote::net_price(size_t n) const
{
	if (n > quantity)
		return n * (1 - discount) * price;
	else
		return n * price;
}

double Limit_quote::net_price(size_t n) const
{
	if (n < quantity)
		return n * (1 - discount) * price;

	double sum = 0;
	if (n > quantity)
	{
		sum += (n - quantity) * price;
		sum += quantity * (1 - discount) * price;
	}

	return sum;
}

double print_total(ostream& out, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	out << "ISBN: " << item.isbn() << " sold: " << n << " total due: " << ret << endl;
	return ret;
}

int main()
{
	Quote qt("c++ primer", 20);
	Bulk_quote bq("advanced unix programing", 30, 100, 0.25);

	/*cout << print_total(cout, qt, 10) << endl;
	cout << print_total(cout, bq, 200) << endl;*/
	system("pause");
	return 0;
}
