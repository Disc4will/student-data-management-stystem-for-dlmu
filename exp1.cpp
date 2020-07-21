#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<math.h>


using namespace std;


constexpr auto buffersize = 50;
constexpr unsigned int namelen = 8;
constexpr unsigned int classlen = 30;
constexpr unsigned int scorelen = 6;
constexpr unsigned int splen = 24;

struct stu {
	string name;
	string son;
	string classno;
	unsigned int spnum;
	vector<float>scores;
	float aveg;
};
bool same(stu a, stu b) 
{
	unsigned int res = 0;
	res += a.spnum == b.spnum ? 1 : 0;
	res += a.name == b.name ? 1 : 0;
	res += a.classno == b.classno ? 1 : 0;
	res += a.son == b.son ? 1 : 0;
	for (size_t i = 0; i < a.scores.size(); i++)
	{
		res += a.scores[i] == b.scores[i] ? 1 : 0;
	}
	return res == 7 ? 1 : 0;
}
void movepto(vector<stu>::iterator& s, unsigned int pos) {
	for (size_t i = 0; i < pos; i++)
	{
		s++;
	}
}
void uniques(vector<stu>& sets)
{
	for (size_t i = 0; i < sets.size(); i++)
	{
		for (size_t j = i+1; j < sets.size(); j++)
		{
			if (same(sets[i],sets[j]))
			{
				vector<stu>::iterator pt = sets.begin();
				movepto(pt, j);
				sets.erase(pt);
			};
		}
	}

}
unsigned int strtouint(string dat) {
	unsigned int tp = 0;
	for (size_t i = 0; i < dat.size(); i++)
	{
		tp *= 10;
		tp += dat[i] - '0';
	}
	return tp;
}

void readstuall(vector<stu>& sets, vector<string>sp) {
	ifstream in;
	string buf;
	sets.empty();
	in.open("E:\\Project2\\datarev\\studat.csv");
	while (getline(in, buf)) {
		unsigned int spcounter = 0;
		float score = 0;
		unsigned int pointpos = 0;
		bool point = 0;
		string t = "";
		stu a;
		for (size_t i = 0; i < buf.size(); i++)
		{
			if (buf[i] == ' ')//使用space来分割数据部分
			{
				switch (spcounter) {
				case 0:
					a.son = t;
					break;
				case 1:
					a.name = t;
					break;
				case 2:
					a.classno = t;
					break;
				case 3:
					pointpos = strtouint(t);
					a.spnum = pointpos;
					pointpos = 0;
				case 4:
				case 5:
					a.scores.push_back(score / pow(10, pointpos));
					pointpos = 0;
					point = 0;//小数点出现
					break;
				default:break;
				}
				t.clear();
				score = 0;
				spcounter++;
			}//存值并初始化部分计数器
			else if (spcounter <= 3)//前4项是字符串
			{
				t += buf[i];
			}
			else if (spcounter > 3) {//后面的就是数字
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
				else {
					score *= 10;
					score += buf[i] - '0';
				}
			}
		}
		vector<float>::iterator pt = a.scores.begin();
		a.scores.erase(pt);
		a.scores.push_back(score / pow(10, pointpos));
		float sum = 0;
		for (size_t i = 0; i < a.scores.size(); i++)
		{
			sum += a.scores[i];
		}
		sum = sum / a.scores.size();
		a.aveg = sum;
		sets.push_back(a);
		a.scores.empty();
	}
	in.close();
}


void manu() {
	cout << "Management for Students' scores" << '\n';
	cout << "  1.List speciality" << '\n';
	cout << "  2.List record " << '\n';
	cout << "  3.Delete record" << '\n';
	cout << "  4.Modify record" << '\n';
	cout << "  5.Search record" << '\n';
	cout << "  6.Sort score in descending order by student num" << '\n';
	cout << "  7.Sort score in ascending order by studend num" << '\n';
	cout << "  8.Sort score in ascending order by selected lession's score" << '\n';
	cout << "  9.Sort score in descending order by selected lession's score" << '\n';
	cout << "  10.Save to file" << '\n';
	cout << "  11.Reload form file" << '\n';
	cout << "  12.Max\n";
	cout << "  0.Exit" << '\n';
	cout << "Please input your choice:";
}


