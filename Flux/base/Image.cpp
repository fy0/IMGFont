
#include "Image.h"

Color fontcolor;
Color bgcolor(0xFF,0xFF,0xFF,0xFF);

void ImageInit()
{	
	ilInit();
	iluInit();
	ilutInit();
}

const int LoadTexture(const string& fn)
{
	ILuint imgRef;

	ilGenImages(1, &imgRef);
	ilBindImage(imgRef);

	if (!ilLoadImage(fn.c_str())) {
		ILenum error = ilGetError();
		do  {
			printf("%s\n", iluErrorString(error));
		} while ((error = ilGetError()));

		ilDeleteImages(1, &imgRef);
		return 0;
	}

	GLuint	TexID = 0;

	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, IL_FALSE);

	if (!ilutGLTexImage(0)) 
	{
		glDeleteTextures(1, &TexID);
		return 0;
	}

	return TexID;
}

ILuint ImgNew(int width, int height, byte* data, int channel, int Format)
{
	ILuint imageID = ilGenImage() ;
	ilBindImage( imageID ) ;

	if (!data) {
		int sizeOfByte = sizeof( unsigned char );
		int theSize = width * height * sizeOfByte * channel;
		data = (unsigned char*)malloc( theSize );
		if (channel == 4) {
			for(int i=0;i<theSize;i+=4) {
				data[i]   = bgcolor.R;
				data[i+1] = bgcolor.G;
				data[i+2] = bgcolor.B;
				data[i+3] = bgcolor.A;
			}
		} else if (channel == 3) {
			for(int i=0;i<theSize;i+=3) {
				data[i]   = bgcolor.R;
				data[i+1] = bgcolor.G;
				data[i+2] = bgcolor.B;
			}
		}
	}

	ilTexImage(
		width, height,
		1,  // OpenIL supports 3d textures!  but we don't want it to be 3d.  so
		// we just set this to be 1
		channel,  // 3 channels:  one for R , one for G, one for B
		Format,  // duh, yeah use rgb!  coulda been rgba if we wanted trans
		IL_UNSIGNED_BYTE,  // the type of data the imData array contains (next)
		data  // and the array of bytes represneting the actual image data
	);
	return imageID;
}

void ImgSave(ILuint imgID, ILenum fileformat, const string& filename)
{
	ilBindImage(imgID);
	ilEnable(IL_FILE_OVERWRITE);
	ilSave(fileformat, filename.c_str()) ;
}

void SetBackgroundColor(int R, int G, int B, int A)
{
	bgcolor = Color(R,G,B,A);
}

void SetFontColor(int R, int G, int B, int A)
{
	fontcolor = Color(R,G,B,A);
}

Color GetBackgroundColor()
{
	return bgcolor;
}

Color GetFontColor()
{
	return fontcolor;
}
