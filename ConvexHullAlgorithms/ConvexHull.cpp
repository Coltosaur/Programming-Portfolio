#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

//---------------------helper functions and variables---------------------

static int lowest_y = INT_MAX;
static int lowest_x = INT_MAX;

struct point
{
	int x;
	int y;
};

int minimum_y_coordinate(vector<point> Q)
{
	int index_of_lowest = 0;
	lowest_y = INT_MAX;
	lowest_x = INT_MAX;
	while (!Q.empty())
	{
		if (lowest_y > Q.at(Q.size() - 1).y)
		{
			lowest_x = Q.at(Q.size() - 1).x;
			index_of_lowest = Q.size() - 1;
			lowest_y = Q.at(Q.size() - 1).y;
		}
		else if (lowest_y == Q.at(Q.size() - 1).y)
		{
			if (lowest_x >= Q.at(Q.size() - 1).x)
			{
				lowest_x = Q.at(Q.size() - 1).x;
				index_of_lowest = Q.size() - 1;
				lowest_y = Q.at(Q.size() - 1).y;
			}
		}
		Q.pop_back();
	}
	return index_of_lowest;
}

double cross_product(point p0, point p1, point p2)
{
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

bool is_left_turn(point p0, point p1, point p2)
{
	double cross = cross_product(p0, p2, p1);
	if (cross < 0)
		return true;

	return false;
}

double point_distance(point p0, point p1)
{
	return sqrt(pow((p1.y - p0.y), 2) + pow((p1.x - p0.x), 2));
}

void remove_duplicate_angle_points(vector<point>& Q, point p0)
{
	for (int i = 0; i < Q.size() - 1; i++)
	{
		if (cross_product(p0, Q.at(i+1), Q.at(i)) == 0)
		{
			if (point_distance(p0, Q.at(i)) < point_distance(p0, Q.at(i + 1)))
				Q.erase(Q.begin() + i);
			else
				Q.erase(Q.begin() + i + 1);
			i = i - 1;
		}
	}
}

void merge(vector<point>& A, int p, int q, int r, point p0)
{
	int n1 = 0;
	int n2 = p;
	int n3 = q + 1;

	//temp vector
	vector<point> temp;
	temp.resize(r - p + 1);

	//merge in sorted form the 2 arrays
	while (n2 <= q && n3 <= r)
	{
		//gets the angle of n2 and compares if less than n3 (if it is closer to p0 or not)
		//if moving clockwise, and n2 is less than n3, then comparatively, n2->n3 forms a left turn
		//if (get_angle(p0, A.at(n2)) < get_angle(p0, A.at(n3)))
		if (is_left_turn(p0, A.at(n2), A.at(n3)))
			temp.at(n1++) = A.at(n2++);
		else
			temp.at(n1++) = A.at(n3++);
	}

	//merge the remaining elements in left array
	while (n2 <= q)
		temp.at(n1++) = A.at(n2++);

	//merge the remaining elements in the right array
	while (n3 <= r)
		temp.at(n1++) = A.at(n3++);

	//move from temp to main vector
	for (int i = p; i <= r; i++)
	{
		A.at(i) = temp.at(i - p);
	}
}

void merge_sort(vector<point>& A, int p, int r, point p0)
{
	//http://www.sourcetricks.com/2011/06/merge-sort.html
	//where I got merge-sort, after struggling with implementing the text book's pseudocode
	if (p < r)
	{
		int q = floor((p + r) / 2);
		merge_sort(A, p, q, p0);
		merge_sort(A, q + 1, r, p0);
		merge(A, p, q, r, p0);
	}
}

point find_farthest_point_from_lowest(vector<point> Q, point p0)
{
	point highest = { 0, 0 };
	double highest_distance = DBL_MIN;
	int highest_y = INT_MIN;
	for (int i = 0; i < Q.size(); i++)
	{
		if (Q.at(i).y > highest_y)
		{
			highest_y = Q.at(i).y;
			highest_distance = point_distance(p0, Q.at(i));
			highest = Q.at(i);
		}
		else if (Q.at(i).y == highest_y)
		{
			if (point_distance(p0, Q.at(i)) > highest_distance)
			{
				highest_y = Q.at(i).y;
				highest_distance = point_distance(p0, Q.at(i));
				highest = Q.at(i);
			}
		}
	}
	return highest;
}

point find_next_point_on_right_hull(vector<point>& Q, vector<point> S)
{
	point next_point = Q.at(0);
	int index_of_point = 0;
	
	for (int i = 1; i < Q.size(); i++)
	{
		if (cross_product(S.at(S.size() - 1), next_point, Q.at(i)) < 0)
		{
			next_point = Q.at(i);
			index_of_point = i;
		}
		else if (cross_product(S.at(S.size() - 1), next_point, Q.at(i)) == 0)
		{
			if (point_distance(S.at(S.size() - 1), next_point) < point_distance(S.at(S.size() - 1), Q.at(i)))
			{
				next_point = Q.at(i);
				index_of_point = i;
			}
		}
	}
	Q.erase(Q.begin() + index_of_point);
	return next_point; 
}

point find_next_point_on_left_hull(vector<point>& Q, vector<point> S)
{
	Q.push_back(S.at(0));
	point next_point = Q.at(0);
	int index_of_point = 0;
	int index_of_start = Q.size()-1;

	for (int i = 1; i < Q.size(); i++)
	{
		if (cross_product(S.at(S.size() - 1), Q.at(i), next_point) > 0)
		{
			next_point = Q.at(i);
			index_of_point = i;
		}
		else if (cross_product(S.at(S.size() - 1), Q.at(i), next_point) == 0)
		{
			if (point_distance(S.at(S.size() - 1), next_point) < point_distance(S.at(S.size() - 1), Q.at(i)))
			{
				next_point = Q.at(i);
				index_of_point = i;
			}
		}
	}
	Q.erase(Q.begin() + index_of_start);
	if (index_of_point != index_of_start)
		Q.erase(Q.begin() + index_of_point);
	return next_point;
}

//---------------------------ALGORITHM IMPLEMENTATIONS---------------------------

//graham scan implementation
vector<point> graham_scan(vector<point> Q)
{
	vector<point> S;
	int lowest = minimum_y_coordinate(Q);
	point p0 = { lowest_x, lowest_y };
	Q.erase(Q.begin() + lowest);
	merge_sort(Q, 0, Q.size() - 1, p0);
	remove_duplicate_angle_points(Q, p0);
	
	if (Q.size() < 2)
	{
		S.clear();
		return S; //return empty convex hull
	}
	else
	{
		S.push_back(p0);
		S.push_back(Q.at(0));
		S.push_back(Q.at(1));
		for (int i = 2; i < Q.size(); i++)
		{
			while (!(is_left_turn(S.at(S.size() - 2), S.at(S.size() - 1), Q.at(i))))
			{
				S.pop_back();
			}
			S.push_back(Q.at(i));
		}
		return S;
	}
}

//jarvis march implementation
vector<point> jarvis_march(vector<point> Q)
{
	vector<point> S;
	int lowest = minimum_y_coordinate(Q);
	point p0 = { lowest_x, lowest_y };
	Q.erase(Q.begin() + lowest);
	point p_onehalf_n = find_farthest_point_from_lowest(Q, p0);
	S.push_back(p0);
	point next_point = find_next_point_on_right_hull(Q, S);
	S.push_back(next_point);
	
	//find next point, p1 that is part of the convex hull
	while ((next_point.x != p_onehalf_n.x) || (next_point.y != p_onehalf_n.y))
	{
		next_point = find_next_point_on_right_hull(Q, S);
		S.push_back(next_point);
	}
	
	while ((next_point.x != S.at(0).x) || (next_point.y != S.at(0).y))
	{
		next_point = find_next_point_on_left_hull(Q, S);
		if (!(next_point.x == S.at(0).x && next_point.y == S.at(0).y))
			S.push_back(next_point);
	}

	if (S.size() <= 2)
	{
		S.clear();
		return S; //return empty convex hull if points are co-linear
	}
	return S; 
}

//------------------------TESTING BEGINS HERE-----------------------------

//TEST CASES FOR 32 POINT SETS

//test case 1, where h > logn, or in this case, h = 14 and n = 32
void testcase1_32_points()
{
	//CASE 1, SET OF 32 POINTS, N = 32, AND H = 14 (H > LOGN, OR H > 5)
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 10, 1 };
	point p1 = { 15, 1 };
	point p2 = { 20, 2 };
	point p3 = { 21, 3 };
	point p4 = { 5, 2 };
	point p5 = { 4, 3 };
	point p6 = { 4, 10 };
	point p7 = { 21, 10 };
	point p8 = { 20, 20 };
	point p9 = { 5, 20 };
	point p10 = { 18, 23 };
	point p11 = { 8, 23 };
	point p12 = { 12, 24 };
	point p13 = { 12, 20 };
	point p14 = { 13, 20 };
	point p15 = { 13, 24 };
	point p16 = { 6, 10 };
	point p17 = { 6, 9 };
	point p18 = { 8, 19 };
	point p19 = { 13, 4 };
	point p20 = { 14, 4 };
	point p21 = { 15, 7 };
	point p22 = { 18, 16 };
	point p23 = { 19, 16 };
	point p24 = { 11, 16 };
	point p25 = { 11, 17 };
	point p26 = { 20, 4 };
	point p27 = { 17, 7 };
	point p28 = { 16, 9 };
	point p29 = { 9, 14 };
	point p30 = { 10, 10 };
	point p31 = { 15, 10 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);
	Q.push_back(p8);
	Q.push_back(p9);
	Q.push_back(p10);
	Q.push_back(p11);
	Q.push_back(p12);
	Q.push_back(p13);
	Q.push_back(p14);
	Q.push_back(p15);
	Q.push_back(p16);
	Q.push_back(p17);
	Q.push_back(p18);
	Q.push_back(p19);
	Q.push_back(p20);
	Q.push_back(p21);
	Q.push_back(p22);
	Q.push_back(p23);
	Q.push_back(p24);
	Q.push_back(p25);
	Q.push_back(p26);
	Q.push_back(p27);
	Q.push_back(p28);
	Q.push_back(p29);
	Q.push_back(p30);
	Q.push_back(p31);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);
	Q2.push_back(p8);
	Q2.push_back(p9);
	Q2.push_back(p10);
	Q2.push_back(p11);
	Q2.push_back(p12);
	Q2.push_back(p13);
	Q2.push_back(p14);
	Q2.push_back(p15);
	Q2.push_back(p16);
	Q2.push_back(p17);
	Q2.push_back(p18);
	Q2.push_back(p19);
	Q2.push_back(p20);
	Q2.push_back(p21);
	Q2.push_back(p22);
	Q2.push_back(p23);
	Q2.push_back(p24);
	Q2.push_back(p25);
	Q2.push_back(p26);
	Q2.push_back(p27);
	Q2.push_back(p28);
	Q2.push_back(p29);
	Q2.push_back(p30);
	Q2.push_back(p31);

	//CASE 1  n = 32 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 1 n = 32 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//test case 2, where h <= logn, or in this case, h = 5 and n = 32
