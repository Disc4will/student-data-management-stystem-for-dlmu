#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<conio.h>



using namespace std;
constexpr unsigned int lessions = 3;
constexpr unsigned int namelen = 8;
constexpr unsigned int classlen = 30;
constexpr unsigned int scorelen = 6;
constexpr unsigned int splen = 24;
constexpr unsigned int pagerecords = 27;
constexpr unsigned int lenchars = 120;
const string spath= "E:\\Project2\\datarev\\speciality.csv";
const string stupath = "E:\\Project2\\datarev\\studat.csv";


struct stu
{
	string son;
	string name;
	string classno;
	unsigned int spnum;
	float scores[3];
	float aveg;
	stu* next = NULL;
};

struct starnode
{
	unsigned int len = 0;
	stu* nex = NULL;
};
unsigned int strtouint(string dat) {
	unsigned int tp = 0;
	for (size_t i = 0; i < dat.size(); i++)
	{
		tp *= 10;
		tp += dat[i] - '0';
	}
	return tp;
}
string uinttostr(unsigned int dat) {
	string res = "";
	res += dat+'0';
	return res;
}
stu* slicehalf(stu* &p)
{
	stu* slow, * fast, * temp;
	slow = p;
	fast = p;
	temp = NULL;
	if (fast->next==NULL)
	{
		return NULL;
	}
	else if (fast->next->next==NULL)
	{
		slow = fast->next;
		fast->next = NULL;
		return slow;
	}
	while (fast != NULL )
	{
		temp = fast->next;
		fast = fast->next->next;
		slow = slow->next;
		if (fast->next==NULL)
		{
			fast = slow->next;
			slow->next = NULL;
			return 	fast;
		}
		else if (fast->next->next==NULL)
		{
			fast = slow->next;
			slow->next = NULL;
			return 	fast;
		}
	}
}
void middledisplay(string dat) { 
	unsigned int spcnt = (lenchars - dat.size()) / 2;
	for (size_t i = 0; i < spcnt; i++)
	{
		cout << ' ';
	}
	cout << dat;
}

bool compare(stu a, stu b, unsigned int method) {
	switch (method)
	{
	case 1:
	case 2:
	case 3:return a.scores[method - 1] > b.scores[method - 1] ? 1 : 0;
	case 4:return a.aveg > b.aveg;
	case 5:
		for (size_t i = 0; i < a.son.size(); i++)
		{
			if (a.son[i] != b.son[i])
				return a.son[i] > b.son[i] ? 1 : 0;
		}
		break;
	}
}


unsigned int getlen(stu* p) {
	unsigned int res = 0;
	stu* pt = p;
	while (pt!=NULL)
	{
		pt = pt->next;
		res++;
	}
	return res;
}
stu* merage(stu*& a, stu* &b, bool asend, unsigned int pivity) {
	stu* temp = NULL;
	stu* pt = NULL;
	while (a != NULL && b != NULL)
	{
		if ((!compare(*a, *b, pivity) && asend) || (compare(*a, *b, pivity) && !asend))
		{
			if (temp == NULL)
			{
				temp = a;
				pt = temp;
			}
			else
			{
				pt->next = a;
				pt = pt->next;
			}
			a = a->next;
		}
		else if ((!compare(*b, *a, pivity) && asend) || (compare(*b, *a, pivity) && !asend))
		{
			if (temp == NULL)
			{
				temp = b;
				pt = temp;
			}
			else
			{
				pt->next = b;
				pt = pt->next;
			}
			b = b->next;
		}
		else
		{
			if (temp == NULL)
			{
				temp = b;
				pt = temp;
			}
			else
			{
				pt->next = b;
				pt = pt->next;
			}
			b = b->next;
		}
	}
	if (a == NULL)
	{
		pt->next = b;
		b = NULL;
		delete[]b;
	}
	else if (b == NULL)
	{
		pt->next = a;
		a = NULL;
		delete[]a;
	}
	pt = NULL;
	delete pt;
	return temp;
}

