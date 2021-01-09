#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>

using namespace std;

//================StrBlobPtr================

class StrBlob;

class StrBlobPtr
{
public:
	StrBlobPtr() : cur(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0);
	string& deref();
	StrBlobPtr& incur();
private:
	weak_ptr<vector<string> > wkptr;
	size_t cur;
	shared_ptr<vector<string> > check(size_t i, const string& msg) const;
};

string& StrBlobPtr::deref()
{
	auto ptr = check(cur, "dereference pass end");
	return (*ptr)[cur];
}

shared_ptr<vector<string> > StrBlobPtr::check(size_t i, const string& msg) const
{
	auto ret = wkptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
	{
		throw out_of_range(msg);
	}
	return ret;
}

StrBlobPtr& StrBlobPtr::incur()
{
	check(cur, "dereference pass end");
	++cur;
	return *this;
}

//================StrBlob================

class StrBlob
{
public:
	friend StrBlobPtr;
	using size_type = vector<string>::size_type;
	StrBlob() : data(make_shared<vector<string> >()) {}
	explicit StrBlob(initializer_list<string> il) : data(make_shared<vector<string> >(il)) {}
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string& s) { data->push_back(s); }
	void pop_back();
	string& front();
	const string& front() const;
	string& back();
	const string& back() const;

	StrBlobPtr begin();
	StrBlobPtr end();
private:
	shared_ptr<vector<string> > data;
	void check(size_type i, const string& msg) const;
};

void StrBlob::check(size_type i, const string& msg) const
{
	if (i >= size())
		throw out_of_range(msg);
}

string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

const string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

const string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
 {
	check(0, "pop_back on empty StrBlob");
	data->back();
 }

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this, 0);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, size());
}

//Why here? ues StrBlob definition
StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz)
	: wkptr(a.data), cur(sz)
{

}

int main()
{
	StrBlob temp({ "I", "am", "C++" });
	system("pause");
	return 0;
}