void testcase2_32_points()
{
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 12, 0 };
	point p1 = { 15, 1 };
	point p2 = { 20, 2 };
	point p3 = { 21, 1 };
	point p4 = { 5, 2 };
	point p5 = { 4, 1 };
	point p6 = { 4, 24 };
	point p7 = { 21, 24 };
	point p8 = { 20, 20 };
	point p9 = { 5, 20 };
	point p10 = { 18, 23 };
	point p11 = { 8, 23 };
	point p12 = { 12, 24 };
	point p13 = { 12, 20 };
	point p14 = { 13, 20 };
	point p15 = { 13, 24 };
	point p16 = { 6, 10 };
	point p17 = { 6, 9 };
	point p18 = { 8, 19 };
	point p19 = { 13, 4 };
	point p20 = { 14, 4 };
	point p21 = { 15, 7 };
	point p22 = { 18, 16 };
	point p23 = { 19, 16 };
	point p24 = { 11, 16 };
	point p25 = { 11, 17 };
	point p26 = { 20, 4 };
	point p27 = { 17, 7 };
	point p28 = { 16, 9 };
	point p29 = { 9, 14 };
	point p30 = { 10, 10 };
	point p31 = { 15, 10 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);
	Q.push_back(p8);
	Q.push_back(p9);
	Q.push_back(p10);
	Q.push_back(p11);
	Q.push_back(p12);
	Q.push_back(p13);
	Q.push_back(p14);
	Q.push_back(p15);
	Q.push_back(p16);
	Q.push_back(p17);
	Q.push_back(p18);
	Q.push_back(p19);
	Q.push_back(p20);
	Q.push_back(p21);
	Q.push_back(p22);
	Q.push_back(p23);
	Q.push_back(p24);
	Q.push_back(p25);
	Q.push_back(p26);
	Q.push_back(p27);
	Q.push_back(p28);
	Q.push_back(p29);
	Q.push_back(p30);
	Q.push_back(p31);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);
	Q2.push_back(p8);
	Q2.push_back(p9);
	Q2.push_back(p10);
	Q2.push_back(p11);
	Q2.push_back(p12);
	Q2.push_back(p13);
	Q2.push_back(p14);
	Q2.push_back(p15);
	Q2.push_back(p16);
	Q2.push_back(p17);
	Q2.push_back(p18);
	Q2.push_back(p19);
	Q2.push_back(p20);
	Q2.push_back(p21);
	Q2.push_back(p22);
	Q2.push_back(p23);
	Q2.push_back(p24);
	Q2.push_back(p25);
	Q2.push_back(p26);
	Q2.push_back(p27);
	Q2.push_back(p28);
	Q2.push_back(p29);
	Q2.push_back(p30);
	Q2.push_back(p31);

	//CASE 2 n = 32 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 2 n = 32 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//TEST CASES FOR 16 POINT SETS