string inputread() {
	string tp;
	cout << "Please input the name of the speciality,or type 0 to quit:";
	cin >> tp;
	return tp;
}

void moveto(vector<string>::iterator &pt,unsigned int pos)
{
	for (size_t i = 0; i < pos; i++)
	{
		pt++;
	}
}
void correct(vector<stu>&sets,unsigned int ch)
{
	vector<stu>::iterator pt = sets.begin();
	while (pt!=sets.end())
	{
		if (pt->spnum>=ch)
		{
			pt->spnum++;
		}
		pt++;
	}
}
void unique(vector<string>&sp)
{
	for (size_t i = 0; i < sp.size(); i++)
	{
		vector<string>::iterator pt = sp.begin();
		moveto(pt, i);
		auto pt2 = pt+1;
		while (pt2!=sp.end())
		{
			if (*pt2==*pt)
			{
				sp.erase(pt2);
				break;
			}
			pt2++;
		}
	}
}
unsigned int getnum(vector<string>sp)
{
	unsigned int cnt = 0;
	vector<string>::iterator pt = sp.begin();
	while (pt!=sp.end())
	{
		pt++;
		cnt++;
	}
	return cnt;
}
void specialityinput(vector<stu>& sets , vector<string>& sp) {
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
			cout << "Please input the position you want to place it,current avaliable:"<<sp.size()<<'\n';
			unsigned int ch;
			cin >> ch;
			while (ch>sp.size())
			{
				cout << "Invaild input,renter!\n";
				cin >> ch;
			}
			vector<string>::iterator pt = sp.begin();
			moveto(pt, ch);
			sp.insert(pt, tp);
			unique(sp);
			correct(sets, ch);
		}
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
	unique(sp);
}

