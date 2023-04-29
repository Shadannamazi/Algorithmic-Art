
#include "stats.h"

stats::stats(PNG& im) {

    for (unsigned int x = 0; x < im.width(); x++) {

		int height = im.height();
		vector<long> sumRCol (height);
		vector<long> sumBCol (height);
		vector<long> sumGCol (height);
		vector<long> sumsqRCol (height);
		vector<long> sumsqGCol (height);
		vector<long> sumsqBCol (height);
											
		sumRed.push_back(sumRCol);				
		sumGreen.push_back(sumGCol);
		sumBlue.push_back(sumBCol);
		sumsqRed.push_back(sumsqRCol);
		sumsqGreen.push_back(sumsqGCol);
		sumsqBlue.push_back(sumsqBCol);
		
		for (unsigned int y = 0; y < im.height(); y++) {
			
			RGBAPixel* pixel = im.getPixel(x, y);
			
			if (x > 0 && y > 0)	{
				sumRed[x][y] = sumRed[x-1][y] + sumRed[x][y-1] - sumRed[x-1][y-1] + (long) pixel->r;
				sumGreen[x][y] = sumGreen[x-1][y] + sumGreen[x][y-1] - sumGreen[x-1][y-1] + (long) pixel->g;
				sumBlue[x][y] = sumBlue[x-1][y] + sumBlue[x][y-1] - sumBlue[x-1][y-1] + (long) pixel->b;
				sumsqRed[x][y] = sumsqRed[x-1][y] + sumsqRed[x][y-1] - sumsqRed[x-1][y-1] + (long) pow((double) pixel->r, 2);
				sumsqGreen[x][y] = sumsqGreen[x-1][y] + sumsqGreen[x][y-1] - sumsqGreen[x-1][y-1] + (long) pow((double) pixel->g, 2);
				sumsqBlue[x][y] = sumsqBlue[x-1][y] + sumsqBlue[x][y-1] - sumsqBlue[x-1][y-1] + (long) pow((double) pixel->b, 2);
			}
			
			else if (x > 0 && y == 0){
				sumRed[x][y] = sumRed[x-1][y] + (long) pixel->r;
				sumGreen[x][y] = sumGreen[x-1][y] + (long) pixel->g;
				sumBlue[x][y] = sumBlue[x-1][y] + (long) pixel->b;
				sumsqRed[x][y] = sumsqRed[x-1][y] + (long) pow((double) pixel->r, 2);
				sumsqGreen[x][y] = sumsqGreen[x-1][y] + (long) pow((double) pixel->g, 2);
				sumsqBlue[x][y] = sumsqBlue[x-1][y] + (long) pow((double) pixel->b, 2);
			}
			
			else if (x == 0 && y > 0){
				sumRed[x][y] = sumRed[x][y-1] + (long) pixel->r;
				sumGreen[x][y] = sumGreen[x][y-1] + (long) pixel->g;
				sumBlue[x][y] = sumBlue[x][y-1] + (long) pixel->b;
				sumsqRed[x][y] = sumsqRed[x][y-1] + (long) pow((double) pixel->r, 2);
				sumsqGreen[x][y] = sumsqGreen[x][y-1] + (long) pow((double) pixel->g, 2);
				sumsqBlue[x][y] = sumsqBlue[x][y-1] + (long) pow((double) pixel->b, 2);
			}
			
			else{
				sumRed[x][y] = (long) pixel->r;
				sumGreen[x][y] = (long) pixel->g;
				sumBlue[x][y] = (long) pixel->b;
				sumsqRed[x][y] = (long) pow((double) pixel->r, 2);
				sumsqGreen[x][y] = (long) pow((double) pixel->g, 2);
				sumsqBlue[x][y] = (long) pow((double) pixel->b, 2);
			}		

		}
			
			


	}
}

long stats::getSum(char channel, pair<int, int> ul, int dim) {
    long res = 0;
    int x = ul.first;
	int y = ul.second;
    int off = pow(2,dim) - 1;
    if (channel == 'r'){
        if (x>0 && y>0){
			res = sumRed[x+off][y+off] - sumRed[x-1][y+off] - sumRed[x+off][y-1] + sumRed[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumRed[x+off][y+off] - sumRed[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumRed[x+off][y+off] - sumRed[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumRed[x+off][y+off];
        }

    } else if (channel == 'g'){
        if (x>0 && y>0){
			res = sumGreen[x+off][y+off] - sumGreen[x-1][y+off] - sumGreen[x+off][y-1] + sumGreen[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumGreen[x+off][y+off] - sumGreen[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumGreen[x+off][y+off] - sumGreen[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumGreen[x+off][y+off];
        }

    } else if (channel == 'b'){
        if (x>0 && y>0){
			res = sumBlue[x+off][y+off] - sumBlue[x-1][y+off] - sumBlue[x+off][y-1] + sumBlue[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumBlue[x+off][y+off] - sumBlue[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumBlue[x+off][y+off] - sumBlue[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumBlue[x+off][y+off];
        }
    }
    return res;
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
    long res = 0;
    int x = ul.first;
	int y = ul.second;
    int off = pow(2,dim) - 1;
    if (channel == 'r'){
        if (x>0 && y>0){
			res = sumsqRed[x+off][y+off] - sumsqRed[x-1][y+off] - sumsqRed[x+off][y-1] + sumsqRed[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumsqRed[x+off][y+off] - sumsqRed[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumsqRed[x+off][y+off] - sumsqRed[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumsqRed[x+off][y+off];
        }

    } else if (channel == 'g'){
        if (x>0 && y>0){
			res = sumsqGreen[x+off][y+off] - sumsqGreen[x-1][y+off] - sumsqGreen[x+off][y-1] + sumsqGreen[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumsqGreen[x+off][y+off] - sumsqGreen[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumsqGreen[x+off][y+off] - sumsqGreen[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumsqGreen[x+off][y+off];
        }

    } else if (channel == 'b'){
        if (x>0 && y>0){
			res = sumsqBlue[x+off][y+off] - sumsqBlue[x-1][y+off] - sumsqBlue[x+off][y-1] + sumsqBlue[x-1][y-1];
        } 
        else if (x > 0 && y == 0){
			res = sumsqBlue[x+off][y+off] - sumsqBlue[x-1][y+off];
        }
        else if (x ==0 && y > 0){
			res = sumsqBlue[x+off][y+off] - sumsqBlue[x+off][y-1];
        }
        else if (x == 0 && y == 0){
            res = sumsqBlue[x+off][y+off];
        }
    }
	return res;
}

long stats::rectArea(int dim) {
	return pow(2,dim) * pow(2,dim);
    
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {


    long red = getSumSq('r',ul,dim) - ((getSum('r',ul,dim)*getSum('r',ul,dim))/rectArea(dim));
    long green = getSumSq('g',ul,dim) - ((getSum('g',ul,dim)*getSum('g',ul,dim))/rectArea(dim));
    long blue = getSumSq('b',ul,dim) - ((getSum('b',ul,dim)*getSum('b',ul,dim))/rectArea(dim));

    long var = red+ blue + green;


    return var;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    long area = rectArea(dim);
    long avR = getSum('r',ul,dim)/area;
    long avG = getSum('g',ul,dim)/area;
    long avB = getSum('b',ul,dim)/area;
    return RGBAPixel(avR, avG,avB);
}