stu* mesort(stu* &a,stu* &b,bool asend,unsigned int pivity){//归并排序
	if (getlen(a)>1)
	{
		stu* pa = slicehalf(a);
		a=mesort(a,pa ,asend,pivity);
	}
	if (getlen(b)>1)
	{
		stu* pb = slicehalf(a);
		b=mesort(b, pb,asend,pivity);
	}
	else if (getlen(a)==1 && getlen(b)==1)
	{
		if ((!compare(*a, *b, pivity) && asend) || (compare(*a, *b, pivity) && !asend))
		{
			a->next = b;
			b = NULL;
			delete b;
			return a;
		}
		else
		{
			b->next = a;
			a = NULL;
			delete a;
			return b;
		}
	}
	else if (a==NULL||b==NULL)
	{
		return a == NULL ? b : a;
	}
	a=merage(a, b,asend,pivity);
	return a;
}
unsigned int pivitysel() {
	unsigned int ch;
	cout << "Sort on which lession?(defult:math)" << '\n';
	cout << "  1.math" << '\n';
	cout << "  2.literature" << '\n';
	cout << "  3.art" << '\n';
	cout << "  4.average" << '\n';
	cout << "  5.studentnumber" << '\n';
	cin >> ch;
	switch (ch)
	{
	case 1:ch = 1; break;
	case 2:ch = 2; break;
	case 3:ch = 3; break;
	case 4:ch = 4; break;
	case 5:ch = 5; break;
	default:
		ch = 1;
		cout << "Invaild value,using defult value" << '\n' << endl;
		break;
	}
	return ch;
}
unsigned int ordersel() 
{
	unsigned int res;
	cout << "Sort by asend or desend?(defult:asend)\n";
	cout << "  1.asend\n";
	cout << "  2.desend\n";
	cin >> res;
	switch (res)
	{
	case 1:
		break;
	case 2:
		res -= 2;
		break;
	default:
		res = 1;
		cout << "Invaild value,using defult value" << endl;
		break;
	}
	return res;
}
void reorder(starnode* &p,bool &asend,unsigned int &pivity)
{
	pivity = pivitysel();
	asend = ordersel();
	stu* pt = slicehalf(p->nex);
	p->nex=mesort(p->nex, pt, asend, pivity);
	p->len = getlen(p->nex);
}
void moveto(vector<string>::iterator& pt, unsigned int pos)
{
	for (size_t i = 0; i < pos; i++)
	{
		pt++;
	}
}
void unique(vector<string>& sp)
{
	for (size_t i = 0; i < sp.size(); i++)
	{
		vector<string>::iterator pt = sp.begin();
		moveto(pt, i);
		auto pt2 = pt + 1;
		while (pt2 != sp.end())
		{
			if (*pt2 == *pt)
			{
				sp.erase(pt2);
				break;
			}
			pt2++;
		}
	}
}
void uniquestu(starnode*& p) {
	stu* tp, * pt;
	pt = p->nex;
	while (pt->next!=NULL)
	{
		tp = pt;
		while (tp->next != NULL)
		{
			if (tp->next->son==pt->son)
			{
				stu* temp = tp->next;
				tp->next = temp->next;
				free(temp);
			}
			tp = tp->next;
		}
	}
}
bool same(string a, string b) {
	if (a.size() != b.size())
	{
		return 0;
	}
	else
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return 0;
		}
		return 1;
	}
}
string conv(unsigned int pos, vector<string>sp) {
	return sp[pos];
}
unsigned int check(string t, vector<string>speciality) {
	unique(speciality);
	unsigned int tp = speciality.size();
	for (size_t i = 0; i < speciality.size(); i++)
	{
		if (same(t, speciality[i]))
			tp = i;
	}
	if (tp == speciality.size())
	{
		cout << "Invaild input,reinput:";
		cin >> t;
	}
	return tp;
}
void spputter(unsigned int cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		cout << ' ';
	}
}
void formatp(string a, unsigned int len)
{
	unsigned int r, l;
	r = (len - a.size()) / 2;
	l = r + (len - a.size()) % 2;
	spputter(r);
	cout << ' ' << a;
	spputter(l);
}

void formatf(float b, unsigned int len)
{
	cout << ' ';
	spputter(b / 10 == 0 ? 0 : 1);
	printf("%.2f", b);
}
void output(stu* link,vector<string>sp) {
	stu* pt = link;
	cout << link->son;
	formatp(link->name, namelen);
	formatp(link->classno, classlen);
	formatp(conv(link->spnum, sp), splen);
	for (size_t i = 0; i < lessions; i++)
	{
		formatf(link->scores[i], scorelen);
	}
	formatf(link->aveg, scorelen);
	cout << '\n';
}