//test case 1, where h > logn, or in this case, h = 14 and n = 16
void testcase1_16_points()
{
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 10, 1 };
	point p1 = { 15, 1 };
	point p2 = { 20, 2 };
	point p3 = { 21, 3 };
	point p4 = { 5, 2 };
	point p5 = { 4, 3 };
	point p6 = { 4, 10 };
	point p7 = { 21, 10 };
	point p8 = { 20, 20 };
	point p9 = { 5, 20 };
	point p10 = { 18, 23 };
	point p11 = { 8, 23 };
	point p12 = { 12, 24 };
	point p13 = { 12, 20 };
	point p14 = { 13, 20 };
	point p15 = { 13, 24 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);
	Q.push_back(p8);
	Q.push_back(p9);
	Q.push_back(p10);
	Q.push_back(p11);
	Q.push_back(p12);
	Q.push_back(p13);
	Q.push_back(p14);
	Q.push_back(p15);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);
	Q2.push_back(p8);
	Q2.push_back(p9);
	Q2.push_back(p10);
	Q2.push_back(p11);
	Q2.push_back(p12);
	Q2.push_back(p13);
	Q2.push_back(p14);
	Q2.push_back(p15);
	
	//CASE 1 n = 16 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 1 n = 16 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//test case 2, where h <= logn, or in this case, h = 4 and n = 16
