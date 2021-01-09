#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>

using namespace std;

class StrBlob
{
public:
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

int main()
{
	StrBlob temp({ "I", "am", "c++" });
	system("pause");
	return 0;
}