void header()
{
	cout << '\n';
	spputter(2);
	cout << "学  号";
	spputter(4);
	cout << "姓  名";
	spputter(12);
	cout << "班      级";
	spputter(19);
	cout << "专    业";
	spputter(10);
	cout << "数 学";
	spputter(2);
	cout << "文 学";
	spputter(2);
	cout << "艺 术";
	spputter(2);
	cout << "均 分" << endl;
}
void formatdis(unsigned int& curpage, unsigned int totalpage, vector<stu*>res, vector<string>sp) {
	header();
	if (curpage == totalpage - 1)
	{
		for (int i = curpage * pagerecords; i < res.size(); i++)
			output(res[i], sp);
	}
	else 
	{
		for (size_t i = curpage * pagerecords; i < (curpage + 1) * pagerecords + 1; i++)
		{
			output(res[i], sp);
		}
	}
	curpage++;
	string tp = to_string(curpage) + "-" + to_string(totalpage) + " press arrow key to change display,esc to quit";
	middledisplay(tp);
}
void clearscreen() {
	system("cls");
}
void output_all(vector<stu*>res,vector<string>sp) {
	if (res.size()==0)
	{
		cout << '\n';
		middledisplay("No recordes selected!");
		return;
	}
	unsigned int curpage = 0;
	unsigned int totalpage = res.size() / pagerecords + 1;
	formatdis(curpage, totalpage, res,sp);
	while (true)
	{
		unsigned int keyval;
		if (_kbhit())
		{
			keyval = _getch();
			if (keyval==27)
				break;
			else if (keyval == 77 && curpage < totalpage)//press the rigth arrow key
			{
				clearscreen();
				formatdis(curpage, totalpage, res, sp);
			}
			else if (keyval == 75 && curpage > 1) {//press the left arrow key
				curpage -= 2;
				clearscreen();
				formatdis(curpage, totalpage, res, sp);
			}
		}
	}
}
void formatdis(unsigned int& curpage, unsigned int totalpage, vector<string>sp) {
	middledisplay("Speciality");
	cout << '\n';
	if (curpage==totalpage-1)
	{
		for (auto i = curpage * pagerecords; i < sp.size(); i++) {
			middledisplay(sp[i]);
			cout << '\n';
		}
	}
	else 
	{
		for (size_t i = curpage * pagerecords; i < (curpage + 1) * pagerecords; i++)
		{
			middledisplay(sp[i]);
			cout << '\n';
		}
	}
	curpage++;
	string tp = to_string(curpage) + "-" + to_string(totalpage) + " press arrow key to change display,esc to quit";
	middledisplay(tp);
}
void output_spall(vector<string>sp) {
	if (sp.size() == 0)
	{
		cout << '\n';
		middledisplay("No recordes selected!");
		return;
	}
	unsigned int curpage = 0;
	unsigned int totalpage = sp.size() / pagerecords + 1;
	formatdis(curpage, totalpage,sp);
	while (true)
	{
		unsigned int keyval;
		if (_kbhit())
		{
			keyval = _getch();
			if (keyval == 27)
				break;
			else if (keyval == 77 && curpage < totalpage)//press the rigth arrow key
			{
				clearscreen();
				formatdis(curpage, totalpage, sp);
			}
			else if (keyval == 75 && curpage > 1) {//press the left arrow key
				curpage -= 2;
				clearscreen();
				formatdis(curpage, totalpage, sp);
			}
		}
	}
	clearscreen();
}
void movepto(stu* &pt, unsigned int pos) {
	while (pos > 0)
	{
		pt = pt->next;
		pos--;
	}
}
void formatdis(unsigned int& curpage, unsigned int totalpage, starnode* p, vector<string>sp) {
	header();
	stu* pt = p->nex;
	movepto(pt, curpage * pagerecords);
	if (curpage == totalpage - 1)
	{
		while (pt!=NULL)
		{
			output(pt, sp);
			pt = pt->next;
		}
	}
	else
	{
		for (size_t i = curpage * pagerecords; i < (curpage + 1) * pagerecords + 1; i++)
		{
			output(pt, sp);
			pt = pt->next;
		}
	}
	curpage++;
	string tp = to_string(curpage) + "-" + to_string(totalpage) + " press arrow key to change display,esc to quit";
	middledisplay(tp);
}
void output_all(starnode* p, vector<string>sp) {
	if (p->len == 0)
	{
		cout << '\n';
		middledisplay("No recordes selected!");
		return;
	}
	unsigned int curpage = 0;
	unsigned int totalpage = p->len / pagerecords + 1;
	formatdis(curpage, totalpage, p, sp);
	while (true)
	{
		unsigned int keyval;
		if (_kbhit())
		{
			keyval = _getch();
			if (keyval == 27)
				break;
			else if (keyval == 77 && curpage < totalpage)//press the rigth arrow key
			{
				clearscreen();
				formatdis(curpage, totalpage, p, sp);
			}
			else if (keyval == 75 && curpage > 1) {//press the left arrow key
				curpage -= 2;
				clearscreen();
				formatdis(curpage, totalpage, p, sp);
			}
		}
	}
}


