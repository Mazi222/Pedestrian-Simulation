#include "Draw.h"

void Draw::draw_line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP &bmp)const
{
	if(x1!=x2)
	{
		double a=(double)(y1-y2)/(x1-x2);
		double c=y1-a*x1;
		int y,xp;
		if(x1>x2)
		{
			int tmp=x2;
			x2=x1;
			x1=tmp;
		}
		for(int i=x1;i<=x2;++i)
		{
			y=abs((a*i)+c);
			if(bmp.is_in(i,y))
			{
				bmp.setPixel(i,y,r,g,b);
			}
		}
		if(y1>y2)
		{
			int tmp=y2;
			y2=y1;
			y1=tmp;
		}
		for(int i=y1;i<=y2;++i)
		{
			xp=(i-c)/a;
			if(bmp.is_in(xp,i))
				bmp.setPixel(xp,i,r,g,b);
		}
	}
	else if(x1==x2)
	{

		if(y1>y2)
		{
			int tmp=y2;
			y2=y1;
			y1=tmp;
		}
		for(int i=y1;i<=y2;++i)
		{
			if(bmp.is_in(x1,i))
				bmp.setPixel(x1,i,r,g,b);
		}
	}
}
void Draw::draw_circle(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP & bmp)const
{
	int xp,yp;
	for(double i = 0;i<=2*PI;i+=(PI/(360*p/50)))
	{
		xp=x+p*cos(i);
		yp=y-p*sin(i);
		if(bmp.is_in(xp,yp))
			bmp.setPixel(xp,yp,r,g,b);
	}
}
void Draw::draw_round(int x, int y, int p, unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP & bmp)const
{
	int p2=p*p,sq,sqp;
	for(int i=-p;i<=p;++i)
	{
		sq=sqrt(p2-i*i);

		if(i!=-p && (sq!=sqp-1 || sq!=sqp+1) && sq!=sqp)
		{
			for(int j=0;j<=abs(sqp-sq);++j)
			{
				if(i<0)
				{
					if(bmp.is_in(x+i,y+sqp-j-1))
						bmp.setPixel(x+i,y+sqp-j-1,r,g,b);
					if(bmp.is_in(x+i,y-sqp+j+1))
						bmp.setPixel(x+i,y-sqp+j+1,r,g,b);
				}
				else
				{
					if(bmp.is_in(x+i,y+sqp-j))
						bmp.setPixel(x+i-1,y+sqp-j,r,g,b);
					if(bmp.is_in(x+i,y-sqp+j))
						bmp.setPixel(x+i-1,y-sqp+j,r,g,b);
				}
			}
		}
		sqp=sq;
		for(int j=0;j<=sq;++j)
		{
			if(bmp.is_in(x+i,y+j))
				bmp.setPixel(x+i,y+j,r,g,b);
			if(bmp.is_in(x+i,y-j))
				bmp.setPixel(x+i,y-j,r,g,b);
		}
	}
}
void Draw::part_of_circle(int x, int y, int p, double a1, double a2,
		unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP & bmp)const
{
	int x1=x+p*cos(a1), x2=x+p*cos(a2);
	int y1=y-p*sin(a1), y2=y-p*sin(a2);

	draw_line(x,y,x1,y1,r,g,b,bmp);
	draw_line(x,y,x2,y2,r,g,b,bmp);

	if(a1>a2)
	{
		double tmp=a1;
		a1=a2;
		a2=tmp;
	}

	int xp,yp;
	for(double i = a1;i<a2;i+=(PI/(360*(p/50))))
	{
		xp=x+p*cos(i);
		yp=y-p*sin(i);
		if(bmp.is_in(xp,yp))
			bmp.setPixel(xp,yp,r,g,b);
	}
}
void Draw::part_of_round(int x, int y, int p, double a1, double a2,
		unsigned char r, unsigned char g, unsigned char b,JiMP2::BMP & bmp)const
{
	int x1=x+p*cos(a1), x2=x+p*cos(a2);
	int y1=y-p*sin(a1), y2=y-p*sin(a2);

	draw_line(x,y,x1,y1,r,g,b,bmp);
	draw_line(x,y,x2,y2,r,g,b,bmp);

	if(a1>a2)
	{
		double tmp=a1;
		a1=a2;
		a2=tmp;
	}

	int xp,yp;
	for(int j = 0; j<=p;++j)
	{
		for(double i = a1;i<a2;i+=(PI/(360*(p/50))))
		{
			xp=x+j*cos(i);
			yp=y-j*sin(i);
			if(bmp.is_in(xp,yp))
				bmp.setPixel(xp,yp,r,g,b);
		}
	}
}
void Draw::elipsa(int x, int y, int a, int c, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP & bmp)const
{
	int xp,yp;
	for(double i = 0;i<2*PI;i+=(PI/(360*a/100) ))
	{
		xp=x+a*cos(i);
		yp=y-c*sin(i);
		if(bmp.is_in(xp,yp))
			bmp.setPixel(xp,yp,r,g,b);
	}
}
void Draw::prostokat(int *tabx,int *taby, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP & bmp)const
{
	draw_line(tabx[0],taby[0],tabx[1],taby[1],r,g,b,bmp);
	draw_line(tabx[1],taby[1],tabx[2],taby[2],r,g,b,bmp);
	draw_line(tabx[2],taby[2],tabx[3],taby[3],r,g,b,bmp);
	draw_line(tabx[3],taby[3],tabx[0],taby[0],r,g,b,bmp);
}
void Draw::wielokat(int x, int y, int p,int n, unsigned char r, unsigned char g, unsigned char b, JiMP2::BMP & bmp)const
{
	int x1=0,y1=0,x2,y2;
	for(int i=1;i<=n;++i)
	{
		x1=(x+p*cos(2*PI/n *i));
		y1=y-p*sin(2*PI/n *i);
		x2=x+p*cos(2*PI/n *(i+1));
		y2=y-p*sin(2*PI/n *(i+1));
		draw_line(x1,y1,x2,y2,r,g,b,bmp);
	}
}


