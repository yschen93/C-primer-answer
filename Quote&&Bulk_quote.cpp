#include <iostream>
#include <string>
using namespace std;

class Quote
{
public:
	Quote() = default;
	Quote(const string& s, double sales_price) :bookNo(s), price(sales_price){}
	string isbn() const { return bookNo; }
	//Quote(const Quote& rhs) = default;
	virtual double net_price(size_t n) const { return n * price; }
	virtual ~Quote() = default;
	virtual void print() const
	{
		cout << "bookName: " << bookNo << ", price: " << price << endl;
	}
private:
	string bookNo;
protected:
	double price = 0;
};

class Bulk_Quote : public Quote
{
public:
	Bulk_Quote() = default;
	~Bulk_Quote() = default;
	Bulk_Quote(const string&s, double sales_price, size_t qty, double dis)
		:Quote(s, sales_price), quantity(qty), discount(dis){}
	double net_price(size_t n) const override;
	//Bulk_Quote(const Bulk_Quote& rhs);
	void print() const override
	{
		Quote::print();
		cout << "quantity: " << quantity << ", discount: " << discount << endl;
	}
private:
	size_t quantity = 0;
	double discount = 0;
};

double Bulk_Quote::net_price(size_t n) const
{
	if (n > quantity)
		return n * (1 - discount) * price;
	return Quote::net_price(n);
}

/*
Bulk_Quote::Bulk_Quote(const Bulk_Quote& rhs)
	:Quote(rhs)
{
	quantity = rhs.quantity;
	discount = rhs.discount;
}*/
int main()
{
	Bulk_Quote bq("C++ primer", 99, 200, 0.2);
	Bulk_Quote bq1(bq);
	bq.print();
	bq1.print();
	system("pause");
	return 0;
}