void readstu_all(starnode*& p)
{
	vector<string>reg;
	string buf;
	stu* pt = NULL;
	ifstream in;
	in.open(stupath);
	while (getline(in, buf)) 
	{
		unsigned int spcounter = 0;
		float score = 0;
		unsigned int pointpos = 0;
		bool point = 0;
		string t = "";
		stu* a = new stu;
		for (size_t i = 0; i < buf.size(); i++)
		{
			if (buf[i] == ' ')
			{
				switch (spcounter) 
				{
				case 0:
					a->son = t;
					break;
				case 1:
					a->name = t;
					break;
				case 2:
					a->classno = t;
					break;
				case 3:
					a->spnum = strtouint(t);
					pointpos = 0;
					break;
				case 4:
				case 5:
					a->scores[spcounter - 4] = (score / pow(10, pointpos));
					pointpos = 0;
					point = 0;
					break;
				default:break;
				}
				t.clear();
				score = 0;
				spcounter++;
			}
			else if (spcounter <= 3)
			{
				t += buf[i];
			}
			else if (spcounter > 3)
			{
				if (buf[i] == '.')
				{
					point = 1;
				}
				else if (point)
				{
					score *= 10;
					score += buf[i] - '0';
					pointpos++;
				}
				else 
				{
					score *= 10;
					score += buf[i] - '0';
				}
			}
		}
		a->scores[lessions - 1] = score / pow(10, pointpos);
		float sum = 0;
		for (size_t i = 0; i < lessions; i++)
		{
			sum += a->scores[i];
		}
		sum = sum / lessions;
		a->aveg = sum;
		if (p->nex == NULL)
		{
			p->nex = a;
			p->len++;
			pt = p->nex;
		}
		else
		{
			pt->next = a;
			p->len++;
			pt = pt->next;
		}
		reg.push_back(a->son);
	}
	for (size_t i = 0; i < reg.size(); i++)
	{
		for (auto j = i + 1; j < reg.size(); j++) {
			if (reg[i]==reg[j])
			{
				cout << i << ',' << j << endl;
			}
		}
	}
	in.close();
	clearscreen();
}

unsigned int poscheck(string a) {
	string reg[] = { "math","liberature","art","average" ,"sno","sp"};
	unsigned int tp = 0;
	for (size_t i = 0; i < 6; i++)
	{
		if (reg[i] == a)
			tp = i;
	}

	return tp;
}
stu* findpos(stu item, starnode* p, bool asend, unsigned int pivity) {
	stu* pt = p->nex;
	while (pt->next != NULL)
	{
		if ((compare(item, *pt, pivity) && !compare(item, *(pt->next), pivity) && asend) || (!compare(item, *pt, pivity) && compare(item, *(pt->next), pivity) && asend))
		{
			return pt;
		}
		pt = pt->next;
	}
	if ((compare(item, *(pt), pivity) && !asend) || (!compare(item, *(pt), pivity) && !asend))
	{
		return pt;
	}
}
void insert(stu* &item, starnode* &p, bool asend, unsigned int pivity) {
	stu* pt = p->nex;
	if (pt==NULL)
	{
		p->nex = item;
		item->next = NULL;
	}
	else if ((!compare(*item,*pt,pivity)&&asend)||(compare(*item,*pt,pivity)&&!asend))
	{
		p->nex = item;
		item->next = pt;
	}
	else
	{
		pt = findpos(*item, p, asend, pivity);
		item->next = pt->next;
		pt->next = item;
	}
	p->len++;
	return;
}
string stuinputread() {
	string tp, a;
	cout << "Please input the name of the new record,or type 0 to quit:" << endl;
	cin >> tp;
	getline(cin, a);
	tp += a;
	return tp;
}

