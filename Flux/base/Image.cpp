
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
	if (fileformat >= IL_PVR_RGBA2 && fileformat <= IL_PVR_RGBA8) {
		ILubyte *data = ilGetData();
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		int fileLength;
		byte* _data;
		byte* header2;
		byte* header3;

		byte header1[] = {0x34, 0x00, 0x00, 0x00};

		byte header2_RGBA8[] = {0x00, 0x00, 0x00, 0x00, 0x12, 0x80, 0x00, 0x00};
		byte header3_RGBA8[] = {0x20, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
								0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
								0x00, 0x00, 0x00, 0xFF, 0x50, 0x56, 0x52, 0x21,
								0x01, 0x00, 0x00, 0x00};

		byte header2_RGBA4[] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00};
		byte header3_RGBA4[] = {0x10, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00,
								0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,
								0x0F, 0x00, 0x00, 0x00, 0x50, 0x56, 0x52, 0x21,
								0x01, 0x00, 0x00, 0x00};

		byte header2_RGBA2[] = {0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00};
		byte header3_RGBA2[] = {0x08, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
								0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x50, 0x56, 0x52, 0x21,
								0x01, 0x00, 0x00, 0x00};

		if (fileformat == IL_PVR_RGBA8) {
			fileLength = width*height*4;
			_data = (byte*)malloc(fileLength);
			header2 = header2_RGBA8;
			header3 = header3_RGBA8;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					_data[4*(width*i+j)    ] = data[4*(width*(height-i-1)+j)    ];
					_data[4*(width*i+j) + 1] = data[4*(width*(height-i-1)+j) + 1];
					_data[4*(width*i+j) + 2] = data[4*(width*(height-i-1)+j) + 2];
					_data[4*(width*i+j) + 3] = data[4*(width*(height-i-1)+j) + 3];
				}
			}
		} else if (fileformat == IL_PVR_RGBA4) {
			fileLength = width*height*2;
			_data = (byte*)malloc(fileLength);
			header2 = header2_RGBA4;
			header3 = header3_RGBA4;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					_data[2*(i*width+j)    ] = (data[4*(width*(height-i-1)+j)    ] & 0xF0) | (data[4*(width*(height-i-1)+j) + 3] >> 4);
					_data[2*(i*width+j) + 1] = (data[4*(width*(height-i-1)+j) + 2] & 0xF0) | (data[4*(width*(height-i-1)+j) + 1] >> 4);
				}
			}
		} else if (fileformat == IL_PVR_RGBA2) {
			fileLength = width*height;
			_data = (byte*)malloc(fileLength);
			header2 = header2_RGBA2;
			header3 = header3_RGBA2;

			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					_data[(i*width+j)] = data[4*(width*(height-i-1)+j)];
				}
			}
		}

		FILE* fp = fopen(filename.c_str(), "wb+");
		fwrite(header1, 4, 1, fp);
		fwrite(&height, 4, 1, fp);
		fwrite(&width, 4, 1, fp);
		fwrite(header2, 8, 1, fp);
		fwrite(&fileLength, 4, 1, fp);
		fwrite(header3, 28, 1, fp);
		fwrite(_data, fileLength, 1, fp);
		fclose(fp);
	} else {
		ilEnable(IL_FILE_OVERWRITE);
		ilSave(fileformat, filename.c_str()) ;
	}
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
