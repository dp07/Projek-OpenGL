struct color{
    double R;
    double G;
    double B;
    color(){

    }
    color(double r, double g, double b){
        if(r>1 || g>1 || b>1){
            r=r/255.0;
            g=g/255.0;
            b=b/255.0;
        }

        R=r;
        G=g;
        B=b;
    }


};

struct point3d{
    double X;
    double Y;
    double Z;
    point3d(){
    }
    point3d(double x, double y, double z){
        X=x;
        Y=y;
        Z=z;
    }
};

void vertex3d(point3d p){
        glVertex3d(p.X,p.Y,p.Z);
}
void color3(color c){
    glColor3d(c.R,c.G,c.B);
}


struct linearImage{
   GLubyte ar[2048*1768*4];
};

struct imageInfo{
    GLubyte image[2048][1768][4];
    unsigned int imageHeight;
    unsigned int imageWidth;
    unsigned long fileSize;
};


/***
p 1 2 3 4 c
***/
void drawQuad(point3d point1,point3d point2,point3d point3,point3d point4, color col){
    glBegin(GL_QUADS);
    glColor3d(col.R,col.G,col.B);
    glVertex3d(point1.X,point1.Y,point1.Z);
    glVertex3d(point2.X,point2.Y,point2.Z);
    glVertex3d(point3.X,point3.Y,point3.Z);
    glVertex3d(point4.X,point4.Y,point4.Z);
    glEnd();
}
/***
p 1 2 3 4 c 1
p 1 2 6 5 c 2
p 2 3 7 6 c 3
p 3 4 8 7 c 4
p 4 1 5 8 c 5
p 5 6 7 8 c 6
***/
void drawQuad3d(point3d eightPoints[], color sixColors[]){
    drawQuad(eightPoints[0],eightPoints[1],eightPoints[2],eightPoints[3],sixColors[0]);
    drawQuad(eightPoints[0],eightPoints[1],eightPoints[5],eightPoints[4],sixColors[1]);
    drawQuad(eightPoints[1],eightPoints[2],eightPoints[6],eightPoints[5],sixColors[2]);
    drawQuad(eightPoints[2],eightPoints[3],eightPoints[7],eightPoints[6],sixColors[3]);
    drawQuad(eightPoints[3],eightPoints[0],eightPoints[4],eightPoints[7],sixColors[4]);
    drawQuad(eightPoints[4],eightPoints[5],eightPoints[6],eightPoints[7],sixColors[5]);
}

void drawLine3d(point3d from, point3d to){
    glBegin(GL_LINE);
    glVertex3d(from.X,from.Y,from.Z);
    glVertex3d(to.X,to.Y,to.Z);
    glEnd();
}

/***
void getLinearImage(imageInfo img){
    int len=0;
    linearImage lin;
	for(unsigned int r=0; r<img.imageHeight; r++)
	{

			for(unsigned int c=0; c<img.imageWidth; c++)
			{
				for(int k=2; k>=0;k--)
				{
					lin.ar[len++] = img.image[r][c][k];
					//linear.Array[len++] = 10;

				}
				lin.ar[len++] = (GLubyte)255;

			}
	}
	//linearImage l;
	return lin;

}

**/

linearImage* getLinearImage(imageInfo *img){
    int len=0;
    linearImage *lin;
	for(unsigned int r=0; r<(*img).imageHeight; r++)
	{

			for(unsigned int c=0; c<(*img).imageWidth; c++)
			{
				for(int k=2; k>=0;k--)
				{
					(*lin).ar[len++] = (*img).image[r][c][k];
					//linear.Array[len++] = 10;

				}
				(*lin).ar[len++] = (GLubyte)255;

			}
	}
	//linearImage l;
	return lin;

}



int loadImage(char *f_name, imageInfo *ptr)
{
	FILE *fp;
	unsigned char blueValue, redValue, greenValue;
	unsigned int r,c;
	unsigned int imageheight, imagewidth;
    unsigned long fileSize;
	if(!(fp = fopen(f_name, "rb")))
	{
		printf("File Open Error\n");
		return 0;
	}

	///seeking bytes from initial position
	fseek(fp,2,0);

	///reads file size
	fread(&fileSize,4,1,fp);

	///seeking bytes from initial position
	fseek(fp,18,0);

	///reading image height and width
	fread(&imagewidth,4,1,fp);
	fseek(fp,22,0);
	fread(&imageheight,4,1,fp);

	printf("%d %d\n",imagewidth,imageheight);

	///now starts data reading
	fseek(fp,54,0);
	//printf("image %d\n")
    ///(*ptr).imageHeight = imageheight;
    /*(*ptr).imageWidth = imagewidth;
    (*ptr).fileSize = fileSize;
	for(r=0; r<imageheight; r++)
	{
		for(c=0; c<imagewidth; c++)
		{
			fread(&blueValue, sizeof(char), 1, fp);
			fread(&greenValue, sizeof(char), 1, fp);
			fread(&redValue , sizeof(char), 1, fp);

			(*ptr).image[r][c][0] = (GLubyte)blueValue;
			(*ptr).image[r][c][1] = (GLubyte)greenValue;
			(*ptr).image[r][c][2] = (GLubyte)redValue;
			(*ptr).image[r][c][3] = (GLubyte)255;

		}
	}


	//end of reading
	fclose(fp);*/
	return 1;
}


