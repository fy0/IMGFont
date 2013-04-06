
typedef unsigned int   ILenum;
typedef unsigned char  ILboolean;
typedef unsigned int   ILbitfield;
typedef signed char    ILbyte;
typedef signed short   ILshort;
typedef int     	   ILint;
typedef size_t         ILsizei;
typedef unsigned char  ILubyte;
typedef unsigned short ILushort;
typedef unsigned int   ILuint;
typedef float          ILfloat;
typedef float          ILclampf;
typedef double         ILdouble;
typedef double         ILclampd;

#ifdef _MSC_VER
typedef __int64          ILint64;
typedef unsigned __int64 ILuint64;
#else
typedef long long int          ILint64;
typedef long long unsigned int ILuint64;
#endif


#include <limits.h>
#ifdef _UNICODE
	#ifndef _WIN32_WCE
		#include <wchar.h>
	#endif
	//if we use a define instead of a typedef,
	//ILconst_string works as intended
	#define ILchar wchar_t
	#define ILstring wchar_t*
	#define ILconst_string  wchar_t const *
#else
	//if we use a define instead of a typedef,
	//ILconst_string works as intended
	#define ILchar char
	#define ILstring char*
	#define ILconst_string char const *
#endif //_UNICODE

#define IL_FALSE			0
#define IL_TRUE				1


#define IL_COLOUR_INDEX     0x1900
#define IL_COLOR_INDEX      0x1900
#define IL_ALPHA			0x1906
#define IL_RGB              0x1907
#define IL_RGBA             0x1908
#define IL_BGR              0x80E0
#define IL_BGRA             0x80E1
#define IL_LUMINANCE        0x1909
#define IL_LUMINANCE_ALPHA  0x190A

#define IL_TYPE_UNKNOWN 0x0000
#define IL_BMP          0x0420  //!< Microsoft Windows Bitmap - .bmp extension
#define IL_CUT          0x0421  //!< Dr. Halo - .cut extension
#define IL_DOOM         0x0422  //!< DooM walls - no specific extension
#define IL_DOOM_FLAT    0x0423  //!< DooM flats - no specific extension
#define IL_ICO          0x0424  //!< Microsoft Windows Icons and Cursors - .ico and .cur extensions
#define IL_JPG          0x0425  //!< JPEG - .jpg, .jpe and .jpeg extensions
#define IL_JFIF         0x0425  //!<
#define IL_ILBM         0x0426  //!< Amiga IFF (FORM ILBM) - .iff, .ilbm, .lbm extensions
#define IL_PCD          0x0427  //!< Kodak PhotoCD - .pcd extension
#define IL_PCX          0x0428  //!< ZSoft PCX - .pcx extension
#define IL_PIC          0x0429  //!< PIC - .pic extension
#define IL_PNG          0x042A  //!< Portable Network Graphics - .png extension
#define IL_PNM          0x042B  //!< Portable Any Map - .pbm, .pgm, .ppm and .pnm extensions
#define IL_SGI          0x042C  //!< Silicon Graphics - .sgi, .bw, .rgb and .rgba extensions
#define IL_TGA          0x042D  //!< TrueVision Targa File - .tga, .vda, .icb and .vst extensions
#define IL_TIF          0x042E  //!< Tagged Image File Format - .tif and .tiff extensions
#define IL_CHEAD        0x042F  //!< C-Style Header - .h extension
#define IL_RAW          0x0430  //!< Raw Image Data - any extension
#define IL_MDL          0x0431  //!< Half-Life Model Texture - .mdl extension
#define IL_WAL          0x0432  //!< Quake 2 Texture - .wal extension
#define IL_LIF          0x0434  //!< Homeworld Texture - .lif extension
#define IL_MNG          0x0435  //!< Multiple-image Network Graphics - .mng extension
#define IL_JNG          0x0435  //!< 
#define IL_GIF          0x0436  //!< Graphics Interchange Format - .gif extension
#define IL_DDS          0x0437  //!< DirectDraw Surface - .dds extension
#define IL_DCX          0x0438  //!< ZSoft Multi-PCX - .dcx extension
#define IL_PSD          0x0439  //!< Adobe PhotoShop - .psd extension
#define IL_EXIF         0x043A  //!< 
#define IL_PSP          0x043B  //!< PaintShop Pro - .psp extension
#define IL_PIX          0x043C  //!< PIX - .pix extension
#define IL_PXR          0x043D  //!< Pixar - .pxr extension
#define IL_XPM          0x043E  //!< X Pixel Map - .xpm extension
#define IL_HDR          0x043F  //!< Radiance High Dynamic Range - .hdr extension
#define IL_ICNS			0x0440  //!< Macintosh Icon - .icns extension
#define IL_JP2			0x0441  //!< Jpeg 2000 - .jp2 extension
#define IL_EXR			0x0442  //!< OpenEXR - .exr extension
#define IL_WDP			0x0443  //!< Microsoft HD Photo - .wdp and .hdp extension
#define IL_VTF			0x0444  //!< Valve Texture Format - .vtf extension
#define IL_WBMP			0x0445  //!< Wireless Bitmap - .wbmp extension
#define IL_SUN			0x0446  //!< Sun Raster - .sun, .ras, .rs, .im1, .im8, .im24 and .im32 extensions
#define IL_IFF			0x0447  //!< Interchange File Format - .iff extension
#define IL_TPL			0x0448  //!< Gamecube Texture - .tpl extension
#define IL_FITS			0x0449  //!< Flexible Image Transport System - .fit and .fits extensions
#define IL_DICOM		0x044A  //!< Digital Imaging and Communications in Medicine (DICOM) - .dcm and .dicom extensions
#define IL_IWI			0x044B  //!< Call of Duty Infinity Ward Image - .iwi extension
#define IL_BLP			0x044C  //!< Blizzard Texture Format - .blp extension
#define IL_FTX			0x044D  //!< Heavy Metal: FAKK2 Texture - .ftx extension
#define IL_ROT			0x044E  //!< Homeworld 2 - Relic Texture - .rot extension
#define IL_TEXTURE		0x044F  //!< Medieval II: Total War Texture - .texture extension
#define IL_DPX			0x0450  //!< Digital Picture Exchange - .dpx extension
#define IL_UTX			0x0451  //!< Unreal (and Unreal Tournament) Texture - .utx extension
#define IL_MP3			0x0452  //!< MPEG-1 Audio Layer 3 - .mp3 extension

#define IL_PVR			0x0480
#define IL_PVR_RGBA2	0x047F
#define IL_PVR_RGBA4	0x0480
#define IL_PVR_RGBA8	0x0481