void input(starnode* &p, vector<string>speciality, bool asend, unsigned int pivity) {
	string tp;
	tp = stuinputread();
	unsigned int spcounter = 0;
	float score = 0;
	unsigned int pointpos = 0;
	bool point = 0;
	string t = "";
	stu* a = new stu;
	if (tp == "0")
		return;
	for (size_t i = 0; i < tp.size(); i++)
	{
		if (tp[i] == ' ')
		{
			switch (spcounter) {
			case 0:
				a->son = t;
				break;
			case 1:
				a->name = t;
				break;
			case 2:
				a->classno = t;
				break;
			case 3:
				a->spnum = check(t, speciality);
				break;
			default:
				a->scores[spcounter - 4] = score / pow(10, pointpos);
				pointpos = 0;
				point = 0;
				break;
			}
			t.clear();
			score = 0;
			spcounter++;
		}
		else if (spcounter <= 3)
		{
			t += tp[i];
		}
		else if (spcounter > 3) {
			if (tp[i] == '.')
			{
				point = 1;
			}
			else if (point)
			{
				score *= 10;
				score += tp[i] - '0';
				pointpos++;
			}
			else {
				score *= 10;
				score += tp[i] - '0';
			}
		}
	}
	a->scores[lessions - 1] = score / pow(10, pointpos);
	float sum = 0;
	for (size_t i = 0; i < lessions; i++)
	{
		sum += a->scores[i];
	}
	sum = sum / lessions;
	a->aveg = sum;
	insert(a, p, asend, pivity);
}