void testcase2_16_points()
{
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 10, 1 };
	point p1 = { 15, 1 };
	point p2 = { 20, 2 };
	point p3 = { 21, 1 };
	point p4 = { 5, 2 };
	point p5 = { 4, 1 };
	point p6 = { 4, 24 };
	point p7 = { 21, 24 };
	point p8 = { 20, 20 };
	point p9 = { 5, 20 };
	point p10 = { 18, 23 };
	point p11 = { 8, 23 };
	point p12 = { 12, 24 };
	point p13 = { 12, 20 };
	point p14 = { 13, 20 };
	point p15 = { 13, 24 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);
	Q.push_back(p8);
	Q.push_back(p9);
	Q.push_back(p10);
	Q.push_back(p11);
	Q.push_back(p12);
	Q.push_back(p13);
	Q.push_back(p14);
	Q.push_back(p15);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);
	Q2.push_back(p8);
	Q2.push_back(p9);
	Q2.push_back(p10);
	Q2.push_back(p11);
	Q2.push_back(p12);
	Q2.push_back(p13);
	Q2.push_back(p14);
	Q2.push_back(p15);

	//CASE 2, n = 16 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 2, n = 16 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//test case 1, where h > logn, or in this case, h = 8 and n = 8
void testcase1_8_points()
{
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 10, 1 };
	point p1 = { 9, 3 };
	point p2 = { 16, 3 };
	point p3 = { 15, 1 };
	point p4 = { 9, 5 };
	point p5 = { 16, 5 };
	point p6 = { 15, 7 };
	point p7 = { 10, 7 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);

	//CASE 1, n = 8 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 1, n = 8 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//test case 2, where h <= logn, or in this case, h = 3 and n = 8
