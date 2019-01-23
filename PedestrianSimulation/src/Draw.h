#ifndef DRAW_H_
#define DRAW_H_

#include "bmp.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265


class Draw_v{
public:
	virtual void draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void draw_circle(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void draw_round(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void part_of_circle(int x, int y, int p, double a1, double a2, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void part_of_round(int x, int y, int p, double a1, double a2, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void elipsa(int x, int y, int a, int c, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void prostokat(int *tabx,int *taby, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual void wielokat(int x, int y, int p, int n, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &)const=0;
	virtual ~Draw_v(){};
};

class Draw : public Draw_v{
public:
	Draw(){};
	virtual void draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const;
	virtual void draw_circle(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const;
	virtual void draw_round(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const;
	virtual void part_of_circle(int x, int y, int p, double a1, double a2, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const;
	virtual void part_of_round(int x, int y, int p, double a1, double a2, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const;
	virtual void elipsa(int x, int y, int a, int c, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &bmp)const;
	virtual void prostokat(int *tabx,int *taby, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &bmp)const;
	virtual void wielokat(int x, int y, int p, int n, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP &bmp)const;
	virtual ~Draw(){};
};

#endif /* DRAW_H_ */