void save(string dat) {
	ofstream out;
	out.open("E:\\Project1\\datarev\\speciality.csv", ofstream::app);
	out << dat << endl;
	out.close();
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
void spputter(unsigned int cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		cout << ' ';
	}
}
void header() 
{
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
void read(vector<stu>& sets, vector<string>sp, unsigned int startpos) {
	ifstream in;
	string buf;
	sets.empty();
	in.open("E:\\Project1\\datarev\\studat.csv");
	for (size_t i = 0; i <= startpos; i++)
	{
		getline(in, buf);
	}
	while (getline(in, buf) && sets.size() <= buffersize) {
		unsigned int spcounter = 0;
		float score = 0;
		unsigned int pointpos = 0;
		bool point = 0;
		string t = "";
		stu a;
		for (size_t i = 0; i < buf.size(); i++)
		{
			if (buf[i] == ' ')
			{
				switch (spcounter) {
				case 0:
					a.son = t;
					break;
				case 1:
					a.name = t;
					break;
				case 2:
					a.classno = t;
					break;
				case 3:
					pointpos = strtouint(t);
					a.spnum = pointpos;
					pointpos = 0;
				case 4:
				case 5:
					a.scores.push_back(score / pow(10, pointpos));
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
				else {
					score *= 10;
					score += buf[i] - '0';
				}
			}
		}
		vector<float>::iterator pt = a.scores.begin();
		a.scores.erase(pt);
		a.scores.push_back(score / pow(10, pointpos));
		float sum = 0;
		for (size_t i = 0; i < a.scores.size(); i++)
		{
			sum += a.scores[i];
		}
		sum = sum / a.scores.size();
		a.aveg = sum;
		sets.push_back(a);
		a.scores.empty();
	}
	in.close();
}



void savetf(stu dat) {
	ofstream write;
	write.open("E:\\Project1\\datarev\\studat.csv", ofstream::app);
	write << dat.son << ' ';
	write << dat.name << ' ';
	write << dat.classno << ' ';
	write << dat.spnum;
	for (size_t i = 0; i < dat.scores.size(); i++)
	{
		write << ' ' << dat.scores[i];
	}
	write << endl;
	write.close();
}

void savestu_all(vector<stu>dat, vector<string>sp, unsigned int pos) {
	vector<string>pre;
	vector<string>nex;
	ifstream in;
	in.open("E:\\Project1\\datarev\\studat.csv");
	unsigned int p = 0;
	while (p < pos * buffersize)
	{
		string a;
		getline(in, a);
		pre.push_back(a);
		p++;
	}
	for (size_t i = 0; i < buffersize; i++)
	{
		string a;
		getline(in, a);
	}
	string a;
	while (getline(in, a)) {
		nex.push_back(a);
	}
	ofstream out;
	out.open("E:\\Project1\\datarev\\studat.csv");
	for (size_t i = 0; i < pre.size(); i++)
	{
		out << pre[i] << endl;
	}
	out.close();
	for (size_t i = 1; i < dat.size(); i++)
	{
		savetf(dat[i]);
	}
	out.open("E:\\Project1\\datarev\\studat.csv", ofstream::app);
	for (size_t i = 0; i < nex.size(); i++)
	{
		out << nex[i] << endl;
	}
	out.close();
}

void spinsert(vector<string>& st) {
	string tm;
	bool recov = 1;
	cout << "Please input the new speciality name:";
	cin >> tm;
	vector<string>::iterator b = st.begin();
	while (recov && b != st.end()) {
		if (*b == tm)
		{
			recov = 0;
		}
		b++;
	}
	if (recov) {
		string pos;
		cout << "Please input the num or name that you want to explace:";
		cin >> pos;
		if (pos[0] <= '9' && pos[0] >= '0') {
			unsigned int p = 0;
			for (size_t i = 0; i < pos.size(); i++)
			{
				p *= 10;
				p += pos[i] - '0';
			}
			if (p > st.size())
			{
				cout << "Invaild value,insert into the end";
				st.push_back(tm);
			}
			else
			{
				vector<string>::iterator j = st.begin();
				for (size_t i = 0; i < p - 1; i++)
				{
					j++;
				}
				st.insert(j, tm);
			}
		}
		else
		{
			vector<string>::iterator p = st.begin();
			for (p; p != st.end(); p++)
			{
				if (*p == pos)
				{
					break;
				}
			}
			if (p == st.end())
			{
				cout << "Invaild input,insert into the end";
				st.push_back(tm);
			}
			else
			{
				st.insert(p, tm);
			}
		}
	}
}

bool same(string a, string b) {
	if (a.size()!=b.size())
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
unsigned int check(string t, vector<string>speciality) {
	unique(speciality);
	unsigned int tp = speciality.size();
		for (size_t i = 0; i < speciality.size(); i++)
		{
			if (same(t,speciality[i]))
				tp = i;
		}
		if (tp == speciality.size())
		{
			cout << "Invaild input,reinput:";
			cin >> t;
		}
	return tp;
}

string stuinputread() {
	string tp, a;
	cout << "Please input the name of the new record,or type 0 to quit:" << endl;
	cin >> tp;
	getline(cin, a);
	tp += a;
	return tp;
}
void input(vector<stu>& sets, vector<string>speciality) {
	string tp;
	tp=stuinputread();
	unsigned int spcounter = 0;
	float score = 0;
	unsigned int pointpos = 0;
	bool point = 0;
	string t = "";
	stu a;
	if (tp=="0")
		return;
	for (size_t i = 0; i < tp.size(); i++)
	{
		if (tp[i] == ' ')
		{
			switch (spcounter) {
			case 0:
				a.son = t;
				break;
			case 1:
				a.name = t;
				break;
			case 2:
				a.classno = t;
				break;
			case 3:
				a.spnum = check(t, speciality);
				break;
			case 4:
			case 5:
				a.scores.push_back(score / pow(10, pointpos));
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
	a.scores.push_back(score / pow(10, pointpos));
	float sum = 0;
	for (size_t i = 0; i < a.scores.size(); i++)
	{
		sum += a.scores[i];
	}
	sum = sum / a.scores.size();
	a.aveg = sum;
	sets.push_back(a);
	cout << "Please input the position you want to put,current avaliable:" << sets.size();
	unsigned int ps;
	cin >> ps;
	while (ps>sets.size())
	{
		cout << "Invaild input,renter!\n";
		cin >> ps;
	}
	vector<stu>::iterator pt = sets.begin();
	movepto(pt, ps);
	sets.insert(pt, a);
	cout << '\n' << "Input complete!" << '\n';
}

string conv(unsigned int pos, vector<string>sp) {
	return sp[pos];
}


void formatp(string a,unsigned int len)
{
	unsigned int r,l;
	r = (len - a.size()) / 2;
	l = r + (len - a.size()) % 2;
	spputter(r);
	cout << ' ' << a;
	spputter(l);
}

void formatf(float b,unsigned int len)
{
	cout << ' ';
	spputter(b / 10 == 0 ? 0 : 1);
	printf("%.2f", b);
}

void output(stu dat, vector<string>sp) {
	/*cout << "name:" << dat.name << '\n';
	cout << "Student number:" << dat.son << '\n';
	cout << "Class:" << dat.classno << '\n';
	cout << "Speciality:" << conv(dat.spnum, sp) << '\n';
	cout << "Scores:";
	for (size_t i = 0; i < dat.scores.size(); i++)
	{
		cout << dat.scores[i] << ' ';
	}
	cout << "Average score:" << dat.aveg << endl;*/
	/*cout << dat.name << ' ' << dat.son << ' ' << dat.classno << ' ' << conv(dat.spnum, sp) << ' ';
	for (size_t i = 0; i < dat.scores.size(); i++)
	{
		cout << dat.scores[i] << ' ';
	}
	cout << dat.aveg<<"\n";
	cout << dat.son<<'\n';*/
	cout << dat.son;
	formatp(dat.name, namelen);
	formatp(dat.classno, classlen);
	formatp(conv(dat.spnum, sp), splen);
	for (size_t i = 0; i < dat.scores.size(); i++)
	{
		formatf(dat.scores[i], scorelen);
	}
	formatf(dat.aveg, scorelen);
	cout << '\n';
}




void save_all(vector<stu>sets) {
	for (size_t i = 0; i < sets.size(); i++)
	{
		savetf(sets[i]);
	}
}


bool concompare_1(float& top, stu a, unsigned int ch) {
	bool tp;
	switch (ch)
	{
	case 1:
		tp = top > a.scores[0];
		return tp;
		break;
	case 2:
		tp = top > a.scores[1];
		return tp;
		break;
	case 3:
		tp = top > a.scores[2];
		return tp;
		break;
	case 4:
		tp = top > a.aveg;
		return tp;
		break;
	}
}


void maxname(vector<string>sp) {
	unsigned int ch;
	string s[] = { "math","literature","art","average score" };
	cout << "Max and min on which lession?(defult:math)" << '\n';
	cout << "  1.math" << '\n';
	cout << "  2.literature" << '\n';
	cout << "  3.art" << '\n';
	cout << "  4.average score" << '\n';
	cin >> ch;
	switch (ch)
	{
	case 1:ch = 1; break;
	case 2:ch = 2; break;
	case 3:ch = 3; break;
	case 4:ch = 4; break;
	default:
		ch = 1;
		cout << "Invaild value,using defult value" << '\n' << endl;
		break;
	}
	vector<stu>dat;
	ifstream in;
	in.open("E:\\Project1\\datarev\\studat.csv");
	unsigned int lines = 0;
	string name;
	while (getline(in, name))
		lines++;
	in.close();
	unsigned int loads = lines / buffersize + 1;
	float max, min;
	stu reg[2];
	max = -1;
	min = 155;
	for (size_t j = 0; j < loads; j++)
	{
		read(dat, sp, j * buffersize);
		for (size_t i = 0; i < buffersize; i++)
		{
			if (!concompare_1(max, dat[i], ch))
			{
				switch (ch)
				{
				case 1:max = dat[i].scores[0]; break;
				case 2:max = dat[i].scores[1]; break;
				case 3:max = dat[i].scores[2]; break;
				case 4:max = dat[i].aveg; break;
				}
				reg[0] = dat[i];
			}
			else if (concompare_1(min, dat[i], ch)) {
				switch (ch)
				{
				case 1:min = dat[i].scores[0]; break;
				case 2:min = dat[i].scores[1]; break;
				case 3:min = dat[i].scores[2]; break;
				case 4:min = dat[i].aveg; break;
				}
				reg[1] = dat[i];
			}
		}
	}
	cout << reg[0].name << " gets the highest score on " << s[ch - 1] << " of " << max << endl;
	cout << reg[1].name << " gets the lowest score on " << s[ch - 1] << " of " << min << endl;;
	cout << "To see their other information,enter 0:";
	cin >> ch;
	if (ch == 0)
	{
		output(reg[0], sp);
		output(reg[1], sp);
	}
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

unsigned int poscheck(string a) {
	string reg[] = { "math","liberature","art","average" };
	unsigned int tp = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (reg[i] == a)
			tp = i;
	}
	return tp;
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

void search(vector<string>sp)
{
	float scores[4];
	int chs[] = { -1,-1,-1,-1 };
	unsigned int q = 0;
	vector<stu>sets, res;
	string classno;
	string buf;
	string a, b;
	a = "";
	b = "";
	bool sep = 0;
	unsigned int spcnt = 0;
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
			}
			else
			{
				if (i == buf.size() - 1)
				{
					b += buf[i];
				}
				pos = poscheck(a);
				scores[pos] = strtoflat(b);
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
	}
	ifstream in;
	in.open("E:\\Project1\\datarev\\studat.csv");
	unsigned int lines = 0;
	string name;
	while (getline(in, name))
		lines++;
	unsigned int loads = lines / buffersize + 1;
	unsigned int p = spcnt;
	in.close();
	for (size_t j = 0; j < loads; j++)
	{
		read(sets, sp, j * buffersize);
		for (size_t i = 0; i < sets.size(); i++)
		{
			if (sets[i].classno == classno)
			{
				spcnt--;
			}
			for (unsigned int k = 0; k < 4; k++)
			{
				if (chs[k] > -1 && k < 3 && concheck(chs, sets[i].scores[k], scores[k], k))
				{
					spcnt--;
				}
				else if (chs[k] > -1 && k == 3 && concheck(chs, sets[i].aveg, scores[k], k))
					spcnt--;
			}
			if (spcnt == 0)
			{
				res.push_back(sets[i]);
				spcnt = p;
			}
		}
	}
	uniques(res);
	cout << '\n' << res.size() << " record found:" << '\n';
	for (size_t i = 0; i < res.size(); i++)
	{
		output(res[i], sp);
	}
	return;
}


bool compare(stu a, stu b, unsigned int method) {
	switch (method)
	{
	case 1:
	case 2:
	case 3:return a.scores[method - 1] > b.scores[method - 1];
	case 4:return a.aveg > b.aveg;
	case 5:
		for (size_t i = 0; i < a.son.size(); i++)
		{
			if (a.son[i] != b.son[i])
				return a.son[i]>b.son[i]?1:0;
		}
		break;
	}
}


void valsel(unsigned int lpos, unsigned int hpos, bool asend, unsigned int pivity, vector<stu>sets, unsigned int& maxpos, unsigned int& minpos) {
	minpos = lpos;
	maxpos = lpos;
	for (size_t i = lpos + 1; i <= hpos; i++)
	{
		if ((!compare(sets[maxpos], sets[i], pivity) && asend) || (compare(sets[maxpos], sets[i], pivity) && !asend))
		{
			maxpos = i;
		}
		else if ((compare(sets[minpos], sets[i], pivity) && asend) || (!compare(sets[minpos], sets[i], pivity) && !asend))
		{
			minpos = i;
		}
	}
}


void Sort_select(vector<stu>& sets, bool asend, unsigned int pivity) {
	unsigned int lpos = 0;
	unsigned int hpos = sets.size() - 1;
	stu swap;
	while (lpos - hpos > 0)
	{
		unsigned int maxpos, minpos;
		valsel(lpos, hpos, asend, pivity, sets, maxpos, minpos);
		swap = sets[lpos];
		sets[lpos] = sets[minpos];
		sets[minpos] = swap;
		swap = sets[hpos];
		sets[hpos] = sets[maxpos];
		sets[maxpos] = swap;
		lpos++;
		hpos--;
	}
	uniques(sets);
	cout << "Sort completed!" << '\n';
}
void unique(vector<stu>sets) {
	vector<stu>::iterator pt1 = sets.begin();
	vector<stu>::iterator pt2 = pt1++;
	for (size_t i = 0; i < sets.size(); i++)
	{
		vector<stu>::iterator pt1 = sets.begin();
		vector<stu>::iterator pt2 = pt1++;
	}
}
void Sort_buble(vector<stu>& sets, bool asend, unsigned int pivity) {
	bool flag = 0;
	cout << '\n';
	for (size_t i = 0; i < sets.size() - 1; i++)
	{
		for (unsigned int j = i + 1; j < sets.size(); j++) {
			stu swap;
			/*if ((compare(sets[i], sets[j], pivity) && asend) || (!compare(sets[i],sets[j],pivity) && !asend))//控制升降序
			{
				swap = sets[i];
				sets[i] = sets[j];
				sets[j] = swap;
				flag = 1;
			}*/
			if (asend)
			{
				if (compare(sets[i], sets[j], pivity))
				{
					swap = sets[i];
					sets[i] = sets[j];
					sets[j] = swap;
					flag = 1;
				}
			}
			else
			{
				if (!compare(sets[i], sets[j], pivity))
				{
					swap = sets[i];
					sets[i] = sets[j];
					sets[j] = swap;
					flag = 1;
				}
			}
		}
		if (!flag)
			break;
	}
	uniques(sets);
	cout << "Sort completed!" << '\n';
	//试着输出结果
}


unsigned int findm(vector<stu>sets, unsigned int spos, bool asend, unsigned int pivity) {
	unsigned int m = spos;
	unsigned int i = spos == 0 ? 0 : spos - 1;
	for (i; i < sets.size(); i++)
	{
		if ((!compare(sets[m], sets[i], pivity) && asend) || (compare(sets[m], sets[i], pivity) && !asend))
		{
			m = i;
		}
	}
	return m;
}




void insertosets(vector<stu>& sets, unsigned int spos, unsigned int m, bool asend, unsigned int pivity)
{
	vector<stu>::iterator s = sets.begin();
	movepto(s, m);
	unsigned int pos = 0;
	unsigned int i = 0;
	if (spos == 0)
	{
		pos = 0;
	}
	else if (spos > 0 && ((compare(sets[m], sets[spos - 1], pivity) && !asend) || !(compare(sets[m], sets[spos - 1], pivity) || !asend)))
	{
		pos = spos - 1;
	}
	else
	{
		for (i = 0; i + 1 < spos; i++)
		{
			bool nex = compare(sets[m], sets[i + 1], pivity);
			bool pre = compare(sets[m], sets[i], pivity);
			if ((!nex && pre && asend) || (nex && !pre && !asend))
			{
				pos = i;
			}
		}
	}
	vector<stu>::iterator n = sets.begin();
	movepto(n, pos);
	sets.insert(n, *s);
	s = sets.begin();
	movepto(s, m + 1);
	sets.erase(s);
	return;
}

void Sort_insert(vector<stu>& sets, bool asend, unsigned int pivity) {
	unsigned int pos = 0;
	for (size_t i = 0; i < sets.size(); i++)
	{
		insertosets(sets, i, findm(sets, i, asend, pivity), asend, pivity);
	}
	cout << "Sort completed!\n";
	uniques(sets);
	return;
}


void sort_selection(vector<stu>&sets,vector<string>sp,bool asend,unsigned int pivity) {
	unsigned int a;
	cout << "Please select a sort method(defult:simple select sort)" << '\n';
	cout << "  1.Simple select sort" << '\n';
	cout << "  2.Bubel sort" << '\n';
	cout << "  3.Insert sort" << '\n';
	cin >> a;
	switch (a)
	{
	case 1:Sort_select(sets,asend,pivity); break;
	case 2:Sort_buble(sets,asend,pivity); break;
	case 3:Sort_insert(sets,asend,pivity); break;
	default:
		Sort_select(sets,asend,pivity);break;
	}
	header();
	for (size_t i = 0; i < sets.size(); i++)
	{
		output(sets[i], sp);
	}
}

bool confirm() 
{
	unsigned int h;
	cout << "Are you sure? Unsaved change may be discorded\n  0.No\n  1.Yes\n";
	cin >> h;
	while (h>1)
	{
		cout << "Invaild input,renter\n";
		cin >> h;
	}
	return h + 1 == 2 ? 1 : 0;
}


void Fetch(vector<string>sp)
{
	vector<stu>sets;
	readstuall(sets, sp);
	unsigned int pos = rand() % (sets.size() + 1);
	output(sets[pos], sp);
}
void showsp(vector<string>sp)
{
	cout << endl;
	for (size_t i = 0; i < sp.size(); i++)
	{
		cout << sp[i] << "\n";
	}
}
void modify(vector<stu>&sets,vector<string>&sp)
{
	unsigned int ch,p;
	cout << "Please select your instruction code:\n";
	cout << "  1.Append an new speciality\n";
	cout << "  2.Reload speciality from file\n";
	cout << "  3.Fetch record\n";
	cout << "  4.Append an new record\n";
	cout << "  0.Exit\n";
	cin >> ch;
	while (ch>5)
	{
		cout << "Invaild input,renter\n";
		cin >> ch;
	}
	switch (ch)
	{
	case 1:specialityinput(sets,sp); break;
	case 2:
		readspeciality(sp);
		if (confirm())
		{
			savesp_all(sp);
		}
		break;
	case 3:Fetch(sp); break;
	case 4:input(sets, sp); break;
	case 5:
		cout << "Are you sure?\n  0.No\n  1.Yes" << endl;
		cin >> p;
		while (p>1)
		{
			cout << "Invaild input,renter!\n";
			cin >> p;
		}
		if (p == 0)break;
		else
		{
			savesp_all(sp);
			break;
		}
	case 0:
	default:
		break;
	}
}

void List_all(vector<stu>sets,vector<string>sp)
{
	header();
	for (size_t i = 0; i < sets.size(); i++)
	{
		output(sets[i],sp);
	}
}


void Deleterecord(vector<string>sp)
{
	float scores[4];
	int chs[] = { -1,-1,-1,-1 };
	unsigned int q = 0;
	vector<stu>sets, res;
	string classno;
	string buf;
	string a, b;
	a = "";
	b = "";
	bool sep = 0;
	unsigned int spcnt = 0;
	cout << '\n' << "Please input the equation of records(seperate by space):" << endl;
	getline(std::cin, buf);
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
			}
			else
			{
				if (i == buf.size() - 1)
				{
					b += buf[i];
				}
				pos = poscheck(a);
				scores[pos] = strtoflat(b);
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
	}
	unsigned int p = spcnt;
	for (size_t i = 0; i < sets.size(); i++)
	{
		if (sets[i].classno == classno)
		{
			spcnt--;
		}
		for (unsigned int k = 0; k < 4; k++)
		{
			if (chs[k] > -1 && k < 3 && concheck(chs, sets[i].scores[k], scores[k], k))
			{
				spcnt--;
			}
			else if (chs[k] > -1 && k == 3 && concheck(chs, sets[i].aveg, scores[k], k))
				spcnt--;
		}
		if (spcnt == 0)
		{
			res.push_back(sets[i]);
			spcnt = p;
		}
	}
	cout << '\n' << res.size() << " record deleted:" << '\n';
	for (size_t i = 0; i < res.size(); i++)
	{
		output(res[i], sp);
	}
	unsigned int rs = res.size();
	while (rs!=0)
	{
		for (size_t i = 0; i < sets.size(); i++)
		{
			if(same(res[rs-1],sets[i]))
			{
				vector<stu>::iterator pt = sets.begin();
				movepto(pt, i);
				sets.erase(pt);
			}
		}
		rs--;
	}
	cout << "Save to file?(defult:no)" << '\n';
	cout << "  1.yes\n  2.no";
	unsigned int ch;
	cin >> ch;
	switch (ch)
	{
	case 1:
		save_all(res);
		cout << "Change saved to file!" << endl;
	default:
		break;
	}
	return;
}


void read(vector<stu>& sets) {
	ifstream in;
	string buf;
	in.open("E:\\Project1\\datarev\\studat.csv");
	while (getline(in, buf) && sets.size() <= buffersize) {
		unsigned int spcounter = 0;
		float score = 0;
		unsigned int pointpos = 0;
		bool point = 0;
		string t = "";
		stu a;
		for (size_t i = 0; i < buf.size(); i++)
		{
			if (buf[i] == ' ')
			{
				switch (spcounter) {
				case 0:
					a.name = t;
					break;
				case 1:
					a.son = t;
					break;
				case 2:
					a.classno = t;
					break;
				case 3:
				case 4:
					a.scores.push_back(score / pow(10, pointpos));
					pointpos = 0;
					point = 0;
					break;
				default:break;
				}
				t.clear();
				score = 0;
				spcounter++;
			}
			else if (spcounter < 3)
			{
				t += buf[i];
			}
			else if (spcounter >= 3) {
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
				else {
					score *= 10;
					score += buf[i] - '0';
				}
			}
		}
		a.scores.push_back(score / pow(10, pointpos));
		float sum = 0;
		for (size_t i = 0; i < a.scores.size(); i++)
		{
			sum += a.scores[i];
		}
		sum = sum / a.scores.size();
		a.aveg = sum;
		sets.push_back(a);
		a.scores.empty();
	}
}


void handle(unsigned int ch,vector<stu>&sets,vector<string>&sp) {
	switch (ch)
	{
	case 0:break;
	case 1:showsp(sp); break;
	case 2:List_all(sets,sp); break;
	case 3:Deleterecord(sp); break;
	case 4:modify(sets,sp); break;
	case 5:search(sp); break;
	case 6:sort_selection(sets,sp, 1, 5); break;
	case 7:sort_selection(sets,sp, 0, 5); break;
	case 8:
		sort_selection(sets,sp, 1, pivitysel());
		break;
	case 9:
		sort_selection(sets,sp, 0, pivitysel());
		break;
	case 10:save_all(sets); break;
	case 11:
		if (confirm())
		{
			sets.empty();
			read(sets);
			cout << "Reload complete" << endl;
		}
		break;
	case 12:
		maxname(sp);
		break;
	default:
		cout <<'\n'<< "Invaild choice! Please enter again!" << endl;
		break;
	}
}


void reload(vector<stu>& sets) {
	ifstream in;
	string buf;
	stu a;
	unsigned int count = 0;
	in.open("E:\\Project1\\datarev\\studat.csv");
	getline(in, buf);
	while (count < buffersize && buf == "");
	{
		unsigned int spcounter = 0;
		float score = 0;
		unsigned int pointpos = 0;
		bool point = 0;
		string t = "";
		for (size_t i = 0; i < buf.size(); i++)
		{
			if (buf[i] == ' ')
			{
				switch (spcounter) {
				case 0:
					a.name = t;
					break;
				case 1:
					a.son = t;
					break;
				case 2:
					a.classno = t;
					break;
				case 3:
				case 4:
					a.scores.push_back(score / pow(10, pointpos));
					pointpos = 0;
					point = 0;
					break;
				default:break;
				}
				t.clear();
				score = 0;
				spcounter++;
			}
			else if (spcounter < 3)
			{
				t += buf[i];
			}
			else if (spcounter >= 3) 
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
				else {
					score *= 10;
					score += buf[i] - '0';
				}
			}
		}
		a.scores.push_back(score / pow(10, pointpos));
		float sum = 0;
		for (size_t i = 0; i < a.scores.size(); i++)
		{
			sum += a.scores[i];
		}
		sum = sum / a.scores.size();
		a.aveg = sum;
	}
	sets.push_back(a);
}


void init(vector<stu>& sets, vector<string>& sp) {
	readspeciality(sp);
	readstuall(sets,sp);
}
bool co(string a, string b) {
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] > b[i])
			return 1;
	}
	return 0;
}
int main() {
	vector<stu> sets;
	vector<string>sp;
	unsigned int choice;
	init(sets, sp);
	manu();
	cin >> choice;
	while (choice > 0)
	{
		handle(choice, sets, sp);
		manu();
		cin >> choice;
	}
	cout << '\n' << "See you in the space,cowboy!" << endl;
	return 0;
}