void fetch(starnode* p,vector<string>sp,vector<stu*>&re) {
	re.empty();
	unsigned int pos = p->len;
	stu* res = p->nex;
	movepto(res, rand() % p->len);
	re.push_back(res);
}
float strtoflat(string c) {
	float ta = 0;
	bool point = 0;
	unsigned int pointpos = 0;
	for (size_t i = 0; i < c.size(); i++)
	{
		cout << c[i] - '0';
		if (c[i] == '.')
		{
			point = 1;
		}
		else
		{
			if (point)
			{
				pointpos++;
			}
			ta *= 10;
			ta += c[i] - '0';
		}
	}
	ta *= pow(0.1, pointpos);
	return ta;
}
bool concheck(int chs[], float a, float b, unsigned int pos) {
	bool res;
	switch (chs[pos])
	{
	case (int)0:res = a < b ? 1 : 0; break;
	case (int)1:res = a == b ? 1 : 0; break;
	case (int)2:res = a > b ? 1 : 0; break;
	}
	return res;
}
bool concheck(int chs[], string a, string b, unsigned int pos) {
	bool res;
	unsigned int diff = a.compare(b);
	switch (chs[pos])
	{
	case (int)0:res = diff > 0 ? 0 : 1; break;
	case (int)1:res = diff==0 ? 1 : 0; break;
	case (int)2:res = diff > 0 ? 1 : 0; break;
	}
	return res;
}
unsigned int seperate_speciality(string classon)
{
	for (size_t i = 0; i < classon.size(); i++)
	{
		int tp = classon[i] - '0';
		if(tp > 0 && tp < 9)
		{
			return i;
		}
	}
}
vector<stu*>search(starnode* pt,vector<string>speciality) 
{
	vector<stu*>res;
	stu* p = pt->nex;
	unsigned int q = 0;
	float scores[4];
	int chs[] = { -1,-1,-1,-1 ,-1,-1 };
	string classno,sno,sp;
	unsigned int spnm;
	string buf;
	string a, b;
	a = "";
	b = "";
	bool sep = 0;
	unsigned int spcnt = 0;//sep condi by space
	cout << '\n' << "Please input the equation of records(seperate by space):" << endl;
	cin >> buf;
	for (size_t i = 0; i < buf.size(); i++)
	{
		unsigned int pos = 0;
		if (buf[i] == ' ' || i == buf.size() - 1)
		{
			if (!sep) {
				if (i == buf.size() - 1)
				{
					a += buf[i];
				}
				classno = a;
				spnm = check(classno.substr(0, seperate_speciality(classno)), speciality);
			}
			else
			{
				if (i == buf.size() - 1)
				{
					b += buf[i];
				}
				pos = poscheck(a);
				if (pos<4)
					scores[pos] = strtoflat(b);
				else {
					switch (pos)
					{
					case 4:
						sno = b;
						break;
					case 5:
						sp = b;
						break;
					}
				}
				chs[pos] = q;
				sep = 0;
			}
			a = "";
			b = "";
			spcnt++;
		}
		else if (buf[i] < 63 && buf[i] > 59)
		{
			sep = 1;
			q = buf[i] - 60;
		}
		else if (!sep)
		{
			a += buf[i];
		}
		else if (sep)
		{
			b += buf[i];
		}
	}//condition reg
	unsigned int totalconditions = spcnt;
	while (p!=NULL)
	{
		if (p->classno == classno)
		{
			spcnt--;
		}
		for (unsigned int k = 0; k < 6; k++)
		{
			switch (k)
			{

			case 0:
			case 1:
			case 2:
				if (chs[k] > -1 && concheck(chs, p->scores[k], scores[k], k))
					spcnt--;
				break;
			case 3:
				if (chs[k] > -1 && concheck(chs, p->aveg, scores[k], k))
					spcnt--;
				break;
			case 4:
				if (chs[k] > -1 && concheck(chs, p->son, sno, k))
					spcnt--;
				break;
			case 5:
				if (chs[k] > -1 && k == 5 && concheck(chs, conv(p->spnum, speciality), sp, k))
					spcnt--;
				break;
			}
		}
		if (spcnt == 0)
		{
			res.push_back(p);
			spcnt = totalconditions;
		}
		p = p->next;
	}
	return res;
}
void movestupto(vector<stu*>::iterator& a, unsigned int pos) {
	while (pos>0)
	{
		a++;
	}
}
void deletestu(starnode*& p,vector<string>sp,vector<stu*>&res) {
	if (res.size()==0)
	{
		cout << "No records selected!" << endl;
		return;
	}
	unsigned int seg = 0;
	unsigned int i = 0;
	stu* re = new stu;
	re->next = p->nex;
	while (i!=res.size())
	{
		stu* pt = re;
		while (pt != NULL&&pt->next!=NULL)
		{
			if (pt->next==res[i])
			{
				pt->next = pt->next->next;
				i++;
				p->len--;
			}
			pt = pt->next;
		}
	}
	p->nex = re->next;
	for (size_t i = 0; i < res.size(); i++)
	{
		stu* pt = res[i];
		free(pt);
	}
	res.empty();
}
void save_singalstu(stu* pt) {
	ofstream out;
	out.open("E:\\Project1\\datarev\\speciality.csv", ofstream::app);
	out << pt->classno << ' ';
	out << pt->name << ' ';
	out << pt->classno << ' ';
	out << pt->spnum;
	for (size_t i = 0; i < lessions; i++)
	{
		out << ' ' << pt->scores[i];
	}
	out << endl;
	out.close();
}
void save_stuall(starnode* p) 
{
	ofstream out;
	out.open("E:\\Project1\\datarev\\speciality.csv");
	out << p->nex->classno << ' ';
	out << p->nex->name << ' ';
	out << p->nex->classno << ' ';
	out << p->nex->spnum;
	for (size_t i = 0; i < lessions; i++)
	{
		out << ' ' << p->nex->scores[i];
	}
	out << endl;
	out.close();
	stu* pt = p->nex->next;
	for (size_t i = 1; i < lessions; i++)
	{
		save_singalstu(pt);
		pt = pt->next;
	}
}

void readspeciality(vector<string>& sp) {
	ifstream in;
	string tp;
	in.open("E:\\Project1\\datarev\\speciality.csv");
	while (getline(in, tp))
	{
		sp.push_back(tp);
	}
	clearscreen();
	unique(sp);
}

bool confirm()
{
	unsigned int h;
	cout << "Are you sure? Unsaved change may be discorded\n  0.No\n  1.Yes\n";
	cin >> h;
	while (h > 1)
	{
		cout << "Invaild input,renter\n";
		cin >> h;
	}
	return h + 1 == 2 ? 1 : 0;
}
string inputread() {
	string tp;
	cout << "Please input the name of the speciality,or type 0 to quit:";
	cin >> tp;
	return tp;
}