void testcase2_8_points()
{
	vector<point> Q;
	vector<point> Q2;
	point p0 = { 1, 1 };
	point p1 = { 9, 3 };
	point p2 = { 16, 3 };
	point p3 = { 24, 1 };
	point p4 = { 12, 12 };
	point p5 = { 16, 5 };
	point p6 = { 15, 7 };
	point p7 = { 10, 7 };

	Q.push_back(p0);
	Q.push_back(p1);
	Q.push_back(p2);
	Q.push_back(p3);
	Q.push_back(p4);
	Q.push_back(p5);
	Q.push_back(p6);
	Q.push_back(p7);

	Q2.push_back(p0);
	Q2.push_back(p1);
	Q2.push_back(p2);
	Q2.push_back(p3);
	Q2.push_back(p4);
	Q2.push_back(p5);
	Q2.push_back(p6);
	Q2.push_back(p7);

	//CASE 2, n = 8 graham scan
	vector<point> convex_hull = graham_scan(Q);
	cout << "According to Graham's Scan: " << endl;
	for (int i = 0; i < convex_hull.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull.at(i).x << ", " << convex_hull.at(i).y << endl;
	}
	cout << endl;

	//CASE 2, n = 8 jarvis march
	vector<point> convex_hull2 = jarvis_march(Q2);
	cout << "According to Jarvis's March: " << endl;
	for (int i = 0; i < convex_hull2.size(); i++)
	{
		cout << "Convex Hull Element: " << convex_hull2.at(i).x << ", " << convex_hull2.at(i).y << endl;
	}
	cout << endl;
}

//main - test function
int main()
{
	//-----------------------------------------------------------------
	//CASE 1, SET OF 32 POINTS, N = 32, AND H = 14 (H > LOGN, OR H > 5)
	cout << "Case 1, 32 points: " << endl;
	testcase1_32_points();

	//CASE 2, SET OF 32 POINTS, N = 32, AND H = 5, (H = LOGN, OR H = 5)
	cout << "Case 2, 32 points: " << endl;
	testcase2_32_points();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	//CASE 1, SET OF 16 POINTS, N = 16, AND H = 14 (H > LOGN, OR H > 4)
	cout << "Case 1, 16 points: " << endl;
	testcase1_16_points();

	//CASE 2, SET OF 16 POINTS, N = 16, AND H = 4, (H = LOGN, OR H = 4)
	cout << "Case 2, 16 points: " << endl;
	testcase2_16_points();
	//-----------------------------------------------------------------
	//-----------------------------------------------------------------
	//CASE 1, SET OF 08 POINTS, N = 8, AND H = 8 (H > LOGN, OR H > 3)
	cout << "Case 1, 08 points: " << endl;
	testcase1_8_points();

	//CASE 2, SET OF 08 POINTS, N = 8, AND H = 3, (H = LOGN, OR H = 3)
	cout << "Case 2, 08 points: " << endl;
	testcase2_8_points();
	//-----------------------------------------------------------------

	int x;
	cin >> x;
	return 0;
}