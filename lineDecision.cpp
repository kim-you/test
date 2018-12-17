
#include <iostream>
#include < windows.h>
#include <cstring>
#include <vector>   
#include < stdio.h>
#include <algorithm>
#include < opencv2\opencv.hpp>


using namespace cv;
using namespace std;

bool comp(const Point2f a, const Point2f b) {

	if (a.x != b.x) return a.x < b.x;
	else if (a.y != b.y) return a.y < b.y;

}
float distPoints(Point2f a, Point2f b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float radTodegree(float n) {
	float temp = n*(180.0 / CV_PI);

	if (temp < 0)
		return 180 - abs(temp);
	else
		return temp;
}

bool lineDecision(Vec4i line, int gridSize, Mat angleMap, float decision_ratio) {

	Point2f p1 = Point2f(line[0], line[1]);
	Point2f p2 = Point2f(line[2], line[3]);
	float angle_deg;
	float angle;
	float b;
	int xp1 = (int)p1.x / gridSize;
	int yp1 = (int)p1.y / gridSize;

	int xp2 = (int)p2.x / gridSize;
	int yp2 = (int)p2.y / gridSize;

	bool inf = false;
	if (p1.x == p2.x) {
		inf = true;
		angle_deg = 90;
	}
	else {
		angle = (p2.y - p1.y) / (p2.x - p1.x);
		b = p2.y - angle*p2.x;
		angle_deg = radTodegree(atan(angle));
	}

	vector<Point2f> sigPoints;
	sigPoints.push_back(p1);
	sigPoints.push_back(p2);

	for (int i = MIN(xp1, xp2) + 1; i <= MAX(xp1, xp2); i++)
	{
		int tempx = i * gridSize;
		int tempy = tempx * angle + b;

		sigPoints.push_back(Point2f(tempx, tempy));
	}
	
	for (int i = MIN(yp1, yp2) + 1; i <= MAX(yp1, yp2); i++)
	{
		int tempy;
		int tempx;
		tempy = i * gridSize;

		if (inf) 
			tempx = p1.x;
		else 
			tempx = (tempy - b) / angle;

		sigPoints.push_back(Point2f(tempx, tempy));
	}
	
	
	//for (int i = 0; i < sigPoints.size(); i++) {
	//	cout << sigPoints[i] << endl;
	//}

	stable_sort(sigPoints.begin(), sigPoints.end(), comp);

	struct lineparts {
		int gridx;
		int gridy;
		float length;
	};

	vector<lineparts> segLine;
	
	for (int i = 0; i < sigPoints.size() -1; i++) {
		
		lineparts temp;
		temp.length = distPoints(sigPoints[i], sigPoints[i + 1]);
		temp.gridx = (int)sigPoints[i].x / gridSize;
		temp.gridy = (int)sigPoints[i].y / gridSize;
	
		segLine.push_back(temp);
	}
	float m_length = 0;

	for (int i = 0; i < segLine.size(); i++) {
		float gridangle = angleMap.at<float>(segLine[i].gridy,segLine[i].gridx);
		bool goodangle;
		if (gridangle < 0)
			goodangle = true;
		else {
			float negangle = gridangle < 90 ? gridangle + 90 : gridangle - 90;
			goodangle = abs(gridangle - angle_deg) <= abs(negangle - angle_deg) ? true : false;
		}

		if (goodangle)
			m_length += segLine[i].length;
	//	cout << sigPoints[i] << "  " << segLine[i].gridy << " " << segLine[i].gridx << "  " << segLine[i].length << endl;
	}


	if (m_length >= distPoints(p1, p2)*decision_ratio)
		return true;
	else
		return false;
}

void main()
{
	
	Vec4i a;
	a[0] = 45; 
	a[1] = 45;
	a[2] = 60;
	a[3] = 60;
	Mat k;
	lineDecision (a, 10, k, 0.6);

	system("PAUSE");
}