void save(string dat) {
	ofstream out;
	out.open("E:\\Project1\\datarev\\speciality.csv", ofstream::app);
	out << dat << endl;
	out.close();
}
void correct(starnode* &p, unsigned int ch)
{
	stu* pt = p->nex;
	while (pt != NULL)
	{
		if (pt->spnum >= ch)
		{
			pt->spnum++;
		}
		pt = pt->next;
	}
}
void savesp_all(vector<string>sp) {
	ofstream out;
	out.open("E:\\Project1\\datarev\\speciality.csv");
	out << sp[0] << endl;
	out.close();
	for (size_t i = 1; i < sp.size(); i++)
	{
		save(sp[i]);
	}
	cout << "Save completed!" << '\n';
}
void specialityinput(starnode* &p, vector<string>& sp) {
	unique(sp);
	while (true)
	{
		cout << "Please input the name of the new specialiy,then enter to confirm,0 to exit\n";
		string tp = inputread();
		if (tp == "0")
		{
			return;
		}
		else
		{
			cout << "Please input the position you want to place it,current avaliable:" << sp.size() << '\n';
			unsigned int ch;
			cin >> ch;
			while (ch > sp.size())
			{
				cout << "Invaild input,renter!\n";
				cin >> ch;
			}
			vector<string>::iterator pt = sp.begin();
			moveto(pt, ch);
			sp.insert(pt, tp);
			unique(sp);
			correct(p, ch);
		}
	}
}
void createlist(starnode*& p,vector<string>speciality,bool asend,unsigned int pivity) {
	input(p, speciality, asend, pivity);
}

void manu() {
	cout << "Management for Students' scores\n";
	cout << "  1.Creat new records\n";
	cout << "  2.Reorder records\n";
	cout << "  3.Search and select\n";
	cout << "  4.List selected recordes\n";
	cout << "  5.Fetch and select record\n";
	cout << "  6.Reload student data from file\n";
	cout << "  7.Reload specialty data from file\n";
	cout << "  8.List speciality\n";
	cout << "  9.List record " << '\n';
	cout << "  10.Modify\n";
	cout << "  0.Exit" << '\n';
	cout << "Please input your choice:";
}
void modifymanu() 
{
	cout << "Modify selected records\n";
	cout << "  1.Append new student data\n";
	cout << "  2.Delete selected data\n";
	cout << "  3.Append new speciality\n";
	cout << "  4.Save student data to file\n";
	cout << "  5.Save speciality data to file\n";
	cout << "  0.Exit\n";
	cout << "Please input your choice:";
}
void modify(starnode*& p, vector<string>& speciality,vector<stu*>&res, bool asend, unsigned int pivity) {
	clearscreen();
	while (true)
	{
		modifymanu();
		unsigned int ch;
		cin >> ch;
		while (ch > 5)
		{
			cout << "\nInvalid input! Enter again:";
			cin >> ch;
		}
		switch (ch)
		{
		case 1:input(p, speciality, asend, pivity); break;
		case 2:deletestu(p, speciality, res); break;
		case 3:specialityinput(p, speciality); break;
		case 4:save_stuall(p); break;
		case 5:savesp_all(speciality); break;
		default:
			break;
		}
		if (ch==0)
			break;
		
	}
	clearscreen();
}
void init(vector<string>&sp)
{
	readspeciality(sp);
}
void handle(starnode* &p,vector<string>speciality,vector<stu*> &res,bool &asend,unsigned int &pivity) {
	while (true)
	{
		manu();
		unsigned int ch;
		cin >> ch;
		while (ch > 10)
		{
			cout << "Invaild input,renter!" << endl;
			cin >> ch;
		}
		clearscreen();
		switch (ch)
		{
		case 0: break;
		case 1: createlist(p, speciality, asend, pivity); break;
		case 2:
			if (confirm() && p->len > 0)
				reorder(p, asend, pivity);
			else 
			{
				clearscreen();
				cout << "No records!" << endl;
			}
			break;
		case 3:res = search(p, speciality); break;
		case 4:
			output_all(res, speciality); break;
		case 5:fetch(p, speciality, res); break;
		case 6:
			if (confirm())
				readstu_all(p);
			break;
		case 7:
			if (confirm())
				readspeciality(speciality);
			break;
		case 8:output_spall(speciality); cout << endl; break;
		case 9:output_all(p, speciality); cout << endl; break;
		case 10:modify(p, speciality, res, asend, pivity); break;
		}
		if (ch == 0)
			return;
	}
}

int main() 
{
	bool asend = 1;
	unsigned int pivity = 5;
	starnode* p = new starnode;
	vector<string>sp;
	vector<stu*>res;
	init(sp);
	handle(p, sp, res, asend, pivity);
	cout << '\n';
	middledisplay("See you in the space,cowboy!");
	cout << endl;
	return 0;
}